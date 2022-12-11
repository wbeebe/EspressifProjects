#pragma once
#include "ht16k33.hpp"

class AlphaNumeric : Device {
    uint8_t device_address;

    public:
        AlphaNumeric(uint8_t _device_address);

        esp_err_t initialize();

        /* This clears an entire HT16K33 driven four digit alpha-numeric display by
           turning off all segments on all digits.
   
           Call this AFTER initialize() in order to turn off all
           digit segments, otherwise they will all be on.
         */
        esp_err_t reset();

        /* This tests the display by turning on every segment in every digit.

           Call this AFTER initialize()
         */
        esp_err_t test();

        /* This displays a 16-bit number on the four digits. Handles full hexadecimal
           range from 0-9 and A-F.
         */
        esp_err_t display(uint16_t number_to_display);

        /* This displays a decimal number on the four digits. Handles range from 0000
           to 9999. Each value for each digit is a single uint8. The function is
           called with the most significant to the least significant as the arguments.
         */
        esp_err_t display(uint8_t thou, uint8_t hund, uint8_t tens, uint8_t ones);
};
