#include "head.h"
#include "LOGIC_public.h"
#include "LOGIC_admin.h"
#include "VIEW_admin.h"
#include "CACHE_file.h"
#include "CACHE_list.h"

extern FILE *people_fp;  //引进文件的全局变量，对文件操作必定用到文件指针
extern pNode *people_head;//引进链表的全局变量，对链表操作必定用到头结点

extern int glb_people_id;	//引进一个用户id
extern int glb_trade_id;

extern pNode *trade_head;	//定义一个链表结点
extern FILE *trade_fp;		//定义一个账单结构体

extern Person g_currentUser;	//引进当前进入界面的用户，当进行存款时必定需要匹配

/*****************************************************************************************************************
* 函数名称：int Admin()
* 功能描述：
*			 实现 管理员管理用户 的功能  
* 参数说明：
*           
* 返回值：0
******************************************************************************************************************/

int Admin()
{
		while(1)
		{
			AdminView();					//管理员界面
			gotoxy(20,10);
			printf(" 	       当前管理员:%s        ",g_currentUser.szUsername);		//对当前用户进行显示

			switch(select_interface(5,36,13))		//控制光标移动根据返回的值进行判断进入的为4个选择的页面
			{
			case 1:						//管理员添加模块
				{
						AdminAdd_View();		//管理员添加显示界面
						AdminAdd();				//管理员添加功能
				}
				break;
			case 2:
				{		while(1)
						{
								AdminQuery_View();		//管理员查询显示界面
								switch(select_interface(4,36,13))		//控制光标移动根据返回的值进行判断进入的为3个选择的页面	
								{
								case 1:				//管理员全部查询模块
									{	
											system("cls");
											AdminAllquery_View();
											query();			
									}
									break;
								case 2:				//管理员分类查询模块
									{
											AdminClassifyQuery_View();				
											switch(select_interface(2,36,13))
											{
											case 1:
												{
														AdminAquery();			//管理员查询
												}
												break;
											case 2:
												{
														AdminUquery();			//用户查询
												}
												break;
											case -3:
												{
														continue;
												}
												break;
											default:
												break;
											}
									}
									break;
								case 3:				//管理员条件查询模块
									{		
											AdminConditionquery_View();
											switch(select_interface(2,36,13))
											{
											case 1:
												{
														AdminVaguesearch();			//管理员模糊查询功能
												}
												break;
											case 2:
												{
														AdminExactsearch();			//管理员精确查询功能	
												}
												break;
											case -3:
												{
														continue;
												}
												break;
											default:
												break;
											}
									}
									break;
								case 4:
									{
											AdminPassword();
									}
									break;
								case -3:	//返回模块
									{
											return Admin();
									}
									break;
								default:
									break;
								}
						}
				}
				break;
			case 3:				//管理员删除模块
				{
						AdminDel_View();		//管理员删除显示界面
						AdminDel();				//管理员删除功能
				}
				break;
			case 4:				//管理员修改密码模块
				{
						AdminUpdpsw();			//管理员密码修改功能
				}
				break;
			case 5:
				{
						AdminRecover();
				}
				break;
			case -3:			//返回模块
				{
						system("cls");
						return main();			//返回登录界面
				}
			default:
				break;
			}
		}
		return 0;
}


/*****************************************************************************************************************
* 函数名称：int AdminAdd()
* 功能描述：
*			 实现 管理添加用户 的功能  
* 参数说明：
*           
* 返回值：0
******************************************************************************************************************/

int AdminAdd()
{
		char ch = 0,ch1=0,ch2 = 0;			//定义ch,ch1,ch2 来接受命令的数组
		char role;							//定义role来接受身份,并且赋值给添加的用户
		char acName[20] = {0};				//acName[20]来临时接收用户名
		char acPsw[20] = {0};				//acPsw[20]	来临时接收密码
		char acPsw1[20] = {0};				//acPsw1[20] 来临时接收再次输入密码
		int count = 0;						//count接收链表的结点数
		int count1 = 0;
		int i = 0;							//i来做一个循环的初始值
		int num = 0;						//num临时接收银行账号的值
		int num1 = 0;
		Person *ps;							//定义一个员工结构体
		Person *ps1;						//定义一个临时接收的员工结构体
		Trade *ts;
		Person *people;
		while(1)
		{
				AdminAdd_View();
				
				gotoxy(24,13);			//(24,13)光标位置，为后面清空作用
				printf("请输入新用户名(小写字母,数字组成):");		
				if(27 == glb_putString(acName,8,3,1))
				{
					return 0;
				}

				count = LIST_GetCount(people_head);
				//进行遍历查找用户的姓名是否与输入的姓名是否存在
				for(i = 1; i <= count; i++)
				{
						people = (Person *)LIST_GetNode(i,people_head);
						
						if(0 == strcmp(people->szUsername,acName) )
						{
								printf("用户已经存在！");
								Sleep(500);
								gotoxy(51,13);
								printf("                                     ");
								break;
						}
				}

				if(i<=count)
				{
					continue;
				}
				
				//输入的字符不能为空
				if(0 == strlen(acName))
				{
					printf("输入不能为空！");
					Sleep(500);
					printf("                 ");
					gotoxy(45,13);
					printf("                     ");
					continue;
				}
				if(strlen(acName)<4)
				{
					printf("账号最少为4位！");
					Sleep(500);
					printf("                 ");
					gotoxy(45,13);
					printf("                     ");
					continue;
				}
				else if(acName[0]<'a' || acName[0]>'z')			//判断首字符是否为数字
				{
					printf("\n\t\t首字符不能为数字，应该为字母！");
					system("pause");
					continue;
				}

				printf("\n\t\t\t请输入密码(6位):");
				if(27 == glb_putString(acPsw,6,1,0))
				{
					return 0;
				}

				if(strlen(acPsw)<6)
				{
					printf("密码需要6位");
					Sleep(500);
					printf("                                         ");
					gotoxy(45,13);
					printf("                                       ");
					gotoxy(40,14);
					printf("                                       ");
					continue;	
				}

				printf("\n\t\t\t请再次输入密码(6位):");
				if(27 == glb_putString(acPsw1,6,1,0))
				{
					return 0;
				}
			
				
				//进行密码与第二次密码输入的验证,判断密码是否为空
				if(strcmp(acPsw,acPsw1) == 0 && acPsw[0] != 0)
				{
						ps = (Person *)malloc(sizeof(Person));
						memset(ps,0,sizeof(Person));
						strcpy(ps->szUsername,acName);
						strcpy(ps->szPassword,acPsw);
						ps->fMoney = 0;
						ps->iVilid = 1;
						

						printf("\n\t\t\t请选择身份(0-管理员 1-普通用户 )：");
						if(27 == public_num(&role))
						{
							return 0;
						}

						//根据赋值的角色,来判别添加管理员角色还是用户角色
						if(role == '0')
						{
								ps->iRole = 0;
						}
						else if(role == '1')
						{
								ps->iRole = 1;
						}
						else
						{
								printf("\n\t\t\t输入错误, 按1重新添加,其他任意键返回上一级\n");
								printf("\t\t\t请输入:");
								ch2 = getch();

								//根据输入的指令判断继续添加,就重循环,退出的话退出循环
								if (ch2 == '1')
								{
										system("cls");
										continue;
								}
								else if(ch2 == '2')
								{
										break;
								}
						}
						
						//如果添加符合管理员和用户的身份,就添加成功
						if (role == '0' || role == '1')
						{
								glb_people_id++;
								ps->ID = glb_people_id;			//ID赋值
								count = LIST_GetCount(people_head);
								ps1 = LIST_GetNode(count,people_head);
								num = ps1->AccountNumber;
								num++;
								ps->AccountNumber= num;			//账号赋值

							
								
								ts = (Trade *)malloc(sizeof(Trade));
								memset(ts,0,sizeof(Trade));	
					
										//ID赋值
								count1 = LIST_GetCount(trade_head);
								ts = LIST_GetNode(count1,trade_head);
								glb_trade_id++;
								ts->rank = glb_trade_id;
								num1 = ts->num;
								num1++;
								ts->num = num1;			//账号赋值
								ts->balance = 0;
								ts->sum = 0;
								ts->from = 0;
								ts->way = 0;


								//同步文件数据		
								LIST_Add(ps,people_head);  //只是添加到链表
								LIST_Add(ts,trade_head); 

								FILE_add(people_fp,ps,sizeof(Person));	//追加到文件里面数据后面
								FILE_add(trade_fp,ts,sizeof(Trade));
								
								printf("\n\t\t\t正在添加中,");
								Sleep(200);
								printf("请稍等>");
								
								//实现加载的显示
								for (i=0;i<20;i++)
								{
										printf(">");
										Sleep(50);
								}

								Sleep(300);
								printf("\n\n\t\t\t添加用户成功\n");
								printf("\n\t\t\t新增的用户信息:");
								printf("\n\t\t\t账号:%d\n",ps->AccountNumber);
								printf("\t\t\t用户名:%s\n",ps->szUsername);
								printf("\t\t\t余额:%d\n",ps->fMoney);
								printf("\t\t\tID:%d\n",ps->ID);

								switch(ps->iRole)
								{
									case 0:printf("\t\t\t身份:管理员\n");break;
									case 1:printf("\t\t\t身份:用户\n");break;
								}

//添加用户成功后显示相应的用户信息显示,DEBUG进行调试使用								
#ifdef DEBUG	
								
								printf("\n\t\t\t账号:%d\n",ts->num);
								printf("\t\t\t金额:%d\n",ts->sum);
								printf("\t\t\t余额:%d\n",ts->balance);
								printf("\t\t\tID:%d\n",ts->rank);
#endif DEBUG

								printf("\n\n输入任意键返回\n");
								ch1 = getch();
								return 0;
						}	
			}

			//当密码和再次输入的不一致
			else
			{
					  printf("\n\t\t\t输入两次密码不一致,按1重新添加,其他任意键返回上一级\n");
					  printf("\t\t\t请输入:");
					  public_num(&ch);

					  //输入1清空之前输入的数据
					  if(ch == '1')
					  {
								gotoxy(23,13);
								printf("\t\t\t                   ");
								printf("\n\t\t\t                               ");
								printf("\n\t\t\t                                     ");
								printf("\n\t\t\t                                              ");
								printf("\n\t\t\t                                                   ");
								printf("\t\t\t                    ");
								printf("\t\t\t                      ");

							    //清空数据
							    memset(acName,0,sizeof(acName));
							    memset(acPsw,0,sizeof(acPsw));
							    memset(acPsw1,0,sizeof(acPsw1));
					  }
			   		  else
					  {
							    break;
					  } 
			}
		}
		return 0;
}


/*****************************************************************************************************************
* 函数名称：int AdminAllquery()
* 功能描述：
*			 实现 管理查询用户 的功能  
* 参数说明：
*           
* 返回值：0
******************************************************************************************************************/

int AdminAllquery()
{
		int i = 0;			//定义循环的初始变量i
		int count = 0;		//count来接收获取的结点数
		int num = 0;		//num来表示序列号
		Person *people;		//定义一个员工结构体people
		char ch[10] = {0};	//定义数组ch接受输入命令
		
		printf("\t序号      姓名        	身份		账号		余额	\n");
		//遍历链表
		count = LIST_GetCount(people_head);

		//通过遍历一个个找出用户的信息
		for (i = 1; i <= count; i++)
		{
				people = LIST_GetNode(i,people_head);
				
				//判断是否为有效的用户
				if (people->iVilid == 1)
				{	
						num++;
					//根据他们的身份是否匹配进行打印出来
						switch (people->iRole)
						{
						case 0:					//0为管理员身份
							{
									printf("\t%-6d     %-10s 	管理员",num,people->szUsername,people->iRole);
									printf("		%8d",people->AccountNumber);
									printf("	%.2f\n",people->fMoney);
							}
							break;
						case 1:					//1为用户身份
							{
									printf("\t%-6d     %-10s   普通用户",num,people->szUsername,people->iRole);
									printf("	%8d",people->AccountNumber);
									printf("	%.2f\n",people->fMoney);
							}
							break;
						}
				}
			
		}
		return 0;
}



/*****************************************************************************************************************
* 函数名称：void query()
* 功能描述：
*			 实现 管理查询用户 的功能  
* 参数说明：
*           
* 返回值：0
******************************************************************************************************************/

void query()
{
		AdminAllquery_View();
		AdminAllquery();

		printf("\n\n\n\t\t\t输入任意键返回\n");
		getch();
}

/*****************************************************************************************************************
* 函数名称：int AdminAquery()
* 功能描述：
*			 实现 管理分类查询管理员 的功能  
* 参数说明：
*           
* 返回值：0
******************************************************************************************************************/

int AdminAquery()
{
		while(1)
		{
				int i = 0;			//定义循环的初始变量i
				int count = 0;		//count来接收获取的结点数
				Person *people;		//定义一个员工结构体people
				char ch[10] = {0};	//定义数组ch接受输入命令
				int num = 0;		//num表示序列号

				AdminAquery_View();		//管理员查询界面

				printf("\t序号      姓名        	身份		账号	       余额\n");
				//遍历链表
				count = LIST_GetCount(people_head);

				//通过遍历一个个找出用户的信息
				for (i = 1; i <= count; i++)
				{
					people = LIST_GetNode(i,people_head);
					
					//判断是否为有效的用户
					if (people->iVilid == 1)
					{
						num++;
						//根据他们的身份是否匹配进行打印出来
						switch (people->iRole)
						{
						case 0:					//0为管理员身份
							{
								printf("\t%-6d     %-10s 	管理员",num,people->szUsername,people->iRole);
								printf("		%8d",people->AccountNumber);
								printf("	%.2f\n",people->fMoney);
							}
							break;
						}
					}
				}

				printf("\n\n\n\t\t\t输入任意键返回\n");
				getch();
				break;
		}
		return 0;
}


/*****************************************************************************************************************
* 函数名称：int AdminUquery()
* 功能描述：
*			 实现 管理分类查询普通用户 的功能  
* 参数说明：
*           
* 返回值：0
******************************************************************************************************************/

int AdminUquery()
{
		while(1)
		{
				int i = 0;			//定义循环的初始变量i
				int count = 0;		//count来接收获取的结点数
				Person *people;		//定义一个员工结构体people
				char ch[10] = {0};	//定义数组ch接受输入命令
				int num = 0;		//num表示序列号

				AdminUquery_View();		//用户查询界面

				printf("\t序号      姓名        	身份		       账号	        余额\n");

				//遍历链表
				count = LIST_GetCount(people_head);

				//通过遍历一个个找出用户的信息
				for (i = 1; i <= count; i++)
				{
						people = LIST_GetNode(i,people_head);
						
						//判断是否为有效的用户
						if (people->iVilid == 1)
						{
							num++;
							//根据他们的身份是否匹配进行打印出来
							switch (people->iRole)
							{
							case 1:					//0为管理员身份
								{
										printf("\t%-6d     %-10s 	普通用户",num,people->szUsername,people->iRole);
										printf("		%8d",people->AccountNumber);
										printf("	%.2f\n",people->fMoney);
								}
								break;
							}
						}
				}

				printf("\n\n\n\t\t\t输入任意键返回\n");
				getch();
				break;
		}
		return 0;
}




/*****************************************************************************************************************
* 函数名称：int AdminExactsearch()
* 功能描述：
*			 实现 精确查询 的功能  
* 参数说明：
*           
* 返回值：0
******************************************************************************************************************/

int AdminExactsearch()
{
		while(1)
		{
				char ch[10] = {0};			//定义数组ch接受输入命令
				char name[10] = {0};		//定义数组name匹配用户的名字
				int count = 0;				//count接收链表的结点数	
				int i = 0;					//定义循环的初始变量i
				int num = 0;				//定义num变量表示序列号
				Person *people;				//定义用户结构体people

				AdminExactsearch_View();	//管理员精确查询界面

				gotoxy(7,10);
				printf("\t\t\t请输入目标用户的姓名:");
				
				//判断是否输入esc返回
				if(27 == glb_putString(name,10,2,1))
				{
					return 0;
				}

				//判断不能输入为空
				if(0 == strlen(name))
				{
					printf("不能输入为空！");
					Sleep(500);
					continue;
				}

				gotoxy(7,10);
				printf("\t\t\t                                   \n");

				//遍历链表
				count = LIST_GetCount(people_head);

				printf("\t序号      姓名          余额	身份		账号\n");

				//通过遍历一个个找出用户的信息
				for (i = 1; i <= count; i++)
				{
					people = LIST_GetNode(i,people_head);
					
					//输入的名字来找到链表中的用户名字
					if (0 == strcmp((people->szUsername),name))
					{
						num++;
						//根据他们的身份是否匹配进行打印出来
						switch (people->iRole)
						{
						case 0:					//0为管理员身份
							{
								printf("\t%-6d     %-10s    %d	管理员",num,people->szUsername,people->fMoney,people->iRole);
								printf("		%.2f\n",people->AccountNumber);
							}
							break;
						case 1:					//1为用户身份
							{
								printf("\t%-6d     %-10s    %d	普通用户",num,people->szUsername,people->fMoney,people->iRole);
								printf("	%.2f\n",people->AccountNumber);
							}
							break;
						}
					}
				}

				printf("\n\n\n\t\t\t输入任意键返回\n");
				getch();
				break;
		}
		return 0;
}


/*****************************************************************************************************************
* 函数名称：int AdminVaguesearch()
* 功能描述：
*			 实现 精确查询 的功能  
* 参数说明：
*           
* 返回值：0
******************************************************************************************************************/

int AdminVaguesearch()
{
		while(1)
		{
				char ch[10] = {0};		//定义数组ch接受输入命令
				char name[10] = {0};	//定义数组name匹配用户的名字
				int count = 0;			//count接收链表的结点数	
				int i = 0;				//定义循环的初始变量i
				int num = 0;			//定义num用来排序
				Person *people;			//定义用户结构体people

				AdminVaguesearch_View();	//管理员模糊查询界面
				gotoxy(7,10);
				printf("\t\t\t请输入目标用户的姓名:");
				if(27 == glb_putString(name,10,3,1))
				{
					return 0;
				}

				//判断不能输入为空
				if(0 == strlen(name))
				{
					printf("不能输入为空！");
					Sleep(500);
					continue;
				}

				gotoxy(7,10);
				printf("\t\t\t                                   \n");

				//遍历链表
				count = LIST_GetCount(people_head);


				printf("\t序号      姓名          余额	身份		账号\n");

				//通过遍历一个个找出用户的信息
				for (i = 1; i <= count; i++)
				{
					people = LIST_GetNode(i,people_head);

					
					//输入的名字来找到链表中的用户名字
					if (0 != strstr((people->szUsername),name) )
					{
						num++;
						//根据他们的身份是否匹配进行打印出来
						switch (people->iRole)
						{
						case 0:					//0为管理员身份
							{
								printf("\t%-6d     %-10s    %d	管理员",num,people->szUsername,people->fMoney,people->iRole);
								printf("		%-.2f\n",people->AccountNumber);
							}
							break;
						case 1:					//1为用户身份
							{
								printf("\t%-6d     %-10s    %d	普通用户",num,people->szUsername,people->fMoney,people->iRole);
								printf("	%-.2f\n",people->AccountNumber);
							}
							break;
						}
					}
				}

				printf("\n\n\n\t\t\t输入任意键返回\n");
				getch();
				break;
		}
		return 0;
}


/*****************************************************************************************************************
* 函数名称：int AdminDel()
* 功能描述：
*			 实现 管理删除用户 的功能  
* 参数说明：
*           
* 返回值：0
******************************************************************************************************************/

int AdminDel()
{
		int i = 0;				//定义变量i作为循环的初始值
		int count = 0;			//定义变量count来接获取的结点个数
		int rnum = 0;			//定义变量rnum来接收返回
		int flag = 0;			//定义变量flag作为标记  方便返回	
		char acName[10]={0};	//定义变量acName来作为输入的账号
		char  ch = 0;			//定义ch来作为getch的存储变量
		int flag1 = 0;			//定义标志位flag1
		Person *people;			//定义用户结构体people

		while (1)
		{
				//删除和查询界面显示
				AdminDel_View();
				AdminAllquery();

				printf("\n请输入删除用户的姓名：");
				rnum = glb_putString(acName,8,3,1);
				if(rnum == 27)
				{
					return 0;
				}

				//遍历
				count = LIST_GetCount(people_head);

				//进行循环遍历找到对应账号的结点
				for(i = 1; i <= count; i++)
				{
						people = LIST_GetNode(i,people_head);
						if(0 == strcmp(people->szUsername,acName))
						{
							//匹配同一用户
							if (people->iRole == 1)
							{
									//如果余额不为0,就可以删除
									if(people->fMoney != 0)
									{
										printf("\n用户余额不为0,不可删除！\n");
										continue;
									}
									
									people->iVilid = 0; //对内存操作
									
									//同步文件的数据
									FILE_update(people_fp,people,sizeof(Person),i);
									
									printf("\n请删除用户成功,输入1.再次删除 2.返回上一级\n");
									ch =getch();
									if(ch == '1')
									{
											system("cls");
											acName[10] = 0;
											i = count;
											flag1 = 1;
									}
									else
									{
											flag = 1;  //跳出多重循环进行标记  
									}
									break;
							}
							else
							{
							printf("\n此为管理员不可删除！\n");
							i = count;
							Sleep(500);
							continue;
							}
						}
						
				} /*	end of for(i = 1; i <= count; i++)	*/

				//设置flag结束上一个循环,判断是否返回
				if(flag1 == 1)
				{
					continue;
				}
				
				//如果遍历找不到,就提示错误
				if(i > count)
				{			
						printf("\n输入错误,输入1.再次删除 2.返回上一级\n");
						ch =getch();
						if(ch == '1')
						{
								system("cls");
								acName[10] = 0;
								continue;
						}
						else
						{
								break;
						}
				}

				//当用户输入返回，使flag值赋值为1，返回出去
				if (flag == 1)
				{
						break;
				}
		}	/* end of while (1) */
		return 0;	
}


/*****************************************************************************************************************
* 函数名称：int AdminUpdpsw()
* 功能描述：
*			 实现 管理密码修改 的功能  
* 参数说明：
*           
* 返回值：0
******************************************************************************************************************/

int AdminUpdpsw()
{
		Person *people;		//定义一个员工结构体people
		while(1)
		{
				int i = 0;		//定义循环的初始变量i
				int count = 0;		//count来接收获取的结点数
				int rnum = 0;			//rnum用户返回的指令
				char acName[10] = {0};		//acName数组存名字的数组
				char psw[10] = {0};		//psw存储修改密码的数组
				char opsw[10] = {0};		//psw存储修改密码的数组
				char npsw[10] = {0};		//psw存储修改密码的数组
				char ch = 0;			//用来接收getch()

				AdminUpdpsw_View();		//管理员密码修改界面
				printf("请输入需要修改密码的名字：");

				rnum = glb_putString(acName,8,3,1);
				if(rnum == 27)
				{
					return 0;
				}

				count = LIST_GetCount(people_head);

				//循环遍历寻找头结点
				for(i = 1; i <= count; i++)
				{
						people = LIST_GetNode(i,people_head);
						
						//判断是否为有效的用户
						if(0 == strcmp(people->szUsername,acName))
						{
							break;
						}
				}
				if(i>count)
				{
						printf("\n输入的名字错误\n");
						Sleep(300);
						system("cls");
						continue;
				}
				gotoxy(20,14);
				printf("请输入旧的密码：");
				rnum = glb_putString(opsw,6,3,0);
				if(rnum == 27)
				{
					return 0;
				}

				//通过遍历一个个找出用户的信息
				for (i = 1; i <= count; i++)
				{
						people = LIST_GetNode(i,people_head);
						
						//判断是否为有效的用户
						if ( 0 == strcmp(people->szPassword,opsw)  && 0 == strcmp(people->szUsername,acName))
						{
							break;
						}	
				}
				if(i>count)
				{
						printf("\n输入的密码错误\n");
						Sleep(300);
						system("cls");
						continue;
				}
				//通过遍历一个个找出用户的信息
				for (i = 1; i <= count; i++)
				{
						people = LIST_GetNode(i,people_head);
						
						//判断是否为有效的用户
						if (0 == strcmp(people->szUsername,acName))
						{
							gotoxy(20,15);
							printf("请输入新的密码(6位):");
							rnum = glb_putString(psw,6,3,0);
							if(rnum == 27)
							{
								return 0;
							}
					
							if(strlen(psw)<6)
							{
								printf("账号密码不得小于6位数！");
								Sleep(300);
								system("cls");
								break;
							}
							
							gotoxy(20,16);
							printf("请再次输入新的密码(6位):");
							rnum = glb_putString(npsw,8,3,0);
							if(rnum == 27)
							{
								return 0;
							}
							
							//输入的密码和密码进行匹配
							if(strcmp(npsw,psw) == 0)
							{
								strcpy(people->szPassword,psw);		//对内存操作
								//同步文件的数据
								FILE_update(people_fp,people,sizeof(Person),i);
								
								//当数据更新完毕,提示成功
								printf("\n修改密码成功,输入1.再次修改\n");
								ch =getch();
								if(ch == '1')
								{
									acName[10] = 0;
								}
								else
								{
									return -3;  //跳出多重循环进行标记  
								}
								break;
							}
							else
							{
								printf("\n输入的两次密码不一致，输入1.再次修改\n");
								ch =getch();
								if(ch == '1')
								{
									acName[10] = 0;
								}
								else
								{
									return -3;  //跳出多重循环进行标记  
								}
								break;
							}			
						}
				}
		}	
		return 0;
}



/*****************************************************************************************************************
* 函数名称：int AdminRecover()
* 功能描述：
*			 实现 恢复用户 的功能  
* 参数说明：
*           
* 返回值：0
******************************************************************************************************************/


int AdminRecover()
{
	while(1)
	{
			int i = 0;				//定义循环的初始变量i
			int count = 0;			//count来接收获取的结点数
			int num = 0;			//定义num变量作为序列号
			Person *people;			//定义一个员工结构体people
			char ch = 0;			//定义数组ch接受输入命令
			int rnum = 0;			//定义变量rnum来接收返回
			int flag = 0;			//定义变量flag作为标记  方便返回	
			char acName[10]={0};	//定义变量acName来作为输入的账号
			int flag1 = 0;			//定义flag1标志位为返回
			
			system("cls");
			AdminRecover_View();	//恢复成员显示界面

			printf("\t序号      姓名        	身份		账号		余额		状态\n");
			
			//遍历链表
			count = LIST_GetCount(people_head);
			
			//通过遍历一个个找出用户的信息
			for(i = 1; i <= count; i++)
			{
				people = LIST_GetNode(i,people_head);
				
				//判断是否为有效的用户	
					num++;
					//根据他们的身份是否匹配进行打印出来
					switch (people->iRole)
					{
					case 0:					//0为管理员身份
						{
							printf("\t%-6d     %-10s 	管理员",num,people->szUsername,people->iRole);
							printf("		%8d",people->AccountNumber);
							printf("	%.2f",people->fMoney);
							switch(people->iVilid)
							{
							case 0:
								{
										printf("		销户\n");
								}
								break;
							case 1:
								{
										printf("		开户\n");
								}
								break;
							}
			
						}
						break;
					case 1:					//1为用户身份
						{
							printf("\t%-6d     %-10s   普通用户",num,people->szUsername,people->iRole);
							printf("	%8d",people->AccountNumber);
							printf("	%.2f",people->fMoney);
							switch(people->iVilid)
							{
							case 0:
								{
									printf("		销户\n");
								}
								break;
							case 1:
								{
									printf("		开户\n");
								}
								break;
							}
						}
						break;
					}	
			}		/*		end of for(i = 1; i <= count; i++)	*/

			printf("\n请输入恢复用户的姓名：");
			rnum = glb_putString(acName,8,3,1);

			//如果输入esc返回
			if(rnum == 27)
			{
				return 0;
			}
			
			//遍历
			count = LIST_GetCount(people_head);
			
			//进行循环遍历找到对应账号的结点
			for (i = 1; i <= count; i++)
			{
				people = LIST_GetNode(i,people_head);
				if(0 == strcmp(people->szUsername,acName))
				{
					//匹配同一用户
					if (people->iVilid == 0)
					{
					
						people->iVilid = 1; //对内存操作
						
						//同步文件的数据
						FILE_update(people_fp,people,sizeof(Person),i);
						
						printf("\n恢复用户成功,输入1.再次恢复 2.返回上一级\n");
						ch =getch();
						if(ch == '1')
						{
							system("cls");
							acName[10] = 0;
							i = count;
							flag1 = 1;
						}
						else
						{
							flag = 1;  //跳出多重循环进行标记  
						}
						break;
					}
					else
					{
						printf("\n此为用户已开户！\n");
						i = count;
						Sleep(500);
						continue;
					}
				}		
			}

			//判断flag1的值,为上一循环传过来的值,是否继续
			if(flag1 == 1)
			{
				continue;
			}
			
			//如果遍历找不到,就提示错误
			if(i > count)
			{
				
				printf("\n输入错误,输入1.再次恢复 2.返回上一级\n");
				ch =getch();
				if(ch == '1')
				{
					system("cls");
					acName[10] = 0;
					continue;
				}
				else
				{
					break;
				}
			}
			
			//当用户输入返回，使flag值赋值为1，返回出去
			if (flag == 1)
			{
				break;
			}

	}
	return 0;
}


/*****************************************************************************************************************
* 函数名称：int AdminPassword()
* 功能描述：
*			 实现 查看用户密码 的功能  
* 参数说明：
*           
* 返回值：0
******************************************************************************************************************/

int AdminPassword()
{
		int i = 0;			//定义循环的初始变量i
		int count = 0;		//count来接收获取的结点数		
		Person *people;		//定义一个员工结构体people
		char ch[10] = {0};	//定义数组ch接受输入命令

		while(1)
		{
				int num = 0;				//num来表示序列号
				char acPsw[100] = {0};		//输入的密码存储数组

				AdminPassword_View();		//管理员查询密码界面显示
				
				gotoxy(15,16);
				printf("请输入9位密码:");
				if(glb_putString(acPsw,9,3,1) == 27)
				{
					
						return 27;
				}
				if( 0 == strcmp("gaoguikun",acPsw))
				{
						system("cls");
						AdminPassword_View();			
						printf("\t序号       姓名          身份  		账号	   	 密码	\n");
						//遍历链表
						count = LIST_GetCount(people_head);

						//通过遍历一个个找出用户的信息
						for (i = 1; i <= count; i++)
						{
								people = LIST_GetNode(i,people_head);
							
								//判断是否为有效的用户
								if (people->iVilid == 1)
								{		
									
									//根据他们的身份是否匹配进行打印出来
										switch (people->iRole)
										{
										case 1:					//1为用户身份
											{
													num++;
													printf("\t%-6d     %-10s   普通用户",num,people->szUsername);
													printf("	%8d",people->AccountNumber);
													printf("	%s\n",people->szPassword);
											}
											break;
										}
								}
							
						}

						system("pause");
						break;
				}
				gotoxy(15,18);
				printf("密码错误,请重新登录！\n");
				Sleep(700);
				gotoxy(34,6);
				printf("           \n");		//密码输入的位置进行清空
				gotoxy(24,7);
				printf("                             \n");		//提示密码错误语句进行清空
		}
		return 0;
}

