/*
 * HostProcess_Ation.c
 *
 *  Created on: 2018年11月5日
 *      Author: Administrator
 */
/******************************************************************************/
#include "Device_Action.h"
#include "Comm_CAN.h"

/******************************************************************************/
void Filling_Act (void)
{
	if(cmdBuffer[5])
	{
		Buffer[0] = 1;
		L100_Filling = 1;
		HostComm_Cmd_Send_RawData(1, Buffer,CMD_CODE_BUMP_FILLING);
		Delay_ms_SW(5);
		Comm_CanDirectSend(STDID_SEND_BACK_ZERO, CAN_Buffer, 1);
	}
	else
	{
		Buffer[0] = 0;
		HostComm_Cmd_Send_RawData(1, Buffer,CMD_CODE_BUMP_FILLING);
	}
}

/******************************************************************************/
void Bump_Wash_Act (void)
{
	uint8 buf[2] = {0,0};
	if(cmdBuffer[5])
	{
		HostComm_Cmd_Send_RawData(1, sBuffer,CMD_CODE_WASH);

		/* 开始清洗  */
		buf[0] = 0X01;
		Comm_CanDirectSend(STDID_PUMP_WASH_PREARE, buf, 1);
	}
	else
	{
		DIAP_PUMP_OPEN();
		Waste_Bump_Count = 0;
		Waste_Bump_Open = 0;
		Waste_Bump_Closed = 0;
		HostComm_Cmd_Send_RawData(1, fBuffer,CMD_CODE_WASH);

		/* 停止清洗  */
		buf[0] = 0X00;
		Comm_CanDirectSend(STDID_PUMP_WASH_PREARE, buf, 1);
	}
}

/******************************************************************************/
void Injucet_Volume_R1 (void)
{
	uint16 MBuffer = 0;
	memcpy(&MBuffer,&cmdBuffer[5],2);
	PumpPrecision_Step_R1 = MBuffer * Base_Calculation_1ml;
}

/******************************************************************************/
void Injucet_Volume_R2 (void)
{
	uint8 MBuffer[3] = {0};
	MBuffer[0] = VOLUME_R2;
	memcpy(&MBuffer[1],&cmdBuffer[5],2);
	Comm_CanDirectSend(STDID_SEND_BUMP_VOL,MBuffer,3);
}

/******************************************************************************/
void Injucet_Volume_M (void)
{
	uint16 MBuffer = 0;
	memcpy(&MBuffer,&cmdBuffer[5],2);
	PumpPrecision_Step_M = MBuffer * Base_Calculation_1ml;
}

/******************************************************************************/
void Injucet_Volume_W (void)
{
	uint16 DATA = 0;
	uint8 MBuffer[3] = {0};
	MBuffer[0] = VOLUME_W;
	memcpy(&MBuffer[1],&cmdBuffer[5],2);
	memcpy(&DATA,&cmdBuffer[5],2);
	PumpPrecision_Step_W = DATA * Base_Calculation_5ml;
	Comm_CanDirectSend(STDID_SEND_BUMP_VOL,MBuffer,3);
}

/******************************************************************************/
void Injucet_Volume_BASE (void)
{
	uint8 MBuffer[3] = {0};
	MBuffer[0] = VOLUME_BASE;
	memcpy(&MBuffer[1],&cmdBuffer[5],2);
	Comm_CanDirectSend(STDID_SEND_BUMP_VOL,MBuffer,3);
}

/******************************************************************************/
void Set_Volume(uint8 *data)
{
	uint16 MBuffer = 0;
	switch(data[0])
	{
	case VOLUME_W:
		memcpy(&MBuffer,&data[1],2);
		PumpPrecision_Step_W = MBuffer * Base_Calculation_5ml;
		break;

	case VOLUME_BASE:
		memcpy(&MBuffer,&data[1],2);
		PumpPrecision_Step_BASE = MBuffer * Base_Calculation_5ml;
		break;

	case VOLUME_R2:
		memcpy(&MBuffer,&data[1],2);
		PumpPrecision_Step_R2 = MBuffer * Base_Calculation_1ml;
		break;

	default:
		break;
	}
}

