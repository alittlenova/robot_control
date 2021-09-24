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
  
#include "./iic/bsp_iic_ADXL345.h"
#include "./usart/bsp_debug_usart.h"
#include  <math.h>

/*
要实现往EEPROM里面写入数据
1. 初始化硬件IIC
2. 编写往EEPROM传输数据的函数（包括读和写）
3. 利用读写函数往EEPROM写入数据，并读取进行校验





*/
uint8_t TX_DATA[4];  	 //显示据缓存区
uint8_t BUF[10];       //接收数据缓存区
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
  * @brief  ADXL345_IIC_Config 初始化GPIO及IIC的模式
  * @param  无
  * @retval 无
  */
void ADXL345_IIC_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  I2C_InitTypeDef  IIC_InitStructure;
		/*使能GPIO的时钟*/
  RCC_AHB1PeriphClockCmd(ADXL345_IIC_SCL_GPIO_CLK|ADXL345_IIC_SDA_GPIO_CLK,ENABLE);

  /* 使能 IIC 时钟 */
  RCC_APB1PeriphClockCmd(ADXL345_IIC_CLK, ENABLE);
	
	 /* 连接 PXx 到 IIC*/
  GPIO_PinAFConfig(ADXL345_IIC_SCL_GPIO_PORT,ADXL345_IIC_SCL_SOURCE,ADXL345_IIC_SCL_AF);

  /*  连接 PXx 到 IIC*/
  GPIO_PinAFConfig(ADXL345_IIC_SDA_GPIO_PORT,ADXL345_IIC_SDA_SOURCE,ADXL345_IIC_SDA_AF);
  
  /* GPIO SCL初始化 */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;//开漏输出模式
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = ADXL345_IIC_SCL_PIN  ;  
  GPIO_Init(ADXL345_IIC_SCL_GPIO_PORT, &GPIO_InitStructure);

  /* GPIO SDA 初始化 */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = ADXL345_IIC_SDA_PIN;
  GPIO_Init(ADXL345_IIC_SDA_GPIO_PORT, &GPIO_InitStructure);
  /*配置IIC寄存器 初始化IIC*/
  IIC_InitStructure.I2C_Ack = I2C_Ack_Enable  ;
  IIC_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit  ;
	IIC_InitStructure.I2C_ClockSpeed =  ADXL345_IIC_BAUDRATE  ;
	IIC_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2 ;
	IIC_InitStructure.I2C_Mode = I2C_Mode_I2C  ;
	IIC_InitStructure.I2C_OwnAddress1 = STM32_IIC_OWN_ADDR;
	
  I2C_Init (ADXL345_IIC, &IIC_InitStructure); 
  /* 使能串口 */
  I2C_Cmd(ADXL345_IIC, ENABLE);
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
	I2C_GenerateSTART(ADXL345_IIC, ENABLE);

  /*重置 count_wait */
	count_wait = TIME_OUT;
	
	/*等待EV5事件，直到检测成功*/
	while(I2C_CheckEvent (ADXL345_IIC, I2C_EVENT_MASTER_MODE_SELECT)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(1);
		}	
	}
	
	/*发送从设备的地址*/
	I2C_Send7bitAddress( ADXL345_IIC,SlaveAddress,I2C_Direction_Transmitter );
	
	/*重置 count_wait */
	count_wait = TIME_OUT;
	
	/*等待EV6事件，直到检测成功*/
	while(I2C_CheckEvent (ADXL345_IIC, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(2);
		}	
	}
	
	/*发送要写入的存储单元格地址*/
	I2C_SendData  ( ADXL345_IIC,  REG_Address );
	
		/*等待EV8_2事件，直到检测成功*/
	while(I2C_CheckEvent (ADXL345_IIC, I2C_EVENT_MASTER_BYTE_TRANSMITTED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(3);
		}	
	}
	
	/*发送要写入的数据*/
	I2C_SendData  ( ADXL345_IIC,  REG_data );
	
	/*重置 count_wait */
	count_wait = TIME_OUT;
	
	/*等待EV8_2事件，直到检测成功*/
	while(I2C_CheckEvent (ADXL345_IIC, I2C_EVENT_MASTER_BYTE_TRANSMITTED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(4);
		}	
	}

	/*产生结束信号*/
	I2C_GenerateSTOP(ADXL345_IIC, ENABLE);

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
	I2C_GenerateSTART(ADXL345_IIC, ENABLE);
	
	/*重置 count_wait */
	count_wait = TIME_OUT;
	
	/*等待EV5事件，直到检测成功*/
	while(I2C_CheckEvent (ADXL345_IIC, I2C_EVENT_MASTER_MODE_SELECT)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(5);
		}	
	}
	
	/*发送从设备的地址*/
	I2C_Send7bitAddress( ADXL345_IIC,SlaveAddress,I2C_Direction_Transmitter );
	
	/*重置 count_wait */
	count_wait = TIME_OUT;
	
	/*等待EV6事件，直到检测成功*/
	while(I2C_CheckEvent (ADXL345_IIC, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(6);
		}	
	}
  
	
	/*发送要读取的存储单元格地址*/
	I2C_SendData  ( ADXL345_IIC,  REG_Address );
	
		/*等待EV8_2事件，直到检测成功*/
	while(I2C_CheckEvent (ADXL345_IIC, I2C_EVENT_MASTER_BYTE_TRANSMITTED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(7);
		}	
	}
	
  /*产生第二次起始信号*/
	I2C_GenerateSTART(ADXL345_IIC, ENABLE);
	
		/*重置 count_wait */
	count_wait = TIME_OUT;
	
	/*等待EV5事件，直到检测成功*/
	while(I2C_CheckEvent (ADXL345_IIC, I2C_EVENT_MASTER_MODE_SELECT)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(8);
		}	
	}
	
	/*发送从设备的地址 ，并且设置为读方向*/
	I2C_Send7bitAddress( ADXL345_IIC,SlaveAddress,I2C_Direction_Receiver );
	
	/*重置 count_wait */
	count_wait = TIME_OUT;
	
	/*等待EV6事件，直到检测成功*/
	while(I2C_CheckEvent (ADXL345_IIC, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(9);
		}	
	}
	/*做除非应答信号*/
	I2C_AcknowledgeConfig (ADXL345_IIC,DISABLE); 
	
		/*重置 count_wait */
	count_wait = TIME_OUT;
	
	/*等待EV8_2事件，直到检测成功*/
	while(I2C_CheckEvent (ADXL345_IIC, I2C_EVENT_MASTER_BYTE_RECEIVED)!= SUCCESS)
	{
	 count_wait--;
		if(count_wait == 0)
		{
		return  Error_CallBack(10);
		}	
	}

	
	/*发送要读入的数据*/
	 readdata = I2C_ReceiveData  ( ADXL345_IIC );  
	
	/*产生结束信号*/
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
   Single_Write(STM32_IIC_ADXL345_ADDR,0x31,0x0B);   //测量范围,正负16g，13位模式
  // Single_Write(ADXL345_Addr,0x2C,0x0e);   //速率设定为100hz 参考pdf13页
   Single_Write(STM32_IIC_ADXL345_ADDR,0x2D,0x08);   //选择电源模式   参考pdf24页
   Single_Write(STM32_IIC_ADXL345_ADDR,0x2E,0x80);   //使能 DATA_READY 中断
  // Single_Write(ADXL345_Addr,0x1E,0x00);   //X 偏移量 根据测试传感器的状态写入pdf29页
  // Single_Write(ADXL345_Addr,0x1F,0x00);   //Y 偏移量 根据测试传感器的状态写入pdf29页
  // Single_Write(ADXL345_Addr,0x20,0x05);   //Z 偏移量 根据测试传感器的状态写入pdf29页
}
void read_ADXL345(void)
{
     BUF[0]=Single_Read(STM32_IIC_ADXL345_ADDR,0x32);//OUT_X_L_A
     BUF[1]=Single_Read(STM32_IIC_ADXL345_ADDR,0x33);//OUT_X_H_A

	   BUF[2]=Single_Read(STM32_IIC_ADXL345_ADDR,0x34);//OUT_Y_L_A
     BUF[3]=Single_Read(STM32_IIC_ADXL345_ADDR,0x35);//OUT_Y_H_A

	   BUF[4]=Single_Read(STM32_IIC_ADXL345_ADDR,0x36);//OUT_Z_L_A
     BUF[5]=Single_Read(STM32_IIC_ADXL345_ADDR,0x37);//OUT_Z_H_A

	   A_X=(BUF[1]<<8)+BUF[0];  //合成数据  
	   A_Y=(BUF[3]<<8)+BUF[2];  //合成数据
	   A_Z=(BUF[5]<<8)+BUF[4];  //合成数据
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
        temp=dis_data*3.9;  //计算数据和显示,查考ADXL345快速入门第4页
        conversion(temp);          //转换出显示需要的数据	 
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
