#ifndef __MPU6050_H
#define __MPU6050_H



void MPU6050_WriteReg(uint8_t Address, uint8_t Byte);
uint8_t MPU6050_ReadReg(uint8_t Address);
void MPU6050_Init(void);
MPU6050_GetId();
uint8_t MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ,
						int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ);

	
#endif
