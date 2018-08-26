#ifndef __TIMER_H__
#define __TIMER_H__

#include "irq.h"
#include "type.h"

// ��Ƶ��
typedef enum 
{
	MUX2 = 0,
	MUX4,
	MUX8,
	MUX16
	
}MUX_E;


// ��ʱ���ı��ID
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
	unsigned char precalu; //Ԥ��Ƶ
	MUX_E mux; //�̶���Ƶ
	int bAutoload; //�Զ���װ��
	unsigned short ms; //��ʱʱ�䣬ms
	IRQHandler irq;
	
}TIMER_T;

/******************************************************************

  *  �������ƣ� timer_create
  
	*  ���������� 
	*		������ʱ��
	*  ����˵��
	*		@id����ʱ�������
    *		@prescaler��Ԥ��Ƶֵ
    *		@mux���̶���Ƶ��
	*		@ms����ʱ��ʱ�䣬��λ(ms)
	*		@bAuto���Ƿ��Զ���װ�أ�0�����Զ����أ�1���Զ�����
	*		@handler���жϴ�����
	*  ����ֵ 
	*     	��  
******************************************************************/
void timer_create(TIMER_T *pstConfig);

void timer_start(TIMER_ID_E timer);
void timer_stop(TIMER_ID_E timer);
void timer_destroy(TIMER_ID_E timer);

void timer0_init(int pre, MUX_E mux, int ms, IRQHandler irq);



#endif /*__TIMER_H__ */


