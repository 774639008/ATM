#include "head.h"
#include "CACHE_file.h"
#include "CACHE_list.h"
#include "LOGIC_public.h"

extern pNode *head;	//����һ��������
Person *p;		//����һ���û��ṹ��

pNode *trade_head;	//����һ��������
Trade *t;		//����һ���˵��ṹ��

/*****************************************************************************************************************
* �������ƣ�void Data()
* ����������
*			 ʵ�� �ļ����������ݴ洢 �Ĺ���  
* ����˵����
*           
* ����ֵ��
******************************************************************************************************************/

pNode *USER_Data(FILE *fp)
{
		Person *people1 = NULL;			//����һ���û�people1�ṹ��
		Person *people2 = NULL;			//����һ���û�people2�ṹ��
		Person *people3 = NULL;			//����һ���û�people3�ṹ��

		//�ⲿ�����û��ṹ��p���ٿռ�
		p = (Person *)malloc(sizeof(Person));
		memset(p,0,sizeof(Person));

		//��ʼ���û�people1
		people1 = (Person *)malloc(sizeof(Person));
		memset(people1,0,sizeof(Person));

		strcpy(people1->szUsername,"admin");
		strcpy(people1->szPassword,"123456");
		people1->AccountNumber = 36600001;
		people1->fMoney = 0;
		people1->iRole = 0;
		people1->ID = 1;
		people1->iVilid = 1;

		//��ʼ���û�people2
		people2 = (Person *)malloc(sizeof(Person));
		memset(people2,0,sizeof(Person));

		strcpy(people2->szUsername,"user");
		strcpy(people2->szPassword,"123456");
		people2->AccountNumber = 36600002;
		people2->fMoney = 0;
		people2->iRole = 1;
		people2->ID = 2;
		people2->iVilid = 1;

		//��ʼ���û�people3
		people3 = (Person *)malloc(sizeof(Person));
		memset(people3,0,sizeof(Person));

		strcpy(people3->szUsername,"gao");
		strcpy(people3->szPassword,"123456");
		people3->AccountNumber=36600003;
		people3->fMoney = 0;
		people3->iRole = 1;
		people3->ID = 3;
		people3->iVilid = 1;

		//ͷ��㸳��head
		head = LIST_Init(NULL);

		//���people1,2,3������
		LIST_Add(people1,head);
		LIST_Add(people2,head);
		LIST_Add(people3,head);
		
		//�����������д���ļ�
		fp = FILE_open("data/user/people.txt");
		FILE_write(fp,head,sizeof(Person));
		
		//�ر��ļ�
		fclose(fp);
		return head;
}


pNode *TRADE_Data(FILE *fp)
{
		Trade *trade1 = NULL;			//����һ���û�trade1�ṹ��
		Trade *trade2 = NULL;			//����һ���û�trade2�ṹ��
		Trade *trade3 = NULL;		//����һ���û�trade3�ṹ��

		char *fgettime=NULL;
		char *sgettime=NULL;
		char *tgettime=NULL;

		//�ⲿ�����û��ṹ��p���ٿռ�
		t = (Trade *)malloc(sizeof(Trade));
		memset(t,0,sizeof(Trade));

		//��ʼ���û�trade1
		trade1 = (Trade *)malloc(sizeof(Trade));
		memset(trade1,0,sizeof(Trade));

		trade1->rank = 1; 
		trade1->num = 36600001;
		trade1->balance = 0;
		trade1->sum = 0;
		trade1->from = 0;
		trade1->way = 0;
		fgettime=CurTime(0,0,3);			//CurTime(0,0,3)   0,0�ֱ�������ڵ�λ��,3��������ʾ������
		strcpy(trade1->date,fgettime);

		//��ʼ���û�trade2
		trade2 = (Trade *)malloc(sizeof(Trade));
		memset(trade2,0,sizeof(Trade));

		trade2->rank = 2; 
		trade2->num = 36600002;
		trade2->balance = 0;
		trade2->sum = 0;
		trade2->from = 0;
		trade2->way = 0;
		sgettime = CurTime(0,0,3);			//CurTime(0,0,3)   0,0�ֱ�������ڵ�λ��,3��������ʾ������
		strcpy(trade2->date,sgettime);

		//��ʼ���û�trade3
		trade3 = (Trade *)malloc(sizeof(Trade));
		memset(trade3,0,sizeof(Trade));

		trade3->rank = 3; 
		trade3->num = 36600003;
		trade3->balance = 0;
		trade3->sum = 0;
		trade3->from = 0;
		trade3->way = 0;
		tgettime = CurTime(0,0,3);			//CurTime(0,0,3)   0,0�ֱ�������ڵ�λ��,3��������ʾ������
		strcpy(trade3->date,tgettime);

		//ͷ��㸳��head
		trade_head = LIST_Init(NULL);

		//���trade1,2,3������
		LIST_Add(trade1,trade_head);
		LIST_Add(trade2,trade_head);
		LIST_Add(trade3,trade_head);
		
		//�����������д���ļ�
		fp = FILE_open("data/trade/trade.txt");
		FILE_write(fp,trade_head,sizeof(Trade));
		gotoxy(0,0);
		printf("                                                                       ");
		gotoxy(0,0);

		//�ر��ļ�
		fclose(fp);
		return trade_head;
}

