#include "stepper.h"
#include "stm32g070xx.h"

#define PB11 11
#define PB12 12
#define PC3 3
#define PC2 2

#define PB4 4
#define PB5 5
#define PB10 10
#define PB13 13

void STEPPER_INIT1()
{

    RCC->IOPENR |= RCC_IOPENR_GPIOCEN;
    RCC->IOPENR |= RCC_IOPENR_GPIOBEN;

    GPIOC->MODER &= ~((3 << (2 * PC2)) | (3 << (2 * PC3)));
    GPIOC->MODER |= ((1 << (2 * PC2)) | (1 << (2 * PC3)));
    GPIOB->MODER &= ~((3 << (2 * PB11)) | (3 << (2 * PB12)));
    GPIOB->MODER |= ((1 << (2 * PB11)) | (1 << (2 * PB12)));

    GPIOC->PUPDR &= ~(((3 << (2 * PC2)) | (3 << (2 * PC3))));
    GPIOB->PUPDR &= ~((3 << (2 * PB11)) | (3 << (2 * PB12)));
}

void STEPPER_INIT2()
{

    RCC->IOPENR |= RCC_IOPENR_GPIOBEN;

    GPIOB->MODER &= ~((3 << (2 * PB4)) | (3 << (2 * PB5)) | (3 << (2 * PB10)) | (3 << (2 * PB13)));
    GPIOB->MODER |= ((1 << (2 * PB4)) | (1 << (2 * PB5)) | (1 << (2 * PB10)) | (1 << (2 * PB13)));

    GPIOB->PUPDR &= ~((3 << (2 * PB4)) | (3 << (2 * PB5)) | (3 << (2 * PB10)) | (3 << (2 * PB13)));
    GPIOB->PUPDR &= ~((3 << (2 * PB4)) | (3 << (2 * PB5)) | (3 << (2 * PB10)) | (3 << (2 * PB13)));
}

void stepper_time1(uint8_t delay)
{

    GPIOB->BSRR = (1 << PB12) | ((1 << PB11) << 16);
    GPIOC->BSRR = ((1 << PC2) | (1 << PC3)) << 16;
    delay_us(delay);

    GPIOC->BSRR = (1 << PC3) | ((1 << PC2) << 16);
    GPIOB->BSRR = ((1 << PB11) | (1 << PB12)) << 16;
    delay_us(delay);

    GPIOC->BSRR = (1 << PC2) | ((1 << PC3) << 16);
    GPIOB->BSRR = ((1 << PB11) | (1 << PB12)) << 16;
    delay_us(delay);

    GPIOB->BSRR = (1 << PB11) | ((1 << PB12) << 16);
    GPIOC->BSRR = ((1 << PC2) | (1 << PC3)) << 16;
    delay_us(delay);
}

void stepper_time2(uint8_t delay)
{

    GPIOB->BSRR = (1 << PB4) | ((1 << PB5 | 1 << PB10 | 1 << PB13) << 16);
    delay_us(delay);

    GPIOB->BSRR = (1 << PB5) | ((1 << PB4 | 1 << PB10 | 1 << PB13) << 16);
    delay_us(delay);

    GPIOB->BSRR = (1 << PB10) | ((1 << PB4 | 1 << PB5 | 1 << PB13) << 16);
    delay_us(delay);

    GPIOB->BSRR = (1 << PB13) | ((1 << PB4 | 1 << PB5 | 1 << PB10) << 16);
    delay_us(delay);
}

void stepper_reverse_time1(uint8_t delay)
{

    GPIOB->BSRR = (1 << PB11) | ((1 << PB12) << 16);
    GPIOC->BSRR = ((1 << PC2) | (1 << PC3)) << 16;
    delay_us(delay);

    GPIOC->BSRR = (1 << PC2) | ((1 << PC3) << 16);
    GPIOB->BSRR = ((1 << PB11) | (1 << PB12)) << 16;
    delay_us(delay);

    GPIOC->BSRR = (1 << PC3) | ((1 << PC2) << 16);
    GPIOB->BSRR = ((1 << PB11) | (1 << PB12)) << 16;
    delay_us(delay);

    GPIOB->BSRR = (1 << PB12) | ((1 << PB11) << 16);
    GPIOC->BSRR = ((1 << PC2) | (1 << PC3)) << 16;
    delay_us(delay);
}

void stepper_reverse_time2(uint8_t delay)
{

    GPIOB->BSRR = (1 << PB13) | ((1 << PB4 | 1 << PB5 | 1 << PB10) << 16);
    delay_us(delay);

    GPIOB->BSRR = (1 << PB10) | ((1 << PB4 | 1 << PB5 | 1 << PB13) << 16);
    delay_us(delay);

    GPIOB->BSRR = (1 << PB5) | ((1 << PB4 | 1 << PB10 | 1 << PB13) << 16);
    delay_us(delay);

    GPIOB->BSRR = (1 << PB4) | ((1 << PB5 | 1 << PB10 | 1 << PB13) << 16);
    delay_us(delay);
}
