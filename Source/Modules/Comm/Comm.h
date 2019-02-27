/*
 * Comm.h
 *
 *  Created on: 2016Äê5ÔÂ23ÈÕ
 *      Author: Administrator
 */

#ifndef SOURCE_MODULE_COMM_COMM_H_
#define SOURCE_MODULE_COMM_COMM_H_

/******************************************************************************/
#include "comDef.h"
#include "stm32f10x.h"

/******************************************************************************/
void Comm_Init(void);
void Comm_Process(void);
void Comm_CanRxDataGet(void);
ErrorStatus Comm_CanTxDataSend(void);
ErrorStatus Comm_CanRxData(CanRxMsg *RxMsg);
void Comm_CanTxDataPut(uint32 stdid, uint8* dataPtr, uint8 len);
void Comm_CanDirectSend(uint16 stdId, uint8 *dataPtr, uint16 len);
void Comm_CanTxMultiDataPut(uint32 stdid, uint8* dataPtr, uint8 len);
void Comm_CanTxSingleDataPut(uint32 stdid, uint8* dataPtr, uint8 len);
void Comm_CAN_SendOnePackage(uint16 stdId, uint8 *dataPtr, uint8 len);
ErrorStatus Comm_CanTxDataSend(void);
ErrorStatus Comm_CanRxData(CanRxMsg *RxMsg);

#endif /* SOURCE_MODULE_COMM_COMM_H_ */
