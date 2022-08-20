/* Adafruit 0.8" 8x16 LED Matrix FeatherWing Display Support Code for ESP-IDF.
   Part: https://www.adafruit.com/product/3152

   This was copied from code originally written in Go for the Raspberry Pi 3
   and 4.

   This code is licensed under Apache Version 2.0, January 2004

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
 */
#pragma once
#include "ht16k33.hpp"

/* Sample display glyphs
 */
const uint8_t Circle[8] {0x3c, 0x42, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3c};
const uint8_t Square[8] {0xFF, 0xFF, 0xC3, 0xC3, 0xC3, 0xC3, 0xFF, 0xFF};
const uint8_t Diamond[8] {0x18, 0x3C, 0x7E, 0xFF, 0xFF, 0x7E, 0x3C, 0x18};
const uint8_t Check[8] {0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55};
const uint8_t Cross[8] {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81};
const uint8_t Face[8] {0x3C, 0x42, 0xA9, 0x89, 0x89, 0xA9, 0x42, 0x3C};
const uint8_t Frown[8] {0x3C, 0x42, 0xA5, 0x89, 0x89, 0xA5, 0x42, 0x3C};
const uint8_t Smile[8] {0x3C, 0x42, 0xA9, 0x85, 0x85, 0xA9, 0x42, 0x3C};
const uint8_t ForwardSlash[8] {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
const uint8_t BackSlash[8] {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

enum Glyphs {
    CIRCLE,
    SQUARE,
    DIAMOND,
    CHECK,
    X,
    FACE,
    FROWN,
    SMILE,
    FORWARD_SLASH,
    BACK_SLASH,
};

class Matrix8by16 : Device {
    uint8_t device_address;
    uint8_t buffer[17];

    public:
        Matrix8by16(uint8_t _device_address);

        esp_err_t initialize();

        esp_err_t reset();

        esp_err_t test();

        esp_err_t display(const uint8_t digit, const uint8_t glyph[]);

        esp_err_t display(const uint8_t digit, const char character);

        esp_err_t display(const uint8_t tens, const uint8_t ones);
};