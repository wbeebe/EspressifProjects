#pragma once

#include <stdint.h>

const static uint8_t VT52rom[][8] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0
    0x00, 0x30, 0x40, 0x41, 0x31, 0x07, 0x09, 0x07, // 1
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, // 2
    0x00, 0x21, 0x61, 0x22, 0x22, 0x74, 0x04, 0x08, // 3
    0x00, 0x71, 0x09, 0x32, 0x0a, 0x74, 0x04, 0x08, // 4
    0x00, 0x79, 0x41, 0x72, 0x0a, 0x74, 0x04, 0x08, // 5
    0x00, 0x79, 0x09, 0x12, 0x22, 0x44, 0x04, 0x08, // 6
    0x00, 0x18, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00, // 7
    0x00, 0x00, 0x08, 0x08, 0x7f, 0x08, 0x08, 0x7f, // 8
    0x00, 0x00, 0x04, 0x02, 0x7f, 0x02, 0x04, 0x00, // 9
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, // 10
    0x00, 0x00, 0x08, 0x00, 0x7f, 0x00, 0x08, 0x00, // 11
    0x00, 0x08, 0x08, 0x49, 0x2a, 0x1c, 0x08, 0x00, // 12
    0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 13
    0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 14
    0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, // 15
    0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, // 16
    0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, // 17
    0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, // 18
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, // 19
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, // 20
    0x00, 0x00, 0x00, 0x30, 0x48, 0x48, 0x48, 0x30, // 21
    0x00, 0x00, 0x00, 0x20, 0x60, 0x20, 0x20, 0x70, // 22
    0x00, 0x00, 0x00, 0x70, 0x08, 0x30, 0x40, 0x78, // 23
    0x00, 0x00, 0x00, 0x70, 0x08, 0x30, 0x08, 0x70, // 24
    0x00, 0x00, 0x00, 0x10, 0x30, 0x50, 0x78, 0x10, // 25
    0x00, 0x00, 0x00, 0x78, 0x40, 0x70, 0x08, 0x70, // 26
    0x00, 0x00, 0x00, 0x38, 0x40, 0x70, 0x48, 0x30, // 27
    0x00, 0x00, 0x00, 0x78, 0x08, 0x10, 0x20, 0x40, // 28
    0x00, 0x00, 0x00, 0x30, 0x48, 0x30, 0x48, 0x30, // 29
    0x00, 0x00, 0x00, 0x30, 0x48, 0x38, 0x08, 0x70, // 30
    0x00, 0x3f, 0x7a, 0x7a, 0x3a, 0x0a, 0x0a, 0x0a, // 31
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 32 ' '
    0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x08, // 33 '!'
    0x00, 0x14, 0x14, 0x14, 0x00, 0x00, 0x00, 0x00, // 34 '"'
    0x00, 0x14, 0x14, 0x7f, 0x14, 0x7f, 0x14, 0x14, // 35 '#'
    0x00, 0x08, 0x3e, 0x48, 0x3e, 0x09, 0x3e, 0x08, // 36 '$'
    0x00, 0x61, 0x62, 0x04, 0x08, 0x10, 0x23, 0x43, // 37 '%'
    0x00, 0x1c, 0x22, 0x14, 0x08, 0x15, 0x22, 0x1d, // 38 '&'
    0x00, 0x0c, 0x08, 0x10, 0x00, 0x00, 0x00, 0x00, // 39 '''
    0x00, 0x04, 0x08, 0x10, 0x10, 0x10, 0x08, 0x04, // 40 '('
    0x00, 0x10, 0x08, 0x04, 0x04, 0x04, 0x08, 0x10, // 41 ')'
    0x00, 0x08, 0x49, 0x2a, 0x1c, 0x2a, 0x49, 0x08, // 42 '*'
    0x00, 0x00, 0x08, 0x08, 0x7f, 0x08, 0x08, 0x00, // 43 '+'
    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x10, 0x20, // 44 ','
    0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, // 45 '-'
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, // 46 '.'
    0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, // 47 '/'
    0x00, 0x1c, 0x22, 0x45, 0x49, 0x51, 0x22, 0x1c, // 48 '0'
    0x00, 0x08, 0x18, 0x28, 0x08, 0x08, 0x08, 0x3e, // 49 '1'
    0x00, 0x3c, 0x42, 0x01, 0x0e, 0x30, 0x40, 0x7f, // 50 '2'
    0x00, 0x7f, 0x02, 0x04, 0x0e, 0x01, 0x41, 0x3e, // 51 '3'
    0x00, 0x04, 0x0c, 0x14, 0x24, 0x7f, 0x04, 0x04, // 52 '4'
    0x00, 0x7f, 0x40, 0x5e, 0x61, 0x01, 0x41, 0x3e, // 53 '5'
    0x00, 0x1e, 0x21, 0x40, 0x5e, 0x61, 0x21, 0x1e, // 54 '6'
    0x00, 0x7f, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, // 55 '7'
    0x00, 0x3e, 0x41, 0x41, 0x3e, 0x41, 0x41, 0x3e, // 56 '8'
    0x00, 0x3c, 0x42, 0x43, 0x3d, 0x01, 0x42, 0x3c, // 57 '9'
    0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, // 58 ':'
    0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x10, 0x20, // 59 ';'
    0x00, 0x02, 0x04, 0x08, 0x10, 0x08, 0x04, 0x02, // 60 '<'
    0x00, 0x00, 0x00, 0x7f, 0x00, 0x7f, 0x00, 0x00, // 61 '='
    0x00, 0x20, 0x10, 0x08, 0x04, 0x08, 0x10, 0x20, // 62 '>'
    0x00, 0x3e, 0x41, 0x01, 0x0e, 0x08, 0x00, 0x08, // 63 '?'
    0x00, 0x3e, 0x41, 0x45, 0x49, 0x4e, 0x40, 0x3e, // 64 '@'
    0x00, 0x08, 0x14, 0x22, 0x41, 0x7f, 0x41, 0x41, // 65 'A'
    0x00, 0x7e, 0x21, 0x21, 0x3e, 0x21, 0x21, 0x7e, // 66 'B'
    0x00, 0x1e, 0x21, 0x40, 0x40, 0x40, 0x21, 0x1e, // 67 'C'
    0x00, 0x7e, 0x21, 0x21, 0x21, 0x21, 0x21, 0x7e, // 68 'D'
    0x00, 0x7f, 0x40, 0x40, 0x78, 0x40, 0x40, 0x7f, // 69 'E'
    0x00, 0x7f, 0x40, 0x40, 0x78, 0x40, 0x40, 0x40, // 70 'F'
    0x00, 0x3e, 0x41, 0x40, 0x47, 0x41, 0x41, 0x3e, // 71 'G'
    0x00, 0x41, 0x41, 0x41, 0x7f, 0x41, 0x41, 0x41, // 72 'H'
    0x00, 0x3e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x3e, // 73 'I'
    0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x41, 0x3e, // 74 'J'
    0x00, 0x41, 0x46, 0x58, 0x60, 0x58, 0x46, 0x41, // 75 'K'
    0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7f, // 76 'L'
    0x00, 0x41, 0x63, 0x55, 0x49, 0x41, 0x41, 0x41, // 77 'M'
    0x00, 0x41, 0x61, 0x51, 0x49, 0x45, 0x43, 0x41, // 78 'N'
    0x00, 0x3e, 0x41, 0x41, 0x41, 0x41, 0x41, 0x3e, // 79 'O'
    0x00, 0x7e, 0x41, 0x41, 0x7e, 0x40, 0x40, 0x40, // 80 'P'
    0x00, 0x3e, 0x41, 0x41, 0x41, 0x45, 0x42, 0x3d, // 81 'Q'
    0x00, 0x7e, 0x41, 0x41, 0x7e, 0x44, 0x42, 0x41, // 82 'R'
    0x00, 0x3e, 0x41, 0x40, 0x3e, 0x01, 0x41, 0x3e, // 83 'S'
    0x00, 0x7f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, // 84 'T'
    0x00, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x3e, // 85 'U'
    0x00, 0x41, 0x41, 0x22, 0x22, 0x14, 0x14, 0x08, // 86 'V'
    0x00, 0x41, 0x41, 0x41, 0x49, 0x49, 0x55, 0x22, // 87 'W'
    0x00, 0x41, 0x22, 0x14, 0x08, 0x14, 0x22, 0x41, // 88 'X'
    0x00, 0x41, 0x22, 0x14, 0x08, 0x08, 0x08, 0x08, // 89 'Y'
    0x00, 0x7f, 0x02, 0x04, 0x08, 0x10, 0x20, 0x7f, // 90 'Z'
    0x00, 0x3c, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3c, // 91 '['
    0x00, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, // 92 '\'
    0x00, 0x1e, 0x06, 0x06, 0x06, 0x06, 0x06, 0x1e, // 93 ']'
    0x00, 0x08, 0x14, 0x22, 0x00, 0x00, 0x00, 0x00, // 94 '^'
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, // 95 '_'
    0x00, 0x18, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, // 96 '`'
    0x00, 0x00, 0x00, 0x3e, 0x01, 0x3f, 0x41, 0x3f, // 97 'a'
    0x00, 0x40, 0x40, 0x5e, 0x61, 0x41, 0x61, 0x5e, // 98 'b'
    0x00, 0x00, 0x00, 0x3e, 0x41, 0x40, 0x40, 0x3f, // 99 'c'
    0x00, 0x01, 0x01, 0x3d, 0x43, 0x41, 0x43, 0x3d, // 100 'd'
    0x00, 0x00, 0x00, 0x3c, 0x42, 0x7f, 0x40, 0x3e, // 101 'e'
    0x00, 0x0e, 0x11, 0x7c, 0x10, 0x10, 0x10, 0x10, // 102 'f'
    0x00, 0x00, 0x00, 0x1d, 0x22, 0x1e, 0x42, 0x3c, // 103 'g'
    0x00, 0x40, 0x40, 0x7e, 0x41, 0x41, 0x41, 0x41, // 104 'h'
    0x00, 0x08, 0x00, 0x18, 0x08, 0x08, 0x08, 0x3e, // 105 'i'
    0x00, 0x01, 0x00, 0x01, 0x01, 0x01, 0x41, 0x3e, // 106 'j'
    0x00, 0x40, 0x40, 0x44, 0x48, 0x50, 0x44, 0x41, // 107 'k'
    0x00, 0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0x1c, // 108 'l'
    0x00, 0x00, 0x00, 0x76, 0x49, 0x49, 0x49, 0x49, // 109 'm'
    0x00, 0x00, 0x00, 0x5e, 0x61, 0x41, 0x41, 0x41, // 110 'n'
    0x00, 0x00, 0x00, 0x3e, 0x41, 0x41, 0x41, 0x3e, // 111 'o'
    0x00, 0x00, 0x00, 0x5e, 0x61, 0x7e, 0x40, 0x40, // 112 'p'
    0x00, 0x00, 0x00, 0x3d, 0x43, 0x3f, 0x01, 0x01, // 113 'q'
    0x00, 0x00, 0x00, 0x4e, 0x31, 0x20, 0x20, 0x20, // 114 'r'
    0x00, 0x00, 0x00, 0x3e, 0x40, 0x3e, 0x01, 0x7e, // 115 's'
    0x00, 0x10, 0x10, 0x7c, 0x10, 0x10, 0x12, 0x0c, // 116 't'
    0x00, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x3d, // 117 'u'
    0x00, 0x00, 0x00, 0x41, 0x41, 0x22, 0x14, 0x08, // 118 'v'
    0x00, 0x00, 0x00, 0x41, 0x41, 0x49, 0x55, 0x22, // 119 'w'
    0x00, 0x00, 0x00, 0x42, 0x24, 0x18, 0x24, 0x42, // 120 'x'
    0x00, 0x00, 0x00, 0x41, 0x22, 0x14, 0x08, 0x70, // 121 'y'
    0x00, 0x00, 0x00, 0x7f, 0x02, 0x1c, 0x20, 0x7f, // 122 'z'
    0x00, 0x07, 0x08, 0x08, 0x70, 0x08, 0x08, 0x07, // 123 '{'
    0x00, 0x08, 0x08, 0x08, 0x00, 0x08, 0x08, 0x08, // 124 '|'
    0x00, 0x70, 0x08, 0x08, 0x07, 0x08, 0x08, 0x70, // 125 '}'
    0x00, 0x11, 0x2a, 0x44, 0x00, 0x00, 0x00, 0x00, // 126 '~'
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // 127
};

const uint8_t vt52_rom_numeric_start = 0x30;
const uint8_t vt52_rom_alpha_start = vt52_rom_numeric_start + 6;

const uint8_t *get_vt52_character(uint8_t character) {
    return VT52rom[character & 0x7F];
}
