/*
 * Movement.c
 *
 *  Created on: 2019年2月14日
 *      Author: Administrator
 */
/******************************************************************************/
#include "Movement.h"

/******************************************************************************/
uint8 Movement_M1_initPos = 0;
uint8 Movement_M3_initPos = 0;
uint8 Movement_M4_initPos = 0;
uint8 Movement_M6_initPos = 0;
uint8 Movement_M10_initPos = 0;

/******************************************************************************/
void Movement_GotoInitialPosition(void)
{
#if TIMER1_M10_R1_R2_ENABLED
	PosSensor_M10_ENABLE();
#endif
#if TIMER2_M3_M_W1_ENABLED
	PosSensor_M3_ENABLE();
#endif
#if TIMER3_M6_W2_W3_ENABLED
	PosSensor_M6_ENABLE();
#endif
#if TIMER4_M4_W6_BASE_ENABLED
	PosSensor_M4_ENABLE();
#endif
#if TIMER5_M1_W4_W5_ENABLED
	PosSensor_M1_ENABLE();
#endif

#if TIMER1_M10_R1_R2_ENABLED
	if(Pos_Read_Sensor(SWITCH10))
	{
		Movement_M10_initPos = 0;
		Movement_M10_MotorDriver_DIR(DIR_CW);
		Movement_M10_Start();
	}
	else
	{
		Movement_M10_initPos = 1;
	}
#endif

#if TIMER2_M3_M_W1_ENABLED
	if(Pos_Read_Sensor(SWITCH3))
	{
		Movement_M3_initPos = 0;
		Movement_M3_MotorDriver_DIR(DIR_CW);
		Movement_M3_Start();
	}
	else
	{
		Movement_M3_initPos = 1;
	}
#endif

#if TIMER3_M6_W2_W3_ENABLED
	if(Pos_Read_Sensor(SWITCH6))
	{
		Movement_M6_initPos = 0;
		Movement_M6_MotorDriver_DIR(DIR_CW);
		Movement_M6_Start();
	}
	else
	{
		Movement_M6_initPos = 1;
	}
#endif

#if TIMER4_M4_W6_BASE_ENABLED
	if(Pos_Read_Sensor(SWITCH4))
	{
		Movement_M4_initPos = 0;
		Movement_M4_MotorDriver_DIR(DIR_CW);
		Movement_M4_Start();
	}
	else
	{
		Movement_M4_initPos = 1;
	}

#endif

#if TIMER5_M1_W4_W5_ENABLED
	if(Pos_Read_Sensor(SWITCH1))
	{
		Movement_M1_initPos = 0;
		Movement_M1_MotorDriver_DIR(DIR_CW);
		Movement_M1_Start();
	}
	else
	{
		Movement_M1_initPos = 1;
	}
#endif

#if TIMER1_M10_R1_R2_ENABLED
	while(Movement_M10_initPos == 0);
#endif
#if TIMER2_M3_M_W1_ENABLED
	while(Movement_M3_initPos == 0);
#endif
#if TIMER3_M6_W2_W3_ENABLED
	while(Movement_M6_initPos == 0);
#endif
#if TIMER4_M4_W6_BASE_ENABLED
	while(Movement_M4_initPos == 0);
#endif
#if TIMER5_M1_W4_W5_ENABLED
	while(Movement_M1_initPos == 0);
#endif

#if TIMER1_M10_R1_R2_ENABLED
	PosSensor_M10_DISABLE();
#endif
#if TIMER2_M3_M_W1_ENABLED
	PosSensor_M3_DISABLE();
#endif
#if TIMER3_M6_W2_W3_ENABLED
	PosSensor_M6_DISABLE();
#endif
#if TIMER4_M4_W6_BASE_ENABLED
	PosSensor_M4_DISABLE();
#endif
#if TIMER5_M1_W4_W5_ENABLED
	PosSensor_M1_DISABLE();
#endif
}

/******************************************************************************/
void Movement_M1_GotoTarget(MOTOR_DIR dir, uint32 steps)
{
	Movement_M1_pulseNumber = steps;
	Movement_M1_pulseCount = 0;
	Movement_M1_start = TRUE;
	Movement_M1_MotorDriver_DIR(dir);
	Movement_M1_Start();
}

/******************************************************************************/
void Movement_M2_GotoTarget(MOTOR_DIR dir,uint32 steps)
{
	Movement_M2_pulseNumber = steps;
	Movement_M2_pulseCount = 0;
	Movement_M2_start = TRUE;
	Movement_M2_MotorDriver_DIR(dir);
	Movement_M2_Start();
}

/******************************************************************************/
void Movement_M3_GotoTarget(MOTOR_DIR dir,uint32 steps)
{
	Movement_M3_pulseNumber = steps;
	Movement_M3_pulseCount = 0;
	Movement_M3_start = TRUE;
	Movement_M3_MotorDriver_DIR(dir);
	Movement_M3_Start();
}

/******************************************************************************/
void Movement_M4_GotoTarget(MOTOR_DIR dir,uint32 steps)
{
	Movement_M4_pulseNumber = steps;
	Movement_M4_pulseCount = 0;
	Movement_M4_start = TRUE;
	Movement_M4_MotorDriver_DIR(dir);
	Movement_M4_Start();
}

/******************************************************************************/
void Movement_M5_GotoTarget(MOTOR_DIR dir,uint32 steps)
{
	Movement_M5_pulseNumber = steps;
	Movement_M5_pulseCount = 0;
	Movement_M5_start = TRUE;
	Movement_M5_MotorDriver_DIR(dir);
	Movement_M5_Start();
}

/******************************************************************************/
void Movement_M6_GotoTarget(MOTOR_DIR dir,uint32 steps)
{
	Movement_M6_pulseNumber = steps;
	Movement_M6_pulseCount = 0;
	Movement_M6_start = TRUE;
	Movement_M6_MotorDriver_DIR(dir);
	Movement_M6_Start();
}

/******************************************************************************/
void Movement_M7_GotoTarget(MOTOR_DIR dir,uint32 steps)
{
	Movement_M7_pulseNumber = steps;
	Movement_M7_pulseCount = 0;
	Movement_M7_start = TRUE;
	Movement_M7_MotorDriver_DIR(dir);
	Movement_M7_Start();
}

/******************************************************************************/
void Movement_M8_GotoTarget(MOTOR_DIR dir,uint32 steps)
{
	Movement_M8_pulseNumber = steps;
	Movement_M8_pulseCount = 0;
	Movement_M8_start = TRUE;
	Movement_M8_MotorDriver_DIR(dir);
	Movement_M8_Start();
}

/******************************************************************************/
void Movement_M9_GotoTarget(MOTOR_DIR dir,uint32 steps)
{
	Movement_M9_pulseNumber = steps;
	Movement_M9_pulseCount = 0;
	Movement_M9_start = TRUE;
	Movement_M9_MotorDriver_DIR(dir);
	Movement_M9_Start();
}

/******************************************************************************/
void Movement_M10_GotoTarget(MOTOR_DIR dir,uint32 steps)
{
	Movement_M10_pulseNumber = steps;
	Movement_M10_pulseCount = 0;
	Movement_M10_start = TRUE;
	Movement_M10_MotorDriver_DIR(dir);
	Movement_M10_Start();
}

/******************************************************************************/
void Infusion_Air_50ul(void)
{
#if CH1_ENABLED
	Movement_M10_GotoTarget(DIR_CCW, Infusion_Air_50ul_1ml);
	Movement_M3_GotoTarget(DIR_CCW, Infusion_Air_50ul_1ml);
	Movement_M6_GotoTarget(DIR_CCW, Infusion_Air_50ul_5ml);

	/* @TODO */
	Movement_M1_GotoTarget(DIR_CCW, Infusion_Air_50ul_5ml);
	Movement_M4_GotoTarget(DIR_CCW, Infusion_Air_50ul_5ml);

	while(Movement_M10_start);
	while(Movement_M3_start);
	while(Movement_M6_start);
	while(Movement_M1_start);
	while(Movement_M4_start);
#endif

#if CH2_ENABLED
	Movement_M10_GotoTarget(DIR_CCW, Infusion_Air_50ul_1ml);
	Movement_M3_GotoTarget(DIR_CCW, Infusion_Air_50ul_5ml);
	Movement_M6_GotoTarget(DIR_CCW, Infusion_Air_50ul_5ml);
	Movement_M1_GotoTarget(DIR_CCW, Infusion_Air_50ul_5ml);

	/* @TODO */
	Movement_M4_GotoTarget(DIR_CCW, Infusion_Air_50ul_5ml);

	while(Movement_M10_start);
	while(Movement_M3_start);
	while(Movement_M6_start);
	while(Movement_M1_start);
	while(Movement_M4_start);
#endif
}

/******************************************************************************/
void ProcessCMD_Extract(void)
{
	/**************************************************************************/
#if CH1_ENABLED
#if TIMER1_M10_R1_R2_ENABLED
	Movement_M10_GotoTarget(DIR_CCW, PumpPrecision_Step_R1);
#endif
#if TIMER2_M3_M_W1_ENABLED
	Movement_M3_GotoTarget(DIR_CCW, PumpPrecision_Step_M);
#endif
#if TIMER3_M6_W2_W3_ENABLED
	Movement_M6_GotoTarget(DIR_CCW, PumpPrecision_Step_W);
#endif
#if TIMER5_M1_W4_W5_ENABLED
	Movement_M1_GotoTarget(DIR_CCW, PumpPrecision_Step_W);
#endif
#if TIMER4_M4_W6_BASE_ENABLED
	Movement_M4_GotoTarget(DIR_CCW, PumpPrecision_Step_W);
#endif

	/**************************************************************************/
#if TIMER1_M10_R1_R2_ENABLED
	while(Movement_M10_start);
#endif
#if TIMER2_M3_M_W1_ENABLED
	while(Movement_M3_start);
#endif
#if TIMER3_M6_W2_W3_ENABLED
	while(Movement_M6_start);
#endif
#if TIMER5_M1_W4_W5_ENABLED
	while(Movement_M1_start);
#endif
#if TIMER4_M4_W6_BASE_ENABLED
	while(Movement_M4_start);
#endif
#endif

	/**************************************************************************/
#if CH2_ENABLED
#if TIMER1_M10_R1_R2_ENABLED
	Movement_M10_GotoTarget(DIR_CCW,PumpPrecision_Step_R2);
#endif
#if TIMER2_M3_M_W1_ENABLED
	Movement_M3_GotoTarget(DIR_CCW,PumpPrecision_Step_W);
#endif
#if TIMER3_M6_W2_W3_ENABLED
	Movement_M6_GotoTarget(DIR_CCW,PumpPrecision_Step_W);
#endif
#if TIMER5_M1_W4_W5_ENABLED
	Movement_M1_GotoTarget(DIR_CCW,PumpPrecision_Step_W);
#endif
#if TIMER4_M4_W6_BASE_ENABLED
	Movement_M4_GotoTarget(DIR_CCW,PumpPrecision_Step_BASE);
#endif

	/**************************************************************************/
#if TIMER1_M10_R1_R2_ENABLED
	while(Movement_M10_start);
#endif
#if TIMER2_M3_M_W1_ENABLED
	while(Movement_M3_start);
#endif
#if TIMER3_M6_W2_W3_ENABLED
	while(Movement_M6_start);
#endif
#if TIMER5_M1_W4_W5_ENABLED
	while(Movement_M1_start);
#endif
#if TIMER4_M4_W6_BASE_ENABLED
	while(Movement_M4_start);
#endif
#endif

#if CH1_ENABLED
	Comm_CanDirectSend(STDID_INFUSION_ACHIEVE,CAN_Buffer,1);
#endif
}

/******************************************************************************/
void ProcessCMD_Inject(uint8 *data)
{
#if CH1_ENABLED
	Movement_GotoInitialPosition();

//	Movement_M10_GotoTarget(DIR_CW, PumpPrecision_Step_R1);
//	Movement_M3_GotoTarget(DIR_CW, PumpPrecision_Step_M);
//	Movement_M6_GotoTarget(DIR_CW, PumpPrecision_Step_W);
//
//	Movement_M1_GotoTarget(DIR_CW, PumpPrecision_Step_W);
//	Movement_M4_GotoTarget(DIR_CW, PumpPrecision_Step_W);
//
//	while(Movement_M10_start);
//	while(Movement_M3_start);
//	while(Movement_M6_start);
//	while(Movement_M1_start);
//	while(Movement_M4_start);
#endif

#if CH2_ENABLED
	Movement_GotoInitialPosition();

//	Movement_M10_GotoTarget(DIR_CCW,PumpPrecision_Step_R2);
//	Movement_M3_GotoTarget(DIR_CCW,PumpPrecision_Step_W);
//	Movement_M6_GotoTarget(DIR_CCW,PumpPrecision_Step_W);
//
//	Movement_M1_GotoTarget(DIR_CCW,PumpPrecision_Step_W);
//	Movement_M4_GotoTarget(DIR_CCW,PumpPrecision_Step_BASE);
//
//	while(Movement_M10_start);
//	while(Movement_M3_start);
//	while(Movement_M6_start);
//	while(Movement_M1_start);
//	while(Movement_M4_start);
#endif

//#if CH1_ENABLED
//	Comm_CanDirectSend(STDID_SEND_BACK_ZERO,CAN_Buffer,1);
//#endif
}

/******************************************************************************/
void Inject_Achieve(uint8 *data)
{
	if(data[0])
	{
		/* 未注完5次  */
		Buffer[0] = 0;
		if(L100_Filling)
		{
			Delay_ms_SW(500);
			Comm_CanDirectSend(STDID_INFUSION_PREPARE,Buffer,1);
#if CH1_ENABLED
			Infusion_Air_50ul();
#endif
		}
		else
		{
			HostComm_Cmd_Send_RawData(1, Buffer, CMD_CODE_INJECT);
		}
	}
	else
	{
		/* 注完5次  */
		Buffer[0] = 0;
		L100_Filling = 0;
		HostComm_Cmd_Send_RawData(1, Buffer, CMD_CODE_BUMP_FILLING);
	}
}
