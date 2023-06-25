#pragma once

#include "driver/i2c.h"

const uint8_t I2C_MASTER_TX_BUF_DISABLE = 0; // I2C master doesn't need buffer
const uint8_t I2C_MASTER_RX_BUF_DISABLE = 0; // I2C master doesn't need buffer
const uint8_t ACK_CHECK_EN = 0x1;
const TickType_t I2C_TICKS_TO_WAIT = (500 / portTICK_PERIOD_MS);

esp_err_t i2c_initialize(void);
esp_err_t write_byte(uint8_t device_address, uint8_t command);
esp_err_t write_data(uint8_t device_address, uint8_t *data, uint8_t length);
esp_err_t read_register(uint8_t device_address, uint8_t reg, uint8_t * buffer,
                        uint8_t len);
void i2c_scan();

// An abstract device class that defines an interface.
// Any physical device derived from this class is-a device.
// The methods are all virtual and must be implemented in the derived class.
// This allows differing devices to be, in essence, interchangeable at the
//software level.
//
class Device {
    // Initializes the devices controller chip. This method must be called AFTER
    // the call to i2c_initialize() so that the I2C buss is active.
    //
    virtual esp_err_t initialize() = 0;

    // Reset the device to a known state. For displays this means setting the
    // display to a known state, such as blank or off. It is read to be used.
    // This should always
    // be called after initialize().
    //
    virtual esp_err_t reset() = 0;

    // A simple test for the device. For displays this means turning on LEDs in
    // a known pattern. This should be called after a call to reset().
    // After test() you should call reset() again.
    //
    virtual esp_err_t test() = 0;
};
