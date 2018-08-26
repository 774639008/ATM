#include <stdio.h>
#include <S3C2440.h>
#include "lcd.h"
#include "irq.h"
#include "uart_cmd.h"
#include <string.h>
#include <stdlib.h>
#include "heap.h"



/*------------------------ Type Declarations ---------------------------------*/
//UART������UART��ص�IO�ڵ����ã�UART�Ĵ������ơ�UART�жϴ������������
#define FCLK	(405000000) //405M
#define HCLK	(101000000) //101M
#define	PCLK	 (50000000)  //50.5M


int UART0_init(int baudrate)
{
	
	//���ò�����
	int nUBRDIV = PCLK/16/baudrate - 1;
	
	// �������ţ���������ģʽ
	GPHCON = 0xA0;
	GPHUP = 0x0C;
 
	//�������ݴ����ʽ����ʼ��UART�߿��ƼĴ���
	//��ͨģʽ����  ����żУ�� 1��ֹͣλ  8���ֽڳ���
	ULCON0 = (0x3);
//	ULCON1 = (0<<6)|(0<<3)|(0<<2)|(3<<0);
//	ULCON2 = (0<<6)|(0<<3)|(0<<2)|(3<<0);

//����ͨ������ģʽ������UART���ƼĴ���
//    [10]       [9]     [8]        [7]        [6]      [5]         [4]           [3:2]        [1:0]
// ʱ��ѡ��,  Tx �ж�,  Rx �ж�, Rx ��ʱʹ��, Rx ����, �ػ�ģʽ, �����ϵ��ź�,  	����ģʽ, 	����ģʽ
//     0          1       0    ,     0          1        0           0     ,       01          01
//   PCLK       ��ƽ    ����       ��ֹ       ����  	����      ��������        �ж� �� ��ѯ
	
	UCON0 = (0x5); //��ѯ���ж�
//	UCON1 = (0<<12)|(2<<10)|(0<<9)|(0<<8)|(0<<7)|(0<<6)|(0<<5)|(0<<4)|(1<<2)|(1<<0);
//	UCON2 = (0<<12)|(2<<10)|(0<<9)|(0<<8)|(0<<7)|(0<<6)|(0<<5)|(0<<4)|(1<<2)|(1<<0);

//����FIFO������
//   		[7:6]               [5:4]         		[3]           [2]        [1]            [0]
//	Tx FIFO��ȴ���   Rx FIFO��ȴ���				����	Tx FIFO��λ		Rx FIFO��λ		FIFOʹ��
//				0					0				/		0				1               1
//    	 ��                 һ�ֽ�				����					��λ			ʹ��
	UFCON0 = (0<<6)|(0<<4)|(0<<2)|(1<<1)|(1<<0);
	//UFCON1 = (0<<6)|(0<<4)|(0<<2)|(1<<1)|(1<<0);
	//UFCON2 = (0<<6)|(0<<4)|(0<<2)|(1<<1)|(1<<0);

	//��������
	UMCON0 = 0;
	//UMCON1 = 0;
	//UMCON2 = 0;

	//����������
	UBRDIV0 = nUBRDIV;
	//UBRDIV1 = nUBRDIV;
	//UBRDIV2 = nUBRDIV;

	return 0;
}


//���ݷ���
int UART0_SendByte(unsigned char cSendChar)
{
	//����ʽ��һֱ�ȴ���ֱ�����ڻ������п���λ�����������ڷ���
	while(!(UTRSTAT0 & 0x2));
	UTXH0 = (int)cSendChar;
	
	return 0;
}

//��������
unsigned char UART0_RecvByte(void)
{
	//����ʽ��һֱ�ȴ���ֱ�������������ٶ�ȡ
	while(!(UTRSTAT0 & 0x1));
	return (unsigned char)URXH0;
}

//���ݷ����Ƿ����
int UART0_IsTransFinish(void)
{
	return (UTRSTAT0 & (1<<2));
}

//���FIFO��������
void UART0_cleanRX(void)
{
    int num = 	UFSTAT0 & 0x1f;   //��ǰFIFO�еĽ�������
    while(num > 0)
    {
        char ch = URXH0;     //ֻҪ��ȡ�üĴ����ʹ�FIFO��ȡ��һ���ֽ�
	    num--;
    }   
}
  
//------------�����ǽ��ա�����һ���ַ���-------------
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


//----------FIFO�ж�ģʽ----------------------
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

	count = UFSTAT0&0x3F;	   //�жϷ���ʱ���ܵ��ֽ���
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
		ReceiveBuffer[ReceiveIndex] = 0;//�������memcpy��ʹ��

	    //�����յ������� 
		uartcmd_run(ReceiveBuffer);
		
		ReceiveIndex = 0;
		flag_Receive_end = 1;//flag_Receive_endΪ���ս�����־��ֵΪ1��ʾһ�����ݽ��ս���
		printf("%s", ReceiveBuffer); //����		
	}
}



//���ڳ�ʼ��
void UART0_InitFIFO(int baudrate)
{
	//���ò�����
	int nUBRDIV = PCLK/16/baudrate - 1;

	GPHCON = 0xA0;
	GPHUP = 0x0C;

	//�������ݴ����ʽ����ʼ��UART�߿��ƼĴ���
	//��ͨģʽ����  ����żУ�� 1��ֹͣλ  8���ֽڳ���
	ULCON0 = (0<<6)|(0<<3)|(0<<2)|(3<<0);

	UCON0 = (0 << 12) | (2 << 10) |  (1 << 7) | (1 << 2) | (1 << 0);      //��ѯ��ʽΪ��ѯ���жϣ�ʱ��ѡ��ΪPCLK       
	UFCON0 = (2 << 6) | (3 << 4) | (0 << 3) | (1 << 2) | (1 << 1) | (1 << 0);   //����FIFO�����ݷ����ж�ģʽ(0�ֽ�),���ݽ����ж�ģʽ��32�ֽڣ�    
	UMCON0 = 0x00;    //��ʹ������    
	UBRDIV0 = nUBRDIV;	  //������Ϊ115200,PCLK = 50MHz 

	//��װ�жϴ�����
	irq_install(IRQ_SUB_RXD0, UART0_IRQ_Receive);  //����ʹ��FIFO�ж�
	//irq_install(IRQ_SUB_TXD0, UART0_IRQ_Send); //���÷����ж�
}


//�ض���
int fputc(int ch,FILE *p)  //����Ĭ�ϵģ���ʹ��printf����ʱ�Զ�����
{
	UART0_SendByte((unsigned char)ch);	
	return ch;
}

