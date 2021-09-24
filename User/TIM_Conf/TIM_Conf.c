#include "./TIM_Conf/TIM_Conf.h" 
#include "./global/global.h"

void TIM_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;//�������ṹ���ʼ��
	TIM_OCInitTypeDef TIM_OCInitStructure;//����ȽϽṹ���ʼ��
	
	RCC_APB1PeriphClockCmd(OUTPUT123_TIM_CLK, ENABLE);//��ʱ���� ʱ�ӽ���
	
	TIM_TimeBaseStructure.TIM_Prescaler = (9-1);//Ԥ��ƵΪ��������ʱ�����ڵ�9��Ƶ=20mHz
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//��������Ƶ�趨 1��Ƶ
	TIM_TimeBaseStructure.TIM_Period = (1000-1);//�������������� һ��PWM����Ҫ100�������������PWMƵ��Ϊ20KHz
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInit(OUTPUT123_TIM, &TIM_TimeBaseStructure);//�������ṹ��ʼ��
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//����Ƚ�PWM1ģʽ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//����Ƚ�����
	TIM_OCInitStructure.TIM_Pulse = 0;//��ʼ����=0
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ LED����
	
	TIM_OC1Init(OUTPUT123_TIM, &TIM_OCInitStructure);//����ȽϽṹ��ʼ��ͨ��1
	TIM_OC1PreloadConfig(OUTPUT123_TIM, TIM_OCPreload_Enable);//���ٸ���ͨ������ CCR1�Ĵ����������̸���
	TIM_OC2Init(OUTPUT123_TIM, &TIM_OCInitStructure);//����ȽϽṹ��ʼ��ͨ��2
	TIM_OC1PreloadConfig(OUTPUT123_TIM, TIM_OCPreload_Enable);//���ٸ���ͨ������ CCR2�Ĵ����������̸���
	TIM_OC3Init(OUTPUT123_TIM, &TIM_OCInitStructure);//����ȽϽṹ��ʼ��ͨ��3
	TIM_OC1PreloadConfig(OUTPUT123_TIM, TIM_OCPreload_Enable);//���ٸ���ͨ������ CCR3�Ĵ����������̸���
	
	TIM_ARRPreloadConfig(OUTPUT123_TIM, ENABLE);//ARR���ؿ���
	//TIM_ITConfig(OUTPUT123_TIM,TIM_IT_Update,ENABLE);//�����������ж�
	TIM_Cmd(OUTPUT123_TIM,ENABLE);//ʹ�ܼ�����
}
void TIM_PWMINPUT_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	// ����TIMx_CLK,x[1,8]

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	
	TIM_DeInit(TIM3);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;              //Ԥ��Ƶ�� 
  TIM_TimeBaseStructure.TIM_Period = 1;  //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM���ϼ���  
	// ��ʼ����ʱ��TIMx, x[1,8]
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	
	// ����ͨ��IC1 ����
	// ѡ�񲶻�ͨ��
	//TIM_ICInitStructure.TIM_Channel = ADVANCE_IC1PWM_CHANNEL;
	// ���ò���ı���
	//TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
	// ���ò���ͨ�����ź��������ĸ�����ͨ��
	//TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;
	// 1 ��Ƶ���������źŵ�ÿ����Ч���ض�����
	//TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	
	// ��ʼ��PWM ����ģʽ
	//TIM_PWMIConfig(ADVANCE_TIM, &TIM_ICInitStructure);	
	
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising ,TIM_ICPolarity_Rising );
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	// ���˲�
	TIM_ICInitStructure.TIM_ICFilter = 0x6;
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	// ���˲�
	TIM_ICInitStructure.TIM_ICFilter = 0x6;
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	// ��������PWM ����ģʽʱ,ֻ��Ҫ���ô����źŵ���һ·���ɣ����ڲ������ڣ�
	// ����һ·�����ڲ���ռ�ձȣ�����Ӳ���Դ�����
	// ����ͨ��IC2 ����
	// TIM_ICInitStructure.TIM_Channel = ADVANCE_IC2PWM_CHANNEL;
	// TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
	// TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;
	// TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	// TIM_ICInitStructure.TIM_ICFilter = 0x0;
	// TIM_PWMIConfig(ADVANCE_TIM, &TIM_ICInitStructure);

	//ѡ�����벶��Ĵ����ź�
	//TIM_SelectInputTrigger(ADVANCE_TIM, TIM_TS_TI1FP1);

	//ѡ���ģʽ: ��λģʽ
	//PWM ����ģʽʱ,��ģʽ���빤���ڸ�λģʽ��������ʼʱ,������CNT �ᱻ��λ
	//TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
	//TIM_SelectMasterSlaveMode(TIM3,TIM_MasterSlaveMode_Enable);
	
	
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	

	//ʹ�ܲ����ж�,����ж���Ե���������ͨ�������������Ǹ���
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_SetCounter(TIM3,0);
	//ʹ�ܸ߼����ƶ�ʱ������������ʼ����
	TIM_Cmd(TIM3, ENABLE);
	}
void TIM_BASIC_Config(void)
{
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		// ����TIMx_CLK,x[6,7]
		RCC_APB1PeriphClockCmd(BASIC_TIM_CLK, ENABLE);
		/* �ۼ� TIM_Period �������һ�����»����ж�*/
		//����ʱ����0 ������4999����Ϊ5000 �Σ�Ϊһ����ʱ����
		TIM_TimeBaseStructure.TIM_Period = 4-1;
		
		//��ʱ��ʱ��ԴTIMxCLK = 2 * PCLK1
		// PCLK1 = HCLK / 4
		// => TIMxCLK=HCLK/2=SystemCoreClock/2=90MHz
		// �趨��ʱ��Ƶ��Ϊ=TIMxCLK/(TIM_Prescaler+1)=1000Hz
		TIM_TimeBaseStructure.TIM_Prescaler = 90000-1;

		// ��ʼ����ʱ��TIMx, x[2,3,4,5]
		TIM_TimeBaseInit(BASIC_TIM, &TIM_TimeBaseStructure);
		
		
		// �����ʱ�������жϱ�־λ
		TIM_ClearFlag(BASIC_TIM, TIM_FLAG_Update);
		
		// ������ʱ�������ж�
		TIM_ITConfig(BASIC_TIM,TIM_IT_Update,ENABLE);
		
		// ʹ�ܶ�ʱ��
		TIM_Cmd(BASIC_TIM, ENABLE);
}
