#include "stm32f10x.h"                  // Device header




void PWM_LED_Init(void)
{
	// 开启RCC 中的 TIM2定时器
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	// 开启RCC GPIOB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	// 通过结构体创建对象
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	// GPIOB初始化
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	
	// 选择时钟源
	TIM_InternalClockConfig(TIM4);
	
	// 创建时基单元 对象 创建、输入实例参数
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInitStruct.TIM_Period = 100 - 1; //ARR
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 720 - 1; // CNT
	
	// 时基单元 初始化
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
	
	
	//创建OC结构体
	TIM_OCInitTypeDef TIM_OC1InitStruct;

	// OC结构体默认初始化
	TIM_OCStructInit(&TIM_OC1InitStruct);
	

	// OC结构体需求配置
	TIM_OC1InitStruct.TIM_OCMode = TIM_OCMode_PWM1; //OC模式
	TIM_OC1InitStruct.TIM_Pulse = 0; // 控制脉冲 高电平时间 CCR
	TIM_OC1InitStruct.TIM_OCPolarity = TIM_OCPolarity_High; // 信号极性
	TIM_OC1InitStruct.TIM_OutputState = TIM_OutputState_Enable; // OC状态

	// OC初始化
	TIM_OC1Init(TIM4, &TIM_OC1InitStruct);
	
	// TIM使能
	TIM_Cmd(TIM4, ENABLE);
	
}

void PWM_SetCompare1(uint16_t Compare)
{
	// 单独设置CCR值
	TIM_SetCompare1(TIM4, Compare);
}


