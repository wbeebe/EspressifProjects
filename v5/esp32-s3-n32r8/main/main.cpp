/* ESP32-S3 N32R8 Work Example

   This example code is released under the Apache License, Version 2

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <array>
#include <cinttypes>
#include <string>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"
#include "esp_chip_info.h"
#include "esp_system.h"

static const char *TAG = "ESP32-S3-DevKitC-1.1-N32R8";

#define stringify( _name ) #_name

static const char* translate_esp_chip_model(esp_chip_model_t model){
    switch(model) {
        case CHIP_ESP32:   return stringify(CHIP_ESP32);
        case CHIP_ESP32S2: return stringify(CHIP_ESP32S2);
        case CHIP_ESP32S3: return stringify(CHIP_ESP32S3);
        case CHIP_ESP32C3: return stringify(CHIP_ESP32C3);
        case CHIP_ESP32H2: return stringify(CHIP_ESP32H2);
        case CHIP_ESP32C2: return stringify(CHIP_ESP32C2);
        //case CHIP_ESP32C6: return stringify(CHIP_ESP32C6);
    }

    return "CHIP_UNKNOWN";
}

using std::string;
static void decode_features(uint32_t features, string &results) {
    if (features == 0) {
        results = "NO_FEATURES";
        return;
    }

    if (features & CHIP_FEATURE_EMB_FLASH) results += "FLASH ";
    if (features & CHIP_FEATURE_WIFI_BGN) results += "WIFI ";
    if (features & CHIP_FEATURE_BLE) results += "BLE ";
    if (features & CHIP_FEATURE_BT) results += "BT ";
    if (features & CHIP_FEATURE_IEEE802154) results += "IEEE802154 ";
    if (features & CHIP_FEATURE_EMB_PSRAM) results += "PSRAM";
}

// Create an array of color arrays to cycle through continuously.
//
using std::array;
const array<array<int, 3>, 7> colors {{
    {32,0,0},  // red
    {0,32,0},  // green
    {0,0,32},  // blue
    {0,32,32}, // cyan
    {32,0,32}, // magenta
    {32,16,0}, // yellow
    {0,0,0}    // black
    }};

static led_strip_handle_t led_strip;
static void initialize_neo_pixel() {
    led_strip_config_t strip_config = {
        .strip_gpio_num = CONFIG_BLINK_GPIO,
        .max_leds = 1, // at least one LED on board
    };

    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10000000, // 10 MHz
    };

    ESP_ERROR_CHECK(led_strip_new_rmt_device(
        &strip_config, &rmt_config, &led_strip));

    // Darken NeoPixel by setting individual LED values to 0
    //
    led_strip_clear(led_strip);
}

static void blink_neo_pixel() {
    for(auto color : colors) {
        led_strip_set_pixel(led_strip, 0, color[0], color[1], color[2]);
        led_strip_refresh(led_strip);
        vTaskDelay(800 / portTICK_PERIOD_MS);
        led_strip_clear(led_strip);
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

extern "C" void app_main(void) {
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    string features;
    decode_features(chip_info.features, features);

    ESP_LOGI(TAG, "BEGIN");
    ESP_LOGI(TAG, "ESP-IDF VERSION %s", esp_get_idf_version());
    ESP_LOGI(TAG, "CHIP MODEL %s", translate_esp_chip_model(chip_info.model));
    ESP_LOGI(TAG, "CHIP FEATURES %s", features.c_str());
    ESP_LOGI(TAG, "REVISION %X", chip_info.revision);
    ESP_LOGI(TAG, "FREE HEAP %" PRIu32, esp_get_free_heap_size());
    ESP_LOGI(TAG, "INITIALIZE NEOPIXEL");

    initialize_neo_pixel();

    ESP_LOGI(TAG, "ENTER MAIN LOOP");

    while (true) {
        blink_neo_pixel();
    }
}
