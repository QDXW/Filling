#include "Temp.h"
#include "thermistor.h"

/******************************************************************************/
void Temp_1_2_Pwm_Init(void);
void Temp_3_Pwm_Init(void);

/******************************************************************************/
void Temp_1_2_Pwm_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
	
	 /* CLK */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	/* HOT1 */
	GPIO_InitStructure.GPIO_Pin = PIN_TEMP_HEAT_CTR_1;	
	GPIO_Init(PORT_TEMP_HEAT_CTR_1, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_TEMP_HEAT_CTR_1, PIN_TEMP_HEAT_CTR_1);

	/* HOT2 */ 
	GPIO_InitStructure.GPIO_Pin = PIN_TEMP_HEAT_CTR_2;
	GPIO_Init(PORT_TEMP_HEAT_CTR_2, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_TEMP_HEAT_CTR_2, PIN_TEMP_HEAT_CTR_2);

	  /* Time base structure */
	TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;
	TIM_TimeBaseStructure.TIM_Period = 99;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	TIM_CtrlPWMOutputs(TIM3, ENABLE);	
	TIM_Cmd(TIM3, ENABLE); 
}

/******************************************************************************/
void Temp_3_Pwm_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	 /* CLK */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	/* HOT3 */
	GPIO_InitStructure.GPIO_Pin = PIN_TEMP_HEAT_CTR_3;
	GPIO_Init(PORT_TEMP_HEAT_CTR_3, &GPIO_InitStructure);
	GPIO_SetBits(PORT_TEMP_HEAT_CTR_3, PIN_TEMP_HEAT_CTR_3);
	
	  /* Time base structure */
	TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;
	TIM_TimeBaseStructure.TIM_Period = 99;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM2, ENABLE);
	TIM_CtrlPWMOutputs(TIM2, ENABLE);
}

/******************************************************************************/
void TempPwm_Init(void)
{
	Temp_1_2_Pwm_Init();
	Temp_3_Pwm_Init();
	ClearAllpwmValue();
}

/******************************************************************************/
void SetpwmValue(uint8 ch, uint16 pwmvalue)
{
   switch(ch)
	{
		case 1:
			TIM3->CCR2 = pwmvalue;
			break;
		case 2:
			TIM3->CCR1 = pwmvalue;
			break;
		case 3:
			TIM2->CCR2 = pwmvalue;
			break;	
	}
}

/******************************************************************************/
float Get_Temp_Average(uint8 condition)
{
	float temp,temp1, temp2, temp3;
	switch(condition)
	{
		case 1:
			ADC_DMA_StartConversion_1_times();
			temp1 = Get_50Adc_DMA_10Average(Receive_ADC_Buffer, 0);
			temp1 = analog2temp_thermistor(temp1, temptable, NUMTEMPS);
			temp = temp1;
			Temper_HOT1 = temp1;
			break;

		case 2:
			temp2 = Get_50Adc_DMA_10Average(Receive_ADC_Buffer, 1);
			temp2 = analog2temp_thermistor(temp2, temptable, NUMTEMPS);
			temp = temp2;
			Temper_HOT2= temp2;
			break;

		case 3:
			temp3 = Get_50Adc_DMA_10Average(Receive_ADC_Buffer, 2);
			temp3 = analog2temp_thermistor(temp3, temptable, NUMTEMPS);
			temp = temp3;
			break;

		default:
			break;
	}

	return temp;
}

/******************************************************************************/
float analog2temp_thermistor(int raw,const float table[][2], int numtemps) 
{
    float celsius = 0.0;
	  float R_value;
    char i;
	
    /* R_thermistor = R_resistor * Get_Adc /(2^12 - Get_Adc) */
		R_value = ((float)raw  * 2.478 / 4096) * 87.428 - 0.349;
//		R_value=((float)raw * 2.48 / 4096 *  2400)/ (11 * 2.93);
//    R_value = (float)(RESISTOR * raw) / (float)(4096 - raw);
    for (i=1; i<numtemps; i++)
    {
      if (table[i][0] < R_value)
      {
        celsius  = table[i-1][1] + 
          (R_value - table[i-1][0]) * 
          (table[i][1] - table[i-1][1]) /
          (table[i][0] - table[i-1][0]) ;

        break;
      }
    }

    /* Overflow: Set to last value in the table */
    if (i == numtemps) celsius = table[i-1][1];

    return celsius;
}

/******************************************************************************/
void ClearAllpwmValue(void)
{ 
	SetpwmValue(HOT1, 0);
	SetpwmValue(HOT2, 0);
	SetpwmValue(HOT3, 0);
}

/******************************************************************************/
void Temp_Monitor (void)
{
	switch(Temp_Count)
	{
		case 0:
			/* 关闭加热1 */
			SetpwmValue(HOT1,0);

			/* 关闭加热 */
			SetpwmValue(HOT2,0);
		break;

		case 1:
			/* 关闭加热2 */
			SetpwmValue(HOT2,0);

			if(Temper_HOT1 > Control_Temperature)
			{
				/* 关闭加热 1 */
				SetpwmValue(HOT1,0);
			}
			else
			{
				if(Temp_Switch  & 0x01)
				{
					/* 四分之一功率加热 */
					SetpwmValue(HOT1,25);
				}
			}
			break;

		case 2:
			/* 关闭加热 1*/
			SetpwmValue(HOT1,0);

			if(Temper_HOT2 > Control_Temperature)
			{
				/* 关闭加热2 */
				SetpwmValue(HOT2,0);
			}
			else
			{
				if(Temp_Switch  & 0x02)
				{
					/* 四分之一功率加热 */
					SetpwmValue(HOT2,25);
				}
			}
			break;

		case 3:
			if(Temper_HOT1 > Control_Temperature)
			{
				/* 关闭加热 */
				SetpwmValue(HOT1,0);
			}
			else
			{
				if(Temp_Switch  & 0x01)
				{
					/* 四分之一功率加热 */
					SetpwmValue(HOT1,25);
				}
			}

			if(Temper_HOT2 > Control_Temperature)
			{
				/* 关闭加热 */
				SetpwmValue(HOT2,0);
			}
			else
			{
				if(Temp_Switch  & 0x02)
				{
					/* 四分之一功率加热 */
					SetpwmValue(HOT2,25);
				}
			}
			break;
		default:
			break;
	}
}
