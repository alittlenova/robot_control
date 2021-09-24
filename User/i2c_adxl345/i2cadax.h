#ifndef __BSP_IIC_ADXL345_H
#define	__BSP_IIC_ADXL345_H

#include "stm32f4xx.h"
#include <stdio.h>


//Òý½Å¶¨Òå
/*******************************************************/

#define STM32_IIC_OWN_ADDR                      0x78
#define STM32_IIC_ADXL345_ADDR                  0xA6

#define ADXL345_IIC                              I2C1
#define ADXL345_IIC_CLK                          RCC_APB1Periph_I2C1
#define ADXL345_IIC_BAUDRATE                     400000  

#define ADXL345_IIC_SCL_GPIO_PORT                GPIOB
#define ADXL345_IIC_SCL_GPIO_CLK                 RCC_AHB1Periph_GPIOB
#define ADXL345_IIC_SCL_PIN                      GPIO_Pin_6
#define ADXL345_IIC_SCL_AF                       GPIO_AF_I2C1
#define ADXL345_IIC_SCL_SOURCE                   GPIO_PinSource6

#define ADXL345_IIC_SDA_GPIO_PORT                GPIOB
#define ADXL345_IIC_SDA_GPIO_CLK                 RCC_AHB1Periph_GPIOB
#define ADXL345_IIC_SDA_PIN                      GPIO_Pin_7
#define ADXL345_IIC_SDA_AF                       GPIO_AF_I2C1
#define ADXL345_IIC_SDA_SOURCE                   GPIO_PinSource7

/************************************************************/
//extern uint8_t ge,shi,bai,qian,wan,shiwan; 
extern uint32_t A_Xout,A_Yout,A_Zout;
extern uint32_t A_X,A_Y,A_Z;
void ADXL345_IIC_Config(void);
void NVIC_Configuration(void);
void WWDG_Configuration(void);
void WWDG_IRQHandler(void);
void Init_ADXL345(void);
void ADXL_generate_data(void);
//void Send_ADXL345(void);
void read_ADXL345(void);
#endif 