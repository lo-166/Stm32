#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "BKP.h"
#include "Key.h"
#include "time.h"
#include "RTC.h"


uint8_t KeyNum;

uint16_t ArryWrite[] = {1, 1};
uint16_t ArryRead[2] = {0};

int main(void)
{
	OLED_Init();
	Key_Init();
	RTC_Init();
	BKP_Init();
		/*开启时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);		//开启PWR的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);		//开启BKP的时钟
	
	/*备份寄存器访问使能*/
	PWR_BackupAccessCmd(ENABLE);
	
	OLED_ShowString(1, 1, "bkpW:");
	OLED_ShowString(2, 1, "bkpR:");
	
	time_t TimeNum;
	struct tm time_nct;
	
	while(1)
	{
		KeyNum = Key_GetNum();
		if(1 == KeyNum)
		{
			ArryWrite[0] ++;
			ArryWrite[1] ++;
			
			BKP_Write(BKP_DR1, ArryWrite[0]);
			BKP_Write(BKP_DR2, ArryWrite[1]);
			
			OLED_ShowHexNum(1, 6, ArryWrite[0], 4);
			OLED_ShowHexNum(1, 12, ArryWrite[1], 4);
		}
		
		ArryRead[0] = BKP_Read(BKP_DR1);
		ArryRead[1] = BKP_Read(BKP_DR2);
		
		OLED_ShowHexNum(2, 6, ArryRead[0], 4);
		OLED_ShowHexNum(2, 12, ArryRead[1], 4);

	}
}
