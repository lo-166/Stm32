#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
uint8_t RxData;	
uint8_t Arry[10] = {0x42, 0x43, 0x44, 0x45};

int main(void)
{
	OLED_Init();
	Serial_Init();
{
//	Serial_SendByte('A');
//	Serial_SendString("\r\n");
//	//Serial_SendArry(Arry);
//	Seiral_SendNumber(1234, 4);
//	
//	Serial_SendString("\r\n");
//	Serial_SendString("abc\r\n");
//	
//	// 修改底层fputc输出到串口 缺点: 其他USART使用需要进行修改
//	printf("Hellow, world!\r\n");
//	printf("Num=%d\r\n", 123);
//	
//	// sprintf 格式化字符串 多个USART都可直接使用
//	char arry1[100];
//	sprintf(arry1, "sprintf: Hellow, world!\r\n");
//	Serial_SendString(arry1);
//	
//	// sprintf封装 可变参数
//	Serial_Print("vsprintf: Hellow, world!\r\n");
//	// 标签栏 C/C++项 杂项填写--no-multibyte-chars UTF-8下防中文乱码
//	Serial_Print("你好!, 世界!\r\n");
};

while(1)
{
	// 显示延时字符串
	OLED_ShowString(2, 1, "Runing");
	Delay_ms(500);
	OLED_ShowString(2, 1, "      ");
	
	
	// 串口触发中断唤醒
	if(Serial_GetFlag() == 1)
	{
			RxData = Serial_GetRxData();		//获取串口接收的数据
			Serial_SendByte(RxData);			//串口将收到的数据回传回去，用于测试
			OLED_ShowHexNum(1, 1, RxData, 2);	//显示串口接收的数据
			Delay_ms(500);
			OLED_Clear();
	}
	// 进入睡眠模式
	__WFI();
}
}
