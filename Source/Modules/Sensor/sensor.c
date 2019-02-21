/******************************************************************************/
#include "sensor.h"

/******************************************************************************/
SWITCH_NUM Switch;
FLAG ExitFlag;

/******************************************************************************/
void PosSensor_Init(void)
{
	/**************************************************************************/
#if TIMER1_M10_R1_R2_ENABLED
	Common_EXTI_Init(PORT_SWITCH_10, PIN_SWITCH_10,
			GPIO_PortSourceGPIOE, GPIO_PinSource11, EXTI_Line11,
			EXTI_Trigger_Rising, ENABLE, EXTI15_10_IRQn, 0X00, 0X010);
#endif

	/**************************************************************************/
#if TIMER2_M3_M_W1_ENABLED
	Common_EXTI_Init(PORT_SWITCH_3, PIN_SWITCH_3,
			GPIO_PortSourceGPIOC, GPIO_PinSource5, EXTI_Line5,
			EXTI_Trigger_Rising, ENABLE, EXTI9_5_IRQn, 0X00, 0X03);
#endif

	/**************************************************************************/
#if TIMER3_M6_W2_W3_ENABLED
	Common_EXTI_Init(PORT_SWITCH_6, PIN_SWITCH_6,
				GPIO_PortSourceGPIOE, GPIO_PinSource7, EXTI_Line7,
				EXTI_Trigger_Rising, ENABLE, EXTI9_5_IRQn, 0X00, 0X06);
#endif

	/**************************************************************************/
#if TIMER4_M4_W6_BASE_ENABLED
	Common_EXTI_Init(PORT_SWITCH_4, PIN_SWITCH_4,
			GPIO_PortSourceGPIOB, GPIO_PinSource0, EXTI_Line0,
			EXTI_Trigger_Rising, ENABLE, EXTI0_IRQn, 0X00, 0X04);
#endif

	/**************************************************************************/
#if TIMER5_M1_W4_W5_ENABLED
	Common_EXTI_Init(PORT_SWITCH_1, PIN_SWITCH_1,
			GPIO_PortSourceGPIOA, GPIO_PinSource3, EXTI_Line3,
			EXTI_Trigger_Rising, ENABLE, EXTI3_IRQn, 0X00, 0X01);
#endif
}

/******************************************************************************/
void PosSensor_M10_ENABLE(void)
{
	Common_EXTI_Init(PORT_SWITCH_10, PIN_SWITCH_10,
			GPIO_PortSourceGPIOE, GPIO_PinSource11, EXTI_Line11,
			EXTI_Trigger_Rising, ENABLE, EXTI15_10_IRQn, 0X00, 0X010);
}

void PosSensor_M10_DISABLE(void)
{
	Common_EXTI_Init(PORT_SWITCH_10, PIN_SWITCH_10,
			GPIO_PortSourceGPIOE, GPIO_PinSource11, EXTI_Line11,
			EXTI_Trigger_Rising, DISABLE, EXTI15_10_IRQn, 0X00, 0X010);
}

/******************************************************************************/
void PosSensor_M3_ENABLE(void)
{
	Common_EXTI_Init(PORT_SWITCH_3, PIN_SWITCH_3,
			GPIO_PortSourceGPIOC, GPIO_PinSource5, EXTI_Line5,
			EXTI_Trigger_Rising, ENABLE, EXTI9_5_IRQn, 0X00, 0X03);
}

void PosSensor_M3_DISABLE(void)
{
	Common_EXTI_Init(PORT_SWITCH_3, PIN_SWITCH_3,
			GPIO_PortSourceGPIOC, GPIO_PinSource5, EXTI_Line5,
			EXTI_Trigger_Rising, DISABLE, EXTI9_5_IRQn, 0X00, 0X03);
}

/******************************************************************************/
void PosSensor_M6_ENABLE(void)
{
	Common_EXTI_Init(PORT_SWITCH_6, PIN_SWITCH_6,
				GPIO_PortSourceGPIOE, GPIO_PinSource7, EXTI_Line7,
				EXTI_Trigger_Rising, ENABLE, EXTI9_5_IRQn, 0X00, 0X06);
}

void PosSensor_M6_DISABLE(void)
{
	Common_EXTI_Init(PORT_SWITCH_6, PIN_SWITCH_6,
				GPIO_PortSourceGPIOE, GPIO_PinSource7, EXTI_Line7,
				EXTI_Trigger_Rising, DISABLE, EXTI9_5_IRQn, 0X00, 0X06);
}

/******************************************************************************/
void PosSensor_M4_ENABLE(void)
{
	Common_EXTI_Init(PORT_SWITCH_4, PIN_SWITCH_4,
			GPIO_PortSourceGPIOB, GPIO_PinSource0, EXTI_Line0,
			EXTI_Trigger_Rising, ENABLE, EXTI0_IRQn, 0X00, 0X04);
}

void PosSensor_M4_DISABLE(void)
{
	Common_EXTI_Init(PORT_SWITCH_4, PIN_SWITCH_4,
			GPIO_PortSourceGPIOB, GPIO_PinSource0, EXTI_Line0,
			EXTI_Trigger_Rising, DISABLE, EXTI0_IRQn, 0X00, 0X04);
}

/******************************************************************************/
void PosSensor_M1_ENABLE(void)
{
	Common_EXTI_Init(PORT_SWITCH_1, PIN_SWITCH_1,
			GPIO_PortSourceGPIOA, GPIO_PinSource3, EXTI_Line3,
			EXTI_Trigger_Rising, ENABLE, EXTI3_IRQn, 0X00, 0X01);
}

void PosSensor_M1_DISABLE(void)
{
	Common_EXTI_Init(PORT_SWITCH_1, PIN_SWITCH_1,
			GPIO_PortSourceGPIOA, GPIO_PinSource3, EXTI_Line3,
			EXTI_Trigger_Rising, DISABLE, EXTI3_IRQn, 0X00, 0X01);
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
