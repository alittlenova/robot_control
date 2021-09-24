/**
  ******************************************************************************
  * @file    DGPS_usart.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   �ض���c��printf������usart�˿�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F429 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "./usart/DGPS_Usart_Conf.h"

 /**
  * @brief  DGPS_USART GPIO ����,����ģʽ���á�9600 8-N-1
  * @param  ��
  * @retval ��
  */
void DGPS_USART_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
		
  RCC_AHB1PeriphClockCmd( DGPS_USART_RX_GPIO_CLK|DGPS_USART_TX_GPIO_CLK, ENABLE);

  /* ʹ�� UART ʱ�� */
  RCC_APB1PeriphClockCmd(DGPS_USART_CLK, ENABLE);
  
  /* ���� PXx �� USARTx_Tx*/
  GPIO_PinAFConfig(DGPS_USART_RX_GPIO_PORT,DGPS_USART_RX_SOURCE, DGPS_USART_RX_AF);

  /*  ���� PXx �� USARTx__Rx*/
  GPIO_PinAFConfig(DGPS_USART_TX_GPIO_PORT,DGPS_USART_TX_SOURCE,DGPS_USART_TX_AF);

  /* ����Tx����Ϊ���ù���  */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = DGPS_USART_TX_PIN  ;
  GPIO_Init(DGPS_USART_TX_GPIO_PORT, &GPIO_InitStructure);

  /* ����Rx����Ϊ���ù��� */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = DGPS_USART_RX_PIN;
  GPIO_Init(DGPS_USART_RX_GPIO_PORT, &GPIO_InitStructure);
			
  /* ���ô�DGPS_USART ģʽ */
  USART_InitStructure.USART_BaudRate = DGPS_USART_BAUDRATE;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(DGPS_USART, &USART_InitStructure); 
	// ʹ�ܴ��ڽ����ж�
	USART_ITConfig(DGPS_USART, USART_IT_RXNE, ENABLE);
  USART_Cmd(DGPS_USART, ENABLE);
}