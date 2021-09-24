#ifndef GPIO_H
#define GPIO_H
#include "stm32f4xx.h"
//PWM1ͨ������
#define OUTPUT_CONTROL_GPIO1_PIN GPIO_Pin_10//���Ŷ���
#define OUTPUT_CONTROL_GPIO1_CLK RCC_AHB1Periph_GPIOH//���ſ������� ʱ�ӽ��붨��

#define OUTPUT_CONTROL_GPIO1_PORT GPIOH//�������Žӿ����ż�����������
#define OUTPUT_CONTROL_GPIO1_PINSOURCE GPIO_PinSource10//�������ŽǱ�Ŷ���
#define OUTPUT_CONTROL_GPIO1_AF GPIO_AF_TIM5//�������Ž���㶨��

//PWM2ͨ������
#define OUTPUT_CONTROL_GPIO2_PIN GPIO_Pin_11//���Ŷ���
#define OUTPUT_CONTROL_GPIO2_CLK RCC_AHB1Periph_GPIOH//���ſ������� ʱ�ӽ��붨��

#define OUTPUT_CONTROL_GPIO2_PORT GPIOH//�������Žӿ����ż�����������
#define OUTPUT_CONTROL_GPIO2_PINSOURCE GPIO_PinSource11//�������ŽǱ�Ŷ���
#define OUTPUT_CONTROL_GPIO2_AF GPIO_AF_TIM5//�������Ž���㶨��

//PWM3ͨ������
#define OUTPUT_CONTROL_GPIO3_PIN GPIO_Pin_12//���Ŷ���
#define OUTPUT_CONTROL_GPIO3_CLK RCC_AHB1Periph_GPIOH//���ſ������� ʱ�ӽ��붨��

#define OUTPUT_CONTROL_GPIO3_PORT GPIOH//�������Žӿ����ż�����������
#define OUTPUT_CONTROL_GPIO3_PINSOURCE GPIO_PinSource12//�������ŽǱ�Ŷ���
#define OUTPUT_CONTROL_GPIO3_AF GPIO_AF_TIM5//�������Ž���㶨��

//Encoder1ͨ������
#define inPUT_CONTROL_GPIO1_PIN GPIO_Pin_6//���Ŷ���
#define inPUT_CONTROL_GPIO1_CLK RCC_AHB1Periph_GPIOA//���ſ������� ʱ�ӽ��붨��

#define inPUT_CONTROL_GPIO1_PORT GPIOA//�������Žӿ����ż�����������
#define inPUT_CONTROL_GPIO1_PINSOURCE GPIO_PinSource6//�������ŽǱ�Ŷ���
#define inPUT_CONTROL_GPIO1_AF GPIO_AF_TIM3//�������Ž���㶨��

//��������1����

/* PWM ���벶������ */
#define ADVANCE_ICPWM_PIN GPIO_Pin_6
#define ADVANCE_ICPWM_GPIO_PORT GPIOA
#define ADVANCE_ICPWM_GPIO_CLK RCC_AHB1Periph_GPIOA
#define ADVANCE_ICPWM_PINSOURCE GPIO_PinSource6
#define ADVANCE_ICPWM_AF GPIO_AF_TIM3
#define ADVANCE_IC1PWM_CHANNEL TIM_Channel_1
#define ADVANCE_IC2PWM_CHANNEL TIM_Channel_2


void PWM_GPIO_Config(void);
void I2C_GTP_GPIO_Config(void);
#endif
