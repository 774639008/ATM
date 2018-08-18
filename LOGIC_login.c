#include "head.h"
#include "CACHE_list.h"
#include "VIEW_login.h"
#include "LOGIC_login.h"
#include "LOGIC_public.h"

extern Person *p;		//引进成员结构体的全局变量，对输出成员的数据必定用到
extern pNode *people_head;		//引进链表的全局变量，对链表操作必定用到头结点

extern Person g_currentUser;	////当登陆成功时，记录当前进入的登陆界面用户

/*****************************************************************************************************************
* 函数名称：int Login()
* 功能描述：
*			 实现 登陆 的功能  
* 参数说明：
*           
* 返回值：
******************************************************************************************************************/

int Login()
{
		Person *people;		//定义一个用户结构体people	用来匹配登录时的信息

		while(1)
		{	
			
				char acStr[100] = {0};		//输入的字符存储数组
				char acName[100] = {0};		//输入的姓名存储数组
				char acPsw[100] = {0};		//输入的密码存储数组
				int num = 0;				//定义num来接收输入的用户名或账号
				int count = 0;				//用来接链表结点的个数
				int i = 0;		//循环遍历使用的初始变量

				Banktips();
				gotoxy(34,5);
			
				//输入的字符存入acAcount,最大输入数为（8）个,控制输入类型为数字（1）,为明文（1）
				if(glb_putString(acName,8,3,1) == 0	)
				{
					
						printf("");
				}

				count = LIST_GetCount(people_head);
				num = atoi(acName);
				//进行遍历查找用户的姓名是否与输入的姓名是否匹配
				for(i = 1; i <= count; i++)
				{
						people = (Person *)LIST_GetNode(i,people_head);
						if(people->iVilid == 0)
						{
							continue;
						}
						if(0 == strcmp(people->szUsername,acName) || people->AccountNumber == num )
						{
								break;
						}
					
				}


				//判断输入的字符是否为空
				if( 0 == strlen(acName))
				{
						printf("输入不能为空！");
						Sleep(500);
						gotoxy(34,5);
						printf("               ");
						continue;
				}

				//如果找不到 就提示用户不存在
				if(i > count)
				{
						
						gotoxy(34,7);
						printf("用户名不存在！\n");	
						Sleep(300);
						gotoxy(34,7);
						printf("              \n");		//用户名提示不存在进行清空
						gotoxy(34,5);
						printf("              \n");		//用户名进行清空
						continue;
				}
				
				//加一个循环与之前用户匹配隔开,进行验证
				while(1)
				{
					gotoxy(34,6);
					
					//输入的字符存入acPsw,最大输入数为（6）个,控制输入类型为数字和字母（3）,为密文（0）
					if(27 == glb_putString(acPsw,6,1,0))
					{
						system("cls");
						return main();
					}
					
					////进行遍历查找用户的密码与姓名是否与输入的密码与姓名是否匹配
					for(i = 0; i < count; i++)
					{
						p =  (Person *)LIST_GetNode(i,people_head);

						//如果找到匹配的密码与姓名,就提示成功,返回出去此用户的身份,进入相应的界面
						if((0 == strcmp(people->szUsername,acName)|| people->AccountNumber == num )&& 0 == strcmp(people->szPassword,acPsw)&&people->iVilid == 1)
						{	
								gotoxy(20,7);
								printf("登陆成功,");
								memcpy(&g_currentUser,people,sizeof(Person));
								Sleep(200);
								printf("请稍等>");
								for (i=0;i<10;i++)
								{
										printf(">");
										Sleep(50);
								}
								Sleep(300);
								num = people->iRole;	//返回身份信息,进行验证作用,进入对应的界面
								return num;
						}
					}
				
					gotoxy(24,7);
					printf("密码错误,请重新登录！\n");
					Sleep(700);
					gotoxy(34,6);
					printf("           \n");		//密码输入的位置进行清空
					gotoxy(24,7);
					printf("                             \n");		//提示密码错误语句进行清空
				}
		}
}