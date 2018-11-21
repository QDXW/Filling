/******************************************************************************/
#include "devices.h"

/******************************************************************************/
PUMP_NUM Pump;
uint8 Push_Count = 0,Carve_Flag = 1;

/******************************************************************************/
void Devices_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC |
			RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOD, ENABLE);
	

	/* pump1~20 */ 
	GPIO_InitStructure.GPIO_Pin = PIN_PUMP_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_PUMP_1, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_PUMP_1, PIN_PUMP_1);
	
	GPIO_InitStructure.GPIO_Pin = PIN_PUMP_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_PUMP_2, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_PUMP_2, PIN_PUMP_2);
	
	GPIO_InitStructure.GPIO_Pin = PIN_PUMP_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_PUMP_3, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_PUMP_3, PIN_PUMP_3);
	
	GPIO_InitStructure.GPIO_Pin = PIN_PUMP_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_PUMP_4, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_PUMP_4, PIN_PUMP_4);
	
	GPIO_InitStructure.GPIO_Pin = PIN_PUMP_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_PUMP_5, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_PUMP_5, PIN_PUMP_5);
	
	GPIO_InitStructure.GPIO_Pin = PIN_PUMP_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_PUMP_6, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_PUMP_6, PIN_PUMP_6);
	
	GPIO_InitStructure.GPIO_Pin = PIN_PUMP_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_PUMP_7, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_PUMP_7, PIN_PUMP_7);
	
	GPIO_InitStructure.GPIO_Pin = PIN_PUMP_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_PUMP_8, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_PUMP_8, PIN_PUMP_8);
	
	GPIO_InitStructure.GPIO_Pin = PIN_PUMP_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_PUMP_9, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_PUMP_9, PIN_PUMP_9);
	
	GPIO_InitStructure.GPIO_Pin = PIN_PUMP_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_PUMP_10, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_PUMP_10, PIN_PUMP_10);
	
	GPIO_InitStructure.GPIO_Pin = PIN_PUMP_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_PUMP_11, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_PUMP_11, PIN_PUMP_11);
	
	GPIO_InitStructure.GPIO_Pin = PIN_PUMP_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_PUMP_12, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_PUMP_12, PIN_PUMP_12);
	
	GPIO_InitStructure.GPIO_Pin = PIN_PUMP_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_PUMP_13, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_PUMP_13, PIN_PUMP_13);
	
	GPIO_InitStructure.GPIO_Pin = PIN_PUMP_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_PUMP_14, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_PUMP_14, PIN_PUMP_14);
	
	GPIO_InitStructure.GPIO_Pin = PIN_PUMP_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_PUMP_15, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_PUMP_15, PIN_PUMP_15);
	
	GPIO_InitStructure.GPIO_Pin = PIN_PUMP_16;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_PUMP_16, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_PUMP_16, PIN_PUMP_16);
	
	GPIO_InitStructure.GPIO_Pin = PIN_PUMP_17;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_PUMP_17, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_PUMP_17, PIN_PUMP_17);
	
	GPIO_InitStructure.GPIO_Pin = PIN_PUMP_18;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_PUMP_18, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_PUMP_18, PIN_PUMP_18);
	
	GPIO_InitStructure.GPIO_Pin = PIN_PUMP_19;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_PUMP_19, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_PUMP_19, PIN_PUMP_19);
	
	GPIO_InitStructure.GPIO_Pin = PIN_PUMP_20;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_PUMP_20, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_PUMP_20, PIN_PUMP_20);


	/* Heat Led 1-3 */ 
	GPIO_InitStructure.GPIO_Pin = PIN_LED_HEAT_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_LED_HEAT_1, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_LED_HEAT_1, PIN_LED_HEAT_1);
	
	GPIO_InitStructure.GPIO_Pin = PIN_LED_HEAT_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_LED_HEAT_2, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_LED_HEAT_2, PIN_LED_HEAT_2);
	
	GPIO_InitStructure.GPIO_Pin = PIN_LED_HEAT_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_LED_HEAT_3, &GPIO_InitStructure);
	GPIO_ResetBits(PORT_LED_HEAT_3, PIN_LED_HEAT_3);
	
	/* key */
	GPIO_InitStructure.GPIO_Pin = PIN_KEY_CTR;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_KEY_CTR, &GPIO_InitStructure);	
	GPIO_ResetBits(PORT_KEY_CTR, PIN_KEY_CTR);
}

/******************************************************************************/
void Pump_Set(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,FunctionalState status)
{
	if(ENABLE == status)
	{
		GPIO_SetBits(GPIOx, GPIO_Pin);
	}
	else
	{
		GPIO_ResetBits(GPIOx, GPIO_Pin);
	}
}

/******************************************************************************/
void Pump_Control(PUMP_NUM Pump,FunctionalState status)
{
	switch(Pump)
	{
		case PUMP1:Pump_Set(PORT_PUMP_1,PIN_PUMP_1,status);break;
		case PUMP2:Pump_Set(PORT_PUMP_2,PIN_PUMP_2,status);break;
		case PUMP3:Pump_Set(PORT_PUMP_3,PIN_PUMP_3,status);break;
		case PUMP4:Pump_Set(PORT_PUMP_4,PIN_PUMP_4,status);break;
		case PUMP5:Pump_Set(PORT_PUMP_5,PIN_PUMP_5,status);break;
		case PUMP6:Pump_Set(PORT_PUMP_6,PIN_PUMP_6,status);break;
		case PUMP7:Pump_Set(PORT_PUMP_7,PIN_PUMP_7,status);break;
		case PUMP8:Pump_Set(PORT_PUMP_8,PIN_PUMP_8,status);break;
		case PUMP9:Pump_Set(PORT_PUMP_9,PIN_PUMP_9,status);break;
		case PUMP10:Pump_Set(PORT_PUMP_10,PIN_PUMP_10,status);break;
		case PUMP11:Pump_Set(PORT_PUMP_11,PIN_PUMP_11,status);break;
		case PUMP12:Pump_Set(PORT_PUMP_12,PIN_PUMP_12,status);break;
		case PUMP13:Pump_Set(PORT_PUMP_13,PIN_PUMP_13,status);break;
		case PUMP14:Pump_Set(PORT_PUMP_14,PIN_PUMP_14,status);break;
		case PUMP15:Pump_Set(PORT_PUMP_15,PIN_PUMP_15,status);break;
		case PUMP16:Pump_Set(PORT_PUMP_16,PIN_PUMP_16,status);break;
		case PUMP17:Pump_Set(PORT_PUMP_17,PIN_PUMP_17,status);break;
		case PUMP18:Pump_Set(PORT_PUMP_18,PIN_PUMP_18,status);break;
		case PUMP19:Pump_Set(PORT_PUMP_19,PIN_PUMP_19,status);break;
		case PUMP20:Pump_Set(PORT_PUMP_20,PIN_PUMP_20,status);break;
		default:
			break;
	}
}

/******************************************************************************/
void Devices_Valve_Action(void)
{
	switch(8)
	{
		case 8:
			if(Valve_Lock & 0x80)
			{
				Valve8_Action();

				/* 结束当前操作  */
				Valve_Lock &= 0X7F;
			}
		case 7:
			if(Valve_Lock & 0x40)
			{
				Valve7_Action();

				/* 结束当前操作  */
				Valve_Lock &= 0XBF;
			}

		case 6:
			if(Valve_Lock & 0x20)
			{
				Valve6_Action();

				/* 结束当前操作  */
				Valve_Lock &= 0XDF;
			}

		case 5:
			if(Valve_Lock & 0x10)
			{
				if(L100_Apparatus)
				{
//					Valve5_Action();

					/* 结束当前操作  */
					Valve_Lock &= 0XEF;
				}
			}

		case 4:
			if(Valve_Lock & 0x08)
			{

//				Valve4_Action();
				Valve_Lock &= 0XF7;
			}

		case 3:
			if(Valve_Lock & 0x04)
			{
//				Valve3_Action();
				Valve_Lock &= 0XFB;
			}

		case 2:
			if(Valve_Lock & 0x02)
			{
				Valve2_Action();
			}

		case 1:
			if(Valve_Lock & 0x01)
			{
				Valve1_Action();
			}

		case 0:
			break;

		default:
			break;
	}
}

/******************************************************************************/
void Valve1_Action (void)
{
	if(!GPIO_ReadInputDataBit(PORT_SWITCH_5, PIN_SWITCH_5))
	{
		/* 阀1移动  */
		Valve1_Lock(CLOSED);
		Delay_ms_SW(1500);
		Valve1_Lock(OPEN);

		/* 结束当前操作  */
		Valve_Lock &= 0xFE;
	}
}

/******************************************************************************/
void Valve2_Action (void)
{

	/* 结束当前操作  */
	Valve_Lock &= 0XFD;
}

/******************************************************************************/
void Valve3_Action (void)
{
	uint8 buf[2] = {0x09,0x00};
//	if(Heat_Status & 0x04)
	{
		Valve5_Lock(CLOSED);

		buf[1] = 0X01,buf[0] = 0X05;						//滑块挡柱3
		Comm_CanDirectSend(STDID_RX_VALVE_LOCK,buf,2);

		/* 运动架6 8 运动  */
		Valve6_Lock(CLOSED);
		Delay_ms_SW(800);
		Valve8_Lock(CLOSED);

		/* 结束当前操作  */
		Valve_Lock &= 0XFB;
	}
}

/******************************************************************************/
void Valve4_Action (void)
{
	uint8 buf[2] = {0x09,0x00};

	Valve7_Lock(OPEN);
	buf[1] = 0X00,buf[0] = 0X06;							//滑块挡柱4
	Comm_CanDirectSend(STDID_RX_VALVE_LOCK,buf,2);
	/* 气缸9运动  */
	Valve9_Lock(CLOSED);
	Delay_ms_SW(800);

	buf[1] = 0X01,buf[0] = 0X06;							//滑块挡柱4
	Comm_CanDirectSend(STDID_RX_VALVE_LOCK,buf,2);

	Delay_ms_SW(500);
	Valve9_Lock(OPEN);

//	if(Push_Count)
//	{
//		Valve11_Lock(CLOSED);							//Z轴下降
//		Delay_ms_SW(1000);
//		Valve11_Lock(OPEN);								//Z轴上升
//		Delay_ms_SW(500);
//		Valve10_Lock(CLOSED);							//X轴后退
//		Delay_ms_SW(2000);
//		Valve11_Lock(CLOSED);							//Z轴下降
//		Delay_ms_SW(1000);
//		Valve11_Lock(OPEN);								//Z轴上升
//		Delay_ms_SW(1000);
//		Valve10_Lock(OPEN);								//X轴前进
//		Delay_ms_SW(1000);
//
//		if(Push_Count > 10)
//		{
//			Push_Count = 10;
//		}
//	}
//	Push_Count++;

	/* 结束当前操作  */
	Valve_Lock &= 0XF7;
}

/******************************************************************************/
void Valve5_Action (void)
{
//	Valve5_Lock (CLOSED);
	Valve4_Lock (CLOSED);
//	Valve3_Lock (CLOSED);

//	/* 打开风扇  */
//	buf[1] = 0X01,buf[0] = 0X07;
//	Comm_CanDirectSend(STDID_RX_VALVE_LOCK,buf,2);

	/* 已经进行过第一次加热  */
	Heat_Status |=  1<<0;							//第一次加热
	Heat_Status |=  1<<2;							//第一次加热

	/* 结束当前操作  */
	Valve_Lock &= 0XEF;
}

/******************************************************************************/
void Valve6_Action (void)
{

}

/******************************************************************************/
void Valve7_Action (void)
{

}

/******************************************************************************/
void Valve8_Action (void)
{

}

/******************************************************************************/
void Devices_Return_Zero(void)
{
	uint8 buf[2] = {0x09,0x00};

	Valve1_Lock(OPEN);
	Valve2_Lock(OPEN);
	Valve3_Lock(OPEN);
	Valve4_Lock(OPEN);
	Valve5_Lock(OPEN);
	Valve6_Lock(OPEN);
	Valve7_Lock(OPEN);
	Valve8_Lock(OPEN);
	Valve9_Lock(OPEN);
	Valve10_Lock(OPEN);
	Valve11_Lock(OPEN);

	buf[1] = 0X00,buf[0] = 0X04;						//滑块挡柱1
	Comm_CanDirectSend(STDID_RX_VALVE_LOCK,buf,2);
	Delay_ms_SW(5);

	buf[1] = 0X00,buf[0] = 0X03;						//滑块挡柱2
	Comm_CanDirectSend(STDID_RX_VALVE_LOCK,buf,2);
	Delay_ms_SW(5);

	buf[1] = 0X00,buf[0] = 0X05;						//滑块挡柱3
	Comm_CanDirectSend(STDID_RX_VALVE_LOCK,buf,2);
	Delay_ms_SW(5);

	buf[1] = 0X01,buf[0] = 0X06;						//滑块挡柱4
	Comm_CanDirectSend(STDID_RX_VALVE_LOCK,buf,2);
	Delay_ms_SW(5);

	buf[0] = 1;
	HostComm_Cmd_Send_RawData(1, buf,CMD_CODE_WARM_BLOCK1);
	Delay_ms_SW(5);
	HostComm_Cmd_Send_RawData(1, buf,CMD_CODE_WARM_BLOCK2);
	Delay_ms_SW(5);

	/* 最大功率进行加热 */
	Start_Temp = 1;
	L100_Switch = 1;
}

/******************************************************************************/
void Valve1_Lock (uint8 status)
{
	if(status)
	{
		Pump_Control(PUMP8,DISABLE);
		Pump_Control(PUMP9,ENABLE);
	}
	else
	{
		Pump_Control(PUMP8,ENABLE);
		Pump_Control(PUMP9,DISABLE);
	}
}

/******************************************************************************/
void Valve2_Lock (uint8 status)
{
	if(status)
	{
		Pump_Control(PUMP10,DISABLE);
		Pump_Control(PUMP11,ENABLE);
	}
	else
	{
		Pump_Control(PUMP10,ENABLE);
		Pump_Control(PUMP11,DISABLE);
	}
}

/******************************************************************************/
void Valve3_Lock (uint8 status)
{
	if(status)
	{
		Pump_Control(PUMP2,DISABLE);
		Pump_Control(PUMP3,ENABLE);
	}
	else
	{
		Pump_Control(PUMP2,ENABLE);
		Pump_Control(PUMP3,DISABLE);
	}
}

/******************************************************************************/
void Valve4_Lock (uint8 status)
{
	if(status)
	{
		Pump_Control(PUMP4,DISABLE);
		Pump_Control(PUMP5,ENABLE);
	}
	else
	{
		Pump_Control(PUMP4,ENABLE);
		Pump_Control(PUMP5,DISABLE);
	}
}

/******************************************************************************/
void Valve5_Lock (uint8 status)
{
	if(status)
	{
		Pump_Control(PUMP6,DISABLE);
		Pump_Control(PUMP7,ENABLE);
	}
	else
	{
		Pump_Control(PUMP6,ENABLE);
		Pump_Control(PUMP7,DISABLE);
	}
}

/******************************************************************************/
void Valve6_Lock (uint8 status)
{
	if(status)
	{
		Pump_Control(PUMP14,DISABLE);
		Pump_Control(PUMP15,ENABLE);
	}
	else
	{
		Pump_Control(PUMP14,ENABLE);
		Pump_Control(PUMP15,DISABLE);
	}
}

/******************************************************************************/
void Valve7_Lock (uint8 status)
{
	if(status)
	{
		Pump_Control(PUMP16,DISABLE);
		Pump_Control(PUMP17,ENABLE);
	}
	else
	{
		Pump_Control(PUMP16,ENABLE);
		Pump_Control(PUMP17,DISABLE);
	}
}

/******************************************************************************/
void Valve8_Lock (uint8 status)
{
	if(status)
	{
		Pump_Control(PUMP18,DISABLE);
		Pump_Control(PUMP19,ENABLE);
	}
	else
	{
		Pump_Control(PUMP18,ENABLE);
		Pump_Control(PUMP19,DISABLE);
	}
}

/******************************************************************************/
void Valve9_Lock (uint8 status)
{
	if(status)
	{
		Pump_Control(PUMP12,DISABLE);
		Pump_Control(PUMP13,ENABLE);
	}
	else
	{
		Pump_Control(PUMP12,ENABLE);
		Pump_Control(PUMP13,DISABLE);
	}
}

/******************************************************************************/
void Valve10_Lock (uint8 status)
{
	if(status)
	{
		Pump_Control(PUMP1,ENABLE);
	}
	else
	{
		Pump_Control(PUMP1,DISABLE);
	}
}

/******************************************************************************/
void Valve11_Lock (uint8 status)
{
	if(status)
	{
		Pump_Control(PUMP20,ENABLE);
	}
	else
	{
		Pump_Control(PUMP20,DISABLE);
	}
}

/******************************************************************************/
void Warm_Achieve (void)
{
	uint8 buf[2]  = {0x09,0x00};

	Valve3_Lock (OPEN);
	Valve4_Lock (OPEN);
	Valve5_Lock (OPEN);

	Heat_Status &= 0XFA;

	/* 后方挡柱 */
	buf[1] = 0X00,buf[0] = 0X04;
	Comm_CanDirectSend(STDID_RX_VALVE_LOCK,buf,2);

	/* 前方挡柱 */
	buf[1] = 0X00,buf[0] = 0X03;
	Comm_CanDirectSend(STDID_RX_VALVE_LOCK,buf,2);
	Time_second = 0;
	buf[0] = 0X00;
	HostComm_Cmd_Send_RawData(1, buf,CMD_CODE_APPARATUS_ACHIEVE);
}
