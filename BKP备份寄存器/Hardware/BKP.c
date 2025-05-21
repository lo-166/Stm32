#include "stm32f10x.h"                  // Device header

void BKP_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
	
	PWR_BackupAccessCmd(ENABLE);

}

void BKP_Write(uint16_t BKP_DRx, uint16_t Byte)
{
	BKP_WriteBackupRegister(BKP_DRx, Byte);
}

uint16_t BKP_Read(uint16_t BKP_DRx)
{
	return BKP_ReadBackupRegister(BKP_DRx);
}
