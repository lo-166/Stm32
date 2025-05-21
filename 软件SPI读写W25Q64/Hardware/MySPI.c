#include "stm32f10x.h"                  // Device header

//	引脚封装
void MySPI_W_SS(uint8_t bitValue)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)bitValue);
}

void MySPI_W_SCK(uint8_t bitValue)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)bitValue);
}

void MySPI_W_MOSI(uint8_t bitValue)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)bitValue);
}		
uint8_t MySPI_R_MISO(void)
{
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
}

//	引脚初始化
void MySPI_Init(void)
{
	// 时钟使能GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	// 通过结构体对象创建实例
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	MySPI_W_SS(1);
	MySPI_W_SCK(0);
	
}


//	SPI起始
void MySPI_Start(void)
{
	MySPI_W_SS(0);
}

//	SPI终止
void MySPI_Stop(void)
{
	MySPI_W_SS(1);
}

//	SPI交换字节-Mode0
uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
	uint8_t i;
	
	for(i = 0; i < 8; i++)
	{
		MySPI_W_MOSI(ByteSend & 0x80);
		ByteSend <<= 1;
		MySPI_W_SCK(1);
		if(MySPI_R_MISO() == 1)
		{
			 ByteSend |= 0x01;
		}
		MySPI_W_SCK(0);
	}
	return ByteSend;
}

////	SPI交换字节-Mode0
//uint8_t SPI_SwapByte(uint8_t ByteSend)
//{
//	uint8_t i, ByteReceive = 0x00;
//	
//	for(i = 0; i < 8; i++)
//	{
//		SPI_W_MOSI(ByteSend & (0x80 >> i));
//		SPI_W_SCK(1);
//		if(SPI_R_MISO() == 1)
//		{
//			ByteReceive |= (0x80 >> i);
//		}
//		SPI_W_SCK(0);
//	}
//	return ByteReceive;
//}

////	SPI交换字节-Mode1
//uint8_t SPI_SwapByte(uint8_t ByteSend)
//{
//	uint8_t i;
//	
//	for(i = 0; i < 8; i++)
//	{
//		SPI_W_SCK(1);
//		SPI_W_MOSI(ByteSend & 0x80);
//		ByteSend <<= 1;
//		SPI_W_SCK(0);
//		if(SPI_R_MISO() == 1)
//		{
//			 ByteSend |= 0x01;
//		}

//	}
////	SPI交换字节-Mode2 SCK默认高电平
//uint8_t SPI_SwapByte(uint8_t ByteSend)
//{
//	uint8_t i;
//	
//	for(i = 0; i < 8; i++)
//	{
//		SPI_W_MOSI(ByteSend & 0x80);
//		ByteSend <<= 1;
//		SPI_W_SCK(0);
//		if(SPI_R_MISO() == 1)
//		{
//			 ByteSend |= 0x01;
//		}
//		SPI_W_SCK(1);
//	}
//}
//}//	SPI交换字节-Mode3 SCK默认高电平
//uint8_t SPI_SwapByte(uint8_t ByteSend)
//{
//	uint8_t i;
//	
//	for(i = 0; i < 8; i++)
//	{
//		if(SPI_R_MISO() == 1)
//		{
//			 ByteSend |= 0x01;
//		}
//		SPI_W_SCK(0);
//		SPI_W_MOSI(ByteSend & 0x80);
//		ByteSend <<= 1;
//		SPI_W_SCK(1);
//	}
//}





