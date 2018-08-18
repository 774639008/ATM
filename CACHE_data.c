#include "head.h"
#include "CACHE_file.h"
#include "CACHE_list.h"
#include "LOGIC_public.h"

extern pNode *head;	//定义一个链表结点
Person *p;		//定义一个用户结构体

pNode *trade_head;	//定义一个链表结点
Trade *t;		//定义一个账单结构体

/*****************************************************************************************************************
* 函数名称：void Data()
* 功能描述：
*			 实现 文件和链表数据存储 的功能  
* 参数说明：
*           
* 返回值：
******************************************************************************************************************/

pNode *USER_Data(FILE *fp)
{
		Person *people1 = NULL;			//定义一个用户people1结构体
		Person *people2 = NULL;			//定义一个用户people2结构体
		Person *people3 = NULL;			//定义一个用户people3结构体

		//外部变量用户结构体p开辟空间
		p = (Person *)malloc(sizeof(Person));
		memset(p,0,sizeof(Person));

		//初始化用户people1
		people1 = (Person *)malloc(sizeof(Person));
		memset(people1,0,sizeof(Person));

		strcpy(people1->szUsername,"admin");
		strcpy(people1->szPassword,"123456");
		people1->AccountNumber = 36600001;
		people1->fMoney = 0;
		people1->iRole = 0;
		people1->ID = 1;
		people1->iVilid = 1;

		//初始化用户people2
		people2 = (Person *)malloc(sizeof(Person));
		memset(people2,0,sizeof(Person));

		strcpy(people2->szUsername,"user");
		strcpy(people2->szPassword,"123456");
		people2->AccountNumber = 36600002;
		people2->fMoney = 0;
		people2->iRole = 1;
		people2->ID = 2;
		people2->iVilid = 1;

		//初始化用户people3
		people3 = (Person *)malloc(sizeof(Person));
		memset(people3,0,sizeof(Person));

		strcpy(people3->szUsername,"gao");
		strcpy(people3->szPassword,"123456");
		people3->AccountNumber=36600003;
		people3->fMoney = 0;
		people3->iRole = 1;
		people3->ID = 3;
		people3->iVilid = 1;

		//头结点赋给head
		head = LIST_Init(NULL);

		//添加people1,2,3到链表
		LIST_Add(people1,head);
		LIST_Add(people2,head);
		LIST_Add(people3,head);
		
		//把上面的数据写入文件
		fp = FILE_open("data/user/people.txt");
		FILE_write(fp,head,sizeof(Person));
		
		//关闭文件
		fclose(fp);
		return head;
}


pNode *TRADE_Data(FILE *fp)
{
		Trade *trade1 = NULL;			//定义一个用户trade1结构体
		Trade *trade2 = NULL;			//定义一个用户trade2结构体
		Trade *trade3 = NULL;		//定义一个用户trade3结构体

		char *fgettime=NULL;
		char *sgettime=NULL;
		char *tgettime=NULL;

		//外部变量用户结构体p开辟空间
		t = (Trade *)malloc(sizeof(Trade));
		memset(t,0,sizeof(Trade));

		//初始化用户trade1
		trade1 = (Trade *)malloc(sizeof(Trade));
		memset(trade1,0,sizeof(Trade));

		trade1->rank = 1; 
		trade1->num = 36600001;
		trade1->balance = 0;
		trade1->sum = 0;
		trade1->from = 0;
		trade1->way = 0;
		fgettime=CurTime(0,0,3);			//CurTime(0,0,3)   0,0分别代表所在的位置,3带代表显示的类型
		strcpy(trade1->date,fgettime);

		//初始化用户trade2
		trade2 = (Trade *)malloc(sizeof(Trade));
		memset(trade2,0,sizeof(Trade));

		trade2->rank = 2; 
		trade2->num = 36600002;
		trade2->balance = 0;
		trade2->sum = 0;
		trade2->from = 0;
		trade2->way = 0;
		sgettime = CurTime(0,0,3);			//CurTime(0,0,3)   0,0分别代表所在的位置,3带代表显示的类型
		strcpy(trade2->date,sgettime);

		//初始化用户trade3
		trade3 = (Trade *)malloc(sizeof(Trade));
		memset(trade3,0,sizeof(Trade));

		trade3->rank = 3; 
		trade3->num = 36600003;
		trade3->balance = 0;
		trade3->sum = 0;
		trade3->from = 0;
		trade3->way = 0;
		tgettime = CurTime(0,0,3);			//CurTime(0,0,3)   0,0分别代表所在的位置,3带代表显示的类型
		strcpy(trade3->date,tgettime);

		//头结点赋给head
		trade_head = LIST_Init(NULL);

		//添加trade1,2,3到链表
		LIST_Add(trade1,trade_head);
		LIST_Add(trade2,trade_head);
		LIST_Add(trade3,trade_head);
		
		//把上面的数据写入文件
		fp = FILE_open("data/trade/trade.txt");
		FILE_write(fp,trade_head,sizeof(Trade));
		gotoxy(0,0);
		printf("                                                                       ");
		gotoxy(0,0);

		//关闭文件
		fclose(fp);
		return trade_head;
}

