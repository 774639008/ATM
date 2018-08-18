#ifndef _FILE_H_
#define _FILE_H_

FILE *FILE_open(char *pcFilename);								//δ���г�ʼ���Ĵ��ļ�������װ

FILE *FILE_openinit(char *pcFilename,void (*init)(FILE *fp));	//�򿪳�ʼ������ļ�������װ

void *FILE_read(FILE *fp,int size);								//���ļ���ȡ�ĺ�����װ

void FILE_add(FILE *fp,void *data,int size);					// ������ӵ�����׷���ļ�β������װ

void FILE_write(FILE *fp, void *head,int size);					//������д���ļ�

void FILE_update(FILE *fp,void *data,int size,int index);		//���ļ����и��µĺ�����װ

#endif _FILE_H_