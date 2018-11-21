#ifndef SOURCE_MODULES_DEVICES_DEVICES_H_
#define SOURCE_MODULES_DEVICES_DEVICES_H_ 

/******************************************************************************/
#include "Project_File.h"

/******************************************************************************/
#define PORT_LED_HEAT_1					(GPIOD)
#define PIN_LED_HEAT_1					(GPIO_Pin_4)

#define PORT_LED_HEAT_2					(GPIOD)
#define PIN_LED_HEAT_2					(GPIO_Pin_3)

#define PORT_LED_HEAT_3					(GPIOD)
#define PIN_LED_HEAT_3					(GPIO_Pin_2)

#define PORT_KEY_CTR					(GPIOB)
#define PIN_KEY_CTR						(GPIO_Pin_6)

#define PORT_PUMP_1						(GPIOB)
#define PIN_PUMP_1						(GPIO_Pin_12)

#define PORT_PUMP_2						(GPIOB)
#define PIN_PUMP_2						(GPIO_Pin_13)

#define PORT_PUMP_3						(GPIOB)
#define PIN_PUMP_3						(GPIO_Pin_14)

#define PORT_PUMP_4						(GPIOB)
#define PIN_PUMP_4						(GPIO_Pin_15)

#define PORT_PUMP_5						(GPIOD)
#define PIN_PUMP_5						(GPIO_Pin_8)

#define PORT_PUMP_6						(GPIOD)
#define PIN_PUMP_6						(GPIO_Pin_9)

#define PORT_PUMP_7						(GPIOD)
#define PIN_PUMP_7						(GPIO_Pin_10)

#define PORT_PUMP_8						(GPIOD)
#define PIN_PUMP_8						(GPIO_Pin_11)

#define PORT_PUMP_9						(GPIOD)
#define PIN_PUMP_9						(GPIO_Pin_12)

#define PORT_PUMP_10					(GPIOD)
#define PIN_PUMP_10						(GPIO_Pin_13)

#define PORT_PUMP_11					(GPIOD)
#define PIN_PUMP_11						(GPIO_Pin_14)

#define PORT_PUMP_12					(GPIOD)
#define PIN_PUMP_12						(GPIO_Pin_15)

#define PORT_PUMP_13					(GPIOC)
#define PIN_PUMP_13						(GPIO_Pin_6)

#define PORT_PUMP_14					(GPIOC)
#define PIN_PUMP_14						(GPIO_Pin_7)

#define PORT_PUMP_15					(GPIOC)
#define PIN_PUMP_15						(GPIO_Pin_8)

#define PORT_PUMP_16					(GPIOC)
#define PIN_PUMP_16						(GPIO_Pin_9)

#define PORT_PUMP_17					(GPIOA)
#define PIN_PUMP_17						(GPIO_Pin_8)

#define PORT_PUMP_18					(GPIOA)
#define PIN_PUMP_18						(GPIO_Pin_11)

#define PORT_PUMP_19					(GPIOA)
#define PIN_PUMP_19						(GPIO_Pin_12)

#define PORT_PUMP_20					(GPIOC)
#define PIN_PUMP_20						(GPIO_Pin_10)

#define KEY GPIO_ReadInputDataBit(PORT_KEY_CTR,PIN_KEY_CTR)

/******************************************************************************/
typedef enum
{
	 PUMP1=1,
	 PUMP2,				
	 PUMP3,				
	 PUMP4,				
	 PUMP5,				
	 PUMP6,				
	 PUMP7,				
	 PUMP8,				
	 PUMP9,				
	 PUMP10,			
	 PUMP11,			
	 PUMP12,			
	 PUMP13,			
	 PUMP14,			
	 PUMP15,			
	 PUMP16,			
	 PUMP17,			
	 PUMP18,			
	 PUMP19,			
	 PUMP20,  		
}PUMP_NUM;

/******************************************************************************/
extern PUMP_NUM Pump;
extern uint32 Count;

/******************************************************************************/
extern void Devices_Init(void);
extern void Devices_Return_Zero(void);
extern void Devices_Valve_Action(void);
extern void Pump_Control(PUMP_NUM Pump,FunctionalState status);

extern void Valve1_Lock (uint8 status);
extern void Valve2_Lock (uint8 status);
extern void Valve3_Lock (uint8 status);
extern void Valve4_Lock (uint8 status);
extern void Valve5_Lock (uint8 status);
extern void Valve6_Lock (uint8 status);
extern void Valve7_Lock (uint8 status);
extern void Valve8_Lock (uint8 status);
extern void Valve9_Lock (uint8 status);
extern void Valve10_Lock (uint8 status);
extern void Valve11_Lock (uint8 status);

extern void Warm_Achieve (void);
extern void Valve1_Action (void);
extern void Valve2_Action (void);
extern void Valve3_Action (void);
extern void Valve4_Action (void);
extern void Valve5_Action (void);
extern void Valve6_Action (void);
extern void Valve7_Action (void);
extern void Valve8_Action (void);


#endif

