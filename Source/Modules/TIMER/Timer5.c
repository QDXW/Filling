/*
 * Timer5.c
 *
 *  Created on: 2018��4��11��
 *      Author: Administrator
 */

/******************************************************************************/
#include "Timer5.h"

/******************************************************************************/
void TIM6_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);			//ʱ��ʹ��

	//��ʱ��TIM6��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; 						//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 						//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 		//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); 				//����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE ); 						//ʹ��ָ����TIM5�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  				//TIM5�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  		//��ռ���ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  			//�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  								//��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM6, ENABLE);  //ʹ��TIMx
}
