#ifndef _LIST_H_
#define _LIST_H_

//����ͨ������
typedef struct list_t
{
	void* pData;			//������
	struct list_t *next;	//ָ����
}pNode;

pNode *LIST_Init(void* pData);					//ͷ����ʼ��������װ

int LIST_Add(void* pData, pNode *head);			//������Ӻ�����װ

void LIST_Print(pNode *head);					//�����ӡ������װ

int LIST_GetCount(pNode *head);					//��ȡ������������װ

void *LIST_GetNode(int iIndex, pNode *head);	//��ȡͷ������������װ

void LIST_Free(pNode *head);					//�ͷ���������װ

int LIST_Del( int iIndex, pNode *head);			//ɾ����㺯����װ

#endif _LIST_H_

