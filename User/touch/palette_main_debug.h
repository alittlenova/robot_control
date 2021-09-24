#ifndef _PALETTE_MAIN_DEBUG_H
#define _PALETTE_MAIN_DEBUG_H

	#include "stm32f4xx.h"
	#include "./touch/palette.h"
	
	#define MAIN_BLOCK_WIDTH   180
	#define MAIN_BLOCK_HEIGHT  50

	#define MAIN_PALETTE_START_Y   30
	#define MAIN_PALETTE_END_Y     LCD_PIXEL_HEIGHT

	#if 1     //按钮栏在左边
		#define MAIN_BUTTON_START_X      0
		#define MAIN_PALETTE_START_X   MAIN_BLOCK_WIDTH+1
		#define MAIN_PALETTE_END_X     LCD_PIXEL_WIDTH

	#else     //按钮栏在右边，(存在触摸按键时也会的bug仅用于测试触摸屏左边界)
		#define MAIN_BUTTON_START_X      LCD_PIXEL_WIDTH-2*COLOR_BLOCK_WIDTH
		#define PALETTE_START_X   0
		#define MAIN_PALETTE_END_X     LCD_PIXEL_WIDTH-2*COLOR_BLOCK_WIDTH

	#endif
void MAIN_DEBUG_Palette_Init(void);
void MAIN_DEBUG_Touch_Button_Init(void);
#endif
