#ifndef __UART_H_
#define __UART_H_

#include "stdio.h"

int UART0_init(int baudrate);

//���ݷ���
int UART0_SendByte(unsigned char cSendChar);

//��������
unsigned char UART0_RecvByte(void);

// ���鷢�ͺͽ���
int UART0_SendString(unsigned char* buf, int len);
int UART0_RecvString(unsigned char * buf, int len);


// printf�ض��򵽴��ڣ����ٴ��ڷ����鷳
int fputc(int ch, FILE *p);  //����Ĭ�ϵģ���ʹ��printf����ʱ�Զ�����



// FIFO�ж�ģʽ
//���ڳ�ʼ��
void UART0Init_FIFO(int baudrate);




#endif /* __UART_H_ */
