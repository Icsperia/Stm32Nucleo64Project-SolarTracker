
#include "i2c.h"     
#include "stm32g070xx.h"
#include "servo.h"
#define PCA9685_ADDR     0x40   
#define REG_MODE1        0x00
#define REG_PRESCALE     0xFE
#define REG_LED0_ON_L    0x06

static void PCA9685_Write8(uint8_t reg, uint8_t val)
{
    uint8_t buf[2];
    buf[0] = reg;
    buf[1] = val;
    i2c_write(PCA9685_ADDR, buf, 2);
}

static void PCA9685_WriteBytes(uint8_t reg, uint8_t *data, uint8_t len)
{
    
    uint8_t buf[1 + 4]; 
    buf[0] = reg;
    for (uint8_t i = 0; i < len; i++)
        buf[1 + i] = data[i];

    i2c_write(PCA9685_ADDR, buf, 1 + len);
}

void PCA9685_Init(void)
{

  
    I2C_INIT();


    PCA9685_Write8(REG_MODE1, 0x10);   

    PCA9685_Write8(REG_PRESCALE, 121);


    PCA9685_Write8(REG_MODE1, 0xA1);  
}


void PCA9685_SetPWM(uint8_t channel, uint16_t on, uint16_t off)
{
    uint8_t reg = REG_LED0_ON_L + 4 * channel;
    uint8_t data[4];

    data[0] = on & 0xFF;
    data[1] = (on >> 8) & 0x0F;
    data[2] = off & 0xFF;
    data[3] = (off >> 8) & 0x0F;

    PCA9685_WriteBytes(reg, data, 4);
}


void PCA9685_SetServoAngle(uint8_t channel, uint8_t angle)
{
    if (angle > 180) angle = 180;   

    float min_ticks = 205.0f;  
    float max_ticks = 410.0f; 

    float ratio = angle / 180.0f;
    uint16_t ticks = (uint16_t)(min_ticks + (max_ticks - min_ticks) * ratio);

    PCA9685_SetPWM(channel, 0, ticks);
}
