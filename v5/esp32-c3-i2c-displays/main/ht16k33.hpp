#pragma once

#include "i2c_support.hpp"

/* These are HT16K33 commands.
   
   A number of these are bit flags.
   A complex command is created by ORing several of these together.
 */
const uint8_t HT16K33_SYSTEM_SETUP = 0x20;
const uint8_t HT16K33_OSCILLATOR_ON = 0x01;
const uint8_t HT16K33_DISPLAY_SETUP = 0x80;
const uint8_t HT16K33_DISPLAY_ON = 0x01;
const uint8_t HT16K33_BLINK_OFF = 0x00;
const uint8_t HT16K33_BLINK_2HZ = 0x02;
const uint8_t HT16K33_BLINK_1HZ = 0x04;
const uint8_t HT16K33_BLINK_HALFHZ = 0x06;
const uint8_t HT16K33_CMD_BRIGHTNESS = 0xE0;
const uint8_t initialize_command_sequence[] = {
      (HT16K33_SYSTEM_SETUP | HT16K33_OSCILLATOR_ON),
      (HT16K33_DISPLAY_SETUP | HT16K33_DISPLAY_ON),
      (HT16K33_CMD_BRIGHTNESS | 0x0f)
};

/* Initialize the HT16K33 device and prepare it for displaying data on LED digits.
   Called AFTER I2C initizliation, before any other functions for the HT16K33.
   It only needs to be called once.
 */
esp_err_t ht16k33_initialize(uint8_t device_address);
