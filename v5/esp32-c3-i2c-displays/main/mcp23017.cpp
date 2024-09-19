#include "i2c_support.hpp"
#include "mcp23017.hpp"

MCP23017::MCP23017(uint8_t _device_address) {
    device_address = _device_address;
}

esp_err_t MCP23017::initialize() {
    auto rtn1 = write_byte_data(IODIRA, 0x00);
    auto rtn2 = write_byte_data(IODIRB, 0x00);

    if (rtn1 != ESP_OK) return rtn1;
    return rtn2;
}

esp_err_t MCP23017::reset() {
    auto rtn1 = write_byte_data(GPIOA, 0x00);
    auto rtn2 = write_byte_data(GPIOB, 0x00);

    if (rtn1 != ESP_OK) return rtn1;
    return rtn2;
}

esp_err_t MCP23017::test() {
    auto rtn1 = write_byte_data(GPIOA, 0xFF);
    auto rtn2 = write_byte_data(GPIOB, 0xFF);

    if (rtn1 != ESP_OK) return rtn1;
    return rtn2;
}

esp_err_t MCP23017::write_byte_data(uint8_t port, uint8_t data) {
    uint8_t buffer[2];
    buffer[0] = port;
    buffer[1] = data;
    return i2c_master_write_to_device(
        I2C_NUM_0, device_address, buffer, sizeof(buffer),
        (500 / portTICK_PERIOD_MS));
}
