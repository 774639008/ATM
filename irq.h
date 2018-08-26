#ifndef __IRQ_H_
#define __IRQ_H_

typedef enum
{
	//32��һ���ж�
	IRQ_EINT0 = 0,
	IRQ_EINT1 = 1,
	IRQ_EINT2 = 2,
	IRQ_EINT3 = 3,
	IRQ_EINT4_7,			//�ж����ⲿ�ж�
	IRQ_EINT8_23,			//�ж����ⲿ�ж�
	IRQ_CAM,
	IRQ_BATT_FLT,
	IRQ_TICK,
	IRQ_WDT_AC97,	   	    //�ж����ڲ��ж�
	IRQ_TIMER0,
	IRQ_TIMER1,
	IRQ_TIMER2,
	IRQ_TIMER3,
	IRQ_TIMER4,
	IRQ_UART2,	 			//�ж����ڲ��ж�
	IRQ_LCD,
	IRQ_DMA0,
	IRQ_DMA1,
	IRQ_DMA2,
	IRQ_DMA3,
	IRQ_SDI,
	IRQ_SPI0,
	IRQ_UART1,			    //�ж����ڲ��ж�
	IRQ_UFCON,
	IRQ_USBD,
	IRQ_USBH,
	IRQ_IIC,
	IRQ_UART0,		 		//�ж����ڲ��ж�
	IRQ_SPI1,
	IRQ_RTC,
	IRQ_ADC,                 //�ж����ڲ��ж�

	//�����Ƕ����ⲿ���ж�
	IRQ_SUB_EINT4 = 32,	  //IRQ_SUB_EINT4-7��Ӧһ���ж�
	IRQ_SUB_EINT5,
	IRQ_SUB_EINT6,
	IRQ_SUB_EINT7,

    IRQ_SUB_EINT8,
	IRQ_SUB_EINT9,
	IRQ_SUB_EINT10,
	IRQ_SUB_EINT11,
	IRQ_SUB_EINT12,
	IRQ_SUB_EINT13,
	IRQ_SUB_EINT14,
	IRQ_SUB_EINT15,
	IRQ_SUB_EINT16,
	IRQ_SUB_EINT17,
	IRQ_SUB_EINT18,
	IRQ_SUB_EINT19,
	IRQ_SUB_EINT20,
	IRQ_SUB_EINT21,
	IRQ_SUB_EINT22,
	IRQ_SUB_EINT23,

	//�����Ƕ����ڲ��ж�
	IRQ_SUB_RXD0 = 52,
	IRQ_SUB_TXD0,
	IRQ_SUB_ERR0,

	IRQ_SUB_RXD1,
	IRQ_SUB_TXD1,
	IRQ_SUB_ERR1,

	IRQ_SUB_RXD2,
	IRQ_SUB_TXD2,
	IRQ_SUB_ERR2,

	IRQ_SUB_TC,
	IRQ_SUB_ADC_S,

	IRQ_SUB_CAM_P,
	IRQ_SUB_CAM_C,

	IRQ_SUB_AC97,
	IRQ_SUB_WDT,

	IRQ_MAX,

}IRQ_E;


//2.���ݽṹ��
typedef void (*IRQHandler)(void);
typedef struct irqEvent_s
{
	int irqno;   //�ж�Դ
	int parent;   //�����ж϶�Ӧ��һ���жϺ�

	IRQHandler irq;
    void (*irqFun)(void);	//����һ���жϵĴ�����

}irqEvent_t;


void irq_init(void);   		//�ж����ǳ�ʼ��
void irq_install(IRQ_E irqno, IRQHandler irq);		//�жϰ�װ
void irq_unstall(IRQ_E irqno);		//�ж�ж��
void irq_dispatch(void);    //�жϷַ�

#endif 

