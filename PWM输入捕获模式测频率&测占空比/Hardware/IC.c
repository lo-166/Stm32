#include "stm32f10x.h"                  // Device header


void IC_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 选择时钟源
	TIM_InternalClockConfig(TIM3);
	
	// 创建时基单元 对象 创建、输入实例参数
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInitStruct.TIM_Period = 65536 - 1; //ARR
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1; // CNT
	
	// 时基单元 初始化
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);

	TIM_ICInitTypeDef TIM_ICInitStructrue;
	
	TIM_ICInitStructrue.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructrue.TIM_ICFilter = 0xF;
	TIM_ICInitStructrue.TIM_ICPolarity = NVIC_LP_SEVONPEND;
	TIM_ICInitStructrue.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructrue.TIM_ICSelection = TIM_ICSelection_DirectTI;
	
	TIM_PWMIConfig(TIM3, &TIM_ICInitStructrue);
	
	
	
	//TIM_ICInit(TIM3, &TIM_ICInitStructrue);
	
	TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
	
	TIM_Cmd(TIM3, ENABLE);
	
}

uint32_t IC_GetFreq(void)
{
	return 1000000 / (TIM_GetCapture1(TIM3) + 1) ;
}

uint32_t IC_GetDuty(void)
{
	return (TIM_GetCapture2(TIM3) + 1) * 100 / (TIM_GetCapture1(TIM3) + 1) ;
}
