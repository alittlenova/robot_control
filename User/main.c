#include "stm32f4xx.h"
#include "./EXTI_Conf/EXTI_Conf.h"
#include "./GPIO_Conf/GPIO_Conf.h" 
#include "./NVIC_Conf/NVIC_Conf.h" 
#include "./TIM_Conf/TIM_Conf.h" 
#include "./usart/bsp_debug_usart.h"
//#include "./sdram/bsp_sdram.h"
#include "./lcd/bsp_lcd.h"
#include "./touch/gt9xx.h"
#include "./touch/palette_main_debug.h"
#include "./usart/DGPS_Usart_Conf.h"
#include "./i2c_adxl345/i2cadax.h"
#include "./global/global.h"
#include "./GPS/GPS.h"

int main(void)
{	
	GlobalInitialization();
	PWM_GPIO_Config();	
	TIM_Config();
	TIM_PWMINPUT_Config();
	
	TIM_NVIC_Config();
	TIMx_NVIC_Configuration();
	
	TIM_BASIC_Config();
	TIM_BASIC_NVIC_Configuration();
	//EXTI_Key_Config();
	//EXTI_NVIC_Config();
	DGPS_NVIC_Configuration();
	DEBUG_NVIC_Configuration();
	
	
	
  Debug_USART_Config();
	DGPS_USART_Config();
	
	//I2C ADXL
	ADXL345_IIC_Config();
	Init_ADXL345();
	read_ADXL345();
//	LED_BLUE;
	// 初始化触摸屏
  GTP_Init_Panel(); 
	
	//初始化液晶屏
  LCD_Init();
  LCD_LayerInit();
  LTDC_Cmd(ENABLE);
	
	//把背景层刷黑色
  LCD_SetLayer(LCD_BACKGROUND_LAYER);  
	LCD_Clear(LCD_COLOR_BLACK);
	
  //初始化后默认使用前景层
	LCD_SetLayer(LCD_FOREGROUND_LAYER); 
	//默认设置不透明	，该函数参数为不透明度，范围 0-0xff ，0为全透明，0xff为不透明
  LCD_SetTransparency(0xFF);
	LCD_Clear(LCD_COLOR_BLACK);
	
	//主界面初始化
	MAIN_DEBUG_Palette_Init();
	GPS_Init();
	while(1)
	{
		
	};
}
