#ifndef __RTC_H
#define __RTC_H

// [0]年 [1]月 [2]日 [3]时 [4]分 [5]秒
extern uint16_t MyRTC_Time[];

void RTC_Init(void);
void RTC_SetTime(void);
void RTC_ReadTime(void);



#endif
