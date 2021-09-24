#ifndef __BSP_IIC_HMC5883L_H
#define	__BSP_IIC_HMC5883L_H

#include "stm32f4xx.h"
#include <stdio.h>


//Òý½Å¶¨Òå
/*******************************************************/

#define STM32_IIC_OWN_ADDR                      0x78
#define STM32_IIC_HMC5883L_ADDR                 0x3C

#define HMC5883L_IIC                              I2C1
#define HMC5883L_IIC_CLK                          RCC_APB1Periph_I2C1
#define HMC5883L_IIC_BAUDRATE                     400000  

#define HMC5883L_IIC_SCL_GPIO_PORT                GPIOB
#define HMC5883L_IIC_SCL_GPIO_CLK                 RCC_AHB1Periph_GPIOB
#define HMC5883L_IIC_SCL_PIN                      GPIO_Pin_8
#define HMC5883L_IIC_SCL_AF                       GPIO_AF_I2C1
#define HMC5883L_IIC_SCL_SOURCE                   GPIO_PinSource8

#define HMC5883L_IIC_SDA_GPIO_PORT                GPIOB
#define HMC5883L_IIC_SDA_GPIO_CLK                 RCC_AHB1Periph_GPIOB
#define HMC5883L_IIC_SDA_PIN                      GPIO_Pin_9
#define HMC5883L_IIC_SDA_AF                       GPIO_AF_I2C1
#define HMC5883L_IIC_SDA_SOURCE                   GPIO_PinSource9

/************************************************************/

void HMC5883L_IIC_Config(void);
void NVIC_Configuration(void);
void WWDG_Configuration(void);
void WWDG_IRQHandler(void);
void Init_HMC5883L(void);
void Send_HMC5883L(void);
void read_HMC5883L(void);
#endif 
