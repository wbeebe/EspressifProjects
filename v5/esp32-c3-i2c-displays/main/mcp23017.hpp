#pragma once
#include "i2c_support.hpp"

const uint8_t MCP23017_DEFAULT_ADDRESS = 0x20;

// MCP23017 register addresses port A
//
const uint8_t IODIRA   = 0x00;
const uint8_t IPOLA    = 0x02;
const uint8_t GPINTENA = 0x04;
const uint8_t DEFVALA  = 0x06;
const uint8_t INTCONA  = 0x08;
const uint8_t IOCONA   = 0x0A;
const uint8_t GPPUA    = 0x0C;
const uint8_t INTFA    = 0x0E;
const uint8_t INTCAPA  = 0x10;
const uint8_t GPIOA    = 0x12;
const uint8_t OLATA    = 0x14;

// MCP23017 register addresses port B
//
const uint8_t IODIRB   = 0x01;
const uint8_t IPOLB    = 0x03;
const uint8_t GPINTENB = 0x05;
const uint8_t DEFVALB  = 0x07;
const uint8_t INTCONB  = 0x09;
const uint8_t IOCONB   = 0x0B;
const uint8_t GPPUB    = 0x0D;
const uint8_t INTFB    = 0x0F;
const uint8_t INTCAPB  = 0x11;
const uint8_t GPIOB    = 0x13;
const uint8_t OLATB    = 0x15;


class MCP23017 : Device {
    uint8_t device_address;

    public:
        MCP23017(uint8_t _device_address);

        esp_err_t initialize();

        esp_err_t reset();

        esp_err_t test();

        esp_err_t write_byte_data(const uint8_t port, const uint8_t data);

};