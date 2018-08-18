#ifndef _PUBLIC_H_
#define _PUBLIC_H_

int glb_putString(char acStr[100], int iMaxlen, int iputType, int isPlainttext);	//明密文函数封装

int gotoxy(int x,int y);															//光标函数封装

int select_interface(int max,int x,int y);											//控制光标移动函数封装

int putNum(char acStr[100],int iMaxlen,int iputType);								//控制输入字符的函数封装

int public_num(char *acBuf);			//输入一个字符的函数封装

int select_quit();						//选择退出函数封装

int select_return();					//选择返回函数封装

void Banktips();						//界面小贴士

char *CurTime(int x,int y,int a);		//选择退出和返回的函数


#endif _PUBLIC_H_