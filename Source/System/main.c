/*
 * Main.c
 *
 *  Created on: 2019��2��14��
 *      Author: Administrator
 */

/******************************************************************************/
#include "Project_File.h"

/******************************************************************************/
int main(void)
{
	SysTick_Init();

	HostComm_Init();

//	TIM5_Int_Init(9999,7199);			/* 10Khz�ļ���Ƶ�ʣ�������1000Ϊ100ms */

	Comm_Init();

	Devices_Init();

	PosSensor_Init();

	while(1)
	{
		HostComm_Process();
		Comm_Process();
	}
}
