#ifndef INAREAD
#define INAREAD
#include <stdint.h>
#define SHUNT_RESISTOR 100


float ina_read_shunt_voltage(uint8_t addr);
float ina_read_bus_voltage(uint8_t addr);

#endif