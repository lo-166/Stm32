#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "encode.h"

uint16_t Speed;
uint16_t Num;
int16_t CNT;

int main(void)
{
	OLED_Init();
	Timer_Init();
	
	OLED_ShowString(1, 1, "CNT:");	
	OLED_ShowString(2, 2, "Speed:");

while(1)
{
	OLED_ShowNum(1, 5, CNT, 5);

	OLED_ShowNum(2, 11, Encode_GetCounter(), 5);

}
}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
	{
		Speed = Encode_GetCounter();
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}
