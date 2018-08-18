#include "head.h"
#include "CACHE_list.h"
#include "CACHE_file.h"


/*****************************************************************************************************************
* �������ƣ�FILE *FILE_open(char *pcFilename)
* ����������
*			 ʵ�� δ��ʼ���ļ��� �Ĺ���  
* ����˵����
*           char *pcFilename --�����ļ���
*
* ����ֵ��	fp
******************************************************************************************************************/

FILE *FILE_open(char *pcFilename)
{
		FILE *fp;
		fp = fopen(pcFilename,"rb+");
		if(!fp)
		{
			fp = fopen(pcFilename,"wb+");  //��������ھʹ���һ���µ��ļ�	
		}
		return fp;  //�������fp����һ��ָ��
}


/*****************************************************************************************************************
* �������ƣ�FILE *FILE_openinit(char *pcFilename,void (*init)(FILE *fp))
* ����������
*			 ʵ�� ���ļ�,������ʱ�������ҳ�ʼ�� �Ĺ���  
* ����˵����
*           char *pcFilename --�����ļ���  void (*init)(FILE *fp) --�����ʼ�����ļ�ָ��
*
* ����ֵ��	fp
******************************************************************************************************************/

FILE *FILE_openinit(char *pcFilename,void (*init)(FILE *fp))
{
		FILE *fp;
		fp = fopen(pcFilename,"rb+");
		if(!fp)
		{
			fp = fopen(pcFilename,"wb+");  //��������ھʹ���һ���µ��ļ�
			init(fp);
		}
		return fp;  //�������fp����һ��ָ��
}


/*****************************************************************************************************************
* �������ƣ�void *FILE_read(FILE *fp,int size)
* ����������
*			 ʵ�� ���ļ��ж�ȡ����,�������� �Ĺ���  
* ����˵����
*           FILE *fp --�����ļ�ָ��  int size --��ȡ���͵Ĵ�С
*
* ����ֵ��	head
******************************************************************************************************************/

void *FILE_read(FILE *fp,int size)
{
		void *data = NULL;
		pNode *head;
		head = (pNode *) malloc(sizeof(pNode));
		memset(head,0,sizeof(pNode));
		head = LIST_Init(NULL);		//��������ͷ���

		rewind(fp);
		data = malloc(size);
		memset(data,0,size);
		fread(data,size,1,fp);
		while(!feof(fp))
		{	
			LIST_Add(data,head);
			data = malloc(size);
			memset(data,0,size);
			fread(data,size,1,fp);
		}
		return head;
}


/*****************************************************************************************************************
* �������ƣ�void FILE_write(FILE *fp, void *head,int size)
* ����������
*			 ʵ�� ������д �Ĺ���  
* ����˵����
*           FILE *fp --�����ļ�ָ��  void *head  --��������ͷ���   int size --��ȡ���͵Ĵ�С
*
* ����ֵ��	head
******************************************************************************************************************/
 
void FILE_write(FILE *fp, void *head,int size)
{
		int count = LIST_GetCount(head);
		int i =0;
		void *data;

		rewind(fp);

		for(i=1;i<=count;i++)
		{
			data = LIST_GetNode(i,head);
			fwrite(data,size,1,fp);
			fflush(fp);
		}
}


/*****************************************************************************************************************
* �������ƣ�void FILE_add(FILE *fp,void *data,int size)
* ����������
*			 ʵ�� ����ӵ�����׷���ļ�β �Ĺ���  
* ����˵����
*           FILE *fp --�����ļ�ָ��  void *data  --������ӵ�����   int size --��ȡ���͵Ĵ�С
*
* ����ֵ��	
******************************************************************************************************************/
 
void FILE_add(FILE *fp,void *data,int size)
{
		fseek(fp,0,SEEK_END);
		fwrite(data,size,1,fp);
		fflush(fp);
}

/*****************************************************************************************************************
* �������ƣ�void FILE_add(FILE *fp,void *data,int size)
* ����������
*			 ʵ�� ���޸ĵ���������д���ļ� index  �޸ĵڼ��� �Ĺ���  
* ����˵����
*           FILE *fp --�����ļ�ָ��  void *data  --������ӵ�����   int size --��ȡ���͵Ĵ�С
*
* ����ֵ��	
******************************************************************************************************************/

void FILE_update(FILE *fp,void *data,int size,int index)
{
		fseek(fp,size*(index-1),SEEK_SET);
		fwrite(data,size,1,fp);
		fflush(fp);
}

