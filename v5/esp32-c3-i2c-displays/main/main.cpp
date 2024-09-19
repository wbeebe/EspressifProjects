/* ESP32-C3-WROOM-02/ESP32-C3-DevKitC-02 v1.1 Device Control Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
 */
#include <stdio.h>
#include <array>
#include <string>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"
#include "esp_idf_version.h"

#include "ht16k33.hpp"
#include "matrix8by16.hpp"
#include "alphanumeric.hpp"
#include "Adafruit_BNO055.hpp"
#include "mcp23017.hpp"

static const char *TAG = "ESP32-C3-I2C-DISPLAYS";

AlphaNumeric alnum = AlphaNumeric(0x70);
AlphaNumeric alnum_2 = AlphaNumeric(0x71);
Matrix8by16 m816 = Matrix8by16(0x72);
Matrix8by16 m816_2 = Matrix8by16(0x73);
Adafruit_BNO055 bno055 = Adafruit_BNO055(0x28);
MCP23017 mcp23017 = MCP23017(MCP23017_DEFAULT_ADDRESS);

uint16_t counter{0};

// Sample clock. Counts one hour up to 59:59
// then rolls over to 00:00.
//
int8_t ones{0},
    tens{0},
    hund{0},
    thou{0};

int8_t alpha_secs_1{0},
    alpha_secs_10{0},
    alpha_min_1{0},
    alpha_min_10{0},
    alpha_hour_1{0},
    alpha_hour_10{0};

static void tick_clock(void) {
    if (++alpha_secs_1 > 9) { alpha_secs_1 = 0;
        if (++alpha_secs_10 > 5) { alpha_secs_10 = 0;
            if (++alpha_min_1 > 9) { alpha_min_1 = 0;
                if (++alpha_min_10 > 5) { alpha_min_10 = 0;
                    if (++alpha_hour_1 > 9) { alpha_hour_1 = 0;
                        if (++alpha_hour_10 > 9) { alpha_hour_10 = 0; }
                    }
                }
            }
        }
    }
}

static void clock_decrement(void) {
    if (--ones < 0) { ones = 9;
        if (--tens < 0) { tens = 5;
            if (--hund < 0) { hund = 9;
                if (--thou < 0) { thou = 5;}
            }
        }
    }
}

// Everything to support blinking the NeoPixel LED.
//
static led_strip_handle_t led_strip;
static void initialize_neo_pixel(void) {
    led_strip_config_t strip_config = {
        .strip_gpio_num = GPIO_NUM_8,
        .max_leds = 1,
        .led_pixel_format = LED_PIXEL_FORMAT_GRBW,
        .led_model = LED_MODEL_WS2812,
    };

    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_APB,
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
        .mem_block_symbols = 0,
    };

    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
    // Set NeoPixel LED dark by clearing all it individual LEDs.
    led_strip_clear(led_strip);
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

const uint8_t bit_arrays[] {
    0x01,
    0x02,
    0x04,
    0x08,
    0x10,
    0x20,
    0x40,
    0x80,
    0x40,
    0x20,
    0x10,
    0x08,
    0x04,
    0x02,
};

uint8_t bit_arrays_index = 0;
uint8_t bit_arrays_max = sizeof(bit_arrays) / sizeof(bit_arrays[0]);

static void march_bits(void) {
    mcp23017.write_byte_data(GPIOA, bit_arrays[bit_arrays_index]);
    if (++bit_arrays_index >= bit_arrays_max) bit_arrays_index = 0;
}

static void cycle_devices(void) {
    for(auto color : colors) {
        led_strip_set_pixel(led_strip, 0, color[0], color[1], color[2]);
        led_strip_refresh(led_strip);
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        clock_decrement();
        m816.display(thou, hund);
        m816_2.display(tens, ones);
        tick_clock();
        alnum.display(alpha_min_10, alpha_min_1, alpha_secs_10, alpha_secs_1);
        alnum_2.display('*','*',alpha_hour_10, alpha_hour_1);
        march_bits();
    }
}

static void check_bno055() {
    if (bno055.begin()) {
        ESP_LOGI(TAG, "BNO055 started.");
        adafruit_bno055_rev_info_t info;
        bno055.getRevInfo(&info);
        ESP_LOGI(TAG,"Acceleration Rev %d",info.accel_rev);
        ESP_LOGI(TAG,"Magnitometer Rev %d",info.mag_rev);
        ESP_LOGI(TAG,"   Gyroscope Rev %d",info.gyro_rev);
        ESP_LOGI(TAG,"          SW Rev %d",info.sw_rev);
        ESP_LOGI(TAG,"  Bootloader Rev %d",info.bl_rev);
        uint8_t system_status, self_test_result, system_error;
        bno055.getSystemStatus(
            &system_status, &self_test_result, &system_error);
        ESP_LOGI(TAG,"   System Status %02X", system_status);
        ESP_LOGI(TAG,"Self Test Result %02X", self_test_result);
        ESP_LOGI(TAG,"    System Error %02X", system_error);
    }
    else {
        ESP_LOGI(TAG, "BNO055 Startup FAILED.");
    }
}

extern "C" void app_main(void) {
    ESP_LOGI(TAG, "Begin");
    ESP_LOGI(TAG, IDF_VER);
    ESP_LOGI(TAG, "LED Configure");
    initialize_neo_pixel();
    ESP_LOGI(TAG, "I2C Configure");

    if (i2c_initialize() != ESP_OK) {
        ESP_LOGI(TAG, "I2C Initialization FAILED");
    }
    else {
        ESP_LOGI(TAG, "I2C Device Scan.");
        i2c_scan();

        check_bno055();

        if (mcp23017.initialize() == ESP_OK)
            ESP_LOGI(TAG, "MCP23017 Initialization SUCCESS");
        if (mcp23017.test() == ESP_OK)
            ESP_LOGI(TAG, "MCP23017 test SUCCESS");

        bool alpha_initialized =
            (m816.initialize() == ESP_OK and m816_2.initialize() == ESP_OK and
            alnum.initialize() == ESP_OK and alnum_2.initialize() == ESP_OK);

        if (alpha_initialized) {
            ESP_LOGI(TAG, "Alphanumeric Initialization SUCCESS");

            bool alpha_tested =
                (m816.test() == ESP_OK and m816_2.test() == ESP_OK and
                alnum.test() == ESP_OK and alnum_2.test() == ESP_OK);
            vTaskDelay(3000 / portTICK_PERIOD_MS);
            mcp23017.reset();
            m816.reset();
            m816_2.reset();
            alnum.reset();
            alnum_2.reset();
            m816.show_all_8x16_glyphs();
            m816.reset();
            m816_2.show_all_8x16_glyphs();

            if (alpha_tested) {
                ESP_LOGI(TAG, "Alphanumeric Testing FINISHED");
            }
            else {
                ESP_LOGI(TAG, "Alphanumeric Testing FAILED");
            }
        }
        else {
            ESP_LOGI(TAG, "Alphanumeric Initialization FAILED");
        }
    }

    ESP_LOGI(TAG, "Start cycling NeoPixel colors.");
    while (true) {
        cycle_devices();
    }
}
