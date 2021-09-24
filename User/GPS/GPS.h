#ifndef _GPS_h_
#define _GPS_h_
#include "stm32f4xx.h"
typedef struct
{
	uint8_t  Connect;
	uint32_t Elevation;
	uint32_t Azimuth;
	uint32_t SNR;
}Satellite_info;
//定义GPS结构体
typedef struct
{
	uint32_t GPVTG_Get;
	uint32_t GPGGA_Get;
	uint32_t GPGLL_Get;
	uint32_t GPGSA_Get;
	uint32_t GPGSV_Get;
	uint32_t GPRMC_Get;
	
	
	uint32_t UTC_H;
	uint32_t UTC_M;
	uint32_t UTC_S;
	uint32_t UTC_MS;
	
	uint64_t Latitude;
	uint32_t Latitude_Type_N;
	uint64_t Longitude;
	uint32_t Longitude_Type_W;
	
	uint64_t Real_Speed_Dirc;
	uint64_t Mag_Speed_Dirc;
	uint64_t Speed_in_knot;
	uint64_t Speed_in_kmh;
	
	uint32_t Quality;
	uint32_t Satellite_n;
	uint64_t Horizontal_p;
	uint32_t Mode;
	uint32_t Dimensional;
	uint64_t PDOP;
	uint64_t HDOP;
	uint64_t VDOP;
	uint64_t Altitude;
	uint8_t  Altitude_Unit[6];
	uint64_t Grond_Altitude;
	uint8_t  Grond_Altitude_Unit[6];
	
	uint32_t Last_update;
	uint32_t Station_ID;
	
	Satellite_info Satellite[32];
	uint32_t Signal_Channel[12];
}GPS_info;
void GPS_Init(void);
void GPS_USART_Receive_Bytes(void);
void GPS_update(uint8_t * msg);
void GPS_SET_NMEA_OUTPUT(void);
void GPS_COLD_START(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
#endif