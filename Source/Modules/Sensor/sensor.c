/******************************************************************************/
#include "sensor.h"

/******************************************************************************/
SWITCH_NUM Switch;
FLAG ExitFlag;

/******************************************************************************/
void PosSensor_Init(void)
{
	Common_EXTI_Init(PORT_SWITCH_1, PIN_SWITCH_1,
			GPIO_PortSourceGPIOA, GPIO_PinSource3, EXTI_Line3,
			EXTI_Trigger_Rising, ENABLE, EXTI3_IRQn, 0X01, 0X01);

	Common_EXTI_Init(PORT_SWITCH_2, PIN_SWITCH_2,
			GPIO_PortSourceGPIOC, GPIO_PinSource4, EXTI_Line4,
			EXTI_Trigger_Rising, ENABLE, EXTI4_IRQn, 0X01, 0X01);

	Common_EXTI_Init(PORT_SWITCH_3, PIN_SWITCH_3,
			GPIO_PortSourceGPIOC, GPIO_PinSource5, EXTI_Line5,
			EXTI_Trigger_Rising, ENABLE, EXTI9_5_IRQn, 0X01, 0X01);

	Common_EXTI_Init(PORT_SWITCH_4, PIN_SWITCH_4,
			GPIO_PortSourceGPIOB, GPIO_PinSource0, EXTI_Line0,
			EXTI_Trigger_Rising, ENABLE, EXTI0_IRQn, 0X01, 0X01);

	Common_EXTI_Init(PORT_SWITCH_5, PIN_SWITCH_5,
			GPIO_PortSourceGPIOB, GPIO_PinSource1, EXTI_Line1,
			EXTI_Trigger_Rising, ENABLE, EXTI1_IRQn, 0X01, 0X01);

	Common_EXTI_Init(PORT_SWITCH_6, PIN_SWITCH_6,
				GPIO_PortSourceGPIOE, GPIO_PinSource7, EXTI_Line7,
				EXTI_Trigger_Rising, ENABLE, EXTI9_5_IRQn, 0X01, 0X01);

	Common_EXTI_Init(PORT_SWITCH_7, PIN_SWITCH_7,
			GPIO_PortSourceGPIOE, GPIO_PinSource8, EXTI_Line8,
			EXTI_Trigger_Rising, ENABLE, EXTI9_5_IRQn, 0X01, 0X01);

	Common_EXTI_Init(PORT_SWITCH_8, PIN_SWITCH_8,
			GPIO_PortSourceGPIOE, GPIO_PinSource9, EXTI_Line9,
			EXTI_Trigger_Rising, ENABLE, EXTI9_5_IRQn, 0X01, 0X01);

	Common_EXTI_Init(PORT_SWITCH_9, PIN_SWITCH_9,
			GPIO_PortSourceGPIOE, GPIO_PinSource10, EXTI_Line10,
			EXTI_Trigger_Rising, ENABLE, EXTI15_10_IRQn, 0X01, 0X01);

	Common_EXTI_Init(PORT_SWITCH_10, PIN_SWITCH_10,
			GPIO_PortSourceGPIOE, GPIO_PinSource11, EXTI_Line11,
			EXTI_Trigger_Rising, ENABLE, EXTI15_10_IRQn, 0X01, 0X01);
}

/******************************************************************************/
uint8 Pos_Read_Sensor(SWITCH_NUM Switch)
{
	switch(Switch)
	{
		case SWITCH1:return (!GPIO_ReadInputDataBit(PORT_SWITCH_1, PIN_SWITCH_1));
		case SWITCH2:return (!GPIO_ReadInputDataBit(PORT_SWITCH_2, PIN_SWITCH_2));
		case SWITCH3:return (!GPIO_ReadInputDataBit(PORT_SWITCH_3, PIN_SWITCH_3));
		case SWITCH4:return (!GPIO_ReadInputDataBit(PORT_SWITCH_4, PIN_SWITCH_4));
		case SWITCH5:return (!GPIO_ReadInputDataBit(PORT_SWITCH_5, PIN_SWITCH_5));
		case SWITCH6:return (!GPIO_ReadInputDataBit(PORT_SWITCH_6, PIN_SWITCH_6));
		case SWITCH7:return (!GPIO_ReadInputDataBit(PORT_SWITCH_7, PIN_SWITCH_7));
		case SWITCH8:return (!GPIO_ReadInputDataBit(PORT_SWITCH_8, PIN_SWITCH_8));
		case SWITCH9:return (!GPIO_ReadInputDataBit(PORT_SWITCH_9, PIN_SWITCH_9));
		case SWITCH10:return (!GPIO_ReadInputDataBit(PORT_SWITCH_10, PIN_SWITCH_10));
		default:break;	
	}
	return 0;
}
