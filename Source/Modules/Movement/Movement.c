/*
 * Movement.c
 *
 *  Created on: 2019年2月14日
 *      Author: Administrator
 */
/******************************************************************************/
#include "Movement.h"

/******************************************************************************/
uint8 Buffer[2] = 0;

/******************************************************************************/
void Movement_GotoInitialPosition(void)
{	Delay_ms_SW(3000);
	if(Pos_Read_Sensor(SWITCH3))
	{
		Movement_M3_MotorDriver_DIR(DIR_CW);
		Movement_M3_Start();
	}

	/* 传感器坏了 */
//	if(Pos_Read_Sensor(SWITCH4))
//	{
//		Movement_M4_MotorDriver_DIR(DIR_CW);
//		Movement_M4_Start();
//	}

	if(Pos_Read_Sensor(SWITCH5))
	{
		Movement_M5_MotorDriver_DIR(DIR_CW);
		Movement_M5_Start();
	}

	if(Pos_Read_Sensor(SWITCH6))
	{
		Movement_M6_MotorDriver_DIR(DIR_CW);
		Movement_M6_Start();
	}

	if(Pos_Read_Sensor(SWITCH7))
	{
		Movement_M7_MotorDriver_DIR(DIR_CW);
		Movement_M7_Start();
	}

	if(Pos_Read_Sensor(SWITCH1))
	{
		Movement_M8_MotorDriver_DIR(DIR_CW);
		Movement_M8_Start();
	}

	if(Pos_Read_Sensor(SWITCH2))
	{
		Movement_M9_MotorDriver_DIR(DIR_CW);
		Movement_M9_Start();
	}

/*			暂时未用
 * if(Pos_Read_Sensor(SWITCH1))
	{
		Movement_M1_MotorDriver_DIR(DIR_CW);
		Movement_M1_Start();
	}

	if(Pos_Read_Sensor(SWITCH2))
	{
		Movement_M2_MotorDriver_DIR(DIR_CW);
		Movement_M2_Start();
	}

	if(Pos_Read_Sensor(SWITCH10))
	{
		Movement_M10_MotorDriver_DIR(DIR_CW);
		Movement_M10_Start();
	}
*/
}

/******************************************************************************/
void Movement_M1_GotoTarget(MOTOR_DIR dir,uint32 Movement_M1_Step)
{
	Movement_M1_pulseNumber = Movement_M1_Step;
	Movement_M1_pulseCount = 0;
	Movement_M1_start = TRUE;
	Movement_M1_MotorDriver_DIR(dir);
	Movement_M1_Start();
	while(Movement_M1_start);
}

/******************************************************************************/
void Movement_M2_GotoTarget(MOTOR_DIR dir,uint32 Movement_M2_Step)
{
	Movement_M2_pulseNumber = Movement_M2_Step;
	Movement_M2_pulseCount = 0;
	Movement_M2_start = TRUE;
	Movement_M2_MotorDriver_DIR(dir);
	Movement_M2_Start();
	while(Movement_M2_start);
}

/******************************************************************************/
void Movement_M3_GotoTarget(MOTOR_DIR dir,uint32 Movement_M3_Step)
{
	Movement_M3_pulseNumber = Movement_M3_Step;
	Movement_M3_pulseCount = 0;
	Movement_M3_start = TRUE;
	Movement_M3_MotorDriver_DIR(dir);
	Movement_M3_Start();
	while(Movement_M3_start);
}

/******************************************************************************/
void Movement_M4_GotoTarget(MOTOR_DIR dir,uint32 Movement_M4_Step)
{
	Movement_M4_pulseNumber = Movement_M4_Step;
	Movement_M4_pulseCount = 0;
	Movement_M4_start = TRUE;
	Movement_M4_MotorDriver_DIR(dir);
	Movement_M4_Start();
	while(Movement_M4_start);
}

/******************************************************************************/
void Movement_M5_GotoTarget(MOTOR_DIR dir,uint32 Movement_M5_Step)
{
	Movement_M5_pulseNumber = Movement_M5_Step;
	Movement_M5_pulseCount = 0;
	Movement_M5_start = TRUE;
	Movement_M5_MotorDriver_DIR(dir);
	Movement_M5_Start();
	while(Movement_M5_start);
}

/******************************************************************************/
void Movement_M6_GotoTarget(MOTOR_DIR dir,uint32 Movement_M6_Step)
{
	Movement_M6_pulseNumber = Movement_M6_Step;
	Movement_M6_pulseCount = 0;
	Movement_M6_start = TRUE;
	Movement_M6_MotorDriver_DIR(dir);
	Movement_M6_Start();
	while(Movement_M6_start);
}

/******************************************************************************/
void Movement_M7_GotoTarget(MOTOR_DIR dir,uint32 Movement_M7_Step)
{
	Movement_M7_pulseNumber = Movement_M7_Step;
	Movement_M7_pulseCount = 0;
	Movement_M7_start = TRUE;
	Movement_M7_MotorDriver_DIR(dir);
	Movement_M7_Start();
	while(Movement_M7_start);
}

/******************************************************************************/
void Movement_M8_GotoTarget(MOTOR_DIR dir,uint32 Movement_M8_Step)
{
	Movement_M8_pulseNumber = Movement_M8_Step;
	Movement_M8_pulseCount = 0;
	Movement_M8_start = TRUE;
	Movement_M8_MotorDriver_DIR(dir);
	Movement_M8_Start();
	while(Movement_M8_start);
}

/******************************************************************************/
void Movement_M9_GotoTarget(MOTOR_DIR dir,uint32 Movement_M9_Step)
{
	Movement_M9_pulseNumber = Movement_M9_Step;
	Movement_M9_pulseCount = 0;
	Movement_M9_start = TRUE;
	Movement_M9_MotorDriver_DIR(dir);
	Movement_M9_Start();
	while(Movement_M9_start);
}

/******************************************************************************/
void Movement_M10_GotoTarget(MOTOR_DIR dir,uint32 Movement_M10_Step)
{
	Movement_M2_pulseNumber = Movement_M10_Step;
	Movement_M10_pulseCount = 0;
	Movement_M10_start = TRUE;
	Movement_M10_MotorDriver_DIR(dir);
	Movement_M10_Start();
	while(Movement_M10_start);
}

/******************************************************************************/
void Infusion_Air_50ul (void)
{
	Movement_M8_GotoTarget(DIR_CCW,Infusion_Air_50ul_5ml);
	Movement_M9_GotoTarget(DIR_CCW,Infusion_Air_50ul_5ml);
	Movement_M3_GotoTarget(DIR_CCW,Infusion_Air_50ul_5ml);
	Movement_M4_GotoTarget(DIR_CCW,Infusion_Air_50ul_5ml);

	Movement_M5_GotoTarget(DIR_CCW,Infusion_Air_50ul_1ml);
	Movement_M6_GotoTarget(DIR_CCW,Infusion_Air_50ul_1ml);
	Movement_M7_GotoTarget(DIR_CCW,Infusion_Air_50ul_1ml);

	while(Movement_M8_start);
	while(Movement_M9_start);
	while(Movement_M3_start);
	while(Movement_M4_start);
	while(Movement_M5_start);
	while(Movement_M6_start);
	while(Movement_M7_start);

	Comm_CanDirectSend(STDID_INFUSION_PREPARE,Buffer,1);
}
