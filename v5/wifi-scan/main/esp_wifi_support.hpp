/* ESP WiFi Support Code for ESP-IDF.

   This code is licensed under Apache Version 2.0, January 2004

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
 */
#pragma once

#include "esp_wifi.h"

#define stringify( _name ) #_name

const char* decode_wifi_auth_mode( wifi_auth_mode_t amode);

const char* decode_wifi_cipher_type( wifi_cipher_type_t ctype);