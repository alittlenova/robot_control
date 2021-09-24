/**
  ******************************************************************************
  * @file    palette.c
  * @author  WT
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   GPS���Խ���������
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include "./touch/palette.h"
#include "./touch/palette_gps_satellite.h"
#include "./touch/palette_main_debug.h"
#include "./touch/gt9xx.h"
#include "./lcd/bsp_lcd.h"
#include "./led/bsp_led.h"
#include "./global/global.h"
#include "./TIM_Conf/TIM_Conf.h" 
#include "./usart/DGPS_Usart_Conf.h"
#include "./usart/bsp_debug_usart.h"
#include "./string/string.h"

static void Draw_Command_Button(void *btn);
static void Command_Send_Info(void *btn);
static void GPS_DEBUG_Display_Info(void);

/**
* @brief  Palette_Init �����ʼ��
* @param  ��
* @retval ��
*/
void GPS_SATELLITE_Palette_Init(void)
{
  
  uint8_t i;
	
  // ������Ϊ��ɫ
  //LCD_Clear(CL_WHITE);
	LCD_Clear(CL_BUTTON_GREY);
  
	//��ʾ����
	LCD_SetColors(CL_RED,CL_BUTTON_GREY);
	//ѡ�����壬ʹ����Ӣ����ʾʱ��������Ӣ��ѡ���16*24�����壬
	//���������С��24*24�ģ���Ҫ��������������������ģ
	//�������ֻ��Ӣ������������
	LCD_SetFont(&Font16x24);
  LCD_DispString_EN_CH( 5,
												300,                     
												(uint8_t*)"GPS���Խ���");
	
  // ��ʼ����ť
	button_n=9;
  GPS_DEBUG_Touch_Button_Init();
  
  // ��水ť
  for(i=0;i<button_n;i++)
  {
    button[i].draw_btn(&button[i]);
  }
  
	GPS_SATELLITE_Display_Info();

}




/**
* @brief  Touch_Button_Init ��ʼ����ť����
* @param  ��
* @retval ��
*/
void GPS_SATELLITE_Touch_Button_Init(void)
{
  //��һ�а�ť
  button[0].start_x = GPS_BUTTON_START_X;
  button[0].start_y = 0;
  button[0].end_x = GPS_BUTTON_START_X+GPS_BLOCK_WIDTH ;
  button[0].end_y = GPS_BLOCK_HEIGHT;
	button[0].para = 0;
  button[0].touch_flag = 0; 
	button[0].draw_btn = Draw_Command_Button ;
	button[0].btn_command = Command_Send_Info ;
  
  button[1].start_x = GPS_BUTTON_START_X;
  button[1].start_y = GPS_BLOCK_HEIGHT;
  button[1].end_x = GPS_BUTTON_START_X+GPS_BLOCK_WIDTH ;
  button[1].end_y = GPS_BLOCK_HEIGHT*2;
	button[1].para = 1;
  button[1].touch_flag = 0;  
	button[1].draw_btn = Draw_Command_Button ;
  button[1].btn_command = Command_Send_Info ;
	
  button[2].start_x = GPS_BUTTON_START_X;
  button[2].start_y = GPS_BLOCK_HEIGHT*2;
  button[2].end_x = GPS_BUTTON_START_X+GPS_BLOCK_WIDTH ;
  button[2].end_y = GPS_BLOCK_HEIGHT*3;
	button[2].para = 2;
  button[2].touch_flag = 0;  
	button[2].draw_btn = Draw_Command_Button ;
  button[2].btn_command = Command_Send_Info ;
	
  button[3].start_x = GPS_BUTTON_START_X;
  button[3].start_y = GPS_BLOCK_HEIGHT*3;
  button[3].end_x = GPS_BUTTON_START_X+GPS_BLOCK_WIDTH ;
  button[3].end_y = GPS_BLOCK_HEIGHT*4;
	button[3].para = 3;
  button[3].touch_flag = 0;  
	button[3].draw_btn = Draw_Command_Button ;
  button[3].btn_command = Command_Send_Info ;
	
  button[4].start_x = GPS_BUTTON_START_X;
  button[4].start_y = GPS_BLOCK_HEIGHT*4;
  button[4].end_x = GPS_BUTTON_START_X+GPS_BLOCK_WIDTH ;
  button[4].end_y = GPS_BLOCK_HEIGHT*5;
  button[4].para = 4;
  button[4].touch_flag = 0;  
	button[4].draw_btn = Draw_Command_Button ;
	button[4].btn_command = Command_Send_Info ;
  
  button[5].start_x = GPS_BUTTON_START_X;
  button[5].start_y = GPS_BLOCK_HEIGHT*5;
  button[5].end_x = GPS_BUTTON_START_X+GPS_BLOCK_WIDTH ;
  button[5].end_y = GPS_BLOCK_HEIGHT*6;
  button[5].para = 5;
  button[5].touch_flag = 0;  
	button[5].draw_btn = Draw_Command_Button ;
	button[5].btn_command = Command_Send_Info ;
  
  button[6].start_x = GPS_BUTTON_START_X;
  button[6].start_y = GPS_BLOCK_HEIGHT*6;
  button[6].end_x = GPS_BUTTON_START_X+GPS_BLOCK_WIDTH ;
  button[6].end_y = GPS_BLOCK_HEIGHT*7;
  button[6].para = 6;
  button[6].touch_flag = 0;  
	button[6].draw_btn = Draw_Command_Button ;
	button[6].btn_command = Command_Send_Info ;
  
  button[7].start_x = GPS_BUTTON_START_X;
  button[7].start_y = GPS_BLOCK_HEIGHT*7;
  button[7].end_x = GPS_BUTTON_START_X+GPS_BLOCK_WIDTH ;
  button[7].end_y = GPS_BLOCK_HEIGHT*8;
  button[7].para = 7;
  button[7].touch_flag = 0;  
	button[7].draw_btn = Draw_Command_Button ;
	button[7].btn_command = Command_Send_Info ;
  
  button[8].start_x = GPS_BUTTON_START_X;
  button[8].start_y = GPS_BLOCK_HEIGHT*8;
  button[8].end_x = GPS_BUTTON_START_X+GPS_BLOCK_WIDTH ;
  button[8].end_y = LCD_PIXEL_HEIGHT;
  button[8].para = 8;
  button[8].touch_flag = 0;  
	button[8].draw_btn = Draw_Command_Button ;
	button[8].btn_command = Command_Send_Info ;
  
  
  
}

/**
* @brief  Draw_Command_Button ������ťͼ��
* @param  btn Touch_Button ���͵İ�������
* @retval ��
*/
static void Draw_Command_Button(void *btn)
{
	 Touch_Button *ptr = (Touch_Button *)btn;
  
  //�ͷŰ���
  if(ptr->touch_flag == 0)
  {
		LCD_SetColors(CL_BUTTON_GREY,CL_WHITE);
    LCD_DrawFullRect(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y);
		//��ť�߿�
		LCD_SetColors(CL_BLUE4,CL_WHITE);
    LCD_DrawRect(ptr->start_x,
									ptr->start_y,
									ptr->end_x - ptr->start_x,
									ptr->end_y - ptr->start_y);
		LCD_SetColors(CL_RED,CL_BUTTON_GREY);
		//ѡ�����壬ʹ����Ӣ����ʾʱ��������Ӣ��ѡ���16*24�����壬
		//���������С��24*24�ģ���Ҫ��������������������ģ
		//�������ֻ��Ӣ������������
		LCD_SetFont(&Font16x24);
		
  }
  else  //��������
  {
    //��ɫ����
		LCD_SetColors(CL_WHITE,CL_WHITE);
    LCD_DrawFullRect(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y);
		//��ť�߿�
		LCD_SetColors(CL_BLUE4,CL_WHITE);
    LCD_DrawRect(ptr->start_x,
									ptr->start_y,
									ptr->end_x - ptr->start_x,
									ptr->end_y - ptr->start_y);
		LCD_SetColors(CL_RED,CL_WHITE);
		//ѡ�����壬ʹ����Ӣ����ʾʱ��������Ӣ��ѡ���16*24�����壬
		//���������С��24*24�ģ���Ҫ��������������������ģ
		//�������ֻ��Ӣ������������
		LCD_SetFont(&Font16x24);
  } 
		switch(ptr->para)
		{
			case 0:
				{
					LCD_DispString_EN_CH( ptr->start_y+10,
															ptr->start_x + (ptr->end_x - ptr->start_x - 24*2 )/2,                     
															(uint8_t*)"B1");
					break;
				}
			case 1:
				{
					LCD_DispString_EN_CH( ptr->start_y+10,
															ptr->start_x + (ptr->end_x - ptr->start_x - 24*2 )/2,                     
															(uint8_t*)"B2");
					break;
				}
			case 2:
				{
					LCD_DispString_EN_CH( ptr->start_y+10,
															ptr->start_x + (ptr->end_x - ptr->start_x - 24*2 )/2,                     
															(uint8_t*)"B3");
					break;
				}
			case 3:
				{
					LCD_DispString_EN_CH( ptr->start_y+10,
															ptr->start_x + (ptr->end_x - ptr->start_x - 24*2 )/2,                     
															(uint8_t*)"B4");
					break;
				}
			case 4:
				{
					LCD_DispString_EN_CH( ptr->start_y+10,
															ptr->start_x + (ptr->end_x - ptr->start_x - 24*2 )/2,                     
															(uint8_t*)"B5");
					break;
				}
			case 5:
				{
					LCD_DispString_EN_CH( ptr->start_y+10,
															ptr->start_x + (ptr->end_x - ptr->start_x - 24*2 )/2,                     
															(uint8_t*)"B6");
					break;
				}
			case 6:
				{
					LCD_DispString_EN_CH( ptr->start_y+10,
															ptr->start_x + (ptr->end_x - ptr->start_x - 24*2 )/2,                     
															(uint8_t*)"B7");
					break;
				}
			case 7:
				{
					LCD_DispString_EN_CH( ptr->start_y+10,
															ptr->start_x + (ptr->end_x - ptr->start_x - 24*2 )/2,                     
															(uint8_t*)"B8");
					break;
				}
			case 8:
				{
					LCD_DispString_EN_CH( ptr->start_y+10,
															ptr->start_x + (ptr->end_x - ptr->start_x - 24*2 )/2,                     
															(uint8_t*)"����");
					break;
				}
				default:
					break;
		}
}

/**
* @brief  Command_Send_Info ��ťִ�в���
* @param  btn Touch_Button ���͵İ�������
* @retval ��
*/
static void Command_Send_Info(void *btn)
{
	Touch_Button *ptr = (Touch_Button *)btn;
	switch(ptr->para)
	{	
		case 0:
		{
			//Usart_SendByte( DGPS_USART, 'A');
			GPS_SATELLITE_Display_Info();
			break;
		}
		
		case 1:
		{
			//
			//Usart_SendByte( DGPS_USART, '\n');
			GPS_SATELLITE_Display_Info();
			break;
		}
		
		case 2:
		{
			//PWM����
			GPS_SATELLITE_Display_Info();
			break;
		}
		
		case 3:
		{
			//PWM����
			GPS_SATELLITE_Display_Info();
			break;
		}
		
		case 4:
		{
			//PWM����
			GPS_SATELLITE_Display_Info();
			break;
		}
		
		case 5:
		{
			//PWM����
			GPS_SATELLITE_Display_Info();
			break;
		}
		case 6:
		{
			//PWM����
			GPS_SATELLITE_Display_Info();
			break;
		}
		
		case 7:
		{
			//PWM����
			GPS_SATELLITE_Display_Info();
			break;
		}
		case 8:
		{
			GPS_SATELLITE_Display_Info();
			break;
		}
		default:
			break;
	}
}


static void GPS_SATELLITE_Display_Info(void)
{
			//������
			LCD_SetColors(CL_BUTTON_GREY,CL_BUTTON_GREY);
			LCD_DrawFullRect(GPS_PALETTE_START_X,
												GPS_PALETTE_START_Y,                    
												GPS_PALETTE_END_X-(GPS_PALETTE_START_X+1), 
												GPS_PALETTE_END_Y-GPS_PALETTE_START_Y );
			//��ʾ���1
			clear_output_string();
			my_strcat(Output_String,"GPS��Ϣ ");
			//myitoa(PWM_FL, NUMBER, 10);
			myitoa(testresult, NUMBER, 10);
			my_strcat(Output_String,NUMBER);
			my_strcat(Output_String,"%");
			my_strcat(Output_String,receive_Buff);
			
			/*
			LCD_SetColors(CL_RED,CL_BUTTON_GREY);
			LCD_SetFont(&Font16x24);
			LCD_DispString_EN_CH( 300,
														200,                     
			Output_String);*/
			//��ʾ���2
			clear_output_string();
			my_strcat(Output_String,"Real Direction: ");
			sprintf(NUMBER,"%.2lf",GPS_Data.Real_Speed_Dirc);
			my_strcat(Output_String,NUMBER);
			LCD_SetColors(CL_RED,CL_BUTTON_GREY);
			LCD_SetFont(&Font16x24);
			LCD_DispString_EN_CH( 80,
														200,                     
			Output_String);
			//��ʾ���3
			clear_output_string();
			my_strcat(Output_String,"Magnetic Direction: ");
			sprintf(NUMBER,"%.2lf",GPS_Data.Mag_Speed_Dirc);
			my_strcat(Output_String,NUMBER);
			LCD_SetColors(CL_RED,CL_BUTTON_GREY);
			LCD_SetFont(&Font16x24);
			LCD_DispString_EN_CH( 130,
														200,                     
			Output_String);
			//��ʾ���4
			clear_output_string();
			my_strcat(Output_String,"Speed: ");
			sprintf(NUMBER,"%.2lf",GPS_Data.Speed_in_kmh);
			my_strcat(Output_String,NUMBER);
			my_strcat(Output_String,"km/h");
			LCD_SetColors(CL_RED,CL_BUTTON_GREY);
			LCD_SetFont(&Font16x24);
			LCD_DispString_EN_CH( 180,
														200,                     
			Output_String);
			//��ʾ���5
			clear_output_string();
			my_strcat(Output_String,"Latitude:");
			sprintf(NUMBER,"%.2lf",GPS_Data.Latitude);
			my_strcat(Output_String,NUMBER);
			LCD_SetColors(CL_RED,CL_BUTTON_GREY);
			LCD_SetFont(&Font16x24);
			LCD_DispString_EN_CH( 230,
														200,                     
			Output_String);
			//��ʾ���6
			clear_output_string();
			my_strcat(Output_String,"Longitude:");
			sprintf(NUMBER,"%.2lf",GPS_Data.Longitude);
			my_strcat(Output_String,NUMBER);
			LCD_SetColors(CL_RED,CL_BUTTON_GREY);
			LCD_SetFont(&Font16x24);
			LCD_DispString_EN_CH( 280,
														200,                     
			Output_String);
}
/* ------------------------------------------end of file---------------------------------------- */
