#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"



int main(void)
{
	OLED_Init();
	// 开启WWDG
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	
	// 设置WWDG 
	WWDG_SetPrescaler(IWDG_Prescaler_16);
	// 开启IWDG		
		// 窗口期
			// 30ms = 2.777777777777778e-5 * 4096 * 8 (T[5:0] - W[5:0])
			// W[5:0] = 54 - 33 = 21
	WWDG_SetWindowValue(0x40 | 21);	// 30ms
	
		// 超时时间
			// Twwdg = Tpclk1 * 4096 * 2^WDGTB * (T[5:0] + 1) Tpclk1 = 1 / Fpclk1
			// 50ms = 2.777777777777778e-5 * 4096 * 8 (T[5:0] + 1)
			// T[5:0] = 54
	WWDG_Enable(0x40 | 54);	// 50ms // 因为T6是标志位 需要置1防止WWDG产生复位
	
	// 显示是否为看门狗复位
	if(RCC_GetFlagStatus(RCC_FLAG_WWDGRST) == SET)
	{
		OLED_ShowString(1, 1, "WWDGRST");
		Delay_ms(20);
		OLED_ShowString(2, 1, "       ");
	}
	else
	{
		OLED_ShowString(1, 1, "RST");
		Delay_ms(20);
		OLED_ShowString(2, 1, "    ");
	}
while(1)
{
	Key_get_num();
	
	OLED_ShowString(2, 1, "Runing");
		Delay_ms(20);
	OLED_ShowString(2, 1, "      ");
	
	// 进行喂狗
	WWDG_SetCounter(0x40 | 54);
}
}
