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
void Infusion_Act (void)
{
	if(cmdBuffer[5])
	{
		HostComm_Cmd_Send_RawData(1, sBuffer,CMD_CODE_INFUSION);
		Delay_ms_SW(5);
		Comm_CanDirectSend(STDID_INFUSION_PREPARE, CAN_Buffer, 1);
		Infusion_Air_50ul();
	}
	else
	{
		HostComm_Cmd_Send_RawData(1, fBuffer,CMD_CODE_INFUSION);
	}
}

/******************************************************************************/
void Inject_Act (void)
{
	if(cmdBuffer[5])
	{
		Buffer[0] = 1;
		HostComm_Cmd_Send_RawData(1, Buffer,CMD_CODE_INJECT);
		CAN_Buffer[0] = 0;
		Comm_CanDirectSend(STDID_INJECT_PREPARE,CAN_Buffer,1);
	}
	else
	{
		Buffer[0] = 0;
		HostComm_Cmd_Send_RawData(1, Buffer,CMD_CODE_INJECT);
	}
}

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
void Bump_Initialize (void)
{
	if(cmdBuffer[5])
	{
		Buffer[0] = 1;
		HostComm_Cmd_Send_RawData(1, Buffer,CMD_CODE_BUMP_INT);
		Buffer[0] = 0;
		Comm_CanDirectSend(STDID_BUMP_INT_PREPARE,Buffer,1);
	}
	else
	{
		Buffer[0] = 0;
		HostComm_Cmd_Send_RawData(1, Buffer,CMD_CODE_BUMP_INT);
	}
}

/******************************************************************************/
void Bump_Wash_Act (void)
{
	uint8 buf[2] = {0,0};
	if(cmdBuffer[5])
	{
		Bump_Wash = 1;
		Waste_Bump = 1;
		Wash_time_second = cmdBuffer[5];
		HostComm_Cmd_Send_RawData(1, sBuffer,CMD_CODE_WASH);

		/* 开始清洗  */
		buf[0] = 0X01;
		Comm_CanDirectSend(STDID_BUMP_WASH,buf,1);
	}
	else
	{
		Bump_Wash = 0;
		Waste_Bump = 0;
		Wash_time_second = 0;
		HostComm_Cmd_Send_RawData(1, fBuffer,CMD_CODE_WASH);

		/* 停止清洗  */
		buf[0] = 0X00;
		Comm_CanDirectSend(STDID_BUMP_WASH,buf,1);
	}
}

/******************************************************************************/
void Injucet_Bump_Switch (void)
{
	uint8 Bump_Data[2] = {0},DATA = 0;
	switch(cmdBuffer[5])
	{
	case 0:
		/* 柱塞泵全部关闭 */
		Bump_Switch = 0;
		Bump_Data[0] = Bump_Switch;
		DATA = 0;
		Bump_Data[1] = DATA;
		Comm_CanDirectSend(STDID_SEND_BUMP,Bump_Data,2);
		Delay_ms_SW(4);
		sBuffer[1] = 0;
		HostComm_Cmd_Send_RawData(2, sBuffer,CMD_CODE_INJUCET_BUMP);
		break;
	case 1:
		if(cmdBuffer[6])
		{
			Bump_Switch |= 0x01;
			Bump_Data[0] = Bump_Switch;
			DATA |= 0x01;
			Bump_Data[1] = DATA;
			Comm_CanDirectSend(STDID_SEND_BUMP,Bump_Data,2);
			Delay_ms_SW(4);
			sBuffer[1] = 1;
			HostComm_Cmd_Send_RawData(2, sBuffer,CMD_CODE_INJUCET_BUMP);
		}
		else
		{
			Bump_Switch &= 0xFE;
			Bump_Data[0] = Bump_Switch;
			DATA &= 0xFE;
			Bump_Data[1] = DATA;
			Comm_CanDirectSend(STDID_SEND_BUMP,Bump_Data,2);
			Delay_ms_SW(4);
			fBuffer[1] = 1;
			HostComm_Cmd_Send_RawData(2, fBuffer,CMD_CODE_INJUCET_BUMP);
		}
		break;
	case 2:
		if(cmdBuffer[6])
		{
			Bump_Switch |= 0x02;
			Bump_Data[0] = Bump_Switch;
			DATA |= 0x02;
			Bump_Data[1] = DATA;
			Comm_CanDirectSend(STDID_SEND_BUMP,Bump_Data,2);
			Delay_ms_SW(4);
			sBuffer[1] = 2;
			HostComm_Cmd_Send_RawData(2, sBuffer,CMD_CODE_INJUCET_BUMP);
		}
		else
		{
			Bump_Switch &= 0xFD;
			Bump_Data[0] = Bump_Switch;
			DATA &= 0xFD;
			Bump_Data[1] = DATA;
			Comm_CanDirectSend(STDID_SEND_BUMP,Bump_Data,2);
			Delay_ms_SW(4);
			fBuffer[1] = 2;
			HostComm_Cmd_Send_RawData(2, fBuffer,CMD_CODE_INJUCET_BUMP);
		}
		break;
	case 3:
		if(cmdBuffer[6])
		{
			Bump_Switch |= 0x04;
			Bump_Data[0] = Bump_Switch;
			DATA |= 0x04;
			Bump_Data[1] = DATA;
			Comm_CanDirectSend(STDID_SEND_BUMP,Bump_Data,2);
			Delay_ms_SW(4);
			sBuffer[1] = 3;
			HostComm_Cmd_Send_RawData(2, sBuffer,CMD_CODE_INJUCET_BUMP);
		}
		else
		{
			Bump_Switch &= 0xFB;
			Bump_Data[0] = Bump_Switch;
			DATA &= 0xFB;
			Bump_Data[1] = DATA;
			Comm_CanDirectSend(STDID_SEND_BUMP,Bump_Data,2);
			Delay_ms_SW(4);
			fBuffer[1] = 3;
			HostComm_Cmd_Send_RawData(2, fBuffer,CMD_CODE_INJUCET_BUMP);
		}
		break;
	case 4:
		if(cmdBuffer[6])
		{
			Bump_Switch |= 0x08;
			Bump_Data[0] = Bump_Switch;
			DATA |= 0x08;
			Bump_Data[1] = DATA;
			Comm_CanDirectSend(STDID_SEND_BUMP,Bump_Data,2);
			Delay_ms_SW(4);
			sBuffer[1] = 4;
			HostComm_Cmd_Send_RawData(2, sBuffer,CMD_CODE_INJUCET_BUMP);
		}
		else
		{
			Bump_Switch &= 0xF7;
			Bump_Data[0] = Bump_Switch;
			DATA &= 0xF7;
			Bump_Data[1] = DATA;
			Comm_CanDirectSend(STDID_SEND_BUMP,Bump_Data,2);
			Delay_ms_SW(4);
			fBuffer[1] = 4;
			HostComm_Cmd_Send_RawData(2, fBuffer,CMD_CODE_INJUCET_BUMP);
		}
		break;
	case 5:
		if(cmdBuffer[6])
		{
			Bump_Switch |= 0x10;
			Bump_Data[0] = Bump_Switch;
			DATA |= 0x10;
			Bump_Data[1] = DATA;
			Comm_CanDirectSend(STDID_SEND_BUMP,Bump_Data,2);
			Delay_ms_SW(4);
			sBuffer[1] = 5;
			HostComm_Cmd_Send_RawData(2, sBuffer,CMD_CODE_INJUCET_BUMP);
		}
		else
		{
			Bump_Switch &= 0xEF;
			Bump_Data[0] = Bump_Switch;
			DATA &= 0xEF;
			Bump_Data[1] = DATA;
			Comm_CanDirectSend(STDID_SEND_BUMP,Bump_Data,2);
			Delay_ms_SW(4);
			fBuffer[1] = 5;
			HostComm_Cmd_Send_RawData(2, fBuffer,CMD_CODE_INJUCET_BUMP);
		}
		break;
	case 6:
		if(cmdBuffer[6])
		{
			Bump_Switch |= 0x20;
			Bump_Data[0] = Bump_Switch;
			DATA |= 0x20;
			Bump_Data[1] = DATA;
			Comm_CanDirectSend(STDID_SEND_BUMP,Bump_Data,2);
			Delay_ms_SW(4);
			sBuffer[1] = 6;
			HostComm_Cmd_Send_RawData(2, sBuffer,CMD_CODE_INJUCET_BUMP);
		}
		else
		{
			Bump_Switch &= 0xDF;
			Bump_Data[0] = Bump_Switch;
			DATA &= 0xDF;
			Bump_Data[1] = DATA;
			Comm_CanDirectSend(STDID_SEND_BUMP,Bump_Data,2);
			Delay_ms_SW(4);
			fBuffer[1] = 6;
			HostComm_Cmd_Send_RawData(2, fBuffer,CMD_CODE_INJUCET_BUMP);
		}
		break;
	case 7:
		if(cmdBuffer[6])
		{
			Bump_Switch |= 0x40;
			Bump_Data[0] = Bump_Switch;
			DATA |= 0x40;
			Bump_Data[1] = DATA;
			Comm_CanDirectSend(STDID_SEND_BUMP,Bump_Data,2);
			Delay_ms_SW(4);
			sBuffer[1] = 7;
			HostComm_Cmd_Send_RawData(2, sBuffer,CMD_CODE_INJUCET_BUMP);
		}
		else
		{
			Bump_Switch &= 0xBF;
			Bump_Data[0] = Bump_Switch;
			DATA &= 0xBF;
			Bump_Data[1] = DATA;
			Comm_CanDirectSend(STDID_SEND_BUMP,Bump_Data,2);
			Delay_ms_SW(4);
			fBuffer[1] = 7;
			HostComm_Cmd_Send_RawData(2, fBuffer,CMD_CODE_INJUCET_BUMP);
		}
		break;
	case 8:
		/* 柱塞泵全部打开 */
		Bump_Switch = 255;
		Bump_Data[0] = Bump_Switch;
		DATA = 255;
		Bump_Data[1] = DATA;
		Comm_CanDirectSend(STDID_SEND_BUMP,Bump_Data,2);
		Delay_ms_SW(4);
		sBuffer[1] = 8;
		HostComm_Cmd_Send_RawData(2, sBuffer,CMD_CODE_INJUCET_BUMP);
		break;
	default:
		break;
	}
}

/******************************************************************************/
void Injucet_Volume1 (void)
{
	uint8 MBuffer[3] = {0};
	MBuffer[0] = 0x01;
	memcpy(&MBuffer[1],&cmdBuffer[5],2);
	Comm_CanDirectSend(STDID_SEND_BUMP_VOL,MBuffer,3);
	Delay_ms_SW(2);
	HostComm_Cmd_Send_RawData(2, sBuffer,CMD_CODE_INJUCET_VOLUME1);
}

/******************************************************************************/
void Injucet_Volume2 (void)
{
	uint8 MBuffer[3] = {0};
	MBuffer[0] = 0x02;
	memcpy(&MBuffer[1],&cmdBuffer[5],2);
	Comm_CanDirectSend(STDID_SEND_BUMP_VOL,MBuffer,3);
	Delay_ms_SW(2);
	HostComm_Cmd_Send_RawData(2, sBuffer,CMD_CODE_INJUCET_VOLUME2);
}

/******************************************************************************/
void Injucet_Volume3 (void)
{
	uint8 MBuffer[3] = {0};
	MBuffer[0] = 0x04;
	memcpy(&MBuffer[1],&cmdBuffer[5],2);
	Comm_CanDirectSend(STDID_SEND_BUMP_VOL,MBuffer,3);
	Delay_ms_SW(2);
	HostComm_Cmd_Send_RawData(2, sBuffer,CMD_CODE_INJUCET_VOLUME3);
}

/******************************************************************************/
void Injucet_Volume4 (void)
{
	uint8 MBuffer[3] = {0};
	MBuffer[0] = 0x08;
	memcpy(&MBuffer[1],&cmdBuffer[5],2);
	Comm_CanDirectSend(STDID_SEND_BUMP_VOL,MBuffer,3);
	Delay_ms_SW(2);
	HostComm_Cmd_Send_RawData(2, sBuffer,CMD_CODE_INJUCET_VOLUME4);
}

/******************************************************************************/
void Injucet_Volume5 (void)
{
	uint8 MBuffer[3] = {0};
	MBuffer[0] = 0x10;
	memcpy(&MBuffer[1],&cmdBuffer[5],2);
	Comm_CanDirectSend(STDID_SEND_BUMP_VOL,MBuffer,3);
	Delay_ms_SW(2);
	HostComm_Cmd_Send_RawData(2, sBuffer,CMD_CODE_INJUCET_VOLUME5);
}

/******************************************************************************/
void Injucet_Volume6 (void)
{
	uint8 MBuffer[3] = {0};
	MBuffer[0] = 0x20;
	memcpy(&MBuffer[1],&cmdBuffer[5],2);
	Comm_CanDirectSend(STDID_SEND_BUMP_VOL,MBuffer,3);
	Delay_ms_SW(2);
	HostComm_Cmd_Send_RawData(2, sBuffer,CMD_CODE_INJUCET_VOLUME6);
}

/******************************************************************************/
void Injucet_Volume7 (void)
{
	uint8 MBuffer[3] = {0};
	MBuffer[0] = 0x40;
	memcpy(&MBuffer[1],&cmdBuffer[5],2);
	Comm_CanDirectSend(STDID_SEND_BUMP_VOL,MBuffer,3);
	Delay_ms_SW(2);
	HostComm_Cmd_Send_RawData(2, sBuffer,CMD_CODE_INJUCET_VOLUME7);
}

