#include "Laminating.h"
#include "devices.h"
#include "HostProcess.h"

void Laminating_Process(void)
{
	if(Laminating.PumpControlSR == TRUE)
	{
		DIAP_PUMP_Control((DIAP_PUMP_NUM)HostComm_UartRx.validBuf[OFFSET_CMD_DATA],(FunctionalState)HostComm_UartRx.validBuf[OFFSET_CMD_DATA + 1]);
		Laminating.PumpControlSR = FALSE;
	}	
}



