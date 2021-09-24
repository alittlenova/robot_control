#ifndef _global_h_
#define _global_h_
#include "stm32f4xx.h"
#include "./GPS/GPS.h"
#include "./touch/display_status.h"
#define PWM_FL OUTPUT123_TIM->CCR1
#define PWM_FR OUTPUT123_TIM->CCR2
#define PWM_BL OUTPUT123_TIM->CCR3
//自定义全局变量表
//字符串处理空间ITOA
extern uint8_t NUMBER[16];
//测试用变量
extern uint32_t received;
extern uint8_t receive_Buff[90];
extern uint8_t receive_Buff_Point;
extern uint32_t testresult;
extern uint8_t onOff;
//GPS数据库
extern GPS_info GPS_Data;
//全局显示状态
extern DISPLAY_info DISPLAY_Data;
//字符串拼接处理空间
extern uint8_t Output_String[100];
extern uint8_t Output_GPS_String[100];
//电机转速变量表
extern float SPEED_FL;
extern float SPEED_FR;
extern float SPEED_BL;
extern float SPEED_BR;
extern float LastErr_Fl;
//脉宽
extern uint32_t speed1;
extern float speed2;
extern uint16_t pwm_up;
void clear_output_string(void);
void clear_output_GPS_string(void);
void Delay(__IO uint32_t nCount);
extern void GlobalInitialization(void);
extern void Every1000s(void);
extern void Every100s(void);
extern void Every10s(void);
extern void Every1s(void);
#endif
