#ifndef __ADC_H
#define __ADC_H	 
#include "stm32f10x.h" 
void OPT101_Init(void);
uint16_t AD_GetValue(void);
void temp_Init(void);
uint16_t AD2_GetValue(void);
void pres_Init(void);
#endif
