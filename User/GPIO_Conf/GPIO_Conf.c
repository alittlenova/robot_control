#include "./GPIO_Conf/GPIO_Conf.h"
void PWM_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//PWM_out_1�ӿ��������
	RCC_AHB1PeriphClockCmd ( OUTPUT_CONTROL_GPIO1_CLK, ENABLE);
	GPIO_PinAFConfig(OUTPUT_CONTROL_GPIO1_PORT,OUTPUT_CONTROL_GPIO1_PINSOURCE,OUTPUT_CONTROL_GPIO1_AF);
	GPIO_InitStructure.GPIO_Pin = OUTPUT_CONTROL_GPIO1_PIN;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(OUTPUT_CONTROL_GPIO1_PORT, &GPIO_InitStructure);
	
	//PWM_out_2�ӿ��������
	RCC_AHB1PeriphClockCmd ( OUTPUT_CONTROL_GPIO2_CLK, ENABLE);
	GPIO_PinAFConfig(OUTPUT_CONTROL_GPIO2_PORT,OUTPUT_CONTROL_GPIO2_PINSOURCE,OUTPUT_CONTROL_GPIO2_AF);
	GPIO_InitStructure.GPIO_Pin = OUTPUT_CONTROL_GPIO2_PIN;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(OUTPUT_CONTROL_GPIO2_PORT, &GPIO_InitStructure);
	
	//PWM_out_3�ӿ��������
	RCC_AHB1PeriphClockCmd ( OUTPUT_CONTROL_GPIO3_CLK, ENABLE);
	GPIO_PinAFConfig(OUTPUT_CONTROL_GPIO3_PORT,OUTPUT_CONTROL_GPIO3_PINSOURCE,OUTPUT_CONTROL_GPIO3_AF);
	GPIO_InitStructure.GPIO_Pin = OUTPUT_CONTROL_GPIO3_PIN;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(OUTPUT_CONTROL_GPIO3_PORT, &GPIO_InitStructure);


	/*����LED ��ص�GPIO ����ʱ��*/
	//RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��PA�˿�ʱ��
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	/* ��ʱ���������� */
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);
	/* �߼����ƶ�ʱ��PWM ���벶������ */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(ADVANCE_ICPWM_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(ADVANCE_ICPWM_GPIO_PORT, &GPIO_InitStructure);
}
