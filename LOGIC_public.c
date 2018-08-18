#include "head.h"
#include "LOGIC_public.h"
#include "VIEW_login.h"


char tmp[64] = {0};		//����ʱ���������ȡʱ��,�ֲ���������ȫ

/*****************************************************************************************************************
* �������ƣ�int putString(char acStr[100], int iMaxlen, int iputType, int isPlainttext)
* ����������
*			 ʵ�� ������ �Ĺ���  
* ����˵����
*           char acStr[100] --����ַ������� int iMaxlen --�����ַ�����󳤶�  int iputType --�����ַ�������
*			int isPlainttext --���������� 1Ϊ����,0Ϊ����
* ����ֵ��0
******************************************************************************************************************/

int glb_putString(char acStr[100], int iMaxlen, int iputType, int isPlainttext)
{
		char ch;				//����ch������getch();
		int iLenth = 0;			//����һ���ַ���������������ĸ���
			
		while(1)
		{
				ch = getch();
				if(ch == '\r')		//�س� ɾ��
				{
						acStr[iLenth] = '\0';
						break;
				}
				if(ch == '\t')
				{
						acStr[iLenth] = '\0';
						break;
				}
				if(ch == '\b')		//ɾ���ַ�
				{
						if(iLenth > 0)
						{
							printf("\b \b");
							iLenth--;				//��ɾҪ������
							acStr[iLenth] = '\0';
						}
				}
				if(ch == 27)
				{
					return 27;
				}
				if(iLenth < iMaxlen)				//�жϳ����Ƿ�С����󳤶�
				{
						switch(iputType)             //���������1Ϊ����,2Ϊ��ĸ,3Ϊ��������ĸ
						{
						case 1:
							{
									if(ch >= '0' && ch <= '9')			//ֻ����������
									{
											if(isPlainttext)
											{
													putchar(ch);	//����
											}
											else
											{
													putchar('*');	//����
											}
											acStr[iLenth]= ch;		//������ַ��������acStr[ilenth]
											iLenth++;				//���м�������ĸ���
									}	
							}
							break;
						case 2:
							{
									if(ch >= 'a' && ch <= 'z')		//ֻ��������ĸ
									{
											if(isPlainttext)
											{
													putchar(ch);	//����
											}
											else
											{
													putchar('*');	//����
											}
											acStr[iLenth]= ch;		//������ַ��������acStr[ilenth]
											iLenth++;				//���м�������ĸ���
									}	
							}
							break;
						case 3:
							{
									if(ch >= '0' && ch <= '9' || ch >= 'a' && ch <= 'z')	//����������ĸ������
									{
											if(isPlainttext)
											{
													putchar(ch);	//����
											}
											else
											{
													putchar('*');	//����
											}
											acStr[iLenth] = ch;		//������ַ��������acStr[ilenth]	
											iLenth++;				//���м�������ĸ���
									}
							}
							break;
						default:
							{
									printf("�������\n");
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
* �������ƣ�int gotoxy(int x,int y)
* ����������
*			 ʵ�� ��� �Ĺ���  
* ����˵����
*           int x --x����   int y  --y����
* ����ֵ��0
******************************************************************************************************************/

int gotoxy(int x,int y)
{
		HANDLE handle;								//���þ��
		COORD coord;								//���ù��
		coord.X=x;									//����x����
		coord.Y=y;									//����y����
		handle=GetStdHandle(STD_OUTPUT_HANDLE);		//��ȡ��׼���
		SetConsoleCursorPosition(handle,coord);		//���ù�����
		return 0;
}


/*****************************************************************************************************************
* �������ƣ�int select_interface(int max,int x,int y)
* ����������
*			 ʵ�� ���,�˳�,���� �Ĺ���  
* ����˵����
*           int max  --�������ѡ���ѡ���м���		x ---���x����	y --���y����
* ����ֵ��count
******************************************************************************************************************/

int select_interface(int max,int x,int y)
{
		int count = 1;		//�����������ֵ
		int confirm = 0;	//����ȷ�ϵ���ֵ
		int i = 0;
		
		gotoxy(x,y);
		printf("\b��\b");

		while(1)
		{		
				
				switch(getch())
				{
				case KEY_UP:           //��
				case KEY_LEFT:		   //��
					{
							//������ָ��,ͨ���ı�����ֵ �����������ƫ��
							if(count == 1)
							{
								count = max;			//ֱ�������λ��Ϊcount��������ѡ��ĸ���		
							}
							else
							{
								count--;				//���count���еݼ�
							}
					}
					break;
				case KEY_DOWN:         //��
				case KEY_RIGHT:		 //��
					{
							//������ָ��,ͨ���ı�����ֵ �����������ƫ��
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
				case '\r':		//�س���

							confirm = 1;	

					break;
				case 'q':
				case 'Q':		//q��Q�˳���Ϸ
					{
						if(select_quit() == -1)
						{
							gotoxy(x,y);
						}
					}
					break;
				case KEY_ESC:			//����
					{
					
						if(select_return() == -3)			//���صĺ�������ֵΪ-3,�ͷ��س�ȥ
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
				
				switch(count)			//�����ת
				{
				case 1:
					{
							printf("\b��\b");		//���ĸ���
							gotoxy(x,y);
							printf("\b��\b");		//������ʾ
					}
					break;
				case 2:
					{
							printf("\b��\b");
							gotoxy(x,y+2);
							printf("\b��\b");
					}
					break;
				case 3:
					{
							printf("\b��\b");
							gotoxy(x,y+4);
							printf("\b��\b");
					}
					break;
				case 4:
					{
							printf("\b��\b");
							gotoxy(x,y+6);
							printf("\b��\b");
					}
					break;
				case 5:
					{
							printf("\b��\b");
							gotoxy(x,y+8);
							printf("\b��\b");
					}
					break;
				case 6:
							printf("\b��\b");
							gotoxy(x,y+10);
							printf("\b��\b");
					break;
				default :
					break;
				}	/* end of switch(count))	*/

				//���confirm��־λΪ1 ���س�ȥ
				if(confirm == 1)
				{
					break;
				}
		}	/*	end of while(1)	*/	

		return count;
}


/*****************************************************************************************************************
* �������ƣ�int putNum(char acStr[100],int iMaxlen,int iputType)
* ����������
*			 ʵ�� ��װ�����ַ� �Ĺ���  
* ����˵����
*           char acStr[100]  --�ַ��洢������	int iMaxlen --�����������     int iputType --���������
* ����ֵ��0
******************************************************************************************************************/

int putNum(char acStr[100],int iMaxlen,int iputType)
{
	char ch;
	int iLenth=0;
	while(1)
	{
			ch=getch();

			//�س� ɾ��
			if(ch=='\r')
			{
					acStr[iLenth]='\0';
					break;
			}
			if(ch=='\b')
			{
					if(iLenth>0)
					printf("\b \b");
					iLenth--;//��ɾҪ������
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
							if(ch>='0'&&ch<='9')			//�������
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
								if(ch>='A'&&ch<='Z')		//�����д��ĸ
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
								if(ch>='0'&&ch<='9'||ch>='a'&&ch<='z')		//���Сд��ĸ
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
								printf("   �������\n");
						}
						break;
					}
			}
	}	
	return 0;	
}



/*****************************************************************************************************************
* �������ƣ�void public_num(char *acBuf)
* ����������
*			 ʵ�� ����һ���ַ� �Ĺ���  
* ����˵����
*           char *acBuf  --�ַ��洢������	
* ����ֵ��0
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
						*acBuf = 0;			//ȷ����acbuf�����0
						break;
				}
				else if (ch >= '0' && ch <= '9')		//�������
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
				else if((unsigned char)ch>=0xa1 && (unsigned char)ch<=0xfe)		//��������ַ�
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
								if((unsigned char)ch>=0xa1 && (unsigned char)ch<=0xfe)		//���л�ɾ
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
								i--;		//�ַ�����
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
* �������ƣ�int select_retrunorquit(int max,int x,int y)
* ����������
*			 ʵ�� �����˳� �Ĺ���  
* ����˵����
*           	
* ����ֵ��0
******************************************************************************************************************/

int select_retrunorquit(int max,int x,int y)
{
		int count = 1;		//�����������ֵ
		int confirm = 0;	//����ȷ�ϵ���ֵ
		int i = 0;			//ѭ���ĳ�ʼֵ����i
		
		gotoxy(x,y);
		printf("\b��\b");
		while(1)
		{		
				
				switch(getch())
				{
				case KEY_UP:           //��
				case KEY_LEFT:		   //��
					{
							//������ָ��,ͨ���ı�����ֵ �����������ƫ��
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
				case KEY_DOWN:         //��
				case KEY_RIGHT:		 //��
					{
							//������ָ��,ͨ���ı�����ֵ �����������ƫ��
					
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
				case '\r':		//�س���

							confirm = 1;	

					break;
				case 'q':
				case 'Q':		//q��Q�˳���Ϸ
					{
						continue;
					}
					break;
				case KEY_ESC:			//����
					{
						continue;
					}
					break;
				default:
					break;
				}	/*	end of switch(getch())	*/
				
				switch(count)			//�����ת
				{
				case 1:
					{
							printf("\b��\b");			//���ĸ���
							gotoxy(x,y);
							printf("\b��\b");			//������ʾ
					}
					break;
				case 2:
					{
							printf("\b��\b");
							gotoxy(x,y+2);
							printf("\b��\b");
					}
					break;
				case 3:
					{
							printf("\b��\b");
							gotoxy(x,y+4);
							printf("\b��\b");
					}
					break;
				case 4:
					{
							printf("\b��\b");
							gotoxy(x,y+6);
							printf("\b��\b");
					}
					break;
				case 5:
					{
							printf("\b��\b");
							gotoxy(x,y+8);
							printf("\b��\b");
					}
					break;
				case 6:
							printf("\b��\b");
							gotoxy(x,y+10);
							printf("\b��\b");
					break;
				default :
					break;
				}	/*	end of switch(count)	*/

				//�����־λconfirmΪ1 ���س�ȥ
				if(confirm == 1)
				{
					break;
				}
		}	/*	end of while(1)	*/	
		return count;
}


/*****************************************************************************************************************
* �������ƣ�int select_quit()
* ����������
*			 ʵ�� �˳�ѡ�� �Ĺ���  
* ����˵����
*           	
* ����ֵ��0
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
					printf("                                           ");		//��ʾ����������
					gotoxy(30,26);
					printf("                                            ");			//��ʾ����������
					gotoxy(30,27);
					printf("		                                       ");
	
					gotoxy(30,27);
					printf("�˳�ϵͳ,");
					Sleep(200);
					printf("���Ե�>");

					//ʵ�ּ��ص�Ч��
					for (i=0;i<20;i++)
					{
							printf(">");
							Sleep(50);
					}
					Sleep(300);
					system("cls");
					gotoxy(15,15);
					printf("��ӭ�´μ���ʹ�ã�");
					exit(0);							
			}
			break;
		case 2:
			{
					gotoxy(30,25);
					printf("                                           ");		//��ʾ����������
					gotoxy(30,26);
					printf("                                            ");			
					gotoxy(30,27);
					printf("		                                       ");
					return -1;							
			}
			break;
		default:
			{
				printf("�������");
			}
			break;
		}
	}
		return 0;
}


/*****************************************************************************************************************
* �������ƣ�int select_return()
* ����������
*			 ʵ�� ����ѡ�� �Ĺ���  
* ����˵����
*           	
* ����ֵ��0
******************************************************************************************************************/

int select_return()
{
	while(1)
	{

		int i = 0;			//ѭ���ĳ�ʼ����i	

		ReturnView();		//���ؽ���

		switch(select_retrunorquit(2,47,25))			//�˳��ͷ��صĹ��ѡ�� 2����ѡ������   47,25��λλ��
		{
		case 1:
			{
					return -3;							
			}
			break;
		case 2:
			{
					gotoxy(30,25);
					printf("                                           ");		//��ʾ����������
					gotoxy(30,26);
					printf("                                            ");			//��ʾ����������
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
* �������ƣ�void Banktips()
* ����������
*			 ʵ�� С��ʿ �Ĺ���  
* ����˵����
*           	
* ����ֵ��
******************************************************************************************************************/

void Banktips()
{
	int i=0;
	srand(time(0));			//����һ������
	i=rand()%10;
	gotoxy(15,12);
	printf("																	");
	gotoxy(10,12);
	printf("	��ܰ��ʾ:");
	switch(i)
	{
	case 0:
		printf("���ѽ���24Сʱ�������");
		break;
	case 1:
		printf("����������ʱ,��ע�����밲ȫ");
		break;
	case 2:
		printf("����������,����ϵ����Ա");
		break;
	case 3:
		printf("�������թƭ,����������ѯ����Ա");
		break;
	case 4:
		printf("�뿪����ʱ��ע��ȡ�����п�");
		break;
	case 5:
		printf("�����ֽ����뵽���й�̨����");
		break;
	case 6:
		printf("��������,����ѯ����Ա");
		break;
	case 7:
		printf("����ٳ�,��������");
		break;
	case 8:
		printf("ת��İ���˺�ʱ,��ȷ��");
		break;
	case 9:
		printf("������֧�ֿ���ת��");
		break;
	default :
		break;
	}
}


/*****************************************************************************************************************
* �������ƣ�void CurTime(int x,int y,int a)
* ����������
*			 ʵ�� ��ȡϵͳʱ�� �Ĺ���  
* ����˵����
*           	
* ����ֵ��tmp
******************************************************************************************************************/

char *CurTime(int x,int y,int a)		//��CPU��ȡϵͳ��ǰʱ��
{
	time_t t = time(0);		//��ȡϵͳʱ��	
	gotoxy(x,y);

	switch(a)		//ѡ����ʾ��ʱ������
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
		printf("��ʽ����");
		break;
	}
	return tmp;
}





 