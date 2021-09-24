/**
  ******************************************************************************
  * @file    palette.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ģ����ƽ��溯��
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include "./touch/palette.h"
#include "./touch/palette_template.h"
#include "./touch/gt9xx.h"
#include "./lcd/bsp_lcd.h"
#include "./led/bsp_led.h"
#include "./global/global.h"
#include "./TIM_Conf/TIM_Conf.h" 
#include "./pwm_control/pwm_control.h"

static void Draw_Color_Button(void *btn);
static void Draw_Clear_Button(void *btn);
static void Draw_Shape_Button(void *btn);
static void Draw_Command_Button(void *btn);

static void Command_Select_Color(void *btn);
static void Command_Select_Brush(void *btn);
static void Command_Clear_Palette(void *btn);
static void Command_Send_Info(void *btn);




/**
* @brief  Palette_Init �����ʼ��
* @param  ��
* @retval ��
*/
void PWM_DEBUG_Palette_Init(void)
{
  
  uint8_t i;

  /* ������Ϊ��ɫ */
  //LCD_Clear(CL_WHITE);	/* ��������ʾȫ�� */
	LCD_Clear(CL_BUTTON_GREY);
  
  /* ��ʼ����ť */
	button_n=6;
  PWM_DEBUG_Touch_Button_Init();
  
  /* ��水ť */
  for(i=0;i<BUTTON_NUM;i++)
  {
    button[i].draw_btn(&button[i]);
  }
  
	
  /* ��ʼ������ */
  brush.color = CL_BLACK;
  brush.shape = LINE_SINGLE_PIXCEL;
	
	LCD_SetTextColor(brush.color);


}




/**
* @brief  Touch_Button_Init ��ʼ����ť����
* @param  ��
* @retval ��
*/
void PWM_DEBUG_Touch_Button_Init(void)
{
  /*��һ�У���ҪΪ��ɫ��ť*/
  button[0].start_x = BUTTON_START_X;
  button[0].start_y = 0;
  button[0].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH ;
  button[0].end_y = COLOR_BLOCK_HEIGHT;
  //button[0].para = CL_BLACK;
	button[0].para = 0;
  button[0].touch_flag = 0;  
  //button[0].draw_btn = Draw_Color_Button ;
  //button[0].btn_command = Command_Select_Color ;
	button[0].draw_btn = Draw_Command_Button ;
	button[0].btn_command = Command_Send_Info ;
  
  button[1].start_x = BUTTON_START_X;
  button[1].start_y = COLOR_BLOCK_HEIGHT;
  button[1].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH ;
  button[1].end_y = COLOR_BLOCK_HEIGHT*2;
  //button[1].para = CL_GREY;
	button[1].para = 1;
  button[1].touch_flag = 0;  
  //button[1].draw_btn = Draw_Color_Button ;
  //button[1].btn_command = Command_Select_Color ;
	button[1].draw_btn = Draw_Command_Button ;
  button[1].btn_command = Command_Send_Info ;
	
  button[2].start_x = BUTTON_START_X;
  button[2].start_y = COLOR_BLOCK_HEIGHT*2;
  button[2].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH ;
  button[2].end_y = COLOR_BLOCK_HEIGHT*3;
  //button[2].para = CL_BLUE;
	button[2].para = 2;
  button[2].touch_flag = 0;  
  //button[2].draw_btn = Draw_Color_Button ;
  //button[2].btn_command = Command_Select_Color ;
	button[2].draw_btn = Draw_Command_Button ;
  button[2].btn_command = Command_Send_Info ;
	
  button[3].start_x = BUTTON_START_X;
  button[3].start_y = COLOR_BLOCK_HEIGHT*3;
  button[3].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH ;
  button[3].end_y = COLOR_BLOCK_HEIGHT*4;
  //button[3].para = CL_BLUE2;
	button[3].para = 3;
  button[3].touch_flag = 0;  
  //button[3].draw_btn = Draw_Color_Button ;
  //button[3].btn_command = Command_Select_Color ;
	button[3].draw_btn = Draw_Command_Button ;
  button[3].btn_command = Command_Send_Info ;
	
  button[4].start_x = BUTTON_START_X;
  button[4].start_y = COLOR_BLOCK_HEIGHT*4;
  button[4].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH ;
  button[4].end_y = COLOR_BLOCK_HEIGHT*5;
  button[4].para = 4;
  button[4].touch_flag = 0;  
  //button[4].draw_btn = Draw_Color_Button ;
  //button[4].btn_command = Command_Select_Color ;
	button[4].draw_btn = Draw_Command_Button ;
	button[4].btn_command = Command_Send_Info ;
  
  button[5].start_x = BUTTON_START_X;
  button[5].start_y = COLOR_BLOCK_HEIGHT*5;
  button[5].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH ;
  button[5].end_y = COLOR_BLOCK_HEIGHT*6;
  button[5].para = 5;
  button[5].touch_flag = 0;  
  //button[5].draw_btn = Draw_Color_Button ;
  //button[5].btn_command = Command_Select_Color ;
	button[5].draw_btn = Draw_Command_Button ;
	button[5].btn_command = Command_Send_Info ;
/*  
  button[6].start_x = BUTTON_START_X;
  button[6].start_y = COLOR_BLOCK_HEIGHT*6;
  button[6].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH ;
  button[6].end_y = COLOR_BLOCK_HEIGHT*7;
  button[6].para = CL_GREEN;
  button[6].touch_flag = 0;  
  button[6].draw_btn = Draw_Color_Button ;
  button[6].btn_command = Command_Select_Color ;
  
  button[7].start_x = BUTTON_START_X;
  button[7].start_y = COLOR_BLOCK_HEIGHT*7;
  button[7].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH ;
  button[7].end_y = COLOR_BLOCK_HEIGHT*8;
  button[7].para = CL_CYAN;
  button[7].touch_flag = 0;  
  button[7].draw_btn = Draw_Color_Button ;
  button[7].btn_command = Command_Select_Color ;
  
  button[8].start_x = BUTTON_START_X;
  button[8].start_y = COLOR_BLOCK_HEIGHT*8;
  button[8].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH ;
  button[8].end_y = LCD_PIXEL_HEIGHT;
  button[8].para = CL_BUTTON_GREY;
  button[8].touch_flag = 0;  
  button[8].draw_btn = Draw_Clear_Button ;
  button[8].btn_command = Command_Clear_Palette ;
  */
  
  
  /*�ڶ��У���ҪΪ��ˢ��ť*/
/*  button[9].start_x = BUTTON_START_X + COLOR_BLOCK_WIDTH;
  button[9].start_y = 0;
  button[9].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH*2 ;
  button[9].end_y = COLOR_BLOCK_HEIGHT;
  button[9].para = LINE_SINGLE_PIXCEL;
  button[9].touch_flag = 0;  
  button[9].draw_btn = Draw_Shape_Button ;
  button[9].btn_command = Command_Select_Brush ;
  
  button[10].start_x = BUTTON_START_X + COLOR_BLOCK_WIDTH;
  button[10].start_y = COLOR_BLOCK_HEIGHT;
  button[10].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH*2 ;
  button[10].end_y = COLOR_BLOCK_HEIGHT*2;
  button[10].para = LINE_2_PIXCEL;
  button[10].touch_flag = 0;  
  button[10].draw_btn = Draw_Shape_Button ;
  button[10].btn_command = Command_Select_Brush ;
  
  button[11].start_x = BUTTON_START_X + COLOR_BLOCK_WIDTH;
  button[11].start_y = COLOR_BLOCK_HEIGHT*2;
  button[11].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH*2 ;
  button[11].end_y = COLOR_BLOCK_HEIGHT*3;
  button[11].para = LINE_4_PIXCEL;
  button[11].touch_flag = 0;  
  button[11].draw_btn = Draw_Shape_Button ;
  button[11].btn_command = Command_Select_Brush ;
  
  button[12].start_x = BUTTON_START_X + COLOR_BLOCK_WIDTH;
  button[12].start_y = COLOR_BLOCK_HEIGHT*3;
  button[12].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH*2 ;
  button[12].end_y = COLOR_BLOCK_HEIGHT*4;
  button[12].para = LINE_6_PIXCEL;
  button[12].touch_flag = 0;  
  button[12].draw_btn = Draw_Shape_Button ;
  button[12].btn_command = Command_Select_Brush ;
  
  button[13].start_x = BUTTON_START_X + COLOR_BLOCK_WIDTH;
  button[13].start_y = COLOR_BLOCK_HEIGHT*4;
  button[13].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH*2 ;
  button[13].end_y = COLOR_BLOCK_HEIGHT*5;
  button[13].para = LINE_8_PIXCEL;
  button[13].touch_flag = 0;  
  button[13].draw_btn = Draw_Shape_Button ;
  button[13].btn_command = Command_Select_Brush ;
  
  button[14].start_x = BUTTON_START_X + COLOR_BLOCK_WIDTH;
  button[14].start_y = COLOR_BLOCK_HEIGHT*5;
  button[14].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH*2 ;
  button[14].end_y = COLOR_BLOCK_HEIGHT*6;
  button[14].para = LINE_16_PIXCEL;
  button[14].touch_flag = 0;  
  button[14].draw_btn = Draw_Shape_Button ;
  button[14].btn_command = Command_Select_Brush ;
  
  button[15].start_x = BUTTON_START_X + COLOR_BLOCK_WIDTH;
  button[15].start_y = COLOR_BLOCK_HEIGHT*6;
  button[15].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH*2 ;
  button[15].end_y = COLOR_BLOCK_HEIGHT*7;
  button[15].para = LINE_20_PIXCEL;
  button[15].touch_flag = 0;  
  button[15].draw_btn = Draw_Shape_Button ;
  button[15].btn_command = Command_Select_Brush ;   
  
  button[16].start_x = BUTTON_START_X + COLOR_BLOCK_WIDTH;
  button[16].start_y = COLOR_BLOCK_HEIGHT*7;
  button[16].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH*2 ;
  button[16].end_y = COLOR_BLOCK_HEIGHT*8;
  button[16].para = LINE_WITH_CIRCLE;
  button[16].touch_flag = 0;  
  button[16].draw_btn = Draw_Shape_Button ;
  button[16].btn_command = Command_Select_Brush ;
  
  button[17].start_x = BUTTON_START_X + COLOR_BLOCK_WIDTH;
  button[17].start_y = COLOR_BLOCK_HEIGHT*8;
  button[17].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH*2 ;
  button[17].end_y = LCD_PIXEL_HEIGHT;
  button[17].para = RUBBER;
  button[17].touch_flag = 0;  
  button[17].draw_btn = Draw_Shape_Button ;
  button[17].btn_command = Command_Select_Brush ;
*/
}

/**
* @brief  Draw_Color_Button ��ɫ��ť����溯��
* @param  btn Touch_Button ���͵İ�������
* @retval ��
*/
static void Draw_Color_Button(void *btn)
{
  Touch_Button *ptr = (Touch_Button *)btn;
  
  /*�ͷŰ���*/
  if(ptr->touch_flag == 0)
  {
		/*����Ϊ���ܼ���Ӧ����ɫ*/
		//LCD_SetColors(ptr->para,CL_WHITE);
		LCD_SetColors(CL_BUTTON_GREY,CL_WHITE);
    LCD_DrawFullRect(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y);
  }
  else  /*��������*/
  {
    /*��ɫ����*/
		LCD_SetColors(CL_WHITE,CL_WHITE);
    LCD_DrawFullRect(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y);
  } 
    /*��ť�߿�*/
		LCD_SetColors(CL_BLUE4,CL_WHITE);
    LCD_DrawRect(ptr->start_x,
									ptr->start_y,
									ptr->end_x - ptr->start_x,
									ptr->end_y - ptr->start_y);
  
}


/**
* @brief  Draw_Clear_Button ������ť����溯��
* @param  btn Touch_Button ���͵İ�������
* @retval ��
*/
static void Draw_Clear_Button(void *btn)
{
  Touch_Button *ptr = (Touch_Button *)btn;
    
  /*�ͷŰ���*/
  if(ptr->touch_flag == 0)
  {
	
		LCD_SetColors(CL_BUTTON_GREY,CL_WHITE);
    LCD_DrawFullRect(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y);
    

		
		LCD_SetColors(CL_RED,CL_BUTTON_GREY);
		//ѡ�����壬ʹ����Ӣ����ʾʱ��������Ӣ��ѡ���16*24�����壬
		//���������С��24*24�ģ���Ҫ��������������������ģ
		//�������ֻ��Ӣ������������
		LCD_SetFont(&Font8x12);
    LCD_DispString_EN_CH( ptr->start_y+30,
														ptr->start_x + (ptr->end_x - ptr->start_x - 24*2 )/2,                     
														(uint8_t*)"Clear");
  }
  else  /*��������*/
  {
		
		LCD_SetColors(CL_WHITE,CL_WHITE);
    LCD_DrawFullRect(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y);
    
		
		LCD_SetColors(CL_RED,CL_WHITE);
		/*ѡ�����壬ʹ����Ӣ����ʾʱ��������Ӣ��ѡ���16*24�����壬
		*���������С��24*24�ģ���Ҫ��������������������ģ*/
		/*�������ֻ��Ӣ������������*/
		LCD_SetFont(&Font8x12);
    LCD_DispString_EN_CH( ptr->start_y+30,
														ptr->start_x + (ptr->end_x - ptr->start_x - 24*2 )/2,                     
														(uint8_t*)"Clear");
  } 
  
     /*��ť�߿�*/
		LCD_SetColors(CL_BLUE4,CL_WHITE);
    LCD_DrawRect(ptr->start_x,
										ptr->start_y,
										ptr->end_x - ptr->start_x,
										ptr->end_y - ptr->start_y);
  
}
static void Draw_Shape_Button(void *btn)
{
  Touch_Button *ptr = (Touch_Button *)btn;
  
   uint16_t i;
  
    /* ������ɫ û����ʱΪ��ɫ������ʱΪ��ɫ*/                  
    if(ptr->touch_flag ==0 )
    {
			
			LCD_SetColors(CL_BUTTON_GREY,CL_WHITE);
			LCD_DrawFullRect(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y);
      

			 /*��ʾ����ʱ�ı�����ɫ*/     
			LCD_SetColors(CL_BLUE4,CL_BUTTON_GREY);
			LCD_DrawRect(ptr->start_x,
										ptr->start_y,
										ptr->end_x - ptr->start_x,
										ptr->end_y - ptr->start_y);

    }
    else
    {

			LCD_SetColors(CL_WHITE,CL_WHITE);
			LCD_DrawFullRect(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y);
      

			 /*��ʾ����ʱ�ı�����ɫ*/     
			LCD_SetColors(CL_BLUE4,CL_WHITE);
			LCD_DrawRect(ptr->start_x,
										ptr->start_y,
										ptr->end_x - ptr->start_x,
										ptr->end_y - ptr->start_y);
    }
  
	LCD_SetColors(CL_BLACK,CL_WHITE);	
  /*���ݻ�ˢ��״��水ťͼ��*/
 switch(ptr->para)
  {
    		/*
    case LINE_SINGLE_PIXCEL:      
     		
				LCD_SetColors(CL_BLACK,CL_WHITE);
        LCD_DrawUniLine(ptr->start_x+20,
                          ptr->start_y+(ptr->end_y-ptr->start_y)/2,
                          ptr->end_x-20,
                          ptr->start_y+(ptr->end_y-ptr->start_y)/2);
      
      break;   

      
    case LINE_2_PIXCEL:
        
        LCD_DrawUniLineCircle(ptr->start_x+20,
                          ptr->start_y+(ptr->end_y-ptr->start_y)/2,ptr->end_x-20,
                          ptr->start_y+(ptr->end_y-ptr->start_y)/2,
                          1);
 
    
      break;
        
    case LINE_4_PIXCEL:
   
            LCD_DrawUniLineCircle(ptr->start_x+20,
                          ptr->start_y+(ptr->end_y-ptr->start_y)/2,ptr->end_x-20,
                          ptr->start_y+(ptr->end_y-ptr->start_y)/2,
                          2);
 
    
      break;
    
        case LINE_6_PIXCEL:
        
        LCD_DrawUniLineCircle(ptr->start_x+20,
                          ptr->start_y+(ptr->end_y-ptr->start_y)/2,ptr->end_x-20,
                          ptr->start_y+(ptr->end_y-ptr->start_y)/2,
                          3);
 
    
      break;
        
     case LINE_8_PIXCEL:
   
            LCD_DrawUniLineCircle(ptr->start_x+20,
                          ptr->start_y+(ptr->end_y-ptr->start_y)/2,ptr->end_x-20,
                          ptr->start_y+(ptr->end_y-ptr->start_y)/2,
                          4);
 
    
      break;
    
       case LINE_16_PIXCEL:
   
            LCD_DrawUniLineCircle(ptr->start_x+20,
                          ptr->start_y+(ptr->end_y-ptr->start_y)/2,ptr->end_x-20,
                          ptr->start_y+(ptr->end_y-ptr->start_y)/2,
                          8 );
 
    
      break;
        
       case LINE_20_PIXCEL:
   
            LCD_DrawUniLineCircle(ptr->start_x+20,
                          ptr->start_y+(ptr->end_y-ptr->start_y)/2,ptr->end_x-20,
                          ptr->start_y+(ptr->end_y-ptr->start_y)/2,
                          10);
 
    
      break;
            
            
    
     case LINE_WITH_CIRCLE: 
        LCD_SetColors(CL_BLACK,CL_WHITE);      
        LCD_DrawUniLine(ptr->start_x+5,
                          ptr->start_y+(ptr->end_y-ptr->start_y)/2,
                          ptr->end_x-5,
                          ptr->start_y+(ptr->end_y-ptr->start_y)/2);
		 
        
        for(i=0;i<((ptr->end_x - ptr->start_x-10)/10);i++)
        {
        
        LCD_DrawFullCircle(ptr->start_x+5+i*10,
                            ptr->start_y+(ptr->end_y-ptr->start_y)/2,
                            3);
        

        }

      
    break;
      
      
    case RUBBER:
			LCD_SetColors(CL_WHITE,CL_BLACK);
       LCD_DrawFullRect( ptr->start_x+((ptr->end_x - ptr->start_x -40)/3),
                          ptr->start_y+ ((ptr->end_y - ptr->start_y-40 -30)/3),
                          40,
                          40 );   
      
  
			LCD_SetColors(CL_RED,CL_BUTTON_GREY);    

		//ѡ�����壬ʹ����Ӣ����ʾʱ��������Ӣ��ѡ���16*24�����壬
		���������С��24*24�ģ���Ҫ��������������������ģ
		//�������ֻ��Ӣ������������
		LCD_SetFont(&Font16x24);
    LCD_DispString_EN_CH( ptr->end_y -30,
														ptr->start_x+(ptr->end_x - ptr->start_x -24*2)/3,
														(uint8_t*)"Eraser");
		

    break;
*/
  }
  
}

static void Draw_Command_Button(void *btn)
{
	 Touch_Button *ptr = (Touch_Button *)btn;
  
  /*�ͷŰ���*/
  if(ptr->touch_flag == 0)
  {
		LCD_SetColors(CL_BUTTON_GREY,CL_WHITE);
    LCD_DrawFullRect(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y);
  }
  else  /*��������*/
  {
    /*��ɫ����*/
		LCD_SetColors(CL_WHITE,CL_WHITE);
    LCD_DrawFullRect(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y);
  } 
    /*��ť�߿�*/
		LCD_SetColors(CL_BLUE4,CL_WHITE);
    LCD_DrawRect(ptr->start_x,
									ptr->start_y,
									ptr->end_x - ptr->start_x,
									ptr->end_y - ptr->start_y);
}
/**
* @brief  Command_Select_Color �л���ˢ��ɫ����ɫ�����Ĺ���ִ�к���
* @param  btn Touch_Button ���͵İ�������
* @retval ��
*/
static void Command_Select_Color(void *btn)
{
  Touch_Button *ptr = (Touch_Button *)btn;
  
  brush.color = ptr->para;	
	LCD_SetColors(brush.color,CL_WHITE);
  
  if(brush.shape == RUBBER)
  {
    brush.shape = LINE_SINGLE_PIXCEL;
  }

}

/**
* @brief  Command_Select_Brush �л���ˢ��ϸ����ˢ�����Ĺ���ִ�к���
* @param  btn Touch_Button ���͵İ�������
* @retval ��
*/
static void Command_Select_Brush(void *btn)
{
  Touch_Button *ptr = (Touch_Button *)btn;
  brush.shape =(SHAPE) ptr->para;
	LCD_SetColors(brush.color,CL_WHITE);
}

/**
* @brief  Command_Select_Brush �л���ˢ��ɫ�����������Ĺ���ִ�к���
* @param  btn Touch_Button ���͵İ�������
* @retval ��
*/
static void Command_Clear_Palette(void *btn)
{
		LCD_SetColors(CL_WHITE,CL_WHITE);
    LCD_DrawFullRect(PALETTE_START_X,
                      PALETTE_START_Y,                    
                      PALETTE_END_X-(PALETTE_START_X+1), 
											PALETTE_END_Y-PALETTE_START_Y );

}
static void Command_Send_Info(void *btn)
{
	Touch_Button *ptr = (Touch_Button *)btn;
	switch(ptr->para)
	{	
		case 0:
		{
			//������
			LCD_SetColors(CL_BUTTON_GREY,CL_BUTTON_GREY);
			LCD_DrawFullRect(PALETTE_START_X,
												PALETTE_START_Y,                    
												PALETTE_END_X-(PALETTE_START_X+1), 
												PALETTE_END_Y-PALETTE_START_Y );
			//PWM����
			increase_pwm_100(&PWM_FL);
			//��ʾ���
			clear_output_string();
			my_strcat(Output_String,"The Current Speed is:");
			myitoa(PWM_FL, NUMBER, 10);
			my_strcat(Output_String,NUMBER);
			LCD_SetColors(CL_RED,CL_BUTTON_GREY);
			LCD_SetFont(&Font16x24);
			LCD_DispString_EN_CH( 130,
														200,                     
			Output_String);
			break;
		}
		
		case 1:
		{
			//������
			LCD_SetColors(CL_BUTTON_GREY,CL_BUTTON_GREY);
			LCD_DrawFullRect(PALETTE_START_X,
												PALETTE_START_Y,                    
												PALETTE_END_X-(PALETTE_START_X+1), 
												PALETTE_END_Y-PALETTE_START_Y );
			//PWM����
			decrease_pwm_100(&PWM_FL);
			//��ʾ���
			clear_output_string();
			my_strcat(Output_String,"The Current Speed is:");
			myitoa(PWM_FL, NUMBER, 10);
			my_strcat(Output_String,NUMBER);
			LCD_SetColors(CL_RED,CL_BUTTON_GREY);
			LCD_SetFont(&Font16x24);
			LCD_DispString_EN_CH( 130,
														200,                     
			Output_String);
			break;
		}
		default:
			break;
	}
}


/* ------------------------------------------end of file---------------------------------------- */



