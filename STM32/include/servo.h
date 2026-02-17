#ifndef PCA9685_H
#define PCA9685_H

#include <stdint.h>

void PCA9685_Init(void);
void PCA9685_SetPWM(uint8_t channel, uint16_t on, uint16_t off);
void PCA9685_SetServoAngle(uint8_t channel, uint8_t angle);

#endif
