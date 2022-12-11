/* ESP32-C3-WROOM-02/ESP32-C3-DevKitC-02 V1.1

   This code is licensed under Apache Version 2.0, January 2004

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"

#include <vector>
#include <tuple>

#include "ht16k33.hpp"
#include "matrix8by16.hpp"
#include "alphanumeric.hpp"
#include "Adafruit_BNO055.hpp"

static const char *TAG = "LED_DISPLAY";

AlphaNumeric alnum = AlphaNumeric(0x70);
Matrix8by16 m816 = Matrix8by16(0x72);
Matrix8by16 m816_2 = Matrix8by16(0x73);
Adafruit_BNO055 bno055 = Adafruit_BNO055(0x28);

uint16_t counter = 0;

/* Sample clock. Counts one hour up to 59:59
   then rolls over to 00:00.
 */
uint8_t ones = 0,
    tens = 0,
    hund = 0,
    thou = 0;

static void clock_count(void) {
    if (++ones > 9) { ones = 0;
        if (++tens > 5) { tens = 0;
            if (++hund > 9) { hund = 0;
                if (++thou > 5) { thou = 0;
                }
            }
        }
    }
}

/* Everything to support blinking the NeoPixel LED.
 */
static led_strip_t *pStrip_a;
static void configure_led(void) {
    // LED strip initialization with the GPIO and pixels number
    pStrip_a = led_strip_init(CONFIG_BLINK_LED_RMT_CHANNEL, GPIO_NUM_8, 1);
    // Set NeoPixel LED dark by clearing all its individual LEDs.
    pStrip_a->clear(pStrip_a, 50);
}

/* Create a vector of color tuples to cycle through continuously.
   I wanted something similar to what I do in Python.
 */
typedef std::tuple<int, int, int, int> led_color;

std::vector <led_color> colors {
    {0,32,0,0},  // red
    {0,0,32,0},  // green
    {0,0,0,32},  // blue
    {0,0,32,32}, // cyan
    {0,32,0,32}, // magenta
    {0,32,16,0}, // yellow
    {0,0,0,0}    // black
    };

static void cycle_led_colors(void) {
    for(auto c : colors) {
        pStrip_a->set_pixel(pStrip_a,
            std::get<0>(c), std::get<1>(c), std::get<2>(c), std::get<3>(c));
        pStrip_a->refresh(pStrip_a, 100);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        
        // Set NeoPixel LED dark by clearing all its individual LEDs.
        pStrip_a->clear(pStrip_a, 50);
        vTaskDelay(500 / portTICK_PERIOD_MS);

        m816.display(thou, hund);
        m816_2.display(tens, ones);
        clock_count();
        alnum.display(counter++);
        //ESP_LOGI(TAG, "bnoO55 temperature %d", (bno055.getTemp() * 9)/5 + 32);
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
    ESP_LOGI(TAG, "Configure LED.");
    configure_led();
    ESP_LOGI(TAG, "Configure I2C.");
    auto i2c_status = i2c_initialize();

    if (i2c_status != ESP_OK) {
        ESP_LOGI(TAG, "I2C failed to initialize.");
    }
    else {
        ESP_LOGI(TAG, "Scan for I2C devices.");
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
        cycle_led_colors();
    }
}
