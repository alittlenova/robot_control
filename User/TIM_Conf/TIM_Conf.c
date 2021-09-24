#include "./TIM_Conf/TIM_Conf.h" 
#include "./global/global.h"

void TIM_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;//计数器结构体初始化
	TIM_OCInitTypeDef TIM_OCInitStructure;//输出比较结构体初始化
	
	RCC_APB1PeriphClockCmd(OUTPUT123_TIM_CLK, ENABLE);//定时器打开 时钟接入
	
	TIM_TimeBaseStructure.TIM_Prescaler = (9-1);//预分频为外设总线时钟周期的9分频=20mHz
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//计数器分频设定 1分频
	TIM_TimeBaseStructure.TIM_Period = (1000-1);//计数器记数周期 一个PWM波需要100个计数周期完成PWM频率为20KHz
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInit(OUTPUT123_TIM, &TIM_TimeBaseStructure);//计数器结构初始化
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//输出比较PWM1模式
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//输出比较启动
	TIM_OCInitStructure.TIM_Pulse = 0;//初始脉宽=0
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于CCR1_Val时为高电平 LED灯灭
	
	TIM_OC1Init(OUTPUT123_TIM, &TIM_OCInitStructure);//输出比较结构初始化通道1
	TIM_OC1PreloadConfig(OUTPUT123_TIM, TIM_OCPreload_Enable);//快速更新通道开启 CCR1寄存器可以立刻更新
	TIM_OC2Init(OUTPUT123_TIM, &TIM_OCInitStructure);//输出比较结构初始化通道2
	TIM_OC1PreloadConfig(OUTPUT123_TIM, TIM_OCPreload_Enable);//快速更新通道开启 CCR2寄存器可以立刻更新
	TIM_OC3Init(OUTPUT123_TIM, &TIM_OCInitStructure);//输出比较结构初始化通道3
	TIM_OC1PreloadConfig(OUTPUT123_TIM, TIM_OCPreload_Enable);//快速更新通道开启 CCR3寄存器可以立刻更新
	
	TIM_ARRPreloadConfig(OUTPUT123_TIM, ENABLE);//ARR重载开启
	//TIM_ITConfig(OUTPUT123_TIM,TIM_IT_Update,ENABLE);//开启计数器中断
	TIM_Cmd(OUTPUT123_TIM,ENABLE);//使能计数器
}
void TIM_PWMINPUT_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	// 开启TIMx_CLK,x[1,8]

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	
	TIM_DeInit(TIM3);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;              //预分频器 
  TIM_TimeBaseStructure.TIM_Period = 1;  //设定计数器自动重装值
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //选择时钟分频：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM向上计数  
	// 初始化定时器TIMx, x[1,8]
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	
	// 捕获通道IC1 配置
	// 选择捕获通道
	//TIM_ICInitStructure.TIM_Channel = ADVANCE_IC1PWM_CHANNEL;
	// 设置捕获的边沿
	//TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
	// 设置捕获通道的信号来自于哪个输入通道
	//TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;
	// 1 分频，即捕获信号的每个有效边沿都捕获
	//TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	
	// 初始化PWM 输入模式
	//TIM_PWMIConfig(ADVANCE_TIM, &TIM_ICInitStructure);	
	
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising ,TIM_ICPolarity_Rising );
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	// 不滤波
	TIM_ICInitStructure.TIM_ICFilter = 0x6;
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	// 不滤波
	TIM_ICInitStructure.TIM_ICFilter = 0x6;
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	// 当工作做PWM 输入模式时,只需要设置触发信号的那一路即可（用于测量周期）
	// 另外一路（用于测量占空比）会由硬件自带设置
	// 捕获通道IC2 配置
	// TIM_ICInitStructure.TIM_Channel = ADVANCE_IC2PWM_CHANNEL;
	// TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
	// TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;
	// TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	// TIM_ICInitStructure.TIM_ICFilter = 0x0;
	// TIM_PWMIConfig(ADVANCE_TIM, &TIM_ICInitStructure);

	//选择输入捕获的触发信号
	//TIM_SelectInputTrigger(ADVANCE_TIM, TIM_TS_TI1FP1);

	//选择从模式: 复位模式
	//PWM 输入模式时,从模式必须工作在复位模式，当捕获开始时,计数器CNT 会被复位
	//TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
	//TIM_SelectMasterSlaveMode(TIM3,TIM_MasterSlaveMode_Enable);
	
	
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	

	//使能捕获中断,这个中断针对的是主捕获通道（测量周期那个）
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_SetCounter(TIM3,0);
	//使能高级控制定时器，计数器开始计数
	TIM_Cmd(TIM3, ENABLE);
	}
void TIM_BASIC_Config(void)
{
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		// 开启TIMx_CLK,x[6,7]
		RCC_APB1PeriphClockCmd(BASIC_TIM_CLK, ENABLE);
		/* 累计 TIM_Period 个后产生一个更新或者中断*/
		//当定时器从0 计数到4999，即为5000 次，为一个定时周期
		TIM_TimeBaseStructure.TIM_Period = 4-1;
		
		//定时器时钟源TIMxCLK = 2 * PCLK1
		// PCLK1 = HCLK / 4
		// => TIMxCLK=HCLK/2=SystemCoreClock/2=90MHz
		// 设定定时器频率为=TIMxCLK/(TIM_Prescaler+1)=1000Hz
		TIM_TimeBaseStructure.TIM_Prescaler = 90000-1;

		// 初始化定时器TIMx, x[2,3,4,5]
		TIM_TimeBaseInit(BASIC_TIM, &TIM_TimeBaseStructure);
		
		
		// 清除定时器更新中断标志位
		TIM_ClearFlag(BASIC_TIM, TIM_FLAG_Update);
		
		// 开启定时器更新中断
		TIM_ITConfig(BASIC_TIM,TIM_IT_Update,ENABLE);
		
		// 使能定时器
		TIM_Cmd(BASIC_TIM, ENABLE);
}
