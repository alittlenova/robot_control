#ifndef _PALETTE_I2C_DEBUG_H
#define _PALETTE_I2C_DEBUG_H

	#include "stm32f4xx.h"
	#include "./touch/palette.h"
	
	#define I2C_BLOCK_WIDTH   180
	#define I2C_BLOCK_HEIGHT  50

	#define I2C_PALETTE_START_Y   30
	#define I2C_PALETTE_END_Y     LCD_PIXEL_HEIGHT

	#if 1     //��ť�������
		#define I2C_BUTTON_START_X      0
		#define I2C_PALETTE_START_X   MAIN_BLOCK_WIDTH+1
		#define I2C_PALETTE_END_X     LCD_PIXEL_WIDTH

	#else     //��ť�����ұߣ�(���ڴ�������ʱҲ���bug�����ڲ��Դ�������߽�)
		#define MAIN_BUTTON_START_X      LCD_PIXEL_WIDTH-2*COLOR_BLOCK_WIDTH
		#define PALETTE_START_X   0
		#define MAIN_PALETTE_END_X     LCD_PIXEL_WIDTH-2*COLOR_BLOCK_WIDTH

	#endif
void I2C_DEBUG_Palette_Init(void);
void I2C_DEBUG_Touch_Button_Init(void);
#endif
