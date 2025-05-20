#include "stm32f10x.h"                  // Device header


// AD初始化
void AD_Init(void)
{	
		
	// RCC启用 GPIOA AD
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	// RCC ADCCLK预分频 12MHZ
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	// 配置GPIO实例
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	// GPIOA初始化
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 配置ADC
	
	// 固定输入通道
	// ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	
	ADC_InitTypeDef ADCInitStructure;
	
	ADCInitStructure.ADC_DataAlign = ADC_DataAlign_Right; 				// 数据对齐方式
	ADCInitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  // 触发源
	ADCInitStructure.ADC_Mode = ADC_Mode_Independent;					// ADC模式 
	ADCInitStructure.ADC_NbrOfChannel = 1;								// 扫描通道数量
	ADCInitStructure.ADC_ContinuousConvMode = ENABLE; 					// 连续转换&单次转换
	ADCInitStructure.ADC_ScanConvMode = DISABLE;						// 扫描模式&非扫描模式
	
	ADC_Init(ADC1, &ADCInitStructure);
	
	// ADC上电
	ADC_Cmd(ADC1, ENABLE);
		
	// ADC校准
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);
	
	// 连续转换仅需触发一次
	ADC_SoftwareStartInjectedConvCmd(ADC1, ENABLE);
}



// 获取AD转换值
uint16_t AD_GetValue(uint8_t ADC_Channel)
{	
	{ // 非连续转换 控制触发和等待转换完成
	// ADC_SoftwareStartInjectedConvCmd(ADC1, ENABLE);
	// while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	}
	ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_55Cycles5);
	
	return ADC_GetConversionValue(ADC1);

}
