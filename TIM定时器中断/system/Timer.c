#include "stm32f10x.h"                  // Device header

extern uint16_t Num;



void Timer_Init(void)
{
	// RCC 启动 CPU APB1外围时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// 时钟源 选择
	TIM_InternalClockConfig(TIM2);
	
	// TIM 创建 对象和实例
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	{
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; // 对极性滤波 采样频率 设置
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; // 计数器模式 选择
	
	// 周期Period 和 预分频Prescaler 计算定时 72M / 7201 - 1 / 10001 - 1 = 1Hz 1s = 1Hz 
	TIM_TimeBaseInitStruct.TIM_Period = 10000 - 1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200 - 1;
		
	// 重复重装器 高级定时器才有
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	}
	
	// 时基单元初始化
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	// 中断控制 配置
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	// NVIC 分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	// NVIC 创建 对象和实例
	NVIC_InitTypeDef NVIC_InitStruct;
	
	// 选择 中断函数
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	
	// 手动清除标志位 防止初始化直接进入中断更新
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	
	// 配置 NVIC初始化
	NVIC_Init(&NVIC_InitStruct);
	
	// 使能计数器
	TIM_Cmd(TIM2, ENABLE);

}

// 中断函数
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		Num++;
	
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
