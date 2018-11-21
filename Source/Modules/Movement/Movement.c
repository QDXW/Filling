/******************************************************************************/
#include "Movement.h"

/******************************************************************************/
CHECK Check;

/******************************************************************************/
void Movement_Process(void)
{
	if(ExitFlag.PlaceLumpSR == TRUE)
	{
		ExitFlag.PlaceLumpSR = FALSE;
		PlaceLump_Action();
	}
	else if(ExitFlag.FillingPosSR == TRUE)
	{
		ExitFlag.FillingPosSR = FALSE;
		Filling_Action();
	}
	else if(ExitFlag.GotoHeatPosSR == TRUE)
	{
		ExitFlag.GotoHeatPosSR = FALSE;
		GotoHeat_Action();
	}
	else if(ExitFlag.CurrentHeatSR == TRUE)
	{
		Heat_Action();
	}
	else if(ExitFlag.ConpactionPosSR == TRUE)
	{
		Conpaction_Action();
	}
	else if(ExitFlag.IncisePosSR == TRUE)
	{
		Incise_Action();
	}
	else if(ExitFlag.InciseFinishSR == TRUE)
	{
		ExitFlag.InciseFinishSR = FALSE;
		InciseFinish_Action();
	}
	else if(ExitFlag.TrunPosSR == TRUE)
	{
		ExitFlag.TrunPosSR = FALSE;
		Trun_Action();
	}
	else if(ExitFlag.VibratingDiskSR == TRUE)
	{
		ExitFlag.VibratingDiskSR = FALSE;
		Trun_Action();
	}
}

/******************************************************************************/
/*有放置块放下*/
void PlaceLump_Action(void)
{		
/*开启气泵,将放置块推入到灌装位置，等待传感器触发*/
//	Pump_Control(PUMP1，DISABLE)		//禁止控制放置块后退的运动
//	Pump_Control(PUMP2，ENABLE)			//开始控制放置块向前的运动
}

/******************************************************************************/
/*放置块到达灌装位置，灌装*/
void Filling_Action(void)
{
	/*每次动作前都要结束上一个动作的所有事情*/
//	Pump_Control(PUMP2，DISABLE)		//禁止控制放置块向前的运动
//	Pump_Control(PUMP1，ENABLE)			//开始控制放置块后退的禁止

	//检查具有试剂条的通道
	//将其发送给运动板
	//运动板执行灌装，灌装完成后回复
	//采用Can中断，记得将灌装标志位改变
	//等待运动板回复之后，前往加热位置
}

/******************************************************************************/
/*灌装完成，前往加热位置*/
void GotoHeat_Action(void)
{
		/*开启气泵,将放置块推到加热位置，等待传感器触发*/
//		Pump_Control(PUMP3，DISABLE)	
//		Pump_Control(PUMP4，ENABLE)	
}

/******************************************************************************/
/*当前位置加热位置，可加热*/
void Heat_Action(void)
{
	/*到达加热位置之后，气泵回去*/
//		Pump_Control(PUMP4，DISABLE)	
//		Pump_Control(PUMP3，ENABLE)	
	if(1)
	{
		//检测温度，如果低于目标温度等待
	}
	else
	{
		/*开启气泵,使气泵下降，覆膜*/
//		Pump_Control(PUMP5，DISABLE)	
//		Pump_Control(PUMP6，ENABLE)	
		//计数
		//if(计数>time)
		//关闭气泵，并使其向上运动
//		Pump_Control(PUMP6，DISABLE)	
//		Pump_Control(PUMP5，ENABLE)
			ExitFlag.CurrentHeatSR = FALSE;
	}
}

/******************************************************************************/
void Conpaction_Action(void)
{
			/*开启气泵,使气泵下降，覆膜*/
//		Pump_Control(PUMP7，DISABLE)	
//		Pump_Control(PUMP8，ENABLE)	
		//计数
		//if(计数>time)
		//关闭气泵，并使其向上运动
//		Pump_Control(PUMP7，DISABLE)	
//		Pump_Control(PUMP8，ENABLE)
			ExitFlag.ConpactionPosSR = FALSE;
}

/******************************************************************************/
void Incise_Action(void)
{
					/*开启气泵,使气泵下降，覆膜*/
//		Pump_Control(PUMP11，DISABLE)	
//		Pump_Control(PUMP12，DISABLE)
//		Pump_Control(PUMP9，ENABLE)	
//		Pump_Control(PUMP10，ENABLE)	

		//计数
		//if(计数>time)
		//关闭气泵，并使其向上运动
//		Pump_Control(PUMP9，DISABLE)	
//		Pump_Control(PUMP10，DISABLE)
//		Pump_Control(PUMP11，ENABLE)	
//		Pump_Control(PUMP12，ENABLE)
			ExitFlag.IncisePosSR = TRUE;
}

/******************************************************************************/
void InciseFinish_Action(void)
{
			/*开启气泵,将放置块推到转向位置，等待传感器触发*/
//		Pump_Control(PUMP13，DISABLE)	
//		Pump_Control(PUMP14，ENABLE)	
}

/******************************************************************************/
void Trun_Action(void)
{
	/*先让气泵13,14回去*/
//		Pump_Control(PUMP14，DISABLE)	
//		Pump_Control(PUMP13，ENABLE)	
	/*开启气泵,将放置块推到放置反应盘位置，等待传感器触发*/
//		Pump_Control(PUMP16，DISABLE)	
//		Pump_Control(PUMP15，ENABLE)	
}

/******************************************************************************/
void VibratingDisk_Action(void)
{
		/*先让气泵13,14回去*/
//		Pump_Control(PUMP15，DISABLE)	
//		Pump_Control(PUMP16，ENABLE)	
}
