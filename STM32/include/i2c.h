#ifndef I2C_LOW_H
#define I2C_LOW_H

#include <stdint.h>

void I2C_INIT(void);
void i2c_transfer(uint8_t slave_addr, uint8_t data);
int  i2c_write(uint8_t slave_addr, uint8_t *buf, uint8_t len);
int i2c_read(uint8_t slave_addr, uint8_t *buf, uint8_t len);
#endif
