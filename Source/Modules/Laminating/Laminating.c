#include "Laminating.h"
#include "devices.h"
#include "HostProcess.h"

void Laminating_Process(void)
{
	if(Laminating.PumpControlSR == TRUE)
	{
		Pump_Control((PUMP_NUM)HostComm_UartRx.validBuf[OFFSET_CMD_DATA],(FunctionalState)HostComm_UartRx.validBuf[OFFSET_CMD_DATA + 1]);
		Laminating.PumpControlSR = FALSE;
	}	
}



