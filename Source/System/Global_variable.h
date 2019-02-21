/*
 * Global_variable.h
 *
 *  Created on: 2018Äê9ÔÂ29ÈÕ
 *      Author: Administrator
 */

#ifndef SYSTEM_GLOBAL_VARIABLE_H_
#define SYSTEM_GLOBAL_VARIABLE_H_

/******************************************************************************/
#include "Project_File.h"

/******************************************************************************/
extern uint8 Recycle_Bead,Bump_Switch,Bump_Wash,Waste_Bump;
extern uint8 respBuffer[30],HostComm_RecBufAvailable,Bump_Init;
extern uint8 cmdType,cmdCode,recBuffer[30],cmdBuffer[30],contReceive;

extern uint16 recCount,HostComm_RecBufSize,cmdLength,respLength,Fiber_Optic;
extern uint16 Wash_time_second;

/***************************Motor Driver***************************************/
extern uint8 Movement_M1_start,Movement_M2_start;
extern uint8 Movement_M3_start,Movement_M4_start;
extern uint8 Movement_M5_start,Movement_M6_start;
extern uint8 Movement_M7_start,Movement_M8_start;
extern uint8 Movement_M9_start,Movement_M10_start;

extern uint32 Movement_M1_pulseCount,Movement_M1_pulseNumber;
extern uint32 Movement_M2_pulseCount,Movement_M2_pulseNumber;
extern uint32 Movement_M3_pulseCount,Movement_M3_pulseNumber;
extern uint32 Movement_M4_pulseCount,Movement_M4_pulseNumber;
extern uint32 Movement_M5_pulseCount,Movement_M5_pulseNumber;
extern uint32 Movement_M6_pulseCount,Movement_M6_pulseNumber;
extern uint32 Movement_M7_pulseCount,Movement_M7_pulseNumber;
extern uint32 Movement_M8_pulseCount,Movement_M8_pulseNumber;
extern uint32 Movement_M9_pulseCount,Movement_M9_pulseNumber;
extern uint32 Movement_M10_pulseCount,Movement_M10_pulseNumber;

/***************************Filling********************************************/
extern float  Base_Calculation_1ml,Base_Calculation_5ml;

extern uint32 Infusion_Air_50ul_1ml,Infusion_Air_50ul_5ml;
extern uint32 PumpPrecision_Step_1ml,PumpPrecision_Step_5ml;

extern uint32 PumpPrecision_Step_R1;
extern uint32 PumpPrecision_Step_R2;
extern uint32 PumpPrecision_Step_M;
extern uint32 PumpPrecision_Step_W;
extern uint32 PumpPrecision_Step_BASE;

/***************************USB & CAN Command********************************************/
extern uint8 CAN_Buffer[2];
extern uint8 sBuffer[2],fBuffer[2],Buffer[2];



#endif /* SYSTEM_GLOBAL_VARIABLE_H_ */
