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
  
#include "./iic/bsp_iic_ADXL345.h"
#include "./usart/bsp_debug_usart.h"
#include  <math.h>

/*
Ҫʵ����EEPROM����д������
1. ��ʼ��Ӳ��IIC
2. ��д��EEPROM�������ݵĺ�������������д��
3. ���ö�д������EEPROMд�����ݣ�����ȡ����У��





*/
uint8_t TX_DATA[4];  	 //��ʾ�ݻ�����
uint8_t BUF[10];       //�������ݻ�����
int A_X,A_Y,A_Z;
short data_xyz[3];
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
  * @brief  ADXL345_IIC_Config ��ʼ��GPIO��IIC��ģʽ
  * @param  ��
  * @retval ��
  */
void ADXL345_IIC_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  I2C_InitTypeDef  IIC_InitStructure;
		/*ʹ��GPIO��ʱ��*/
  RCC_AHB1PeriphClockCmd(ADXL345_IIC_SCL_GPIO_CLK|ADXL345_IIC_SDA_GPIO_CLK,ENABLE);

  /* ʹ�� IIC ʱ�� */
  RCC_APB1PeriphClockCmd(ADXL345_IIC_CLK, ENABLE);
	
	 /* ���� PXx �� IIC*/
  GPIO_PinAFConfig(ADXL345_IIC_SCL_GPIO_PORT,ADXL345_IIC_SCL_SOURCE,ADXL345_IIC_SCL_AF);

  /*  ���� PXx �� IIC*/
  GPIO_PinAFConfig(ADXL345_IIC_SDA_GPIO_PORT,ADXL345_IIC_SDA_SOURCE,ADXL345_IIC_SDA_AF);
  
  /* GPIO SCL��ʼ�� */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;//��©���ģʽ
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = ADXL345_IIC_SCL_PIN  ;  
  GPIO_Init(ADXL345_IIC_SCL_GPIO_PORT, &GPIO_InitStructure);

  /* GPIO SDA ��ʼ�� */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = ADXL345_IIC_SDA_PIN;
  GPIO_Init(ADXL345_IIC_SDA_GPIO_PORT, &GPIO_InitStructure);
  /*����IIC�Ĵ��� ��ʼ��IIC*/
  IIC_InitStructure.I2C_Ack = I2C_Ack_Enable  ;
  IIC_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit  ;
	IIC_InitStructure.I2C_ClockSpeed =  ADXL345_IIC_BAUDRATE  ;
	IIC_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2 ;
	IIC_InitStructure.I2C_Mode = I2C_Mode_I2C  ;
	IIC_InitStructure.I2C_OwnAddress1 = STM32_IIC_OWN_ADDR;
	
  I2C_Init (ADXL345_IIC, &IIC_InitStructure); 
  /* ʹ�ܴ��� */
  I2C_Cmd(ADXL345_IIC, ENABLE);
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
	I2C_GenerateSTART(ADXL345_IIC, ENABLE);

  /*���� count_wait */
	count_wait = TIME_OUT;
	
	/*�ȴ�EV5�¼���ֱ�����ɹ�*/
	while(I2C_CheckEvent (ADXL345_IIC, I2C_EVENT_MASTER_MODE_SELECT)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(1);
		}	
	}
	
	/*���ʹ��豸�ĵ�ַ*/
	I2C_Send7bitAddress( ADXL345_IIC,SlaveAddress,I2C_Direction_Transmitter );
	
	/*���� count_wait */
	count_wait = TIME_OUT;
	
	/*�ȴ�EV6�¼���ֱ�����ɹ�*/
	while(I2C_CheckEvent (ADXL345_IIC, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(2);
		}	
	}
	
	/*����Ҫд��Ĵ洢��Ԫ���ַ*/
	I2C_SendData  ( ADXL345_IIC,  REG_Address );
	
		/*�ȴ�EV8_2�¼���ֱ�����ɹ�*/
	while(I2C_CheckEvent (ADXL345_IIC, I2C_EVENT_MASTER_BYTE_TRANSMITTED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(3);
		}	
	}
	
	/*����Ҫд�������*/
	I2C_SendData  ( ADXL345_IIC,  REG_data );
	
	/*���� count_wait */
	count_wait = TIME_OUT;
	
	/*�ȴ�EV8_2�¼���ֱ�����ɹ�*/
	while(I2C_CheckEvent (ADXL345_IIC, I2C_EVENT_MASTER_BYTE_TRANSMITTED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(4);
		}	
	}

	/*���������ź�*/
	I2C_GenerateSTOP(ADXL345_IIC, ENABLE);

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
	I2C_GenerateSTART(ADXL345_IIC, ENABLE);
	
	/*���� count_wait */
	count_wait = TIME_OUT;
	
	/*�ȴ�EV5�¼���ֱ�����ɹ�*/
	while(I2C_CheckEvent (ADXL345_IIC, I2C_EVENT_MASTER_MODE_SELECT)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(5);
		}	
	}
	
	/*���ʹ��豸�ĵ�ַ*/
	I2C_Send7bitAddress( ADXL345_IIC,SlaveAddress,I2C_Direction_Transmitter );
	
	/*���� count_wait */
	count_wait = TIME_OUT;
	
	/*�ȴ�EV6�¼���ֱ�����ɹ�*/
	while(I2C_CheckEvent (ADXL345_IIC, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(6);
		}	
	}
  
	
	/*����Ҫ��ȡ�Ĵ洢��Ԫ���ַ*/
	I2C_SendData  ( ADXL345_IIC,  REG_Address );
	
		/*�ȴ�EV8_2�¼���ֱ�����ɹ�*/
	while(I2C_CheckEvent (ADXL345_IIC, I2C_EVENT_MASTER_BYTE_TRANSMITTED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(7);
		}	
	}
	
  /*�����ڶ�����ʼ�ź�*/
	I2C_GenerateSTART(ADXL345_IIC, ENABLE);
	
		/*���� count_wait */
	count_wait = TIME_OUT;
	
	/*�ȴ�EV5�¼���ֱ�����ɹ�*/
	while(I2C_CheckEvent (ADXL345_IIC, I2C_EVENT_MASTER_MODE_SELECT)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(8);
		}	
	}
	
	/*���ʹ��豸�ĵ�ַ ����������Ϊ������*/
	I2C_Send7bitAddress( ADXL345_IIC,SlaveAddress,I2C_Direction_Receiver );
	
	/*���� count_wait */
	count_wait = TIME_OUT;
	
	/*�ȴ�EV6�¼���ֱ�����ɹ�*/
	while(I2C_CheckEvent (ADXL345_IIC, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(9);
		}	
	}
	/*������Ӧ���ź�*/
	I2C_AcknowledgeConfig (ADXL345_IIC,DISABLE); 
	
		/*���� count_wait */
	count_wait = TIME_OUT;
	
	/*�ȴ�EV8_2�¼���ֱ�����ɹ�*/
	while(I2C_CheckEvent (ADXL345_IIC, I2C_EVENT_MASTER_BYTE_RECEIVED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(10);
		}	
	}

	
	/*����Ҫ���������*/
	 readdata = I2C_ReceiveData  ( ADXL345_IIC );  
	
	/*���������ź�*/
	I2C_GenerateSTOP(ADXL345_IIC, ENABLE);

 return readdata;
}

uint8_t Error_CallBack(uint8_t code)
{
	printf("IIC error occur, code=%d", code);
	return code;
}

void  Init_ADXL345(void)
{
   Single_Write(STM32_IIC_ADXL345_ADDR,0x31,0x0B);   //������Χ,����16g��13λģʽ
  // Single_Write(ADXL345_Addr,0x2C,0x0e);   //�����趨Ϊ100hz �ο�pdf13ҳ
   Single_Write(STM32_IIC_ADXL345_ADDR,0x2D,0x08);   //ѡ���Դģʽ   �ο�pdf24ҳ
   Single_Write(STM32_IIC_ADXL345_ADDR,0x2E,0x80);   //ʹ�� DATA_READY �ж�
  // Single_Write(ADXL345_Addr,0x1E,0x00);   //X ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
  // Single_Write(ADXL345_Addr,0x1F,0x00);   //Y ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
  // Single_Write(ADXL345_Addr,0x20,0x05);   //Z ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
}
void read_ADXL345(void)
{
     BUF[0]=Single_Read(STM32_IIC_ADXL345_ADDR,0x32);//OUT_X_L_A
     BUF[1]=Single_Read(STM32_IIC_ADXL345_ADDR,0x33);//OUT_X_H_A

	   BUF[2]=Single_Read(STM32_IIC_ADXL345_ADDR,0x34);//OUT_Y_L_A
     BUF[3]=Single_Read(STM32_IIC_ADXL345_ADDR,0x35);//OUT_Y_H_A

	   BUF[4]=Single_Read(STM32_IIC_ADXL345_ADDR,0x36);//OUT_Z_L_A
     BUF[5]=Single_Read(STM32_IIC_ADXL345_ADDR,0x37);//OUT_Z_H_A

	   A_X=(BUF[1]<<8)+BUF[0];  //�ϳ�����  
	   A_Y=(BUF[3]<<8)+BUF[2];  //�ϳ�����
	   A_Z=(BUF[5]<<8)+BUF[4];  //�ϳ�����
}

void Send_ADXL345_data(int dis_data)
  { float temp ;
	if(dis_data>0x7fff)dis_data-=0xffff;
 	if(dis_data<0){
  	     dis_data=-dis_data;
	     USART_SendData(USART1,'-');
		 Delayms(2);
	}
	else
	  { 
	   USART_SendData(USART1,'+');
	   Delayms(2);
	   }
        temp=dis_data*3.9;  //�������ݺ���ʾ,�鿼ADXL345�������ŵ�4ҳ
        conversion(temp);          //ת������ʾ��Ҫ������	 
	    USART_SendData(USART1,qian);
		   Delayms(10);
		USART_SendData(USART1,'.');
		   Delayms(10);
	   USART_SendData(USART1,bai); 
		   Delayms(10);
	   USART_SendData(USART1,shi); 
		   Delayms(10);
	    USART_SendData(USART1,ge); 
		 
}
void  Send_ADXL345(void)
{
USART_SendData(USART1,'A');
	  Delayms(10);
USART_SendData(USART1,'D');
	  Delayms(10);
USART_SendData(USART1,'X');
	  Delayms(10);
USART_SendData(USART1,'L');
	  Delayms(10);
USART_SendData(USART1,'3');
	  Delayms(10);
USART_SendData(USART1,'4');
	  Delayms(10);
USART_SendData(USART1,'5');
	  Delayms(10);
USART_SendData(USART1,':');
	  Delayms(10);
USART_SendData(USART1,'X');
	  Delayms(10);
USART_SendData(USART1,'=');
	  Delayms(10);
Send_ADXL345_data(A_X);
    Delayms(10);
USART_SendData(USART1,'g'); 
	  Delayms(10);	 
USART_SendData(USART1,'Y');
		Delayms(10);
USART_SendData(USART1,'=');
		Delayms(10);
Send_ADXL345_data(A_Y);
    Delayms(10);
USART_SendData(USART1,'g'); 
		Delayms(10);
USART_SendData(USART1,'Z');
		Delayms(10);
USART_SendData(USART1,'=');
		Delayms(10);
Send_ADXL345_data(A_Z);
	  Delayms(10);
USART_SendData(USART1,'g'); 
		Delayms(10);
		 
		 USART_SendData(USART1,0x0d);
     USART_SendData(USART1,0x0a);
}
 
/*********************************************END OF FILE**********************/
