#include "./pwm_control/pwm_control.h"
void increase_pwm_100(__IO uint32_t* Channel)
{
			if((*Channel)<100)
			{
				(*Channel)++;
			}
}
void decrease_pwm_100(__IO uint32_t* Channel)
{
			if((*Channel)>0)
			{
				(*Channel)--;
			}
}
void increase_pwm_1000(__IO uint32_t* Channel)
{
			if((*Channel)<1000)
			{
				(*Channel)=(*Channel)+10;
			}
}
void decrease_pwm_1000(__IO uint32_t* Channel)
{
			if((*Channel)>0)
			{
				(*Channel)=(*Channel)-10;
			}
}
void increase_speed_100(float* SpeedCH)
{
			if(*SpeedCH<100)
			{
				*SpeedCH=50;
				//*SpeedCH=*SpeedCH+1;
			}
}
void decrease_speed_100(float* SpeedCH)
{
			if(*SpeedCH>0)
			{
				*SpeedCH=20;
				//*SpeedCH=*SpeedCH-1;
			}
}
void PIDControl(__IO uint32_t* Channel,float CurSpeed, float TarSpeed, float* LastErr)// (0-100) Range
{
	static float outpt,outpt1;
	static int output,output2,output3;
	outpt=(TarSpeed-CurSpeed);
	//outpt1=outpt*0.5;
	//output=(int)outpt1;
	//output2=(*Channel);
	if(*Channel+output>=100)
	{
		*Channel=100;
	}
	else if(*Channel+output <= 0)
	{
		*Channel=0;
	}
	else
	{
		//output3=output2+output;
		//*Channel=output3;
	}
	
	//*LastErr=outpt;
	*LastErr=CurSpeed;
}