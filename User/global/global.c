#include "stm32f4xx.h"
#include "./global/global.h"
#include "./GPS/GPS.h"
#include "./pwm_control/pwm_control.h"
uint8_t NUMBER[16];
uint8_t Output_String[100]="";
uint8_t Output_GPS_String[100]="";
uint32_t received=0;
uint8_t receive_Buff[90];
uint8_t receive_Buff_Point=0;
uint32_t testresult=0;
GPS_info GPS_Data;
DISPLAY_info DISPLAY_Data;
uint8_t onOff;
uint8_t Every1000count,Every100count,Every10count,Every1count;
uint32_t speed1 =0;
float speed2 =0;
float SPEED_FL=0;
float SPEED_FR=0;
float SPEED_BL=0;
float SPEED_BR=0;
float LastErr_Fl=0;
uint16_t pwm_up=1;
void clear_output_string(void)
{
	Output_String[0]='\0';
}
void clear_output_GPS_string(void)
{
	Output_GPS_String[0]='\0';
}
void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}
void GlobalInitialization(void)
{
	Every1000count=0;
	Every100count=0;
	Every10count=0;
	Every1count=0;
}
void Every1000s(void)
{

		Every1000count++;
	  if(Every1000count>=10)
		{
			Every100s();
			Every1000count=0;
			
		}
}
void Every100s(void)
{
		Every100count++;
	  if(Every100count>=10)
		{
			Every10s();
			Every100count=0;
		}
		//speed2=((float)speed1)/1.10;
		//PIDControl(&PWM_FL,speed2,SPEED_FL,&LastErr_Fl);
		//speed1=(TIM3->CR1>>4 & 0x01);
		speed1=TIM3->CNT;
}
void Every10s(void)
{
		RefreshDisplay();
		
		onOff=1-onOff;
		//上面是主要要做的事 下面是循环体
		Every10count++;
	  if(Every10count>=10)
		{
			Every1s();
			Every10count=0;
		}
}
void Every1s(void)
{		
		Every1count++;
	  if(Every1count>=10)
		{
			Every1count=0;
		}
		
}