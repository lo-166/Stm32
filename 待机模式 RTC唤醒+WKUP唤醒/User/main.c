#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "RTC.h"


int main(void)
{
	OLED_Init();
	RTC_Init();
	// 开启PWR
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	
	// 显示静态信息 
	OLED_ShowString(1, 1, "Cnt :");
	OLED_ShowString(2, 1, "ALR :");
	OLED_ShowString(3, 1, "ALRF:");
//	OLED_ShowString(4, 1, "DIV :");
	
	/*使能WKUP引脚*/
	PWR_WakeUpPinCmd(ENABLE);	
	
	
	// RTC闹钟设置
	uint32_t Alarm = RTC_GetCounter() + 3;			
	RTC_SetAlarm(Alarm); 
	

while(1)
{
	// 显示动态信息
	OLED_ShowNum(1, 6, RTC_GetCounter(),10);
	OLED_ShowNum(2, 6, Alarm, 10);
	OLED_ShowNum(3, 6, RTC_GetFlagStatus(RTC_FLAG_ALR),1);
//	OLED_ShowNum(4, 6, RTC_GetDivider(), 10);
	
	// 延时清空
	
	//OLED闪烁STANDBY，指示即将进入待机模式
	for(int i = 0; i < 3; i++)
	{
		OLED_ShowString(4, 9, "STANDBY");
		Delay_ms(1000);
		OLED_ShowString(4, 9, "       ");
		Delay_ms(1000);
	
	}
	OLED_Clear();
	
	// 进入待机模式
	PWR_EnterSTANDBYMode();

}
}
