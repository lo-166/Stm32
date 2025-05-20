#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "encode.h"
#include "ADC.h"

uint16_t Speed;
uint16_t Num;
int16_t CNT;
int16_t ADValue;
float ADVolatge;

int main(void)
{
	OLED_Init();
	Timer_Init();
	AD_Init();
	
	
	OLED_ShowString(1, 1, "ADValue:");	
	OLED_ShowString(2, 1, "ADVolatge:0.00V");	

while(1)
{
	ADValue = AD_GetValue(ADC_Channel_1);
	ADVolatge = (AD_GetValue(ADC_Channel_1) / 4095.0) * 3.3;
	
	OLED_ShowNum(1, 9, ADValue, 4);
	OLED_ShowNum(2, 11, ADVolatge, 1);
	OLED_ShowNum(2, 13, ((int16_t)(ADVolatge * 100) % 100), 2);
 
}
}

//void TIM3_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
//	{
//		Speed = Encode_GetCounter();
//		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
//	}
//}
