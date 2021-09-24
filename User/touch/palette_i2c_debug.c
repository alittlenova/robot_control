/**
  ******************************************************************************
  * @file    palette.c
  * @author  WT
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   主界面函数
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include "./touch/palette.h"
#include "./touch/palette_main_debug.h"
#include "./touch/palette_i2c_debug.h"
#include "./touch/gt9xx.h"
#include "./lcd/bsp_lcd.h"
#include "./led/bsp_led.h"
#include "./global/global.h"
#include "./TIM_Conf/TIM_Conf.h" 
#include "./i2c_adxl345/i2cadax.h"
#include "./string/string.h"


static void Draw_Command_Button(void *btn);
static void Command_Send_Info(void *btn);
static void I2C_DEBUG_Display_Info(void);



/**
* @brief  Palette_Init 画板初始化
* @param  无
* @retval 无
*/
void I2C_DEBUG_Palette_Init(void)
{
  
  uint8_t i;
	
  // 整屏清为灰色
  //LCD_Clear(CL_WHITE);
	LCD_Clear(CL_BUTTON_GREY);
  
	//显示界面
	LCD_SetColors(CL_RED,CL_BUTTON_GREY);
	//选择字体，使用中英文显示时，尽量把英文选择成16*24的字体，
	//中文字体大小是24*24的，需要其它字体请自行制作字模
	//这个函数只对英文字体起作用
	LCD_SetFont(&Font16x24);
  LCD_DispString_EN_CH( 5,
												300,                     
												(uint8_t*)"i2c操作界面");
	
  // 初始化按钮
	button_n=2;
  I2C_DEBUG_Touch_Button_Init();
  
  // 描绘按钮
  for(i=0;i<button_n;i++)
  {
    button[i].draw_btn(&button[i]);
  }
  
	I2C_DEBUG_Display_Info();

}




/**
* @brief  Touch_Button_Init 初始化按钮参数
* @param  无
* @retval 无
*/
void I2C_DEBUG_Touch_Button_Init(void)
{
  //第一列按钮
  button[0].start_x = MAIN_BUTTON_START_X;
  button[0].start_y = 0;
  button[0].end_x = MAIN_BUTTON_START_X+MAIN_BLOCK_WIDTH ;
  button[0].end_y = MAIN_BLOCK_HEIGHT;
	button[0].para = 0;
  button[0].touch_flag = 0; 
	button[0].draw_btn = Draw_Command_Button ;
	button[0].btn_command = Command_Send_Info ;
  
  button[1].start_x = MAIN_BUTTON_START_X;
  button[1].start_y = MAIN_BLOCK_HEIGHT;
  button[1].end_x = MAIN_BUTTON_START_X+MAIN_BLOCK_WIDTH ;
  button[1].end_y = MAIN_BLOCK_HEIGHT*2;
	button[1].para = 1;
  button[1].touch_flag = 0;  
	button[1].draw_btn = Draw_Command_Button ;
  button[1].btn_command = Command_Send_Info ;
/*	
  button[2].start_x = MAIN_BUTTON_START_X;
  button[2].start_y = MAIN_BLOCK_HEIGHT*2;
  button[2].end_x = MAIN_BUTTON_START_X+MAIN_BLOCK_WIDTH ;
  button[2].end_y = MAIN_BLOCK_HEIGHT*3;
	button[2].para = 2;
  button[2].touch_flag = 0;  
	button[2].draw_btn = Draw_Command_Button ;
  button[2].btn_command = Command_Send_Info ;
	
  button[3].start_x = MAIN_BUTTON_START_X;
  button[3].start_y = MAIN_BLOCK_HEIGHT*3;
  button[3].end_x = MAIN_BUTTON_START_X+MAIN_BLOCK_WIDTH ;
  button[3].end_y = MAIN_BLOCK_HEIGHT*4;
	button[3].para = 3;
  button[3].touch_flag = 0;  
	button[3].draw_btn = Draw_Command_Button ;
  button[3].btn_command = Command_Send_Info ;
	
  button[4].start_x = MAIN_BUTTON_START_X;
  button[4].start_y = MAIN_BLOCK_HEIGHT*4;
  button[4].end_x = MAIN_BUTTON_START_X+MAIN_BLOCK_WIDTH ;
  button[4].end_y = MAIN_BLOCK_HEIGHT*5;
  button[4].para = 4;
  button[4].touch_flag = 0;  
	button[4].draw_btn = Draw_Command_Button ;
	button[4].btn_command = Command_Send_Info ;
  
  button[5].start_x = MAIN_BUTTON_START_X;
  button[5].start_y = MAIN_BLOCK_HEIGHT*5;
  button[5].end_x = MAIN_BUTTON_START_X+MAIN_BLOCK_WIDTH ;
  button[5].end_y = MAIN_BLOCK_HEIGHT*6;
  button[5].para = 5;
  button[5].touch_flag = 0;  
	button[5].draw_btn = Draw_Command_Button ;
	button[5].btn_command = Command_Send_Info ;
  
  button[6].start_x = MAIN_BUTTON_START_X;
  button[6].start_y = MAIN_BLOCK_HEIGHT*6;
  button[6].end_x = MAIN_BUTTON_START_X+MAIN_BLOCK_WIDTH ;
  button[6].end_y = MAIN_BLOCK_HEIGHT*7;
  button[6].para = 6;
  button[6].touch_flag = 0;  
	button[6].draw_btn = Draw_Command_Button ;
	button[6].btn_command = Command_Send_Info ;
  
  button[7].start_x = MAIN_BUTTON_START_X;
  button[7].start_y = MAIN_BLOCK_HEIGHT*7;
  button[7].end_x = MAIN_BUTTON_START_X+MAIN_BLOCK_WIDTH ;
  button[7].end_y = MAIN_BLOCK_HEIGHT*8;
  button[7].para = 7;
  button[7].touch_flag = 0;  
	button[7].draw_btn = Draw_Command_Button ;
	button[7].btn_command = Command_Send_Info ;
  
  button[8].start_x = MAIN_BUTTON_START_X;
  button[8].start_y = MAIN_BLOCK_HEIGHT*8;
  button[8].end_x = MAIN_BUTTON_START_X+MAIN_BLOCK_WIDTH ;
  button[8].end_y = LCD_PIXEL_HEIGHT;
  button[8].para = 8;
  button[8].touch_flag = 0;  
	button[8].draw_btn = Draw_Command_Button ;
	button[8].btn_command = Command_Send_Info ;
  
  
  
	//第二列按钮
  
	button[9].start_x = MAIN_BUTTON_START_X + MAIN_BLOCK_WIDTH;
  button[9].start_y = 0;
  button[9].end_x = MAIN_BUTTON_START_X+MAIN_BLOCK_WIDTH*2 ;
  button[9].end_y = MAIN_BLOCK_HEIGHT;
  button[9].para = LINE_SINGLE_PIXCEL;
  button[9].touch_flag = 0;  
  button[9].draw_btn = Draw_Shape_Button ;
  button[9].btn_command = Command_Select_Brush ;
  
  button[10].start_x = MAIN_BUTTON_START_X + MAIN_BLOCK_WIDTH;
  button[10].start_y = MAIN_BLOCK_HEIGHT;
  button[10].end_x = MAIN_BUTTON_START_X+MAIN_BLOCK_WIDTH*2 ;
  button[10].end_y = MAIN_BLOCK_HEIGHT*2;
  button[10].para = LINE_2_PIXCEL;
  button[10].touch_flag = 0;  
  button[10].draw_btn = Draw_Shape_Button ;
  button[10].btn_command = Command_Select_Brush ;
  
  button[11].start_x = MAIN_BUTTON_START_X + MAIN_BLOCK_WIDTH;
  button[11].start_y = MAIN_BLOCK_HEIGHT*2;
  button[11].end_x = MAIN_BUTTON_START_X+MAIN_BLOCK_WIDTH*2 ;
  button[11].end_y = MAIN_BLOCK_HEIGHT*3;
  button[11].para = LINE_4_PIXCEL;
  button[11].touch_flag = 0;  
  button[11].draw_btn = Draw_Shape_Button ;
  button[11].btn_command = Command_Select_Brush ;
  
  button[12].start_x = MAIN_BUTTON_START_X + MAIN_BLOCK_WIDTH;
  button[12].start_y = MAIN_BLOCK_HEIGHT*3;
  button[12].end_x = MAIN_BUTTON_START_X+MAIN_BLOCK_WIDTH*2 ;
  button[12].end_y = MAIN_BLOCK_HEIGHT*4;
  button[12].para = LINE_6_PIXCEL;
  button[12].touch_flag = 0;  
  button[12].draw_btn = Draw_Shape_Button ;
  button[12].btn_command = Command_Select_Brush ;
  
  button[13].start_x = MAIN_BUTTON_START_X + MAIN_BLOCK_WIDTH;
  button[13].start_y = MAIN_BLOCK_HEIGHT*4;
  button[13].end_x = MAIN_BUTTON_START_X+MAIN_BLOCK_WIDTH*2 ;
  button[13].end_y = MAIN_BLOCK_HEIGHT*5;
  button[13].para = LINE_8_PIXCEL;
  button[13].touch_flag = 0;  
  button[13].draw_btn = Draw_Shape_Button ;
  button[13].btn_command = Command_Select_Brush ;
  
  button[14].start_x = MAIN_BUTTON_START_X + MAIN_BLOCK_WIDTH;
  button[14].start_y = MAIN_BLOCK_HEIGHT*5;
  button[14].end_x = MAIN_BUTTON_START_X+MAIN_BLOCK_WIDTH*2 ;
  button[14].end_y = MAIN_BLOCK_HEIGHT*6;
  button[14].para = LINE_16_PIXCEL;
  button[14].touch_flag = 0;  
  button[14].draw_btn = Draw_Shape_Button ;
  button[14].btn_command = Command_Select_Brush ;
  
  button[15].start_x = MAIN_BUTTON_START_X + MAIN_BLOCK_WIDTH;
  button[15].start_y = MAIN_BLOCK_HEIGHT*6;
  button[15].end_x = MAIN_BUTTON_START_X+MAIN_BLOCK_WIDTH*2 ;
  button[15].end_y = MAIN_BLOCK_HEIGHT*7;
  button[15].para = LINE_20_PIXCEL;
  button[15].touch_flag = 0;  
  button[15].draw_btn = Draw_Shape_Button ;
  button[15].btn_command = Command_Select_Brush ;   
  
  button[16].start_x = MAIN_BUTTON_START_X + MAIN_BLOCK_WIDTH;
  button[16].start_y = MAIN_BLOCK_HEIGHT*7;
  button[16].end_x = MAIN_BUTTON_START_X+MAIN_BLOCK_WIDTH*2 ;
  button[16].end_y = MAIN_BLOCK_HEIGHT*8;
  button[16].para = LINE_WITH_CIRCLE;
  button[16].touch_flag = 0;  
  button[16].draw_btn = Draw_Shape_Button ;
  button[16].btn_command = Command_Select_Brush ;
  
  button[17].start_x = MAIN_BUTTON_START_X + MAIN_BLOCK_WIDTH;
  button[17].start_y = MAIN_BLOCK_HEIGHT*8;
  button[17].end_x = MAIN_BUTTON_START_X+MAIN_BLOCK_WIDTH*2 ;
  button[17].end_y = LCD_PIXEL_HEIGHT;
  button[17].para = RUBBER;
  button[17].touch_flag = 0;  
  button[17].draw_btn = Draw_Shape_Button ;
  button[17].btn_command = Command_Select_Brush ;
*/
}

/**
* @brief  Draw_Command_Button 画出按钮图样
* @param  btn Touch_Button 类型的按键参数
* @retval 无
*/
static void Draw_Command_Button(void *btn)
{
	 Touch_Button *ptr = (Touch_Button *)btn;
  
  //释放按键
  if(ptr->touch_flag == 0)
  {
		LCD_SetColors(CL_BUTTON_GREY,CL_WHITE);
    LCD_DrawFullRect(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y);
		//按钮边框
		LCD_SetColors(CL_BLUE4,CL_WHITE);
    LCD_DrawRect(ptr->start_x,
									ptr->start_y,
									ptr->end_x - ptr->start_x,
									ptr->end_y - ptr->start_y);
		LCD_SetColors(CL_RED,CL_BUTTON_GREY);
		//选择字体，使用中英文显示时，尽量把英文选择成16*24的字体，
		//中文字体大小是24*24的，需要其它字体请自行制作字模
		//这个函数只对英文字体起作用
		LCD_SetFont(&Font16x24);
		
  }
  else  //按键按下
  {
    //白色背景
		LCD_SetColors(CL_WHITE,CL_WHITE);
    LCD_DrawFullRect(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y);
		//按钮边框
		LCD_SetColors(CL_BLUE4,CL_WHITE);
    LCD_DrawRect(ptr->start_x,
									ptr->start_y,
									ptr->end_x - ptr->start_x,
									ptr->end_y - ptr->start_y);
		LCD_SetColors(CL_RED,CL_WHITE);
		//选择字体，使用中英文显示时，尽量把英文选择成16*24的字体，
		//中文字体大小是24*24的，需要其它字体请自行制作字模
		//这个函数只对英文字体起作用
		LCD_SetFont(&Font16x24);
  } 
		switch(ptr->para)
		{
			case 0:
				{
					LCD_DispString_EN_CH( ptr->start_y+10,
															ptr->start_x + (ptr->end_x - ptr->start_x - 24*2 )/2,                     
															(uint8_t*)"按键1");
					break;
				}
			case 1:
				{
					LCD_DispString_EN_CH( ptr->start_y+10,
															ptr->start_x + (ptr->end_x - ptr->start_x - 24*2 )/2,                     
															(uint8_t*)"主调试");
					break;
				}
			case 2:
				{
					break;
				}
			case 3:
				{
					break;
				}
			case 4:
				{
					break;
				}
			case 5:
				{
					break;
				}
			case 6:
				{
					break;
				}
			case 7:
				{
					break;
				}
			case 8:
				{
					break;
				}
				default:
					break;
		}
}

/**
* @brief  Command_Send_Info 按钮执行操作
* @param  btn Touch_Button 类型的按键参数
* @retval 无
*/
static void Command_Send_Info(void *btn)
{
	Touch_Button *ptr = (Touch_Button *)btn;
	switch(ptr->para)
	{	
		case 0:
		{
			//进入电机调试界面
			//PWM_DEBUG_Palette_Init();
			break;
		}
		
		case 1:
		{
			//进入主调试界面
			MAIN_DEBUG_Palette_Init();
			break;
		}
		default:
			break;

	}
}


/**
* @brief  Command_Send_Info 按钮执行操作
* @param  无
* @retval 无
*/
static void I2C_DEBUG_Display_Info(void)
{
			//先清屏
			LCD_SetColors(CL_BUTTON_GREY,CL_BUTTON_GREY);
			LCD_DrawFullRect(MAIN_PALETTE_START_X,
												MAIN_PALETTE_START_Y,                    
												MAIN_PALETTE_END_X-(MAIN_PALETTE_START_X+1), 
												MAIN_PALETTE_END_Y-MAIN_PALETTE_START_Y );
				//显示语句1
			clear_output_string();
			my_strcat(Output_String,"I2C数据x加速度: ");
			A_Xout=1000;
			myitoa(A_Xout, NUMBER, 10);
			my_strcat(Output_String,NUMBER);
			//my_strcat(Output_String,"%");
			LCD_SetColors(CL_RED,CL_BUTTON_GREY);
			LCD_SetFont(&Font16x24);
			LCD_DispString_EN_CH( 150,
														200,                     
			Output_String);
			//显示语句1
			clear_output_string();
			my_strcat(Output_String,"I2C数据x加速度: ");
			//
			A_X=-1000;
			myitoa(A_X, NUMBER, 10);
			my_strcat(Output_String,NUMBER);
			//my_strcat(Output_String,"%");
			LCD_SetColors(CL_RED,CL_BUTTON_GREY);
			LCD_SetFont(&Font16x24);
			LCD_DispString_EN_CH( 200,
														200,                     
			Output_String);
}
/* ------------------------------------------end of file---------------------------------------- */


