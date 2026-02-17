#include <stdint.h>
#include "i2c.h"
#include "ina_read.h"
#define BYT 2
float ina_read_bus_voltage(uint8_t addr)
{
    uint8_t bytes[2];
    uint8_t reg = 0x02;
    i2c_write(addr, &reg, 1);
    i2c_read(addr, bytes, 2);
    uint16_t raw = ((uint16_t)bytes[0] << 8) | bytes[1];
    raw >>= 3;                     
    return (float)raw * 0.004f;          
}

float ina_read_shunt_voltage(uint8_t addr)
{
    uint8_t bytes[2];
    uint8_t reg = 0x01;
    i2c_write(addr, &reg, 1);
    i2c_read(addr, bytes, 2);
    int16_t raw = (int16_t)(((uint16_t)bytes[0] << 8) | bytes[1]);
    return (float)raw * 0.01f;           
}


