#ifndef __DGPS_USART_H
#define	__DGPS_USART_H

#include "stm32f4xx.h"
#include <stdio.h>


#define DGPS_USART                             USART3
#define DGPS_USART_CLK                         RCC_APB1Periph_USART3
#define DGPS_USART_BAUDRATE                    9600

#define DGPS_USART_RX_GPIO_PORT                GPIOB
#define DGPS_USART_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOB
#define DGPS_USART_RX_PIN                      GPIO_Pin_11
#define DGPS_USART_RX_AF                       GPIO_AF_USART3
#define DGPS_USART_RX_SOURCE                   GPIO_PinSource11

#define DGPS_USART_TX_GPIO_PORT                GPIOB
#define DGPS_USART_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOB
#define DGPS_USART_TX_PIN                      GPIO_Pin_10
#define DGPS_USART_TX_AF                       GPIO_AF_USART3
#define DGPS_USART_TX_SOURCE                   GPIO_PinSource10




void DGPS_USART_Config(void);





#endif 