#pragma once

#include "driver/i2c_master.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

const uint8_t I2C_MASTER_TX_BUF_DISABLE = 0; // I2C master doesn't need buffer
const uint8_t I2C_MASTER_RX_BUF_DISABLE = 0; // I2C master doesn't need buffer
const uint8_t ACK_CHECK_EN = 0x1;
const TickType_t I2C_TICKS_TO_WAIT = (500 / portTICK_PERIOD_MS);
const uint16_t I2C_TOOL_TIMEOUT_VALUE_MS = 50;

esp_err_t i2c_initialize(void);
void i2c_scan();

// An abstract device class that defines an interface.
// Any physical device derived from this class is-a device.
// The methods are all virtual and must be implemented in the derived class.
// This allows differing devices to be, in essence, interchangeable at the
// software level.
//
class Device {
protected:
    uint8_t device_address;
    i2c_device_config_t device_config;
    i2c_master_dev_handle_t device_handle;

    esp_err_t initialize_device_handle();

public:
    // Initializes the device's controller chip. This method must be called AFTER
    // the call to i2c_initialize() so that the I2C buss is active.
    //
    virtual esp_err_t initialize() = 0;

    // Reset the device to a known state. For displays this means setting the
    // display to a known state, such as blank or off.
    // This should always be called after initialize().
    //
    virtual esp_err_t reset() = 0;

    // A simple test for the device. For displays this means turning on LEDs in
    // a known pattern. This should be called after a call to reset().
    // After test() you should call reset() again.
    //
    virtual esp_err_t test() = 0;
};
