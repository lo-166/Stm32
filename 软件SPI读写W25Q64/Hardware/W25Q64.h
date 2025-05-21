#ifndef __W25Q64_H
#define __W25Q64_H

void W25Q64_Init(void);
void W25Q64_SectorErase(uint32_t Address);
void W25Q64_R_ReadData(uint8_t *ByteArry, uint32_t Address, uint32_t Count);
void W25Q64_PageProgram(uint8_t *ByteArry, uint32_t Address, uint8_t Count);
void W25Q64_W_Enable(void);
void W25Q64_R_WaitBsuy(void);
void W25Q64_R_ID(uint8_t *MID, uint16_t *DID);

#endif
