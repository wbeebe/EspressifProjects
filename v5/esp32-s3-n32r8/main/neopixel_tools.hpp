#pragma once

#include <array>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "led_strip.h"

void initialize_neopixel();
void set_neopixel_red();
void set_neopixel_green();
void set_neopixel_blue();
void blink_neopixel();
void blend_neopixel();
void clear_neopixel();
