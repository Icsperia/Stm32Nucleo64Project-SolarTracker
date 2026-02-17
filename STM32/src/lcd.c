#include "lcd.h"
#include "i2c.h"

void delay_us(uint32_t us){
   
    for(volatile int i=0;i<4000-us;i++); 
}

void delay_ms(uint32_t ms){
    for(uint32_t i=0;i<ms;i++){
       
        for(volatile int j=0;j<16000;j++); 
    }
}

static void lcd_send_nibble(uint8_t nibble, uint8_t control){
    
    uint8_t data = (nibble & 0xF0) | control | LCD_BACKLIGHT;
    i2c_transfer(LCD_ADDR, data | LCD_EN); 
    delay_us(0);
    i2c_transfer(LCD_ADDR, data);          
    delay_us(0);
}

static void lcd_send_byte(uint8_t byte, uint8_t rs){
    uint8_t control = LCD_BACKLIGHT;
    if(rs) control |= LCD_RS;
    

    lcd_send_nibble(byte & 0xF0, control); 
    lcd_send_nibble((byte << 4) & 0xF0, control);
}

void lcd_send_command(uint8_t cmd){
    lcd_send_byte(cmd, 0);
}

void lcd_send_char(uint8_t data){
    lcd_send_byte(data, 1);
}

void lcd_send_string(const char *str){
    while(*str){
        lcd_send_char(*str++);
    }
}

void lcd_set_cursor(uint8_t row, uint8_t col){
    uint8_t addr;
    switch(row){
        case 0: addr = 0x00 + col; break;
        case 1: addr = 0x40 + col; break;
        case 2: addr = 0x14 + col; break; 
        case 3: addr = 0x54 + col; break;
        default: addr = 0x00 + col;
    }
    lcd_send_command(0x80 | addr);
}

void LCD_INIT(void){
   
    delay_ms(50);
    lcd_send_nibble(0x30, 0); delay_ms(20); 
    lcd_send_nibble(0x30, 0); delay_ms(1);  
    lcd_send_nibble(0x30, 0); delay_ms(1);  
    
    lcd_send_nibble(0x20, 0);            
    

    lcd_send_command(0x28); 
    lcd_send_command(0x0C); 
    lcd_send_command(0x06); 
    lcd_send_command(0x01); 
    delay_ms(2);
}