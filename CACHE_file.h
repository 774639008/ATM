#ifndef _FILE_H_
#define _FILE_H_

FILE *FILE_open(char *pcFilename);								//未进行初始化的打开文件函数封装

FILE *FILE_openinit(char *pcFilename,void (*init)(FILE *fp));	//打开初始化后的文件函数封装

void *FILE_read(FILE *fp,int size);								//对文件读取的函数封装

void FILE_add(FILE *fp,void *data,int size);					// 将新添加的数据追加文件尾函数封装

void FILE_write(FILE *fp, void *head,int size);					//将数据写入文件

void FILE_update(FILE *fp,void *data,int size,int index);		//对文件进行更新的函数封装

#endif _FILE_H_