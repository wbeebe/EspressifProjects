#include "ht16k33.hpp"

esp_err_t ht16k33_initialize(i2c_master_dev_handle_t &device_handle) {
    auto error = ESP_OK;
    for (auto command : initialize_command_sequence) {
        error = i2c_master_transmit(
            device_handle, &command, 1, I2C_TICKS_TO_WAIT);
        if (error != ESP_OK) return error;
    }
    return error;
}
