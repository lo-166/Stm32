#include "stm32f10x.h"                  // Device header
#include "I2C.h" 
#include "MPU6050_Reg.h" 

#define MPU6050_ADDRESS 0xD0


// 指定写
void MPU6050_WriteReg(uint8_t Address, uint8_t Byte)
{
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Address);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Byte);
	MyI2C_Stop();
}

uint8_t MPU6050_ReadReg(uint8_t Address)
{
	uint8_t Data;
	// 指定写 -> 指定地址
	MyI2C_Start();
	
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Address);
	MyI2C_ReceiveAck();
	// 当前读 -> 修改读写模式
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS | 0x01);
	MyI2C_ReceiveAck();
	
	Data = MyI2C_ReceiveByte();
	MyI2C_SendAck(1);
	
	MyI2C_Stop();
	return Data;

}

uint8_t MPU6050_GetId(void)
{	
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

uint8_t MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ,
						int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
	uint8_t i, j, Data[15];
	
	for(i = 0x3B; i < 0x49; i++)
	{			
		if(0x41 == i)
		{
			i = 0x43;
		}
		for(j = 0; j < 13; i++)
		{
			Data[j] = MPU6050_ReadReg(i);
		}
	}
	
	*AccX = (Data[0] << 8) | Data[1];
	*AccY = (Data[2] << 8) | Data[3];
	*AccZ = (Data[4] << 8) | Data[5];
	*GyroX = (Data[6] << 8) | Data[7];
	*GyroY = (Data[8] << 8) | Data[9];
	*GyroZ = (Data[10] << 8) | Data[11];
	
}

void MPU6050_Init(void)
{
	MyI2C_Init();
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);
	
}
