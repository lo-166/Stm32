#include "stm32f10x.h"                  // Device header




void PWM_Init(void)
{
	// 开启RCC 中的 TIM2定时器
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	// 开启RCC GPIOB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	// 通过结构体创建对象
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	// GPIOA初始化
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	
	// 选择时钟源
	TIM_InternalClockConfig(TIM2);
	
	// 创建时基单元 对象 创建、输入实例参数
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInitStruct.TIM_Period = 20000 - 1; //ARR
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1; // CNT
	
	// 时基单元 初始化
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	
	//创建OC结构体
	TIM_OCInitTypeDef TIM_OCInitStruct;

	// OC结构体默认初始化
	TIM_OCStructInit(&TIM_OCInitStruct);
	

	// OC结构体需求配置
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1; //OC模式
	TIM_OCInitStruct.TIM_Pulse = 0; // 控制脉冲 高电平时间 CCR
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High; // 信号极性
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable; // OC状态

	// OC初始化
	TIM_OC2Init(TIM2, &TIM_OCInitStruct);
	
	// TIM使能
	TIM_Cmd(TIM2, ENABLE);
	
}

void PWM_SetCompare2(uint16_t Compare)
{
	TIM_SetCompare2(TIM2, Compare);		//设置CCR2的值
}


