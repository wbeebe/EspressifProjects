/* VT-52 Character Display Support Code for ESP-IDF.

   This was copied from code originally written in Go for the Raspberry Pi 3
   and 4.

   This code is licensed under Apache Version 2.0, January 2004

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
 */
#include "vt52_rom.hpp"

// This is a translation from a row-based VT52 ROM dump to
// the Adafruit 8x16 LED Matrix display's column-based format.
// The VT52 ROM was found here: https://github.com/fritzm/vt52
// The VT52 ROM, originally pushed as a C header file, was
// edited into Go's structure format, then pasted into a utility
// in the tool section (vt52convert.go) where it converted from
// the original format to this format.
//
// Now I've taken my Go-based version and converted it back to
// C++, but preserving the same column-based format.
//
const static uint8_t VT52rom[][8] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, }, // 0x00
    { 0x00, 0x30, 0x48, 0x48, 0x02, 0x05, 0x05, 0x1f, }, // 0x01
    { 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, }, // 0x02
    { 0x00, 0x24, 0x7c, 0x04, 0x01, 0x06, 0x18, 0x60, }, // 0x03
    { 0x00, 0x44, 0x54, 0x54, 0x29, 0x06, 0x18, 0x60, }, // 0x04
    { 0x00, 0x74, 0x54, 0x54, 0x49, 0x06, 0x18, 0x60, }, // 0x05
    { 0x00, 0x44, 0x48, 0x50, 0x61, 0x06, 0x18, 0x60, }, // 0x06
    { 0x00, 0x00, 0x20, 0x50, 0x50, 0x20, 0x00, 0x00, }, // 0x07
    { 0x00, 0x09, 0x09, 0x09, 0x3f, 0x09, 0x09, 0x09, }, // 0x08
    { 0x00, 0x08, 0x08, 0x08, 0x08, 0x2a, 0x1c, 0x08, }, // 0x09
    { 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, }, // 0x0a
    { 0x00, 0x08, 0x08, 0x08, 0x2a, 0x08, 0x08, 0x08, }, // 0x0b
    { 0x00, 0x10, 0x08, 0x04, 0x7e, 0x04, 0x08, 0x10, }, // 0x0c
    { 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, }, // 0x0d
    { 0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, }, // 0x0e
    { 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, }, // 0x0f
    { 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, }, // 0x10
    { 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, }, // 0x11
    { 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, }, // 0x12
    { 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, }, // 0x13
    { 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, }, // 0x14
    { 0x00, 0x0e, 0x11, 0x11, 0x0e, 0x00, 0x00, 0x00, }, // 0x15
    { 0x00, 0x09, 0x1f, 0x01, 0x00, 0x00, 0x00, 0x00, }, // 0x16
    { 0x00, 0x13, 0x15, 0x15, 0x09, 0x00, 0x00, 0x00, }, // 0x17
    { 0x00, 0x11, 0x15, 0x15, 0x0a, 0x00, 0x00, 0x00, }, // 0x18
    { 0x00, 0x06, 0x0a, 0x1f, 0x02, 0x00, 0x00, 0x00, }, // 0x19
    { 0x00, 0x1d, 0x15, 0x15, 0x12, 0x00, 0x00, 0x00, }, // 0x1a
    { 0x00, 0x0e, 0x15, 0x15, 0x12, 0x00, 0x00, 0x00, }, // 0x1b
    { 0x00, 0x11, 0x12, 0x14, 0x18, 0x00, 0x00, 0x00, }, // 0x1c
    { 0x00, 0x0a, 0x15, 0x15, 0x0a, 0x00, 0x00, 0x00, }, // 0x1d
    { 0x00, 0x09, 0x15, 0x15, 0x0e, 0x00, 0x00, 0x00, }, // 0x1e
    { 0x00, 0x30, 0x78, 0x78, 0x7f, 0x40, 0x7f, 0x40, }, // 0x1f
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, }, // 0x20
    { 0x00, 0x00, 0x00, 0x00, 0x7d, 0x00, 0x00, 0x00, }, // 0x21
    { 0x00, 0x00, 0x00, 0x70, 0x00, 0x70, 0x00, 0x00, }, // 0x22
    { 0x00, 0x14, 0x14, 0x7f, 0x14, 0x7f, 0x14, 0x14, }, // 0x23
    { 0x00, 0x10, 0x2a, 0x2a, 0x7f, 0x2a, 0x2a, 0x04, }, // 0x24
    { 0x00, 0x61, 0x62, 0x04, 0x08, 0x10, 0x23, 0x43, }, // 0x25
    { 0x00, 0x00, 0x22, 0x55, 0x49, 0x55, 0x22, 0x05, }, // 0x26
    { 0x00, 0x00, 0x00, 0x10, 0x60, 0x40, 0x00, 0x00, }, // 0x27
    { 0x00, 0x00, 0x00, 0x1c, 0x22, 0x41, 0x00, 0x00, }, // 0x28
    { 0x00, 0x00, 0x00, 0x41, 0x22, 0x1c, 0x00, 0x00, }, // 0x29
    { 0x00, 0x22, 0x14, 0x08, 0x7f, 0x08, 0x14, 0x22, }, // 0x2a
    { 0x00, 0x08, 0x08, 0x08, 0x3e, 0x08, 0x08, 0x08, }, // 0x2b
    { 0x00, 0x00, 0x01, 0x06, 0x04, 0x00, 0x00, 0x00, }, // 0x2c
    { 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, }, // 0x2d
    { 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, }, // 0x2e
    { 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, }, // 0x2f
    { 0x00, 0x1c, 0x22, 0x45, 0x49, 0x51, 0x22, 0x1c, }, // 0x30
    { 0x00, 0x00, 0x11, 0x21, 0x7f, 0x01, 0x01, 0x00, }, // 0x31
    { 0x00, 0x23, 0x45, 0x45, 0x49, 0x49, 0x29, 0x11, }, // 0x32
    { 0x00, 0x42, 0x41, 0x41, 0x49, 0x59, 0x69, 0x46, }, // 0x33
    { 0x00, 0x04, 0x0c, 0x14, 0x24, 0x7f, 0x04, 0x04, }, // 0x34
    { 0x00, 0x7a, 0x49, 0x51, 0x51, 0x51, 0x51, 0x4e, }, // 0x35
    { 0x00, 0x1c, 0x26, 0x49, 0x49, 0x49, 0x49, 0x26, }, // 0x36
    { 0x00, 0x40, 0x41, 0x42, 0x44, 0x48, 0x50, 0x60, }, // 0x37
    { 0x00, 0x36, 0x49, 0x49, 0x49, 0x49, 0x49, 0x36, }, // 0x38
    { 0x00, 0x32, 0x49, 0x49, 0x49, 0x49, 0x32, 0x1c, }, // 0x39
    { 0x00, 0x00, 0x00, 0x33, 0x33, 0x00, 0x00, 0x00, }, // 0x3a
    { 0x00, 0x00, 0x01, 0x36, 0x34, 0x00, 0x00, 0x00, }, // 0x3b
    { 0x00, 0x00, 0x00, 0x08, 0x14, 0x22, 0x41, 0x00, }, // 0x3c
    { 0x00, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, }, // 0x3d
    { 0x00, 0x00, 0x41, 0x22, 0x14, 0x08, 0x00, 0x00, }, // 0x3e
    { 0x00, 0x20, 0x40, 0x40, 0x4d, 0x48, 0x48, 0x30, }, // 0x3f
    { 0x00, 0x3e, 0x41, 0x41, 0x4d, 0x55, 0x45, 0x38, }, // 0x40
    { 0x00, 0x0f, 0x14, 0x24, 0x44, 0x24, 0x14, 0x0f, }, // 0x41
    { 0x00, 0x41, 0x7f, 0x49, 0x49, 0x49, 0x49, 0x36, }, // 0x42
    { 0x00, 0x1c, 0x22, 0x41, 0x41, 0x41, 0x41, 0x22, }, // 0x43
    { 0x00, 0x41, 0x7f, 0x41, 0x41, 0x41, 0x41, 0x3e, }, // 0x44
    { 0x00, 0x7f, 0x49, 0x49, 0x49, 0x41, 0x41, 0x41, }, // 0x45
    { 0x00, 0x7f, 0x48, 0x48, 0x48, 0x40, 0x40, 0x40, }, // 0x46
    { 0x00, 0x3e, 0x41, 0x41, 0x41, 0x49, 0x49, 0x2e, }, // 0x47
    { 0x00, 0x7f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x7f, }, // 0x48
    { 0x00, 0x00, 0x41, 0x41, 0x7f, 0x41, 0x41, 0x00, }, // 0x49
    { 0x00, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x7e, }, // 0x4a
    { 0x00, 0x7f, 0x08, 0x14, 0x14, 0x22, 0x22, 0x41, }, // 0x4b
    { 0x00, 0x7f, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, }, // 0x4c
    { 0x00, 0x7f, 0x20, 0x10, 0x08, 0x10, 0x20, 0x7f, }, // 0x4d
    { 0x00, 0x7f, 0x20, 0x10, 0x08, 0x04, 0x02, 0x7f, }, // 0x4e
    { 0x00, 0x3e, 0x41, 0x41, 0x41, 0x41, 0x41, 0x3e, }, // 0x4f
    { 0x00, 0x7f, 0x48, 0x48, 0x48, 0x48, 0x48, 0x30, }, // 0x50
    { 0x00, 0x3e, 0x41, 0x41, 0x41, 0x45, 0x42, 0x3d, }, // 0x51
    { 0x00, 0x7f, 0x48, 0x48, 0x48, 0x4c, 0x4a, 0x31, }, // 0x52
    { 0x00, 0x32, 0x49, 0x49, 0x49, 0x49, 0x49, 0x26, }, // 0x53
    { 0x00, 0x40, 0x40, 0x40, 0x7f, 0x40, 0x40, 0x40, }, // 0x54
    { 0x00, 0x7e, 0x01, 0x01, 0x01, 0x01, 0x01, 0x7e, }, // 0x55
    { 0x00, 0x60, 0x18, 0x06, 0x01, 0x06, 0x18, 0x60, }, // 0x56
    { 0x00, 0x7e, 0x01, 0x02, 0x0c, 0x02, 0x01, 0x7e, }, // 0x57
    { 0x00, 0x41, 0x22, 0x14, 0x08, 0x14, 0x22, 0x41, }, // 0x58
    { 0x00, 0x40, 0x20, 0x10, 0x0f, 0x10, 0x20, 0x40, }, // 0x59
    { 0x00, 0x41, 0x43, 0x45, 0x49, 0x51, 0x61, 0x41, }, // 0x5a
    { 0x00, 0x00, 0x7f, 0x7f, 0x41, 0x41, 0x00, 0x00, }, // 0x5b
    { 0x00, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, }, // 0x5c
    { 0x00, 0x00, 0x00, 0x41, 0x41, 0x7f, 0x7f, 0x00, }, // 0x5d
    { 0x00, 0x00, 0x10, 0x20, 0x40, 0x20, 0x10, 0x00, }, // 0x5e
    { 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, }, // 0x5f
    { 0x00, 0x00, 0x00, 0x40, 0x60, 0x10, 0x00, 0x00, }, // 0x60
    { 0x00, 0x02, 0x15, 0x15, 0x15, 0x15, 0x15, 0x0f, }, // 0x61
    { 0x00, 0x7f, 0x0a, 0x11, 0x11, 0x11, 0x11, 0x0e, }, // 0x62
    { 0x00, 0x0e, 0x11, 0x11, 0x11, 0x11, 0x11, 0x09, }, // 0x63
    { 0x00, 0x0e, 0x11, 0x11, 0x11, 0x11, 0x0a, 0x7f, }, // 0x64
    { 0x00, 0x0e, 0x15, 0x15, 0x15, 0x15, 0x0d, 0x04, }, // 0x65
    { 0x00, 0x10, 0x10, 0x3f, 0x50, 0x50, 0x40, 0x20, }, // 0x66
    { 0x00, 0x02, 0x09, 0x15, 0x15, 0x15, 0x0e, 0x10, }, // 0x67
    { 0x00, 0x7f, 0x10, 0x10, 0x10, 0x10, 0x10, 0x0f, }, // 0x68
    { 0x00, 0x00, 0x01, 0x11, 0x5f, 0x01, 0x01, 0x00, }, // 0x69
    { 0x00, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x5e, }, // 0x6a
    { 0x00, 0x7f, 0x00, 0x04, 0x08, 0x12, 0x00, 0x01, }, // 0x6b
    { 0x00, 0x00, 0x00, 0x41, 0x7f, 0x01, 0x00, 0x00, }, // 0x6c
    { 0x00, 0x1f, 0x10, 0x10, 0x0f, 0x10, 0x10, 0x0f, }, // 0x6d
    { 0x00, 0x1f, 0x08, 0x10, 0x10, 0x10, 0x10, 0x0f, }, // 0x6e
    { 0x00, 0x0e, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0e, }, // 0x6f
    { 0x00, 0x1f, 0x0c, 0x14, 0x14, 0x14, 0x14, 0x08, }, // 0x70
    { 0x00, 0x08, 0x14, 0x14, 0x14, 0x14, 0x0c, 0x1f, }, // 0x71
    { 0x00, 0x10, 0x0f, 0x08, 0x10, 0x10, 0x10, 0x08, }, // 0x72
    { 0x00, 0x09, 0x15, 0x15, 0x15, 0x15, 0x15, 0x02, }, // 0x73
    { 0x00, 0x10, 0x10, 0x7e, 0x11, 0x11, 0x02, 0x00, }, // 0x74
    { 0x00, 0x1e, 0x01, 0x01, 0x01, 0x01, 0x1e, 0x01, }, // 0x75
    { 0x00, 0x18, 0x04, 0x02, 0x01, 0x02, 0x04, 0x18, }, // 0x76
    { 0x00, 0x1e, 0x01, 0x02, 0x04, 0x02, 0x01, 0x1e, }, // 0x77
    { 0x00, 0x11, 0x0a, 0x04, 0x04, 0x0a, 0x11, 0x00, }, // 0x78
    { 0x00, 0x11, 0x09, 0x05, 0x02, 0x04, 0x08, 0x10, }, // 0x79
    { 0x00, 0x11, 0x13, 0x15, 0x15, 0x15, 0x19, 0x11, }, // 0x7a
    { 0x00, 0x08, 0x08, 0x08, 0x36, 0x41, 0x41, 0x41, }, // 0x7b
    { 0x00, 0x00, 0x00, 0x00, 0x77, 0x00, 0x00, 0x00, }, // 0x7c
    { 0x00, 0x41, 0x41, 0x41, 0x36, 0x08, 0x08, 0x08, }, // 0x7d
    { 0x00, 0x10, 0x20, 0x40, 0x20, 0x10, 0x20, 0x40, }, // 0x7e
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, }, // 0x7f
};

const uint8_t *get_vt52_character(uint8_t character) {
    return VT52rom[character & 0x7F];
}
