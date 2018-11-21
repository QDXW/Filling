#include "adc.h"
#include "Common.h"

/******************************************************************************/
void adc_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	/* ADC Clock 72/6=12M */
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);  
	
	ADC_DeInit(ADC1);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	/* Temp1 */
	GPIO_InitStructure.GPIO_Pin = PIN_ADC_TEMP_1;	
	GPIO_Init(PORT_ADC_TEMP_1, &GPIO_InitStructure);
	/* Temp2 */ 
	GPIO_InitStructure.GPIO_Pin = PIN_ADC_TEMP_2;	
	GPIO_Init(PORT_ADC_TEMP_2, &GPIO_InitStructure);
	/* Temp3 */ 
	GPIO_InitStructure.GPIO_Pin = PIN_ADC_TEMP_3;	
	GPIO_Init(PORT_ADC_TEMP_3, &GPIO_InitStructure);

	ADC_DeInit(ADC1);
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	/* Scan mode */
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	/* Continuous conversion */
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 3; /* Temp1 - Temp8 */
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4,1, ADC_SampleTime_239Cycles5 );                
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5,2, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6,3, ADC_SampleTime_239Cycles5 );                


	/* Enable ADC DMA Channel Convert */
	ADC_DMACmd(ADC1, ENABLE);
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);
	/* Enable Reset Calibration */
	ADC_ResetCalibration(ADC1);
	/* Wait for reset calibreation end */
	while(ADC_GetResetCalibrationStatus(ADC1));
	
	/* Enable ADC Calibration */
	ADC_StartCalibration(ADC1);
	/* Wait AD calibration end */
	while(ADC_GetCalibrationStatus(ADC1));
	
}

/******************************************************************************/
uint16 Get_50Adc_DMA_10Average(uint16 (*dma_adcValue)[3], uint8 ch)
{
	uint32 temp;
	uint8 i, j;
	
	/* Sorting */
	for(i = 0; i < ADC_SAMPLETIMES; i++)
	{
		for(j = i + 1; j < ADC_SAMPLETIMES; j++)
		{
			if(dma_adcValue[i][ch] < dma_adcValue[j][ch])
			{
				temp = dma_adcValue[i][ch];
				dma_adcValue[i][ch] = dma_adcValue[j][ch];
				dma_adcValue[j][ch] = temp;
			}
		}
	}
	/* The average of 10 data */
	temp = 0;
	for(i = 0; i < TIMES; i++)
	{
		temp += dma_adcValue[i + 20][ch];
	}
	return temp/TIMES;	
}



