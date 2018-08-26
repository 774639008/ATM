#include "irq.h"
#include <string.h>
#include <s3c2440.h>
#include "type.h"

static irqEvent_t G_IRQEvents[IRQ_MAX];


//�ж����ǳ�ʼ��
void irq_init(void)
{
	 int i; 	

	 memset(G_IRQEvents,0,sizeof(G_IRQEvents));  //��ʼ����Ϣ

	 //��ʼ�����е��жϼĴ���
	 EINTMASK = 0xFFFFFFFF;
	 INTSUBMSK = 0xFFFFFFFF;
	 INTMSK = 0xFFFFFFFF;
	 
	 EINTPEND=  0xFFFFFFFF;
	 SUBSRCPND =  0xFFFFFFFF;
	 SRCPND =  0xFFFFFFFF;
	 INTPND =  0xFFFFFFFF;
	 
	 INTMOD = 0; 

	 //��ʼ��������Ϣ�ṹ��
	 for(i = 0; i < IRQ_MAX; i++)
	 {
	 	G_IRQEvents[i].irqno = i;
		G_IRQEvents[i].parent = -1;
		G_IRQEvents[i].irq = NULL;

		if(i >= IRQ_SUB_EINT4 && i <= IRQ_SUB_EINT7)
		{
			G_IRQEvents[i].parent = IRQ_EINT4_7;
		}
		else if(i >= IRQ_SUB_EINT8 && i <= IRQ_SUB_EINT23)
		{
			G_IRQEvents[i].parent = IRQ_EINT8_23;
		}
		else if(i >= IRQ_SUB_RXD0 && i <= IRQ_SUB_ERR0)
		{
			G_IRQEvents[i].parent = IRQ_UART0;
		}
		else if(i >= IRQ_SUB_RXD1 && i <= IRQ_SUB_ERR1)
		{
			G_IRQEvents[i].parent = IRQ_UART1;
		}
		else if(i >= IRQ_SUB_RXD2 && i <= IRQ_SUB_ERR2)
		{
			G_IRQEvents[i].parent = IRQ_UART2;
		}
		else if(i >= IRQ_SUB_TC && i <= IRQ_SUB_ADC_S)
		{
			G_IRQEvents[i].parent = IRQ_ADC;
		}
		else if(i >= IRQ_SUB_CAM_P && i <= IRQ_SUB_CAM_C)
		{
			G_IRQEvents[i].parent = IRQ_CAM;
		}
		else if(i >= IRQ_SUB_AC97 && i <= IRQ_SUB_WDT)
		{
			G_IRQEvents[i].parent = IRQ_WDT_AC97;
		}
	 }
} 



//�жϰ�װ  		
void irq_install(IRQ_E irqno, IRQHandler irq)
{
  //1.���ʵ�ʵ��жϴ�����
  G_IRQEvents[irqno].irq = irq;

  //2.�򿪶�Ӧ�Ŀ���
  if(irqno >= IRQ_SUB_EINT4 && irqno <= IRQ_SUB_EINT23)
  {
  	BIT_CLR(EINTMASK,(irqno- IRQ_SUB_EINT4 +4));  //���ⲿ��������
	BIT_CLR(INTMSK, G_IRQEvents[irqno].parent);   //�򿪶�Ӧ��һ������
  }
  else if(irqno >= IRQ_SUB_RXD0 && irqno <= IRQ_SUB_WDT)
  {
  	BIT_CLR(INTSUBMSK,(irqno- IRQ_SUB_RXD0));  //���ⲿ��������
	BIT_CLR(INTMSK, G_IRQEvents[irqno].parent);   //�򿪶�Ӧ��һ������ 	
  }
  else
  {
  	BIT_CLR(INTMSK,irqno);  //�򿪶�Ӧ��һ������
  }
}


//�ж�ж��		
void irq_unstall(IRQ_E irqno)
{
  //1.���ʵ�ʵ��жϴ�����
  G_IRQEvents[irqno].irq = NULL;

  //2.�򿪶�Ӧ�Ŀ���
  if(irqno >= IRQ_SUB_EINT4 && irqno <= IRQ_SUB_EINT23)
  {
  	BIT_SET(EINTMASK,(irqno- IRQ_SUB_EINT4 +4));  //���ⲿ��������
	BIT_SET(INTMSK, G_IRQEvents[irqno].parent);   //�򿪶�Ӧ��һ������
  }
  else if(irqno >= IRQ_SUB_RXD0 && irqno <= IRQ_SUB_WDT)
  {
  	BIT_SET(INTSUBMSK,(irqno- IRQ_SUB_RXD0));  //���ⲿ��������
	BIT_SET(INTMSK, G_IRQEvents[irqno].parent);   //�򿪶�Ӧ��һ������ 	
  }
  else
  {
  	BIT_SET(INTMSK,irqno);  //�򿪶�Ӧ��һ������
  }


}
#define EINTIRQ_RUN(start,end)\
  for(i = start; i <= end; i++) \
  {	\
	   if(EINTPEND &(1 << i)) \
	   { \
	   		BIT_SET(EINTPEND,i);  	   /*����δ���ж����*/	\
			if(	G_IRQEvents[IRQ_SUB_EINT4+(i - 4)].irq)	\
			{ \
	   		 G_IRQEvents[IRQ_SUB_EINT4+(i - 4)].irq();\
			}  \
			break;	 \
	   } \
  } break;

#define SUBIRQ_RUN(start,end) \
  for(i = start; i <= end; i++) \
  {	\
	   if(SUBSRCPND &(1 << i)) \
	   { \
	   		BIT_SET(SUBSRCPND,i);  \
			if(	G_IRQEvents[IRQ_SUB_RXD0+i].irq)	\
			{ \
	   		    G_IRQEvents[IRQ_SUB_RXD0+i].irq();\
			} \
			break;	 \
	   } \
  } break;

//�жϷַ�		
void irq_dispatch(void)
{
  int ofs = INTOFFSET;
  int i;

  switch(ofs)
  {
  	case IRQ_EINT4_7:
			EINTIRQ_RUN(4,7);
	case IRQ_EINT8_23:
			EINTIRQ_RUN(8,23);
	case IRQ_WDT_AC97:
		    SUBIRQ_RUN(13,14);
	 case IRQ_CAM:
			SUBIRQ_RUN(11,12);
	case IRQ_ADC:
			SUBIRQ_RUN(9,10);
	case IRQ_UART2:
			SUBIRQ_RUN(6,8);
	case IRQ_UART1:
			SUBIRQ_RUN(3,5);
	case IRQ_UART0:
			SUBIRQ_RUN(0,2);

    default:  //Ĭ��һ���ж�
		if(G_IRQEvents[ofs].irq)
		{
			G_IRQEvents[ofs].irq();
		}
		break;
  }

  //2.һ���ж����
  BIT_SET(SRCPND,ofs);
  BIT_SET(INTPND,ofs);
}  

  



