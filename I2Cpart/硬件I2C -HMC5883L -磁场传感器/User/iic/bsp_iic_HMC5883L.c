/**
  ******************************************************************************
  * @file    bsp_iic_ee.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   EEPROM ��������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F407 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "./iic/bsp_iic_HMC5883L.h"
#include "./usart/bsp_debug_usart.h"
#include  <math.h>

/*
Ҫʵ����EEPROM����д������
1. ��ʼ��Ӳ��IIC
2. ��д��EEPROM�������ݵĺ�������������д��
3. ���ö�д������EEPROMд�����ݣ�����ȡ����У��





*/
uint8_t BUF[10];       //�������ݻ�����
int x,y;
float angle;
#define TIME_OUT   0x000FFFFF
#define   uchar unsigned char
uint32_t count_wait = TIME_OUT;
uchar ge,shi,bai,qian,wan,shiwan;    
static uint8_t Error_CallBack(uint8_t code);


void conversion(long temp_data)  
{     
    shiwan=temp_data/100000+0x30 ;
    temp_data=temp_data%100000;   //ȡ������ 
    wan=temp_data/10000+0x30 ;
    temp_data=temp_data%10000;   //ȡ������
	qian=temp_data/1000+0x30 ;
    temp_data=temp_data%1000;    //ȡ������
    bai=temp_data/100+0x30   ;
    temp_data=temp_data%100;     //ȡ������
    shi=temp_data/10+0x30    ;
    temp_data=temp_data%10;      //ȡ������
    ge=temp_data+0x30; 	
}
void Delayms(vu32 m)
{
  u32 i;
  
  for(; m != 0; m--)	
       for (i=0; i<50000; i++);
}
 /**
  * @brief  HMC5883L_IIC_Config ��ʼ��GPIO��IIC��ģʽ
  * @param  ��
  * @retval ��
  */
void HMC5883L_IIC_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  I2C_InitTypeDef  IIC_InitStructure;
		/*ʹ��GPIO��ʱ��*/
  RCC_AHB1PeriphClockCmd(HMC5883L_IIC_SCL_GPIO_CLK|HMC5883L_IIC_SDA_GPIO_CLK,ENABLE);

  /* ʹ�� IIC ʱ�� */
  RCC_APB1PeriphClockCmd(HMC5883L_IIC_CLK, ENABLE);
	
	 /* ���� PXx �� IIC*/
  GPIO_PinAFConfig(HMC5883L_IIC_SCL_GPIO_PORT,HMC5883L_IIC_SCL_SOURCE,HMC5883L_IIC_SCL_AF);

  /*  ���� PXx �� IIC*/
  GPIO_PinAFConfig(HMC5883L_IIC_SDA_GPIO_PORT,HMC5883L_IIC_SDA_SOURCE,HMC5883L_IIC_SDA_AF);
  
  /* GPIO SCL��ʼ�� */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;//��©���ģʽ
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = HMC5883L_IIC_SCL_PIN  ;  
  GPIO_Init(HMC5883L_IIC_SCL_GPIO_PORT, &GPIO_InitStructure);

  /* GPIO SDA ��ʼ�� */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = HMC5883L_IIC_SDA_PIN;
  GPIO_Init(HMC5883L_IIC_SDA_GPIO_PORT, &GPIO_InitStructure);
  /*����IIC�Ĵ��� ��ʼ��IIC*/
  IIC_InitStructure.I2C_Ack = I2C_Ack_Enable  ;
  IIC_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit  ;
	IIC_InitStructure.I2C_ClockSpeed =  HMC5883L_IIC_BAUDRATE  ;
	IIC_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2 ;
	IIC_InitStructure.I2C_Mode = I2C_Mode_I2C  ;
	IIC_InitStructure.I2C_OwnAddress1 = STM32_IIC_OWN_ADDR;
	
  I2C_Init (HMC5883L_IIC, &IIC_InitStructure); 
  /* ʹ�ܴ��� */
  I2C_Cmd(HMC5883L_IIC, ENABLE);
}

 /**
  * @brief  NVIC_Config �жϳ�ʼ��
  * @param  ��
  * @retval ��
  */
void NVIC_Configuration(void)
{ 
  NVIC_InitTypeDef NVIC_InitStructure;  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); 
  NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
 /**
  * @brief  WWDG_Config �жϳ�ʼ��
  * @param  ��
  * @retval ��
  */
void WWDG_Configuration(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);	
  WWDG_SetPrescaler(WWDG_Prescaler_8);	              //  WWDG clock counter = (PCLK1/4096)/8 = 244 Hz (~4 ms)  
  WWDG_SetWindowValue(0x41);		                 // Set Window value to 0x41
  WWDG_Enable(0x7f);		       // Enable WWDG and set counter value to 0x7F, WWDG timeout = ~4 ms * 64 = 262 ms 
  WWDG_ClearFlag();			       // Clear EWI flag
  WWDG_EnableIT();			       // Enable EW interrupt
}
void WWDG_IRQHandler(void)
{
  /* Update WWDG counter */
  WWDG_SetCounter(0x7f);
	
  /* Clear EWI flag */
  WWDG_ClearFlag(); 
}

 /**
  * @brief  Single_Write ���ֽ�д��
  * @param  ��
  * @retval ��
  */

uint8_t Single_Write(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t REG_data)
{
   /*������ʼ�ź�*/
	I2C_GenerateSTART(HMC5883L_IIC, ENABLE);

  /*���� count_wait */
	count_wait = TIME_OUT;
	
	/*�ȴ�EV5�¼���ֱ�����ɹ�*/
	while(I2C_CheckEvent (HMC5883L_IIC, I2C_EVENT_MASTER_MODE_SELECT)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(1);
		}	
	}
	
	/*���ʹ��豸�ĵ�ַ*/
	I2C_Send7bitAddress( HMC5883L_IIC,SlaveAddress,I2C_Direction_Transmitter );
	
	/*���� count_wait */
	count_wait = TIME_OUT;
	
	/*�ȴ�EV6�¼���ֱ�����ɹ�*/
	while(I2C_CheckEvent (HMC5883L_IIC, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(2);
		}	
	}
	
	/*����Ҫд��Ĵ洢��Ԫ���ַ*/
	I2C_SendData  ( HMC5883L_IIC,  REG_Address );
	
		/*�ȴ�EV8_2�¼���ֱ�����ɹ�*/
	while(I2C_CheckEvent (HMC5883L_IIC, I2C_EVENT_MASTER_BYTE_TRANSMITTED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(3);
		}	
	}
	
	/*����Ҫд�������*/
	I2C_SendData  ( HMC5883L_IIC,  REG_data );
	
	/*���� count_wait */
	count_wait = TIME_OUT;
	
	/*�ȴ�EV8_2�¼���ֱ�����ɹ�*/
	while(I2C_CheckEvent (HMC5883L_IIC, I2C_EVENT_MASTER_BYTE_TRANSMITTED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(4);
		}	
	}

	/*���������ź�*/
	I2C_GenerateSTOP(HMC5883L_IIC, ENABLE);

 return 0;
}

 /**
  * @brief  Single_Read ���ֽڶ�ȡ
  * @param  ��
  * @retval ��
  */
uint8_t Single_Read(uint8_t SlaveAddress,uint8_t REG_Address)
{
   uint8_t readdata;
	/*������ʼ�ź�*/
	I2C_GenerateSTART(HMC5883L_IIC, ENABLE);
	
	/*���� count_wait */
	count_wait = TIME_OUT;
	
	/*�ȴ�EV5�¼���ֱ�����ɹ�*/
	while(I2C_CheckEvent (HMC5883L_IIC, I2C_EVENT_MASTER_MODE_SELECT)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(5);
		}	
	}
	
	/*���ʹ��豸�ĵ�ַ*/
	I2C_Send7bitAddress( HMC5883L_IIC,SlaveAddress,I2C_Direction_Transmitter );
	
	/*���� count_wait */
	count_wait = TIME_OUT;
	
	/*�ȴ�EV6�¼���ֱ�����ɹ�*/
	while(I2C_CheckEvent (HMC5883L_IIC, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(6);
		}	
	}
  
	
	/*����Ҫ��ȡ�Ĵ洢��Ԫ���ַ*/
	I2C_SendData  ( HMC5883L_IIC,  REG_Address );
	
		/*�ȴ�EV8_2�¼���ֱ�����ɹ�*/
	while(I2C_CheckEvent (HMC5883L_IIC, I2C_EVENT_MASTER_BYTE_TRANSMITTED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(7);
		}	
	}
	
  /*�����ڶ�����ʼ�ź�*/
	I2C_GenerateSTART(HMC5883L_IIC, ENABLE);
	
		/*���� count_wait */
	count_wait = TIME_OUT;
	
	/*�ȴ�EV5�¼���ֱ�����ɹ�*/
	while(I2C_CheckEvent (HMC5883L_IIC, I2C_EVENT_MASTER_MODE_SELECT)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(8);
		}	
	}
	
	/*���ʹ��豸�ĵ�ַ ����������Ϊ������*/
	I2C_Send7bitAddress( HMC5883L_IIC,SlaveAddress,I2C_Direction_Receiver );
	
	/*���� count_wait */
	count_wait = TIME_OUT;
	
	/*�ȴ�EV6�¼���ֱ�����ɹ�*/
	while(I2C_CheckEvent (HMC5883L_IIC, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(9);
		}	
	}
	/*������Ӧ���ź�*/
	I2C_AcknowledgeConfig (HMC5883L_IIC,DISABLE); 
	
		/*���� count_wait */
	count_wait = TIME_OUT;
	
	/*�ȴ�EV8_2�¼���ֱ�����ɹ�*/
	while(I2C_CheckEvent (HMC5883L_IIC, I2C_EVENT_MASTER_BYTE_RECEIVED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(10);
		}	
	}

	
	/*����Ҫ���������*/
	 readdata = I2C_ReceiveData  ( HMC5883L_IIC );  
	
	/*���������ź�*/
	I2C_GenerateSTOP(HMC5883L_IIC, ENABLE);

 return readdata;
}

uint8_t Error_CallBack(uint8_t code)
{
	printf("IIC error occur, code=%d", code);
	return code;
}

void  Init_HMC5883L(void)
{
   Single_Write(STM32_IIC_HMC5883L_ADDR,0x00,0x14);  //���üĴ���A
	 Single_Write(STM32_IIC_HMC5883L_ADDR,0x02,0x00);  //����ģʽ�Ĵ���
	 Delayms(10);
  
}
void read_HMC5883L(void)
{
     BUF[1]=Single_Read(STM32_IIC_HMC5883L_ADDR,0x03);//OUT_X_L_A
     BUF[2]=Single_Read(STM32_IIC_HMC5883L_ADDR,0x04);//OUT_X_H_A

	   BUF[3]=Single_Read(STM32_IIC_HMC5883L_ADDR,0x07);//OUT_Y_L_A
     BUF[4]=Single_Read(STM32_IIC_HMC5883L_ADDR,0x08);//OUT_Y_H_A

     x=(BUF[1] << 8) | BUF[2]; //Combine MSB and LSB of X Data output register
     y=(BUF[3] << 8) | BUF[4]; //Combine MSB and LSB of Z Data output register

     if(x>0x7fff)x-=0xffff;	  
     if(y>0x7fff)y-=0xffff;	  
     angle= atan2(y,x) * (180 / 3.14159265) + 180; // angle in degrees
}


void  Send_HMC5883L(void)
{
USART_SendData(USART1,'H');
	  Delayms(10);
USART_SendData(USART1,'M');
	  Delayms(10);
USART_SendData(USART1,'C');
	  Delayms(10);
USART_SendData(USART1,'5');
	  Delayms(10);
USART_SendData(USART1,'8');
	  Delayms(10);
USART_SendData(USART1,'8');
	  Delayms(10);
USART_SendData(USART1,'3');
	  Delayms(10);
USART_SendData(USART1,'L');
	  Delayms(10);
USART_SendData(USART1,':');
	  Delayms(10);
conversion(angle);
USART_SendData(USART1,bai);
	  Delayms(10);	
USART_SendData(USART1,shi);
	  Delayms(10);
USART_SendData(USART1,ge);
	  Delayms(10);	
USART_SendData(USART1,'`');
	  Delayms(10);		
		 USART_SendData(USART1,0x0d);
     USART_SendData(USART1,0x0a);
}
 
/*********************************************END OF FILE**********************/
