/*
 *  dma.h
 *  Created on: 2017Äê6ÔÂ22ÈÕ
 *  Author: Administrator
 */

#ifndef  SOURCE_MODULE_DMA_DMA_H_
#define SOURCE_MODULE_DMA_DMA_H_

#include "comDef.h"

/******************************************************************************/
extern uint16 Receive_ADC_Buffer[50][3];

/******************************************************************************/
extern void ADC_DMA_Init(void);
extern void DMA_UART4_Init(void);
extern void ADC_DMA_StartConversion_1_times(void);
void UART4_DMA_StartConversion_1_times(void);

#endif
