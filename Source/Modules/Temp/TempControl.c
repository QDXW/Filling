#include "TempControl.h"
#include "adc.h"
#include "Temp.h"
#include "dma.h"
#include "math.h"
#include "Common.h"
#include "string.h"
#include <stdio.h>

/***********************************************************************/
PID_InitTypeDef pid;
uint32 millis = 0;
uint32 tempTime;

/***********************************************************************/
#define TEMP_PWM_DUTY_CYCLE_MIN   (10)
#define TEMP_PWM_DUTY_CYCLE_MAX   (90)

/***********************************************************************/
void TempControl_Init(void)
{
		ADC_DMA_Init();
		
		adc_Init();
	
		/* Temperature PWM Control */
		TempPwm_Init();
		
		PIDAutoRegulation_Init();
}

/***********************************************************************/
void TempControl_Process(void)
{
  	if(millis - tempTime > pid.timeInterval)
	{
		tempTime = millis;
		
		/* DMA : Start Conversion ::: 50 data * 5 channel  */
		ADC_DMA_StartConversion_1_times();
		PIDAutoRegulation(1,185.0);
		/* Setting Temperature */
	}	
}

/***********************************************************************/
float PIDAutoRegulation(u8 ch,float setTemp)
{ 
	pid.setTemp = setTemp;	
	pid.curTemp = Get_Temp_Average(ch);	
	pid.err = pid.setTemp - pid.curTemp;
	if(pid.curTemp > pid.maxTemp)
	{	
		pid.integral = 0;
		pid.err = 0;
		pid.err_last = 0;		
		pid.pwmValue = 0;
	}
	else if(pid.curTemp < pid.minTemp || pid.err < 0)
	{
		pid.integral = 0;
		pid.err = 0;
		pid.err_last = 0;	
		pid.pwmValue = 0;		
	}	
	else if(pid.err > pid.kiSeparate)
	{
	   pid.pwmValue = pid.Kp * pid.err;
	}
	else   /* 5 */
	{
		pid.integral += pid.err;
		if(pid.integral > 3)pid.integral = 3;
		if(pid.integral < -3)pid.integral = -3;
		
		/* PID Control */
		(fabs(pid.err) < pid.deadZone) ?  /* PD £º0.28 */			
			(pid.pwmValue = pid.Kp * pid.err + pid.Kd * (pid.err - pid.err_last)): 	
			(pid.pwmValue = pid.Kp * pid.err + pid.Ki * pid.integral +
						pid.Kd * (pid.err - pid.err_last));
	}	
	pid.err_last = pid.err;
	pid.pwmValue = pid.pwmValue * 1.0;

	if(pid.pwmValue > TEMP_PWM_DUTY_CYCLE_MAX) pid.pwmValue = TEMP_PWM_DUTY_CYCLE_MAX;
	if(pid.pwmValue < TEMP_PWM_DUTY_CYCLE_MIN) pid.pwmValue = TEMP_PWM_DUTY_CYCLE_MIN;
  printf("pid.pwmValue = %0.2f,pid.curTemp = %0.2f,pid.err = %0.2f\n",pid.pwmValue,pid.curTemp,pid.err);

	SetpwmValue(ch, pid.pwmValue);
   return pid.pwmValue;		
		
}

/***********************************************************************/
void PIDAutoRegulation_Init(void)
{
	pid.curTemp = 0.0;
	pid.setTemp = 0;
	pid.err = 0.0;
	pid.err_last = 0.0;
	pid.pwmValue = 0.0;
	pid.integral = 0.0;

	pid.Kp = 5;    
	pid.Ki = 15;  
	pid.Kd = 20;   
	pid.maxTemp = 200;     
	pid.minTemp = 0.0;	  
	pid.kiSeparate = 5.0; 
	pid.deadZone = 0.5;
	pid.timeInterval = 2000;
}
