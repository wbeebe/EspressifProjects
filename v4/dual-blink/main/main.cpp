/* Dual Blink Application

   This code is licensed under Apache Version 2.0, January 2004

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
 */
#include <vector>
#include <tuple>
#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"

// Task 1.
//
static void task_blink_neo_pixel(void * pvParameters) {
    static led_strip_t *pStrip_a;
    pStrip_a = led_strip_init(CONFIG_BLINK_LED_RMT_CHANNEL, CONFIG_BLINK_GPIO, 1);
    pStrip_a->clear(pStrip_a, 50);

    /* Create a vector of color tuples to cycle through continuously.
     */
    typedef std::tuple<int, int, int, int> led_color;

    static std::vector <led_color> colors {
        {0,32,0,0},  // red
        {0,0,32,0},  // green
        {0,0,0,32},  // blue
        {0,0,32,32}, // cyan
        {0,32,0,32}, // magenta
        {0,32,16,0}, // yellow
        {0,0,0,0}    // black
        };

    // Stay in an endless loop. Don't return from this task.
    //
    while(true) {
        for(auto c : colors) {
            pStrip_a->set_pixel(pStrip_a,
                std::get<0>(c), std::get<1>(c), std::get<2>(c), std::get<3>(c));
            pStrip_a->refresh(pStrip_a, 100);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        
            // Set NeoPixel LED dark by clearing all its individual LEDs.
            pStrip_a->clear(pStrip_a, 50);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
    }
}

// Task 2.
//
static void task_blink_led(void * pvParameters) {
    gpio_reset_pin(GPIO_NUM_46);
    gpio_set_direction(GPIO_NUM_46, GPIO_MODE_OUTPUT); // Set as push/pull output

    // Stay in an endless loop. Don't return from this task.
    // External LED has a three second period, with the LED flashed twice in
    // quick succession with a long (2.7 second) off period.
    //
    while (true) {
        gpio_set_level(GPIO_NUM_46, true);   // LED on
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_NUM_46, false);  // LED off
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_NUM_46, true);   // LED on
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_NUM_46, false);  // LED off
        vTaskDelay(2700 / portTICK_PERIOD_MS);
    }
}

extern "C" void app_main(void) {
    static const char *TAG = "DUAL_BLINK";
    int core = xPortGetCoreID();
    ESP_LOGI(TAG, "app_main running on core %i", core);
    ESP_LOGI(TAG, "CONFIG_BLINK_GPIO %i", CONFIG_BLINK_GPIO);

    // Create task 1.
    //
    TaskHandle_t xHandle1 = NULL;
    static uint8_t ucParameterToPass1 = 1;

    ESP_LOGI(TAG, "Start Task 1");
    xTaskCreate(
        task_blink_neo_pixel,
        "BlinkNeoPixel",        // human readable task name.
        2048,                   // stack size in bytes.
        &ucParameterToPass1,
        tskIDLE_PRIORITY,
        &xHandle1
    );
    configASSERT(xHandle1);

    // Create task 2.
    //
    TaskHandle_t xHandle2 = NULL;
    static uint8_t ucParameterToPass2 = 1;

    ESP_LOGI(TAG, "Start Task 2");
    xTaskCreate(
        task_blink_led,
        "BlinkLED",             // human-readable task name.
        2048,                   // stack size in bytes.
        &ucParameterToPass2,
        tskIDLE_PRIORITY,
        &xHandle2
    );
    configASSERT(xHandle2);

    // Stay in an endless loop. Don't return from this task.
    //
    while (true) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
