/*
 * Comm.c
 *
 *  Created on: 2016年5月23日
 *      Author: Administrator
 */
#include "Comm.h"
#include "Comm_CAN.h"
#include "Comm_CAN_FIFO.h"
#include "string.h"
#include "Movement.h"
#include "sensor.h"
#include "Project_File.h"

void Comm_Init(void)
{
	/* Initialize CAN bus */
	Comm_CAN_Init();
	
	/* 发送和接收FIFO初始化 */
	Comm_CAN_FIFO_Init(&RxDataFIFO);
	Comm_CAN_FIFO_Init(&TxDataFIFO);
}

/******************************************************************************/
void Comm_Process(void)
{
	/* Send Queue Management */
	Comm_CanTxDataSend();
	/* Receive Queue Management */
	Comm_CanRxDataGet();
}

/******************************************************************************/
/* 待发送的单帧数据入列函数 */
void Comm_CanTxSingleDataPut(uint32 stdid, uint8 *dataPtr, uint8 len)
{
	CAN_SendDataTypedef TxMsg;

	TxMsg.StdId = stdid;
	TxMsg.DLC = len;

	memcpy(&TxMsg.Data, dataPtr, len);
	
	/* 待发送的数据存入FIFO */
	Comm_CAN_FIFO_TxDataPut( &TxMsg, &TxDataFIFO );
}

/******************************************************************************/
/* 待发送的多帧数据入列函数 */
void Comm_CanTxMultiDataPut(uint32 stdid, uint8* dataPtr, uint8 len)
{
	MultiFrameBufferTypedef SourceData;
	CAN_SendDataTypedef TxMsg;

	/* 多帧数据拥有相同的ID号 */
	TxMsg.StdId = stdid;
	
	/* 获取总帧数并保存 */
	SourceData.TotleLenth = (len / MultiFrameOnePackage_LenMax - 1);
	
	/* 例:总长为6帧的数据,每帧第一个字节为帧信号
			第一帧发送0x0500
			第二帧发送0x0501
			...
			最后一帧发送0x0505 --->发送完成
	*/
	
	/* 最后一帧判断 */
	if(len % MultiFrameOnePackage_LenMax != RESET)
	{
		SourceData.TotleLenth++;
	}
	
	/* 获取len长度的数据 */
	memcpy(&SourceData.MultiDataBuffer, dataPtr, len);
	
	/* 初始化当前长度和状态 */
	SourceData.CurrentLenth = RESET;
	SourceData.Status = RESET;
	
	/* 将数据分割成多帧入列到FIFO中 */
	for(SourceData.CurrentLenth = 0; 
		SourceData.CurrentLenth <= SourceData.TotleLenth; 
		SourceData.CurrentLenth++)
	{
		/* 这是最后一帧 */
		if(SourceData.CurrentLenth == SourceData.TotleLenth)
		{
			/* 获取最后一帧的数据长度 */
			TxMsg.DLC = len % MultiFrameOnePackage_LenMax + 1;
		}
		else
		{
			/* 不是最后一帧,则长度固定为8 */
			TxMsg.DLC = MultiFrameOnePackage_LenMax + 1;
		}
		
		/* 每一帧的第一个字节作为帧信息,高4位--总帧数,低4位--当前帧数 */
		TxMsg.Data[0] = (((SourceData.TotleLenth & 0x0f) << 4) 
						| (SourceData.CurrentLenth & 0x0f));
		
		/* 从源数据中Copy相应长度的数据, */
		memcpy(&TxMsg.Data[1], 
			   &SourceData.MultiDataBuffer
					[SourceData.CurrentLenth * MultiFrameOnePackage_LenMax],
			   (TxMsg.DLC - 1));
		
		/* Copy好的数据入列到FIFO中 */
		Comm_CAN_FIFO_TxDataPut( &TxMsg, &TxDataFIFO );
	}
	
	/* 缓存区用完记得清空 ^-^ */
	Comm_CanMultiFIFOInit(&SourceData);
}

/******************************************************************************/
void Comm_CanTxDataPut(uint32 stdid, uint8* dataPtr, uint8 len)
{
	if(len > 8)
	{
		/* 这是一个多帧 */
		Comm_CanTxMultiDataPut(stdid, dataPtr, len);
	}
	else
	{
		/* 这是一个单帧 */
		Comm_CanTxSingleDataPut(stdid, dataPtr, len);
	}
}
/******************************************************************************/
/* 待发送的数据出列并触发CAN发送 */
ErrorStatus Comm_CanTxDataSend(void)
{
	CanTxMsg TxMsg;
	uint8 TMailBox, Status;
	uint8 i;
	
	Status = Comm_CAN_FIFO_TxDataGet(&TxDataFIFO, &TxMsg);
	
	/* 获取成功 */
	if(Status == SUCCESS)
	{
		TxMsg.IDE = CAN_Id_Standard;
		TxMsg.RTR = CAN_RTR_Data;
		
		/* Transmit */
		TMailBox = CAN_Transmit(CAN1, &TxMsg);

		/* Wait for completion */
		i=0;
		while((CAN_TransmitStatus(CAN1, TMailBox) != CAN_TxStatus_Ok) 
			   && (i < 0XFF))
		{
			i++;
		}
	}
	/* Time Out 返回错误 */
	if(i > 0xff)
	{
		return ERROR;
	}
	return SUCCESS;
}

/******************************************************************************/
void Comm_CanDirectSend(uint16 stdId, uint8 *dataPtr, uint16 len)
{
	uint8 packageNumSend = 0;
	uint8 packageCountSend = 0;
	uint8 lastPackageSize = 0;

	if(len <= CAN_PACKAGE_MAX)
	{
	   Comm_CAN_SendOnePackage(stdId, 
				&dataPtr[packageCountSend * CAN_PACKAGE_MAX], len);
	}
	else
	{
		/* Calculate package number */
		packageNumSend = len / CAN_PACKAGE_MAX;
		lastPackageSize = len % CAN_PACKAGE_MAX;
		
		if(lastPackageSize != 0)
			packageNumSend ++;
		
		/* Send one by one */
		for (packageCountSend = 0; packageCountSend < packageNumSend;
			packageCountSend++)
		{
			if (packageCountSend == (packageNumSend - 1))
				/* Last package */
				Comm_CAN_SendOnePackage(stdId, 
					&dataPtr[packageCountSend * CAN_PACKAGE_MAX], lastPackageSize);
			else
				/* Others */
				Comm_CAN_SendOnePackage(stdId, 
					&dataPtr[packageCountSend * CAN_PACKAGE_MAX], CAN_PACKAGE_MAX);
		}
	}
}

/******************************************************************************/
void Comm_CAN_SendOnePackage(uint16 stdId, uint8 *dataPtr, uint8 len)
{
	CanTxMsg TxMessage;
	uint8 i = 0;
	uint8 TMailbox;

	/* Fill header */
	TxMessage.StdId = stdId;
	TxMessage.IDE = CAN_Id_Standard;
	TxMessage.RTR = CAN_RTR_Data;
	TxMessage.DLC = len;
	/* Move data */
	for(i = 0; i < len; i++)
		TxMessage.Data[i]= dataPtr[i];

	/* Transmit */
	TMailbox = CAN_Transmit(CAN1, &TxMessage);
	
	/* Wait for completion */
	i=0;
	while((CAN_TransmitStatus(CAN1, TMailbox) == CAN_TxStatus_Failed) &&
			(i < 0XFF))
		i++;
}


/******************************************************************************/
/* 从FIFO中获取数据并处理 */
void Comm_CanRxDataGet(void)            
{
	uint8 Status;
	CAN_ReceiveDataTypedef RxMsg;
	Status = Comm_CAN_FIFO_RxDataGet(&RxDataFIFO, &RxMsg);
	
	/* 获取成功 */
	if(Status == SUCCESS)
	{
		switch(RxMsg.StdId)
		{
		case STDID_RX_INFUSION:
			/* 抽液 */
			ProcessCMD_Extract();
			break;

		case STDID_RX_INIPUMP:
			/* 初始化柱塞泵 */
			Movement_GotoInitialPosition();
			Delay_ms_SW(100);
//#if CH1_ENABLED
//			VAVLE_CLOSED();
//			DIAP_PUMP_OPEN();
//#endif
//#if CH2_ENABLED
//			if(RxMsg.Data[0])
//			{
//				VAVLE_CLOSED();
//			}
//			else
//			{
//				VAVLE_OPEN();
//			}
//#endif
			break;

		case STDID_SEND_BACK_ZERO_ACHIEVE:
			/* 抽空气  */
			Infusion_Air_70ul();
#if CH1_ENABLED
			Comm_CanDirectSend(STDID_INFUSION_PREPARE,Buffer,1);
#endif
			break;

#if CH2_ENABLED
		case STDID_INFUSION_PREPARE_CH2:
			/* 抽空气  */
			Infusion_Air_50ul();
			break;
#endif

#if CH1_ENABLED
		case STDID_RX_INJECT_CH1:
			/* 注液 */
			ProcessCMD_Inject(RxMsg.Data);
			break;
#endif

#if CH2_ENABLED
		case STDID_RX_INJECT_CH2:
			/* 注液 */
			ProcessCMD_Inject(RxMsg.Data);
			break;
#endif

		case STDID_RX_INJECT:
			/* 注液 */
			ProcessCMD_Inject_Double_Row(RxMsg.Data);
			break;

#if CH1_ENABLED
		case STDID_RX_INJECT_ACHIEVE:
			Inject_Achieve(RxMsg.Data);
			break;
#endif


		case STDID_FILLING_ACHIEVE:
			/* 初始化泵 */
			Movement_GotoInitialPosition();
#if CH1_ENABLED
			/* 灌装完成 */
			Buffer[0] = 0;
			HostComm_Cmd_Send_RawData(1, Buffer, CMD_CODE_BUMP_FILLING);
#endif
			break;

		case STDID_BUMP_WASH_START:
			/* 打开阀门及隔膜泵   关闭废液隔膜泵 */
#if CH1_ENABLED
			VAVLE_CLOSED();
			DIAP_PUMP_OPEN();
#endif
#if CH2_ENABLED
			if(RxMsg.Data[0])
			{
				VAVLE_CLOSED();
			}
			else
			{
				VAVLE_OPEN();
			}
#endif
			Waste_Bump_Open = 1;
		break;

		case STDID_PUMP_WASH_ACHIEVE:
			Wash_Sencond = 0;
			VAVLE_CLOSED();
#if CH1_ENABLED
			DIAP_PUMP_CLOSED();
#endif
		break;

#if CH2_ENABLED
		case STDID_SEND_BUMP_VOL:
			Set_Volume(RxMsg.Data);
		break;
#endif

		default:
			break;
		}
	}
}

/******************************************************************************/
ErrorStatus Comm_CanRxData(CanRxMsg *RxMsg)            
{	
	/* Deal directly with the data from the CAN interrupt */
	switch(RxMsg->StdId)
	{
		case 1:
			break;
		default:
			return SUCCESS;
	}
	return ERROR;
}
