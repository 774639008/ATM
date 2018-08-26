#ifndef __TIMER_H__
#define __TIMER_H__

#include "irq.h"
#include "type.h"

// 分频比
typedef enum 
{
	MUX2 = 0,
	MUX4,
	MUX8,
	MUX16
	
}MUX_E;


// 定时器的编号ID
typedef enum
{
	TIMER_ID0,
	TIMER_ID1,
	TIMER_ID2,
	TIMER_ID3,
	TIMER_ID4,

}TIMER_ID_E;


typedef struct {
	
	TIMER_ID_E id;
	unsigned char precalu; //预分频
	MUX_E mux; //固定分频
	int bAutoload; //自动重装载
	unsigned short ms; //定时时间，ms
	IRQHandler irq;
	
}TIMER_T;

/******************************************************************

  *  函数名称： timer_create
  
	*  功能描述： 
	*		创建定时器
	*  参数说明
	*		@id：定时器的序号
    *		@prescaler：预分频值
    *		@mux：固定分频比
	*		@ms：定时的时间，单位(ms)
	*		@bAuto：是否自动重装载，0：非自动加载，1：自动加载
	*		@handler：中断处理函数
	*  返回值 
	*     	无  
******************************************************************/
void timer_create(TIMER_T *pstConfig);

void timer_start(TIMER_ID_E timer);
void timer_stop(TIMER_ID_E timer);
void timer_destroy(TIMER_ID_E timer);

void timer0_init(int pre, MUX_E mux, int ms, IRQHandler irq);



#endif /*__TIMER_H__ */


