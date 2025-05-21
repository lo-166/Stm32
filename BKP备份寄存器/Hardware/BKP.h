#ifndef __LED_H
#define __LED_H


void BKP_Init(void);

void BKP_Write(uint16_t BKP_DRx, uint16_t Byte);

uint16_t BKP_Read(uint16_t BKP_DRx);


#endif
