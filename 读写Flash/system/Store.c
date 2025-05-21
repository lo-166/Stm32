#include "stm32f10x.h"                  // Device header
#include "Flash.h" 

#define FLASH_CAPACITY 512
#define FLASH_BASE_ADDRESS 0x0800FC00

uint16_t Store_Data[FLASH_CAPACITY];

// Flash初始化
void Flash_Init(void)
{
	// 使用 标志位 判断 是否第一次使用
	if(0xAFAF != MyFlash_ReadHalfWord(FLASH_BASE_ADDRESS))
	{
		// 擦除页
		MyFlash_ErasePage(FLASH_BASE_ADDRESS);
		
		// 初始化页
		for(uint16_t i = 0; i < FLASH_CAPACITY; i++)
		{
			MyFlash_WritelHalfWord(FLASH_BASE_ADDRESS + (i * 2), 0x0000);
		}
		// 写入标志位
		MyFlash_WritelHalfWord(FLASH_BASE_ADDRESS, 0xAFAF);
	}
	// 不是第一次
	for(uint16_t i = 1; i < FLASH_CAPACITY; i++)
	{
		// 初始化页
		MyFlash_WritelHalfWord(FLASH_BASE_ADDRESS + (i * 2), 0x0000);
	}
	
}

// 保存数据到Flash
void Save_Flash(void)
{
	FLASH_Unlock();
	
	for(uint16_t i = 1; i < FLASH_CAPACITY; i++)
	{
		// 初始化页
		FLASH_ProgramHalfWord(FLASH_BASE_ADDRESS + (i * 2), Store_Data[i]);
	}
	
	FLASH_Lock();
}

// 清除数据
void Erase_Flash(void)
{
	for(uint16_t i = 0; i < FLASH_CAPACITY; i++)
	{
		Store_Data[i] = 0x0000;
	}
		Save_Flash();
	
}

