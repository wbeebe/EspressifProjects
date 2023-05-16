#include "neopixel_tools.hpp"

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

    // Darken NeoPixel by setting individual LED values to 0
    //
    led_strip_clear(led_strip);
}

void set_neopixel_red() {
    auto color = colors[0];
    led_strip_set_pixel(led_strip, 0, color[0], color[1], color[2]);
    led_strip_refresh(led_strip);
}

void set_neopixel_green() {
    auto color = colors[1];
    led_strip_set_pixel(led_strip, 0, color[0], color[1], color[2]);
    led_strip_refresh(led_strip);
}

void set_neopixel_blue() {
    auto color = colors[2];
    led_strip_set_pixel(led_strip, 0, color[0], color[1], color[2]);
    led_strip_refresh(led_strip);
}

void clear_neopixel() {
    led_strip_clear(led_strip);
}

void blink_neopixel() {
    for(auto color : colors) {
        led_strip_set_pixel(led_strip, 0, color[0], color[1], color[2]);
        led_strip_refresh(led_strip);
        vTaskDelay(400 / portTICK_PERIOD_MS);
        led_strip_clear(led_strip);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void blend_neopixel() {
    uint8_t red(0), green(0), blue(0);
    for (; red < 128; ++red) {
        led_strip_set_pixel(led_strip, 0, red, green, blue);
        led_strip_refresh(led_strip);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    for (; green < 128; ++green) {
        --red;
        led_strip_set_pixel(led_strip, 0, red, green, blue);
        led_strip_refresh(led_strip);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    for (; blue < 128; ++blue) {
        --green;
        led_strip_set_pixel(led_strip, 0, red, green, blue);
        led_strip_refresh(led_strip);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }

    vTaskDelay(1000 / portTICK_PERIOD_MS);
    led_strip_clear(led_strip);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}
