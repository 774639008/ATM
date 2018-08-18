#ifndef _HEAD_H_
#define _HEAD_H_

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define KEY_UP 72			//�궨�����ϰ���Ϊ 72
#define KEY_LEFT 75			//�궨�����󰴼�Ϊ 75
#define KEY_DOWN 77			//�궨�����°���Ϊ 77
#define KEY_RIGHT 80		//�궨�����Ұ���Ϊ 80
#define KEY_ESC 27			//�궨��ESC����Ϊ 27

//#define DEBUG				��ӡ�˵�ʱ���е���

//����һ���˻�������Ϣ�ṹ��
typedef struct per
{
	char szUsername[20];			///�û���
	char szPassword[7];				///����	
	float fMoney;					//���
	int iRole;						//���
	int ID;							//ID
	int AccountNumber;				//�����˺�
	int iVilid;						//��Чֵ
}Person;

//����һ���˵�������Ϣ�ṹ��
typedef struct savingrecord
{
	int rank;						//���к�
	int sum;						//���׶�
	int balance;					//���
	char date[20];					//���ʱ��
	int from;						//��Դ
	int num;						//�˺�
	int way;						//��ȡת��״̬
}Trade;

int main();			//���������� ��Ҫ���õ�

#endif _HEAD_H_