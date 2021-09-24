/**
  ******************************************************************************
  * @file    palette.c
  * @author  WT
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   ͨ�ý��溯��
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include "./touch/palette.h"
//���水������
uint8_t button_n;

//��ť�ṹ������
Touch_Button button[40];

//���ʲ���
Brush_Style brush;



/**
* @brief  Touch_Button_Down ����������ʱ���õĺ������ɴ���������
* @param  x ����λ�õ�x����
* @param  y ����λ�õ�y����
* @retval ��
*/
void Touch_Button_Down(uint16_t x,uint16_t y)
{
  uint8_t i;
  for(i=0;i<button_n;i++)
  {
    /* �������˰�ť */
    if(x<=button[i].end_x && y<=button[i].end_y && y>=button[i].start_y && x>=button[i].start_x )
    {
      if(button[i].touch_flag == 0)     /*ԭ����״̬Ϊû�а��£������״̬*/
      {
      button[i].touch_flag = 1;         /* ��¼���±�־ */
      
      button[i].draw_btn(&button[i]);  /*�ػ水ť*/
      }        
      
    }
    else if(button[i].touch_flag == 1) /* �����Ƴ��˰����ķ�Χ��֮ǰ�а��°�ť */
    {
      button[i].touch_flag = 0;         /* ������±�־���ж�Ϊ�����*/
      
      button[i].draw_btn(&button[i]);   /*�ػ水ť*/
    }

  }

}

/**
* @brief  Touch_Button_Up �������ͷ�ʱ���õĺ������ɴ���������
* @param  x ��������ͷ�ʱ��x����
* @param  y ��������ͷ�ʱ��y����
* @retval ��
*/
void Touch_Button_Up(uint16_t x,uint16_t y)
{
   uint8_t i; 
   for(i=0;i<button_n;i++)
   {
     /* �����ڰ�ť�����ͷ� */
      if((x<button[i].end_x && x>button[i].start_x && y<button[i].end_y && y>button[i].start_y))
      {        
        button[i].touch_flag = 0;       /*�ͷŴ�����־*/
        
        button[i].draw_btn(&button[i]); /*�ػ水ť*/        
      
        button[i].btn_command(&button[i]);  /*ִ�а����Ĺ�������*/
        
        break;
      }
    }  

}

/**
* @brief  Draw_Trail �ڻ���������津���켣
* @param  pre_x ��һ���x����
* @param  pre_y ��һ���y����
* @param  x     ����һ���x����
* @param  y     ����һ���y����
* @param  brush ��ˢ����
* @retval ��
*/
void Draw_Trail(int16_t pre_x,int16_t pre_y,int16_t x,int16_t y,Brush_Style* brush)
{
  /*���û�������Ϊ�����,bsp_lcd.c������û�������ĺ������������ƻ滭����*/
//  RA8875_SetActiveWindow(PALETTE_START_X,PALETTE_START_Y,PALETTE_END_X,PALETTE_END_Y);
  
	
  /*����λ���ڻ�������*/
  if(x>PALETTE_START_X && pre_x>PALETTE_START_X )
  {
    switch(brush->shape)  /*���ݻ�ˢ������治ͬ�Ĺ켣*/
    {
      /* ���1���ؿ�ȵĹ켣�� */
      case LINE_SINGLE_PIXCEL:                 
            if(pre_x< 0 || pre_y < 0) //�µıʼ�
            {      
              PutPixel(x,y);              
            }
            else //������һ�εıʼ�
            {      
              LCD_DrawUniLine(pre_x,pre_y,x,y);
            } 
        
        break;
            
      case LINE_2_PIXCEL:
        
				if(x-1<PALETTE_START_X||pre_x-1<PALETTE_START_X)	//������߽�
					break;

        /* ���2���ؿ�ȵĹ켣�� */
        LCD_DrawUniLineCircle(pre_x,pre_y,x,y,1);
        
        break;
      
      case LINE_4_PIXCEL:
				
				if(x-2<PALETTE_START_X||pre_x-2<PALETTE_START_X)	//������߽�
					break;
        
            LCD_DrawUniLineCircle(pre_x,pre_y,x,y,2);

        break;
      
      case LINE_6_PIXCEL:
        
				if(x-3<PALETTE_START_X||pre_x-3<PALETTE_START_X)	//������߽�
					break;
      
        LCD_DrawUniLineCircle(pre_x,pre_y,x,y,3);
        
        break;
      
      case LINE_8_PIXCEL:
				
				if(x-4<PALETTE_START_X||pre_x-4<PALETTE_START_X)	//������߽�
					break;
        
            LCD_DrawUniLineCircle(pre_x,pre_y,x,y,4);

        break;
      
     case LINE_16_PIXCEL:
			 
		 		if(x-8<PALETTE_START_X||pre_x-8<PALETTE_START_X)	//������߽�
					break;
        
            LCD_DrawUniLineCircle(pre_x,pre_y,x,y,8);

        break;
            
      case LINE_20_PIXCEL:
				
				if(x-10<PALETTE_START_X ||pre_x-10<PALETTE_START_X)	//������߽�
					break;
        
            LCD_DrawUniLineCircle(pre_x,pre_y,x,y,10);

        break;
      
      /*�������ӵĵ�������*/
      case LINE_WITH_CIRCLE:  

		 		if(x-3<PALETTE_START_X||pre_x-3<PALETTE_START_X)	//������߽�
					break;			
           
            if(pre_x< 0 || pre_y< 0)//�µıʼ�
            {      
              PutPixel(x,y); 
            }
            else //������һ�εıʼ�
            {      
              LCD_DrawUniLine(pre_x,pre_y,x,y);
              LCD_DrawFullCircle(x,y,3);
            } 
        
        break;
           
      /*��Ƥ����*/            
      case RUBBER:
				
				if(x-20<PALETTE_START_X ||						//������߽�
					  x+20>LCD_PIXEL_WIDTH || x-20<0 || //Һ�����ұ߽�
						y+20>LCD_PIXEL_HEIGHT || y-20<0)	 //Һ�����±߽�				
					break;	
			
//        if(x>PALETTE_START_X+20)
        {
						LCD_SetColors(CL_WHITE,CL_WHITE);
            
						LCD_DrawFullRect( x-40/2,
                                y-40/2,
                                40,
                                40);   
      
        }
      break;

    }
  }
  
  /*�˳����޻���Ļ�ͼ���ڣ�bsp_lcd.c������û�������ĺ������������ƻ滭����*/
//  RA8875_SetActiveWindow(0,0,LCD_PIXEL_WIDTH,LCD_PIXEL_HEIGHT);


}

#define ABS(X)  ((X) > 0 ? (X) : -(X))

/**
  * @brief  ������֮�����켣
  * @param  x1: specifies the point 1 x position.
  * @param  y1: specifies the point 1 y position.
  * @param  x2: specifies the point 2 x position.
  * @param  y2: specifies the point 2 y position.
  * @retval None
  */
void LCD_DrawUniLineCircle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint8_t thick )
{
  int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, 
  yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0, 
  curpixel = 0;
  
  deltax = ABS(x2 - x1);        /* The difference between the x's */
  deltay = ABS(y2 - y1);        /* The difference between the y's */
  x = x1;                       /* Start x off at the first pixel */
  y = y1;                       /* Start y off at the first pixel */
  
	
  if (x2 >= x1)                 /* The x-values are increasing */
  {
    xinc1 = 1;
    xinc2 = 1;
  }
  else                          /* The x-values are decreasing */
  {
    xinc1 = -1;
    xinc2 = -1;
  }
  
  if (y2 >= y1)                 /* The y-values are increasing */
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          /* The y-values are decreasing */
  {
    yinc1 = -1;
    yinc2 = -1;
  }
  
  if (deltax >= deltay)         /* There is at least one x-value for every y-value */
  {
    xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
    yinc2 = 0;                  /* Don't change the y for every iteration */
    den = deltax;
    num = deltax / 2;
    numadd = deltay;
    numpixels = deltax;         /* There are more x-values than y-values */
  }
  else                          /* There is at least one y-value for every x-value */
  {
    xinc2 = 0;                  /* Don't change the x for every iteration */
    yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
    den = deltay;
    num = deltay / 2;
    numadd = deltax;
    numpixels = deltay;         /* There are more y-values than x-values */
  }
  
  for (curpixel = 0; curpixel <= numpixels; curpixel++)
  {
		
		//�жϱ߽�
		if(x+thick>LCD_PIXEL_WIDTH || x-thick<0 || //Һ�����ұ߽�
			y+thick>LCD_PIXEL_HEIGHT || y-thick<0  ) //Һ�����±߽�
			continue;

    LCD_DrawFullCircle(x,y,thick);             /* Draw the current pixel */
    num += numadd;              /* Increase the numerator by the top of the fraction */
    if (num >= den)             /* Check if numerator >= denominator */
    {
      num -= den;               /* Calculate the new numerator value */
      x += xinc1;               /* Change the x as appropriate */
      y += yinc1;               /* Change the y as appropriate */
    }
    x += xinc2;                 /* Change the x as appropriate */
    y += yinc2;                 /* Change the y as appropriate */
  }
}
