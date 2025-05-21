#include "stm32f10x.h"                  // Device header
#include <time.h>

uint16_t MyRTC_Time[] = {2025, 1, 1, 23, 59 , 59};

//struct Tm{
//	
//	int tm_sec;   /* seconds after the minute, 0 to 60
//                     (0 - 60 allows for the occasional leap second) */
//    int tm_min;   /* minutes after the hour, 0 to 59 */
//    int tm_hour;  /* hours since midnight, 0 to 23 */
//    int tm_mday;  /* day of the month, 1 to 31 */
//    int tm_mon;   /* months since January, 0 to 11 */
//    int tm_year;  /* years since 1900 */
//    int tm_wday;  /* days since Sunday, 0 to 6 */
//    int tm_yday;  /* days since January 1, 0 to 365 */

//}Tm1;


void RTC_SetTime(void);

void RTC_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
	
	PWR_BackupAccessCmd(ENABLE);
	
	if(0xFFFF != BKP_ReadBackupRegister(BKP_DR1))
	{
		RCC_LSEConfig(RCC_LSE_ON);	
		
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
		
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		RCC_RTCCLKCmd(ENABLE);
		
		RTC_WaitForSynchro();	
		RTC_WaitForLastTask();

		
		RTC_SetPrescaler(32768 - 1);
		RTC_WaitForLastTask();
		
		RTC_SetTime();
		
		BKP_WriteBackupRegister(BKP_DR1, 0xFFFF);
	}	
	else													
	{
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
	}
}



void RTC_SetTime(void)
{
	
	struct tm time_data;
	time_t time_cnt;
	
	time_data.tm_sec = MyRTC_Time[5];
	time_data.tm_min = MyRTC_Time[4];
	time_data.tm_hour = MyRTC_Time[3];
	time_data.tm_mday = MyRTC_Time[2];
	time_data.tm_mon = MyRTC_Time[1] - 1;
	time_data.tm_year = MyRTC_Time[0] - 1900;
	
	time_cnt = mktime(&time_data) - (8 * 60 * 60);
	
	RTC_SetCounter(time_cnt);	
	RTC_WaitForLastTask();
}

void RTC_ReadTime(void)
{
	time_t time_cnt;
	struct tm time_data;

	time_cnt = RTC_GetCounter() + (8 * 60 * 60);
	time_data = *localtime(&time_cnt);
	
	MyRTC_Time[5] = time_data.tm_sec;
	MyRTC_Time[4] = time_data.tm_min;
	MyRTC_Time[3] = time_data.tm_hour;
	MyRTC_Time[2] = time_data.tm_mday;
	MyRTC_Time[1] = time_data.tm_mon + 1;
	MyRTC_Time[0] = time_data.tm_year + 1900;
	
	RTC_WaitForLastTask();
}       


