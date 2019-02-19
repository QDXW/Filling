/*
 * devices.c
 *
 *  Created on: 2019年2月14日
 *      Author: Administrator
 */
/******************************************************************************/
#include "devices.h"

/******************************************************************************/
DIAP_PUMP_NUM DIAP_PUMP;

/******************************************************************************/
void Devices_Init(void)
{
	/* 隔膜泵初始化 */
	DIAP_PUMP_Init();

	/* 阀门初始化  */
	VAVLE_Init();

	/* 柱塞泵初始化  */
	Motor_Init();

	/* 隔膜泵全部关闭  */
	DIAP_PUMP_CLOSED();

	/* 阀门全部关闭  */
	VAVLE_CLOSED();
}

/******************************************************************************/
void Set_Initialize_Parameter(void)
{
	Base_Calculation_5ml = 6.4;
	Base_Calculation_1ml = 32;
	PumpPrecision_Step_5ml = 1920;
	PumpPrecision_Step_1ml = 1600;
	Infusion_Air_50ul_5ml = 320;
	Infusion_Air_50ul_1ml = 1600;
}

/******************************************************************************/
void DIAP_PUMP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC |
			RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOD, ENABLE);
	
	/* DIAP_PUMP1~20 */
	GPIO_InitStructure.GPIO_Pin = PIN_DIAP_PUMP_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_DIAP_PUMP_1, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_DIAP_PUMP_1, PIN_DIAP_PUMP_1);
	
	GPIO_InitStructure.GPIO_Pin = PIN_DIAP_PUMP_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_DIAP_PUMP_2, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_DIAP_PUMP_2, PIN_DIAP_PUMP_2);
	
	GPIO_InitStructure.GPIO_Pin = PIN_DIAP_PUMP_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_DIAP_PUMP_3, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_DIAP_PUMP_3, PIN_DIAP_PUMP_3);
	
	GPIO_InitStructure.GPIO_Pin = PIN_DIAP_PUMP_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_DIAP_PUMP_4, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_DIAP_PUMP_4, PIN_DIAP_PUMP_4);
	
	GPIO_InitStructure.GPIO_Pin = PIN_DIAP_PUMP_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_DIAP_PUMP_5, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_DIAP_PUMP_5, PIN_DIAP_PUMP_5);
	
	GPIO_InitStructure.GPIO_Pin = PIN_DIAP_PUMP_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_DIAP_PUMP_6, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_DIAP_PUMP_6, PIN_DIAP_PUMP_6);
	
	GPIO_InitStructure.GPIO_Pin = PIN_DIAP_PUMP_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_DIAP_PUMP_7, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_DIAP_PUMP_7, PIN_DIAP_PUMP_7);
	
	GPIO_InitStructure.GPIO_Pin = PIN_DIAP_PUMP_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_DIAP_PUMP_8, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_DIAP_PUMP_8, PIN_DIAP_PUMP_8);
	
	GPIO_InitStructure.GPIO_Pin = PIN_DIAP_PUMP_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_DIAP_PUMP_9, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_DIAP_PUMP_9, PIN_DIAP_PUMP_9);
	
	GPIO_InitStructure.GPIO_Pin = PIN_DIAP_PUMP_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_DIAP_PUMP_10, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_DIAP_PUMP_10, PIN_DIAP_PUMP_10);
	
	GPIO_InitStructure.GPIO_Pin = PIN_DIAP_PUMP_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_DIAP_PUMP_15, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_DIAP_PUMP_15, PIN_DIAP_PUMP_15);

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	GPIO_InitStructure.GPIO_Pin = PIN_DIAP_PUMP_16;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_DIAP_PUMP_16, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_DIAP_PUMP_16, PIN_DIAP_PUMP_16);
}

/******************************************************************************/
void DIAP_PUMP_Set(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,FunctionalState status)
{
	if(ENABLE == status)
	{
		GPIO_SetBits(GPIOx, GPIO_Pin);
	}
	else
	{
		GPIO_ResetBits(GPIOx, GPIO_Pin);
	}
}

/******************************************************************************/
void DIAP_PUMP_Control(DIAP_PUMP_NUM DIAP_PUMP,FunctionalState status)
{
	switch(DIAP_PUMP)
	{
		case DIAP_PUMP1:DIAP_PUMP_Set(PORT_DIAP_PUMP_1,PIN_DIAP_PUMP_1,status);break;
		case DIAP_PUMP2:DIAP_PUMP_Set(PORT_DIAP_PUMP_2,PIN_DIAP_PUMP_2,status);break;
		case DIAP_PUMP3:DIAP_PUMP_Set(PORT_DIAP_PUMP_3,PIN_DIAP_PUMP_3,status);break;
		case DIAP_PUMP4:DIAP_PUMP_Set(PORT_DIAP_PUMP_4,PIN_DIAP_PUMP_4,status);break;
		case DIAP_PUMP5:DIAP_PUMP_Set(PORT_DIAP_PUMP_5,PIN_DIAP_PUMP_5,status);break;
		case DIAP_PUMP6:DIAP_PUMP_Set(PORT_DIAP_PUMP_6,PIN_DIAP_PUMP_6,status);break;
		case DIAP_PUMP7:DIAP_PUMP_Set(PORT_DIAP_PUMP_7,PIN_DIAP_PUMP_7,status);break;
		case DIAP_PUMP8:DIAP_PUMP_Set(PORT_DIAP_PUMP_8,PIN_DIAP_PUMP_8,status);break;
		case DIAP_PUMP9:DIAP_PUMP_Set(PORT_DIAP_PUMP_9,PIN_DIAP_PUMP_9,status);break;
		case DIAP_PUMP10:DIAP_PUMP_Set(PORT_DIAP_PUMP_10,PIN_DIAP_PUMP_10,status);break;
		case DIAP_PUMP15:DIAP_PUMP_Set(PORT_DIAP_PUMP_15,PIN_DIAP_PUMP_15,status);break;
		case DIAP_PUMP16:DIAP_PUMP_Set(PORT_DIAP_PUMP_16,PIN_DIAP_PUMP_16,status);break;
		default:
			break;
	}
}

/******************************************************************************/
void DIAP_PUMP_OPEN(void)
{
	DIAP_PUMP_Control(DIAP_PUMP1,ENABLE);
	DIAP_PUMP_Control(DIAP_PUMP2,ENABLE);
	DIAP_PUMP_Control(DIAP_PUMP3,ENABLE);
	DIAP_PUMP_Control(DIAP_PUMP4,ENABLE);
	DIAP_PUMP_Control(DIAP_PUMP5,ENABLE);
	DIAP_PUMP_Control(DIAP_PUMP6,ENABLE);
	DIAP_PUMP_Control(DIAP_PUMP7,ENABLE);
	DIAP_PUMP_Control(DIAP_PUMP8,ENABLE);
	DIAP_PUMP_Control(DIAP_PUMP9,ENABLE);
	DIAP_PUMP_Control(DIAP_PUMP10,ENABLE);
	DIAP_PUMP_Control(DIAP_PUMP15,ENABLE);
	DIAP_PUMP_Control(DIAP_PUMP16,ENABLE);
}

/******************************************************************************/
void DIAP_PUMP_CLOSED(void)
{
	DIAP_PUMP_Control(DIAP_PUMP1,DISABLE);
	DIAP_PUMP_Control(DIAP_PUMP2,DISABLE);
	DIAP_PUMP_Control(DIAP_PUMP3,DISABLE);
	DIAP_PUMP_Control(DIAP_PUMP4,DISABLE);
	DIAP_PUMP_Control(DIAP_PUMP5,DISABLE);
	DIAP_PUMP_Control(DIAP_PUMP6,DISABLE);
	DIAP_PUMP_Control(DIAP_PUMP7,DISABLE);
	DIAP_PUMP_Control(DIAP_PUMP8,DISABLE);
	DIAP_PUMP_Control(DIAP_PUMP9,DISABLE);
	DIAP_PUMP_Control(DIAP_PUMP10,DISABLE);
	DIAP_PUMP_Control(DIAP_PUMP15,DISABLE);
	DIAP_PUMP_Control(DIAP_PUMP16,DISABLE);
}

/******************************************************************************/
void VAVLE_Init (void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC |
				RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOD, ENABLE);

	/* Initialize pins */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	/* Valve 1 */
	GPIO_InitStructure.GPIO_Pin = PIN_VALVE1;
	GPIO_Init(PORT_VALVE1, &GPIO_InitStructure);

	/* Valve 2 */
	GPIO_InitStructure.GPIO_Pin = PIN_VALVE2;
	GPIO_Init(PORT_VALVE2, &GPIO_InitStructure);

	/* Valve 3 */
	GPIO_InitStructure.GPIO_Pin = PIN_VALVE3;
	GPIO_Init(PORT_VALVE3, &GPIO_InitStructure);

	/* Valve 4 */
	GPIO_InitStructure.GPIO_Pin = PIN_VALVE4;
	GPIO_Init(PORT_VALVE4, &GPIO_InitStructure);

	/* Valve 5 */
	GPIO_InitStructure.GPIO_Pin = PIN_VALVE5;
	GPIO_Init(PORT_VALVE5, &GPIO_InitStructure);

	/* Valve 6 */
	GPIO_InitStructure.GPIO_Pin = PIN_VALVE6;
	GPIO_Init(PORT_VALVE6, &GPIO_InitStructure);

	/* Valve 7 */
	GPIO_InitStructure.GPIO_Pin = PIN_VALVE7;
	GPIO_Init(PORT_VALVE7, &GPIO_InitStructure);

	/* Valve 8 */
	GPIO_InitStructure.GPIO_Pin = PIN_VALVE8;
	GPIO_Init(PORT_VALVE8, &GPIO_InitStructure);

	/* Valve 9 */
	GPIO_InitStructure.GPIO_Pin = PIN_VALVE9;
	GPIO_Init(PORT_VALVE9, &GPIO_InitStructure);

	/* Valve 10 */
	GPIO_InitStructure.GPIO_Pin = PIN_VALVE10;
	GPIO_Init(PORT_VALVE10, &GPIO_InitStructure);
}

/******************************************************************************/
void VAVLE_OPEN (void)
{
	Valve1_Control(ENABLE);
	Valve2_Control(ENABLE);
	Valve3_Control(ENABLE);
	Valve4_Control(ENABLE);
	Valve5_Control(ENABLE);
	Valve6_Control(ENABLE);
	Valve7_Control(ENABLE);
	Valve8_Control(ENABLE);
	Valve9_Control(ENABLE);
	Valve10_Control(ENABLE);
}

/******************************************************************************/
void VAVLE_CLOSED (void)
{
	Valve1_Control(DISABLE);
	Valve2_Control(DISABLE);
	Valve3_Control(DISABLE);
	Valve4_Control(DISABLE);
	Valve5_Control(DISABLE);
	Valve6_Control(DISABLE);
	Valve7_Control(DISABLE);
	Valve8_Control(DISABLE);
	Valve9_Control(DISABLE);
	Valve10_Control(DISABLE);
}

/******************************************************************************/
void Valve1_Control(uint8 status)
{
	(OPEN == status)?GPIO_SetBits(PORT_VALVE1, PIN_VALVE1):GPIO_ResetBits(PORT_VALVE1, PIN_VALVE1);
}

/******************************************************************************/
void Valve2_Control(uint8 status)
{
	(OPEN == status)?GPIO_SetBits(PORT_VALVE2, PIN_VALVE2):GPIO_ResetBits(PORT_VALVE2, PIN_VALVE2);
}

/******************************************************************************/
void Valve3_Control(uint8 status)
{
	(OPEN == status)?GPIO_SetBits(PORT_VALVE3, PIN_VALVE3):GPIO_ResetBits(PORT_VALVE3, PIN_VALVE3);
}

/******************************************************************************/
void Valve4_Control(uint8 status)
{
	(OPEN == status)?GPIO_SetBits(PORT_VALVE4, PIN_VALVE4):GPIO_ResetBits(PORT_VALVE4, PIN_VALVE4);
}

/******************************************************************************/
void Valve5_Control(uint8 status)
{
	(OPEN == status)?GPIO_SetBits(PORT_VALVE5, PIN_VALVE5):GPIO_ResetBits(PORT_VALVE5, PIN_VALVE5);
}

/******************************************************************************/
void Valve6_Control(uint8 status)
{
	(OPEN == status)?GPIO_SetBits(PORT_VALVE6, PIN_VALVE6):GPIO_ResetBits(PORT_VALVE6, PIN_VALVE6);
}

/******************************************************************************/
void Valve7_Control(uint8 status)
{
	(OPEN == status)?GPIO_SetBits(PORT_VALVE7, PIN_VALVE7):GPIO_ResetBits(PORT_VALVE7, PIN_VALVE7);
}

/******************************************************************************/
void Valve8_Control(uint8 status)
{
	(OPEN == status)?GPIO_SetBits(PORT_VALVE8, PIN_VALVE8):GPIO_ResetBits(PORT_VALVE8, PIN_VALVE8);
}

/******************************************************************************/
void Valve9_Control(uint8 status)
{
	(OPEN == status)?GPIO_SetBits(PORT_VALVE9, PIN_VALVE9):GPIO_ResetBits(PORT_VALVE9, PIN_VALVE9);
}

/******************************************************************************/
void Valve10_Control(uint8 status)
{
	(OPEN == status)?GPIO_SetBits(PORT_VALVE10, PIN_VALVE10):GPIO_ResetBits(PORT_VALVE10, PIN_VALVE10);
}
