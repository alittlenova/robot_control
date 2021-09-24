#ifndef _DISPLAY_STATUS_h_
#define _DISPLAY_STATUS_h_
#include "stm32f4xx.h"
typedef struct
{
	uint8_t  Refresh;
	uint32_t Contents;
}DISPLAY_info;
void RefreshDisplay(void);
#endif