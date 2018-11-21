#ifndef SOURCE_MODULES_TEMP_TEMP_H
#define SOURCE_MODULES_TEMP_TEMP_H

/******************************************************************************/
#include "Project_File.h"

/***********************************************************************/
typedef struct  {
	float setTemp;
	float curTemp;
	float err;
	float err_last;
	float Kp, Ki, Kd;
	float pwmValue;
	float integral;
	float maxTemp;
	float minTemp;
	float kiSeparate;
	float deadZone;      /* 4 Byte */
	uint16 timeInterval; /* 2 Byte */
} PID_InitTypeDef;

/******************************************************************************/
extern PID_InitTypeDef   pid;

/***********************************************************************/
typedef enum
{
	TEMP1_BUF,
	TEMP2_BUF,
	TEMP3_BUF,
} TEMP_ADC_BUFFER;

/***********************************************************************/
#define PORT_TEMP_HEAT_CTR_1   (GPIOB)
#define PIN_TEMP_HEAT_CTR_1    (GPIO_Pin_5)
#define PORT_TEMP_HEAT_CTR_2   (GPIOB)
#define PIN_TEMP_HEAT_CTR_2    (GPIO_Pin_4)
#define PORT_TEMP_HEAT_CTR_3   (GPIOB)
#define PIN_TEMP_HEAT_CTR_3    (GPIO_Pin_3)

/***********************************************************************/
extern void TempPwm_Init(void);
extern void SetpwmValue(uint8 ch, uint16 pwmvalue);
extern void ClearAllpwmValue(void);
extern void TestPwmValue(void);
extern float Get_Temp_Average(uint8 condition);
extern float analog2temp_thermistor(int raw,const float table[][2], int numtemps);
extern void PIDAutoRegulation_Init(void);
extern void Temp_Monitor (void);


#endif

