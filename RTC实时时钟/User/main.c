#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "RTC.h"


int main(void)
{
	OLED_Init();
	RTC_Init();
	
	OLED_ShowString(1, 1, "Data:xxxx-xx-xx");
	OLED_ShowString(2, 1, "time:xx:xx:xx");
	OLED_ShowString(3, 1, "Cnt:");
	OLED_ShowString(4, 1, "Div:");

while(1)
{
	RTC_ReadTime();
	
		OLED_ShowNum(1, 6, MyRTC_Time[0], 4);		//显示MyRTC_Time数组中的时间值，年
		OLED_ShowNum(1, 11, MyRTC_Time[1], 2);		//月
		OLED_ShowNum(1, 14, MyRTC_Time[2], 2);		//日
		OLED_ShowNum(2, 6, MyRTC_Time[3], 2);		//时
		OLED_ShowNum(2, 9, MyRTC_Time[4], 2);		//分
		OLED_ShowNum(2, 12, MyRTC_Time[5], 2);		//秒
		
		OLED_ShowNum(3, 6, RTC_GetCounter(), 10);	//显示32位的秒计数器
		OLED_ShowNum(4, 6, RTC_GetDivider(), 10);	//显示余数寄存器

}
}
