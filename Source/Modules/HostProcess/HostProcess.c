#include "HostProcess.h"

/******************************************************************************/
Judge DevicesInit_enable = FALSE;
LAMINATING Laminating;
/******************************************************************************/
HostComm_UartRxTypedef HostComm_UartRx;

/******************************************************************************/
void HostComm_Process(void)
{
	uint8 sBuffer[2] = {1},fBuffer[2] = {0};

	/* Command type */
	cmdType = cmdBuffer[OFFSET_CMD_TYPE];
	/* Command code */
	cmdCode = cmdBuffer[OFFSET_CMD_CODE];
	if ((cmdType == CMD_TYPE_APP) && HostComm_RecBufAvailable)
	{
		Send_Flag = 1;
		switch (cmdCode)
		{
		case CMD_CODE_CONNECT:
				HostComm_Cmd_Send_RawData(1, sBuffer,CMD_CODE_CONNECT);
			break;

		case CMD_CODE_OPEN:
			if(Start_Temp)
			{
				HostComm_Cmd_Send_RawData(1, fBuffer,CMD_CODE_SUCCESS);
			}
			else
			{
				L100_Switch = cmdBuffer[5];
				HostComm_Cmd_Send_RawData(1, sBuffer,CMD_CODE_SUCCESS);
			}
			break;

		case CMD_CODE_APPARATUS:
			if(!L100_Switch)
			{
				Valve5_Action();
				L100_Apparatus = cmdBuffer[5];
				HostComm_Cmd_Send_RawData(1, sBuffer,CMD_CODE_APPARATUS_ACHIEVE);
			}
			else
			{
				HostComm_Cmd_Send_RawData(1, fBuffer,CMD_CODE_APPARATUS_ACHIEVE);
			}
			break;

		case CMD_CODE_EXHAUST_AIR:
			Exhaus_Air_Act();
			break;

		case CMD_CODE_RECYCLE:
			Recycle_Bead_Act();
			break;

		case CMD_CODE_INJECT:
			Start_Filling();
			break;

		case CMD_CODE_WARM_TEMP:
			Control_Temperature = cmdBuffer[5];
			break;

		case CMD_CODE_WARM_TIME:
			Warm_Time = cmdBuffer[5];
			Warm_Time = Warm_Time*1000 - 1;
			break;

		case CMD_CODE_WARM_BLOCK1:
			Warm_Block1();
			break;

		case CMD_CODE_WARM_BLOCK2:
			Warm_Block2();
			break;

		case CMD_CODE_CARVE_DIRECTION:
			Carve_Action();
			break;

		case CMD_CODE_CARVE_RESET:
			Carve_Action();
			break;

		case CMD_CODE_WARM_BUMP:
			Warm_Bump();
			break;

		case CMD_CODE_CARVE_BUMP:
			Carve_Bump();
			break;

		case CMD_CODE_DEBUG:
			break;

		case CMD_CODE_NORMAL:
			break;

		case CMD_CODE_AIR_CYLINDER1:
			Valve1_Lock(CLOSED);
			break;

		case CMD_CODE_AIR_CYLINDER2:
			Valve2_Movement();
			break;

		case CMD_CODE_AIR_CYLINDER3:
			Valve3_Movement();
			break;

		case CMD_CODE_AIR_CYLINDER4:
			Valve4_Movement();
			break;
		case CMD_CODE_PRESS_PLATE:
			Press_Plate_Movement();
			break;

		case CMD_CODE_INJUCET_BUMP:
			Injucet_Bump_Switch();
			break;

		case CMD_CODE_INJUCET_VOLUME1:
			Injucet_Volume1();
			break;

		case CMD_CODE_INJUCET_VOLUME2:
			Injucet_Volume2();
			break;

		case CMD_CODE_INJUCET_VOLUME3:
			Injucet_Volume3();
			break;

		case CMD_CODE_INJUCET_VOLUME4:
			Injucet_Volume4();
			break;

		case CMD_CODE_INJUCET_VOLUME5:
			Injucet_Volume5();
			break;

		case CMD_CODE_INJUCET_VOLUME6:
			Injucet_Volume6();
			break;

		case CMD_CODE_INJUCET_VOLUME7:
			Injucet_Volume7();
			break;

		case CMD_CODE_INJUCET_TIME:
			Injucet_Time();
			break;

		default:
			break;
		}
		Send_Flag = 0;
		HostComm_RecBufAvailable = 0;
	}
}

/******************************************************************************/
static uint16 HostComm_Cmd_Respond_Common(uint16 cmdDataNum, uint8 cmdType,
		uint8 cmdCode)
{
	uint16 packageLength = 6 + cmdDataNum;
	uint16 crcCal = 0;

	/* Head */
	respBuffer[OFFSET_HEADER] = '$';

	/* Package length */
	respBuffer[OFFSET_LEN_LO] = Common_LoByte(packageLength);
	respBuffer[OFFSET_LEN_HI] = Common_HiByte(packageLength);

	/* Command type and code */
	respBuffer[OFFSET_CMD_TYPE] = cmdType;
	respBuffer[OFFSET_CMD_CODE] = cmdCode;

	/* Calculate CRC
	 * 1. &cmdBuffer[1]: because the first byte is '$' which is not included
	 *    in CRC calculation
	 * 2. cmdLength - 2: because cmdLength includes 2-byte CRC */
	crcCal = CRC16_Calculate(&respBuffer[1], packageLength - 2, 0xFFFF,
									0x0000);

	/* CRC */
	respBuffer[OFFSET_CMD_DATA + cmdDataNum] = Common_LoByte(crcCal);
	respBuffer[OFFSET_CMD_DATA + cmdDataNum + 1] = Common_HiByte(crcCal);

	/* Tail */
	respBuffer[OFFSET_CMD_DATA + cmdDataNum + 2] = '#';

	return packageLength;
}

/******************************************************************************/
uint8 HostComm_Cmd_Send_RawData(uint16 length, uint8 dataBuf[],OFFSET_HOSTCOMM CMD_CODE)
{
	uint16 totalPackageLength = 2; /* Include head and tail */
	uint16 cmdDataLength = 0;

	Send_Flag = 1;
	memcpy(&respBuffer[OFFSET_CMD_DATA], dataBuf, length);
	cmdDataLength = length;
	totalPackageLength += HostComm_Cmd_Respond_Common(cmdDataLength,
							CMD_TYPE_APP, CMD_CODE);
	HostComm_SendCommand(&respBuffer[0], totalPackageLength);
	HostComm_RecBufAvailable = 0;
	Send_Flag = 0;
	return 0;
}

/******************************************************************************/
void Exhaust_Air_Process (void)
{
	uint8 buf[2] = {0,0};
	if(1 == Exhaust_Air)
	{
		/* 开始排空  */
		buf[0] = 0X01;
		Comm_CanDirectSend(STDID_EXHAUST_AIR,buf,2);
		Exhaust_Air = 2;
	}

	if(0 == Exhaust_Air)
	{
		/* 结束排空  */
		buf[0] = 0X00;
		Comm_CanDirectSend(STDID_EXHAUST_AIR,buf,2);
		Exhaust_Air = 2;
	}
}

/******************************************************************************/
void Recycle_Bead_Process (void)
{
	uint8 buf[2] = {0,0};
	if(1 == Recycle_Bead)
	{
		/* 开始回收磁珠  */
		buf[0] = 0X01;
		Comm_CanDirectSend(STDID_RECYCLE_BEAD,buf,2);
		Recycle_Bead = 2;
	}

	if(0 == Recycle_Bead)
	{
		/* 停止回收磁珠  */
		buf[0] = 0X00;
		Comm_CanDirectSend(STDID_RECYCLE_BEAD,buf,2);
		Recycle_Bead = 2;
	}
}
