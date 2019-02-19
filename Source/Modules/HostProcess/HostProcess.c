#include "HostProcess.h"

/******************************************************************************/
Judge DevicesInit_enable = FALSE;
LAMINATING Laminating;
/******************************************************************************/
HostComm_UartRxTypedef HostComm_UartRx;

/******************************************************************************/
void HostComm_Process(void)
{
	if(HostComm_RecBufAvailable)
	{
		HostComm_RecBufAvailable = 0;
		HostComm_Cmd_Process();
	}
}

/******************************************************************************/
void HostComm_Cmd_Process (void)
{
	uint8 sBuffer[2] = {1};

	/* Command type */
	cmdType = cmdBuffer[OFFSET_CMD_TYPE];
	/* Command code */
	cmdCode = cmdBuffer[OFFSET_CMD_CODE];

	if (cmdType == CMD_TYPE_APP)
	{
		switch (cmdCode)
		{
		case CMD_CODE_CONNECT:
			HostComm_Cmd_Send_RawData(1, sBuffer,CMD_CODE_CONNECT);
			break;

		case CMD_CODE_INFUSION:
			Infusion_Act();
			break;

		case CMD_CODE_WASH:
			Bump_Wash_Act();
			break;

		case CMD_CODE_INJECT:
			Start_Filling();
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

		case CMD_CODE_RETURN_ZERO:
			Comm_CanDirectSend(STDID_SEND_BACK_ZERO,sBuffer,1);
			break;

		case CMD_CODE_BUMP_INT:
			Bump_Initialize();
			break;

		default:
			break;
		}

		memset(cmdBuffer,0,30);
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

	memcpy(&respBuffer[OFFSET_CMD_DATA], dataBuf, length);
	cmdDataLength = length;
	totalPackageLength += HostComm_Cmd_Respond_Common(cmdDataLength,
							CMD_TYPE_APP, CMD_CODE);
	HostComm_SendCommand(&respBuffer[0], totalPackageLength);
	return 0;
}
