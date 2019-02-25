/*
 * Main.c
 *
 *  Created on: 2019Äê2ÔÂ14ÈÕ
 *      Author: Administrator
 */

/******************************************************************************/
#include "Project_File.h"

/******************************************************************************/
void Pump_Test(void);
void RCC_Configuration (void);

/******************************************************************************/
int main(void)
{
	SysTick_Init();

	RCC_Configuration();				/* RCC Initialize */

	HostComm_Init();

	Comm_Init();

	TIM6_Int_Init(9999,7199);

	PosSensor_Init();

	Devices_Init();

//	Pump_Test();

	while(1)
	{
		HostComm_Process();
		Comm_Process();
	}
}

/******************************************************************************/
void Pump_Test(void)
{
	/**************************************************************************/
	Movement_GotoInitialPosition();

	/**************************************************************************/
#if TIMER1_M10_R1_R2_ENABLED
#if CH1_ENABLED
	Movement_M10_GotoTarget(DIR_CCW, 3 * PumpPrecision_Step_R1);
#endif
#if CH2_ENABLED
	Movement_M10_GotoTarget(DIR_CCW, 3 * PumpPrecision_Step_R2);
#endif
#endif
	/**************************************************************************/
#if TIMER2_M3_M_W1_ENABLED
	Movement_M3_GotoTarget(DIR_CCW, 3 * PumpPrecision_Step_M);
#endif
	/**************************************************************************/
#if TIMER3_M6_W2_W3_ENABLED
	Movement_M6_GotoTarget(DIR_CCW, 3 * PumpPrecision_Step_W);
#endif
	/**************************************************************************/
#if TIMER4_M4_W6_BASE_ENABLED
	Movement_M4_GotoTarget(DIR_CCW, 3 * PumpPrecision_Step_BASE);
#endif
	/**************************************************************************/
#if TIMER5_M1_W4_W5_ENABLED
	Movement_M1_GotoTarget(DIR_CCW, 3 * PumpPrecision_Step_W);
#endif

	/**************************************************************************/
#if TIMER1_M10_R1_R2_ENABLED
	while(Movement_M10_start);
#endif
#if TIMER2_M3_M_W1_ENABLED
	while(Movement_M3_start);
#endif
#if TIMER3_M6_W2_W3_ENABLED
	while(Movement_M6_start);
#endif
#if TIMER4_M4_W6_BASE_ENABLED
	while(Movement_M4_start);
#endif
#if TIMER5_M1_W4_W5_ENABLED
	while(Movement_M1_start);
#endif
}

/******************************************************************************/
void RCC_Configuration (void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE);
}
