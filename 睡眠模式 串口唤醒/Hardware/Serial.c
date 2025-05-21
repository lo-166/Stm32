#include "stm32f10x.h"                  // Device header
#include "stdio.h" 
#include "stdarg.h" 

uint8_t Serial_Flag;
uint8_t Serial_RxData;

void Serial_Init(void)
{
	// RCC START GPIOA, USART
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	
	// 通过结构体创建实例
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	// GPIOA初始化
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	// GPIOA初始化
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; 				// 串口IO模式
	USART_InitStructure.USART_Parity = USART_Parity_No; 							// 检验模式
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 							// 停止模式
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; 					// 字节设置
	USART_Init(USART1, &USART_InitStructure);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);


	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructrue;
	NVIC_InitStructrue.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructrue.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructrue.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructrue.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructrue);
	
	USART_Cmd(USART1, ENABLE);	
}

void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1, Byte);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void Serial_SendArry(uint8_t *Arry, uint16_t Length)
{
		uint8_t i = 0;
	for(i = 0; i < Length; i ++ )
	{
		USART_SendData(USART1, Arry[i]);
	}
	
}

uint16_t Serial_Pow(uint16_t X, uint16_t Y)
{
	uint16_t Result = 1;
	while(Y --)
	{
		 Result *= X;
	}
	return Result;
}

void Seiral_SendNumber(uint16_t Number, uint16_t Length)
{

	uint8_t i = 0;
	for(i = 0; i < Length; i ++ )
	{
		// 12345 / 10000 = 1.2345 %10 = 1
		USART_SendData(USART1,((Number / Serial_Pow(10, Length - i - 1)) %10) + '0');
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	}

}

void Serial_SendString(char *Str)
{
		uint16_t num = 0;
	for(num = 0; Str[num] != '\0'; num ++ )
	{
		USART_SendData(USART1, Str[num]);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	}
}

int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

	return ch;
}
// sprintf封装 可变参数
void Serial_Print(char *format, ...)
{
	char arry1[100];
	va_list arg; // 创建参数表 arg
	va_start(arg, format); // 起始位置为 format 
	vsprintf(arry1, format, arg); // 打印位置 arry1 格式化字符串 format 参数表 arg
	va_end(arg);	// 释放参数表 arg
	Serial_SendString(arry1); // 串口发送
}

uint16_t Serial_GetRxData(void)
{
	return Serial_RxData;
}
uint8_t Serial_GetFlag(void)
{
	if(Serial_Flag == 1)
	{
		Serial_Flag = 0;
		return 1;
	}
	return 0;
}

//void USART1_IRQHandler(void)
//{
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
//	{
//		Serial_RxData = USART_ReceiveData(USART1);
//		Serial_Flag = 1;
//		// 读取USART_ReceiveData();自动清除标志位
//	}
//}

void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)		//判断是否是USART1的接收事件触发的中断
	{
		Serial_RxData = USART_ReceiveData(USART1);				//读取数据寄存器，存放在接收的数据变量
		Serial_Flag = 1;										//置接收标志位变量为1
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);			//清除USART1的RXNE标志位
																//读取数据寄存器会自动清除此标志位
																//如果已经读取了数据寄存器，也可以不执行此代码
	}
}
