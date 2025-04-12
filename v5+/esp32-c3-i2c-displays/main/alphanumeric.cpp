#include "alphanumeric.hpp"
#include <cstring>

AlphaNumeric::AlphaNumeric(uint8_t _device_address) {
    device_address = _device_address;
}

esp_err_t AlphaNumeric::initialize() {
    auto error = initialize_device_handle();
    if (error != ESP_OK) return error;
    return ht16k33_initialize(device_handle);
}

esp_err_t AlphaNumeric::reset() {
    uint8_t all_data[] = {0,0,0,0,0,0,0,0,0};
    return i2c_master_transmit(device_handle,
        all_data, sizeof(all_data), I2C_TICKS_TO_WAIT);
}

esp_err_t AlphaNumeric::test() {
    uint8_t all_data[] = {0,0xff,0x7f,0xFF,0x7F,0xFF,0x7F,0xFF,0x7F};
    return i2c_master_transmit(device_handle,
        all_data, sizeof(all_data), I2C_TICKS_TO_WAIT);
}

esp_err_t AlphaNumeric::display(uint16_t number_to_display) {
    uint8_t dig1 = (number_to_display >> 12) & 0x0f;
    dig1 += (dig1 > 9 ? ascii_table_alpha_start : ascii_table_numeric_start);
    uint8_t dig2 = (number_to_display >> 8) & 0x0f;
    dig2 += (dig2 > 9 ? ascii_table_alpha_start : ascii_table_numeric_start);
    uint8_t dig3 = (number_to_display >> 4) & 0x0f;
    dig3 += (dig3 > 9 ? ascii_table_alpha_start : ascii_table_numeric_start);
    uint8_t dig4 = number_to_display & 0x0f;
    dig4 += (dig4 > 9 ? ascii_table_alpha_start : ascii_table_numeric_start);
    uint8_t all_data[9];
    all_data[0] = 0;
    all_data[1] = ascii_table[dig1] & 0xff;
    all_data[2] = (ascii_table[dig1] >> 8) & 0xff;
    all_data[3] = ascii_table[dig2] & 0xff;
    all_data[4] = (ascii_table[dig2] >> 8) & 0xff;
    all_data[5] = ascii_table[dig3] & 0xff;
    all_data[6] = (ascii_table[dig3] >> 8) & 0xff;
    all_data[7] = ascii_table[dig4] & 0xff;
    all_data[8] = (ascii_table[dig4] >> 8) & 0xff;
    return i2c_master_transmit(device_handle,
        all_data, sizeof(all_data), I2C_TICKS_TO_WAIT);
}

esp_err_t AlphaNumeric::display(uint8_t thou, uint8_t hund, uint8_t tens,
                                uint8_t ones) {
    uint8_t all_data[9];
    all_data[0] = 0;
    ones &= 0x7F;
    tens &= 0x7F;
    hund &= 0x7F;
    thou &= 0x7F;

    if (thou < 0x10) {
        all_data[1] = ascii_table[thou + ascii_table_numeric_start] & 0xff;
        all_data[2] = (ascii_table[thou + ascii_table_numeric_start] >> 8) & 0xff;
    }
    else if (thou >= space_offset) {
        all_data[1] = ascii_table[thou - space_offset] & 0xff;
        all_data[2] = (ascii_table[thou - space_offset] >> 8) & 0xff;
    }

    if (hund < 0x10) {
        all_data[3] = ascii_table[hund + ascii_table_numeric_start] & 0xff;
        all_data[4] = (ascii_table[hund + ascii_table_numeric_start] >> 8) & 0xff;
    }
    else if (hund >= space_offset) {
        all_data[3] = ascii_table[hund - space_offset] & 0xff;
        all_data[4] = (ascii_table[hund - space_offset] >> 8) & 0xff;
    }

    if (tens < 0x10) {
        all_data[5] = ascii_table[tens + ascii_table_numeric_start] & 0xff;
        all_data[6] = (ascii_table[tens + ascii_table_numeric_start] >> 8) & 0xff;
    }
    else if (tens >= space_offset) {
        all_data[5] = ascii_table[tens - space_offset] & 0xff;
        all_data[6] = (ascii_table[tens - space_offset] >> 8) & 0xff;
    }

    if (ones < 0x10) {
        all_data[7] = ascii_table[ones + ascii_table_numeric_start] & 0xff;
        all_data[8] = (ascii_table[ones + ascii_table_numeric_start] >> 8) & 0xff;
    }
    else if (ones >= space_offset) {
        all_data[7] = ascii_table[ones - space_offset] & 0xff;
        all_data[8] = (ascii_table[ones - space_offset] >> 8) & 0xff;
    }

    return i2c_master_transmit(device_handle,
        all_data, sizeof(all_data), I2C_TICKS_TO_WAIT);
}
