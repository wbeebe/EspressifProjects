#pragma once

#include "vt52.hpp"

const static uint8_t DEFAULT_CHIP_SELECT(10);
const static uint8_t DEFAULT_CLOCK(12);
const static uint8_t DEAFULT_MOSI(11);

enum COMMANDS {
    NO_OP,
    ROW_0,
    ROW_1,
    ROW_2,
    ROW_3,
    ROW_4,
    ROW_5,
    ROW_6,
    ROW_7,
    DECODE_MODE,
    INTENSITY,
    SCAN_LIMIT,
    SHUTDOWN,
    DISPLAY_TEST = 15
};

class MAX7219 {
    private:
        spi_bus_config_t spi_bus_config;
        spi_device_interface_config_t spi_device_interface_config;
        void write_register(const uint8_t _register, const uint8_t value);
        MAX7219();

    public:
        MAX7219(
            const uint8_t chip_select,
            const uint8_t clock,
            const uint8_t mosi,
            const uint8_t data);

        void clear_display();
        void set_led(const uint8_t row_index, const uint8_t column_index);
        void set_row(const uint8_t row_index);
        void set_column(const uint8_t column_index);
        void write_data(const uint8_t *_data, const uint8_t length);
};
