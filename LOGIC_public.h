#ifndef _PUBLIC_H_
#define _PUBLIC_H_

int glb_putString(char acStr[100], int iMaxlen, int iputType, int isPlainttext);	//�����ĺ�����װ

int gotoxy(int x,int y);															//��꺯����װ

int select_interface(int max,int x,int y);											//���ƹ���ƶ�������װ

int putNum(char acStr[100],int iMaxlen,int iputType);								//���������ַ��ĺ�����װ

int public_num(char *acBuf);			//����һ���ַ��ĺ�����װ

int select_quit();						//ѡ���˳�������װ

int select_return();					//ѡ�񷵻غ�����װ

void Banktips();						//����С��ʿ

char *CurTime(int x,int y,int a);		//ѡ���˳��ͷ��صĺ���


#endif _PUBLIC_H_