#ifndef _RTC_H_
#define _RTC_H_

#include "type.h"

#define RTC_BCD2INT(X) (((((X)&0xF0)>>4)*10)+((X)&0xF))
#define RTC_INT2BCD(X) ((((X)/10)<<4)+((X)%10))

typedef struct
{
	u8 tm_sec;
	u8 tm_min;
	u8 tm_hour;
	u8 tm_mday;
	u8 tm_mon;
	u16 tm_year;
	u8 tm_wday;
}TDATE;

void RTC_Init(void);
void RTC_Set(const TDATE *t);
void RTC_Get(TDATE *t);
void RTC_IRQ_TICK_Init(unsigned char tick);
void RTC_timeDisplay(void);
void Alarm_Set(const TDATE *t);

#endif 


