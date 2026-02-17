#include "stm32g070xx.h"
#include "usart.h"
#include "i2c.h"
#include "lcd.h"
#include "ina_read.h"
#include <stdio.h>

uint8_t LCD_ADDR = 0x27;
uint8_t INA219_ADDR = 0x40;


int16_t threshold= 30;


int main(void)
{
    I2C_INIT();

    LCD_INIT();

    USART_INIT();
    ADC1_INIT();

    STEPPER_INIT1();
    STEPPER_INIT2();

    uint16_t ch0 = 0, ch1 = 0, ch4 = 0, ch9 = 0;
    char line0[100];
    char line1[100];
    char line2[100];
    char line3[100];
    char uart_line[80];
    float bus_V;
    float shunt_mV;

 u_int32_t loop_counter = 0;
    while (1)
    {

 

        bus_V = ina_read_bus_voltage(INA219_ADDR);
        shunt_mV = ina_read_shunt_voltage(INA219_ADDR);
         ADC1_READ(&ch0);
         ADC1_READ1(&ch1);
         ADC1_READ4(&ch4);
        ADC1_READ9(&ch9);
        uint16_t light_sensor_1 = ch0;
        uint16_t light_sensor_2 = ch1;
        uint16_t light_sensor_3 = ch4;
        uint16_t light_sensor_4 = ch9;
        
      

int16_t left   = (int16_t)(light_sensor_1 + light_sensor_3) / 2;  
int16_t right  = (int16_t)(light_sensor_2 + light_sensor_4) / 2;  
int16_t top    = (int16_t)(light_sensor_1 + light_sensor_2) / 2;  
int16_t bottom = (int16_t)(light_sensor_3 + light_sensor_4) / 2;  

int16_t diffH = right - left;
int16_t diffV = top - bottom;
if (diffV > threshold) {
    stepper_time1(1000);              
} else if (diffV < -threshold) {
    stepper_reverse_time1(1000);     
}

if (diffH > threshold) {
    stepper_time2(1000);             
} else if (diffH < -threshold) {
    stepper_reverse_time2(1000);     
}


 loop_counter++;
    if (loop_counter >= 10) { 
        sprintf(line0, "DV:%-4d DH:%-4d", diffH, diffV);
        sprintf(line1, "V_Bus: %.2fV  ", (double)bus_V);
        
        USART_TRANS(line0);
         USART_TRANS(line1);
        lcd_set_cursor(0, 0);
        lcd_send_string(line0);
        
        lcd_set_cursor(1, 0);
        lcd_send_string(line1);

        loop_counter = 0; 
        delay_ms(50);
    }

}
}