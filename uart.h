#ifndef __UART_H_
#define __UART_H_

#include "stdio.h"

int UART0_init(int baudrate);

//数据发送
int UART0_SendByte(unsigned char cSendChar);

//接收数据
unsigned char UART0_RecvByte(void);

// 数组发送和接收
int UART0_SendString(unsigned char* buf, int len);
int UART0_RecvString(unsigned char * buf, int len);


// printf重定向到串口，减少串口发送麻烦
int fputc(int ch, FILE *p);  //函数默认的，在使用printf函数时自动调用



// FIFO中断模式
//串口初始化
void UART0Init_FIFO(int baudrate);




#endif /* __UART_H_ */
