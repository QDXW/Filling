/*
 * HostComm.c
 *
 *  Created on: 2016年7月13日
 *      Author: Administrator
 */
#include "HostComm.h"

/******************************************************************************/
uint8 rxBuf[512];				/* 接收缓存 */
uint8 rxIndex;					/* 缓存指示 */

/******************************************************************************/
void HostComm_SendCommand(uint8 *dataPtr, uint16 len);

/******************************************************************************/
static void HostComm_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/*Enable interrupt*/
	NVIC_InitStructure.NVIC_IRQChannel = HOSTCOMM_USART_IRQN;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/******************************************************************************/
static void HostComm_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = HOSTCOMM_TX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(HOSTCOMM_TX_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = HOSTCOMM_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(HOSTCOMM_RX_PORT, &GPIO_InitStructure);
}

/******************************************************************************/
static void HostComm_Config(void)
{
	USART_InitTypeDef USART_InitStructure;

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* Configure */
	USART_Init(HOSTCOMM_USART, &USART_InitStructure);
	USART_ITConfig(HOSTCOMM_USART, USART_IT_RXNE, ENABLE);
	USART_ClearFlag(HOSTCOMM_USART, USART_FLAG_TC);

	USART_Cmd(HOSTCOMM_USART, ENABLE);
}

/******************************************************************************/
static void HostComm_TimeOut_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = 9;
	TIM_TimeBaseStructure.TIM_Prescaler = 719;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
	TIM_TimeBaseInit(TIM_HOSTCOMM_TIMEOUT, &TIM_TimeBaseStructure);

	TIM_ITConfig(TIM_HOSTCOMM_TIMEOUT, TIM_IT_Update, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM_TIMEOUT_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/******************************************************************************/
void HostComm_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	/*Initialize GPIOs*/
	HostComm_GPIO_Init();
	/*Enable interrupt*/
	HostComm_NVIC_Configuration();
	/*Configure parameters*/
	HostComm_Config();

	HostComm_TimeOut_Init();
}

/******************************************************************************/
void HostComm_SendCommand(uint8 *dataPtr, uint16 length)
{
	USART1->SR;
	while(length-- != 0) {
		USART_SendData(HOSTCOMM_USART, *dataPtr++);
		while(USART_GetFlagStatus(HOSTCOMM_USART, USART_FLAG_TC)==RESET);
	}
}

/******************************************************************************/
void HostComm_TimeOut_Reload(void)
{
	/* 向下计数模式,装载TIMx->CNT值 */
	TIM_HOSTCOMM_TIMEOUT->CNT = TIM_CNT_RELOAD;
}

///******************************************************************************/
//void TIM2_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM_HOSTCOMM_TIMEOUT, TIM_IT_Update) != RESET)
//	{
//		TIM_Cmd(TIM_HOSTCOMM_TIMEOUT, DISABLE);
//		TIM_ClearITPendingBit(TIM_HOSTCOMM_TIMEOUT, TIM_IT_Update);
//	}
//}

/******************************************************************************
!!! ISR: Host communication interrupt service routine
******************************************************************************/
void USART1_IRQHandler(void)
{
	uint8 RX_dat;
	USART1->SR;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)//USART_IT_RXNE：接收中断
	{
		RX_dat=USART_ReceiveData(USART1);

		if ((RX_dat == '$') && (contReceive == 0))
		{
			contReceive = 1;
			recCount = 0;
			recBuffer[recCount++] = RX_dat;
		}
		else
		{
			recBuffer[recCount++] = RX_dat;
		}

		/* Get the package length: header + data + tail */
		if (recCount >= 3)
		{
			respLength =
					(recBuffer[OFFSET_LEN_LO] | (recBuffer[OFFSET_LEN_HI] << 8))
					+ 2;
		}
		else
		{
			respLength = 0;
		}

		/* Receive all: start processing response data */
		if ((respLength > 0) && (recCount >= respLength))
		{
			HostComm_RecBufAvailable = 1;
			HostComm_RecBufSize = recCount;

			memcpy(cmdBuffer, recBuffer, recCount);
			memset(recBuffer, 0, recCount);
			contReceive = 0;
			respLength = 0;
			recCount = 0;
		}
	}
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
}

/******************************************************************************/
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	return (ch);
}
