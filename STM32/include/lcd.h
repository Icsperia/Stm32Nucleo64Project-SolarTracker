#ifndef LCD_H
#define LCD_H

#include <stdint.h>


extern uint8_t LCD_ADDR;


#define LCD_RS          0x01
#define LCD_RW          0x02
#define LCD_EN          0x04
#define LCD_BACKLIGHT   0x08

void LCD_INIT(void);
void lcd_send_command(uint8_t cmd);
void lcd_send_char(uint8_t data);
void lcd_send_string(const char *str);
void lcd_set_cursor(uint8_t row, uint8_t col);
 void delay_ms(uint32_t ms);


#endif