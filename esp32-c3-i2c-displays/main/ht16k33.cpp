/* HT16K33 Support Code for ESP-IDF.

   This code is licensed under Apache Apache Version 2.0, January 2004

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
 */
#include "ht16k33.hpp"

esp_err_t ht16k33_initialize(uint8_t device_address) {
    static esp_err_t ret;
    uint8_t init_data[] = {
        (HT16K33_SYSTEM_SETUP | HT16K33_OSCILLATOR_ON),
        (HT16K33_DISPLAY_SETUP | HT16K33_DISPLAY_ON),
        (HT16K33_CMD_BRIGHTNESS | 0x0f)
    };
    for (auto cmd : init_data) {
        ret = write_byte(device_address, cmd);
    }
    return ret;
}
