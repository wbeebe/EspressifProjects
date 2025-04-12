#pragma once

#include <stdint.h>

const uint8_t vt52_rom_numeric_start = 0x30;
const uint8_t vt52_rom_alpha_start = vt52_rom_numeric_start + 6;

const uint8_t *get_vt52_character(uint8_t character);