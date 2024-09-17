#include "alphanumeric.hpp"

static const uint16_t ascii_table[] = {
    0x0000, // SPACE
    0x0006, // !
    0x0220, // "
    0x12CE, // #
    0x12ED, // $
    0x0C24, // %
    0x235D, // &
    0x0400, // '
    0x2400, // (
    0x0900, // )
    0x3FC0, // *
    0x12C0, // +
    0x0800, // ,
    0x00C0, // "-":
    0x3808, // ".":
    0x0C00, // "/":
    0x0C3F, // "0":
    0x0006, // "1":
    0x00DB, // "2":
    0x008F, // "3":
    0x00E6, // "4":
    0x2069, // "5":
    0x00FD, // "6":
    0x0007, // "7":
    0x00FF, // "8":
    0x00EF, // "9":
    0x0009, // ":":
    0x0A00, // ";":
    0x2400, // "<":
    0x00C8, // "=":
    0x0900, // ">":
    0x1083, // "?":
    0x02BB, // "@":
    0x00F7, // "A":
    0x128F, // "B":
    0x0039, // "C":
    0x120F, // "D":
    0x00F9, // "E":
    0x0071, // "F":
    0x00BD, // "G":
    0x00F6, // "H":
    0x1200, // "I":
    0x001E, // "J":
    0x2470, // "K":
    0x0038, // "L":
    0x0536, // "M":
    0x2136, // "N":
    0x003F, // "O":
    0x00F3, // "P":
    0x203F, // "Q":
    0x20F3, // "R":
    0x00ED, // "S":
    0x1201, // "T":
    0x003E, // "U":
    0x0C30, // "V":
    0x2836, // "W":
    0x2D00, // "X":
    0x1500, // "Y":
    0x0C09, // "Z":
    0x0039, // "[":
    0x2100, // "\\":
    0x000F, // "]":
    0x0C03, // "^":
    0x0008, // "_":
    0x0100, // "`":
    0x1058, // "a":
    0x2078, // "b":
    0x00D8, // "c":
    0x088E, // "d":
    0x0858, // "e":
    0x0071, // "f":
    0x048E, // "g":
    0x1070, // "h":
    0x1000, // "i":
    0x000E, // "j":
    0x3600, // "k":
    0x0030, // "l":
    0x10D4, // "m":
    0x1050, // "n":
    0x00DC, // "o":
    0x0170, // "p":
    0x0486, // "q":
    0x0050, // "r":
    0x2088, // "s":
    0x0078, // "t":
    0x001C, // "u":
    0x2004, // "v":
    0x2814, // "w":
    0x28C0, // "x":
    0x200C, // "y":
    0x0848, // "z":
    0x0949, // "{":
    0x1200, // "|":
    0x2489, // "}":
    0x0520, // "~":
    0x00E3, // "°":
};

const uint8_t ascii_table_numeric_start = 16;
const uint8_t ascii_table_alpha_start = ascii_table_numeric_start + 7;
const uint8_t space_offset = 0x20;

AlphaNumeric::AlphaNumeric(uint8_t _device_address) {
    device_address = _device_address;
}

esp_err_t AlphaNumeric::initialize() {
    return ht16k33_initialize(device_address);
}

esp_err_t AlphaNumeric::reset() {
    uint8_t all_data[] = {0,0,0,0,0,0,0,0,0};
    return i2c_master_write_to_device(I2C_NUM_0, device_address, all_data,
                                      sizeof(all_data), I2C_TICKS_TO_WAIT);
}

esp_err_t AlphaNumeric::test() {
    uint8_t all_data[] = {0,0xff,0x7f,0xFF,0x7F,0xFF,0x7F,0xFF,0x7F};
    return i2c_master_write_to_device(I2C_NUM_0, device_address, all_data,
                                      sizeof(all_data), I2C_TICKS_TO_WAIT);
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
    return i2c_master_write_to_device(I2C_NUM_0, device_address, all_data,
                                      sizeof(all_data), I2C_TICKS_TO_WAIT);
}

esp_err_t AlphaNumeric::display(uint8_t thou, uint8_t hund, uint8_t tens,
                                uint8_t ones) {
    uint8_t all_data[9];
    all_data[0] = 0;
    if (thou < 0x10) {
        all_data[1] = ascii_table[thou + ascii_table_numeric_start] & 0xff;
        all_data[2] = (ascii_table[thou + ascii_table_numeric_start] >> 8) & 0xff;
    }
    else {
        all_data[1] = ascii_table[thou - space_offset] & 0xff;
        all_data[2] = (ascii_table[thou - space_offset] >> 8) & 0xff;
    }
    if (hund < 0x10) {
        all_data[3] = ascii_table[hund + ascii_table_numeric_start] & 0xff;
        all_data[4] = (ascii_table[hund + ascii_table_numeric_start] >> 8) & 0xff;
    }
    else {
        all_data[3] = ascii_table[hund - space_offset] & 0xff;
        all_data[4] = (ascii_table[hund - space_offset] >> 8) & 0xff;
    }
    all_data[5] = ascii_table[tens + ascii_table_numeric_start] & 0xff;
    all_data[6] = (ascii_table[tens + ascii_table_numeric_start] >> 8) & 0xff;
    all_data[7] = ascii_table[ones + ascii_table_numeric_start] & 0xff;
    all_data[8] = (ascii_table[ones + ascii_table_numeric_start] >> 8) & 0xff;
    return i2c_master_write_to_device(I2C_NUM_0, device_address, all_data,
                                      sizeof(all_data), I2C_TICKS_TO_WAIT);
}
