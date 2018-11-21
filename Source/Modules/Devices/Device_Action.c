/*
 * HostProcess_Ation.c
 *
 *  Created on: 2018年11月5日
 *      Author: Administrator
 */
/******************************************************************************/
#include "Device_Action.h"

/******************************************************************************/
uint8 sBuffer[2] = {1},fBuffer[2] = {0},Buffer[2] = {0};

/******************************************************************************/
void Start_Filling (void)
{
	if(!L100_Switch)
	{
//		/* 检测试剂条  */
//		Fiber_Optic |= GPIO_ReadInputDataBit(PORT_SWITCH_7, PIN_SWITCH_7)?(1<<0):(0<<0);
//		sBuffer[0] = Common_HiByte(Fiber_Optic);
//		sBuffer[1] = Common_LoByte(Fiber_Optic);

		/* 发送灌装命令  */
		Comm_CanDirectSend(STDID_START,sBuffer,2);
		Delay_ms_SW(10);

		Fiber_Optic = 8;							//预设值

		if(Fiber_Optic)                                               
		Comm_CanDirectSend(STDID_INFUSION_PREPARE,sBuffer,2);
		Delay_ms_SW(10);
		sBuffer[0] = 1;
		HostComm_Cmd_Send_RawData(1, sBuffer,CMD_CODE_INJECT);
	}
	else
	{
		sBuffer[0] = 0;
		HostComm_Cmd_Send_RawData(1, sBuffer,CMD_CODE_INJECT);
	}
}

/******************************************************************************/
void Warm_Block1 (void)
{
	if(cmdBuffer[5])
	{
		Temp_Count |= 0x01;
		HostComm_Cmd_Send_RawData(1, sBuffer,CMD_CODE_WARM_BLOCK1);
	}
	else
	{
		Temp_Count &= 0XFE;
		HostComm_Cmd_Send_RawData(1, fBuffer,CMD_CODE_WARM_BLOCK1);

	}
}

/******************************************************************************/
void Warm_Block2 (void)
{
	if(cmdBuffer[5])
	{
		Temp_Count |= 0X02;
		HostComm_Cmd_Send_RawData(1, sBuffer,CMD_CODE_WARM_BLOCK2);
	}
	else
	{
		Temp_Count &= 0XFD;
		HostComm_Cmd_Send_RawData(1, fBuffer,CMD_CODE_WARM_BLOCK2);
	}
}

/******************************************************************************/
void Carve_Action (void)
{
	if(0 == cmdBuffer[5])
	{
		/* 运动架6 8 运动  */
		Valve6_Lock(CLOSED);
		Valve8_Lock(OPEN);
		HostComm_Cmd_Send_RawData(1, fBuffer,CMD_CODE_CARVE_DIRECTION);
	}

	if(1 == cmdBuffer[5])
	{
		/* 运动架6 8 运动  */
		Valve6_Lock(CLOSED);
		HostComm_Cmd_Send_RawData(1, sBuffer,CMD_CODE_CARVE_DIRECTION);
		Delay_ms_SW(800);
		Valve8_Lock(CLOSED);
		Buffer[1] = 0X01,Buffer[0] = 0X05;						//滑块挡柱3
		Comm_CanDirectSend(STDID_RX_VALVE_LOCK,Buffer,2);
		Delay_ms_SW(10);
		HostComm_Cmd_Send_RawData(1, sBuffer,CMD_CODE_CARVE_BUMP);
	}

	if(2 == cmdBuffer[5])
	{
		/* 运动架6 8 运动  */
		Buffer[1] = 0X01,Buffer[0] = 0X05;						//滑块挡柱3
		Comm_CanDirectSend(STDID_RX_VALVE_LOCK,Buffer,2);
		Delay_ms_SW(10);
		Valve6_Lock(CLOSED);
		Delay_ms_SW(1000);
		Valve8_Lock(CLOSED);
		Delay_ms_SW(2500);

		Valve8_Lock(OPEN);
		Delay_ms_SW(2500);

		Valve6_Lock(OPEN);
		Valve8_Lock(OPEN);
		Delay_ms_SW(500);
		Valve7_Lock(CLOSED);
		Buffer[1] = 0X00,Buffer[0] = 0X05;
		Comm_CanDirectSend(STDID_RX_VALVE_LOCK,Buffer,2);
		Delay_ms_SW(2500);
		Valve7_Lock(OPEN);

		Delay_ms_SW(10);
		HostComm_Cmd_Send_RawData(1, fBuffer,CMD_CODE_CARVE_BUMP);
	}
}

/******************************************************************************/
void Warm_Bump (void)
{
	if(cmdBuffer[5])
	{
		Buffer[1] = 0X01,Buffer[0] = 0X04;						//滑块挡柱1
		Comm_CanDirectSend(STDID_RX_VALVE_LOCK,Buffer,2);
		Delay_ms_SW(10);
		Buffer[1] = 0X01,Buffer[0] = 0X03;						//滑块挡柱2
		Comm_CanDirectSend(STDID_RX_VALVE_LOCK,Buffer,2);
		Delay_ms_SW(10);
		HostComm_Cmd_Send_RawData(1, sBuffer,CMD_CODE_WARM_BUMP);
	}
	else
	{
		Buffer[1] = 0X00,Buffer[0] = 0X04;						//滑块挡柱1
		Comm_CanDirectSend(STDID_RX_VALVE_LOCK,Buffer,2);
		Delay_ms_SW(10);
		Buffer[1] = 0X00,Buffer[0] = 0X03;						//滑块挡柱2
		Comm_CanDirectSend(STDID_RX_VALVE_LOCK,Buffer,2);
		Delay_ms_SW(10);
		HostComm_Cmd_Send_RawData(1, fBuffer,CMD_CODE_WARM_BUMP);
	}
}

/******************************************************************************/
void Carve_Bump (void)
{
	if(cmdBuffer[5])
	{
		Buffer[1] = 0X01,Buffer[0] = 0X05;						//滑块挡柱3
		Comm_CanDirectSend(STDID_RX_VALVE_LOCK,Buffer,2);
		Delay_ms_SW(10);
		HostComm_Cmd_Send_RawData(1, sBuffer,CMD_CODE_CARVE_BUMP);
	}
	else
	{
		Buffer[1] = 0X00,Buffer[0] = 0X05;						//滑块挡柱3
		Comm_CanDirectSend(STDID_RX_VALVE_LOCK,Buffer,2);
		Delay_ms_SW(10);
		HostComm_Cmd_Send_RawData(1, fBuffer,CMD_CODE_CARVE_BUMP);
	}
}

/******************************************************************************/
void Valve2_Movement (void)
{
	Valve2_Lock(CLOSED);
	Delay_ms_SW(800);

	/* 后方挡柱 */
	Buffer[1] = 0X01,Buffer[0] = 0X04;
	Comm_CanDirectSend(STDID_RX_VALVE_LOCK,Buffer,2);
	Delay_ms_SW(10);

	/* 前方挡柱 */
	Buffer[1] = 0X01,Buffer[0] = 0X03;
	Comm_CanDirectSend(STDID_RX_VALVE_LOCK,Buffer,2);
	Delay_ms_SW(10);

	HostComm_Cmd_Send_RawData(1, sBuffer,CMD_CODE_WARM_BUMP);

	Delay_ms_SW(1100);
	Valve2_Lock(OPEN);
}


/******************************************************************************/
void Valve3_Movement (void)
{
	Valve7_Lock(CLOSED);
}

/******************************************************************************/
void Valve4_Movement (void)
{
	Valve9_Lock(CLOSED);
	Delay_ms_SW(1100);
	Valve9_Lock(OPEN);
}

/******************************************************************************/
void Press_Plate_Movement (void)
{
	if(cmdBuffer[5])
	{
		Valve5_Lock(CLOSED);
		HostComm_Cmd_Send_RawData(1, sBuffer,CMD_CODE_PRESS_PLATE);
	}
	else
	{
		Valve5_Lock(OPEN);
		HostComm_Cmd_Send_RawData(1, fBuffer,CMD_CODE_PRESS_PLATE);
	}
}

/******************************************************************************/
void Exhaus_Air_Act (void)
{
	if(cmdBuffer[5])
	{
		Exhaust_Air = cmdBuffer[5];
		HostComm_Cmd_Send_RawData(1, sBuffer,CMD_CODE_EXHAUST_AIR);
	}
	else
	{
		Exhaust_Air = cmdBuffer[5];
		HostComm_Cmd_Send_RawData(1, fBuffer,CMD_CODE_EXHAUST_AIR);
	}
}

/******************************************************************************/
void Recycle_Bead_Act (void)
{
	if(cmdBuffer[5])
	{
		Recycle_Bead = cmdBuffer[5];
		HostComm_Cmd_Send_RawData(1, sBuffer,CMD_CODE_RECYCLE);
	}
	else
	{
		Recycle_Bead = cmdBuffer[5];
		HostComm_Cmd_Send_RawData(1, fBuffer,CMD_CODE_RECYCLE);
	}
}

/******************************************************************************/
void Injucet_Bump_Switch (void)
{
	uint8 Bump_Data[2] = {0},DATA = 0;
	switch(cmdBuffer[5])
	{
	case 0:
		/* 注射泵全部关闭 */
		Bump_Switch = 0;
		Bump_Data[0] = Bump_Switch;
		DATA = 0;
		Bump_Data[1] = DATA;
		Comm_CanDirectSend(STDID_SEND_BUMP,Bump_Data,2);
		Delay_ms_SW(10);
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
			Delay_ms_SW(10);
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
			Delay_ms_SW(10);
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
			Delay_ms_SW(10);
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
			Delay_ms_SW(10);
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
			Delay_ms_SW(10);
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
			Delay_ms_SW(10);
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
			Delay_ms_SW(10);
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
			Delay_ms_SW(10);
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
			Delay_ms_SW(10);
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
			Delay_ms_SW(10);
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
			Delay_ms_SW(10);
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
			Delay_ms_SW(10);
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
			Delay_ms_SW(10);
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
			Delay_ms_SW(10);
			fBuffer[1] = 7;
			HostComm_Cmd_Send_RawData(2, fBuffer,CMD_CODE_INJUCET_BUMP);
		}
		break;
	case 8:
		/* 注射泵全部打开 */
		Bump_Switch = 255;
		Bump_Data[0] = Bump_Switch;
		DATA = 255;
		Bump_Data[1] = DATA;
		Comm_CanDirectSend(STDID_SEND_BUMP,Bump_Data,2);
		Delay_ms_SW(10);
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
	Delay_ms_SW(10);
	HostComm_Cmd_Send_RawData(2, sBuffer,CMD_CODE_INJUCET_VOLUME1);
}

/******************************************************************************/
void Injucet_Volume2 (void)
{
	uint8 MBuffer[3] = {0};
	MBuffer[0] = 0x02;
	memcpy(&MBuffer[1],&cmdBuffer[5],2);
	Comm_CanDirectSend(STDID_SEND_BUMP_VOL,MBuffer,3);
	Delay_ms_SW(10);
	HostComm_Cmd_Send_RawData(2, sBuffer,CMD_CODE_INJUCET_VOLUME2);
}

/******************************************************************************/
void Injucet_Volume3 (void)
{
	uint8 MBuffer[3] = {0};
	MBuffer[0] = 0x04;
	memcpy(&MBuffer[1],&cmdBuffer[5],2);
	Comm_CanDirectSend(STDID_SEND_BUMP_VOL,MBuffer,3);
	Delay_ms_SW(10);
	HostComm_Cmd_Send_RawData(2, sBuffer,CMD_CODE_INJUCET_VOLUME3);
}

/******************************************************************************/
void Injucet_Volume4 (void)
{
	uint8 MBuffer[3] = {0};
	MBuffer[0] = 0x08;
	memcpy(&MBuffer[1],&cmdBuffer[5],2);
	Comm_CanDirectSend(STDID_SEND_BUMP_VOL,MBuffer,3);
	Delay_ms_SW(10);
	HostComm_Cmd_Send_RawData(2, sBuffer,CMD_CODE_INJUCET_VOLUME4);
}

/******************************************************************************/
void Injucet_Volume5 (void)
{
	uint8 MBuffer[3] = {0};
	MBuffer[0] = 0x10;
	memcpy(&MBuffer[1],&cmdBuffer[5],2);
	Comm_CanDirectSend(STDID_SEND_BUMP_VOL,MBuffer,3);
	Delay_ms_SW(10);
	HostComm_Cmd_Send_RawData(2, sBuffer,CMD_CODE_INJUCET_VOLUME5);
}

/******************************************************************************/
void Injucet_Volume6 (void)
{
	uint8 MBuffer[3] = {0};
	MBuffer[0] = 0x20;
	memcpy(&MBuffer[1],&cmdBuffer[5],2);
	Comm_CanDirectSend(STDID_SEND_BUMP_VOL,MBuffer,3);
	Delay_ms_SW(10);
	HostComm_Cmd_Send_RawData(2, sBuffer,CMD_CODE_INJUCET_VOLUME6);
}

/******************************************************************************/
void Injucet_Volume7 (void)
{
	uint8 MBuffer[3] = {0};
	MBuffer[0] = 0x40;
	memcpy(&MBuffer[1],&cmdBuffer[5],2);
	Comm_CanDirectSend(STDID_SEND_BUMP_VOL,MBuffer,3);
	Delay_ms_SW(10);
	HostComm_Cmd_Send_RawData(2, sBuffer,CMD_CODE_INJUCET_VOLUME7);
}

/******************************************************************************/
void Injucet_Time (void)
{
	uint8 MBuffer[2] = {0};
	memcpy(MBuffer,&cmdBuffer[5],2);
	Comm_CanDirectSend(STDID_SEND_INJUCET_TIME,MBuffer,2);
	Delay_ms_SW(10);
	HostComm_Cmd_Send_RawData(2, sBuffer,CMD_CODE_INJUCET_TIME);
}
