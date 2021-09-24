#include "./EXTI_Conf/EXTI_Conf.h"
void EXTI_Key_Config(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		EXTI_InitTypeDef EXTI_InitStructure;

		RCC_AHB1PeriphClockCmd(KEY2_INT_GPIO_CLK|KEY1_INT_GPIO_CLK ,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

		GPIO_InitStructure.GPIO_Pin = KEY1_INT_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure);

		SYSCFG_EXTILineConfig(KEY1_INT_EXTI_PORTSOURCE,
		KEY1_INT_EXTI_PINSOURCE);

		EXTI_InitStructure.EXTI_Line = KEY1_INT_EXTI_LINE;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);


		GPIO_InitStructure.GPIO_Pin = KEY2_INT_GPIO_PIN;
		GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStructure);
		
		SYSCFG_EXTILineConfig(KEY2_INT_EXTI_PORTSOURCE,
		KEY2_INT_EXTI_PINSOURCE);
		
		EXTI_InitStructure.EXTI_Line = KEY2_INT_EXTI_LINE;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);
}
