/**
  ******************************************************************************
  * @file    FMC_SDRAM/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    11-November-2013
  * @brief   Main Interrupt Service Routines.
  *         This file provides template for all exceptions handler and
  *         peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "./Interrupt_Service/stm32f4xx_it.h"
#include "./EXTI_Conf/EXTI_Conf.h"
#include "./TIM_Conf/TIM_Conf.h"
#include "./NVIC_Conf/NVIC_Conf.h"
#include "./pwm_control/pwm_control.h"
#include "./usart/DGPS_Usart_Conf.h"
#include "./touch/bsp_i2c_touch.h"
#include "./global/global.h"
#include "./GPS/GPS.h"
#include "./touch/display_status.h"
/** @addtogroup STM32F429I_DISCOVERY_Examples
  * @{
  */

/** @addtogroup FMC_SDRAM
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
	}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f429_439xx.s).                         */
/******************************************************************************/

	/**
  * @brief  This function handles Key Pressing interrupt request.
  * @param  None
  * @retval None
  */
/*
void KEY1_IRQHandler(void)
{
		//确保是否产生了EXTI Line 中断 Line 0
		if (EXTI_GetITStatus(KEY1_INT_EXTI_LINE) != RESET) {
			decrease_pwm_100(PWM_FL);
		//清除中断标志位
		EXTI_ClearITPendingBit(KEY1_INT_EXTI_LINE);
		}
}

void KEY2_IRQHandler(void)
{
		//确保是否产生了EXTI Line 中断 Line 13
		if (EXTI_GetITStatus(KEY2_INT_EXTI_LINE) != RESET) {
			increase_pwm_100(PWM_FL);
		//清除中断标志位
		EXTI_ClearITPendingBit(KEY2_INT_EXTI_LINE);
		}
}
*/

	/**
  * @brief  This function handles TIM interrupt request.
  * @param  None
  * @retval None
  */
void GTP_IRQHandler(void)
{
	if(EXTI_GetITStatus(GTP_INT_EXTI_LINE) != RESET) //确保是否产生了EXTI Line中断
	{
    GTP_TouchProcess();    
		EXTI_ClearITPendingBit(GTP_INT_EXTI_LINE);     //清除中断标志位
	}  
}
void OUTPUT123_TIM_IRQHandler(void)
{
	if (TIM_GetITStatus(OUTPUT123_TIM, TIM_IT_Update) != RESET)//检测中断标志是否已发生
	{
		TIM_ClearITPendingBit (OUTPUT123_TIM, TIM_IT_Update);//清除中断标志 标识为未发生
	}
}
void DGPS_USART_IRQHandler(void)
{
	if (USART_GetITStatus(DGPS_USART,USART_IT_RXNE)!=RESET) {
		GPS_USART_Receive_Bytes();
		USART_ClearITPendingBit (DGPS_USART, USART_IT_RXNE);//清除中断标志 标识为未发生
	}
}
void BASIC_TIM_IRQHandler (void)//0.001S 计时器
{
	if ( TIM_GetITStatus( BASIC_TIM, TIM_IT_Update) != RESET ) {
	Every1000s();
	TIM_ClearITPendingBit(BASIC_TIM , TIM_IT_Update);
	}
}
/*void TIM3_IRQHandler (void)
{
	static uint16_t IC1Value,IC2Value;
	static float DutyCycle,Frequency;
	// 清除定时器捕获/比较1 中断 
	TIM_ClearITPendingBit(TIM3,TIM_IT_CC1);
	
	// 获取输入捕获值 
	IC1Value = TIM_GetCapture1(TIM3);
	//IC2Value = TIM_GetCapture2(ADVANCE_TIM);
	//IC1Value=TIM3->CNT;
	//printf("IC1Value = %d IC2Value = %d ",IC1Value,IC2Value);

	if (IC1Value != 0) {
	// 占空比计算 
	DutyCycle = (float)(IC2Value * 100) / IC1Value;

	// 频率计算 
	Frequency = (int)(180000000/(float)IC1Value);
		speed1=IC1Value;
		//speed1=1000;
	//printf("占空比：%0.2f%% 频率：%0.2fHz\n",DutyCycle,Frequency);
	} else {
	DutyCycle = 0;
	Frequency = 0;
		speed1=10000;
	}
	speed2=speed2+1;
}*/
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
    {       
        if((TIM3->CR1>>4 & 0x01)==0) //DIR==0
				 speed1++;
        else if((TIM3->CR1>>4 & 0x01)==1)//DIR==1
				speed1--;
    }
		//speed1=TIM3->CNT - 0x7fff+1;
		//TIM3->CNT = 0x7fff;
		//speed2=TIM_GetCounter(TIM3);
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);     
}
/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
