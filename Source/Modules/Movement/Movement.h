/*
 * Movement.h
 *
 *  Created on: 2018Äê9ÔÂ19ÈÕ
 *      Author: Administrator
 */
#ifndef SOURCE_MODULES_MOVEMENT_MOVEMENT_H
#define SOURCE_MODULES_MOVEMENT_MOVEMENT_H

/******************************************************************************/
#include "Project_File.h"

extern uint8 Movement_M1_initPos;
extern uint8 Movement_M3_initPos;
extern uint8 Movement_M4_initPos;
extern uint8 Movement_M6_initPos;
extern uint8 Movement_M10_initPos;

/******************************************************************************/
extern void Infusion_Air_50ul(void);
extern void Infusion_Air_70ul(void);
extern void ProcessCMD_Extract(void);
extern void Inject_Achieve(uint8 *data);
extern void ProcessCMD_Inject(uint8 *data);
extern void ProcessCMD_Inject_Single_Row (uint8 *data);
extern void ProcessCMD_Inject_Double_Row (uint8 *data);

/******************************************************************************/
extern void Movement_GotoInitialPosition(void);
extern void Movement_M1_GotoTarget(MOTOR_DIR dir,uint32 Movement_M1_Step);
extern void Movement_M2_GotoTarget(MOTOR_DIR dir,uint32 Movement_M2_Step);
extern void Movement_M3_GotoTarget(MOTOR_DIR dir,uint32 Movement_M3_Step);
extern void Movement_M4_GotoTarget(MOTOR_DIR dir,uint32 Movement_M4_Step);
extern void Movement_M5_GotoTarget(MOTOR_DIR dir,uint32 Movement_M5_Step);
extern void Movement_M6_GotoTarget(MOTOR_DIR dir,uint32 Movement_M6_Step);
extern void Movement_M7_GotoTarget(MOTOR_DIR dir,uint32 Movement_M7_Step);
extern void Movement_M8_GotoTarget(MOTOR_DIR dir,uint32 Movement_M8_Step);
extern void Movement_M9_GotoTarget(MOTOR_DIR dir,uint32 Movement_M9_Step);
extern void Movement_M10_GotoTarget(MOTOR_DIR dir,uint32 Movement_M10_Step);

#endif
