#ifndef SOURCE_MODULES_DEVICES_DEVICES_H_
#define SOURCE_MODULES_DEVICES_DEVICES_H_ 

/******************************************************************************/
#include "Project_File.h"

/******************************************************************************/
#define SUBDIVISION_1ML					(4)
#define SUBDIVISION_5ML					(4)

/******************************************************************************/
#define PORT_DIAP_PUMP_1					(GPIOD)
#define PIN_DIAP_PUMP_1						(GPIO_Pin_4)

#define PORT_DIAP_PUMP_2					(GPIOD)
#define PIN_DIAP_PUMP_2						(GPIO_Pin_5)

#define PORT_DIAP_PUMP_3					(GPIOD)
#define PIN_DIAP_PUMP_3						(GPIO_Pin_6)

#define PORT_DIAP_PUMP_4					(GPIOD)
#define PIN_DIAP_PUMP_4						(GPIO_Pin_7)

#define PORT_DIAP_PUMP_5					(GPIOB)
#define PIN_DIAP_PUMP_5						(GPIO_Pin_4)

#define PORT_DIAP_PUMP_6					(GPIOB)
#define PIN_DIAP_PUMP_6						(GPIO_Pin_5)

#define PORT_DIAP_PUMP_7					(GPIOB)
#define PIN_DIAP_PUMP_7						(GPIO_Pin_6)

#define PORT_DIAP_PUMP_8					(GPIOB)
#define PIN_DIAP_PUMP_8						(GPIO_Pin_7)

#define PORT_DIAP_PUMP_9					(GPIOE)
#define PIN_DIAP_PUMP_9						(GPIO_Pin_0)

#define PORT_DIAP_PUMP_10					(GPIOE)
#define PIN_DIAP_PUMP_10					(GPIO_Pin_1)

#define PORT_DIAP_PUMP_15					(GPIOC)
#define PIN_DIAP_PUMP_15					(GPIO_Pin_3)

#define PORT_DIAP_PUMP_16					(GPIOB)
#define PIN_DIAP_PUMP_16					(GPIO_Pin_3)

/******************************************************************************/
#define PORT_VALVE1							(GPIOA)
#define PIN_VALVE1							(GPIO_Pin_11)

#define PORT_VALVE2							(GPIOA)
#define PIN_VALVE2							(GPIO_Pin_12)

#define PORT_VALVE3							(GPIOA)
#define PIN_VALVE3							(GPIO_Pin_15)

#define PORT_VALVE4							(GPIOC)
#define PIN_VALVE4							(GPIO_Pin_10)

#define PORT_VALVE5							(GPIOC)
#define PIN_VALVE5							(GPIO_Pin_11)

#define PORT_VALVE6							(GPIOC)
#define PIN_VALVE6							(GPIO_Pin_12)

#define PORT_VALVE7							(GPIOD)
#define PIN_VALVE7							(GPIO_Pin_0)

#define PORT_VALVE8							(GPIOD)
#define PIN_VALVE8							(GPIO_Pin_1)

#define PORT_VALVE9							(GPIOD)
#define PIN_VALVE9							(GPIO_Pin_2)

#define PORT_VALVE10						(GPIOD)
#define PIN_VALVE10							(GPIO_Pin_3)

/******************************************************************************/
typedef enum
{
	 DIAP_PUMP1=1,
	 DIAP_PUMP2,
	 DIAP_PUMP3,
	 DIAP_PUMP4,
	 DIAP_PUMP5,
	 DIAP_PUMP6,
	 DIAP_PUMP7,
	 DIAP_PUMP8,
	 DIAP_PUMP9,
	 DIAP_PUMP10,
	 DIAP_PUMP11,
	 DIAP_PUMP12,
	 DIAP_PUMP13,
	 DIAP_PUMP14,
	 DIAP_PUMP15,
	 DIAP_PUMP16,
	 DIAP_PUMP17,
	 DIAP_PUMP18,
	 DIAP_PUMP19,
	 DIAP_PUMP20,
}DIAP_PUMP_NUM;

/******************************************************************************/
extern DIAP_PUMP_NUM DIAP_PUMP;

/******************************************************************************/
extern void VAVLE_Init (void);
extern void Devices_Init(void);
extern void DIAP_PUMP_Init (void);
extern void VAVLE_OPEN (void);
extern void VAVLE_CLOSED (void);
extern void DIAP_PUMP_OPEN(void);
extern void DIAP_PUMP_CLOSED(void);
extern void Set_Initialize_Parameter(void);
extern void DIAP_PUMP_Control(DIAP_PUMP_NUM DIAP_PUMP,FunctionalState status);

/******************************************************************************/
extern void Valve1_Control(uint8 status);
extern void Valve2_Control(uint8 status);
extern void Valve3_Control(uint8 status);
extern void Valve4_Control(uint8 status);
extern void Valve5_Control(uint8 status);
extern void Valve6_Control(uint8 status);
extern void Valve7_Control(uint8 status);
extern void Valve8_Control(uint8 status);
extern void Valve9_Control(uint8 status);
extern void Valve10_Control(uint8 status);

#endif

