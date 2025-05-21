#ifndef __I2C_H
#define __I2C_H

void MyI2C_Init(void);

uint8_t MyI2C_ReceiveAck(void);
void MyI2C_SendAck(uint8_t Ackbit);
	
uint8_t MyI2C_ReceiveByte(void);
void MyI2C_SendByte(uint8_t Address);
	
void MyI2C_Stop(void);
void MyI2C_Start(void);
	
#endif
