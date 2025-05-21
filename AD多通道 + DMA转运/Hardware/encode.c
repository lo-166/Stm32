#include "stm32f10x.h"                  // Device header

void encode_Init(void)
{
	// 开启RCC 中的 TIM2定时器
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	// 开启RCC GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	// 通过结构体创建对象
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	// GPIOB初始化
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	
	// 编码器托管 无需选择时钟源

	
	// 创建时基单元 对象 创建、输入实例参数
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInitStruct.TIM_Period = 65536 - 1; //ARR

	
	// 时基单元 初始化

	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	
	// 创建结构体实例并赋予默认值
	TIM_ICInitTypeDef TIM_ICInitStructrue;
	TIM_ICStructInit(&TIM_ICInitStructrue);
	// 通道1
	TIM_ICInitStructrue.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructrue.TIM_ICFilter = 0xF;
	TIM_ICInitStructrue.TIM_ICPolarity = TIM_ICPolarity_Rising;
	// 通道2
	TIM_ICInitStructrue.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructrue.TIM_ICFilter = 0xF;
	TIM_ICInitStructrue.TIM_ICPolarity = TIM_ICPolarity_Rising;
	
	// IC初始化
	TIM_ICInit(TIM3, &TIM_ICInitStructrue);
	
	// 编码器配置
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	TIM_Cmd(TIM3, ENABLE);
}



int16_t Encode_GetCounter(void)
{	
	int16_t Tmpe;
	Tmpe = TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3, 0);
	return Tmpe;

}
