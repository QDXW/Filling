#ifndef SOURCE_MODULES_HOSTPROCESS_H_
#define SOURCE_MODULES_HOSTPROCESS_H_

/******************************************************************************/
#include "Project_File.h"

/******************************************************************************/
#define HOSTCOMM_UART_DATA_LEN_MAX				(512)

#define STDID_DEVICES_PUMP_CONTROL				(0X1001)

/******************************************************************************/
typedef struct
{
	Judge isRecvSuccess;								/* 一帧数据接收完成 */
	uint8 length;									/* 接收到帧长度 */
	uint8 buf[HOSTCOMM_UART_DATA_LEN_MAX];			/* 帧缓存 */
	uint8 validBuf[HOSTCOMM_UART_DATA_LEN_MAX/8];	/* 提取的帧有效数据 */

} HostComm_UartRxTypedef;

/******************************************************************************/
typedef enum
{
	OFFSET_HEADER = 0,
	OFFSET_LEN_LO,
	OFFSET_LEN_HI,
	OFFSET_CMD_TYPE,
	OFFSET_CMD_CODE,
	OFFSET_CMD_DATA,
	CMD_TYPE_APP = 0x10,
	CMD_CODE_OPEN,
	CMD_CODE_TEMP,
	CMD_CODE_SUCCESS,
	CMD_CODE_APPARATUS,
	CMD_CODE_APPARATUS_ACHIEVE,
	CMD_CODE_INITIALIZE,
	CMD_CODE_CONNECT,
	CMD_CODE_INFUSION,
	CMD_CODE_WASH,
	CMD_CODE_INJECT,
	CMD_CODE_WARM_TEMP,
	CMD_CODE_WARM_TIME,
	CMD_CODE_WARM_BLOCK1,
	CMD_CODE_WARM_BLOCK2,
	CMD_CODE_CARVE_DIRECTION,
	CMD_CODE_CARVE_RESET,
	CMD_CODE_WARM_BUMP,
	CMD_CODE_CARVE_BUMP,
	CMD_CODE_DEBUG,
	CMD_CODE_NORMAL,

	CMD_CODE_AIR_CYLINDER1,
	CMD_CODE_AIR_CYLINDER2,
	CMD_CODE_AIR_CYLINDER3,
	CMD_CODE_AIR_CYLINDER4,

	CMD_CODE_INJUCET_BUMP,
	CMD_CODE_PRESS_PLATE,

	CMD_CODE_INJUCET_VOLUME1,
	CMD_CODE_INJUCET_VOLUME2,
	CMD_CODE_INJUCET_VOLUME3,
	CMD_CODE_INJUCET_VOLUME4,
	CMD_CODE_INJUCET_VOLUME5,
	CMD_CODE_INJUCET_VOLUME6,
	CMD_CODE_INJUCET_VOLUME7,

	CMD_CODE_RETURN_ZERO,
	CMD_CODE_BUMP_INT,

	CMD_CODE_INJUCET_TIME,

} OFFSET_HOSTCOMM;
/******************************************************************************/
typedef struct{
	uint8 PumpControlSR;

} LAMINATING;

/******************************************************************************/
extern LAMINATING Laminating;
extern Judge TEMP_HEAT_START;
extern Judge DevicesInit_enable;
extern HostComm_UartRxTypedef HostComm_UartRx;

/******************************************************************************/
extern void HostComm_Process(void);
extern void HostComm_Cmd_Process (void);
extern uint8 HostComm_Cmd_Send_RawData(uint16 length, uint8 dataBuf[],OFFSET_HOSTCOMM CMD_CODE);

#endif
