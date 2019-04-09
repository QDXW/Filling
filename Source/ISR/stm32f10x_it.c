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
void SysTick_Handler(void)
{
	/* Decrease TimingDelay */
	TimingDelay_Decrement();
}

/******************************************************************************/
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line10) != RESET)
	{
		Movement_M9_pulseCount = Movement_M9_pulseNumber;
//		Movement_M9_Stop();
		EXTI_ClearITPendingBit(EXTI_Line10);
	}

	if(EXTI_GetITStatus(EXTI_Line11) != RESET)
	{
		Movement_M10_pulseCount = Movement_M10_pulseNumber;
		Movement_M10_initPos = 1;
		Movement_M10_Stop();
		EXTI_ClearITPendingBit(EXTI_Line11);
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
		Movement_M3_pulseCount = Movement_M3_pulseNumber;
		Movement_M3_initPos = 1;
		Movement_M3_Stop();
		EXTI_ClearITPendingBit(EXTI_Line5);
	}

	if(EXTI_GetITStatus(EXTI_Line6) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line6);
	}

	if(EXTI_GetITStatus(EXTI_Line7) != RESET)
	{
		Movement_M6_pulseCount = Movement_M6_pulseNumber;
		Movement_M6_initPos = 1;
		Movement_M6_Stop();
		EXTI_ClearITPendingBit(EXTI_Line7);
	}

	if(EXTI_GetITStatus(EXTI_Line8) != RESET)
	{
		Movement_M7_pulseCount = Movement_M7_pulseNumber;
//		Movement_M7_Stop();
		EXTI_ClearITPendingBit(EXTI_Line8);
	}

	if(EXTI_GetITStatus(EXTI_Line9) != RESET)
	{
		Movement_M8_pulseCount = Movement_M8_pulseNumber;
		Movement_M8_Stop();
		EXTI_ClearITPendingBit(EXTI_Line9);
	}
}

/******************************************************************************/
void EXTI4_IRQHandler(void)
{
 	if(EXTI_GetITStatus(EXTI_Line4) != RESET)
	{
 		Movement_M9_pulseCount = Movement_M9_pulseNumber;
//		Movement_M9_Stop();
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}

/******************************************************************************/
void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3) != RESET)
	{
		Movement_M1_pulseCount = Movement_M1_pulseNumber;
		Movement_M1_initPos = 1;
		Movement_M1_Stop();
		EXTI_ClearITPendingBit(EXTI_Line3);
	}
}

/******************************************************************************/
void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}

/******************************************************************************/
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
		Movement_M5_pulseCount = Movement_M5_pulseNumber;
		Movement_M5_Stop();
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

/******************************************************************************/
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		Movement_M4_pulseCount = Movement_M4_pulseNumber;
		Movement_M4_initPos = 1;
		Movement_M4_Stop();
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

/******************************************************************************/
void TIM6_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
	{

#if CH1_ENABLED
		if(Waste_Bump_Open)
		{
			Wash_Sencond++;
			if(Wash_Sencond > 50)
			{
				Waste_Bump_Open = 0;
				Wash_Sencond = 0;
				Waste_Bump_Closed = 1;

				/* ¹Ø±Õ·§ÃÅ¼°¸ôÄ¤±Ã   ´ò¿ª·ÏÒº¸ôÄ¤±Ã */
				VAVLE_OPEN();
				DIAP_PUMP_CLOSED();

				/* ¿ªÊ¼ÇåÏ´  */
				Buffer[0] = 0X00;
				Comm_CanDirectSend(STDID_BUMP_WASH_START, Buffer, 1);
//				/* ÇåÏ´  */
//				Buffer[0] = 0X01;
//				Comm_CanDirectSend(STDID_PUMP_WASH_ACHIEVE,Buffer,1);
				if(Waste_Bump_Count > 4)
				{
					VAVLE_CLOSED();
					DIAP_PUMP_CLOSED();
					Waste_Bump_Open = 0;
					Waste_Bump_Count = 0;
					Wash_Sencond = 0;
					Waste_Bump_Closed = 0;

					/* Í£Ö¹ÇåÏ´  */
					Buffer[0] = 0X00;
					Comm_CanDirectSend(STDID_PUMP_WASH_PREARE, Buffer, 1);
					HostComm_Cmd_Send_RawData(1, fBuffer,CMD_CODE_WASH);
				}
			}
		}
		else
		{
			Waste_Bump_Open = 0;
		}

		if(Waste_Bump_Closed)
		{
			Wash_Sencond++;
			if(Wash_Sencond > 7)
			{
				Waste_Bump_Count++;
				Wash_Sencond = 0;
				Waste_Bump_Closed = 0;
				Waste_Bump_Open = 1;
				/* Í£Ö¹ÇåÏ´  */
				Buffer[0] = 0X01;
				Comm_CanDirectSend(STDID_BUMP_WASH_START, Buffer, 1);

				/* ´ò¿ª·§ÃÅ¼°¸ôÄ¤±Ã   ¹Ø±Õ·ÏÒº¸ôÄ¤±Ã */
				VAVLE_CLOSED();
				DIAP_PUMP_OPEN();
			}
		}
		else
		{
			Waste_Bump_Closed = 0;
		}
#endif

		/* Clear the interrupt pending flag */
		TIM_ClearFlag(TIM6, TIM_FLAG_Update);
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
