#include "./touch/display_status.h"
#include "./global/global.h"
#include "./touch/palette_gps_receive.h"
void DISPLAY_Init(void)
{
	DISPLAY_Data.Refresh=0;
	DISPLAY_Data.Contents=0;
}
void RefreshDisplay(void)
{
	if(DISPLAY_Data.Refresh==1)
	{
		switch(DISPLAY_Data.Contents)
		{
				case 0:
				{
					GPS_RECEIVE_Display_Info();
					break;
				}
				default:
					break;
		}
	}
}