#include "head.h"
#include "VIEW_user.h"
#include "CACHE_file.h"
#include "CACHE_list.h"
#include "CACHE_data.h"
#include "LOGIC_user.h"
#include "LOGIC_public.h"

extern FILE *people_fp;			//引进用户文件的全局变量，对文件操作必定用到文件指针
extern pNode *people_head;		//引进用户链表的全局变量，对链表操作必定用到头结点

extern FILE *trade_fp;			//引进账单文件的全局变量，对文件操作必定用到文件指针
extern pNode *trade_head;		//引进账单链表的全局变量,对链表操作必定用到头结点

extern Person g_currentUser;	//引进当前进入界面的用户，当进行存款时必定需要匹配

extern int glb_trade_id;		////全局变量账单ID


/*****************************************************************************************************************
* 函数名称：int User()
* 功能描述：
*			 实现 用户界面 的功能  
* 参数说明：
*           
* 返回值：0
******************************************************************************************************************/

int User()
{
	
	while(1)
	{
		UserView();

		gotoxy(20,10);
		printf(" 	       当前用户:%s        ",g_currentUser.szUsername);		//对当前用户进行显示

		switch(select_interface(6,36,13))
		{
		case 1:
			{
				UserQuery_View();		//用户查询余额界面
				UserQuery();			//用户查询余额
			}
			break;
		case 2:
			{
				UserDeposit();			//用户存款
			}
			break;
		case 3:
			{
				UserDraw();				//用户取款
			}
			break;
		case 4:
			{
				UserTransfer();			//用户转账
			}
			break;
		case 5:
			{
				UserUpdpsw_View();		//用户修改密码界面
				UserUpdpsw();			//用户修改密码
			}
			break;
		case 6:
			{
				UserQuerylist_View();	//用户查询账单界面
				UserQuerylist();		//用户查询账单
			}
			break;
		case -3:
			{
				system("cls");
				return main();			//返回登陆界面
			}
		default:
			break;
		}
	}
	return 0;
}


/*****************************************************************************************************************
* 函数名称：void UserQuery()
* 功能描述：
*			 实现 用户余额查询 的功能  
* 参数说明：
*           
* 返回值：0
******************************************************************************************************************/

void UserQuery()
{
		printf("\t\t\t持有人:%s\n\n",g_currentUser.szUsername);
		printf("\t\t\t账号为:%d\n\n",g_currentUser.AccountNumber);	
		printf("\t\t\t账号余额为:%.2f",g_currentUser.fMoney);
		printf("\n\n按任意键返回上一级");
		getch();
}


/*****************************************************************************************************************
* 函数名称：void UserDeposit()
* 功能描述：
*			 实现 用户存款 的功能  
* 参数说明：
*           
* 返回值：0
******************************************************************************************************************/

int UserDeposit()
{
 		int num = 0;				//定义变量num接收输入的账户
		int i = 0;					//定义变量i作为循环的初始值
		int count = 0;				//定义变量count来接获取的结点个数	
		int flag = 0;				//定义变量flag作为标记  方便返回
		int money = 0;				//定义存入的钱money
		char acmoney[2] = {0};		//定义存入的钱acmoney
		char  ch = 0;				//定义ch来作为getch的存储变量
		Person *people;				//定义一个结构体用户people
		Trade *trade;				//进行更新和追加用户金额账单

		
		while (1)
		{			
				//获取用户的个数
				count = LIST_GetCount(people_head);

				//进行循环遍历找到对应账号的结点
				for(i = 1; i <= count; i++)
				{
						people = LIST_GetNode(i,people_head);
						trade = LIST_GetNode(i,trade_head);
	
						if(people->ID == g_currentUser.ID) 
						{			
								system("cls");
								UserDeposit_View();		//用户存款界面
								printf("\t  您卡上原有余额%f元\n",g_currentUser.fMoney);     
								printf("\t  ************************************\n");  
								printf("\t  **  1: 100元    *****    2:200元  **\n");  
								printf("\t  ************************************\n");  
								printf("\t  **  3: 300元    *****    4:400元  **\n");  
								printf("\t  ************************************\n");  
								printf("\t  **  5: 500元    *****    6:600元 **\n");  
								printf("\t  ************************************\n");  
								printf("\t  请选择您要存入的余额:\n");  
								printf("\t  ");

								if(27==putNum(acmoney,1,1))
								{
									return 0;
								}

								//判断输入的字符是否符合界面显示的条件
								money = atoi(acmoney);
								if(money>6||money<=0)
								{
									printf("输入的金额有误,请重新输入！");
									Sleep(500);
									continue;
								}

								money=100*money;  //对应选项乘以一百为取款金额  
								g_currentUser.fMoney+=money;  //对金额进行处理 

								//同步文件的数据
								FILE_update(people_fp,&g_currentUser,sizeof(Person),i);
								
								//更新初始账单
								trade->way = 1; 
								trade->from = people->AccountNumber;
								trade->num = people->AccountNumber;
								trade->sum = money;
								trade->balance = (int)g_currentUser.fMoney;
								trade->date,strcpy(trade->date,CurTime(10,25,3));
								FILE_update(trade_fp,trade,sizeof(Trade),i);//更新文件
								
								//追加一条新的账单
								glb_trade_id++;
								trade->way = 1; 
								trade->from = people->AccountNumber;
								trade->num = people->AccountNumber;
								trade->sum = money;
								trade->rank = glb_trade_id;
								trade->balance = (int)g_currentUser.fMoney;
								strcpy(trade->date,CurTime(10,25,3));
								FILE_add(trade_fp,trade,sizeof(Trade));		
								
								//加载数据
								gotoxy(25,25);
								printf("\n\t  正在存入中请稍侯。。。。。\n\t\t");

								for(i=0;i<10;i++)  
								{  
										printf("■");  
										Sleep(100);  
								}
								
								printf("\n\t  您已经成功存入%d元\n",money); 
								Sleep(500);
								printf("\t  存款成功,输入1.再次存入 2.返回上一级\n");
								printf("\t\t");
								ch =getch();

								if(ch == '1')
								{
										num = 0;
								}
								else
								{
										flag = 1;  //跳出多重循环进行标记  
								}

								break;
						}	/* end of if(people->ID == g_currentUser.ID)  */
				}	/* end of for(i = 1; i <= count; i++) */
				
				//当用户输入返回，使flag值赋值为1，返回出去
				if (flag == 1)
				{
						break;
				}

		}	/* end of while(1) */
		return 0;
}



/*****************************************************************************************************************
* 函数名称：int UserDraw()
* 功能描述：
*			 实现 用户取款 的功能  
* 参数说明：
*           
* 返回值：0
******************************************************************************************************************/

int UserDraw()
{
		int num = 0;				//定义变量num接收输入的账户
		int i = 0;					//定义变量i作为循环的初始值
		int count = 0;				//定义变量count来接获取的结点个数
		int flag = 0;				//定义变量flag作为标记  方便返回	
		int money = 0;				//定义取出的钱money	
		char acmoney[2] = {0};		//定义存入的钱acmoney
		char  ch = 0;				//定义ch来作为getch的存储变量
		Person *people;				//定义一个结构体用户people
		Trade *trade;				//进行更新和追加用户金额账单

		while (1)
		{		
				//遍历
				count = LIST_GetCount(people_head);
				
				//进行循环遍历找到对应账号的结点
				for(i = 1; i <= count; i++)
				{
					people = LIST_GetNode(i,people_head);
					trade = LIST_GetNode(i,trade_head);

					if(people->ID == g_currentUser.ID) 
					{			
							system("cls"); 
							UserDraw_View();		//用户取款界面
							printf("\t  您卡上原有余额%f元\n",g_currentUser.fMoney);     
							printf("\t  ************************************\n");  
							printf("\t  **  1: 100元    *****    2:200元  **\n");  
							printf("\t  ************************************\n");  
							printf("\t  **  3: 300元    *****    4:400元  **\n");  
							printf("\t  ************************************\n");  
							printf("\t  **  5: 500元    *****    6:600元 **\n");  
							printf("\t  ************************************\n");  
							printf("\t  请选择您要取出的余额\n");  
							printf("\t  ");
							if(27==putNum(acmoney,1,1))
							{
								return 0;
							}

							//判断输入的字符是否符合界面显示的条件
							money = atoi(acmoney);
			
							if(money>6||money<=0)
							{
								printf("输入的金额有误,请重新输入！");
								Sleep(500);
								continue;
							}

							money=100*money;  //对应选项乘以一百为取款金额

							//判断输入的金额是否大于余额
							if(money > g_currentUser.fMoney)
							{
									printf("余额不足！");
									Sleep(500);
									break;
							}

							g_currentUser.fMoney-=money;  //对金额进行处理
							
							//同步用户的数据
							FILE_update(people_fp,&g_currentUser,sizeof(Person),i);
									
							//更新初始账单
							trade->way = 2; 
							trade->from = people->AccountNumber;
							trade->num = people->AccountNumber;
							trade->sum = money;
							trade->balance = (int)g_currentUser.fMoney;
							strcpy(trade->date,CurTime(10,25,3));
							FILE_update(trade_fp,trade,sizeof(Trade),i);//更新文件
							
							//追加一条新的账单
							glb_trade_id++;
							trade->way = 2; 
							trade->from = people->AccountNumber;
							trade->num = people->AccountNumber;
							trade->sum = money;
							trade->rank = glb_trade_id;
							trade->balance = (int)g_currentUser.fMoney;
							strcpy(trade->date,CurTime(10,25,3));
							FILE_add(trade_fp,trade,sizeof(Trade));	
						
							//加载数据
							gotoxy(25,25);
							printf("\n\t  正在取出中请稍侯。。。。。\n\t\t");
							for(i=0;i<10;i++)  
							{  
									printf("■");  
									Sleep(100);  
							}
							
							printf("\n\t  您已经成功取出%d元\n",money); 
							Sleep(500);
							printf("\t  取款成功,输入1.再次取出 2.返回上一级\n");
							printf("\t\t");
							ch =getch();

							if(ch == '1')
							{
									num = 0;
							}
							else
							{
									flag = 1;  //跳出多重循环进行标记  
							}

							break;
					}	/* end of if(people->ID == g_currentUser.ID) */
				}	/* end of for(i = 1; i <= count; i++) */
				
				//当用户输入返回，使flag值赋值为1，返回出去
				if (flag == 1)
				{
					break;
				}

		}	/* end of while(1) */
		return 0;
}


/*****************************************************************************************************************
* 函数名称：void UserTransfer()
* 功能描述：
*			 实现 用户转账 的功能  
* 参数说明：
*           
* 返回值：0
******************************************************************************************************************/

int UserTransfer()
{
		int flag = 0;				//定义变量flag作为标记  方便返回
		char fnum[10] = {0};		//第一次输入的账号
		char snum[10] = {0};		//再次确认的账号
		int money = 0;				//输入的金额
		int i = 0;					//定义变量i作为循环的初始值
		int count = 0;				//定义变量count来接获取的结点个数
		int rnum = 0;				//rnum返回的值
		char acmoney[2] = {0};		//定义存入的钱acmoney
		char  ch = 0;				//定义ch来作为getch的存储变量
		Trade *trade;				//进行更新和追加用户金额账单
		Person *people;				//定义一个结构体用户people
		Person *tpeople;			//定义一个结构体用户people
		
		while (1)
		{		
				UserTransfer_View();	//用户转账界面显示
				
				gotoxy(7,10);
				printf("请输入转账对方的名字:");  
				rnum = glb_putString(fnum,8,3,1);
				
				if(rnum == 27)
				{
					return 0;
				}
				
				gotoxy(7,11);
				printf("请再次输入转账对方的名字:");  
				rnum = glb_putString(snum,8,3,1);
				
				if(rnum == 27)
				{
					return 0;
				}
				
				//判断是否为原账户
				if(0 == strcmp(g_currentUser.szUsername,fnum))
				{
						printf("\n不能转给原账户\n");
						Sleep(500);
						continue;
				}
				
				//判断第一次输入的账号和第二次输入的账号是否匹配
				if(0 != strcmp(fnum,snum))  
				{  
						printf("\n两次用户名不同，请重新输入\n"); 
						Sleep(500);
						continue; 
				}

				//遍历
				count = LIST_GetCount(people_head);
				
				//进行循环遍历找到对应账号的结点
				for (i = 1; i <= count; i++)
				{
						people = LIST_GetNode(i,people_head);
						trade = LIST_GetNode(i,trade_head);
						tpeople = LIST_GetNode(i,people_head);
						if(people->iVilid == 1)
						{
								if(0 == strcmp(people->szUsername,fnum)) 
								{	
									while(1)
									{
										system("cls");  
										UserTransfer_View();
										printf("\t  您卡上原有余额%f元\n",g_currentUser.fMoney);     
										printf("\t  ************************************\n");  
										printf("\t  **  1: 100元    *****    2:200元  **\n");  
										printf("\t  ************************************\n");  
										printf("\t  **  3: 300元    *****    4:400元  **\n");  
										printf("\t  ************************************\n");  
										printf("\t  **  5: 500元    *****    6:600元 **\n");  
										printf("\t  ************************************\n");   	
										printf("\t  请输入转账金额\n");
										printf("\t  ");
										if(27==putNum(acmoney,1,1))
										{
											return 0;
										}
										//判断输入的字符是否符合界面显示的条件
										money = atoi(acmoney);
										if(money>6 || money<=0)  
										{  
											printf("对不起，您的输入有误\n"); 
											Sleep(500);
											continue;  
										}  
										money=100*money;  //对应选项乘以一百为取款金额
										if(money > g_currentUser.fMoney)
										{
												printf("余额不足！\n");
												Sleep(500);
												continue;
										}

										//转账人的余额
										g_currentUser.fMoney-=money;  //对金额进行处理 

										//同步文件的数据，第i个为此时匹配到的用户
										FILE_update(people_fp,&g_currentUser,sizeof(Person),i);	
										
						
										//更新初始账单
										trade->way = 3; 
										trade->from = people->AccountNumber;
										trade->num = g_currentUser.AccountNumber;
										trade->sum = money;
										trade->balance = (int)g_currentUser.fMoney;
										strcpy(trade->date,CurTime(10,25,3));
										FILE_update(trade_fp,trade,sizeof(Trade),g_currentUser.ID);//更新文件				
										
										//追加一条新的账单
										glb_trade_id++;
										trade->way = 3; 
										trade->from = people->AccountNumber;
										trade->num = g_currentUser.AccountNumber;
										trade->sum = money;
										trade->rank = glb_trade_id;
										trade->balance = (int)g_currentUser.fMoney;
										strcpy(trade->date,CurTime(10,25,3));
										FILE_add(trade_fp,trade,sizeof(Trade));	
										
										//被转账人的余额
										people->fMoney+=money;

										//同步文件的数据，第i个为此时匹配到的用户
										FILE_update(people_fp,people,sizeof(Person),i);

										//更新初始账单
										trade->way = 4; 
										trade->from = g_currentUser.AccountNumber;
										trade->num = tpeople->AccountNumber;
										trade->sum = money;
										trade->rank = people->ID;
										trade->balance = (int)people->fMoney;
										strcpy(trade->date,CurTime(10,25,3));
										FILE_update(trade_fp,trade,sizeof(Trade),i);//更新文件
										
										//追加一条新的账单
										glb_trade_id++;
										trade->way = 4; 
										trade->from = g_currentUser.AccountNumber;
										trade->num = tpeople->AccountNumber;
										trade->sum = money;
										trade->rank = glb_trade_id;
										trade->balance = (int)people->fMoney;
										strcpy(trade->date,CurTime(10,25,3));
										FILE_add(trade_fp,trade,sizeof(Trade));	

										//加载数据
										gotoxy(25,25);
										printf("\n\t  正在转款中请稍侯。。。。。\n\t\t");
										for(i=0;i<10;i++)  
										{  
												printf("■");  
												Sleep(100);  
										}
					
										printf("\n\t  您已经成功转出%d元\n",money); 
										Sleep(500);
										printf("\t  转款成功,输入1.再次转出 2.返回上一级\n");
										printf("\t\t");
										ch =getch();
										if(ch == '1')
										{
												fnum[10] = 0;		//用户名归零
												snum[10] = 0;		//用户名归零
												continue;
										}
										else
										{
												flag = 1;  //跳出多重循环进行标记  
										}
										break;
									}	/* end of while(1) */
								}	/* end of if (people->AccountNumber == snum) */		
						}	/* end of if(people->ID == g_currentUser.ID) */
				}	/* end of for(i = 1; i <= count; i++) */
				
				//当用户输入返回，使flag值赋值为1，返回出去
				if (flag == 1)
				{
					break;
				}
				if(i>count)
				{
					printf("账号不存在！");
					Sleep(500);
					continue;
				}
			

		}	/* end of while(1) */
		return 0;
}




/*****************************************************************************************************************
* 函数名称：int UserUpdpsw()
* 功能描述：
*			 实现 用户密码修改 的功能  
* 参数说明：
*           
* 返回值：0
******************************************************************************************************************/

int UserUpdpsw()
{
		while(1)
		{
				int i = 0;				//i用来作为循环的初始变量
				int count = 0;			//count来接收获取的结点数
				int num = 0;			//num变量存账号的数组
				char psw[10] = {0};		//psw存储修改密码的数组
				char opsw[10] = {0};	//psw存储修改密码的数组
				char npsw[10] = {0};	//psw存储修改密码的数组
				char ch = 0;			//ch用来接收getch()

				UserUpdpsw_View();		//管理员密码修改界面
				gotoxy(20,13);	
				printf("请输入旧的密码(6位)：");
				if(27 == glb_putString(opsw,6,1,0))
				{
						return 0;
				}

				//通过遍历一个个找出用户的信息
				if(0 != strcmp(g_currentUser.szPassword,opsw))
				{
						printf("输入的密码错误\n");
						Sleep(300);
						system("cls");
						continue;
				}

				
				gotoxy(20,14);
				printf("请输入新的密码(6位):");
				if(27 == glb_putString(psw,6,1,0))
				{
					return 0;
				}
				if(strlen(psw)<6)
				{
						printf("\n\t\t账号密码不得小于6位数！");
						system("pause");
						continue;
				}

				gotoxy(20,15);
				printf("请再次输入新的密码(6位):");
				if(27 == glb_putString(npsw,6,1,0))
				{
					return 0;
				}
				
				if(strcmp(npsw,psw) == 0)
				{
						strcpy(g_currentUser.szPassword,psw);		//对内存操作
						//同步文件的数据
						FILE_update(people_fp,&g_currentUser,sizeof(Person),g_currentUser.ID);
						
						//当数据更新完毕,提示成功
						printf("\n\t\t修改密码成功,输入1.再次修改 2.返回上一级\n");
						ch =getch();
						if(ch == '1')
						{
								num = 0;
								continue;
						}
						else
						{
								return -3;  //跳出多重循环进行标记  
						}
						break;
				}
				else
				{
						printf("\n\t\t输入的两次密码不一致，输入1.再次修改 2.返回上一级\n");
						ch =getch();
						if(ch == '1')
						{
								num = 0;
								continue;
						}
						else
						{
								return -3;  //跳出多重循环进行标记  
						}
						break;
				}		
		}

		return 0;
}

int UserQuerylist()
{
		int i = 0;			//定义循环的初始变量i
		int count = 0;		//count来接收获取的结点数
		Trade *trade;		//定义一个员工结构体people
		char ch[10] = {0};	//定义数组ch接受输入命令
		int num = 0;		//num序列号
		char ch1 = 0;		//变量ch1获取字符
		int page=0;			//page当前页
		int flag = 0;		//flag标志位

		
		trade_fp = FILE_open("data/trade/trade.txt");
		trade_head=FILE_read(trade_fp,sizeof(Trade));
		if(	trade_head->next == NULL)
		{
			trade_head = TRADE_Data(trade_fp);		
		}
		//遍历链表
		while(!flag)
		{
			
			UserQuerylist_View();
			gotoxy(25,20);
			printf("↑向上翻页 ↓向下翻页 ESC退出");
			gotoxy(0,7);
			printf("\t序号	状态		交易额		余额		账单号归属	账单生成时间			交易发生对象\n");
		
			count = LIST_GetCount(trade_head);
		
			
			//通过遍历一个个找出用户的信息
			for (i = 1+page*10; i <= (page+1)*10; i++)		//每次翻10页 用关于page页数的数学公式来作为循环的条件和初始条件
			{
				trade = LIST_GetNode(i,trade_head);
				if(trade == NULL)
				{
					break;
				}

				//序列号
				num++;

				//判断是否为有效的用户
				switch(trade->way)
				{
				case 0:
					{
						printf("\t%-6d	原始 		%-10d	%-10d",num,trade->sum,trade->balance);
						printf("	%d",trade->num);
						printf("	%s",trade->date);
						printf("	ATM\n");
					}
					break;
				case 1:
					{
						printf("\t%-6d	存款 		+%-10d	%-10d",num,trade->sum,trade->balance);
						printf("	%d",trade->num);
						printf("	%s",trade->date);
						printf("	ATM\n");
					}
					break;
				case 2:
					{
						printf("\t%-6d	取款 		-%-10d	%-10d",num,trade->sum,trade->balance);
						printf("	%d",trade->num);
						printf("	%s",trade->date);
						printf("	ATM\n");
					}
					break;
				case 3:
					{
						printf("\t%-6d	转出 		-%-10d	%-10d",num,trade->sum,trade->balance);
						printf("	%d",trade->num);	
						printf("	%s",trade->date);
						printf("	%d\n",trade->from);
					}
					break;
				case 4:
					{
						printf("\t%-6d	转入 		+%-10d	%-10d",num,trade->sum,trade->balance);
						printf("	%d",trade->num);	
						printf("	%s",trade->date);
						printf("	%d\n",trade->from);
					}
					break;
				default:
					break;
				}
		

			}

			//循环一次页数增加
			page++;

			while(1)
			{
				ch1 = getch();
				if(ch1 == 27)
				{
					return 0;
				}
				if (ch1 == 'w' || ch1 == 72 || ch1 == 'W')
				{
					if (page < 2)				//页数进行判断
					{
						continue;
					}
					num = (page - 2) * 10;		
					page = page - 2;
					break;
				}
				if (ch1 == 's' || ch1 == 80 || ch1 == 'S')
				{
					if (page * 10 >= count)		//总条数进行判断
					{
						continue;
					}
					num = page * 10;
					break;
				}	
				
			}
		}	/* end of while(!flag) */
		
		return 0;
}

