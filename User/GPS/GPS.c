#include "./GPS/GPS.h"
#include "./string/string.h"
#include "./usart/DGPS_Usart_Conf.h"
#include "./global/global.h"
#include "stdio.h"
//GPS控制层
static uint8_t* PMTK_Get_Arg(uint8_t* msg, uint8_t* argo);
static uint32_t Check_GPS_NMEA(uint8_t* msgst);
static uint32_t Compute_NMEA_check_value(uint8_t* msgst);
static uint32_t Pick_NMEA_check_value(uint8_t* msgst);
static uint32_t is_N(uint8_t* arg);
static uint32_t is_W(uint8_t* arg);
static uint32_t is_Auto(uint8_t* arg);
static uint32_t Compute_UTC_H(double arg);
static uint32_t Compute_UTC_M(double arg);
static uint32_t Compute_UTC_S(double arg);
static uint32_t Compute_UTC_MS(double arg);
static void GPS_GPGGA_update(uint8_t * msgst);
static void GPS_GPRMC_update(uint8_t * msgst);
static void GPS_GPGLL_update(uint8_t * msgst);
static void GPS_GPVTG_update(uint8_t * msgst);
static void GPS_GPGSA_update(uint8_t * msgst);
static void GPS_GPGSV_update(uint8_t * msgst);
static void GPS_SEND(uint8_t* msg);
static void calculating_Tail(uint8_t* msg);
static void wait01s();
static void wait01s()
{
	onOff=0;
	while(onOff==0)
	{
	}
	while(onOff==1)
	{
	}
}
//GPS结构体初始化
void GPS_Init(void)
{
	GPS_Data.GPVTG_Get=0;
	GPS_Data.GPGGA_Get=0;
	GPS_Data.GPGLL_Get=0;
	GPS_Data.GPGSA_Get=0;
	GPS_Data.GPGSV_Get=0;
	GPS_SET_NMEA_OUTPUT();
	GPS_COLD_START();
	
}
//GPS信号接收
void GPS_USART_Receive_Bytes(void)
{
		uint8_t ucTemp='\n';
		ucTemp = USART_ReceiveData( DGPS_USART );
			if(ucTemp=='\n')
			{
				received++;
				receive_Buff_Point=0;
				GPS_update(receive_Buff);
			}
			else
			{
				if(receive_Buff_Point<88)
				{
					receive_Buff[receive_Buff_Point]=ucTemp;
					receive_Buff[receive_Buff_Point+1]='\0';
					receive_Buff_Point++;
				}
			}
}
//GPS信号处理层

//Main function for processing the GPS data
void GPS_update(uint8_t * msgst)
{
	//setup the reading pointer
	uint8_t* msg=msgst;
	//setup the current argument string
	uint8_t args[100];
	
	//check the data
	testresult=Check_GPS_NMEA(msgst);
	if(testresult==0)
		return;
	
	//pick up one argument from a sentence
	msg=PMTK_Get_Arg(msg, args);

	if(isequal(args,"$GPGGA",6))
	{
		GPS_Data.GPGGA_Get++;
		GPS_GPGGA_update(msg);
	}
	
	if(isequal(args,"$GPGLL",6))
	{
		GPS_Data.GPGLL_Get++;
		GPS_GPGLL_update(msg);
	}
	
	if(isequal(args,"$GPVTG",6))
	{
		GPS_Data.GPVTG_Get++;
		GPS_GPVTG_update(msg);
	}
	
	if(isequal(args,"$GPGSA",6))
	{
		GPS_Data.GPGSA_Get++;
		GPS_GPGSA_update(msg);
	}
	
	if(isequal(args,"$GPGSV",6))
	{
		GPS_Data.GPGSV_Get++;
		GPS_GPGSV_update(msg);
	}
	if(isequal(args,"$GPRMC",6))
	{
		GPS_Data.GPRMC_Get++;
		GPS_GPGSV_update(msg);
	}
	
}
//checking data
static uint32_t Check_GPS_NMEA(uint8_t* msgst)
{
	uint32_t Check_VC,Check_V;
	Check_VC=Compute_NMEA_check_value(msgst);
	Check_V=Pick_NMEA_check_value(msgst);
	if(Check_VC==Check_V)
		return 1;
	else
		return 0;
}
//compute the check value
static uint32_t Compute_NMEA_check_value(uint8_t* msgst)
{
		int i = 0;
    char result = msgst[1];
    for(i = 2; (msgst[i] != '\0')&&(msgst[i] != '*'); i++)
    {
        result ^= msgst[i];
    }
		return result;
}
//pick the check value
static uint32_t Pick_NMEA_check_value(uint8_t* msgst)
{
	uint32_t result=0,temp=0;
	uint8_t* pointer=msgst;
	while((*pointer!='*')&&(*pointer!='\0'))
	{
		pointer++;
	}
	
	if((*pointer)=='*')
	{
		pointer++;
		if(*pointer>='0'&&*pointer<='9')
		{
			temp=*pointer-'0';
			pointer++;
		}
		else if(*pointer>='A'&&*pointer<='F')
		{
			temp=(*pointer-'A')+10;
			pointer++;
		}
		result=result+(temp*16);
		if(*pointer>='0'&&*pointer<='9')
		{
			temp=*pointer-'0';
			pointer++;
		}
		else if(*pointer>='A'&&*pointer<='F')
		{
			temp=(*pointer-'A')+10;
			pointer++;
		}
		result=result+temp;
		return result;
	}
	else
	{
		return 0;
	}
}
//Reading one argument from a sentence
static uint8_t* PMTK_Get_Arg(uint8_t* msg, uint8_t* argo)
{
	uint8_t* pointer=msg;
	//check the forwarding conditions
	while(*pointer!=','&&*pointer!='\r'&&*pointer!='\0')
	{
		//copy one byte
		*argo=*pointer;
		argo++;
		pointer++;
	}
	//ceil the arg output
	*argo='\0';
	//check if it is the last argument
	if(*pointer==',')
	{
		pointer++;
	}
	return pointer;
}
//Processing tools
static uint32_t is_N(uint8_t* arg)
{
	if(*arg=='N')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
static uint32_t is_W(uint8_t* arg)
{
	if(*arg=='W')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
static uint32_t is_Auto(uint8_t* arg)
{
	if(*arg=='A')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
static uint32_t Compute_UTC_H(double arg)
{
	return (((int)arg)/10000);
}
static uint32_t Compute_UTC_M(double arg)
{
	return ((((int)arg)%10000)/100);
}
static uint32_t Compute_UTC_S(double arg)
{
	return (((int)arg)%100);
}
static uint32_t Compute_UTC_MS(double arg)
{
	return ((int)(arg*1000))%1000;
}
//Processing the GPGGA sentence
static void GPS_GPGGA_update(uint8_t * msgst)
{
	uint8_t args[20];
	uint8_t* msg=msgst;
	uint64_t temp=0;
	
	msg=PMTK_Get_Arg(msg, args);//UTC时间
	temp=myatof(args);
	GPS_Data.UTC_H=Compute_UTC_H(temp);
	GPS_Data.UTC_M=Compute_UTC_M(temp);
	GPS_Data.UTC_S=Compute_UTC_S(temp);
	GPS_Data.UTC_MS=Compute_UTC_MS(temp);
	
	msg=PMTK_Get_Arg(msg, args);//纬度
	GPS_Data.Latitude=myatof(args);
	
	msg=PMTK_Get_Arg(msg, args);//北纬/南纬
	GPS_Data.Latitude_Type_N=is_N(args);
	
	msg=PMTK_Get_Arg(msg, args);//经度
	GPS_Data.Longitude=myatof(args);
	
	msg=PMTK_Get_Arg(msg, args);//东经/西经
	GPS_Data.Longitude_Type_W=is_W(args);
	
	msg=PMTK_Get_Arg(msg, args);//定位质量指标
	GPS_Data.Quality=myatoi(args);
	
	msg=PMTK_Get_Arg(msg, args);//使用卫星数量
	GPS_Data.Satellite_n=myatoi(args);
	
	msg=PMTK_Get_Arg(msg, args);//水平精度
	GPS_Data.Horizontal_p=myatof(args);
	
	msg=PMTK_Get_Arg(msg, args);//天线离海平面的高度
	GPS_Data.Altitude=myatof(args);
	
	msg=PMTK_Get_Arg(msg, args);//高度单位
	GPS_Data.Altitude_Unit[0]='\0';
	my_strcat(GPS_Data.Altitude_Unit,args);
	
	msg=PMTK_Get_Arg(msg, args);//大地椭球面相对海平面的高度
	GPS_Data.Grond_Altitude=myatof(args);
	
	msg=PMTK_Get_Arg(msg, args);//高度单位
	GPS_Data.Grond_Altitude_Unit[0]='\0';
	my_strcat(GPS_Data.Grond_Altitude_Unit,args);
	
	msg=PMTK_Get_Arg(msg, args);//差分GPS数据期限
	GPS_Data.Last_update=myatoi(args);
	
	msg=PMTK_Get_Arg(msg, args);//差分参考基站标号
	GPS_Data.Station_ID=myatoi(args);
}

//Processing the GPGLL sentence
static void GPS_GPGLL_update(uint8_t * msgst)
{
	uint8_t args[20];
	uint8_t* msg=msgst;
	msg=PMTK_Get_Arg(msg, args);//ddmm.mmmm
	GPS_Data.Latitude=myatof(args);
	msg=PMTK_Get_Arg(msg, args);//N
	GPS_Data.Latitude_Type_N=is_N(args);
	msg=PMTK_Get_Arg(msg, args);//ddmm.mmmm
	GPS_Data.Longitude=myatof(args);
	msg=PMTK_Get_Arg(msg, args);//W
	GPS_Data.Longitude_Type_W=is_W(args);
}
//Processing the GPVTG sentence
static void GPS_GPVTG_update(uint8_t * msgst)
{
	uint8_t args[20];
	uint8_t* msg=msgst;
	msg=PMTK_Get_Arg(msg, args);//0.00
	GPS_Data.Real_Speed_Dirc=myatof(args);
	msg=PMTK_Get_Arg(msg, args);//T
	msg=PMTK_Get_Arg(msg, args);//0.00
	GPS_Data.Mag_Speed_Dirc=myatof(args);
	msg=PMTK_Get_Arg(msg, args);//M
	msg=PMTK_Get_Arg(msg, args);//0.00
	GPS_Data.Speed_in_knot=myatof(args);
	msg=PMTK_Get_Arg(msg, args);//N
	msg=PMTK_Get_Arg(msg, args);//0.00
	GPS_Data.Speed_in_kmh=myatof(args);
	msg=PMTK_Get_Arg(msg, args);//K
}
//Processing the GPGSA sentence
static void GPS_GPGSA_update(uint8_t * msgst)
{
	uint8_t args[20];
	uint8_t* msg=msgst;
	uint32_t S_ID;
	uint32_t ID;
	msg=PMTK_Get_Arg(msg, args);//GPS Mode 0.Manul 1.Automatic
	GPS_Data.Mode=is_Auto(args);
	
	msg=PMTK_Get_Arg(msg, args);//GPS Dimensional
	GPS_Data.Dimensional=myatoi(args);
	ID=0;
	for(;ID<32;ID++)
	{
			GPS_Data.Satellite[ID].Connect=0;
	}
	ID=0;
	for(;ID<12;ID++)
	{
		msg=PMTK_Get_Arg(msg, args);//Satellite ID
		S_ID=myatoi(args)-1;
		GPS_Data.Signal_Channel[ID]=S_ID;
		if(S_ID!=-1)
		{
			GPS_Data.Satellite[S_ID].Connect=1;
		}
	}
	
	msg=PMTK_Get_Arg(msg, args);//PDOP
	GPS_Data.PDOP=myatof(args);
	
	msg=PMTK_Get_Arg(msg, args);//HDOP
	GPS_Data.HDOP=myatof(args);
	
	msg=PMTK_Get_Arg(msg, args);//VDOP
	GPS_Data.VDOP=myatof(args);
}
//Processing the GPGSV sentence
static void GPS_GPGSV_update(uint8_t * msgst)
{
	uint8_t args[20];
	uint8_t* msg=msgst;
	uint32_t S_ID;
	msg=PMTK_Get_Arg(msg, args);//All Number Msg
	
	msg=PMTK_Get_Arg(msg, args);//Current Msg Code
	
	msg=PMTK_Get_Arg(msg, args);//Visable Satellite Number
	GPS_Data.Satellite_n=myatoi(args);
	
	while(((*msg)!='*')&&((*msg)!='\r')&&((*msg)!='\n')&&((*msg)!='\0'))
	{
		msg=PMTK_Get_Arg(msg, args);//Satellite ID
		S_ID=myatoi(args)-1;
		
		msg=PMTK_Get_Arg(msg, args);//Satellite Elevation
		GPS_Data.Satellite[S_ID].Elevation=myatoi(args);
		
		msg=PMTK_Get_Arg(msg, args);//Satellite Azimuth
		GPS_Data.Satellite[S_ID].Azimuth=myatoi(args);
		
		msg=PMTK_Get_Arg(msg, args);//Satellite SNR
		GPS_Data.Satellite[S_ID].SNR=myatoi(args);
	}
}
static void GPS_GPRMC_update(uint8_t * msgst)
{
		uint8_t args[20];
		uint8_t* msg=msgst;
		msg=PMTK_Get_Arg(msg, args);//Time Stamp
		msg=PMTK_Get_Arg(msg, args);//validity - A-ok, V-invalid
		msg=PMTK_Get_Arg(msg, args);//current Latitude
		msg=PMTK_Get_Arg(msg, args);//North/South
		msg=PMTK_Get_Arg(msg, args);//current Longitude
		msg=PMTK_Get_Arg(msg, args);//East/West
		msg=PMTK_Get_Arg(msg, args);//Speed in knots
		msg=PMTK_Get_Arg(msg, args);//True course
		msg=PMTK_Get_Arg(msg, args);//Date Stamp
		msg=PMTK_Get_Arg(msg, args);//Variation
		msg=PMTK_Get_Arg(msg, args);//East/West
		msg=PMTK_Get_Arg(msg, args);//checksum
}
//GPS显示


//GPS指令
void GPS_SET_NMEA_OUTPUT(void)
{
	//GPS_SEND("$PMTK314,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0");
}
void GPS_COLD_START(void)
{
	GPS_SEND("$PMTK103");
	wait01s();
	GPS_SEND("$PMTK314,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0");
	wait01s();
	//GPS_SEND("$PMTK605");
	wait01s();

}
static void GPS_SEND(uint8_t* msg)
{
	clear_output_GPS_string();
	my_strcat(Output_GPS_String,msg);
	calculating_Tail(Output_GPS_String);
	Usart_SendString(DGPS_USART,Output_GPS_String);
}
//包尾加工
static void calculating_Tail(uint8_t* msg)
{
	uint32_t vlu;
	uint8_t buf[3];
	vlu=Compute_NMEA_check_value(msg);
	my_strcat(msg,"*");
	myitohex_twob(vlu,buf);
	my_strcat(msg,buf);
	my_strcat(msg,"\r\n");
}

//Usart指令
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	// 发送一个字节数据到USART2
	USART_SendData(pUSARTx,ch);

	// 等待发送数据寄存器为空
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
	do {
		Usart_SendByte( pUSARTx, *(str + k) );
		k++;
	} while (*(str + k)!='\0');

	// 等待发送完成
	while (USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET) {
	}
}