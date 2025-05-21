#ifndef __SERIAL_H
#define __SERIAL_H
#include "stdio.h" 


void Serial_SendByte(uint8_t Byte);
void Serial_Init(void);
void Serial_SendArry(uint8_t *Arry);
void Seiral_SendNumber(uint16_t Number, uint16_t Length);
void Serial_SendString(char *Str);

void Serial_Print(char *format, ...);

uint16_t Serial_GetRxData(void);
uint8_t Serial_GetFlag(void);


#endif
