#ifndef SOURCE_MODULES_SENSOR_SENSOR_H_
#define SOURCE_MODULES_SENSOR_SENSOR_H_

/******************************************************************************/
#include "Project_File.h"

/******************************************************************************/
typedef struct
{
	 uint8 PlaceLumpSR;				//放置块标志位
	 uint8 FillingPosSR;
	 uint8 GotoHeatPosSR;
	 uint8 CurrentHeatSR;
	 uint8 ConpactionPosSR;			//再次压紧
	 uint8 IncisePosSR;
	 uint8 InciseFinishSR;
   uint8 TrunPosSR;	
	 uint8 VibratingDiskSR;
}FLAG;

/******************************************************************************/
typedef enum
{
	 SWITCH1=1,
	 SWITCH2,				
	 SWITCH3,				
	 SWITCH4,				
	 SWITCH5,				
	 SWITCH6,				
	 SWITCH7,				
	 SWITCH8,				
	 SWITCH9,				
	 SWITCH10,			
	 SWITCH11,			
	 SWITCH12,			
	 SWITCH13,			
	 SWITCH14,			
	 SWITCH15,			 		
}SWITCH_NUM;

/******************************************************************************/
extern SWITCH_NUM Switch;
extern FLAG ExitFlag;

/******************************************************************************/
void PosSensor_Init(void);
uint8 Pos_Read_Sensor(SWITCH_NUM Switch);


#endif
