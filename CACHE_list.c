#include "head.h"
#include "CACHE_list.h"


/*****************************************************************************************************************
* 函数名称：pNode *LIST_Init(void* Node)
* 功能描述：
*			 实现 头结点初始化 的功能  
* 参数说明：
*           void* Node --传入数据
* 返回值：pnew
******************************************************************************************************************/

pNode *LIST_Init(void* Node)
{
		pNode *pnew;
		pnew = (pNode *)malloc(sizeof(pNode));
		memset(pnew,0,sizeof(pNode));

		//填充数据域 指针域为NULL
		if(NULL == pnew)
		{
				printf("开辟空间失败");
		}
		else
		{
				pnew->pData = Node;
				pnew->next = NULL;
		}

		return pnew;
}


/*****************************************************************************************************************
* 函数名称：int LIST_Add(void* Node, pNode *head)
* 功能描述：
*			 实现 链表添加 的功能  
* 参数说明：
*           void* Node --传入数据  pNode *head --传入头结点
* 返回值：pnew
******************************************************************************************************************/

int LIST_Add(void* Node, pNode *head)
{
		pNode *pnew = NULL;
		pNode *ptemp = head;
		pnew = LIST_Init(Node);

		//找到尾结点
		while( NULL != ptemp->next)
		{
				ptemp=ptemp->next;
		}

		ptemp->next = pnew;
		return 1;
}


/*****************************************************************************************************************
* 函数名称：void LIST_Print(pNode *head)
* 功能描述：
*			 实现 链表打印 的功能  
* 参数说明：
*            pNode *head --传入头结点
* 返回值：pnew
******************************************************************************************************************/

void LIST_Print(pNode *head)
{
		pNode *ptemp = head->next;

		//循环到ptemp不为空
		while(NULL != ptemp)
		{
				printf("%s\n",((Person *)ptemp->pData)->szUsername);
				ptemp = ptemp->next;
		}
}



/*****************************************************************************************************************
* 函数名称：int LIST_GetCount(pNode *head)
* 功能描述：
*			 实现 获取头结点个数 的功能  
* 参数说明：
*            pNode *head --传入头结点
* 返回值：pnew
******************************************************************************************************************/


int LIST_GetCount(pNode *head)
{
		int count = 0;
		pNode *ptemp = head->next;

		//结点为空结束循环
		while(NULL != ptemp)
		{	
				ptemp = ptemp->next;
				count++;
		}

		return count;
}


/*****************************************************************************************************************
* 函数名称：void LIST_Free(pNode *head)
* 功能描述：
*			 实现 释放链表 的功能  
* 参数说明：
*            pNode *head --传入头结点
* 返回值：
******************************************************************************************************************/


void LIST_Free(pNode *head)
{	
		pNode *ptemp = head->next;

		//直到结点不为空结束循环
		while(NULL != ptemp)
		{	
				ptemp = head->next;
				free(head->pData);		//释放数据域
				free(head);				//释放头结点
				head=ptemp;
		}

}


/*****************************************************************************************************************
* 函数名称：int LIST_Del( int iIndex, pNode *head)
* 功能描述：
*			 实现 头结点删除 的功能  
* 参数说明：
*            int iIndex --删除的第几个结点	pNode *head --传入头结点 
* 返回值：pnew
******************************************************************************************************************/

int LIST_Del( int iIndex, pNode *head)
{
		pNode *p = head->next,*p1 = head; //p1下一个结点永远是p
		int count = 0; //用来计结点
		
		//直到结点为空时结束循环
		while(p != NULL)
		{
				count++;

				//1.一遍遍历过去找到iIndex
				if(count == iIndex)
				{
						//2.重新串接借调
						p1->next = p->next;

						//3.释放内存空间
						free(p->pData); //释放p的data
						free(p);		//释放完p的data还有p
						return 1;		//释放成功
				}

				p1 = p1->next;
				p = p->next;
		}
		return -1;		//删除失败
}


/*****************************************************************************************************************
* 函数名称：void *LIST_GetNode(int iIndex, pNode *head)
* 功能描述：
*			 实现 头结点删除 的功能  
* 参数说明：
*            int iIndex --传入第几个结点	pNode *head --传入头结点	
* 返回值：pnew
******************************************************************************************************************/

void *LIST_GetNode(int iIndex, pNode *head)
{
		//遍历（重复上面那个函数）
		pNode *p =head->next;
		int count = 0;	 //用来计结点
		
		//直到结点为空时结束循环
		while(p != NULL)
		{
				count++;

				if(count == iIndex)
				{
						return p->pData; //返回给外面数据
				}

				p = p->next;
		}
		return NULL;
}