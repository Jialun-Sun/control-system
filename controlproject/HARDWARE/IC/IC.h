#ifndef __IC_H
#define __IC_H	 
#include "stm32f10x.h" 
void IC_Init(void);
uint32_t IC_GetFreq(void);
uint32_t IC_GetDuty(void);
#endif
