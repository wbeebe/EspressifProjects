/* ESP WiFi Support Code for ESP-IDF.

   This code is licensed under Apache Version 2.0, January 2004

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
 */
#include "esp_wifi_support.hpp"

/* Tables of stringified enumerations are created to avoid the
   maintenance nightmare of using switch/case statements where
   the enumeration is repeated twice for every instance, one to
   check and then again to product/return the string.
 */

/* Create a table of wifi_auto_mode_t stringified enumerations.
 */
static const char* wifi_auth_mode_strings[] = {
    stringify(WIFI_AUTH_OPEN),
    stringify(WIFI_AUTH_OPEN),
    stringify(WIFI_AUTH_WPA_PSK),
    stringify(WIFI_AUTH_WPA2_PSK),
    stringify(WIFI_AUTH_WPA_WPA2_PSK),
    stringify(WIFI_AUTH_WPA2_ENTERPRISE),
    stringify(WIFI_AUTH_WPA3_PSK),
    stringify(WIFI_AUTH_WPA2_WPA3_PSK),
    stringify(WIFI_AUTH_WAPI_PSK),
};

const char* decode_wifi_auth_mode( wifi_auth_mode_t amode ) {
    if (amode < 0 or amode >= WIFI_AUTH_MAX) {
        return "WIFI_AUTH_ENUM_UNDEFINED";
    }

    return wifi_auth_mode_strings[amode];
}

/* Create a table of wifi_cipher_type_t stringified enumerations.
 */
static const char* wifi_cipher_type_strings[] = {
    stringify(WIFI_CIPHER_TYPE_NONE),
    stringify(WIFI_CIPHER_TYPE_WEP40),
    stringify(WIFI_CIPHER_TYPE_WEP104),
    stringify(WIFI_CIPHER_TYPE_TKIP),
    stringify(WIFI_CIPHER_TYPE_CCMP),
    stringify(WIFI_CIPHER_TYPE_TKIP_CCMP),
    stringify(WIFI_CIPHER_TYPE_AES_CMAC128),
    stringify(WIFI_CIPHER_TYPE_AES_CMAC128),
    stringify(WIFI_CIPHER_TYPE_GCMP),
    stringify(WIFI_CIPHER_TYPE_GCMP256),
    stringify(WIFI_CIPHER_TYPE_AES_GMAC128),
    stringify(WIFI_CIPHER_TYPE_AES_GMAC256),
};

const char* decode_wifi_cipher_type( wifi_cipher_type_t ctype) {
    if (ctype < 0 or ctype >= WIFI_CIPHER_TYPE_UNKNOWN) {
        return "WIFI_CIPHER_TYPE_UNDEFINED";
    }

    return wifi_cipher_type_strings[ctype];
}
