#ifndef NVIC_H
#define NVIC_H
#include "stm32f4xx.h"
#define OUTPUT123_TIM_IRQn TIM5_IRQn
#define OUTPUT123_TIM_IRQHandler TIM5_IRQHandler
#define KEY1_INT_EXTI_IRQ EXTI0_IRQn
#define KEY1_IRQHandler EXTI0_IRQHandler
#define KEY2_INT_EXTI_IRQ EXTI15_10_IRQn
#define KEY2_IRQHandler EXTI15_10_IRQHandler
#define DEBUG_USART_IRQHandler USART1_IRQHandler
#define DEBUG_USART_IRQ USART1_IRQn
#define DGPS_USART_IRQHandler USART3_IRQHandler
#define DGPS_USART_IRQ USART3_IRQn
#define BASIC_TIM_IRQn TIM6_DAC_IRQn
#define BASIC_TIM_IRQHandler TIM6_DAC_IRQHandler
/* 捕获/比较中断 */
#define ADVANCE_TIM_IRQn TIM3_IRQn
#define ADVANCE_TIM_IRQHandler TIM3_IRQHandler
void TIM_BASIC_NVIC_Configuration(void);
void TIM_NVIC_Config(void);
void TIMx_NVIC_Configuration(void);
void EXTI_NVIC_Config(void);
void DGPS_NVIC_Configuration(void);
void DEBUG_NVIC_Configuration(void);
#endif
