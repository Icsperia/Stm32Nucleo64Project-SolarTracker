#ifndef STEPPER
#define STEPPER

#include "stm32g070xx.h"
void STEPPER_INIT1();
void STEPPER_INIT2();
void stepper_time1(uint8_t delay);
void stepper_time2(uint8_t delay);
#endif