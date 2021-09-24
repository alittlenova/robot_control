#ifndef GPIO_H
#define GPIO_H
#include "stm32f4xx.h"
//PWM1通道定义
#define OUTPUT_CONTROL_GPIO1_PIN GPIO_Pin_10//引脚定义
#define OUTPUT_CONTROL_GPIO1_CLK RCC_AHB1Periph_GPIOH//引脚控制器打开 时钟接入定义

#define OUTPUT_CONTROL_GPIO1_PORT GPIOH//复用引脚接口引脚集控制器定义
#define OUTPUT_CONTROL_GPIO1_PINSOURCE GPIO_PinSource10//复用引脚角标号定义
#define OUTPUT_CONTROL_GPIO1_AF GPIO_AF_TIM5//复用引脚接入点定义

//PWM2通道定义
#define OUTPUT_CONTROL_GPIO2_PIN GPIO_Pin_11//引脚定义
#define OUTPUT_CONTROL_GPIO2_CLK RCC_AHB1Periph_GPIOH//引脚控制器打开 时钟接入定义

#define OUTPUT_CONTROL_GPIO2_PORT GPIOH//复用引脚接口引脚集控制器定义
#define OUTPUT_CONTROL_GPIO2_PINSOURCE GPIO_PinSource11//复用引脚角标号定义
#define OUTPUT_CONTROL_GPIO2_AF GPIO_AF_TIM5//复用引脚接入点定义

//PWM3通道定义
#define OUTPUT_CONTROL_GPIO3_PIN GPIO_Pin_12//引脚定义
#define OUTPUT_CONTROL_GPIO3_CLK RCC_AHB1Periph_GPIOH//引脚控制器打开 时钟接入定义

#define OUTPUT_CONTROL_GPIO3_PORT GPIOH//复用引脚接口引脚集控制器定义
#define OUTPUT_CONTROL_GPIO3_PINSOURCE GPIO_PinSource12//复用引脚角标号定义
#define OUTPUT_CONTROL_GPIO3_AF GPIO_AF_TIM5//复用引脚接入点定义

//Encoder1通道定义
#define inPUT_CONTROL_GPIO1_PIN GPIO_Pin_6//引脚定义
#define inPUT_CONTROL_GPIO1_CLK RCC_AHB1Periph_GPIOA//引脚控制器打开 时钟接入定义

#define inPUT_CONTROL_GPIO1_PORT GPIOA//复用引脚接口引脚集控制器定义
#define inPUT_CONTROL_GPIO1_PINSOURCE GPIO_PinSource6//复用引脚角标号定义
#define inPUT_CONTROL_GPIO1_AF GPIO_AF_TIM3//复用引脚接入点定义

//广电输入脚1定义

/* PWM 输入捕获引脚 */
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
