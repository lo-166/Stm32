#include "stm32f10x.h"                  // Device header
#include "Delay.h"

uint16_t AD_Value[4];	

//// AD初始化
//void AD_Init(void)
//{	
//		
//	// RCC启用 GPIOA AD DMA
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

//	// RCC ADCCLK预分频 12MHZ
//	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
//	
//	// 配置GPIO实例
//	GPIO_InitTypeDef GPIO_InitStructure;
//	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	
//	// GPIOA初始化
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//	// 配置ADC
//	
//	// 固定输入通道
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
//	
//	ADC_InitTypeDef ADCInitStructure;
//	ADCInitStructure.ADC_DataAlign = ADC_DataAlign_Right; 				// 数据对齐方式
//	ADCInitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  // 触发源
//	ADCInitStructure.ADC_Mode = ADC_Mode_Independent;					// ADC模式 
//	ADCInitStructure.ADC_NbrOfChannel = 4;								// 扫描通道数量
//	ADCInitStructure.ADC_ContinuousConvMode = DISABLE; 					// 连续转换&单次转换
//	ADCInitStructure.ADC_ScanConvMode = ENABLE;						// 扫描模式&非扫描模式
//	ADC_Init(ADC1, &ADCInitStructure);
//	
//		
//	// 创建DMA实例
//	DMA_InitTypeDef DMA_InitStructure;
//	
//	// 配置DMA实例
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;	// 源地址    
//    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;// 数据类型
//    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	// 地址是否自增 

//	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;// 目的地址  
//    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;	// 数据类型
//    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	// 地址是否自增 
//	
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	// 传输方向    
//	DMA_InitStructure.DMA_BufferSize = 4;// 转运次数
//	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	 //触发源选择 与M2M软件触发同时使用导致DMA死循环
//    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;	// 是否重装
//	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;	// 优先级选择器
//	// 应用DMA实例
//	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
//	
//	DMA_Cmd(DMA1_Channel1, ENABLE);
//	ADC_DMACmd(ADC1, ENABLE);
//	// ADC上电
//	ADC_Cmd(ADC1, ENABLE);
//		
//	// ADC校准
//	ADC_ResetCalibration(ADC1);
//	while(ADC_GetResetCalibrationStatus(ADC1) == SET);
//	ADC_StartCalibration(ADC1);
//	while(ADC_GetCalibrationStatus(ADC1) == SET);
//	
//	// 连续转换仅需触发一次
//	
//}



// 获取AD转换值
void AD_GetValue(void)
{	
	DMA_Cmd(DMA1_Channel1, DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1, 4);
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
	DMA_ClearFlag(DMA1_FLAG_TC1);

}

//uint16_t AD_Value; // DMA传输目标数组（4通道）

void AD_Init(void)
{
    /* 时钟使能 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    /* ADC时钟配置（PCLK2=72MHz，6分频得12MHz）*/
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    /* GPIO配置（PA0-PA3模拟输入） */
    GPIO_InitTypeDef GPIO_InitStruct = {
        .GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3,
        .GPIO_Mode = GPIO_Mode_AIN,
        .GPIO_Speed = GPIO_Speed_50MHz
    };
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* ADC基本配置 */
    ADC_InitTypeDef ADC_InitStruct = {
        .ADC_Mode = ADC_Mode_Independent,       // 独立模式
        .ADC_ScanConvMode = ENABLE,             // 扫描模式
        .ADC_ContinuousConvMode = ENABLE,      // 连续转换
        .ADC_ExternalTrigConv = ADC_ExternalTrigConv_None, // 软件触发
        .ADC_DataAlign = ADC_DataAlign_Right,   // 数据右对齐
        .ADC_NbrOfChannel = 4                   // 4个转换通道
    };
    ADC_Init(ADC1, &ADC_InitStruct);

    /* 配置ADC通道采样时间（239.5周期保障精度） */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_239Cycles5);

    /* DMA配置（循环模式自动搬运数据） */
    DMA_InitTypeDef DMA_InitStruct = {
        .DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR,  // 外设地址
        .DMA_MemoryBaseAddr = (uint32_t)AD_Value,       // 内存地址
        .DMA_DIR = DMA_DIR_PeripheralSRC,               // 外设为源
        .DMA_BufferSize = 4,                            // 4通道数据
        .DMA_PeripheralInc = DMA_PeripheralInc_Disable, // 外设地址不递增
        .DMA_MemoryInc = DMA_MemoryInc_Enable,          // 内存地址递增
        .DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord,
        .DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord,
        .DMA_Mode = DMA_Mode_Circular,                  // 循环模式
        .DMA_Priority = DMA_Priority_High,
        .DMA_M2M = DMA_M2M_Disable
    };
    DMA_Init(DMA1_Channel1, &DMA_InitStruct);
    DMA_Cmd(DMA1_Channel1, ENABLE);

    /* 启用ADC DMA */
    ADC_DMACmd(ADC1, ENABLE);
    
    /* ADC校准流程 */
    ADC_Cmd(ADC1, ENABLE);
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
    
    /* 启动连续转换 */
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
