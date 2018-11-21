/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2018
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 

/******************************************************************************/
uint16 Time_Millisecond2 = 0;
uint16 Display_second = 0,Time_Millisecond = 0;
uint8 buf[2]  = {0x09,0x00},tBuffer[8] = {0},Press_COunt = 0;
float Temper_Display = 0.0,Temper_Display2 = 0.0;

/******************************************************************************/
void SysTick_Handler(void)
{
	/* Decrease TimingDelay */
	TimingDelay_Decrement();
	millis++;

	/* 串口发送温度数据 */
	Display_second++;
	if(Display_second > 499)
	{
		Display_second = 0;

		/* 发送温度  */
		memcpy(&tBuffer[0],&Temper_HOT1,4);
		memcpy(&tBuffer[4],&Temper_HOT2,4);
		HostComm_Cmd_Send_RawData(8, tBuffer,CMD_CODE_TEMP);
	}

	if(Heat_Status & 0x04)
	{
		Time_second++;
		if(Time_second > Warm_Time)
		{
			Warm_Achieve();
		}
	}
	else
	{
		Time_second = 0;
	}
}

/******************************************************************************/
void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  	//检查TIM4更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  		//清除TIMx更新中断标志
		if(!Send_Flag)
		{
			if(Temp_Switch != 0)
			{
				Time_Millisecond++;
				if(Time_Millisecond > 3)
				{
					Time_Millisecond = 0;
					Get_Temp_Average(HOT1);
					Get_Temp_Average(HOT2);
					Temp_Monitor();
				}
			}
			else
			{
				Time_Millisecond2++;
				if(Time_Millisecond2 > 3)
				{
					Time_Millisecond2 = 0;
					Get_Temp_Average(HOT1);
					Get_Temp_Average(HOT2);
				}
			}
		}
	}
}
 
/******************************************************************************/
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line10) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line10);
		if(GPIO_ReadInputDataBit(PORT_SWITCH_14, PIN_SWITCH_14))
		{
			Delay_ms_SW(50);
			Valve7_Lock(OPEN);
		}
	}

	if(EXTI_GetITStatus(EXTI_Line11) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line11);
		if(GPIO_ReadInputDataBit(PORT_SWITCH_15, PIN_SWITCH_15))
		{
			Delay_ms_SW(50);
			Valve1_Lock(OPEN);
		}
	}

	if(EXTI_GetITStatus(EXTI_Line12) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line12);
	}

	if(EXTI_GetITStatus(EXTI_Line13) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line13);
	}

	if(EXTI_GetITStatus(EXTI_Line14) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line14);
	}

	if(EXTI_GetITStatus(EXTI_Line15) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line15);
	}
}

/******************************************************************************/
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line5);
		Valve_Lock |= GPIO_ReadInputDataBit(PORT_SWITCH_2, PIN_SWITCH_2)?(1<<4):(0<<4);
		Valve7_Lock(OPEN);
	}

	if(EXTI_GetITStatus(EXTI_Line7) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line7);
		Valve_Lock |= GPIO_ReadInputDataBit(PORT_SWITCH_5, PIN_SWITCH_5)?(1<<1):( 0<<1);
	}

	if(EXTI_GetITStatus(EXTI_Line8) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line8);
		Valve_Lock |= GPIO_ReadInputDataBit(PORT_SWITCH_6, PIN_SWITCH_6)?(1<<0):( 0<<0);
	}

	if(EXTI_GetITStatus(EXTI_Line9) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line9);
	}
}

/******************************************************************************/
void EXTI4_IRQHandler(void)
{
 	if(EXTI_GetITStatus(EXTI_Line4) != RESET)
	{
 		Press_COunt++;
		EXTI_ClearITPendingBit(EXTI_Line4);
		if(GPIO_ReadInputDataBit(PORT_SWITCH_1, PIN_SWITCH_1) && 1 == Press_COunt)
		{
//			buf[1] = 0X00,buf[0] = 0X05;						//滑块挡柱3
//			Comm_CanDirectSend(STDID_RX_VALVE_LOCK,buf,2);
//			Delay_ms_SW(10);
//			Valve6_Lock(OPEN);
//			Delay_ms_SW(40);
//			Valve8_Lock(OPEN);
		}
	}
}

/******************************************************************************/
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line1);
		Valve_Lock |= GPIO_ReadInputDataBit(PORT_SWITCH_4, PIN_SWITCH_4)?(1<<2):(0<<2);
	}
}

/******************************************************************************/
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line0);
		Valve_Lock |= GPIO_ReadInputDataBit(PORT_SWITCH_3, PIN_SWITCH_3)?(1<<3):(0<<3);
	}
}

/******************************************************************************/
void NMI_Handler(void)
{
}
 
/******************************************************************************/
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
/******************************************************************************/
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/******************************************************************************/
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
/******************************************************************************/
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
/******************************************************************************/
void SVC_Handler(void)
{
}
 
/******************************************************************************/
void DebugMon_Handler(void)
{
}
 
/******************************************************************************/
void PendSV_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
