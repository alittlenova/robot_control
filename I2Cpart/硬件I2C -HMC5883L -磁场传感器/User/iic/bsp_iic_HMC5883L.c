/**
  ******************************************************************************
  * @file    bsp_iic_ee.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   EEPROM 驱动程序
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F407 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "./iic/bsp_iic_HMC5883L.h"
#include "./usart/bsp_debug_usart.h"
#include  <math.h>

/*
要实现往EEPROM里面写入数据
1. 初始化硬件IIC
2. 编写往EEPROM传输数据的函数（包括读和写）
3. 利用读写函数往EEPROM写入数据，并读取进行校验





*/
uint8_t BUF[10];       //接收数据缓存区
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
    temp_data=temp_data%100000;   //取余运算 
    wan=temp_data/10000+0x30 ;
    temp_data=temp_data%10000;   //取余运算
	qian=temp_data/1000+0x30 ;
    temp_data=temp_data%1000;    //取余运算
    bai=temp_data/100+0x30   ;
    temp_data=temp_data%100;     //取余运算
    shi=temp_data/10+0x30    ;
    temp_data=temp_data%10;      //取余运算
    ge=temp_data+0x30; 	
}
void Delayms(vu32 m)
{
  u32 i;
  
  for(; m != 0; m--)	
       for (i=0; i<50000; i++);
}
 /**
  * @brief  HMC5883L_IIC_Config 初始化GPIO及IIC的模式
  * @param  无
  * @retval 无
  */
void HMC5883L_IIC_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  I2C_InitTypeDef  IIC_InitStructure;
		/*使能GPIO的时钟*/
  RCC_AHB1PeriphClockCmd(HMC5883L_IIC_SCL_GPIO_CLK|HMC5883L_IIC_SDA_GPIO_CLK,ENABLE);

  /* 使能 IIC 时钟 */
  RCC_APB1PeriphClockCmd(HMC5883L_IIC_CLK, ENABLE);
	
	 /* 连接 PXx 到 IIC*/
  GPIO_PinAFConfig(HMC5883L_IIC_SCL_GPIO_PORT,HMC5883L_IIC_SCL_SOURCE,HMC5883L_IIC_SCL_AF);

  /*  连接 PXx 到 IIC*/
  GPIO_PinAFConfig(HMC5883L_IIC_SDA_GPIO_PORT,HMC5883L_IIC_SDA_SOURCE,HMC5883L_IIC_SDA_AF);
  
  /* GPIO SCL初始化 */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;//开漏输出模式
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = HMC5883L_IIC_SCL_PIN  ;  
  GPIO_Init(HMC5883L_IIC_SCL_GPIO_PORT, &GPIO_InitStructure);

  /* GPIO SDA 初始化 */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = HMC5883L_IIC_SDA_PIN;
  GPIO_Init(HMC5883L_IIC_SDA_GPIO_PORT, &GPIO_InitStructure);
  /*配置IIC寄存器 初始化IIC*/
  IIC_InitStructure.I2C_Ack = I2C_Ack_Enable  ;
  IIC_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit  ;
	IIC_InitStructure.I2C_ClockSpeed =  HMC5883L_IIC_BAUDRATE  ;
	IIC_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2 ;
	IIC_InitStructure.I2C_Mode = I2C_Mode_I2C  ;
	IIC_InitStructure.I2C_OwnAddress1 = STM32_IIC_OWN_ADDR;
	
  I2C_Init (HMC5883L_IIC, &IIC_InitStructure); 
  /* 使能串口 */
  I2C_Cmd(HMC5883L_IIC, ENABLE);
}

 /**
  * @brief  NVIC_Config 中断初始化
  * @param  无
  * @retval 无
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
  * @brief  WWDG_Config 中断初始化
  * @param  无
  * @retval 无
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
  * @brief  Single_Write 单字节写入
  * @param  无
  * @retval 无
  */

uint8_t Single_Write(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t REG_data)
{
   /*产生起始信号*/
	I2C_GenerateSTART(HMC5883L_IIC, ENABLE);

  /*重置 count_wait */
	count_wait = TIME_OUT;
	
	/*等待EV5事件，直到检测成功*/
	while(I2C_CheckEvent (HMC5883L_IIC, I2C_EVENT_MASTER_MODE_SELECT)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(1);
		}	
	}
	
	/*发送从设备的地址*/
	I2C_Send7bitAddress( HMC5883L_IIC,SlaveAddress,I2C_Direction_Transmitter );
	
	/*重置 count_wait */
	count_wait = TIME_OUT;
	
	/*等待EV6事件，直到检测成功*/
	while(I2C_CheckEvent (HMC5883L_IIC, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(2);
		}	
	}
	
	/*发送要写入的存储单元格地址*/
	I2C_SendData  ( HMC5883L_IIC,  REG_Address );
	
		/*等待EV8_2事件，直到检测成功*/
	while(I2C_CheckEvent (HMC5883L_IIC, I2C_EVENT_MASTER_BYTE_TRANSMITTED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(3);
		}	
	}
	
	/*发送要写入的数据*/
	I2C_SendData  ( HMC5883L_IIC,  REG_data );
	
	/*重置 count_wait */
	count_wait = TIME_OUT;
	
	/*等待EV8_2事件，直到检测成功*/
	while(I2C_CheckEvent (HMC5883L_IIC, I2C_EVENT_MASTER_BYTE_TRANSMITTED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(4);
		}	
	}

	/*产生结束信号*/
	I2C_GenerateSTOP(HMC5883L_IIC, ENABLE);

 return 0;
}

 /**
  * @brief  Single_Read 单字节读取
  * @param  无
  * @retval 无
  */
uint8_t Single_Read(uint8_t SlaveAddress,uint8_t REG_Address)
{
   uint8_t readdata;
	/*产生起始信号*/
	I2C_GenerateSTART(HMC5883L_IIC, ENABLE);
	
	/*重置 count_wait */
	count_wait = TIME_OUT;
	
	/*等待EV5事件，直到检测成功*/
	while(I2C_CheckEvent (HMC5883L_IIC, I2C_EVENT_MASTER_MODE_SELECT)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(5);
		}	
	}
	
	/*发送从设备的地址*/
	I2C_Send7bitAddress( HMC5883L_IIC,SlaveAddress,I2C_Direction_Transmitter );
	
	/*重置 count_wait */
	count_wait = TIME_OUT;
	
	/*等待EV6事件，直到检测成功*/
	while(I2C_CheckEvent (HMC5883L_IIC, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(6);
		}	
	}
  
	
	/*发送要读取的存储单元格地址*/
	I2C_SendData  ( HMC5883L_IIC,  REG_Address );
	
		/*等待EV8_2事件，直到检测成功*/
	while(I2C_CheckEvent (HMC5883L_IIC, I2C_EVENT_MASTER_BYTE_TRANSMITTED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(7);
		}	
	}
	
  /*产生第二次起始信号*/
	I2C_GenerateSTART(HMC5883L_IIC, ENABLE);
	
		/*重置 count_wait */
	count_wait = TIME_OUT;
	
	/*等待EV5事件，直到检测成功*/
	while(I2C_CheckEvent (HMC5883L_IIC, I2C_EVENT_MASTER_MODE_SELECT)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(8);
		}	
	}
	
	/*发送从设备的地址 ，并且设置为读方向*/
	I2C_Send7bitAddress( HMC5883L_IIC,SlaveAddress,I2C_Direction_Receiver );
	
	/*重置 count_wait */
	count_wait = TIME_OUT;
	
	/*等待EV6事件，直到检测成功*/
	while(I2C_CheckEvent (HMC5883L_IIC, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(9);
		}	
	}
	/*做除非应答信号*/
	I2C_AcknowledgeConfig (HMC5883L_IIC,DISABLE); 
	
		/*重置 count_wait */
	count_wait = TIME_OUT;
	
	/*等待EV8_2事件，直到检测成功*/
	while(I2C_CheckEvent (HMC5883L_IIC, I2C_EVENT_MASTER_BYTE_RECEIVED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(10);
		}	
	}

	
	/*发送要读入的数据*/
	 readdata = I2C_ReceiveData  ( HMC5883L_IIC );  
	
	/*产生结束信号*/
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
   Single_Write(STM32_IIC_HMC5883L_ADDR,0x00,0x14);  //配置寄存器A
	 Single_Write(STM32_IIC_HMC5883L_ADDR,0x02,0x00);  //配置模式寄存器
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
