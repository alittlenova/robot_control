#ifndef __STRING_H
#define	__STRING_H
#include "stm32f4xx.h"
uint32_t myatoi(const char *str);
void		 myitoa(uint32_t value, char *string, uint8_t radix);
uint64_t myatof(const char *str);
void		 myitohex_twob(int aa,char *buffer);
void		 my_strcat(char *str1, char *str2);
uint32_t isequal(const char *str1, const char *str2,const int n);
#endif