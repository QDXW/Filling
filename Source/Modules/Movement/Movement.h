#ifndef SOURCE_MODULES_MOVEMENT_MOVEMENT_H
#define SOURCE_MODULES_MOVEMENT_MOVEMENT_H

/******************************************************************************/
#include "Project_File.h"

/******************************************************************************/
typedef struct
{
	 uint8 PlaceLump_Flag;			//加个标志位，防止检测有无放置块放下中断被误触发
	 uint8 FillingPos_Flag;			//加个标志位，防止检测到达灌装位置中断被误触发
	 uint8 GotoHeatPos_Flag;		//加个标志位，防止检测到加热位置被误触发
	 uint8 CurrentHeatPos_Flag;	//加个标志位，防止检测到加热位置被误触发
	 uint8 ConpactionPos_Flag;	//加个标志位，防止检测到再次压紧被误触发
	 uint8 IncisePos_Flag;			//加个标志位，防止检测切割被误触发
	 uint8 InciseFinish_Flag;		
	 uint8 TrunPos_Flag;
	 uint8 VibratingDisk_Flag;
}CHECK;

/******************************************************************************/
extern CHECK Check;

/******************************************************************************/
void Movement_Process(void);
void PlaceLump_Action(void);
void Filling_Action(void);
void GotoHeat_Action(void);
void Heat_Action(void);
void Conpaction_Action(void);
void Incise_Action(void);
void InciseFinish_Action(void);
void Trun_Action(void);
void VibratingDisk_Action(void);


#endif
