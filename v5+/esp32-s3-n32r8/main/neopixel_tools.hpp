#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "led_strip.h"

void initialize_neopixel();
void set_neopixel_red();
void set_neopixel_green();
void set_neopixel_blue();
void clear_neopixel();
void color_cycle_neopixel();
void color_blend_neopixel();
