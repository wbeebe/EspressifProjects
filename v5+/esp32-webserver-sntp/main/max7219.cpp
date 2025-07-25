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
#include "driver/spi_master.h"
#include "hal/spi_types.h"
#include "max7219.hpp"

MAX7219::MAX7219() { }

MAX7219::MAX7219(
    const uint8_t chip_select,
    const uint8_t clock,
    const uint8_t mosi,
    const uint8_t data) {

    spi_bus_config.mosi_io_num = mosi;
    spi_bus_config.data0_io_num = data;
    spi_bus_config.sclk_io_num = clock;

    spi_bus_config.quadwp_io_num = -1;
    spi_bus_config.quadhd_io_num = -1;

    spi_device_interface_config.clock_speed_hz = 10 * 1000 * 1000; // 10 MHz
    spi_device_interface_config.mode = 0;
    spi_device_interface_config.spics_io_num = chip_select;
    spi_device_interface_config.queue_size = 8;
}

void MAX7219::write_register(const uint8_t _register, const uint8_t value) {

}

void clear_display() {

}

void set_led(const uint8_t row_index, const uint8_t column_index) {

}

void set_row(const uint8_t row_index) {

}

void set_column(const uint8_t column_index) {

}

void write_data(const uint8_t *_data, const uint8_t length) {

}
