/******************************************************************************/
#include "Project_File.h"

/******************************************************************************/
uint8 Temptertuer = 0;
uint32 Initialize_Count = 0;

/******************************************************************************/
int main(void)
{
	SysTick_Init();

	Devices_Init();

	HostComm_Init();

	TIM4_Int_Init(999,7199);			/* 10Khz的计数频率，计数到1000为100ms */

	Comm_Init();

	PosSensor_Init();

	TempControl_Init();

	Devices_Return_Zero();

	Judge_Temp();

	Open_Device();

	while(1)
	{
		HostComm_Process();
		Comm_Process();

		Devices_Valve_Action();
	}
}

/******************************************************************************/
void Judge_Temp (void)
{
	/* 温度未到180°时不执行程序  */
	while(Start_Temp)
	{
		HostComm_Process();

		/* 温度检测处理  */
		Temp_Switch |= (Temper_HOT1 >= Control_Temperature)?(1<<0):(0<<0);
		Temp_Switch |= (Temper_HOT2 >= Control_Temperature)?(1<<1):(0<<1);

		Temp_Switch = 3;

		switch(Temp_Count)
		{
			case 0:
				SetpwmValue(HOT1,0);
				SetpwmValue(HOT2,0);
				break;

			case 1:
				SetpwmValue(HOT1,100);
				SetpwmValue(HOT2,0);
				break;

			case 2:
				SetpwmValue(HOT1,0);
				SetpwmValue(HOT2,100);
				break;

			case 3:
				if(!(Temp_Switch & 0x01))
				{
					SetpwmValue(HOT1,100);
				}

				if(!(Temp_Switch & 0x02))
				{
					SetpwmValue(HOT2,100);
				}
				break;

			default:
				break;
		}

		switch(Temp_Count)
		{
			case 1:
				if(1 == Temp_Switch)
					Start_Temp = 0;
				break;

			case 2:
				if(2 == Temp_Switch)
					Start_Temp = 0;
				break;

			case 3:
				if(3 == Temp_Switch)
					Start_Temp = 0;
				break;

			default:
				break;
		}

		/* 传感器信号归零  */
		Valve_Lock = 0;
		Heat_Status = 0;

		Exhaust_Air_Process();
		Recycle_Bead_Process();
	}
}

/******************************************************************************/
void Open_Device (void)
{
	uint8 fBuffer[1] = {1};

	/* 机器开关 */
	while(L100_Switch)
	{
		HostComm_Process();
		Exhaust_Air_Process();
		Recycle_Bead_Process();

		Initialize_Count++;
		if(Initialize_Count > 599999)
		{
			Send_Flag = 1;
			HostComm_Cmd_Send_RawData(1, fBuffer,CMD_CODE_INITIALIZE);
			Initialize_Count = 0;
			Delay_ms_SW(10);
			Send_Flag = 1;
		}
	}
}
