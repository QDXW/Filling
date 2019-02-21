/*
 * Motor.h
 *
 *  Created on: 2019Äê2ÔÂ14ÈÕ
 *      Author: Administrator
 */

#ifndef MODULES_MOTOR_MOTOR_H_
#define MODULES_MOTOR_MOTOR_H_

/******************************************************************************/
#include "Project_File.h"

/******************************************************************************/
#define PUMP_PRECISION_PWM_PERIOD_1ML		(1200)
#define PUMP_PRECISION_PWM_PERIOD_5ML		(800)

/******************************************************************************/
#define PORT_MOTOR_M1_EN			(GPIOA)
#define PIN_MOTOR_M1_EN				(GPIO_Pin_4)

#define PORT_MOTOR_M1_STP			(GPIOA)
#define PIN_MOTOR_M1_STP			(GPIO_Pin_0)

#define PORT_MOTOR_M1_DIR			(GPIOB)
#define PIN_MOTOR_M1_DIR			(GPIO_Pin_12)

/******************************************************************************/
#define PORT_MOTOR_M2_EN			(GPIOA)
#define PIN_MOTOR_M2_EN				(GPIO_Pin_5)

#define PORT_MOTOR_M2_STP			(GPIOA)
#define PIN_MOTOR_M2_STP			(GPIO_Pin_1)

#define PORT_MOTOR_M2_DIR			(GPIOB)
#define PIN_MOTOR_M2_DIR			(GPIO_Pin_13)

/******************************************************************************/
#define PORT_MOTOR_M3_EN			(GPIOA)
#define PIN_MOTOR_M3_EN				(GPIO_Pin_6)

#define PORT_MOTOR_M3_STP			(GPIOA)
#define PIN_MOTOR_M3_STP			(GPIO_Pin_2)

#define PORT_MOTOR_M3_DIR			(GPIOB)
#define PIN_MOTOR_M3_DIR			(GPIO_Pin_14)

/******************************************************************************/
#define PORT_MOTOR_M4_EN			(GPIOA)
#define PIN_MOTOR_M4_EN				(GPIO_Pin_7)

#define PORT_MOTOR_M4_STP			(GPIOD)
#define PIN_MOTOR_M4_STP			(GPIO_Pin_14)

#define PORT_MOTOR_M4_DIR			(GPIOB)
#define PIN_MOTOR_M4_DIR			(GPIO_Pin_15)

/******************************************************************************/
#define PORT_MOTOR_M5_EN			(GPIOE)
#define PIN_MOTOR_M5_EN				(GPIO_Pin_12)

#define PORT_MOTOR_M5_STP			(GPIOD)
#define PIN_MOTOR_M5_STP			(GPIO_Pin_15)

#define PORT_MOTOR_M5_DIR			(GPIOD)
#define PIN_MOTOR_M5_DIR			(GPIO_Pin_8)

/******************************************************************************/
#define PORT_MOTOR_M6_EN			(GPIOE)
#define PIN_MOTOR_M6_EN				(GPIO_Pin_13)

#define PORT_MOTOR_M6_STP			(GPIOC)
#define PIN_MOTOR_M6_STP			(GPIO_Pin_6)

#define PORT_MOTOR_M6_DIR			(GPIOD)
#define PIN_MOTOR_M6_DIR			(GPIO_Pin_9)

/******************************************************************************/
#define PORT_MOTOR_M7_EN			(GPIOE)
#define PIN_MOTOR_M7_EN				(GPIO_Pin_14)

#define PORT_MOTOR_M7_STP			(GPIOC)
#define PIN_MOTOR_M7_STP			(GPIO_Pin_7)

#define PORT_MOTOR_M7_DIR			(GPIOD)
#define PIN_MOTOR_M7_DIR			(GPIO_Pin_10)

/******************************************************************************/
#define PORT_MOTOR_M8_EN			(GPIOE)			//M8
#define PIN_MOTOR_M8_EN				(GPIO_Pin_15)

#define PORT_MOTOR_M8_STP			(GPIOC)
#define PIN_MOTOR_M8_STP			(GPIO_Pin_8)

#define PORT_MOTOR_M8_DIR			(GPIOD)
#define PIN_MOTOR_M8_DIR			(GPIO_Pin_11)

/******************************************************************************/
#define PORT_MOTOR_M9_EN			(GPIOB)			//M9
#define PIN_MOTOR_M9_EN				(GPIO_Pin_10)

#define PORT_MOTOR_M9_STP			(GPIOC)
#define PIN_MOTOR_M9_STP			(GPIO_Pin_9)

#define PORT_MOTOR_M9_DIR			(GPIOD)
#define PIN_MOTOR_M9_DIR			(GPIO_Pin_12)


/******************************************************************************/
#define PORT_MOTOR_M10_EN			(GPIOB)
#define PIN_MOTOR_M10_EN			(GPIO_Pin_11)

#define PORT_MOTOR_M10_STP			(GPIOA)
#define PIN_MOTOR_M10_STP			(GPIO_Pin_8)

#define PORT_MOTOR_M10_DIR			(GPIOD)
#define PIN_MOTOR_M10_DIR			(GPIO_Pin_13)

/******************************************************************************/
extern void Motor_Init(void);
extern void RAM_PUMP_Init (void);

/******************************************************************************/
extern void Motor_M1_Init(void);
extern void Movement_M1_Stop(void);
extern void Movement_M1_Start(void);
extern void Movement_M1_MotorDriver_DIR(MOTOR_DIR dir);
extern void Movement_M1_MotorDriver_EN(POWER_LEVEL status);
extern void Movement_M1_MotorDriver_PWM(FunctionalState status);

/******************************************************************************/
extern void Motor_M2_Init(void);
extern void Movement_M2_Stop(void);
extern void Movement_M2_Start(void);
extern void Movement_M2_MotorDriver_DIR(MOTOR_DIR dir);
extern void Movement_M2_MotorDriver_EN(POWER_LEVEL status);
extern void Movement_M2_MotorDriver_PWM(FunctionalState status);

/******************************************************************************/
extern void Motor_M3_Init(void);
extern void Movement_M3_Stop(void);
extern void Movement_M3_Start(void);
extern void Movement_M3_MotorDriver_DIR(MOTOR_DIR dir);
extern void Movement_M3_MotorDriver_EN(POWER_LEVEL status);
extern void Movement_M3_MotorDriver_PWM(FunctionalState status);

/******************************************************************************/
extern void Motor_M4_Init(void);
extern void Movement_M4_Stop(void);
extern void Movement_M4_Start(void);
extern void Movement_M4_MotorDriver_DIR(MOTOR_DIR dir);
extern void Movement_M4_MotorDriver_EN(POWER_LEVEL status);
extern void Movement_M4_MotorDriver_PWM(FunctionalState status);

/******************************************************************************/
extern void Motor_M5_Init(void);
extern void Movement_M5_Stop(void);
extern void Movement_M5_Start(void);
extern void Movement_M5_MotorDriver_DIR(MOTOR_DIR dir);
extern void Movement_M5_MotorDriver_EN(POWER_LEVEL status);
extern void Movement_M5_MotorDriver_PWM(FunctionalState status);

/******************************************************************************/
extern void Motor_M6_Init(void);
extern void Movement_M6_Stop(void);
extern void Movement_M6_Start(void);
extern void Movement_M6_MotorDriver_DIR(MOTOR_DIR dir);
extern void Movement_M6_MotorDriver_EN(POWER_LEVEL status);
extern void Movement_M6_MotorDriver_PWM(FunctionalState status);

/******************************************************************************/
extern void Motor_M7_Init(void);
extern void Movement_M7_Stop(void);
extern void Movement_M7_Start(void);
extern void Movement_M7_MotorDriver_DIR(MOTOR_DIR dir);
extern void Movement_M7_MotorDriver_EN(POWER_LEVEL status);
extern void Movement_M7_MotorDriver_PWM(FunctionalState status);

/******************************************************************************/
extern void Motor_M8_Init(void);
extern void Movement_M8_Stop(void);
extern void Movement_M8_Start(void);
extern void Movement_M8_MotorDriver_DIR(MOTOR_DIR dir);
extern void Movement_M8_MotorDriver_EN(POWER_LEVEL status);
extern void Movement_M8_MotorDriver_PWM(FunctionalState status);

/******************************************************************************/
extern void Motor_M9_Init(void);
extern void Movement_M9_Stop(void);
extern void Movement_M9_Start(void);
extern void Movement_M9_MotorDriver_DIR(MOTOR_DIR dir);
extern void Movement_M9_MotorDriver_EN(POWER_LEVEL status);
extern void Movement_M9_MotorDriver_PWM(FunctionalState status);

/******************************************************************************/
extern void Motor_M10_Init(void);
extern void Movement_M10_Stop(void);
extern void Movement_M10_Start(void);
extern void Movement_M10_MotorDriver_DIR(MOTOR_DIR dir);
extern void Movement_M10_MotorDriver_EN(POWER_LEVEL status);
extern void Movement_M10_MotorDriver_PWM(FunctionalState status);

extern void Motor_TIMER1_M10_Init(void);
extern void Motor_TIMER2_M3_Init(void);
extern void Motor_TIMER3_M6_Init(void);
extern void Motor_TIMER4_M4_Init(void);
extern void Motor_TIMER5_M1_Init(void);

#endif /* MODULES_MOTOR_MOTOR_H_ */
