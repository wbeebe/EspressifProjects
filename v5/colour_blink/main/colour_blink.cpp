/* Colour Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <array>
#include <cinttypes>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"

static const char *TAG = "COLOUR_BLINK";

// Use project configuration menu (idf.py menuconfig) to choose the GPIO
// to blink, or you can edit the following line and set a number here.
//
static gpio_num_t BLINK_GPIO{static_cast<gpio_num_t>(CONFIG_BLINK_GPIO)};

#ifdef CONFIG_BLINK_LED_RMT

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
static int cycle_count{0};

static void blink_led(void) {
    ESP_LOGI(TAG, "NeoPixel cycle %d.", ++cycle_count);

    for(auto color : colors) {
        led_strip_set_pixel(led_strip, 0, color[0], color[1], color[2]);
        led_strip_refresh(led_strip);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }

    led_strip_clear(led_strip);
}

static void configure_led(void) {
    ESP_LOGI(TAG, "Configure addressable NeoPixel.");
    // LED strip initialization with the GPIO and pixels number
    led_strip_config_t strip_config = {
        .strip_gpio_num = BLINK_GPIO,
        .max_leds = 1, // at least one LED on board
    };
    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
    };
    ESP_ERROR_CHECK(
        led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
    // Set all LED off to clear all pixels
    led_strip_clear(led_strip);
}

#elif CONFIG_BLINK_LED_GPIO

uint_t s_led_state = 1;

static void blink_led(void) {
    ESP_LOGI(TAG, "Turning the LED %s", s_led_state == true ? "ON" : "OFF");
    // Set the GPIO level according to the state, LOW (0) or HIGH (1)
    gpio_set_level(BLINK_GPIO, s_led_state);
    s_led_state = s_led_state == 1 ? 0 : 1;
}

static void configure_led(void) {
    ESP_LOGI(TAG, "Configure regular GPIO LED.");
    gpio_reset_pin(BLINK_GPIO);
    // Set the GPIO as a push/pull output
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
}

#endif

extern "C" void app_main(void) {
    // Configure the peripheral according to the LED type
    configure_led();

    while (true) {
        blink_led();
        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    }
}
