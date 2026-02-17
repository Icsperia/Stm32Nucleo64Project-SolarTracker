#ifndef USART_H
#define USART_H

#include <stdint.h>

void USART_INIT(void);
void USART_TRANS(char *s);
void uart_printf(const char *format, ...);

#endif 