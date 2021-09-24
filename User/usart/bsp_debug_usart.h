#ifndef __DEBUG_USART_H
#define	__DEBUG_USART_H

#include "stm32f4xx.h"
#include <stdio.h>


#define DEBUG_USART                             USART1
#define DEBUG_USART_CLK                         RCC_APB2Periph_USART1
#define DEBUG_USART_BAUDRATE                    115200

#define DEBUG_USART_RX_GPIO_PORT                GPIOA
#define DEBUG_USART_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define DEBUG_USART_RX_PIN                      GPIO_Pin_10
#define DEBUG_USART_RX_AF                       GPIO_AF_USART1
#define DEBUG_USART_RX_SOURCE                   GPIO_PinSource10

#define DEBUG_USART_TX_GPIO_PORT                GPIOA
#define DEBUG_USART_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define DEBUG_USART_TX_PIN                      GPIO_Pin_9
#define DEBUG_USART_TX_AF                       GPIO_AF_USART1
#define DEBUG_USART_TX_SOURCE                   GPIO_PinSource9



//#define __DEBUG 	//开启串口调试
/*
#ifdef  __DEBUG
#define DEBUG(format,...)	printf("File:"__FILE__",Line:%03d:"format"\n",__LINE__,##__VA_ARGS__) 
#else

#define DEBUG(format,...)

#endif
*/

void Debug_USART_Config(void);





#endif // __USART1_H 

/*
#ifndef __DEBUG_USART_H
#define	__DEBUG_USART_H

#include "stm32f4xx.h"
#include <stdio.h>


//引脚定义

#define DEBUG_USART                             USART2
#define DEBUG_USART_CLK                         RCC_APB1Periph_USART2
//#define USARTx_CLOCKCMD                    RCC_APB1PeriphClockCmd
#define DEBUG_USART_BAUDRATE                    115200  //串口波特率

#define DEBUG_USART_RX_GPIO_PORT                GPIOD
#define DEBUG_USART_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOD
#define DEBUG_USART_RX_PIN                      GPIO_Pin_6
#define DEBUG_USART_RX_AF                       GPIO_AF_USART2
#define DEBUG_USART_RX_SOURCE                   GPIO_PinSource6

#define DEBUG_USART_TX_GPIO_PORT                GPIOD
#define DEBUG_USART_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOD
#define DEBUG_USART_TX_PIN                      GPIO_Pin_5
#define DEBUG_USART_TX_AF                       GPIO_AF_USART2
#define DEBUG_USART_TX_SOURCE                   GPIO_PinSource5



#define __DEBUG 	//开启串口调试

#ifdef  __DEBUG
#define DEBUG(format,...)	printf("File:"__FILE__",Line:%03d:"format"\n",__LINE__,##__VA_ARGS__) 
#else

#define DEBUG(format,...)

#endif
void Debug_USART_Config(void);

#endif // __USART_H 
*/