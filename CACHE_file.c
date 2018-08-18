#include "head.h"
#include "CACHE_list.h"
#include "CACHE_file.h"


/*****************************************************************************************************************
* 函数名称：FILE *FILE_open(char *pcFilename)
* 功能描述：
*			 实现 未初始化文件打开 的功能  
* 参数说明：
*           char *pcFilename --传入文件名
*
* 返回值：	fp
******************************************************************************************************************/

FILE *FILE_open(char *pcFilename)
{
		FILE *fp;
		fp = fopen(pcFilename,"rb+");
		if(!fp)
		{
			fp = fopen(pcFilename,"wb+");  //如果不存在就创建一个新的文件	
		}
		return fp;  //如果存在fp返回一个指针
}


/*****************************************************************************************************************
* 函数名称：FILE *FILE_openinit(char *pcFilename,void (*init)(FILE *fp))
* 功能描述：
*			 实现 打开文件,不存在时创建并且初始化 的功能  
* 参数说明：
*           char *pcFilename --传入文件名  void (*init)(FILE *fp) --传入初始化的文件指针
*
* 返回值：	fp
******************************************************************************************************************/

FILE *FILE_openinit(char *pcFilename,void (*init)(FILE *fp))
{
		FILE *fp;
		fp = fopen(pcFilename,"rb+");
		if(!fp)
		{
			fp = fopen(pcFilename,"wb+");  //如果不存在就创建一个新的文件
			init(fp);
		}
		return fp;  //如果存在fp返回一个指针
}


/*****************************************************************************************************************
* 函数名称：void *FILE_read(FILE *fp,int size)
* 功能描述：
*			 实现 从文件夹读取出来,创建链表 的功能  
* 参数说明：
*           FILE *fp --传入文件指针  int size --读取类型的大小
*
* 返回值：	head
******************************************************************************************************************/

void *FILE_read(FILE *fp,int size)
{
		void *data = NULL;
		pNode *head;
		head = (pNode *) malloc(sizeof(pNode));
		memset(head,0,sizeof(pNode));
		head = LIST_Init(NULL);		//创建链表头结点

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
* 函数名称：void FILE_write(FILE *fp, void *head,int size)
* 功能描述：
*			 实现 链表重写 的功能  
* 参数说明：
*           FILE *fp --传入文件指针  void *head  --传入链表头结点   int size --读取类型的大小
*
* 返回值：	head
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
* 函数名称：void FILE_add(FILE *fp,void *data,int size)
* 功能描述：
*			 实现 新添加的数据追加文件尾 的功能  
* 参数说明：
*           FILE *fp --传入文件指针  void *data  --传入添加的数据   int size --读取类型的大小
*
* 返回值：	
******************************************************************************************************************/
 
void FILE_add(FILE *fp,void *data,int size)
{
		fseek(fp,0,SEEK_END);
		fwrite(data,size,1,fp);
		fflush(fp);
}

/*****************************************************************************************************************
* 函数名称：void FILE_add(FILE *fp,void *data,int size)
* 功能描述：
*			 实现 将修改的数据重新写入文件 index  修改第几个 的功能  
* 参数说明：
*           FILE *fp --传入文件指针  void *data  --传入添加的数据   int size --读取类型的大小
*
* 返回值：	
******************************************************************************************************************/

void FILE_update(FILE *fp,void *data,int size,int index)
{
		fseek(fp,size*(index-1),SEEK_SET);
		fwrite(data,size,1,fp);
		fflush(fp);
}

