#ifndef pwm_control_H
#define pwm_control_H
#include "stm32f4xx.h"
#include "./TIM_Conf/TIM_Conf.h"
void increase_pwm_100(__IO uint32_t* Channel);
void decrease_pwm_100(__IO uint32_t* Channel);
void increase_pwm_1000(__IO uint32_t* Channel);
void decrease_pwm_1000(__IO uint32_t* Channel);
void increase_speed_100 (float* SpeedCH);
void decrease_speed_100 (float* SpeedCH);
void PIDControl(__IO uint32_t* Channel,float CurSpeed, float TarSpeed, float* LastErr);
#endif
