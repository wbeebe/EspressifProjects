#pragma once
#include "ht16k33.hpp"

class AlphaNumeric : Device {
   const uint16_t ascii_table[96] = {
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

   public:
      AlphaNumeric(uint8_t _device_address);

      esp_err_t initialize();

      /* reset the display by turning OFF every segments and decimal point in every digit.
   
         Call AFTER initialize().
      */
      esp_err_t reset();

      /* test the display by turning ON every segment and decimal point in every digit.

         Call AFTER initialize().
      */
      esp_err_t test();

      /* display a 16-bit hexadecimal number in the range from 0000 to FFFF.
         Hexadecimal digits are displayed left to right, most significant digit first.

         Call AFTER initialize().
      */
      esp_err_t display(uint16_t number_to_display);

      /* display a four-digit decimal number in the range from 0000 to 9999. 
         Each value for each digit is a single uint8. The function is
         called with most significant to the least significant as the arguments.

         Call AFTER initialize().
      */
      esp_err_t display(uint8_t thou, uint8_t hund, uint8_t tens, uint8_t ones);
};
