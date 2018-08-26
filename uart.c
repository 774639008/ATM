#include <stdio.h>
#include <S3C2440.h>
#include "lcd.h"
#include "irq.h"
#include "uart_cmd.h"
#include <string.h>
#include <stdlib.h>
#include "heap.h"



/*------------------------ Type Declarations ---------------------------------*/
//UART驱动由UART相关的IO口的配置，UART寄存器控制。UART中断处理三部分组成
#define FCLK	(405000000) //405M
#define HCLK	(101000000) //101M
#define	PCLK	 (50000000)  //50.5M


int UART0_init(int baudrate)
{
	
	//设置波特率
	int nUBRDIV = PCLK/16/baudrate - 1;
	
	// 设置引脚，配置上拉模式
	GPHCON = 0xA0;
	GPHUP = 0x0C;
 
	//设置数据传输格式：初始化UART线控制寄存器
	//普通模式操作  无奇偶校验 1个停止位  8个字节长度
	ULCON0 = (0x3);
//	ULCON1 = (0<<6)|(0<<3)|(0<<2)|(3<<0);
//	ULCON2 = (0<<6)|(0<<3)|(0<<2)|(3<<0);

//设置通道工作模式：设置UART控制寄存器
//    [10]       [9]     [8]        [7]        [6]      [5]         [4]           [3:2]        [1:0]
// 时钟选择,  Tx 中断,  Rx 中断, Rx 超时使能, Rx 错误, 回环模式, 发出断点信号,  	传输模式, 	接收模式
//     0          1       0    ,     0          1        0           0     ,       01          01
//   PCLK       电平    脉冲       禁止       生成  	正常      正常传输        中断 或 轮询
	
	UCON0 = (0x5); //轮询或中断
//	UCON1 = (0<<12)|(2<<10)|(0<<9)|(0<<8)|(0<<7)|(0<<6)|(0<<5)|(0<<4)|(1<<2)|(1<<0);
//	UCON2 = (0<<12)|(2<<10)|(0<<9)|(0<<8)|(0<<7)|(0<<6)|(0<<5)|(0<<4)|(1<<2)|(1<<0);

//设置FIFO控制器
//   		[7:6]               [5:4]         		[3]           [2]        [1]            [0]
//	Tx FIFO深度触发   Rx FIFO深度触发				保留	Tx FIFO复位		Rx FIFO复位		FIFO使能
//				0					0				/		0				1               1
//    	 空                 一字节				正常					复位			使能
	UFCON0 = (0<<6)|(0<<4)|(0<<2)|(1<<1)|(1<<0);
	//UFCON1 = (0<<6)|(0<<4)|(0<<2)|(1<<1)|(1<<0);
	//UFCON2 = (0<<6)|(0<<4)|(0<<2)|(1<<1)|(1<<0);

	//流控设置
	UMCON0 = 0;
	//UMCON1 = 0;
	//UMCON2 = 0;

	//波特率设置
	UBRDIV0 = nUBRDIV;
	//UBRDIV1 = nUBRDIV;
	//UBRDIV2 = nUBRDIV;

	return 0;
}


//数据发送
int UART0_SendByte(unsigned char cSendChar)
{
	//阻塞式，一直等待，直到串口缓冲区有空闲位并发送数据在返回
	while(!(UTRSTAT0 & 0x2));
	UTXH0 = (int)cSendChar;
	
	return 0;
}

//接收数据
unsigned char UART0_RecvByte(void)
{
	//阻塞式，一直等待，直到串口有数据再读取
	while(!(UTRSTAT0 & 0x1));
	return (unsigned char)URXH0;
}

//数据发送是否完成
int UART0_IsTransFinish(void)
{
	return (UTRSTAT0 & (1<<2));
}

//清空FIFO接收数据
void UART0_cleanRX(void)
{
    int num = 	UFSTAT0 & 0x1f;   //当前FIFO中的接收数据
    while(num > 0)
    {
        char ch = URXH0;     //只要读取该寄存器就从FIFO中取出一个字节
	    num--;
    }   
}
  
//------------下面是接收、发送一个字符串-------------
int UART0_RecvString(unsigned char * buf, int len)
{
    int i = 0;
    while(i < len)
	{
	   buf[i++] = UART0_RecvByte();
	}

	return i;
}

int UART0_SendString(unsigned char * buf, int len)
{
	int i;
	
  for(i = 0; i < len; i++)
	{
	   UART0_SendByte(buf[i]);
	}

	return i;
}


//----------FIFO中断模式----------------------
int ReceiveIndex = 0;
char ReceiveBuffer[200] = {0};
int flag_Receive_end = 0;
int count2 = 0;
unsigned char *p = (unsigned char*)0x31000000;	

 
static void UART0_IRQ_Receive(void)
{ 
	char temp ;
	char count, i;
	//p = xmalloc(480*272*3);

	count = UFSTAT0&0x3F;	   //中断发生时接受的字节数
	for(i = 0; i < count; i++)
	{
		temp = URXH0;
		ReceiveBuffer[ReceiveIndex] = temp;
		ReceiveIndex++;
	}
	
	memcpy(p+count2,ReceiveBuffer,32);
	count2+=count;
//	gg[0]=p;
//	UART0_RecvString((unsigned char*)(0x31000000),count);	
	//	printf("%d",count2);

	//page++;
//  p+=480*272*2*page;
	ReceiveIndex=0;
	
	if(count < 32)
	{
		ReceiveBuffer[ReceiveIndex] = 0;//数组或者memcpy的使用

	    //处理收到的数据 
		uartcmd_run(ReceiveBuffer);
		
		ReceiveIndex = 0;
		flag_Receive_end = 1;//flag_Receive_end为接收结束标志，值为1表示一次数据接收结束
		printf("%s", ReceiveBuffer); //回送		
	}
}



//串口初始化
void UART0_InitFIFO(int baudrate)
{
	//设置波特率
	int nUBRDIV = PCLK/16/baudrate - 1;

	GPHCON = 0xA0;
	GPHUP = 0x0C;

	//设置数据传输格式：初始化UART线控制寄存器
	//普通模式操作  无奇偶校验 1个停止位  8个字节长度
	ULCON0 = (0<<6)|(0<<3)|(0<<2)|(3<<0);

	UCON0 = (0 << 12) | (2 << 10) |  (1 << 7) | (1 << 2) | (1 << 0);      //查询方式为轮询或中断；时钟选择为PCLK       
	UFCON0 = (2 << 6) | (3 << 4) | (0 << 3) | (1 << 2) | (1 << 1) | (1 << 0);   //启用FIFO，数据发送中断模式(0字节),数据接收中断模式（32字节）    
	UMCON0 = 0x00;    //不使用流控    
	UBRDIV0 = nUBRDIV;	  //波特率为115200,PCLK = 50MHz 

	//安装中断处理函数
	irq_install(IRQ_SUB_RXD0, UART0_IRQ_Receive);  //接收使用FIFO中断
	//irq_install(IRQ_SUB_TXD0, UART0_IRQ_Send); //不用发送中断
}


//重定向
int fputc(int ch,FILE *p)  //函数默认的，在使用printf函数时自动调用
{
	UART0_SendByte((unsigned char)ch);	
	return ch;
}

