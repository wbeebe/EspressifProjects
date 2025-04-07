#include "ht16k33.hpp"

esp_err_t ht16k33_initialize(uint8_t device_address) {
    auto error = ESP_OK;
    for (auto command : initialize_command_sequence) {
        error = i2c_master_write_to_device(
            I2C_NUM_0, device_address, &command, 1, I2C_TICKS_TO_WAIT);
        if (error != ESP_OK) return error;
    }
    return error;
}
