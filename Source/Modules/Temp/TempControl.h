#ifndef SOURCE_MODULES_TEMPCONTROL_H_
#define SOURCE_MODULES_TEMPCONTROL_H_

/******************************************************************************/
#include "Project_File.h"

/***********************************************************************/
#define INITIAL_TEMP	180.0

/***********************************************************************/
extern uint32 millis;

/***********************************************************************/
void TempControl_Init(void);
float PIDAutoRegulation(u8 ch,float setTemp);
void PIDAutoRegulation_Init(void);
void TempControl_Process(void);


#endif
