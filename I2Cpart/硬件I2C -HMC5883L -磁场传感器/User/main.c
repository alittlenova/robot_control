/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ���ڽӷ����ԣ����ڽ��յ����ݺ����ϻش���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F407 ������
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"
#include "./iic/bsp_iic_HMC5883L.h"

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
	
int main(void)
{	
	Debug_USART_Config();
	HMC5883L_IIC_Config();
	Init_HMC5883L();	
	read_HMC5883L();
	Send_HMC5883L();	
  while(1)
{ 
 
	}	
}



/*********************************************END OF FILE**********************/

