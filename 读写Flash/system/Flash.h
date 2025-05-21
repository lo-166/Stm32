#ifndef __FLASH_H
#define __FLASH_H


// 读取Flash
uint32_t MyFlash_ReadWord(uint32_t Address);
uint16_t MyFlash_ReadHalfWord(uint32_t Address);
uint8_t MyFlash_ReadByte(uint32_t Address);
void MyFlash_ErasePage(uint32_t Address);
void MyFlash_EraseAllPage(uint32_t Address);
void MyFlash_WritelWord(uint32_t Address, uint32_t Data);
void MyFlash_WritelHalfWord(uint32_t Address, uint16_t Data);




#endif
