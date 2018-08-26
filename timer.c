#include <s3c2440.h>
#include "timer.h"
#include "irq.h"


void timer0_init(int pre, MUX_E mux, int ms, IRQHandler irq)
{
	//1. ����Ԥ��Ƶ
	TCFG0 &= ~(0xff << 0); //249
	TCFG0 |= (pre & 0xff) << 0;
	
	//2. ���ù̶���Ƶ
	TCFG1 &= ~(0xf << 0); //8��Ƶ
	TCFG1 |= (mux << 0);
	
	//3. ���� TCNTB������ֵ��������ʱ�������
	TCNTB0 = ms * 25;  //ms * 1000 / 40(us)
	
	//4. �����ֶ�����λ����TCNTB��ֵд��TCNT
	TCON |= (1 << 1); //��ʱ��0 �����ֶ�����
	
	//5. �����Զ���װ�أ���������ֶ�����λ
	TCON |= (1 << 3); // ��ʱ��0����Ϊ�Զ���װ��
	TCON &= ~(1 << 1); //����ֶ���װ��
	
	//���úö�ʱ����ʱ�¼�
	irq_install(IRQ_TIMER0, irq);
	
	//6. ������ʱ��0
	TCON |= (1 << 0);
	
}

/*
	ʱ����㣺 
		PCLK = 50M, PCLK/(precalu+1)/(2 << (mux)) = Pin �����Ƶ��
		�����ʱ�䣺 ms ����
	count = 50000 * ms / (precalu+1)/(2 << (mux))
*/

void timer_create(TIMER_T *pstConfig)
{
	unsigned short count = 50000 * pstConfig->ms / (pstConfig->precalu + 1) / (2 << (pstConfig->mux));
	
	//1. ����Ԥ��Ƶ
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
	
	
	//2. ���ù̶���Ƶ
	TCFG1 &= ~(0xf << (pstConfig->id << 2)); //8��Ƶ
	TCFG1 |= (pstConfig->mux << (pstConfig->id << 2));
	
	//3. ���� TCNTB������ֵ��������ʱ�������
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
	
	//4. �����ֶ�����λ����TCNTB��ֵд��TCNT
	if(pstConfig->id == TIMER_ID0)
	{
		TCON |= (1 << 1); //��ʱ��0 �����ֶ�����
		
		//5. �����Զ���װ�أ���������ֶ�����λ
		TCON |= (1 << 3); // ��ʱ��0����Ϊ�Զ���װ��
		TCON &= ~(1 << 1); //����ֶ���װ��
	}
	else
	{
		BIT_SET(TCON, (pstConfig->id * 4 + 5));//��ʱ��0 �����ֶ�����
		
		//5. �����Զ���װ�أ���������ֶ�����λ
		if(pstConfig->bAutoload)
		{
			if(pstConfig->id == TIMER_ID4)
			{
				BIT_SET(TCON, 22);
			}
			else
			{
				BIT_SET(TCON, (pstConfig->id * 4 + 7));// ��ʱ��0����Ϊ�Զ���װ��
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
				BIT_CLR(TCON, (pstConfig->id * 4 + 7));// ��ʱ��0����Ϊ�Զ���װ��
			}
		}
		BIT_CLR(TCON, (pstConfig->id * 4 + 5)); //����ֶ���װ��
	}
	
	//���úö�ʱ����ʱ�¼�
	irq_install((IRQ_E)(pstConfig->id  + IRQ_TIMER0), pstConfig->irq);
	

	
}

void timer_start(TIMER_ID_E timer)
{
	//6. ������ʱ��0
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


