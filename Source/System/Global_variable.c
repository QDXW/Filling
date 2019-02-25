/*
 * Global_variable.c
 *
 *  Created on: 2018Äê9ÔÂ20ÈÕ
 *      Author: Administrator
 */

/******************************************************************************/
#include "Global_variable.h"

/******************************************************************************/
uint8 HostComm_RecBufAvailable = 0,Bump_Switch = 255;
uint8 recBuffer[30] = {0},cmdBuffer[30] = {0},respBuffer[30] = {0};
uint8 cmdType = 0,cmdCode = 0,contReceive = 0,Bump_Wash = 0;
uint8 Waste_Bump = 0,Bump_Init = 0,Waste_Bump_Closed = 0;
uint8 Waste_Bump_Count = 0,Waste_Bump_Open = 0;

uint16 recCount = 0;
uint16 HostComm_RecBufSize = 0,cmdLength = 0,respLength = 0,Fiber_Optic = 0;

/***************************Motor Driver***************************************/
uint8 Movement_M1_start = 0,Movement_M2_start = 0;
uint8 Movement_M3_start = 0,Movement_M4_start = 0;
uint8 Movement_M5_start = 0,Movement_M6_start = 0;
uint8 Movement_M7_start = 0,Movement_M8_start = 0;
uint8 Movement_M9_start = 0,Movement_M10_start = 0;

uint32 Movement_M1_pulseCount = 0,Movement_M1_pulseNumber = 0;
uint32 Movement_M2_pulseCount = 0,Movement_M2_pulseNumber = 0;
uint32 Movement_M3_pulseCount = 0,Movement_M3_pulseNumber = 0;
uint32 Movement_M4_pulseCount = 0,Movement_M4_pulseNumber = 0;
uint32 Movement_M5_pulseCount = 0,Movement_M5_pulseNumber = 0;
uint32 Movement_M6_pulseCount = 0,Movement_M6_pulseNumber = 0;
uint32 Movement_M7_pulseCount = 0,Movement_M7_pulseNumber = 0;
uint32 Movement_M8_pulseCount = 0,Movement_M8_pulseNumber = 0;
uint32 Movement_M9_pulseCount = 0,Movement_M9_pulseNumber = 0;
uint32 Movement_M10_pulseCount = 0,Movement_M10_pulseNumber = 0;

/***************************Filling********************************************/
float  Base_Calculation_1ml = 0.0,Base_Calculation_5ml= 0.0;

uint32 Infusion_Air_50ul_1ml = 0,Infusion_Air_50ul_5ml = 0;
uint32 Infusion_Air_70ul_1ml = 0,Infusion_Air_70ul_5ml = 0;
uint32 PumpPrecision_Step_1ml = 0,PumpPrecision_Step_5ml = 0;

uint32 PumpPrecision_Step_R1 = 0;
uint32 PumpPrecision_Step_R2 = 0;
uint32 PumpPrecision_Step_M = 0;
uint32 PumpPrecision_Step_W = 0;
uint32 PumpPrecision_Step_BASE = 0;

/***************************USB & CAN Command**********************************/
uint8 CAN_Buffer[2] = {0,0},L100_Filling = 0;

uint8 sBuffer[2] = {1},fBuffer[2] = {0},Buffer[2] = {0};
