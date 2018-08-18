#include "head.h"
#include "LOGIC_public.h"
#include "VIEW_login.h"


char tmp[64] = {0};		//定义时间变量来获取时间,局部变量不安全

/*****************************************************************************************************************
* 函数名称：int putString(char acStr[100], int iMaxlen, int iputType, int isPlainttext)
* 功能描述：
*			 实现 明密文 的功能  
* 参数说明：
*           char acStr[100] --存放字符的数组 int iMaxlen --输入字符的最大长度  int iputType --输入字符的类型
*			int isPlainttext --控制明密文 1为明文,0为密文
* 返回值：0
******************************************************************************************************************/

int glb_putString(char acStr[100], int iMaxlen, int iputType, int isPlainttext)
{
		char ch;				//定义ch来接受getch();
		int iLenth = 0;			//定义一个字符长度来计算输入的个数
			
		while(1)
		{
				ch = getch();
				if(ch == '\r')		//回车 删除
				{
						acStr[iLenth] = '\0';
						break;
				}
				if(ch == '\t')
				{
						acStr[iLenth] = '\0';
						break;
				}
				if(ch == '\b')		//删除字符
				{
						if(iLenth > 0)
						{
							printf("\b \b");
							iLenth--;				//回删要减个数
							acStr[iLenth] = '\0';
						}
				}
				if(ch == 27)
				{
					return 27;
				}
				if(iLenth < iMaxlen)				//判断长度是否小于最大长度
				{
						switch(iputType)             //输入的类型1为数字,2为字母,3为数字与字母
						{
						case 1:
							{
									if(ch >= '0' && ch <= '9')			//只能输入数字
									{
											if(isPlainttext)
											{
													putchar(ch);	//明文
											}
											else
											{
													putchar('*');	//密文
											}
											acStr[iLenth]= ch;		//输入的字符存进数组acStr[ilenth]
											iLenth++;				//进行计算输入的个数
									}	
							}
							break;
						case 2:
							{
									if(ch >= 'a' && ch <= 'z')		//只能输入字母
									{
											if(isPlainttext)
											{
													putchar(ch);	//明文
											}
											else
											{
													putchar('*');	//密文
											}
											acStr[iLenth]= ch;		//输入的字符存进数组acStr[ilenth]
											iLenth++;				//进行计算输入的个数
									}	
							}
							break;
						case 3:
							{
									if(ch >= '0' && ch <= '9' || ch >= 'a' && ch <= 'z')	//可以输入字母和数字
									{
											if(isPlainttext)
											{
													putchar(ch);	//明文
											}
											else
											{
													putchar('*');	//密文
											}
											acStr[iLenth] = ch;		//输入的字符存进数组acStr[ilenth]	
											iLenth++;				//进行计算输入的个数
									}
							}
							break;
						default:
							{
									printf("输入错误\n");
							}
							break;
						}
					}
				else
				{
					continue;
				}
		}	
		return 0;	
}


/*****************************************************************************************************************
* 函数名称：int gotoxy(int x,int y)
* 功能描述：
*			 实现 光标 的功能  
* 参数说明：
*           int x --x坐标   int y  --y坐标
* 返回值：0
******************************************************************************************************************/

int gotoxy(int x,int y)
{
		HANDLE handle;								//设置句柄
		COORD coord;								//设置光标
		coord.X=x;									//定义x坐标
		coord.Y=y;									//定义y坐标
		handle=GetStdHandle(STD_OUTPUT_HANDLE);		//获取标准句柄
		SetConsoleCursorPosition(handle,coord);		//设置光标控制
		return 0;
}


/*****************************************************************************************************************
* 函数名称：int select_interface(int max,int x,int y)
* 功能描述：
*			 实现 光标,退出,返回 的功能  
* 参数说明：
*           int max  --代表可以选择的选项有几个		x ---光标x坐标	y --光标y坐标
* 返回值：count
******************************************************************************************************************/

int select_interface(int max,int x,int y)
{
		int count = 1;		//跟踪坐标的数值
		int confirm = 0;	//跟踪确认的数值
		int i = 0;
		
		gotoxy(x,y);
		printf("\b★\b");

		while(1)
		{		
				
				switch(getch())
				{
				case KEY_UP:           //上
				case KEY_LEFT:		   //左
					{
							//当向上指令,通过改变其数值 来跟踪坐标的偏移
							if(count == 1)
							{
								count = max;			//直接令光标的位置为count计数等于选项的个数		
							}
							else
							{
								count--;				//光标count进行递减
							}
					}
					break;
				case KEY_DOWN:         //下
				case KEY_RIGHT:		 //右
					{
							//当向下指令,通过改变其数值 来跟踪坐标的偏移
							if(count == max)
							{
								count = 1;
							}
							else
							{
								count++;
							}
					}
					break;
				case '\r':		//回车键

							confirm = 1;	

					break;
				case 'q':
				case 'Q':		//q、Q退出游戏
					{
						if(select_quit() == -1)
						{
							gotoxy(x,y);
						}
					}
					break;
				case KEY_ESC:			//返回
					{
					
						if(select_return() == -3)			//返回的函数返回值为-3,就返回出去
						{
							return -3;			
						}
						else
						{
							gotoxy(x,y);
						}
					}
					break;
				default:
					break;
				}	/* end of switch(getch())	*/
				
				switch(count)			//光标跳转
				{
				case 1:
					{
							printf("\b☆\b");		//光标的覆盖
							gotoxy(x,y);
							printf("\b★\b");		//光标的显示
					}
					break;
				case 2:
					{
							printf("\b☆\b");
							gotoxy(x,y+2);
							printf("\b★\b");
					}
					break;
				case 3:
					{
							printf("\b☆\b");
							gotoxy(x,y+4);
							printf("\b★\b");
					}
					break;
				case 4:
					{
							printf("\b☆\b");
							gotoxy(x,y+6);
							printf("\b★\b");
					}
					break;
				case 5:
					{
							printf("\b☆\b");
							gotoxy(x,y+8);
							printf("\b★\b");
					}
					break;
				case 6:
							printf("\b☆\b");
							gotoxy(x,y+10);
							printf("\b★\b");
					break;
				default :
					break;
				}	/* end of switch(count))	*/

				//如果confirm标志位为1 返回出去
				if(confirm == 1)
				{
					break;
				}
		}	/*	end of while(1)	*/	

		return count;
}


/*****************************************************************************************************************
* 函数名称：int putNum(char acStr[100],int iMaxlen,int iputType)
* 功能描述：
*			 实现 封装输入字符 的功能  
* 参数说明：
*           char acStr[100]  --字符存储的数组	int iMaxlen --最大可输入个数     int iputType --输入的类型
* 返回值：0
******************************************************************************************************************/

int putNum(char acStr[100],int iMaxlen,int iputType)
{
	char ch;
	int iLenth=0;
	while(1)
	{
			ch=getch();

			//回车 删除
			if(ch=='\r')
			{
					acStr[iLenth]='\0';
					break;
			}
			if(ch=='\b')
			{
					if(iLenth>0)
					printf("\b \b");
					iLenth--;//回删要减个数
					acStr[iLenth]='\0';
			}
			if(ch == 27)
			{
				return 27;
			}
		
			if(iLenth<iMaxlen)
			{
					switch(iputType)
					{
					case 1:
						{
							if(ch>='0'&&ch<='9')			//输出数字
							{
									putchar(ch);
									acStr[iLenth]= ch;
									iLenth++;
							}
							
						}
						break;
					case 2:
						{
							{	
								if(ch>='A'&&ch<='Z')		//输出大写字母
								{
										putchar(ch);
										acStr[iLenth]= ch;
										iLenth++;
								}
								
							}
						}
						break;
					case 3:
						{
							{
								if(ch>='0'&&ch<='9'||ch>='a'&&ch<='z')		//输出小写字母
								{
										putchar(ch);
										acStr[iLenth]= ch;
										iLenth++;
								}				
							}
						}
						break;
					default:
						{
								printf("   输入错误\n");
						}
						break;
					}
			}
	}	
	return 0;	
}



/*****************************************************************************************************************
* 函数名称：void public_num(char *acBuf)
* 功能描述：
*			 实现 输入一个字符 的功能  
* 参数说明：
*           char *acBuf  --字符存储的数组	
* 返回值：0
******************************************************************************************************************/

int public_num(char *acBuf)
{
		char ch = 0,ch1 = 0;
		int i = 0;
		int lenth = 1;
		while (1)
		{
				ch = getch();
				if(ch == '\r')
				{
						*acBuf = 0;			//确定后，acbuf数组归0
						break;
				}
				else if (ch >= '0' && ch <= '9')		//输出数字
				{
					  if(i < lenth)
					  {	
							putchar(ch);
							*acBuf = 0;
							*acBuf++ = ch;
							i++;
					  }
				}
				if(ch == 27)
				{
					return 27;
				}
				else if((unsigned char)ch>=0xa1 && (unsigned char)ch<=0xfe)		//输出两个字符
				{
						ch1 = getch();
						printf("%c%c",ch,ch1);
						*acBuf++ = ch;
						*acBuf++ = ch1;
				}
				else if (ch == '\b')
				{
						if (i>0)
						{
								if((unsigned char)ch>=0xa1 && (unsigned char)ch<=0xfe)		//进行回删
								{
										printf("\b \b\b \b");
										*acBuf-- = 0;
										*acBuf = 0;	
								}
								else
								{
										printf("\b \b");
										*acBuf--;
										*acBuf = 0;
								}
								i--;		//字符减少
						}
				}
				else 
				{
					continue;
				}
		}
		return 0;
}


/*****************************************************************************************************************
* 函数名称：int select_retrunorquit(int max,int x,int y)
* 功能描述：
*			 实现 返回退出 的功能  
* 参数说明：
*           	
* 返回值：0
******************************************************************************************************************/

int select_retrunorquit(int max,int x,int y)
{
		int count = 1;		//跟踪坐标的数值
		int confirm = 0;	//跟踪确认的数值
		int i = 0;			//循环的初始值变量i
		
		gotoxy(x,y);
		printf("\b★\b");
		while(1)
		{		
				
				switch(getch())
				{
				case KEY_UP:           //上
				case KEY_LEFT:		   //左
					{
							//当向上指令,通过改变其数值 来跟踪坐标的偏移
							if(count == 1)
							{
								count = max;	
							}
							else
							{
								count--;
							}
					}
					break;
				case KEY_DOWN:         //下
				case KEY_RIGHT:		 //右
					{
							//当向下指令,通过改变其数值 来跟踪坐标的偏移
					
							if(count == max)
							{
								count = 1;
							}
							else
							{
								count++;
							}
					}
					break;
				case '\r':		//回车键

							confirm = 1;	

					break;
				case 'q':
				case 'Q':		//q、Q退出游戏
					{
						continue;
					}
					break;
				case KEY_ESC:			//返回
					{
						continue;
					}
					break;
				default:
					break;
				}	/*	end of switch(getch())	*/
				
				switch(count)			//光标跳转
				{
				case 1:
					{
							printf("\b☆\b");			//光标的覆盖
							gotoxy(x,y);
							printf("\b★\b");			//光标的显示
					}
					break;
				case 2:
					{
							printf("\b☆\b");
							gotoxy(x,y+2);
							printf("\b★\b");
					}
					break;
				case 3:
					{
							printf("\b☆\b");
							gotoxy(x,y+4);
							printf("\b★\b");
					}
					break;
				case 4:
					{
							printf("\b☆\b");
							gotoxy(x,y+6);
							printf("\b★\b");
					}
					break;
				case 5:
					{
							printf("\b☆\b");
							gotoxy(x,y+8);
							printf("\b★\b");
					}
					break;
				case 6:
							printf("\b☆\b");
							gotoxy(x,y+10);
							printf("\b★\b");
					break;
				default :
					break;
				}	/*	end of switch(count)	*/

				//如果标志位confirm为1 返回出去
				if(confirm == 1)
				{
					break;
				}
		}	/*	end of while(1)	*/	
		return count;
}


/*****************************************************************************************************************
* 函数名称：int select_quit()
* 功能描述：
*			 实现 退出选择 的功能  
* 参数说明：
*           	
* 返回值：0
******************************************************************************************************************/

int select_quit()
{
	while(1)
	{					
		int i = 0;
		QuitView();
		switch(select_retrunorquit(2,47,25))
		{
		case 1:
			{
					gotoxy(30,25);
					printf("                                           ");		//提示命令进行清空
					gotoxy(30,26);
					printf("                                            ");			//提示命令进行清空
					gotoxy(30,27);
					printf("		                                       ");
	
					gotoxy(30,27);
					printf("退出系统,");
					Sleep(200);
					printf("请稍等>");

					//实现加载的效果
					for (i=0;i<20;i++)
					{
							printf(">");
							Sleep(50);
					}
					Sleep(300);
					system("cls");
					gotoxy(15,15);
					printf("欢迎下次继续使用！");
					exit(0);							
			}
			break;
		case 2:
			{
					gotoxy(30,25);
					printf("                                           ");		//提示命令进行清空
					gotoxy(30,26);
					printf("                                            ");			
					gotoxy(30,27);
					printf("		                                       ");
					return -1;							
			}
			break;
		default:
			{
				printf("输入错误");
			}
			break;
		}
	}
		return 0;
}


/*****************************************************************************************************************
* 函数名称：int select_return()
* 功能描述：
*			 实现 返回选择 的功能  
* 参数说明：
*           	
* 返回值：0
******************************************************************************************************************/

int select_return()
{
	while(1)
	{

		int i = 0;			//循环的初始变量i	

		ReturnView();		//返回界面

		switch(select_retrunorquit(2,47,25))			//退出和返回的光标选择 2代表选择项数   47,25定位位置
		{
		case 1:
			{
					return -3;							
			}
			break;
		case 2:
			{
					gotoxy(30,25);
					printf("                                           ");		//提示命令进行清空
					gotoxy(30,26);
					printf("                                            ");			//提示命令进行清空
					gotoxy(30,27);
					printf("		                                       ");
					return -1;							
			}
			break;
		default:
			{
				ReturnView();
			}
			break;
		}
	}
	return 0;
}


/*****************************************************************************************************************
* 函数名称：void Banktips()
* 功能描述：
*			 实现 小贴士 的功能  
* 参数说明：
*           	
* 返回值：
******************************************************************************************************************/

void Banktips()
{
	int i=0;
	srand(time(0));			//设立一次种子
	i=rand()%10;
	gotoxy(15,12);
	printf("																	");
	gotoxy(10,12);
	printf("	温馨提示:");
	switch(i)
	{
	case 0:
		printf("您已进入24小时监控区域");
		break;
	case 1:
		printf("在输入密码时,请注意密码安全");
		break;
	case 2:
		printf("如忘记密码,请联系管理员");
		break;
	case 3:
		printf("警惕电信诈骗,如有疑问咨询管理员");
		break;
	case 4:
		printf("离开机器时请注意取走银行卡");
		break;
	case 5:
		printf("大宗现金交易请到银行柜台办理");
		break;
	case 6:
		printf("若有疑问,请咨询管理员");
		break;
	case 7:
		printf("打击假钞,人人有责");
		break;
	case 8:
		printf("转账陌生账号时,请确认");
		break;
	case 9:
		printf("本银行支持跨行转账");
		break;
	default :
		break;
	}
}


/*****************************************************************************************************************
* 函数名称：void CurTime(int x,int y,int a)
* 功能描述：
*			 实现 获取系统时间 的功能  
* 参数说明：
*           	
* 返回值：tmp
******************************************************************************************************************/

char *CurTime(int x,int y,int a)		//从CPU获取系统当前时间
{
	time_t t = time(0);		//获取系统时间	
	gotoxy(x,y);

	switch(a)		//选择显示的时间类型
	{
	case 0:
		{
			strftime(tmp,sizeof(tmp),"%c",localtime(&t));
			printf("%s",tmp);
		}
		break;
	case 1:
		{
			strftime(tmp,sizeof(tmp),"%c",localtime(&t));
			printf("%x",tmp);		
		}
		break;
	case 2:
		{
			strftime(tmp,sizeof(tmp),"%c",localtime(&t));
			printf("%X",tmp);		
		}
		break;
	case 3:
		{
			strftime(tmp,sizeof(tmp),"%Y-%m-%d %H:%M:%S",localtime(&t));
			printf("%s",tmp);		
		}
		break;
	default:
		printf("格式错误");
		break;
	}
	return tmp;
}





 