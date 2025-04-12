#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "i2c_support.hpp"

esp_err_t i2c_initialize(void) {
    i2c_master_bus_config_t config;
    config.clk_source = I2C_CLK_SRC_DEFAULT;
    config.i2c_port = I2C_NUM_0;
    config.scl_io_num = GPIO_NUM_6;
    config.sda_io_num = GPIO_NUM_5;
    config.glitch_ignore_cnt = 7;
    config.intr_priority = 0;
    config.trans_queue_depth = 0;
    config.flags.allow_pd = false;
    config.flags.enable_internal_pullup = true;

    i2c_master_bus_handle_t bus_handle;
    return i2c_new_master_bus(&config, &bus_handle);
}

esp_err_t Device::initialize_device_handle() {
    i2c_master_bus_handle_t handle;
    auto error = i2c_master_get_bus_handle(I2C_NUM_0, &handle);
    if (error != ESP_OK) return error;
    device_config.dev_addr_length = I2C_ADDR_BIT_LEN_7;
    device_config.device_address = device_address;
    device_config.scl_speed_hz = 80000;
    return i2c_master_bus_add_device(handle, &device_config, &device_handle);
}

void i2c_scan() {
    uint8_t address;
    i2c_master_bus_handle_t bus_handle;
    if (i2c_master_get_bus_handle(I2C_NUM_0, &bus_handle) != ESP_OK) {
        return;
    }

    printf("     0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\r\n");

    for (int i = 0; i < 128; i += 16) {
        printf("%02X: ", i);
        for (int j = 0; j < 16; j++) {
            vTaskDelay(10 / portTICK_PERIOD_MS);
            fflush(stdout);
            address = i + j;
            esp_err_t ret = i2c_master_probe(bus_handle, address, I2C_TOOL_TIMEOUT_VALUE_MS);
            if (ret == ESP_OK) {
                printf("%02X ", address);
            } else if (ret == ESP_ERR_TIMEOUT) {
                printf("TO ");
            } else {
                printf("-- ");
            }
        }
        printf("\r\n");
    }
}
