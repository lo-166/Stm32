#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"



int main(void)
{
	OLED_Init();
	// 开启PWR
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	
	// 设置IWDG 开启IWDG时 自动开启LSI且无法关闭
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_16);
	
	/*  
		Tiwdg = Tlsi * PR * (RL + 1) 
		Tlsi = 1 / Flsi 	1 / 40000hz = 0.025ms
		1000ms = 0.025ms * 2 * (RL + 1) 
		RL = 2499
	*/
	IWDG_SetReload(2499);	
	
	// 进行喂狗
	IWDG_ReloadCounter();
	
	// 开启IWDG
	IWDG_Enable();
	
	// 显示是否为看门狗复位
	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET)
	{
		OLED_ShowString(1, 1, "IWDGRST");
		Delay_ms(200);
		OLED_ShowString(2, 1, "       ");
	}
	else
	{
		OLED_ShowString(1, 1, "RST");
		Delay_ms(200);
		OLED_ShowString(2, 1, "    ");
	}
while(1)
{
	Key_get_num();
	
	OLED_ShowString(2, 1, "Runing");
	Delay_ms(500);
	OLED_ShowString(2, 1, "      ");
	
	IWDG_ReloadCounter();
}
}
