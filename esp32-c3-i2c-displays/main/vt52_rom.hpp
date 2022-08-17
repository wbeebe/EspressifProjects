/* VT-52 Character Display Support Code for ESP-IDF.

   This was copied from code originally written in Go for the Raspberry Pi 3
   and 4.

   This code is licensed under Apache Apache Version 2.0, January 2004

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
 */
#pragma once

#include <stdint.h>

const uint8_t vt52_rom_numeric_start = 0x30;
const uint8_t vt52_rom_alpha_start = vt52_rom_numeric_start + 6;

const uint8_t *get_vt52_character(uint8_t character);