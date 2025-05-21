#include "stm32f10x.h"                  // Device header


// 读取Flash
uint32_t MyFlash_ReadWord(uint32_t Address)
{
	// 读取操作仅需较低权限, 无需解锁
	return *(__IO uint32_t *)(Address);
}

uint16_t MyFlash_ReadHalfWord(uint32_t Address)
{
	// 读取操作仅需较低权限, 无需解锁
	return *(__IO uint16_t *)(Address);
}

uint8_t MyFlash_ReadByte(uint32_t Address)
{
	// 读取操作仅需较低权限, 无需解锁
	return *(__IO uint8_t *)(Address);
}
// 擦除Flash
void MyFlash_ErasePage(uint32_t Address)
{
	FLASH_Unlock();
	FLASH_ErasePage(Address);
	FLASH_Lock();
}
void MyFlash_EraseAllPage(uint32_t Address)
{
	FLASH_Unlock();
	FLASH_EraseAllPages();
	FLASH_Lock();
}


// 编程Flash
void MyFlash_WritelWord(uint32_t Address, uint32_t Data)
{
	FLASH_Unlock();
	FLASH_ProgramWord(Address, Data);
	FLASH_Lock();
	
}
void MyFlash_WritelHalfWord(uint32_t Address, uint16_t Data)
{
	FLASH_Unlock();
	FLASH_ProgramHalfWord(Address, Data);
	FLASH_Lock();
	
}


