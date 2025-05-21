#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "W25Q64.h"

uint8_t MID;
uint16_t DID;
uint8_t WriteArry[4] = {0xA1, 0xB1, 0xC1, 0xD1};
uint8_t ReadArry[10] = {0};

int main(void)
{
	OLED_Init();
	W25Q64_Init();

	OLED_ShowString(1, 1, "MID:   DID:");
	OLED_ShowString(2, 1, "W:");
	OLED_ShowString(3, 1, "R:");
	// 查设备ID	
	W25Q64_R_ID(&MID, &DID);
	OLED_ShowHexNum(1, 1, MID, 2);
	OLED_ShowHexNum(1, 3, DID, 4);
	
	W25Q64_SectorErase(0x000000);
	W25Q64_PageProgram(WriteArry, 0x000000, 4);
	W25Q64_R_ReadData(ReadArry, 0x000000, 4);

	
	OLED_ShowHexNum(2, 3, WriteArry[0], 2);
	OLED_ShowHexNum(2, 6, WriteArry[1], 2);
	OLED_ShowHexNum(2, 9, WriteArry[2], 2);
	OLED_ShowHexNum(2, 11, WriteArry[3], 2);
	
	OLED_ShowHexNum(3, 3, ReadArry[0], 2);
	OLED_ShowHexNum(3, 6, ReadArry[1], 2);
	OLED_ShowHexNum(3, 9, ReadArry[2], 2);
	OLED_ShowHexNum(3, 11, ReadArry[3], 2);
while(1)
{
}
}
