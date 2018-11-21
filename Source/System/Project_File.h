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
#include "main.h"
#include "Timer4.h"
#include "devices.h"
#include "Common.h"
#include "Device_Action.h"
#include "HostProcess.h"
#include "HostComm.h"
#include "sensor.h"
#include "CRC16.h"
#include "TempControl.h"
#include "Laminating.h"
#include "Movement.h"
#include "Flash.h"
#include <stdio.h>
#include "Comm.h"
#include "Comm_CAN.h"
#include "Temp.h"
#include "adc.h"
#include "dma.h"
#include "TempControl.h"
#include "math.h"
#include "string.h"

/******************************************************************************/
#define PORT_SWITCH_1 				(GPIOC)
#define PIN_SWITCH_1 				(GPIO_Pin_4)

#define PORT_SWITCH_2 				(GPIOC)
#define PIN_SWITCH_2 				(GPIO_Pin_5)

#define PORT_SWITCH_3 				(GPIOB)
#define PIN_SWITCH_3 				(GPIO_Pin_0)

#define PORT_SWITCH_4 				(GPIOB)
#define PIN_SWITCH_4 				(GPIO_Pin_1)

#define PORT_SWITCH_5 				(GPIOE)
#define PIN_SWITCH_5 				(GPIO_Pin_7)

#define PORT_SWITCH_6 				(GPIOE)
#define PIN_SWITCH_6 				(GPIO_Pin_8)

#define PORT_SWITCH_7 				(GPIOE)
#define PIN_SWITCH_7				(GPIO_Pin_9)

#define PORT_SWITCH_8 				(GPIOE)
#define PIN_SWITCH_8 				(GPIO_Pin_10)

#define PORT_SWITCH_9 				(GPIOE)
#define PIN_SWITCH_9 				(GPIO_Pin_11)

#define PORT_SWITCH_10 				(GPIOE)
#define PIN_SWITCH_10 				(GPIO_Pin_12)

#define PORT_SWITCH_11 				(GPIOE)
#define PIN_SWITCH_11 				(GPIO_Pin_13)

#define PORT_SWITCH_12 				(GPIOE)
#define PIN_SWITCH_12 				(GPIO_Pin_14)

#define PORT_SWITCH_13 				(GPIOE)
#define PIN_SWITCH_13 				(GPIO_Pin_15)

#define PORT_SWITCH_14 				(GPIOB)
#define PIN_SWITCH_14 				(GPIO_Pin_10)

#define PORT_SWITCH_15 				(GPIOB)
#define PIN_SWITCH_15 				(GPIO_Pin_11)

/******************************************************************************/
#define HOT1   (1)
#define HOT2   (2)
#define HOT3   (3)



#endif /* SYSTEM_PROJECT_FILE_H_ */
