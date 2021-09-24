#include "./NVIC_Conf/NVIC_Conf.h" 
void TIM_BASIC_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	// �����ж���Ϊ1
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	// �����ж���Դ
	NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM_IRQn;
	// ������ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	// ���������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
void TIM_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;//��ʼ���ն˽ṹ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//�����жϷ�����1
	NVIC_InitStructure.NVIC_IRQChannel = OUTPUT123_TIM_IRQn;//�ж�ͨ������
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);//��ʼ���жϹ���ṹ
}
void TIMx_NVIC_Configuration(void)
{
 NVIC_InitTypeDef NVIC_InitStructure;
 // �����ж���Ϊ0
 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
 // �����ж���Դ
 NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
 // ������ռ���ȼ�
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
 // ���������ȼ�
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

// Ƕ�������жϿ�������ѡ�� 
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

// ����USART Ϊ�ж�Դ 
NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
// �������ȼ�Ϊ1 
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
// �����ȼ�Ϊ1 
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
// ʹ���ж� 
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
// ��ʼ������NVIC 
NVIC_Init(&NVIC_InitStructure);
}

void DGPS_NVIC_Configuration(void)
{
NVIC_InitTypeDef NVIC_InitStructure;

// Ƕ�������жϿ�������ѡ�� 
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

// ����USART Ϊ�ж�Դ 
NVIC_InitStructure.NVIC_IRQChannel = DGPS_USART_IRQ;
// �������ȼ�Ϊ1 
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
// �����ȼ�Ϊ1 
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
// ʹ���ж� 
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
// ��ʼ������NVIC 
NVIC_Init(&NVIC_InitStructure);
}