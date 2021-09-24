#include "./string/string.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * @brief  converte the string to uint_63
 * @param  str: number.
 * @retval the uint_64 value
 */
uint64_t myatof(const char *str)
{
	//argument check first!
	double retds=0;
	double retd=0;
	int ret=0,sign=1,p=1;
	//skip tab and space
	for(; *str==' '||*str=='\t'; str++);
	if(*str == '-')sign = -1;
	if(*str == '-' || *str == '+')str++;
	while(isdigit(*str)){
		ret = ret*10 + *str - '0';
		str++;
		}
	retd=ret;
	if((*str)=='.')
	{
		ret=0;
		str++;
		for(; *str==' '||*str=='\t'; str++);
		while(isdigit(*str)){
			ret = ret*10 + *str - '0';
			p=p*10;
			str++;
		}
		if(ret!=0)
		{
			retds=ret;
			retds=retds/p;
		}
	}
	return (uint64_t)sign*retd;
}
/**
 * @brief  converte the string to uint_32
 * @param  str: number.
 * @retval the uint_32 value
 */

uint32_t myatoi(const char *str){
	int ret=0,sign=1;
	//skip tab and space
	for(; *str==' '||*str=='\t'; str++);
	if(*str == '-')sign = -1;
	if(*str == '-' || *str == '+')str++;
	while(isdigit(*str)){
		ret = ret*10 + *str - '0';
		str++;
		}
	return (uint32_t)sign*ret;
}
/**
 * @brief  converte the uint32_t to string
 * @param  value: number.
 * @param  string: the target string.
 * @retval None
 */

void myitoa(uint32_t value, char *string, uint8_t radix)
{
    uint32_t     i, d;
    uint8_t     flag = 0;
    char    *ptr = string;
 
    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        //return string;
    }
 
    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        //return string;
    }
 
    /* if this is a negative value insert the minus sign. */
    if ((int)value < 0 )
    {
        *ptr++ = '-';
 
        /* Make the value positive. */
        value *= -1;
    }
 
    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;
 
        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }
 
    /* Null terminate the string. */
    *ptr = 0;
}



/**
 * @brief  converte the uint32_t to string in 16 
 * @param  aa: number.
 * @param  buffer: the target string.
 * @retval None
 */
void myitohex_twob(int aa,char *buffer)
{
	if (aa / 16 < 10)
		buffer[0] = aa / 16 + '0';
	else
		buffer[0] = aa / 16 - 10 + 'A';
	if (aa % 16 < 10)
		buffer[1] = aa % 16 + '0';
	else
		buffer[1] = aa % 16 - 10 + 'A';
	buffer[2] = '\0';
}
/**
 * @brief  connect the two string and put them into the first string
 * @param  str1: the first string.
 * @param  str2: the second string.
 * @retval None
 */
void my_strcat(char *str1, char *str2)
{
    char *pt = str1;
    while(*str1!='\0') str1++;
    while(*str2!='\0') *str1++ = *str2++;
    *str1 = '\0';
    //return pt;
}
/**
 * @brief  compare the two strings if they are the same
 * @param  str1: the first string.
 * @param  str2: the second string.
 * @param  n: the first n bytes.
 * @retval 1, same; 0 not same
 */
uint32_t isequal(const char *str1, const char *str2,const int n)
{
	int p=0;
	while(p<n)
	{
		if(*str1=='\0')return 0;
		if(*str2=='\0')return 0;
		if(*str1!=*str2)return 0;
		str1++;
		str2++;
		p++;
	}
	return 1;
}
