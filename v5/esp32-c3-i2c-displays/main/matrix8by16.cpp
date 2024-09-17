#include <cstring>
#include "freertos/FreeRTOS.h"
#include "matrix8by16.hpp"
#include "vt52_rom.hpp"

Matrix8by16::Matrix8by16(uint8_t _device_address) {
        std::memset(buffer, 0, sizeof(buffer));
        device_address = _device_address;
}

esp_err_t Matrix8by16::initialize() {
    return ht16k33_initialize(device_address);
}

esp_err_t Matrix8by16::reset() {
    std::memset(buffer, 0, sizeof(buffer));
    return i2c_master_write_to_device(
        I2C_NUM_0, device_address, buffer, sizeof(buffer),
        (500 / portTICK_PERIOD_MS));
}

esp_err_t Matrix8by16::test() {
    std::memset(buffer, 0xFF, sizeof(buffer));
    buffer[0] = 0;
    esp_err_t ret = i2c_master_write_to_device(
        I2C_NUM_0, device_address, buffer, sizeof(buffer),
        (500 / portTICK_PERIOD_MS));
    std::memset(buffer, 0x0, sizeof(buffer));
    return ret;
}

/*  When the HT16K33 is used with a pair of 8x8 displays, the
    HT16K33 is wired in such a way that the two displays are
    interleaved (where D1 is display 1 and D2 is display 2):
    Buffer addr: 0 1  2  3  4  5  6  7  8  9  10 11 12 13 14 16
          Value: 0 D1 D2 D1 D2 D1 D2 D1 D2 D2 D1 D2 D1 D2 D1 D2
    Buffer byte 0 is always 0. The other digit bytes are interleaved
    as shown. Finally. addressing is in columns, not rows. Thus
    each byte fills one column, from left to right. When building
    glyphs to display, this needs to be taken into consideration.
 */    
esp_err_t Matrix8by16::display(const uint8_t digit, const uint8_t glyph[]) {
    auto di = 1 + (digit & 0x01);
    buffer[0] = 0;

    for (int i = 0; i < 8; ++i) {
        buffer[di] = glyph[i];
        di += 2;
    }

    return i2c_master_write_to_device(I2C_NUM_0, device_address, buffer,
                                      sizeof(buffer), I2C_TICKS_TO_WAIT);
}

esp_err_t Matrix8by16::display(const int8_t tens, const int8_t ones) {
    auto digt = get_vt52_character(tens + vt52_rom_numeric_start);
    auto digo = get_vt52_character(ones + vt52_rom_numeric_start);
    buffer[0] = 0;
    int di1 = 1, di2 = 2;

    for (int i=0; i < 8; ++i) {
        buffer[di1] = digt[i];
        buffer[di2] = digo[i];
        di1 += 2;
        di2 += 2;
    }

    return i2c_master_write_to_device(
        I2C_NUM_0, device_address, buffer, sizeof(buffer), I2C_TICKS_TO_WAIT);
}

void Matrix8by16::show_all_8x16_glyphs() {
    display(0,Circle);
    display(1,Square);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    display(0,Diamond);
    display(1,Check);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    display(0,Cross);
    display(1,Face);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    display(0,Frown);
    display(1,Smile);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    display(0,ForwardSlash);
    display(1,BackSlash);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    display(0,BackSlash);
    display(1,ForwardSlash);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}