/*
 * HostComm.h
 *
 *  Created on: 2016Äê7ÔÂ13ÈÕ
 *      Author: Administrator
 */

#ifndef SOURCE_MODULES_HOSTCOMM_HOSTCOMM_H_
#define SOURCE_MODULES_HOSTCOMM_HOSTCOMM_H_

/******************************************************************************/
#include "Project_File.h"

/******************************************************************************/

#define HOSTCOMM_USART 				(USART1)
#define HOSTCOMM_USART_IRQN 		(USART1_IRQn)
#define HOSTCOMM_TX_PORT 			(GPIOA)
#define HOSTCOMM_TX_PIN 			(GPIO_Pin_9)
#define HOSTCOMM_RX_PORT 			(GPIOA)
#define HOSTCOMM_RX_PIN 			(GPIO_Pin_10)


/******************************************************************************/
	#define TIM_HOSTCOMM_TIMEOUT 				(TIM2)
	#define TIM_TIMEOUT_IRQ						(TIM2_IRQn)
	#define TIM_CNT_RELOAD						(9)

/******************************************************************************/
void HostComm_Init(void);
void HostComm_SendCommand(uint8 *dataPtr, uint16 len);

#endif /* SOURCE_MODULES_HOSTCOMM_HOSTCOMM_H_ */
