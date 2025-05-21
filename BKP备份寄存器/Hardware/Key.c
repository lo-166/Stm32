#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void Key_Init(void)
{
	// 时钟使能GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);


	// 通过结构体创建对象
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	// GPIOA初始化
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}


uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;		
	
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)			
	{
		Delay_ms(20);											
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0);	
		Delay_ms(20);											
		KeyNum = 1;												
	}
	
//	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)			
//	{
//		Delay_ms(20);											
//		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0);	
//		Delay_ms(20);											
//		KeyNum = 2;												
//	}
	
	return KeyNum;			
}
