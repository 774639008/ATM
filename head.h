#ifndef _HEAD_H_
#define _HEAD_H_

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define KEY_UP 72			//宏定义向上按键为 72
#define KEY_LEFT 75			//宏定义向左按键为 75
#define KEY_DOWN 77			//宏定义向下按键为 77
#define KEY_RIGHT 80		//宏定义向右按键为 80
#define KEY_ESC 27			//宏定义ESC按键为 27

//#define DEBUG				打印账单时进行调试

//定义一个账户基本信息结构体
typedef struct per
{
	char szUsername[20];			///用户名
	char szPassword[7];				///密码	
	float fMoney;					//余额
	int iRole;						//身份
	int ID;							//ID
	int AccountNumber;				//银行账号
	int iVilid;						//有效值
}Person;

//定义一个账单基本信息结构体
typedef struct savingrecord
{
	int rank;						//序列号
	int sum;						//交易额
	int balance;					//余额
	char date[20];					//存款时间
	int from;						//来源
	int num;						//账号
	int way;						//存取转的状态
}Trade;

int main();			//返回主函数 需要调用到

#endif _HEAD_H_