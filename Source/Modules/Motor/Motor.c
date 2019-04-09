/*
 * Motor.c
 *
 *  Created on: 2019年2月14日
 *      Author: Administrator
 */

/******************************************************************************/
#include "Motor.h"

/******************************************************************************/
void Motor_Init(void)
{
	RAM_PUMP_Init();
}

/******************************************************************************/
void RAM_PUMP_Init (void)
{
	/**************************************************************************/
	/* TIMER1 */
#if TIMER1_M10_R1_R2_ENABLED
	Motor_TIMER1_M10_Init();
#endif
	/**************************************************************************/
	/* TIMER2 */
#if TIMER2_M3_M_W1_ENABLED
	Motor_TIMER2_M3_Init();
#endif
	/**************************************************************************/
	/* TIMER3 */
#if TIMER3_M6_W2_W3_ENABLED
	Motor_TIMER3_M6_Init();
#endif
	/**************************************************************************/
	/* TIMER4 */
#if TIMER4_M4_W6_BASE_ENABLED
	Motor_TIMER4_M4_Init();
#endif
	/**************************************************************************/
	/* TIMER5 */
#if TIMER5_M1_W4_W5_ENABLED
	Motor_TIMER5_M1_Init();
#endif
}

/******************************************************************************/
void Motor_TIMER5_M1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	/* Initialize pins */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	/* EN */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M1_EN;
	GPIO_Init(PORT_MOTOR_M1_EN, &GPIO_InitStructure);
	Movement_M1_MotorDriver_EN(LEVEL_LOW);

	/* CW */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M1_DIR;
	GPIO_Init(PORT_MOTOR_M1_DIR, &GPIO_InitStructure);
	Movement_M1_MotorDriver_DIR(DIR_CCW);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

	/* STP */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M1_STP;
	GPIO_Init(PORT_MOTOR_M1_STP, &GPIO_InitStructure);

	/* Time base structure */
	TIM_TimeBaseStructure.TIM_Prescaler = 71;
	TIM_TimeBaseStructure.TIM_Period = 299;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

	/* Enable the TIM5 Update Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC1Init(TIM5, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);

	TIM5->CCR1 = 0;
	TIM5->CCR2 = 0;
	TIM5->CCR3 = 0;
	TIM5->CCR4 = 0;

	Movement_M1_MotorDriver_PWM(DISABLE);
}

/******************************************************************************/
void Movement_M1_MotorDriver_EN(POWER_LEVEL status)
{
	if(LEVEL_HIGH == status)
		GPIO_SetBits(PORT_MOTOR_M1_EN, PIN_MOTOR_M1_EN);
	else
		GPIO_ResetBits(PORT_MOTOR_M1_EN, PIN_MOTOR_M1_EN);
}

/******************************************************************************/
void Movement_M1_MotorDriver_DIR(MOTOR_DIR dir)
{
	if (DIR_CCW == dir)
		GPIO_SetBits(PORT_MOTOR_M1_DIR, PIN_MOTOR_M1_DIR);
	else
		GPIO_ResetBits(PORT_MOTOR_M1_DIR, PIN_MOTOR_M1_DIR);
}

/******************************************************************************/
void Movement_M1_MotorDriver_PWM(FunctionalState status)
{
	TIM_Cmd(TIM5, status);
	TIM_CtrlPWMOutputs(TIM5, status);
}

/******************************************************************************/
void Movement_M1_Start(void)
{
	/* 50% */
	TIM5->ARR = PUMP_PRECISION_PWM_PERIOD_5ML;
	TIM5->CCR1 = TIM5->ARR / 2;
	Movement_M1_MotorDriver_EN(LEVEL_HIGH);
	Movement_M1_MotorDriver_PWM(ENABLE);
}

/******************************************************************************/
void Movement_M1_Stop(void)
{
	/* 50% */
	TIM5->CCR1 = 0;
	Movement_M1_start = FALSE;
//	Movement_M1_MotorDriver_EN(LEVEL_HIGH);
	Movement_M1_MotorDriver_PWM(DISABLE);
}

/******************************************************************************/
void Motor_TIMER2_M3_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	/* Initialize pins */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	/* EN */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M2_EN;
	GPIO_Init(PORT_MOTOR_M2_EN, &GPIO_InitStructure);
	Movement_M2_MotorDriver_EN(LEVEL_LOW);

	/* CW */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M2_DIR;
	GPIO_Init(PORT_MOTOR_M2_DIR, &GPIO_InitStructure);
	Movement_M2_MotorDriver_DIR(DIR_CCW);

	/* EN */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M3_EN;
	GPIO_Init(PORT_MOTOR_M3_EN, &GPIO_InitStructure);
	Movement_M3_MotorDriver_EN(LEVEL_LOW);

	/* CW */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M3_DIR;
	GPIO_Init(PORT_MOTOR_M3_DIR, &GPIO_InitStructure);
	Movement_M3_MotorDriver_DIR(DIR_CCW);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

	/* STP */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M2_STP;
	GPIO_Init(PORT_MOTOR_M2_STP, &GPIO_InitStructure);

	/* STP */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M3_STP;
	GPIO_Init(PORT_MOTOR_M3_STP, &GPIO_InitStructure);

	/* Time base structure */
	TIM_TimeBaseStructure.TIM_Prescaler = 71;
	TIM_TimeBaseStructure.TIM_Period = 299;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	/* Enable the TIM2 Update Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

	TIM2->CCR1 = 0;
	TIM2->CCR2 = 0;
	TIM2->CCR3 = 0;
	TIM2->CCR4 = 0;

	Movement_M2_MotorDriver_PWM(DISABLE);
	Movement_M3_MotorDriver_PWM(DISABLE);
}

/******************************************************************************/
void Movement_M2_MotorDriver_EN(POWER_LEVEL status)
{
	if(LEVEL_HIGH == status)
		GPIO_SetBits(PORT_MOTOR_M2_EN, PIN_MOTOR_M2_EN);
	else
		GPIO_ResetBits(PORT_MOTOR_M2_EN, PIN_MOTOR_M2_EN);
}

/******************************************************************************/
void Movement_M2_MotorDriver_DIR(MOTOR_DIR dir)
{
	if (DIR_CCW == dir)
		GPIO_SetBits(PORT_MOTOR_M2_DIR, PIN_MOTOR_M2_DIR);
	else
		GPIO_ResetBits(PORT_MOTOR_M2_DIR, PIN_MOTOR_M2_DIR);
}

/******************************************************************************/
void Movement_M2_MotorDriver_PWM(FunctionalState status)
{
	TIM_Cmd(TIM2, status);
	TIM_CtrlPWMOutputs(TIM2, status);
}

/******************************************************************************/
void Movement_M2_Start(void)
{
	/* 50% */
	TIM2->ARR = PUMP_PRECISION_PWM_PERIOD_5ML;
	TIM2->CCR2 = TIM2->ARR / 2;
	Movement_M2_MotorDriver_EN(LEVEL_HIGH);
	Movement_M2_MotorDriver_PWM(ENABLE);
}

/******************************************************************************/
void Movement_M2_Stop(void)
{
	/* 50% */
	TIM2->CCR2 = 0;
	Movement_M2_start = FALSE;
//	Movement_M2_MotorDriver_EN(LEVEL_HIGH);
	Movement_M2_MotorDriver_PWM(DISABLE);
}

/******************************************************************************/
void Movement_M3_MotorDriver_EN(POWER_LEVEL status)
{
	if(LEVEL_HIGH == status)
		GPIO_SetBits(PORT_MOTOR_M3_EN, PIN_MOTOR_M3_EN);
	else
		GPIO_ResetBits(PORT_MOTOR_M3_EN, PIN_MOTOR_M3_EN);
}

/******************************************************************************/
void Movement_M3_MotorDriver_DIR(MOTOR_DIR dir)
{
	if (DIR_CCW == dir)
		GPIO_SetBits(PORT_MOTOR_M3_DIR, PIN_MOTOR_M3_DIR);
	else
		GPIO_ResetBits(PORT_MOTOR_M3_DIR, PIN_MOTOR_M3_DIR);
}

/******************************************************************************/
void Movement_M3_MotorDriver_PWM(FunctionalState status)
{
	TIM_Cmd(TIM2, status);
	TIM_CtrlPWMOutputs(TIM2, status);
}

/******************************************************************************/
void Movement_M3_Start(void)
{
	/* 50% */
#if CH1_ENABLED
	TIM2->ARR = PUMP_PRECISION_PWM_PERIOD_1ML;
#endif

#if CH2_ENABLED
	TIM2->ARR = PUMP_PRECISION_PWM_PERIOD_5ML;
#endif

	TIM2->CCR3 = TIM2->ARR / 2;
	Movement_M3_MotorDriver_EN(LEVEL_HIGH);
	Movement_M3_MotorDriver_PWM(ENABLE);
}

/******************************************************************************/
void Movement_M3_Stop(void)
{
	/* 50% */
	TIM2->CCR3 = 0;
	Movement_M3_start = FALSE;
//	Movement_M3_MotorDriver_EN(LEVEL_HIGH);
	Movement_M3_MotorDriver_PWM(DISABLE);
}

/******************************************************************************/
void Motor_TIMER4_M4_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	GPIO_PinRemapConfig(GPIO_Remap_TIM4,ENABLE);

	/* Initialize pins */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	/* EN */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M4_EN;
	GPIO_Init(PORT_MOTOR_M4_EN, &GPIO_InitStructure);
	Movement_M4_MotorDriver_EN(LEVEL_LOW);

	/* CW */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M4_DIR;
	GPIO_Init(PORT_MOTOR_M4_DIR, &GPIO_InitStructure);
	Movement_M4_MotorDriver_DIR(DIR_CCW);

	/* EN */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M5_EN;
	GPIO_Init(PORT_MOTOR_M5_EN, &GPIO_InitStructure);
	Movement_M5_MotorDriver_EN(LEVEL_LOW);

	/* CW */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M5_DIR;
	GPIO_Init(PORT_MOTOR_M5_DIR, &GPIO_InitStructure);
	Movement_M5_MotorDriver_DIR(DIR_CCW);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

	/* STP */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M4_STP;
	GPIO_Init(PORT_MOTOR_M4_STP, &GPIO_InitStructure);

	/* STP */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M5_STP;
	GPIO_Init(PORT_MOTOR_M5_STP, &GPIO_InitStructure);

	  /* Time base structure */
	TIM_TimeBaseStructure.TIM_Prescaler = 71;
	TIM_TimeBaseStructure.TIM_Period = 9999;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	/* Enable the TIM4 Update Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

	TIM4->CCR1 = 0;
	TIM4->CCR2 = 0;
	TIM4->CCR3 = 0;
	TIM4->CCR4 = 0;

	Movement_M4_MotorDriver_PWM(DISABLE);
	Movement_M5_MotorDriver_PWM(DISABLE);
}

/******************************************************************************/
void Movement_M4_MotorDriver_EN(POWER_LEVEL status)
{
	if(LEVEL_HIGH == status)
		GPIO_SetBits(PORT_MOTOR_M4_EN, PIN_MOTOR_M4_EN);
	else
		GPIO_ResetBits(PORT_MOTOR_M4_EN, PIN_MOTOR_M4_EN);
}

/******************************************************************************/
void Movement_M4_MotorDriver_DIR(MOTOR_DIR dir)
{
	if (DIR_CCW == dir)
		GPIO_SetBits(PORT_MOTOR_M4_DIR, PIN_MOTOR_M4_DIR);
	else
		GPIO_ResetBits(PORT_MOTOR_M4_DIR, PIN_MOTOR_M4_DIR);
}

/******************************************************************************/
void Movement_M4_MotorDriver_PWM(FunctionalState status)
{
	TIM_Cmd(TIM4, status);
	TIM_CtrlPWMOutputs(TIM4, status);
}

/******************************************************************************/
void Movement_M4_Start(void)
{
	/* 50% */
	TIM4->ARR = PUMP_PRECISION_PWM_PERIOD_5ML;
	TIM4->CCR3 = TIM4->ARR / 2;
	Movement_M4_MotorDriver_EN(LEVEL_HIGH);
	Movement_M4_MotorDriver_PWM(ENABLE);
}

/******************************************************************************/
void Movement_M4_Stop(void)
{
	/* 50% */
	TIM4->CCR3 = 0;
	Movement_M4_start = FALSE;
//	Movement_M4_MotorDriver_EN(LEVEL_HIGH);
	Movement_M4_MotorDriver_PWM(DISABLE);
}

/******************************************************************************/
void Movement_M5_MotorDriver_EN(POWER_LEVEL status)
{
	if(LEVEL_HIGH == status)
		GPIO_SetBits(PORT_MOTOR_M5_EN, PIN_MOTOR_M5_EN);
	else
		GPIO_ResetBits(PORT_MOTOR_M5_EN, PIN_MOTOR_M5_EN);
}

/******************************************************************************/
void Movement_M5_MotorDriver_DIR(MOTOR_DIR dir)
{
	if (DIR_CCW == dir)
		GPIO_SetBits(PORT_MOTOR_M5_DIR, PIN_MOTOR_M5_DIR);
	else
		GPIO_ResetBits(PORT_MOTOR_M5_DIR, PIN_MOTOR_M5_DIR);
}

/******************************************************************************/
void Movement_M5_MotorDriver_PWM(FunctionalState status)
{
	TIM_Cmd(TIM4, status);
	TIM_CtrlPWMOutputs(TIM4, status);
}

/******************************************************************************/
void Movement_M5_Start(void)
{
	/* 50% */
	TIM4->ARR = PUMP_PRECISION_PWM_PERIOD_1ML;
	TIM4->CCR4 = TIM4->ARR / 2;
	Movement_M5_MotorDriver_EN(LEVEL_HIGH);
	Movement_M5_MotorDriver_PWM(ENABLE);
}

/******************************************************************************/
void Movement_M5_Stop(void)
{
	/* 50% */
	TIM4->CCR4 = 0;
	Movement_M5_start = FALSE;
//	Movement_M5_MotorDriver_EN(LEVEL_HIGH);
	Movement_M5_MotorDriver_PWM(DISABLE);
}

/******************************************************************************/
void Motor_TIMER3_M6_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* TIM3_CH1 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	/* Initialize pins */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	/* EN */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M6_EN;
	GPIO_Init(PORT_MOTOR_M6_EN, &GPIO_InitStructure);
	Movement_M6_MotorDriver_EN(LEVEL_LOW);

	/* CW */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M6_DIR;
	GPIO_Init(PORT_MOTOR_M6_DIR, &GPIO_InitStructure);
	Movement_M6_MotorDriver_DIR(DIR_CW);

	/* EN */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M7_EN;
	GPIO_Init(PORT_MOTOR_M7_EN, &GPIO_InitStructure);
	Movement_M7_MotorDriver_EN(LEVEL_LOW);

	/* CW */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M7_DIR;
	GPIO_Init(PORT_MOTOR_M7_DIR, &GPIO_InitStructure);
	Movement_M7_MotorDriver_DIR(DIR_CCW);

	/* EN */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M8_EN;
	GPIO_Init(PORT_MOTOR_M8_EN, &GPIO_InitStructure);
	Movement_M8_MotorDriver_EN(LEVEL_LOW);

	/* CW */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M8_DIR;
	GPIO_Init(PORT_MOTOR_M8_DIR, &GPIO_InitStructure);
	Movement_M8_MotorDriver_DIR(DIR_CCW);

	/* EN */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M9_EN;
	GPIO_Init(PORT_MOTOR_M9_EN, &GPIO_InitStructure);
	Movement_M9_MotorDriver_EN(LEVEL_LOW);

	/* CW */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M9_DIR;
	GPIO_Init(PORT_MOTOR_M9_DIR, &GPIO_InitStructure);
	Movement_M9_MotorDriver_DIR(DIR_CCW);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

	/* STP */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M6_STP;
	GPIO_Init(PORT_MOTOR_M6_STP, &GPIO_InitStructure);

	/* STP */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M7_STP;
	GPIO_Init(PORT_MOTOR_M7_STP, &GPIO_InitStructure);

	/* STP */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M8_STP;
	GPIO_Init(PORT_MOTOR_M8_STP, &GPIO_InitStructure);

	/* STP */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M9_STP;
	GPIO_Init(PORT_MOTOR_M9_STP, &GPIO_InitStructure);

	/* Time base structure */
	TIM_TimeBaseStructure.TIM_Prescaler = 71;
	TIM_TimeBaseStructure.TIM_Period = 9999;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* Enable the TIM3 Update Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

	TIM3->CCR1 = 0;
	TIM3->CCR2 = 0;
	TIM3->CCR3 = 0;
	TIM3->CCR4 = 0;

	Movement_M6_MotorDriver_PWM(DISABLE);
	Movement_M7_MotorDriver_PWM(DISABLE);
	Movement_M8_MotorDriver_PWM(DISABLE);
	Movement_M9_MotorDriver_PWM(DISABLE);
}

/******************************************************************************/
void Movement_M6_MotorDriver_EN(POWER_LEVEL status)
{
	if(LEVEL_HIGH == status)
		GPIO_SetBits(PORT_MOTOR_M6_EN, PIN_MOTOR_M6_EN);
	else
		GPIO_ResetBits(PORT_MOTOR_M6_EN, PIN_MOTOR_M6_EN);
}

/******************************************************************************/
void Movement_M6_MotorDriver_DIR(MOTOR_DIR dir)
{
	if (DIR_CCW == dir)
		GPIO_SetBits(PORT_MOTOR_M6_DIR, PIN_MOTOR_M6_DIR);
	else
		GPIO_ResetBits(PORT_MOTOR_M6_DIR, PIN_MOTOR_M6_DIR);
}

/******************************************************************************/
void Movement_M6_MotorDriver_PWM(FunctionalState status)
{
	TIM_Cmd(TIM3, status);
	TIM_CtrlPWMOutputs(TIM3, status);
}

/******************************************************************************/
void Movement_M6_Start(void)
{
	/* 50% */
	TIM3->ARR = PUMP_PRECISION_PWM_PERIOD_5ML;
	TIM3->CCR1 = TIM3->ARR / 2;
	Movement_M6_MotorDriver_EN(LEVEL_HIGH);
	Movement_M6_MotorDriver_PWM(ENABLE);
}

/******************************************************************************/
void Movement_M6_Stop(void)
{
	/* 50% */
	TIM3->CCR1 = 0;
	Movement_M6_start = FALSE;
//	Movement_M6_MotorDriver_EN(LEVEL_HIGH);
	Movement_M6_MotorDriver_PWM(DISABLE);
}

/******************************************************************************/
void Movement_M7_MotorDriver_EN(POWER_LEVEL status)
{
	if(LEVEL_HIGH == status)
		GPIO_SetBits(PORT_MOTOR_M7_EN, PIN_MOTOR_M7_EN);
	else
		GPIO_ResetBits(PORT_MOTOR_M7_EN, PIN_MOTOR_M7_EN);
}

/******************************************************************************/
void Movement_M7_MotorDriver_DIR(MOTOR_DIR dir)
{
	if (DIR_CCW == dir)
		GPIO_SetBits(PORT_MOTOR_M7_DIR, PIN_MOTOR_M7_DIR);
	else
		GPIO_ResetBits(PORT_MOTOR_M7_DIR, PIN_MOTOR_M7_DIR);
}

/******************************************************************************/
void Movement_M7_MotorDriver_PWM(FunctionalState status)
{
	TIM_Cmd(TIM3, status);
	TIM_CtrlPWMOutputs(TIM3, status);
}

/******************************************************************************/
void Movement_M7_Start(void)
{
	/* 50% */
	TIM3->ARR = 1800;
	TIM3->CCR2 = TIM3->ARR / 2;
	Movement_M7_MotorDriver_EN(LEVEL_HIGH);
	Movement_M7_MotorDriver_PWM(ENABLE);
}

/******************************************************************************/
void Movement_M7_Stop(void)
{
	/* 50% */
	TIM3->CCR2 = 0;
	Movement_M7_start = FALSE;
//	Movement_M7_MotorDriver_EN(LEVEL_HIGH);
	Movement_M7_MotorDriver_PWM(DISABLE);
}

/******************************************************************************/
void Movement_M8_MotorDriver_EN(POWER_LEVEL status)
{
	if(LEVEL_HIGH == status)
		GPIO_SetBits(PORT_MOTOR_M8_EN, PIN_MOTOR_M8_EN);
	else
		GPIO_ResetBits(PORT_MOTOR_M8_EN, PIN_MOTOR_M8_EN);
}

/******************************************************************************/
void Movement_M8_MotorDriver_DIR(MOTOR_DIR dir)
{
	if (DIR_CCW == dir)
		GPIO_SetBits(PORT_MOTOR_M8_DIR, PIN_MOTOR_M8_DIR);
	else
		GPIO_ResetBits(PORT_MOTOR_M8_DIR, PIN_MOTOR_M8_DIR);
}

/******************************************************************************/
void Movement_M8_MotorDriver_PWM(FunctionalState status)
{
	TIM_Cmd(TIM3, status);
	TIM_CtrlPWMOutputs(TIM3, status);
}

/******************************************************************************/
void Movement_M8_Start(void)
{
	/* 50% */
	TIM3->ARR = PUMP_PRECISION_PWM_PERIOD_5ML;
	TIM3->CCR3 = TIM3->ARR / 2;
	Movement_M8_MotorDriver_EN(LEVEL_HIGH);
	Movement_M8_MotorDriver_PWM(ENABLE);
}

/******************************************************************************/
void Movement_M8_Stop(void)
{
	/* 50% */
	TIM3->CCR3 = 0;
	Movement_M8_start = FALSE;
//	Movement_M8_MotorDriver_EN(LEVEL_HIGH);
	Movement_M8_MotorDriver_PWM(DISABLE);
}

/******************************************************************************/
void Movement_M9_MotorDriver_EN(POWER_LEVEL status)
{
	if(LEVEL_HIGH == status)
		GPIO_SetBits(PORT_MOTOR_M9_EN, PIN_MOTOR_M9_EN);
	else
		GPIO_ResetBits(PORT_MOTOR_M9_EN, PIN_MOTOR_M9_EN);
}

/******************************************************************************/
void Movement_M9_MotorDriver_DIR(MOTOR_DIR dir)
{
	if (DIR_CCW == dir)
		GPIO_SetBits(PORT_MOTOR_M9_DIR, PIN_MOTOR_M9_DIR);
	else
		GPIO_ResetBits(PORT_MOTOR_M9_DIR, PIN_MOTOR_M9_DIR);
}

/******************************************************************************/
void Movement_M9_MotorDriver_PWM(FunctionalState status)
{
	TIM_Cmd(TIM3, status);
	TIM_CtrlPWMOutputs(TIM3, status);
}

/******************************************************************************/
void Movement_M9_Start(void)
{
	/* 50% */
	TIM3->ARR = 1800;
	TIM3->CCR4 = TIM3->ARR / 2;
	Movement_M9_MotorDriver_EN(LEVEL_HIGH);
	Movement_M9_MotorDriver_PWM(ENABLE);
}

/******************************************************************************/
void Movement_M9_Stop(void)
{
	/* 50% */
	TIM3->CCR4 = 0;
	Movement_M9_start = FALSE;
//	Movement_M9_MotorDriver_EN(LEVEL_HIGH);
	Movement_M9_MotorDriver_PWM(DISABLE);
}

/******************************************************************************/
void Motor_TIMER1_M10_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD,ENABLE);
	/* Initialize pins */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	/* EN */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M10_EN;
	GPIO_Init(PORT_MOTOR_M10_EN, &GPIO_InitStructure);
	Movement_M10_MotorDriver_EN(LEVEL_LOW);

	/* CW */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M10_DIR;
	GPIO_Init(PORT_MOTOR_M10_DIR, &GPIO_InitStructure);
	Movement_M10_MotorDriver_DIR(DIR_CCW);

	/* TIM1_CH1 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	/* CLK */
	GPIO_InitStructure.GPIO_Pin = PIN_MOTOR_M10_STP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(PORT_MOTOR_M10_STP, &GPIO_InitStructure);

	/* Time base structure */
	TIM_TimeBaseStructure.TIM_Prescaler = 71;
	TIM_TimeBaseStructure.TIM_Period = 299;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	/* Enable the TIM8 Update Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

	TIM1->CCR1 = 0;
	TIM1->CCR2 = 0;
	TIM1->CCR3 = 0;
	TIM1->CCR4 = 0;

	Movement_M10_MotorDriver_PWM(DISABLE);
}

/******************************************************************************/
void Movement_M10_MotorDriver_EN(POWER_LEVEL status)
{
	if(LEVEL_HIGH == status)
		GPIO_SetBits(PORT_MOTOR_M10_EN, PIN_MOTOR_M10_EN);
	else
		GPIO_ResetBits(PORT_MOTOR_M10_EN, PIN_MOTOR_M10_EN);
}

/******************************************************************************/
void Movement_M10_MotorDriver_DIR(MOTOR_DIR dir)
{
	if (DIR_CCW == dir)
		GPIO_SetBits(PORT_MOTOR_M10_DIR, PIN_MOTOR_M10_DIR);
	else
		GPIO_ResetBits(PORT_MOTOR_M10_DIR, PIN_MOTOR_M10_DIR);
}

/******************************************************************************/
void Movement_M10_MotorDriver_PWM(FunctionalState status)
{
	TIM_Cmd(TIM1, status);
	TIM_CtrlPWMOutputs(TIM1, status);
}

/******************************************************************************/
void Movement_M10_Start(void)
{
	/* 50% */
	TIM1->ARR = PUMP_PRECISION_PWM_PERIOD_1ML;
	TIM1->CCR1 = TIM1->ARR / 2;
	Movement_M10_MotorDriver_EN(LEVEL_HIGH);
	Movement_M10_MotorDriver_PWM(ENABLE);
}

/******************************************************************************/
void Movement_M10_Stop(void)
{
	/* 50% */
	TIM1->CCR1 = 0;
	Movement_M10_start = FALSE;
//	Movement_M10_MotorDriver_EN(LEVEL_HIGH);
	Movement_M10_MotorDriver_PWM(DISABLE);
}

/******************************************************************************/
void TIM1_UP_IRQHandler (void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
	{
		/* 泵1电机运动步数计数  */
		if(Movement_M10_start)
		{
			Movement_M10_pulseCount++;

			/* Move specified steps */
			if ((Movement_M10_pulseCount >= Movement_M10_pulseNumber))
			{
				Movement_M10_Stop();

				/* Clear flags */
				Movement_M10_pulseCount = 0;
				Movement_M10_start = FALSE;
			}
		}
		/* Clear the interrupt pending flag */
		TIM_ClearFlag(TIM1, TIM_FLAG_Update);
	}
}

/******************************************************************************/
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		/* 泵3电机运动步数计数  */
		if(Movement_M3_start)
		{
			Movement_M3_pulseCount++;

			/* Move specified steps */
			if ((Movement_M3_pulseCount >= Movement_M3_pulseNumber))
			{
				Movement_M3_Stop();

				/* Clear flags */
				Movement_M3_pulseCount = 0;
				Movement_M3_start = FALSE;
			}
		}
		/* Clear the interrupt pending flag */
		TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	}
}

/******************************************************************************/
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		/* 泵6电机运动步数计数  */
		if(Movement_M6_start)
		{
			Movement_M6_pulseCount++;

			/* Move specified steps */
			if ((Movement_M6_pulseCount >= Movement_M6_pulseNumber))
			{
				Movement_M6_Stop();

				/* Clear flags */
				Movement_M6_pulseCount = 0;
				Movement_M6_start = FALSE;
			}
		}

		/* Clear the interrupt pending flag */
		TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	}
}

/******************************************************************************/
void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		/* 泵4电机运动步数计数  */
		if(Movement_M4_start)
		{
			Movement_M4_pulseCount++;

			/* Move specified steps */
			if ((Movement_M4_pulseCount >= Movement_M4_pulseNumber))
			{
				Movement_M4_Stop();

				/* Clear flags */
				Movement_M4_pulseCount = 0;
				Movement_M4_start = FALSE;
			}
		}

		/* Clear the interrupt pending flag */
		TIM_ClearFlag(TIM4, TIM_FLAG_Update);
	}
}

/******************************************************************************/
void TIM5_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
	{
		/* 泵1电机运动步数计数  */
		if(Movement_M1_start)
		{
			Movement_M1_pulseCount++;

			/* Move specified steps */
			if ((Movement_M1_pulseCount >= Movement_M1_pulseNumber))
			{
				Movement_M1_Stop();

				/* Clear flags */
				Movement_M1_pulseCount = 0;
				Movement_M1_start = FALSE;
			}
		}

		/* Clear the interrupt pending flag */
		TIM_ClearFlag(TIM5, TIM_FLAG_Update);
	}
}
