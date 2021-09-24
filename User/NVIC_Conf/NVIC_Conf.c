#include "./NVIC_Conf/NVIC_Conf.h" 
void TIM_BASIC_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	// 设置中断组为1
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	// 设置中断来源
	NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM_IRQn;
	// 设置抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	// 设置子优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
void TIM_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;//初始化终端结构体
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//开启中断服务组1
	NVIC_InitStructure.NVIC_IRQChannel = OUTPUT123_TIM_IRQn;//中断通道名字
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能中断通道
	NVIC_Init(&NVIC_InitStructure);//初始化中断管理结构
}
void TIMx_NVIC_Configuration(void)
{
 NVIC_InitTypeDef NVIC_InitStructure;
 // 设置中断组为0
 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
 // 设置中断来源
 NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
 // 设置抢占优先级
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
 // 设置子优先级
 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 NVIC_Init(&NVIC_InitStructure);
}
void EXTI_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannel = KEY2_INT_EXTI_IRQ;
	NVIC_Init(&NVIC_InitStructure);
}

void DEBUG_NVIC_Configuration(void)
{
NVIC_InitTypeDef NVIC_InitStructure;

// 嵌套向量中断控制器组选择 
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

// 配置USART 为中断源 
NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
// 抢断优先级为1 
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
// 子优先级为1 
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
// 使能中断 
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
// 初始化配置NVIC 
NVIC_Init(&NVIC_InitStructure);
}

void DGPS_NVIC_Configuration(void)
{
NVIC_InitTypeDef NVIC_InitStructure;

// 嵌套向量中断控制器组选择 
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

// 配置USART 为中断源 
NVIC_InitStructure.NVIC_IRQChannel = DGPS_USART_IRQ;
// 抢断优先级为1 
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
// 子优先级为1 
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
// 使能中断 
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
// 初始化配置NVIC 
NVIC_Init(&NVIC_InitStructure);
}