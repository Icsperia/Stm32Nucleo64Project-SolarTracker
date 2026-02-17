#include "stm32g070xx.h"
#include "i2c.h"
#include "lcd.h"
#include "usart.h"
#include <stdint.h>

void USART_INIT(void)
{
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

    RCC->APBENR1 |= RCC_APBENR1_USART2EN;
    GPIOA->MODER &= ~((3 << 4) | (3 << 6));
    GPIOA->MODER |= ((2 << 4) | (2 << 6));

    GPIOA->AFR[0] &= ~((0xF << 8) | (0xF << 12));
    GPIOA->AFR[0] |= ((1 << 8) | (1 << 12));

    USART2->BRR = 0x0683;
    USART2->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;

    while (!(USART2->ISR & USART_ISR_TEACK))
        ;
}

void USART_TRANS(char *s)
{
    while (*s)
    {
        while (!(USART2->ISR & USART_ISR_TXE_TXFNF))
            ;
        USART2->TDR = *s;
        s++;
    }
    while (!(USART2->ISR & USART_ISR_TC))
        ;
}