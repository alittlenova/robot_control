#ifndef _PALETTE_GPS_SATELLITE_H
#define _PALETTE_GPS_SATELLITE_H

	#include "stm32f4xx.h"
	#include "./touch/palette.h"

	#define GPS_BLOCK_WIDTH   180
	#define GPS_BLOCK_HEIGHT  50

	#define GPS_PALETTE_START_Y   30
	#define GPS_PALETTE_END_Y     LCD_PIXEL_HEIGHT

	#if 1     //��ť�������
		#define GPS_BUTTON_START_X      0
		#define GPS_PALETTE_START_X   GPS_BLOCK_WIDTH+1
		#define GPS_PALETTE_END_X     LCD_PIXEL_WIDTH

	#else     //��ť�����ұߣ�(���ڴ�������ʱҲ���bug�����ڲ��Դ�������߽�)
		#define MAIN_BUTTON_START_X      LCD_PIXEL_WIDTH-2*COLOR_BLOCK_WIDTH
		#define PALETTE_START_X   0
		#define PWM_PALETTE_END_X     LCD_PIXEL_WIDTH-2*COLOR_BLOCK_WIDTH

	#endif
void GPS_SATELLITE_Palette_Init(void);
void GPS_SATELLITE_Touch_Button_Init(void);
#endif