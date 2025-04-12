#include "i2c_support.hpp"
#include "mcp23017.hpp"

MCP23017::MCP23017(uint8_t _device_address) {
    device_address = _device_address;
}

esp_err_t MCP23017::initialize() {
    auto error = initialize_device_handle();
    if (error != ESP_OK) return error;
    error = write_byte_data(IODIRA, 0x00);
    if (error != ESP_OK) return error;
    return write_byte_data(IODIRB, 0x00);
}

esp_err_t MCP23017::reset() {
    auto error = write_byte_data(GPIOA, 0x00);
    if (error != ESP_OK) return error;
    return write_byte_data(GPIOB, 0x00);
}

esp_err_t MCP23017::test() {
    auto error = write_byte_data(GPIOA, 0xFF);
    if (error != ESP_OK) return error;
    return write_byte_data(GPIOB, 0xFF);
}

esp_err_t MCP23017::write_byte_data(uint8_t port, uint8_t data) {
    uint8_t buffer[2];
    buffer[0] = port;
    buffer[1] = data;
    return i2c_master_transmit( device_handle,
        buffer, sizeof(buffer), (500 / portTICK_PERIOD_MS));
}


void MCP23017::march_bits(void) {
    write_byte_data(GPIOA, bit_arrays[bit_arrays_index_a]);
    write_byte_data(GPIOB, bit_arrays[bit_arrays_index_a]);
    if (++bit_arrays_index_a >= bit_arrays_max)
        bit_arrays_index_a = bit_arrays_min;
}
