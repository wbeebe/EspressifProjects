/*
 * Copyright 2025 William H. Beebe, Jr.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <array>
#include "neopixel_tools.hpp"
using std::array;

enum Colors {
    BLACK,
    RED,
    GREEN,
    BLUE,
    CYAN,
    MAGENTA,
    YELLOW,
};

// Create an array of color arrays to cycle through continuously.
//
const array<array<int, 3>, 7> colors {{
    {0,0,0},   // BLACK
    {32,0,0},  // RED
    {0,32,0},  // GREEN
    {0,0,32},  // BLUE
    {0,32,32}, // CYAN
    {32,0,32}, // MAGENTA
    {32,16,0}, // YELLOW
    }};

auto last_color = colors[BLACK];

static led_strip_handle_t led_strip;
void initialize_neopixel() {
    led_strip_config_t strip_config;
    strip_config.strip_gpio_num = CONFIG_BLINK_GPIO;
    strip_config.max_leds = 1; // at least one LED on board
    strip_config.led_pixel_format = LED_PIXEL_FORMAT_GRB;
    strip_config.led_model = LED_MODEL_WS2812;
    strip_config.flags.invert_out = false;

    led_strip_rmt_config_t rmt_config;
    rmt_config.clk_src = RMT_CLK_SRC_DEFAULT;
    rmt_config.resolution_hz = 10000000; // 10 MHz
    rmt_config.mem_block_symbols = 0;
    rmt_config.flags.with_dma = false;

    ESP_ERROR_CHECK(led_strip_new_rmt_device(
        &strip_config, &rmt_config, &led_strip));

    led_strip_clear(led_strip);
}

bool toggle_neopixel_color(const array<int, 3> color) {
    if (color != last_color) {
        led_strip_set_pixel(led_strip, 0, color[0], color[1], color[2]);
        led_strip_refresh(led_strip);
        last_color = color;
        return true;
    }
    else {
        return turn_off_neopixel();
    }
}

bool set_neopixel_red() {
    return toggle_neopixel_color(colors[RED]);
}

bool set_neopixel_green() {
    return toggle_neopixel_color(colors[GREEN]);
}

bool set_neopixel_blue() {
    return toggle_neopixel_color(colors[BLUE]);
}

// Darken NeoPixel by setting all LED values to 0
//
bool turn_off_neopixel() {
    led_strip_clear(led_strip);
    last_color = colors[BLACK];
    return false;
}

void color_cycle_neopixel() {
    for(auto color : colors) {
        led_strip_set_pixel(led_strip, 0, color[0], color[1], color[2]);
        led_strip_refresh(led_strip);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    } 
    turn_off_neopixel();
}

void color_blend_neopixel() {
    uint8_t red(0), green(0), blue(0);
    for (; red < 32; ++red) {
        led_strip_set_pixel(led_strip, 0, red, green, blue);
        led_strip_refresh(led_strip);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    for (; green < 32; ++green) {
        --red;
        led_strip_set_pixel(led_strip, 0, red, green, blue);
        led_strip_refresh(led_strip);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    for (; blue < 32; ++blue) {
        --green;
        led_strip_set_pixel(led_strip, 0, red, green, blue);
        led_strip_refresh(led_strip);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    turn_off_neopixel();
}
