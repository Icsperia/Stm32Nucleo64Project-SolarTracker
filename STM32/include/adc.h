#ifndef ADC_H
#define ADC_H

#include "stm32g0xx_hal.h"

void ADC1_INIT(void);

void ADC1_READ(uint16_t *ch0);
void ADC1_READ1(uint16_t *ch1);
void ADC1_READ4(uint16_t *ch4);
void ADC1_READ5(uint16_t *ch9);

#endif
