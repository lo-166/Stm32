#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "Key.h"
#include "string.h"
#include "LED.h"
uint8_t KeyNum;			//定义用于接收按键键码的变量

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	Key_Init();			//按键初始化
	Serial_Init();		//串口初始化
	
	OLED_ShowString(1, 1, "TxPacket:");
	OLED_ShowString(3, 1, "RxPacket:");
	
	while (1)
	{
		if(Serial_RxFlag == 1)
		{
			OLED_ShowString(4, 1, Serial_RxPacket);
			if(Serial_RxPacket[1] == '/')
			{
				// 接收指令状态机
				
				if(0 == strcmp(Serial_RxPacket, "@/LED_ON"))
				{
					Serial_SendString("LED_ON_OK\r\n");
					OLED_ShowString(2, 1, "                ");
					OLED_ShowString(2, 1, "LED_ON_OK");
					LED1_ON();
				}
				
				else if(0 == strcmp(Serial_RxPacket, "@/LED_OFF"))
				{
					Serial_SendString("LED_OFF_OK\r\n");
					OLED_ShowString(2, 1, "                ");
					OLED_ShowString(2, 1, "LED_OFF_OK");
					LED1_OFF();

				}
				else
				{
					OLED_ShowString(2, 1, "                ");
					OLED_ShowString(2, 1, "ERROR_COMMAND");
				}

			}
				Serial_RxFlag = 0;
		}
		
	}
}
