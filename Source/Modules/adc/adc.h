#ifndef SOURCE_MODULES_ADC_ADC_H
#define SOURCE_MODULES_ADC_ADC_H

#include "comDef.h"
#include "stm32f10x.h"

/******************************************************************************/
#define ADC_SAMPLETIMES (50)
#define TIMES     (10)


#define PORT_ADC_TEMP_1 (GPIOA)
#define PIN_ADC_TEMP_1 (GPIO_Pin_4)
#define PORT_ADC_TEMP_2 (GPIOA)
#define PIN_ADC_TEMP_2 (GPIO_Pin_5)
#define PORT_ADC_TEMP_3 (GPIOA)
#define PIN_ADC_TEMP_3 (GPIO_Pin_6)


void adc_Init(void);
uint16 Get_50Adc_DMA_10Average(uint16 (*dma_adcValue)[3], uint8 ch);
#endif 


