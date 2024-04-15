#ifndef __DMA_H
#define __DMA_H
#include "stm32f10x.h" 
void DMA_ReTransfer(void);
void DMA_Transfer(uint32_t addrA,uint32_t addrB, uint16_t size);
#endif

