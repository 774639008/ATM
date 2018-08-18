#ifndef _LIST_H_
#define _LIST_H_

//定义通用链表
typedef struct list_t
{
	void* pData;			//数据域
	struct list_t *next;	//指针域
}pNode;

pNode *LIST_Init(void* pData);					//头结点初始化函数封装

int LIST_Add(void* pData, pNode *head);			//链表添加函数封装

void LIST_Print(pNode *head);					//链表打印函数封装

int LIST_GetCount(pNode *head);					//获取结点个数函数封装

void *LIST_GetNode(int iIndex, pNode *head);	//获取头结点个数函数封装

void LIST_Free(pNode *head);					//释放链表函数封装

int LIST_Del( int iIndex, pNode *head);			//删除结点函数封装

#endif _LIST_H_

