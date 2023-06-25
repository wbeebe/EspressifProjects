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

static const char *TAG = "ESP32-C3-I2C-DISPLAYS";

AlphaNumeric alnum = AlphaNumeric(0x70);
Matrix8by16 m816 = Matrix8by16(0x72);
Matrix8by16 m816_2 = Matrix8by16(0x73);
Adafruit_BNO055 bno055 = Adafruit_BNO055(0x28);

uint16_t counter{0};

// Sample clock. Counts one hour up to 59:59
// then rolls over to 00:00.
//
int8_t ones{0},
    tens{0},
    hund{0},
    thou{0};

static void clock_increment(void) {
    if (++ones > 9) { ones = 0;
        if (++tens > 5) { tens = 0;
            if (++hund > 9) { hund = 0;
                if (++thou > 5) { thou = 0;
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
    // LED strip initialization with the GPIO and 1 NeoPixel.
    led_strip_config_t strip_config = {
        .strip_gpio_num = GPIO_NUM_8,
        .max_leds = 1,
    };

    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
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

static void cycle_devices(void) {
    for(auto color : colors) {
        led_strip_set_pixel(led_strip, 0, color[0], color[1], color[2]);
        led_strip_refresh(led_strip);
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        clock_decrement();
        m816.display(thou, hund);
        m816_2.display(tens, ones);
        //clock_increment();
        alnum.display(counter++);
    }
}

static void test_8x16_glyphs() {
    m816.display(0,Circle);
    m816.display(1,Square);
    m816_2.display(0,Circle);
    m816_2.display(1,Square);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    m816.display(0,Diamond);
    m816.display(1,Check);
    m816_2.display(0,Diamond);
    m816_2.display(1,Check);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    m816.display(0,Cross);
    m816.display(1,Face);
    m816_2.display(0,Cross);
    m816_2.display(1,Face);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    m816.display(0,Frown);
    m816.display(1,Smile);
    m816_2.display(0,Frown);
    m816_2.display(1,Smile);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    m816.display(0,ForwardSlash);
    m816.display(1,BackSlash);
    m816_2.display(0,ForwardSlash);
    m816_2.display(1,BackSlash);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    m816.display(0,BackSlash);
    m816.display(1,ForwardSlash);
    m816_2.display(0,BackSlash);
    m816_2.display(1,ForwardSlash);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
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
        ESP_LOGI(TAG, "BNO055 failed to start.");
    }
}

extern "C" void app_main(void) {
    ESP_LOGI(TAG, "BEGIN");
    ESP_LOGI(TAG, IDF_VER);
    ESP_LOGI(TAG, "LED CONFIGURE");
    initialize_neo_pixel();
    ESP_LOGI(TAG, "I2C CONFIGURE");
    auto i2c_status = i2c_initialize();

    if (i2c_status != ESP_OK) {
        ESP_LOGI(TAG, "I2C FAILED INITIALIZATION");
    }
    else {
        ESP_LOGI(TAG, "I2C DEVICE SCAN.");
        i2c_scan();

        check_bno055();

        auto an_status = m816.initialize();
        auto an_status_2 = m816_2.initialize();

        if (an_status == ESP_OK and an_status_2 == ESP_OK) {
            ESP_LOGI(TAG, "Alphanumeric initialized.");
            m816.reset();
            m816_2.reset();
            alnum.initialize();
            alnum.reset();
            vTaskDelay(1000 / portTICK_PERIOD_MS);

            if (m816.test() == ESP_OK and m816_2.test() == ESP_OK) {
                alnum.test();
                test_8x16_glyphs();
                m816.reset();
                m816_2.reset();
                alnum.reset();
                ESP_LOGI(TAG, "Alphanumeric testing finished.");
            }
            else {
                ESP_LOGI(TAG, "Alphanumeric testing FAILED");
            }
        }
        else {
            ESP_LOGI(TAG, "Alphanumeric initialization FAILED.");
        }
    }

    ESP_LOGI(TAG, "Start cycling NeoPixel colors.");
    while (true) {
        cycle_devices();
    }
}
