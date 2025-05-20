#include "stm32f10x.h"                  // Device header

void LED_Init(void)
{
	// 时钟使能GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	// 通过结构体创建对象
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3;//GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	// GPIOA初始化
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_3);
}

// (开关1/0, GPIO_X, GPIO_X_X)
void LEDn_set_IO(int y , GPIO_TypeDef* x, uint16_t GPIO_Pin_X)
{
	if(y)
	{GPIO_SetBits(x, GPIO_Pin_X);}
	else
	{GPIO_ResetBits(x, GPIO_Pin_X);}
	
}


void LED1_Ture(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	}
}
void LED3_Ture(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_3) == 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_3);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	}
}
