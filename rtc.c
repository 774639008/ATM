#include <s3c2440.h>
#include <stdio.h>
#include "rtc.h"
#include "irq.h"
#include "lcd.h"
#include "led.h"
#include "bee.h"



void RTC_Init()
{
	//RTC初始化 
  TDATE t={0,0,0,10,5,2018};

	
	GPBCON |= (0x1 << 10);//将所有的led1（GPB5）设置为输出模式
	GPBDAT |= (0x1 << 5);
	
	RTC_Set(&t);
	
}
//获取RTC时间
void RTC_Get(TDATE *t)
{
	RTCCON |= 1 << 0;    //先打开RTC控制器使能,设置完时间后必须禁止RTC控制器使能

	t->tm_year = RTC_BCD2INT(BCDYEAR) + 2000;
	t->tm_mon = RTC_BCD2INT(BCDMON);
	t->tm_mday = RTC_BCD2INT(BCDDATE);
	t->tm_hour = RTC_BCD2INT(BCDHOUR);
	t->tm_min = RTC_BCD2INT(BCDMIN);
	t->tm_sec = RTC_BCD2INT(BCDSEC);
	t->tm_wday = RTC_BCD2INT(BCDDAY);
	
	RTCCON &= ~(1 << 0);
}
//设置RTC时间
void RTC_Set(const TDATE *t)
{
	RTCCON |= 1 << 0;    //先打开RTC控制器使能,设置完时间后必须禁止RTC控制器使能

	BCDYEAR = RTC_INT2BCD(t->tm_year - 2000);
	BCDMON  = RTC_INT2BCD(t->tm_mon);
	BCDDATE  = RTC_INT2BCD(t->tm_mday);
	BCDHOUR = RTC_INT2BCD(t->tm_hour);
	BCDMIN  = RTC_INT2BCD(t->tm_min);
	BCDSEC  = RTC_INT2BCD(t->tm_sec);
	BCDDAY = RTC_INT2BCD(t->tm_wday);

	RTCCON &= ~(1 << 0);
}

/******************************** 
* 
*   TICK中断初始化
* 
*********************************/ 
void RTC_IRQ_TICK_Init(unsigned char tick)  
{  
	//中断安装函数
	irq_install(IRQ_TICK, RTC_timeDisplay);       
	TICNT=tick | 0x80;    //一般设置tick(127)周期1s ,开启Tick(第7位使能/禁止)   
} 			

/******************************** 
* 
*   显示实时时间
* 
*********************************/ 
void RTC_timeDisplay()  
{  
	TDATE t;
	char ch[50];
	char ch1[50];

	RTC_Get(&t);  //读取RT时间
	sprintf(ch,"%d-%02d-%02d", t.tm_year,t.tm_mon,t.tm_mday);
	sprintf(ch1,"%02d:%02d:%02d",t.tm_hour,t.tm_min,t.tm_sec);
    lcd_print(295,5,ch, BLUE, WHITE); 
	lcd_print(395,5,ch1, RED, WHITE);
}


//设置ALARM时间
void Alarm_Set(const TDATE *t)
{
	RTCCON |= 1 << 0;    //先打开RTC控制器使能,设置完时间后必须禁止RTC控制器使能

	ALMYEAR = RTC_INT2BCD(t->tm_year - 2000);
	ALMMON  = RTC_INT2BCD(t->tm_mon);
	ALMDATE  = RTC_INT2BCD(t->tm_mday);
	ALMHOUR = RTC_INT2BCD(t->tm_hour);
	ALMMIN  = RTC_INT2BCD(t->tm_min);
	ALMSEC  = RTC_INT2BCD(t->tm_sec);	 
	BCDDATE = RTC_INT2BCD(t->tm_wday);
	RTCALM = 0xFF;

	RTCCON &= ~(1 << 0);
}



