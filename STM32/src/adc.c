#include "adc.h"
#include "stm32g070xx.h"
void ADC1_INIT(void)
{
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
    RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
    RCC->APBENR2 |= RCC_APBENR2_ADCEN;
    GPIOA->MODER |= ((3 << 0) | (3 << 2) | (3 << 8));
    GPIOA->PUPDR &= ~((3 << 0) | (3 << 2) | (3 << 8));

    GPIOB->MODER |= ((3 << 2));
    GPIOB->PUPDR &= ~((3 << 2));

    ADC1->CR |= ADC_CR_ADVREGEN;
    for (volatile int i = 0; i < 1000; i++)
        ;

    ADC1->CR |= ADC_CR_ADCAL;
    while ((ADC1->CR & ADC_CR_ADCAL))
        ;
    ADC1->ISR |= ADC_ISR_ADRDY;
    ADC1->CR |= ADC_CR_ADEN;

    ADC1->SMPR |= 2;

    while (!(ADC1->ISR & ADC_ISR_ADRDY))
        ;
}

void ADC1_READ(uint16_t *ch0)
{
    ADC1->CHSELR = ADC_CHSELR_CHSEL0;
    ADC1->CR |= ADC_CR_ADSTART;

    while (!(ADC1->ISR & ADC_ISR_EOC))
        ;
    *ch0 = ADC1->DR;
}

void ADC1_READ1(uint16_t *ch1)
{
    ADC1->CHSELR = ADC_CHSELR_CHSEL1;
    ADC1->CR |= ADC_CR_ADSTART;

    while (!(ADC1->ISR & ADC_ISR_EOC))
        ;
    *ch1 = ADC1->DR;
}

void ADC1_READ4(uint16_t *ch4)
{
    ADC1->CHSELR = ADC_CHSELR_CHSEL4;
    ADC1->CR |= ADC_CR_ADSTART;

    while (!(ADC1->ISR & ADC_ISR_EOC))
        ;
    *ch4 = ADC1->DR;
}

void ADC1_READ9(uint16_t *ch9)
{
    ADC1->CHSELR = ADC_CHSELR_CHSEL9;
    ADC1->CR |= ADC_CR_ADSTART;

    while (!(ADC1->ISR & ADC_ISR_EOC))
        ;
    *ch9 = ADC1->DR;
}
