#ifndef TIM_H
#define TIM_H
#include "stm32f4xx.h"
#define OUTPUT123_TIM TIM5 //PWM定时器定义
#define OUTPUT123_TIM_CLK RCC_APB1Periph_TIM5 //PWM定时器时钟接入定义

#define BASIC_TIM TIM6  //0.1S定时器定义
#define BASIC_TIM_CLK RCC_APB1Periph_TIM6//0.1s定时器时钟接入定义

/* 高级控制定时器 */
#define ADVANCE_TIM TIM3
#define ADVANCE_TIM_CLK RCC_APB1Periph_TIM3

#define ADVANCE_IC1PWM_CHANNEL TIM_Channel_1

void TIM_Config(void);
void TIM_BASIC_Config(void);
void TIM_PWMINPUT_Config(void);
//void Encoder_Init_TIM3(void);
#endif
