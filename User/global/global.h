#ifndef _global_h_
#define _global_h_
#include "stm32f4xx.h"
#include "./GPS/GPS.h"
#include "./touch/display_status.h"
#define PWM_FL OUTPUT123_TIM->CCR1
#define PWM_FR OUTPUT123_TIM->CCR2
#define PWM_BL OUTPUT123_TIM->CCR3
//�Զ���ȫ�ֱ�����
//�ַ�������ռ�ITOA
extern uint8_t NUMBER[16];
//�����ñ���
extern uint32_t received;
extern uint8_t receive_Buff[90];
extern uint8_t receive_Buff_Point;
extern uint32_t testresult;
extern uint8_t onOff;
//GPS���ݿ�
extern GPS_info GPS_Data;
//ȫ����ʾ״̬
extern DISPLAY_info DISPLAY_Data;
//�ַ���ƴ�Ӵ���ռ�
extern uint8_t Output_String[100];
extern uint8_t Output_GPS_String[100];
//���ת�ٱ�����
extern float SPEED_FL;
extern float SPEED_FR;
extern float SPEED_BL;
extern float SPEED_BR;
extern float LastErr_Fl;
//����
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
