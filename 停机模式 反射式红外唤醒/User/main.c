#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CountSensor.h"

uint16_t CountSenor;

int main(void)
{
	OLED_Init();
	CountSensor_Init();
	// 开启PWR
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	
	while(1)
	{
		CountSenor = CountSensor_GetCount();
		// 唤醒延时闪烁字符
		OLED_ShowString(2, 1, "Count:");
		OLED_ShowNum(2, 7, CountSenor, 4);
		OLED_ShowString(1, 1, "Runing");
		Delay_ms(500);
		OLED_ShowString(1, 1, "      ");
		OLED_ShowString(2, 1, "            ");
		Delay_ms(500);
		
		// 配置停机模式
		PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);
		// 初始化 系统时钟
		SystemInit();
	}
}

