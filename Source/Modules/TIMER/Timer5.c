/*
 * Timer5.c
 *
 *  Created on: 2018年4月11日
 *      Author: Administrator
 */

/******************************************************************************/
#include "Timer5.h"

/******************************************************************************/
void TIM6_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);			//时钟使能

	//定时器TIM6初始化
	TIM_TimeBaseStructure.TIM_Period = arr; 						//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 						//设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 		//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//TIM向上计数模式
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); 				//根据指定的参数初始化TIMx的时间基数单位

	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE ); 						//使能指定的TIM5中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  				//TIM5中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  		//先占优先级1级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  			//从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  								//初始化NVIC寄存器

	TIM_Cmd(TIM6, ENABLE);  //使能TIMx
}
