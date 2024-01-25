/* ESP32-S3 N32R8 Work Example

   This example code is released under the Apache License, Version 2

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <esp_log.h>
#include <esp_chip_info.h>
#include <esp_mac.h>
#include <esp_flash.h>
#include <nvs_flash.h>

#include "chip_decode.hpp"
#include "neopixel_tools.hpp"
#include "webserver.hpp"
#include "utilities.hpp"
//
// Display selective chip information on the console.
//
void chip_information(string &return_SSID) {
    //
    // First gather all the information we want to display.
    //
    uint8_t MAC_ADDR[6]{0};
    char unique_id[13];
    esp_read_mac(&MAC_ADDR[0], ESP_MAC_BASE);
    snprintf(unique_id, sizeof(unique_id), "%02X%02X%02X%02X%02X%02X",
             MAC_ADDR[0],MAC_ADDR[1],MAC_ADDR[2],
             MAC_ADDR[3],MAC_ADDR[4],MAC_ADDR[5]);
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    string features;
    decode_features(chip_info.features, features);
    string idf_version = esp_get_idf_version();
    string chip_model;
    translate_esp_chip_model(chip_info.model, chip_model);
    string heap_size;
    comma_format_number(esp_get_free_heap_size(), heap_size);
    uint32_t nflash_size{0};
    string flash_size;
    esp_flash_get_size(NULL, &nflash_size);
    comma_format_number(nflash_size, flash_size);
    char SSID[32];
    snprintf(SSID, sizeof(SSID), "%s-%02X%02X",
             chip_model.c_str(),
             MAC_ADDR[4],MAC_ADDR[5]);
    return_SSID = SSID;
    //
    // Then display all the gathered and formatted information.
    //
    ESP_LOGI(TAG, "ESP-IDF VERSION: %s", idf_version.c_str());
    ESP_LOGI(TAG, "CHIP MODEL: %s", chip_model.c_str());
    ESP_LOGI(TAG, "CHIP FEATURES: %s", features.c_str());
    ESP_LOGI(TAG, "REVISION: %X", chip_info.revision);
    ESP_LOGI(TAG, "FREE HEAP: %s BYTES", heap_size.c_str());
    ESP_LOGI(TAG, "FLASH SIZE: %s %s BYTES", flash_size.c_str(),
        (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "EMBEDDED" : "EXTERNAL");
    ESP_LOGI(TAG, "MAC ADDR: %s", unique_id);
    ESP_LOGI(TAG, "SSID: %s", SSID);
}
//
// The main loop. Execute all the various initialization and starup routines,
// then go into a permanent loop where all we do is sleep.
//
extern "C" esp_err_t initialize_wifi_station(const char *SSID);

extern "C" void app_main(void) {
    ESP_LOGI(TAG, "APP_MAIN BEGIN");

    string SSID;
    chip_information(SSID);

    ESP_LOGI(TAG, "APP_MAIN INITIALIZE NEOPIXEL");
    initialize_neopixel();
    ESP_LOGI(TAG, "APP_MAIN CYCLE NEOPIXEL");
    color_cycle_neopixel();

    ESP_LOGI(TAG, "APP_MAIN INITIALISE NVS FLASH");
    esp_err_t ret = nvs_flash_init();
    //
    // If initialization fails then erase non-volatile storage and try again.
    //
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
        ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_LOGI(TAG, "APP_MAIN ERASE NVS FLASH");
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    ESP_ERROR_CHECK(ret);

    ESP_LOGI(TAG, "APP_MAIN INITIALIZE WIFI");
    bool wifi_initialize_success = false;

    if (initialize_wifi_station(SSID.c_str()) == ESP_OK) {
        ESP_LOGI(TAG, "APP_MAIN INITIALIZE WEBSERVER");
        initialize_webserver(SSID);
        wifi_initialize_success = true;
    }
    else {
        ESP_LOGI(TAG, "APP_MAIN WEBSERVER NOT INITIALIZED");
    }

    ESP_LOGI(TAG, "APP_MAIN ENTERING MAIN LOOP");

    while (true) {
        if (wifi_initialize_success) {
            vTaskDelay(5000 / portTICK_PERIOD_MS);
        }
        else {
            set_neopixel_red();
            vTaskDelay(500 / portTICK_PERIOD_MS);
            clear_neopixel();
            vTaskDelay(4000 / portTICK_PERIOD_MS);
        }
    }
}
