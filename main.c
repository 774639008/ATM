#include "head.h"
#include "VIEW_login.h"
#include "VIEW_admin.h"
#include "LOGIC_public.h"
#include "LOGIC_login.h"
#include "LOGIC_admin.h"
#include "LOGIC_user.h"
#include "CACHE_list.h"
#include "CACHE_data.h"
#include "CACHE_file.h"
#include "CACHE_list.h"
	
pNode *head;				//定义一个头结点

pNode *people_head = NULL;	//定义一个用户头结点
FILE *people_fp;			//定义一个用户文件指针

extern pNode *trade_head;	//定义一个账单头结点
FILE *trade_fp;				//定义一个账单文件指针

int glb_people_id = 0;		//全局变量用户ID
int glb_trade_id = 0;		//全局变量账单ID

Person g_currentUser;		//记录当前进入的登陆界面用户
		
int main()
{
		Person *ps;			//定义一个用户结构体ps

		int result = 0;		//定义一个result变量接受身份

		//用户数据初始化
		people_fp = FILE_open("data/user/people.txt");
		people_head=FILE_read(people_fp,sizeof(Person));
		if(	people_head->next == NULL)
		{
				people_head = USER_Data(people_fp);		//用户初始化后头结点传给people_head
		}
	
		trade_fp = FILE_open("data/trade/trade.txt");
		trade_head=FILE_read(trade_fp,sizeof(Trade));
		if(	trade_head->next == NULL)
		{
				trade_head = TRADE_Data(trade_fp);		
		}
		
		//登陆界面显示
		LoginView();	
		result = Login();		//result来接通过登录函数返回的身份值

		//函数嵌套,获取的个数来计算最后的一个
		ps = LIST_GetNode(LIST_GetCount(people_head),people_head);  
		glb_people_id = ps->ID;
		

		ps = LIST_GetNode(LIST_GetCount(people_head),people_head); 
		glb_trade_id = ps->ID;

		//判断身份信息,来进管理员界面还是用户界面
		switch(result)
		{
		case 0:
			{
					Admin();	//进入管理员模式
			}
			break;
		case 1:
			{
					User();		//进入用户模式		
			}
			break;
		default:
			break;
		}

		fclose(people_fp);			//关闭用户文件
		LIST_Free(people_head);		//释放用户链表

		fclose(trade_fp);			//关闭账单文件
		LIST_Free(trade_head);		//释放账单链表

		return 0;
}