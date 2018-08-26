#include <s3c2440.h>
#include "timer.h"
#include "irq.h"


void timer0_init(int pre, MUX_E mux, int ms, IRQHandler irq)
{
	//1. 设置预分频
	TCFG0 &= ~(0xff << 0); //249
	TCFG0 |= (pre & 0xff) << 0;
	
	//2. 设置固定分频
	TCFG1 &= ~(0xf << 0); //8分频
	TCFG1 |= (mux << 0);
	
	//3. 设置 TCNTB，计数值，根据延时来计算的
	TCNTB0 = ms * 25;  //ms * 1000 / 40(us)
	
	//4. 设置手动更新位，把TCNTB的值写入TCNT
	TCON |= (1 << 1); //定时器0 设置手动更新
	
	//5. 设置自动重装载，并且清除手动更新位
	TCON |= (1 << 3); // 定时器0设置为自动重装载
	TCON &= ~(1 << 1); //清除手动重装载
	
	//设置好定时器超时事件
	irq_install(IRQ_TIMER0, irq);
	
	//6. 启动定时器0
	TCON |= (1 << 0);
	
}

/*
	时间计算： 
		PCLK = 50M, PCLK/(precalu+1)/(2 << (mux)) = Pin 输入的频率
		输出的时间： ms 毫秒
	count = 50000 * ms / (precalu+1)/(2 << (mux))
*/

void timer_create(TIMER_T *pstConfig)
{
	unsigned short count = 50000 * pstConfig->ms / (pstConfig->precalu + 1) / (2 << (pstConfig->mux));
	
	//1. 设置预分频
	if(pstConfig->id == TIMER_ID0 || pstConfig->id == TIMER_ID1)
	{
		TCFG0 &= ~(0xff); //249
		TCFG0 |= (pstConfig->precalu & 0xff);
	}
	else
	{
		TCFG0 &= ~(0xff << 8); //249
		TCFG0 |= ((pstConfig->precalu & 0xff) << 8);
	}
	
	
	//2. 设置固定分频
	TCFG1 &= ~(0xf << (pstConfig->id << 2)); //8分频
	TCFG1 |= (pstConfig->mux << (pstConfig->id << 2));
	
	//3. 设置 TCNTB，计数值，根据延时来计算的
	switch(pstConfig->id)
	{
		case TIMER_ID0 :
			TCNTB0 = count; 
		break;
		case TIMER_ID1:
			TCNTB1 = count; 
		break;
		case TIMER_ID2:
			TCNTB2 = count; 
		break;
		case TIMER_ID3:
			TCNTB3 = count; 
		break;
		case TIMER_ID4:
			TCNTB4 = count; 
		break;
	}
	
	//4. 设置手动更新位，把TCNTB的值写入TCNT
	if(pstConfig->id == TIMER_ID0)
	{
		TCON |= (1 << 1); //定时器0 设置手动更新
		
		//5. 设置自动重装载，并且清除手动更新位
		TCON |= (1 << 3); // 定时器0设置为自动重装载
		TCON &= ~(1 << 1); //清除手动重装载
	}
	else
	{
		BIT_SET(TCON, (pstConfig->id * 4 + 5));//定时器0 设置手动更新
		
		//5. 设置自动重装载，并且清除手动更新位
		if(pstConfig->bAutoload)
		{
			if(pstConfig->id == TIMER_ID4)
			{
				BIT_SET(TCON, 22);
			}
			else
			{
				BIT_SET(TCON, (pstConfig->id * 4 + 7));// 定时器0设置为自动重装载
			}
		}
		else
		{
			if(pstConfig->id == TIMER_ID4)
			{
				BIT_CLR(TCON, 22);
			}
			else
			{
				BIT_CLR(TCON, (pstConfig->id * 4 + 7));// 定时器0设置为自动重装载
			}
		}
		BIT_CLR(TCON, (pstConfig->id * 4 + 5)); //清除手动重装载
	}
	
	//设置好定时器超时事件
	irq_install((IRQ_E)(pstConfig->id  + IRQ_TIMER0), pstConfig->irq);
	

	
}

void timer_start(TIMER_ID_E timer)
{
	//6. 启动定时器0
	if(timer == TIMER_ID0)	
		BIT_SET(TCON, 0);
	else
		BIT_SET(TCON, (timer*4 + 4));
}

void timer_stop(TIMER_ID_E timer)
{
	if(timer == TIMER_ID0)	
		BIT_CLR(TCON, 0);
	else
		BIT_CLR(TCON, (timer*4 + 4));	
}

void timer_destroy(TIMER_ID_E timer)
{
	timer_stop(timer);
	irq_unstall((IRQ_E)(timer + IRQ_TIMER0));
}


