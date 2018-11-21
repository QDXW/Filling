 /*
 * Task.c
 *
 *  Created on: 2017年6月22日
 *      Author: Administrator
 */
 
#include "dma.h"
#include "stm32f10x_dma.h"

/******************************************************************************/
#define  N   (50)  //每个通道进行50次采样
#define  M   (3)   //连续5个通道的采样顺序

/******************************************************************************/
uint16 Receive_ADC_Buffer[N][M];
uint32 Send_USART_Buffer[1];
uint16 DMA1_MEM_LEN;

/******************************************************************************
*
* DMA_CHx : DMA channel
* cpar : DMA stream x peripheral address register
* cmar : DMA stream x memory address register
* cdir : DMA stream x data transfer direction
* cndtr : DMA stream x number of data register
* psize : Peripheral data size
* msize : Memory data size
*
******************************************************************************/
void DMA_Configuration(DMA_Channel_TypeDef* DMA_CHx, 
								uint32 cpar,
								uint32 cmar,
								uint32 cdir,
								uint16 cndtr,
								uint32 psize,
								uint32 msize)
{
	DMA_InitTypeDef DMA_InitStructure;

	/* Enable DMA */
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	
	/* Reset DMA channel register */
	DMA_DeInit(DMA_CHx);
	/*  */
	DMA1_MEM_LEN = cndtr;
	/* DMA stream x peripheral address register */
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;
	/* DMA stream x memory address register */
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;
	/* DMA stream x data transfer direction */
	DMA_InitStructure.DMA_DIR = cdir;
	/* DMA stream x number of data register */
	DMA_InitStructure.DMA_BufferSize = cndtr; 
	/* Peripheral increment mode */
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	/* Memory increment mode */
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	/* Peripheral data size */
	DMA_InitStructure.DMA_PeripheralDataSize = psize;
	/* Memory data size */
	DMA_InitStructure.DMA_MemoryDataSize = msize;
	/* Circular mode */
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	/* Priority level */
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	/* Memory to memory */
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	/* DMA initialzation */
	DMA_Init(DMA_CHx, &DMA_InitStructure);
}

/******************************************************************************/
void ADC_DMA_Init(void)
{	
	ADC_DMACmd(ADC1, ENABLE);
	
	DMA_Configuration(DMA1_Channel1,             /* ADC1 DMA */
							(uint32)&ADC1->DR,         /* Peripheral address*/
							(uint32)&Receive_ADC_Buffer,/* Memory address */
							DMA_DIR_PeripheralSRC,     /* Peripheral to memory */
							50 * 3,   /* number of data : 50, number of channel : 5 */
							DMA_PeripheralDataSize_HalfWord,/* Peripheral data size */
							DMA_MemoryDataSize_HalfWord);	  /* Peripheral data size */
}

/******************************************************************************/
void DMA_UART5_Init(void)
{
	USART_DMACmd(UART5, USART_DMAReq_Tx, ENABLE);
	
	DMA_Configuration(DMA1_Channel4,            /* USART DMA */
							(uint32)&UART5->DR,       /* Peripheral address*/
							(uint32)Send_USART_Buffer,/* Memory address */
							DMA_DIR_PeripheralDST,    /* Memory to periphral */
							1,                        /* number of data : 1 */
							DMA_PeripheralDataSize_Word, /* Peripheral data size */
							DMA_MemoryDataSize_Word);/* Peripheral data size */
}

/******************************************************************************/
void ADC_DMA_StartConversion_1_times(void)
{	
	ADC_Cmd(ADC1, DISABLE);
	
	/* Configuration DMA number of data */
	DMA_Cmd(DMA1_Channel1, DISABLE);	
 	DMA_SetCurrDataCounter(DMA1_Channel1,DMA1_MEM_LEN);
	/* Enable DMA transfer */
 	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	ADC_Cmd(ADC1, ENABLE);
	/* Enable adc conversion */
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
	/* Wait until finishing transfer  */
	while(!DMA_GetFlagStatus(DMA1_FLAG_TC1));
	DMA_ClearFlag(DMA1_FLAG_TC1);
}

/******************************************************************************/
void UART4_DMA_StartConversion_1_times(void)
{
	/************************************************************** 
					STM32F10x DMA只支持USART1-UART4
	***************************************************************/
	USART_DMACmd(UART4,USART_DMAReq_Tx,ENABLE);
	/* Configuration DMA number of data */
	DMA_Cmd(DMA1_Channel4, DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel4,DMA1_MEM_LEN);
	/* Enable DMA transfer */
	DMA_Cmd(DMA1_Channel4, ENABLE);
	/* Wait until finishing transfer  */
	while(!DMA_GetFlagStatus(DMA1_FLAG_TC4));
	DMA_ClearFlag(DMA1_FLAG_TC4);	
}



