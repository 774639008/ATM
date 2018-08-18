#include "head.h"
#include "VIEW_user.h"
#include "CACHE_file.h"
#include "CACHE_list.h"
#include "CACHE_data.h"
#include "LOGIC_user.h"
#include "LOGIC_public.h"

extern FILE *people_fp;			//�����û��ļ���ȫ�ֱ��������ļ������ض��õ��ļ�ָ��
extern pNode *people_head;		//�����û������ȫ�ֱ���������������ض��õ�ͷ���

extern FILE *trade_fp;			//�����˵��ļ���ȫ�ֱ��������ļ������ض��õ��ļ�ָ��
extern pNode *trade_head;		//�����˵������ȫ�ֱ���,����������ض��õ�ͷ���

extern Person g_currentUser;	//������ǰ���������û��������д��ʱ�ض���Ҫƥ��

extern int glb_trade_id;		////ȫ�ֱ����˵�ID


/*****************************************************************************************************************
* �������ƣ�int User()
* ����������
*			 ʵ�� �û����� �Ĺ���  
* ����˵����
*           
* ����ֵ��0
******************************************************************************************************************/

int User()
{
	
	while(1)
	{
		UserView();

		gotoxy(20,10);
		printf(" 	       ��ǰ�û�:%s        ",g_currentUser.szUsername);		//�Ե�ǰ�û�������ʾ

		switch(select_interface(6,36,13))
		{
		case 1:
			{
				UserQuery_View();		//�û���ѯ������
				UserQuery();			//�û���ѯ���
			}
			break;
		case 2:
			{
				UserDeposit();			//�û����
			}
			break;
		case 3:
			{
				UserDraw();				//�û�ȡ��
			}
			break;
		case 4:
			{
				UserTransfer();			//�û�ת��
			}
			break;
		case 5:
			{
				UserUpdpsw_View();		//�û��޸��������
				UserUpdpsw();			//�û��޸�����
			}
			break;
		case 6:
			{
				UserQuerylist_View();	//�û���ѯ�˵�����
				UserQuerylist();		//�û���ѯ�˵�
			}
			break;
		case -3:
			{
				system("cls");
				return main();			//���ص�½����
			}
		default:
			break;
		}
	}
	return 0;
}


/*****************************************************************************************************************
* �������ƣ�void UserQuery()
* ����������
*			 ʵ�� �û�����ѯ �Ĺ���  
* ����˵����
*           
* ����ֵ��0
******************************************************************************************************************/

void UserQuery()
{
		printf("\t\t\t������:%s\n\n",g_currentUser.szUsername);
		printf("\t\t\t�˺�Ϊ:%d\n\n",g_currentUser.AccountNumber);	
		printf("\t\t\t�˺����Ϊ:%.2f",g_currentUser.fMoney);
		printf("\n\n�������������һ��");
		getch();
}


/*****************************************************************************************************************
* �������ƣ�void UserDeposit()
* ����������
*			 ʵ�� �û���� �Ĺ���  
* ����˵����
*           
* ����ֵ��0
******************************************************************************************************************/

int UserDeposit()
{
 		int num = 0;				//�������num����������˻�
		int i = 0;					//�������i��Ϊѭ���ĳ�ʼֵ
		int count = 0;				//�������count���ӻ�ȡ�Ľ�����	
		int flag = 0;				//�������flag��Ϊ���  ���㷵��
		int money = 0;				//��������Ǯmoney
		char acmoney[2] = {0};		//��������Ǯacmoney
		char  ch = 0;				//����ch����Ϊgetch�Ĵ洢����
		Person *people;				//����һ���ṹ���û�people
		Trade *trade;				//���и��º�׷���û�����˵�

		
		while (1)
		{			
				//��ȡ�û��ĸ���
				count = LIST_GetCount(people_head);

				//����ѭ�������ҵ���Ӧ�˺ŵĽ��
				for(i = 1; i <= count; i++)
				{
						people = LIST_GetNode(i,people_head);
						trade = LIST_GetNode(i,trade_head);
	
						if(people->ID == g_currentUser.ID) 
						{			
								system("cls");
								UserDeposit_View();		//�û�������
								printf("\t  ������ԭ�����%fԪ\n",g_currentUser.fMoney);     
								printf("\t  ************************************\n");  
								printf("\t  **  1: 100Ԫ    *****    2:200Ԫ  **\n");  
								printf("\t  ************************************\n");  
								printf("\t  **  3: 300Ԫ    *****    4:400Ԫ  **\n");  
								printf("\t  ************************************\n");  
								printf("\t  **  5: 500Ԫ    *****    6:600Ԫ **\n");  
								printf("\t  ************************************\n");  
								printf("\t  ��ѡ����Ҫ��������:\n");  
								printf("\t  ");

								if(27==putNum(acmoney,1,1))
								{
									return 0;
								}

								//�ж�������ַ��Ƿ���Ͻ�����ʾ������
								money = atoi(acmoney);
								if(money>6||money<=0)
								{
									printf("����Ľ������,���������룡");
									Sleep(500);
									continue;
								}

								money=100*money;  //��Ӧѡ�����һ��Ϊȡ����  
								g_currentUser.fMoney+=money;  //�Խ����д��� 

								//ͬ���ļ�������
								FILE_update(people_fp,&g_currentUser,sizeof(Person),i);
								
								//���³�ʼ�˵�
								trade->way = 1; 
								trade->from = people->AccountNumber;
								trade->num = people->AccountNumber;
								trade->sum = money;
								trade->balance = (int)g_currentUser.fMoney;
								trade->date,strcpy(trade->date,CurTime(10,25,3));
								FILE_update(trade_fp,trade,sizeof(Trade),i);//�����ļ�
								
								//׷��һ���µ��˵�
								glb_trade_id++;
								trade->way = 1; 
								trade->from = people->AccountNumber;
								trade->num = people->AccountNumber;
								trade->sum = money;
								trade->rank = glb_trade_id;
								trade->balance = (int)g_currentUser.fMoney;
								strcpy(trade->date,CurTime(10,25,3));
								FILE_add(trade_fp,trade,sizeof(Trade));		
								
								//��������
								gotoxy(25,25);
								printf("\n\t  ���ڴ��������Ժ��������\n\t\t");

								for(i=0;i<10;i++)  
								{  
										printf("��");  
										Sleep(100);  
								}
								
								printf("\n\t  ���Ѿ��ɹ�����%dԪ\n",money); 
								Sleep(500);
								printf("\t  ���ɹ�,����1.�ٴδ��� 2.������һ��\n");
								printf("\t\t");
								ch =getch();

								if(ch == '1')
								{
										num = 0;
								}
								else
								{
										flag = 1;  //��������ѭ�����б��  
								}

								break;
						}	/* end of if(people->ID == g_currentUser.ID)  */
				}	/* end of for(i = 1; i <= count; i++) */
				
				//���û����뷵�أ�ʹflagֵ��ֵΪ1�����س�ȥ
				if (flag == 1)
				{
						break;
				}

		}	/* end of while(1) */
		return 0;
}



/*****************************************************************************************************************
* �������ƣ�int UserDraw()
* ����������
*			 ʵ�� �û�ȡ�� �Ĺ���  
* ����˵����
*           
* ����ֵ��0
******************************************************************************************************************/

int UserDraw()
{
		int num = 0;				//�������num����������˻�
		int i = 0;					//�������i��Ϊѭ���ĳ�ʼֵ
		int count = 0;				//�������count���ӻ�ȡ�Ľ�����
		int flag = 0;				//�������flag��Ϊ���  ���㷵��	
		int money = 0;				//����ȡ����Ǯmoney	
		char acmoney[2] = {0};		//��������Ǯacmoney
		char  ch = 0;				//����ch����Ϊgetch�Ĵ洢����
		Person *people;				//����һ���ṹ���û�people
		Trade *trade;				//���и��º�׷���û�����˵�

		while (1)
		{		
				//����
				count = LIST_GetCount(people_head);
				
				//����ѭ�������ҵ���Ӧ�˺ŵĽ��
				for(i = 1; i <= count; i++)
				{
					people = LIST_GetNode(i,people_head);
					trade = LIST_GetNode(i,trade_head);

					if(people->ID == g_currentUser.ID) 
					{			
							system("cls"); 
							UserDraw_View();		//�û�ȡ�����
							printf("\t  ������ԭ�����%fԪ\n",g_currentUser.fMoney);     
							printf("\t  ************************************\n");  
							printf("\t  **  1: 100Ԫ    *****    2:200Ԫ  **\n");  
							printf("\t  ************************************\n");  
							printf("\t  **  3: 300Ԫ    *****    4:400Ԫ  **\n");  
							printf("\t  ************************************\n");  
							printf("\t  **  5: 500Ԫ    *****    6:600Ԫ **\n");  
							printf("\t  ************************************\n");  
							printf("\t  ��ѡ����Ҫȡ�������\n");  
							printf("\t  ");
							if(27==putNum(acmoney,1,1))
							{
								return 0;
							}

							//�ж�������ַ��Ƿ���Ͻ�����ʾ������
							money = atoi(acmoney);
			
							if(money>6||money<=0)
							{
								printf("����Ľ������,���������룡");
								Sleep(500);
								continue;
							}

							money=100*money;  //��Ӧѡ�����һ��Ϊȡ����

							//�ж�����Ľ���Ƿ�������
							if(money > g_currentUser.fMoney)
							{
									printf("���㣡");
									Sleep(500);
									break;
							}

							g_currentUser.fMoney-=money;  //�Խ����д���
							
							//ͬ���û�������
							FILE_update(people_fp,&g_currentUser,sizeof(Person),i);
									
							//���³�ʼ�˵�
							trade->way = 2; 
							trade->from = people->AccountNumber;
							trade->num = people->AccountNumber;
							trade->sum = money;
							trade->balance = (int)g_currentUser.fMoney;
							strcpy(trade->date,CurTime(10,25,3));
							FILE_update(trade_fp,trade,sizeof(Trade),i);//�����ļ�
							
							//׷��һ���µ��˵�
							glb_trade_id++;
							trade->way = 2; 
							trade->from = people->AccountNumber;
							trade->num = people->AccountNumber;
							trade->sum = money;
							trade->rank = glb_trade_id;
							trade->balance = (int)g_currentUser.fMoney;
							strcpy(trade->date,CurTime(10,25,3));
							FILE_add(trade_fp,trade,sizeof(Trade));	
						
							//��������
							gotoxy(25,25);
							printf("\n\t  ����ȡ�������Ժ��������\n\t\t");
							for(i=0;i<10;i++)  
							{  
									printf("��");  
									Sleep(100);  
							}
							
							printf("\n\t  ���Ѿ��ɹ�ȡ��%dԪ\n",money); 
							Sleep(500);
							printf("\t  ȡ��ɹ�,����1.�ٴ�ȡ�� 2.������һ��\n");
							printf("\t\t");
							ch =getch();

							if(ch == '1')
							{
									num = 0;
							}
							else
							{
									flag = 1;  //��������ѭ�����б��  
							}

							break;
					}	/* end of if(people->ID == g_currentUser.ID) */
				}	/* end of for(i = 1; i <= count; i++) */
				
				//���û����뷵�أ�ʹflagֵ��ֵΪ1�����س�ȥ
				if (flag == 1)
				{
					break;
				}

		}	/* end of while(1) */
		return 0;
}


/*****************************************************************************************************************
* �������ƣ�void UserTransfer()
* ����������
*			 ʵ�� �û�ת�� �Ĺ���  
* ����˵����
*           
* ����ֵ��0
******************************************************************************************************************/

int UserTransfer()
{
		int flag = 0;				//�������flag��Ϊ���  ���㷵��
		char fnum[10] = {0};		//��һ��������˺�
		char snum[10] = {0};		//�ٴ�ȷ�ϵ��˺�
		int money = 0;				//����Ľ��
		int i = 0;					//�������i��Ϊѭ���ĳ�ʼֵ
		int count = 0;				//�������count���ӻ�ȡ�Ľ�����
		int rnum = 0;				//rnum���ص�ֵ
		char acmoney[2] = {0};		//��������Ǯacmoney
		char  ch = 0;				//����ch����Ϊgetch�Ĵ洢����
		Trade *trade;				//���и��º�׷���û�����˵�
		Person *people;				//����һ���ṹ���û�people
		Person *tpeople;			//����һ���ṹ���û�people
		
		while (1)
		{		
				UserTransfer_View();	//�û�ת�˽�����ʾ
				
				gotoxy(7,10);
				printf("������ת�˶Է�������:");  
				rnum = glb_putString(fnum,8,3,1);
				
				if(rnum == 27)
				{
					return 0;
				}
				
				gotoxy(7,11);
				printf("���ٴ�����ת�˶Է�������:");  
				rnum = glb_putString(snum,8,3,1);
				
				if(rnum == 27)
				{
					return 0;
				}
				
				//�ж��Ƿ�Ϊԭ�˻�
				if(0 == strcmp(g_currentUser.szUsername,fnum))
				{
						printf("\n����ת��ԭ�˻�\n");
						Sleep(500);
						continue;
				}
				
				//�жϵ�һ��������˺ź͵ڶ���������˺��Ƿ�ƥ��
				if(0 != strcmp(fnum,snum))  
				{  
						printf("\n�����û�����ͬ������������\n"); 
						Sleep(500);
						continue; 
				}

				//����
				count = LIST_GetCount(people_head);
				
				//����ѭ�������ҵ���Ӧ�˺ŵĽ��
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
										printf("\t  ������ԭ�����%fԪ\n",g_currentUser.fMoney);     
										printf("\t  ************************************\n");  
										printf("\t  **  1: 100Ԫ    *****    2:200Ԫ  **\n");  
										printf("\t  ************************************\n");  
										printf("\t  **  3: 300Ԫ    *****    4:400Ԫ  **\n");  
										printf("\t  ************************************\n");  
										printf("\t  **  5: 500Ԫ    *****    6:600Ԫ **\n");  
										printf("\t  ************************************\n");   	
										printf("\t  ������ת�˽��\n");
										printf("\t  ");
										if(27==putNum(acmoney,1,1))
										{
											return 0;
										}
										//�ж�������ַ��Ƿ���Ͻ�����ʾ������
										money = atoi(acmoney);
										if(money>6 || money<=0)  
										{  
											printf("�Բ���������������\n"); 
											Sleep(500);
											continue;  
										}  
										money=100*money;  //��Ӧѡ�����һ��Ϊȡ����
										if(money > g_currentUser.fMoney)
										{
												printf("���㣡\n");
												Sleep(500);
												continue;
										}

										//ת���˵����
										g_currentUser.fMoney-=money;  //�Խ����д��� 

										//ͬ���ļ������ݣ���i��Ϊ��ʱƥ�䵽���û�
										FILE_update(people_fp,&g_currentUser,sizeof(Person),i);	
										
						
										//���³�ʼ�˵�
										trade->way = 3; 
										trade->from = people->AccountNumber;
										trade->num = g_currentUser.AccountNumber;
										trade->sum = money;
										trade->balance = (int)g_currentUser.fMoney;
										strcpy(trade->date,CurTime(10,25,3));
										FILE_update(trade_fp,trade,sizeof(Trade),g_currentUser.ID);//�����ļ�				
										
										//׷��һ���µ��˵�
										glb_trade_id++;
										trade->way = 3; 
										trade->from = people->AccountNumber;
										trade->num = g_currentUser.AccountNumber;
										trade->sum = money;
										trade->rank = glb_trade_id;
										trade->balance = (int)g_currentUser.fMoney;
										strcpy(trade->date,CurTime(10,25,3));
										FILE_add(trade_fp,trade,sizeof(Trade));	
										
										//��ת���˵����
										people->fMoney+=money;

										//ͬ���ļ������ݣ���i��Ϊ��ʱƥ�䵽���û�
										FILE_update(people_fp,people,sizeof(Person),i);

										//���³�ʼ�˵�
										trade->way = 4; 
										trade->from = g_currentUser.AccountNumber;
										trade->num = tpeople->AccountNumber;
										trade->sum = money;
										trade->rank = people->ID;
										trade->balance = (int)people->fMoney;
										strcpy(trade->date,CurTime(10,25,3));
										FILE_update(trade_fp,trade,sizeof(Trade),i);//�����ļ�
										
										//׷��һ���µ��˵�
										glb_trade_id++;
										trade->way = 4; 
										trade->from = g_currentUser.AccountNumber;
										trade->num = tpeople->AccountNumber;
										trade->sum = money;
										trade->rank = glb_trade_id;
										trade->balance = (int)people->fMoney;
										strcpy(trade->date,CurTime(10,25,3));
										FILE_add(trade_fp,trade,sizeof(Trade));	

										//��������
										gotoxy(25,25);
										printf("\n\t  ����ת�������Ժ��������\n\t\t");
										for(i=0;i<10;i++)  
										{  
												printf("��");  
												Sleep(100);  
										}
					
										printf("\n\t  ���Ѿ��ɹ�ת��%dԪ\n",money); 
										Sleep(500);
										printf("\t  ת��ɹ�,����1.�ٴ�ת�� 2.������һ��\n");
										printf("\t\t");
										ch =getch();
										if(ch == '1')
										{
												fnum[10] = 0;		//�û�������
												snum[10] = 0;		//�û�������
												continue;
										}
										else
										{
												flag = 1;  //��������ѭ�����б��  
										}
										break;
									}	/* end of while(1) */
								}	/* end of if (people->AccountNumber == snum) */		
						}	/* end of if(people->ID == g_currentUser.ID) */
				}	/* end of for(i = 1; i <= count; i++) */
				
				//���û����뷵�أ�ʹflagֵ��ֵΪ1�����س�ȥ
				if (flag == 1)
				{
					break;
				}
				if(i>count)
				{
					printf("�˺Ų����ڣ�");
					Sleep(500);
					continue;
				}
			

		}	/* end of while(1) */
		return 0;
}




/*****************************************************************************************************************
* �������ƣ�int UserUpdpsw()
* ����������
*			 ʵ�� �û������޸� �Ĺ���  
* ����˵����
*           
* ����ֵ��0
******************************************************************************************************************/

int UserUpdpsw()
{
		while(1)
		{
				int i = 0;				//i������Ϊѭ���ĳ�ʼ����
				int count = 0;			//count�����ջ�ȡ�Ľ����
				int num = 0;			//num�������˺ŵ�����
				char psw[10] = {0};		//psw�洢�޸����������
				char opsw[10] = {0};	//psw�洢�޸����������
				char npsw[10] = {0};	//psw�洢�޸����������
				char ch = 0;			//ch��������getch()

				UserUpdpsw_View();		//����Ա�����޸Ľ���
				gotoxy(20,13);	
				printf("������ɵ�����(6λ)��");
				if(27 == glb_putString(opsw,6,1,0))
				{
						return 0;
				}

				//ͨ������һ�����ҳ��û�����Ϣ
				if(0 != strcmp(g_currentUser.szPassword,opsw))
				{
						printf("������������\n");
						Sleep(300);
						system("cls");
						continue;
				}

				
				gotoxy(20,14);
				printf("�������µ�����(6λ):");
				if(27 == glb_putString(psw,6,1,0))
				{
					return 0;
				}
				if(strlen(psw)<6)
				{
						printf("\n\t\t�˺����벻��С��6λ����");
						system("pause");
						continue;
				}

				gotoxy(20,15);
				printf("���ٴ������µ�����(6λ):");
				if(27 == glb_putString(npsw,6,1,0))
				{
					return 0;
				}
				
				if(strcmp(npsw,psw) == 0)
				{
						strcpy(g_currentUser.szPassword,psw);		//���ڴ����
						//ͬ���ļ�������
						FILE_update(people_fp,&g_currentUser,sizeof(Person),g_currentUser.ID);
						
						//�����ݸ������,��ʾ�ɹ�
						printf("\n\t\t�޸�����ɹ�,����1.�ٴ��޸� 2.������һ��\n");
						ch =getch();
						if(ch == '1')
						{
								num = 0;
								continue;
						}
						else
						{
								return -3;  //��������ѭ�����б��  
						}
						break;
				}
				else
				{
						printf("\n\t\t������������벻һ�£�����1.�ٴ��޸� 2.������һ��\n");
						ch =getch();
						if(ch == '1')
						{
								num = 0;
								continue;
						}
						else
						{
								return -3;  //��������ѭ�����б��  
						}
						break;
				}		
		}

		return 0;
}

int UserQuerylist()
{
		int i = 0;			//����ѭ���ĳ�ʼ����i
		int count = 0;		//count�����ջ�ȡ�Ľ����
		Trade *trade;		//����һ��Ա���ṹ��people
		char ch[10] = {0};	//��������ch������������
		int num = 0;		//num���к�
		char ch1 = 0;		//����ch1��ȡ�ַ�
		int page=0;			//page��ǰҳ
		int flag = 0;		//flag��־λ

		
		trade_fp = FILE_open("data/trade/trade.txt");
		trade_head=FILE_read(trade_fp,sizeof(Trade));
		if(	trade_head->next == NULL)
		{
			trade_head = TRADE_Data(trade_fp);		
		}
		//��������
		while(!flag)
		{
			
			UserQuerylist_View();
			gotoxy(25,20);
			printf("�����Ϸ�ҳ �����·�ҳ ESC�˳�");
			gotoxy(0,7);
			printf("\t���	״̬		���׶�		���		�˵��Ź���	�˵�����ʱ��			���׷�������\n");
		
			count = LIST_GetCount(trade_head);
		
			
			//ͨ������һ�����ҳ��û�����Ϣ
			for (i = 1+page*10; i <= (page+1)*10; i++)		//ÿ�η�10ҳ �ù���pageҳ������ѧ��ʽ����Ϊѭ���������ͳ�ʼ����
			{
				trade = LIST_GetNode(i,trade_head);
				if(trade == NULL)
				{
					break;
				}

				//���к�
				num++;

				//�ж��Ƿ�Ϊ��Ч���û�
				switch(trade->way)
				{
				case 0:
					{
						printf("\t%-6d	ԭʼ 		%-10d	%-10d",num,trade->sum,trade->balance);
						printf("	%d",trade->num);
						printf("	%s",trade->date);
						printf("	ATM\n");
					}
					break;
				case 1:
					{
						printf("\t%-6d	��� 		+%-10d	%-10d",num,trade->sum,trade->balance);
						printf("	%d",trade->num);
						printf("	%s",trade->date);
						printf("	ATM\n");
					}
					break;
				case 2:
					{
						printf("\t%-6d	ȡ�� 		-%-10d	%-10d",num,trade->sum,trade->balance);
						printf("	%d",trade->num);
						printf("	%s",trade->date);
						printf("	ATM\n");
					}
					break;
				case 3:
					{
						printf("\t%-6d	ת�� 		-%-10d	%-10d",num,trade->sum,trade->balance);
						printf("	%d",trade->num);	
						printf("	%s",trade->date);
						printf("	%d\n",trade->from);
					}
					break;
				case 4:
					{
						printf("\t%-6d	ת�� 		+%-10d	%-10d",num,trade->sum,trade->balance);
						printf("	%d",trade->num);	
						printf("	%s",trade->date);
						printf("	%d\n",trade->from);
					}
					break;
				default:
					break;
				}
		

			}

			//ѭ��һ��ҳ������
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
					if (page < 2)				//ҳ�������ж�
					{
						continue;
					}
					num = (page - 2) * 10;		
					page = page - 2;
					break;
				}
				if (ch1 == 's' || ch1 == 80 || ch1 == 'S')
				{
					if (page * 10 >= count)		//�����������ж�
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

