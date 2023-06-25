#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "i2c_support.hpp"

esp_err_t i2c_initialize(void) {
    i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, I2C_MASTER_RX_BUF_DISABLE,
                       I2C_MASTER_TX_BUF_DISABLE, 0);
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = GPIO_NUM_5;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = GPIO_NUM_6;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = 800000;
    conf.clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL;

    return i2c_param_config(I2C_NUM_0, &conf);
}

esp_err_t read_register(uint8_t device_address, uint8_t reg, uint8_t * buffer,
                        uint8_t len) {
    return i2c_master_write_read_device(I2C_NUM_0, device_address, &reg, 1,
                                        buffer, len, I2C_TICKS_TO_WAIT);
}

esp_err_t write_byte(uint8_t device_address, uint8_t command) {
    return i2c_master_write_to_device(I2C_NUM_0, device_address, &command, 1,
                                      I2C_TICKS_TO_WAIT);
}

esp_err_t write_data(uint8_t device_address, uint8_t *data, uint8_t length) {
    return i2c_master_write_to_device(I2C_NUM_0, device_address, data, length,
                                      I2C_TICKS_TO_WAIT);
}

void i2c_scan() {
    static i2c_cmd_handle_t cmd;
    static esp_err_t ret;

    uint8_t address;

    printf("     0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\r\n");

    for (int i = 0; i < 128; i += 16) {
        printf("%02x: ", i);
        for (int j = 0; j < 16; j++) {
            vTaskDelay(10 / portTICK_PERIOD_MS);
            fflush(stdout);
            address = i + j;
            cmd = i2c_cmd_link_create();
            i2c_master_start(cmd);
            i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE,
                                  ACK_CHECK_EN);
            i2c_master_stop(cmd);
            ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, I2C_TICKS_TO_WAIT);
            i2c_cmd_link_delete(cmd);
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
