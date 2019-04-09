/*
 * Project_File.h
 *
 *  Created on: 2018Äê9ÔÂ19ÈÕ
 *      Author: Administrator
 */

#ifndef SYSTEM_PROJECT_FILE_H_
#define SYSTEM_PROJECT_FILE_H_

/******************************************************************************/
#include "comDef.h"
#include "stm32f10x.h"
#include "Global_variable.h"
#include "Comm_CAN.h"
#include "Motor.h"
#include "devices.h"
#include "Common.h"
#include "Device_Action.h"
#include "HostProcess.h"
#include "HostComm.h"
#include "sensor.h"
#include "CRC16.h"
#include "Laminating.h"
#include "Movement.h"
#include "Flash.h"
#include <stdio.h>
#include "Timer5.h"
#include "Comm.h"
#include "adc.h"
#include "dma.h"
#include "math.h"
#include "string.h"

/******************************************************************************/
#define CH1_ENABLED                 0
#define CH2_ENABLED                 1

/******************************************************************************/
#define TIMER1_M10_R1_R2_ENABLED    1 /* M10 - R1 - R2 */
#define TIMER2_M3_M_W1_ENABLED      1 /* M3 - M - W1 */
#define TIMER3_M6_W2_W3_ENABLED     1 /* M6 - W2 - W3 */
#define TIMER4_M4_W6_BASE_ENABLED   1 /* M4 - W6 - BASE */
#define TIMER5_M1_W4_W5_ENABLED     1 /* M1 - W4 - W5 */

/******************************************************************************/
#define PORT_SWITCH_1 				(GPIOA)
#define PIN_SWITCH_1 				(GPIO_Pin_3)

#define PORT_SWITCH_2 				(GPIOC)
#define PIN_SWITCH_2 				(GPIO_Pin_4)

#define PORT_SWITCH_3 				(GPIOC)
#define PIN_SWITCH_3 				(GPIO_Pin_5)

#define PORT_SWITCH_4 				(GPIOB)
#define PIN_SWITCH_4 				(GPIO_Pin_0)

#define PORT_SWITCH_5 				(GPIOB)
#define PIN_SWITCH_5 				(GPIO_Pin_1)

#define PORT_SWITCH_6 				(GPIOE)
#define PIN_SWITCH_6 				(GPIO_Pin_7)

#define PORT_SWITCH_7 				(GPIOE)
#define PIN_SWITCH_7				(GPIO_Pin_8)

#define PORT_SWITCH_8 				(GPIOE)
#define PIN_SWITCH_8 				(GPIO_Pin_9)

#define PORT_SWITCH_9 				(GPIOE)
#define PIN_SWITCH_9 				(GPIO_Pin_10)

#define PORT_SWITCH_10 				(GPIOE)
#define PIN_SWITCH_10 				(GPIO_Pin_11)

#endif /* SYSTEM_PROJECT_FILE_H_ */
