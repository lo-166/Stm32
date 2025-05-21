#include "stm32f10x.h"                  // Device header
#include "W25Q64_Ins.h" 
#include "MySPI.h" 

void W25Q64_Init(void)
{
	MySPI_Init();
}


void W25Q64_W_Enable(void)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_WRITE_ENABLE);
	MySPI_Stop();
}

void W25Q64_R_WaitBsuy(void)
{
	uint16_t timeout = 10000;
	while(timeout)
	{
		timeout--;
	}
}

void W25Q64_R_ID(uint8_t *MID, uint16_t *DID)
{
	W25Q64_R_WaitBsuy();
	MySPI_Start();
	MySPI_SwapByte(W25Q64_MANUFACTURER_DEVICE_ID);
	*MID = MySPI_SwapByte(0xFF);
	*DID = MySPI_SwapByte(0xFF);
	*DID <<= 8;
	*DID |= MySPI_SwapByte(0xFF);
	MySPI_Stop();
}



void W25Q64_PageProgram(uint8_t *ByteArry, uint32_t Address, uint8_t Count)
{
	W25Q64_R_WaitBsuy();
	uint8_t i;
	W25Q64_W_Enable();
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_DATA);
	MySPI_SwapByte(Address << 16);
	MySPI_SwapByte(Address << 8);
	MySPI_SwapByte(Address);
	for(i = 0; i < Count; i++)
	{
		MySPI_SwapByte(ByteArry[i]);
	}
	MySPI_Stop();
}

void W25Q64_R_ReadData(uint8_t *ByteArry, uint32_t Address, uint32_t Count)
{
	W25Q64_R_WaitBsuy();
	uint8_t i;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_DATA);
	MySPI_SwapByte(Address << 16);
	MySPI_SwapByte(Address << 8);
	MySPI_SwapByte(Address);
	for(i = 0; i < Count; i++)
	{
		ByteArry[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	}
	MySPI_Stop();
}

void W25Q64_SectorErase(uint32_t Address)
{
	W25Q64_R_WaitBsuy();
	W25Q64_W_Enable();
	MySPI_Start();
	MySPI_SwapByte(W25Q64_BLOCK_ERASE_32KB);
	MySPI_SwapByte(Address << 16);
	MySPI_SwapByte(Address << 8);
	MySPI_SwapByte(Address);
	MySPI_Stop();
}


