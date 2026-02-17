#include "i2c.h"
#include "stm32g070xx.h"
#include "usart.h"

void I2C_INIT(void){
    RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
    RCC->APBENR1 |= RCC_APBENR1_I2C1EN;

  
    GPIOB->MODER &= ~((3<<16)|(3<<18));
    GPIOB->MODER |= ((2<<16)|(2<<18));
    GPIOB->OTYPER |= ((1<<8)|(1<<9)); 
    GPIOB->PUPDR &= ~((3<<16)|(3<<18));
    GPIOB->PUPDR |= ((1<<16)|(1<<18));
    GPIOB->AFR[1] &= ~((0xF<<0)|(0xF<<4));
    GPIOB->AFR[1] |= ((6<<0)|(6<<4));

    I2C1->CR1 &= ~I2C_CR1_PE;
    I2C1->TIMINGR=0x00300F38;
    I2C1->CR1 |= I2C_CR1_PE;
}

void i2c_transfer(uint8_t slave_addr, uint8_t data){
    I2C1->CR2 = 0;
    I2C1->CR2 |= (slave_addr<<1) | (1<<16);
    I2C1->CR2 &= ~I2C_CR2_RD_WRN;
    I2C1->CR2 |= I2C_CR2_START;

    uint32_t timeout = 10000;
    while (!(I2C1->ISR & I2C_ISR_TXIS) && timeout--);
    if(timeout == 0) return;

    I2C1->TXDR = data;

    timeout = 10000;
    while (!(I2C1->ISR & I2C_ISR_STOPF) && timeout--);
    I2C1->ICR |= I2C_ICR_STOPCF;
}

static inline int i2c_check_errors(void)
{
    uint32_t isr = I2C1->ISR;

    if (isr & I2C_ISR_NACKF) { I2C1->ICR = I2C_ICR_NACKCF; return -1; }
    if (isr & I2C_ISR_BERR)  { I2C1->ICR = I2C_ICR_BERRCF;  return -2; }
    if (isr & I2C_ISR_ARLO)  { I2C1->ICR = I2C_ICR_ARLOCF;  return -3; }
    if (isr & I2C_ISR_OVR)   { I2C1->ICR = I2C_ICR_OVRCF;   return -4; }

    return 0;
}

int i2c_write(uint8_t slave_addr, uint8_t *buf, uint8_t len)
{
    if (len == 0) return 0;


    I2C1->CR2 = 0;

    I2C1->CR2 |= (slave_addr << 1);         
    I2C1->CR2 |= ((uint32_t)len << 16);      
    I2C1->CR2 &= ~I2C_CR2_RD_WRN;       
    I2C1->CR2 |= I2C_CR2_AUTOEND; 
    I2C1->CR2 |= I2C_CR2_START;              

    for (uint8_t i = 0; i < len; i++)
    {
        uint32_t timeout = 100000;
        while (!(I2C1->ISR & I2C_ISR_TXIS) && timeout--)
            ;


        I2C1->TXDR = buf[i];
    }


    uint32_t timeout = 100000;
    while (!(I2C1->ISR & I2C_ISR_STOPF) && timeout--)
        ;
    I2C1->ICR |= I2C_ICR_STOPCF;
        return 0;
}

int i2c_read(uint8_t slave_addr, uint8_t *buf, uint8_t len)
{
    if (len == 0) return 0;

    I2C1->CR2 = 0;
    I2C1->CR2 |= (slave_addr << 1);
    I2C1->CR2 |= ((uint32_t)len << 16);
    I2C1->CR2 |= I2C_CR2_RD_WRN;
    I2C1->CR2 |= I2C_CR2_AUTOEND;
    I2C1->CR2 |= I2C_CR2_START;

    for (uint8_t i = 0; i < len; i++)
    {
        uint32_t timeout = 100000;
        while (!(I2C1->ISR & I2C_ISR_RXNE) && timeout--)
        {
            int e = i2c_check_errors();
            if (e) return e;
        }
        if (timeout == 0) return -20;

        buf[i] = (uint8_t)I2C1->RXDR;
    }

    uint32_t timeout = 100000;
    while (!(I2C1->ISR & I2C_ISR_STOPF) && timeout--)
    {
        int e = i2c_check_errors();
        if (e) return e;
    }
    if (timeout == 0) return -21;

    I2C1->ICR = I2C_ICR_STOPCF;
    return 0;
}



// void i2c_read(uint8_t slave_addr, uint8_t *buf, uint8_t reg)
// {
 

//     // reset CR2
//     I2C1->CR2 = 0;

//     // 7-bit address in SADD[7:1] (shiftat cu 1) + NBYTES
//     I2C1->CR2 |= (slave_addr << 1);          // SADD
//     I2C1->CR2 |= (2u << 16);      // NBYTES = len
//     I2C1->CR2 |= I2C_CR2_RD_WRN;            // read
//     I2C1->CR2 |= I2C_CR2_AUTOEND; 
//     I2C1->CR2 |= I2C_CR2_START;              // pornește transferul


//     uint8_t msb, lsb;

    
//         uint32_t timeout = 100000;
//         while (!(I2C1->ISR & I2C_ISR_RXNE) && timeout--) ;
//      msb =  (uint8_t)I2C1->RXDR; 
    


 
//         uint32_t timeout = 100000;
//         while (!(I2C1->ISR & I2C_ISR_RXNE) && timeout--) ;


   
//      lsb =  (uint8_t)I2C1->RXDR; 
    

 
//         uint32_t timeout = 100000;
//         while (!(I2C1->ISR & I2C_ISR_RXNE) && timeout--) ;


//   I2C1->ICR =  I2C_ICR_STOPCF; 


    

//         uint32_t timeout = 100000;
//         while (!(I2C1->ISR & I2C_ISR_RXNE) && timeout--) ;


//       *buf = (uint16_t)((msb<<8)|lsb); 
    



// }
