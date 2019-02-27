/*
 * Device_Action.h
 *
 *  Created on: 2018Äê11ÔÂ5ÈÕ
 *      Author: Administrator
 */

#ifndef MODULES_DEVICES_DEVICE_ACTION_H_
#define MODULES_DEVICES_DEVICE_ACTION_H_

/******************************************************************************/
#include "Project_File.h"

/******************************************************************************/
typedef enum
{
	INVALID = 0X00,
	VOLUME_R1,
	VOLUME_R2,
	VOLUME_M,
	VOLUME_W,
	VOLUME_BASE,
} PUMP_VOLUME;

/******************************************************************************/
extern void Inject_Act (void);
extern void Filling_Act (void);
extern void Infusion_Act(void);
extern void Bump_Wash_Act(void);
extern void Set_Volume(uint8 *data);

extern void Injucet_Volume_R1 (void);
extern void Injucet_Volume_R2 (void);
extern void Injucet_Volume_M (void);
extern void Injucet_Volume_W (void);
extern void Injucet_Volume_BASE (void);

#endif /* MODULES_DEVICES_DEVICE_ACTION_H_ */
