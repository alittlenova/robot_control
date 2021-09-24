/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   串口接发测试，串口接收到数据后马上回传。
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F407 开发板
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"
#include "./iic/bsp_iic_ADXL345.h"

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
	
int main(void)
{	
	Debug_USART_Config();
	ADXL345_IIC_Config();
	Init_ADXL345();	
	read_ADXL345();
	Send_ADXL345();	
  while(1)
{ 
 
	}	
}



/*********************************************END OF FILE**********************/

