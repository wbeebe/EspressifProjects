/**
  DualBlink

  This example code is in the Public Domain (or CC0 licensed, at your option.)

  Unless required by applicable law or agreed to in writing, this
  software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
  CONDITIONS OF ANY KIND, either express or implied.
**/
#include <stdio.h>
#include <array>
#include <cinttypes>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"
#include "esp_system.h"
#include "esp_psram.h"

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

// Task 1.
//
static void task_blink_neo_pixel(void * pvParameters) {
    while(true) {
        for(auto color : colors) {
            led_strip_set_pixel(led_strip, 0, color[0], color[1], color[2]);
            led_strip_refresh(led_strip);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
        vTaskDelay(9500 / portTICK_PERIOD_MS);
    }
}

// Task 2.
//
static void task_blink_led(void * pvParameters) {
    gpio_reset_pin(GPIO_NUM_46);

    // Set the GPIO as a push/pull output
    //
    gpio_set_direction(GPIO_NUM_46, GPIO_MODE_OUTPUT);

    // Task 2 endless loop.
    //
    while (true) {
        gpio_set_level(GPIO_NUM_46, true);   // LED on
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_NUM_46, false);  // LED off
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_NUM_46, true);   // LED on
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_NUM_46, false);  // LED off
        vTaskDelay(9700 / portTICK_PERIOD_MS);
    }
}

// Main entry.
//
extern "C" void app_main(void) {
    static const char *TAG = "DUAL_BLINK_V5";
    int core = xPortGetCoreID();
    ESP_LOGI(TAG, "BEGIN");
    ESP_LOGI(TAG, "ESP-IDF VERSION %s", esp_get_idf_version());
    ESP_LOGI(TAG, "APP_MAIN CORE %i", core);
    ESP_LOGI(TAG, "FREE HEAP %" PRIu32, esp_get_free_heap_size());
    ESP_LOGI(TAG, "INITIALIZE NEOPIXEL");
    initialize_neo_pixel();

    // Create task 1.
    //
    ESP_LOGI(TAG, "CREATE TASK 1");
    TaskHandle_t xHandle1 = NULL;
    static uint8_t ucParameterToPass1 = 1;

    xTaskCreate(
        task_blink_neo_pixel,
        "BlinkNeoPixel",        // human readable task name.
        4096,                   // stack size in bytes.
        &ucParameterToPass1,
        tskIDLE_PRIORITY,
        &xHandle1
    );
    configASSERT(xHandle1);

    // Create task 2.
    //
    ESP_LOGI(TAG, "CREATE TASK 2");
    TaskHandle_t xHandle2 = NULL;
    static uint8_t ucParameterToPass2 = 1;

    xTaskCreate(
        task_blink_led,
        "BlinkLED",             // human-readable task name.
        4096,                   // stack size in bytes.
        &ucParameterToPass2,
        tskIDLE_PRIORITY,
        &xHandle2
    );
    configASSERT(xHandle2);

    // Stay in an endless loop. Don't return from this task.
    //
    ESP_LOGI(TAG, "ENTER MAIN LOOP");
    while (true) {
        vTaskDelay(5000 / portTICK_PERIOD_MS); // 5 second period
    }
}
