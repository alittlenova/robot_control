#ifndef TIM_H
#define TIM_H
#include "stm32f4xx.h"
#define OUTPUT123_TIM TIM5 //PWM��ʱ������
#define OUTPUT123_TIM_CLK RCC_APB1Periph_TIM5 //PWM��ʱ��ʱ�ӽ��붨��

#define BASIC_TIM TIM6  //0.1S��ʱ������
#define BASIC_TIM_CLK RCC_APB1Periph_TIM6//0.1s��ʱ��ʱ�ӽ��붨��

/* �߼����ƶ�ʱ�� */
#define ADVANCE_TIM TIM3
#define ADVANCE_TIM_CLK RCC_APB1Periph_TIM3

#define ADVANCE_IC1PWM_CHANNEL TIM_Channel_1

void TIM_Config(void);
void TIM_BASIC_Config(void);
void TIM_PWMINPUT_Config(void);
//void Encoder_Init_TIM3(void);
#endif
