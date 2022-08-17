/* HT16K33 Support Code for ESP-IDF.

   This code is licensed under Apache Apache Version 2.0, January 2004

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
 */
#pragma once

#include "i2c_support.hpp"

/*
   These are HT16K33 commands that need to be sent to a device in order to
   initialize it for use.
   
   Some of these are bit flags, and a complex command is created by ORing
   some several of these together.
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

/*
   This initializes the HT16K33 device and prepares it for displaying data on
   the LED digits.
   
   THIS MUST ALWAYS BE CALLED AFTER THE I2C BUSS IS INITIALIZED.
   THIS MUST ALWAYS BE CALLED BEFORE ANY OTHER PUBLIC FUNCTIONS LISTED BELOW.
   THIS ONLY NEEDS TO BE CALLED ONCE.
 */
esp_err_t ht16k33_initialize(uint8_t device_address);
