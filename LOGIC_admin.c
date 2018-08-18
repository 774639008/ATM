#include "head.h"
#include "LOGIC_public.h"
#include "LOGIC_admin.h"
#include "VIEW_admin.h"
#include "CACHE_file.h"
#include "CACHE_list.h"

extern FILE *people_fp;  //�����ļ���ȫ�ֱ��������ļ������ض��õ��ļ�ָ��
extern pNode *people_head;//���������ȫ�ֱ���������������ض��õ�ͷ���

extern int glb_people_id;	//����һ���û�id
extern int glb_trade_id;

extern pNode *trade_head;	//����һ��������
extern FILE *trade_fp;		//����һ���˵��ṹ��

extern Person g_currentUser;	//������ǰ���������û��������д��ʱ�ض���Ҫƥ��

/*****************************************************************************************************************
* �������ƣ�int Admin()
* ����������
*			 ʵ�� ����Ա�����û� �Ĺ���  
* ����˵����
*           
* ����ֵ��0
******************************************************************************************************************/

int Admin()
{
		while(1)
		{
			AdminView();					//����Ա����
			gotoxy(20,10);
			printf(" 	       ��ǰ����Ա:%s        ",g_currentUser.szUsername);		//�Ե�ǰ�û�������ʾ

			switch(select_interface(5,36,13))		//���ƹ���ƶ����ݷ��ص�ֵ�����жϽ����Ϊ4��ѡ���ҳ��
			{
			case 1:						//����Ա���ģ��
				{
						AdminAdd_View();		//����Ա�����ʾ����
						AdminAdd();				//����Ա��ӹ���
				}
				break;
			case 2:
				{		while(1)
						{
								AdminQuery_View();		//����Ա��ѯ��ʾ����
								switch(select_interface(4,36,13))		//���ƹ���ƶ����ݷ��ص�ֵ�����жϽ����Ϊ3��ѡ���ҳ��	
								{
								case 1:				//����Աȫ����ѯģ��
									{	
											system("cls");
											AdminAllquery_View();
											query();			
									}
									break;
								case 2:				//����Ա�����ѯģ��
									{
											AdminClassifyQuery_View();				
											switch(select_interface(2,36,13))
											{
											case 1:
												{
														AdminAquery();			//����Ա��ѯ
												}
												break;
											case 2:
												{
														AdminUquery();			//�û���ѯ
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
								case 3:				//����Ա������ѯģ��
									{		
											AdminConditionquery_View();
											switch(select_interface(2,36,13))
											{
											case 1:
												{
														AdminVaguesearch();			//����Աģ����ѯ����
												}
												break;
											case 2:
												{
														AdminExactsearch();			//����Ա��ȷ��ѯ����	
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
								case -3:	//����ģ��
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
			case 3:				//����Աɾ��ģ��
				{
						AdminDel_View();		//����Աɾ����ʾ����
						AdminDel();				//����Աɾ������
				}
				break;
			case 4:				//����Ա�޸�����ģ��
				{
						AdminUpdpsw();			//����Ա�����޸Ĺ���
				}
				break;
			case 5:
				{
						AdminRecover();
				}
				break;
			case -3:			//����ģ��
				{
						system("cls");
						return main();			//���ص�¼����
				}
			default:
				break;
			}
		}
		return 0;
}


/*****************************************************************************************************************
* �������ƣ�int AdminAdd()
* ����������
*			 ʵ�� ��������û� �Ĺ���  
* ����˵����
*           
* ����ֵ��0
******************************************************************************************************************/

int AdminAdd()
{
		char ch = 0,ch1=0,ch2 = 0;			//����ch,ch1,ch2 ���������������
		char role;							//����role���������,���Ҹ�ֵ����ӵ��û�
		char acName[20] = {0};				//acName[20]����ʱ�����û���
		char acPsw[20] = {0};				//acPsw[20]	����ʱ��������
		char acPsw1[20] = {0};				//acPsw1[20] ����ʱ�����ٴ���������
		int count = 0;						//count��������Ľ����
		int count1 = 0;
		int i = 0;							//i����һ��ѭ���ĳ�ʼֵ
		int num = 0;						//num��ʱ���������˺ŵ�ֵ
		int num1 = 0;
		Person *ps;							//����һ��Ա���ṹ��
		Person *ps1;						//����һ����ʱ���յ�Ա���ṹ��
		Trade *ts;
		Person *people;
		while(1)
		{
				AdminAdd_View();
				
				gotoxy(24,13);			//(24,13)���λ�ã�Ϊ�����������
				printf("���������û���(Сд��ĸ,�������):");		
				if(27 == glb_putString(acName,8,3,1))
				{
					return 0;
				}

				count = LIST_GetCount(people_head);
				//���б��������û��������Ƿ�������������Ƿ����
				for(i = 1; i <= count; i++)
				{
						people = (Person *)LIST_GetNode(i,people_head);
						
						if(0 == strcmp(people->szUsername,acName) )
						{
								printf("�û��Ѿ����ڣ�");
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
				
				//������ַ�����Ϊ��
				if(0 == strlen(acName))
				{
					printf("���벻��Ϊ�գ�");
					Sleep(500);
					printf("                 ");
					gotoxy(45,13);
					printf("                     ");
					continue;
				}
				if(strlen(acName)<4)
				{
					printf("�˺�����Ϊ4λ��");
					Sleep(500);
					printf("                 ");
					gotoxy(45,13);
					printf("                     ");
					continue;
				}
				else if(acName[0]<'a' || acName[0]>'z')			//�ж����ַ��Ƿ�Ϊ����
				{
					printf("\n\t\t���ַ�����Ϊ���֣�Ӧ��Ϊ��ĸ��");
					system("pause");
					continue;
				}

				printf("\n\t\t\t����������(6λ):");
				if(27 == glb_putString(acPsw,6,1,0))
				{
					return 0;
				}

				if(strlen(acPsw)<6)
				{
					printf("������Ҫ6λ");
					Sleep(500);
					printf("                                         ");
					gotoxy(45,13);
					printf("                                       ");
					gotoxy(40,14);
					printf("                                       ");
					continue;	
				}

				printf("\n\t\t\t���ٴ���������(6λ):");
				if(27 == glb_putString(acPsw1,6,1,0))
				{
					return 0;
				}
			
				
				//����������ڶ��������������֤,�ж������Ƿ�Ϊ��
				if(strcmp(acPsw,acPsw1) == 0 && acPsw[0] != 0)
				{
						ps = (Person *)malloc(sizeof(Person));
						memset(ps,0,sizeof(Person));
						strcpy(ps->szUsername,acName);
						strcpy(ps->szPassword,acPsw);
						ps->fMoney = 0;
						ps->iVilid = 1;
						

						printf("\n\t\t\t��ѡ�����(0-����Ա 1-��ͨ�û� )��");
						if(27 == public_num(&role))
						{
							return 0;
						}

						//���ݸ�ֵ�Ľ�ɫ,���б���ӹ���Ա��ɫ�����û���ɫ
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
								printf("\n\t\t\t�������, ��1�������,���������������һ��\n");
								printf("\t\t\t������:");
								ch2 = getch();

								//���������ָ���жϼ������,����ѭ��,�˳��Ļ��˳�ѭ��
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
						
						//�����ӷ��Ϲ���Ա���û������,����ӳɹ�
						if (role == '0' || role == '1')
						{
								glb_people_id++;
								ps->ID = glb_people_id;			//ID��ֵ
								count = LIST_GetCount(people_head);
								ps1 = LIST_GetNode(count,people_head);
								num = ps1->AccountNumber;
								num++;
								ps->AccountNumber= num;			//�˺Ÿ�ֵ

							
								
								ts = (Trade *)malloc(sizeof(Trade));
								memset(ts,0,sizeof(Trade));	
					
										//ID��ֵ
								count1 = LIST_GetCount(trade_head);
								ts = LIST_GetNode(count1,trade_head);
								glb_trade_id++;
								ts->rank = glb_trade_id;
								num1 = ts->num;
								num1++;
								ts->num = num1;			//�˺Ÿ�ֵ
								ts->balance = 0;
								ts->sum = 0;
								ts->from = 0;
								ts->way = 0;


								//ͬ���ļ�����		
								LIST_Add(ps,people_head);  //ֻ����ӵ�����
								LIST_Add(ts,trade_head); 

								FILE_add(people_fp,ps,sizeof(Person));	//׷�ӵ��ļ��������ݺ���
								FILE_add(trade_fp,ts,sizeof(Trade));
								
								printf("\n\t\t\t���������,");
								Sleep(200);
								printf("���Ե�>");
								
								//ʵ�ּ��ص���ʾ
								for (i=0;i<20;i++)
								{
										printf(">");
										Sleep(50);
								}

								Sleep(300);
								printf("\n\n\t\t\t����û��ɹ�\n");
								printf("\n\t\t\t�������û���Ϣ:");
								printf("\n\t\t\t�˺�:%d\n",ps->AccountNumber);
								printf("\t\t\t�û���:%s\n",ps->szUsername);
								printf("\t\t\t���:%d\n",ps->fMoney);
								printf("\t\t\tID:%d\n",ps->ID);

								switch(ps->iRole)
								{
									case 0:printf("\t\t\t���:����Ա\n");break;
									case 1:printf("\t\t\t���:�û�\n");break;
								}

//����û��ɹ�����ʾ��Ӧ���û���Ϣ��ʾ,DEBUG���е���ʹ��								
#ifdef DEBUG	
								
								printf("\n\t\t\t�˺�:%d\n",ts->num);
								printf("\t\t\t���:%d\n",ts->sum);
								printf("\t\t\t���:%d\n",ts->balance);
								printf("\t\t\tID:%d\n",ts->rank);
#endif DEBUG

								printf("\n\n�������������\n");
								ch1 = getch();
								return 0;
						}	
			}

			//��������ٴ�����Ĳ�һ��
			else
			{
					  printf("\n\t\t\t�����������벻һ��,��1�������,���������������һ��\n");
					  printf("\t\t\t������:");
					  public_num(&ch);

					  //����1���֮ǰ���������
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

							    //�������
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
* �������ƣ�int AdminAllquery()
* ����������
*			 ʵ�� �����ѯ�û� �Ĺ���  
* ����˵����
*           
* ����ֵ��0
******************************************************************************************************************/

int AdminAllquery()
{
		int i = 0;			//����ѭ���ĳ�ʼ����i
		int count = 0;		//count�����ջ�ȡ�Ľ����
		int num = 0;		//num����ʾ���к�
		Person *people;		//����һ��Ա���ṹ��people
		char ch[10] = {0};	//��������ch������������
		
		printf("\t���      ����        	���		�˺�		���	\n");
		//��������
		count = LIST_GetCount(people_head);

		//ͨ������һ�����ҳ��û�����Ϣ
		for (i = 1; i <= count; i++)
		{
				people = LIST_GetNode(i,people_head);
				
				//�ж��Ƿ�Ϊ��Ч���û�
				if (people->iVilid == 1)
				{	
						num++;
					//�������ǵ�����Ƿ�ƥ����д�ӡ����
						switch (people->iRole)
						{
						case 0:					//0Ϊ����Ա���
							{
									printf("\t%-6d     %-10s 	����Ա",num,people->szUsername,people->iRole);
									printf("		%8d",people->AccountNumber);
									printf("	%.2f\n",people->fMoney);
							}
							break;
						case 1:					//1Ϊ�û����
							{
									printf("\t%-6d     %-10s   ��ͨ�û�",num,people->szUsername,people->iRole);
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
* �������ƣ�void query()
* ����������
*			 ʵ�� �����ѯ�û� �Ĺ���  
* ����˵����
*           
* ����ֵ��0
******************************************************************************************************************/

void query()
{
		AdminAllquery_View();
		AdminAllquery();

		printf("\n\n\n\t\t\t�������������\n");
		getch();
}

/*****************************************************************************************************************
* �������ƣ�int AdminAquery()
* ����������
*			 ʵ�� ��������ѯ����Ա �Ĺ���  
* ����˵����
*           
* ����ֵ��0
******************************************************************************************************************/

int AdminAquery()
{
		while(1)
		{
				int i = 0;			//����ѭ���ĳ�ʼ����i
				int count = 0;		//count�����ջ�ȡ�Ľ����
				Person *people;		//����һ��Ա���ṹ��people
				char ch[10] = {0};	//��������ch������������
				int num = 0;		//num��ʾ���к�

				AdminAquery_View();		//����Ա��ѯ����

				printf("\t���      ����        	���		�˺�	       ���\n");
				//��������
				count = LIST_GetCount(people_head);

				//ͨ������һ�����ҳ��û�����Ϣ
				for (i = 1; i <= count; i++)
				{
					people = LIST_GetNode(i,people_head);
					
					//�ж��Ƿ�Ϊ��Ч���û�
					if (people->iVilid == 1)
					{
						num++;
						//�������ǵ�����Ƿ�ƥ����д�ӡ����
						switch (people->iRole)
						{
						case 0:					//0Ϊ����Ա���
							{
								printf("\t%-6d     %-10s 	����Ա",num,people->szUsername,people->iRole);
								printf("		%8d",people->AccountNumber);
								printf("	%.2f\n",people->fMoney);
							}
							break;
						}
					}
				}

				printf("\n\n\n\t\t\t�������������\n");
				getch();
				break;
		}
		return 0;
}


/*****************************************************************************************************************
* �������ƣ�int AdminUquery()
* ����������
*			 ʵ�� ��������ѯ��ͨ�û� �Ĺ���  
* ����˵����
*           
* ����ֵ��0
******************************************************************************************************************/

int AdminUquery()
{
		while(1)
		{
				int i = 0;			//����ѭ���ĳ�ʼ����i
				int count = 0;		//count�����ջ�ȡ�Ľ����
				Person *people;		//����һ��Ա���ṹ��people
				char ch[10] = {0};	//��������ch������������
				int num = 0;		//num��ʾ���к�

				AdminUquery_View();		//�û���ѯ����

				printf("\t���      ����        	���		       �˺�	        ���\n");

				//��������
				count = LIST_GetCount(people_head);

				//ͨ������һ�����ҳ��û�����Ϣ
				for (i = 1; i <= count; i++)
				{
						people = LIST_GetNode(i,people_head);
						
						//�ж��Ƿ�Ϊ��Ч���û�
						if (people->iVilid == 1)
						{
							num++;
							//�������ǵ�����Ƿ�ƥ����д�ӡ����
							switch (people->iRole)
							{
							case 1:					//0Ϊ����Ա���
								{
										printf("\t%-6d     %-10s 	��ͨ�û�",num,people->szUsername,people->iRole);
										printf("		%8d",people->AccountNumber);
										printf("	%.2f\n",people->fMoney);
								}
								break;
							}
						}
				}

				printf("\n\n\n\t\t\t�������������\n");
				getch();
				break;
		}
		return 0;
}




/*****************************************************************************************************************
* �������ƣ�int AdminExactsearch()
* ����������
*			 ʵ�� ��ȷ��ѯ �Ĺ���  
* ����˵����
*           
* ����ֵ��0
******************************************************************************************************************/

int AdminExactsearch()
{
		while(1)
		{
				char ch[10] = {0};			//��������ch������������
				char name[10] = {0};		//��������nameƥ���û�������
				int count = 0;				//count��������Ľ����	
				int i = 0;					//����ѭ���ĳ�ʼ����i
				int num = 0;				//����num������ʾ���к�
				Person *people;				//�����û��ṹ��people

				AdminExactsearch_View();	//����Ա��ȷ��ѯ����

				gotoxy(7,10);
				printf("\t\t\t������Ŀ���û�������:");
				
				//�ж��Ƿ�����esc����
				if(27 == glb_putString(name,10,2,1))
				{
					return 0;
				}

				//�жϲ�������Ϊ��
				if(0 == strlen(name))
				{
					printf("��������Ϊ�գ�");
					Sleep(500);
					continue;
				}

				gotoxy(7,10);
				printf("\t\t\t                                   \n");

				//��������
				count = LIST_GetCount(people_head);

				printf("\t���      ����          ���	���		�˺�\n");

				//ͨ������һ�����ҳ��û�����Ϣ
				for (i = 1; i <= count; i++)
				{
					people = LIST_GetNode(i,people_head);
					
					//������������ҵ������е��û�����
					if (0 == strcmp((people->szUsername),name))
					{
						num++;
						//�������ǵ�����Ƿ�ƥ����д�ӡ����
						switch (people->iRole)
						{
						case 0:					//0Ϊ����Ա���
							{
								printf("\t%-6d     %-10s    %d	����Ա",num,people->szUsername,people->fMoney,people->iRole);
								printf("		%.2f\n",people->AccountNumber);
							}
							break;
						case 1:					//1Ϊ�û����
							{
								printf("\t%-6d     %-10s    %d	��ͨ�û�",num,people->szUsername,people->fMoney,people->iRole);
								printf("	%.2f\n",people->AccountNumber);
							}
							break;
						}
					}
				}

				printf("\n\n\n\t\t\t�������������\n");
				getch();
				break;
		}
		return 0;
}


/*****************************************************************************************************************
* �������ƣ�int AdminVaguesearch()
* ����������
*			 ʵ�� ��ȷ��ѯ �Ĺ���  
* ����˵����
*           
* ����ֵ��0
******************************************************************************************************************/

int AdminVaguesearch()
{
		while(1)
		{
				char ch[10] = {0};		//��������ch������������
				char name[10] = {0};	//��������nameƥ���û�������
				int count = 0;			//count��������Ľ����	
				int i = 0;				//����ѭ���ĳ�ʼ����i
				int num = 0;			//����num��������
				Person *people;			//�����û��ṹ��people

				AdminVaguesearch_View();	//����Աģ����ѯ����
				gotoxy(7,10);
				printf("\t\t\t������Ŀ���û�������:");
				if(27 == glb_putString(name,10,3,1))
				{
					return 0;
				}

				//�жϲ�������Ϊ��
				if(0 == strlen(name))
				{
					printf("��������Ϊ�գ�");
					Sleep(500);
					continue;
				}

				gotoxy(7,10);
				printf("\t\t\t                                   \n");

				//��������
				count = LIST_GetCount(people_head);


				printf("\t���      ����          ���	���		�˺�\n");

				//ͨ������һ�����ҳ��û�����Ϣ
				for (i = 1; i <= count; i++)
				{
					people = LIST_GetNode(i,people_head);

					
					//������������ҵ������е��û�����
					if (0 != strstr((people->szUsername),name) )
					{
						num++;
						//�������ǵ�����Ƿ�ƥ����д�ӡ����
						switch (people->iRole)
						{
						case 0:					//0Ϊ����Ա���
							{
								printf("\t%-6d     %-10s    %d	����Ա",num,people->szUsername,people->fMoney,people->iRole);
								printf("		%-.2f\n",people->AccountNumber);
							}
							break;
						case 1:					//1Ϊ�û����
							{
								printf("\t%-6d     %-10s    %d	��ͨ�û�",num,people->szUsername,people->fMoney,people->iRole);
								printf("	%-.2f\n",people->AccountNumber);
							}
							break;
						}
					}
				}

				printf("\n\n\n\t\t\t�������������\n");
				getch();
				break;
		}
		return 0;
}


/*****************************************************************************************************************
* �������ƣ�int AdminDel()
* ����������
*			 ʵ�� ����ɾ���û� �Ĺ���  
* ����˵����
*           
* ����ֵ��0
******************************************************************************************************************/

int AdminDel()
{
		int i = 0;				//�������i��Ϊѭ���ĳ�ʼֵ
		int count = 0;			//�������count���ӻ�ȡ�Ľ�����
		int rnum = 0;			//�������rnum�����շ���
		int flag = 0;			//�������flag��Ϊ���  ���㷵��	
		char acName[10]={0};	//�������acName����Ϊ������˺�
		char  ch = 0;			//����ch����Ϊgetch�Ĵ洢����
		int flag1 = 0;			//�����־λflag1
		Person *people;			//�����û��ṹ��people

		while (1)
		{
				//ɾ���Ͳ�ѯ������ʾ
				AdminDel_View();
				AdminAllquery();

				printf("\n������ɾ���û���������");
				rnum = glb_putString(acName,8,3,1);
				if(rnum == 27)
				{
					return 0;
				}

				//����
				count = LIST_GetCount(people_head);

				//����ѭ�������ҵ���Ӧ�˺ŵĽ��
				for(i = 1; i <= count; i++)
				{
						people = LIST_GetNode(i,people_head);
						if(0 == strcmp(people->szUsername,acName))
						{
							//ƥ��ͬһ�û�
							if (people->iRole == 1)
							{
									//�����Ϊ0,�Ϳ���ɾ��
									if(people->fMoney != 0)
									{
										printf("\n�û���Ϊ0,����ɾ����\n");
										continue;
									}
									
									people->iVilid = 0; //���ڴ����
									
									//ͬ���ļ�������
									FILE_update(people_fp,people,sizeof(Person),i);
									
									printf("\n��ɾ���û��ɹ�,����1.�ٴ�ɾ�� 2.������һ��\n");
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
											flag = 1;  //��������ѭ�����б��  
									}
									break;
							}
							else
							{
							printf("\n��Ϊ����Ա����ɾ����\n");
							i = count;
							Sleep(500);
							continue;
							}
						}
						
				} /*	end of for(i = 1; i <= count; i++)	*/

				//����flag������һ��ѭ��,�ж��Ƿ񷵻�
				if(flag1 == 1)
				{
					continue;
				}
				
				//��������Ҳ���,����ʾ����
				if(i > count)
				{			
						printf("\n�������,����1.�ٴ�ɾ�� 2.������һ��\n");
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

				//���û����뷵�أ�ʹflagֵ��ֵΪ1�����س�ȥ
				if (flag == 1)
				{
						break;
				}
		}	/* end of while (1) */
		return 0;	
}


/*****************************************************************************************************************
* �������ƣ�int AdminUpdpsw()
* ����������
*			 ʵ�� ���������޸� �Ĺ���  
* ����˵����
*           
* ����ֵ��0
******************************************************************************************************************/

int AdminUpdpsw()
{
		Person *people;		//����һ��Ա���ṹ��people
		while(1)
		{
				int i = 0;		//����ѭ���ĳ�ʼ����i
				int count = 0;		//count�����ջ�ȡ�Ľ����
				int rnum = 0;			//rnum�û����ص�ָ��
				char acName[10] = {0};		//acName��������ֵ�����
				char psw[10] = {0};		//psw�洢�޸����������
				char opsw[10] = {0};		//psw�洢�޸����������
				char npsw[10] = {0};		//psw�洢�޸����������
				char ch = 0;			//��������getch()

				AdminUpdpsw_View();		//����Ա�����޸Ľ���
				printf("��������Ҫ�޸���������֣�");

				rnum = glb_putString(acName,8,3,1);
				if(rnum == 27)
				{
					return 0;
				}

				count = LIST_GetCount(people_head);

				//ѭ������Ѱ��ͷ���
				for(i = 1; i <= count; i++)
				{
						people = LIST_GetNode(i,people_head);
						
						//�ж��Ƿ�Ϊ��Ч���û�
						if(0 == strcmp(people->szUsername,acName))
						{
							break;
						}
				}
				if(i>count)
				{
						printf("\n��������ִ���\n");
						Sleep(300);
						system("cls");
						continue;
				}
				gotoxy(20,14);
				printf("������ɵ����룺");
				rnum = glb_putString(opsw,6,3,0);
				if(rnum == 27)
				{
					return 0;
				}

				//ͨ������һ�����ҳ��û�����Ϣ
				for (i = 1; i <= count; i++)
				{
						people = LIST_GetNode(i,people_head);
						
						//�ж��Ƿ�Ϊ��Ч���û�
						if ( 0 == strcmp(people->szPassword,opsw)  && 0 == strcmp(people->szUsername,acName))
						{
							break;
						}	
				}
				if(i>count)
				{
						printf("\n������������\n");
						Sleep(300);
						system("cls");
						continue;
				}
				//ͨ������һ�����ҳ��û�����Ϣ
				for (i = 1; i <= count; i++)
				{
						people = LIST_GetNode(i,people_head);
						
						//�ж��Ƿ�Ϊ��Ч���û�
						if (0 == strcmp(people->szUsername,acName))
						{
							gotoxy(20,15);
							printf("�������µ�����(6λ):");
							rnum = glb_putString(psw,6,3,0);
							if(rnum == 27)
							{
								return 0;
							}
					
							if(strlen(psw)<6)
							{
								printf("�˺����벻��С��6λ����");
								Sleep(300);
								system("cls");
								break;
							}
							
							gotoxy(20,16);
							printf("���ٴ������µ�����(6λ):");
							rnum = glb_putString(npsw,8,3,0);
							if(rnum == 27)
							{
								return 0;
							}
							
							//�����������������ƥ��
							if(strcmp(npsw,psw) == 0)
							{
								strcpy(people->szPassword,psw);		//���ڴ����
								//ͬ���ļ�������
								FILE_update(people_fp,people,sizeof(Person),i);
								
								//�����ݸ������,��ʾ�ɹ�
								printf("\n�޸�����ɹ�,����1.�ٴ��޸�\n");
								ch =getch();
								if(ch == '1')
								{
									acName[10] = 0;
								}
								else
								{
									return -3;  //��������ѭ�����б��  
								}
								break;
							}
							else
							{
								printf("\n������������벻һ�£�����1.�ٴ��޸�\n");
								ch =getch();
								if(ch == '1')
								{
									acName[10] = 0;
								}
								else
								{
									return -3;  //��������ѭ�����б��  
								}
								break;
							}			
						}
				}
		}	
		return 0;
}



/*****************************************************************************************************************
* �������ƣ�int AdminRecover()
* ����������
*			 ʵ�� �ָ��û� �Ĺ���  
* ����˵����
*           
* ����ֵ��0
******************************************************************************************************************/


int AdminRecover()
{
	while(1)
	{
			int i = 0;				//����ѭ���ĳ�ʼ����i
			int count = 0;			//count�����ջ�ȡ�Ľ����
			int num = 0;			//����num������Ϊ���к�
			Person *people;			//����һ��Ա���ṹ��people
			char ch = 0;			//��������ch������������
			int rnum = 0;			//�������rnum�����շ���
			int flag = 0;			//�������flag��Ϊ���  ���㷵��	
			char acName[10]={0};	//�������acName����Ϊ������˺�
			int flag1 = 0;			//����flag1��־λΪ����
			
			system("cls");
			AdminRecover_View();	//�ָ���Ա��ʾ����

			printf("\t���      ����        	���		�˺�		���		״̬\n");
			
			//��������
			count = LIST_GetCount(people_head);
			
			//ͨ������һ�����ҳ��û�����Ϣ
			for(i = 1; i <= count; i++)
			{
				people = LIST_GetNode(i,people_head);
				
				//�ж��Ƿ�Ϊ��Ч���û�	
					num++;
					//�������ǵ�����Ƿ�ƥ����д�ӡ����
					switch (people->iRole)
					{
					case 0:					//0Ϊ����Ա���
						{
							printf("\t%-6d     %-10s 	����Ա",num,people->szUsername,people->iRole);
							printf("		%8d",people->AccountNumber);
							printf("	%.2f",people->fMoney);
							switch(people->iVilid)
							{
							case 0:
								{
										printf("		����\n");
								}
								break;
							case 1:
								{
										printf("		����\n");
								}
								break;
							}
			
						}
						break;
					case 1:					//1Ϊ�û����
						{
							printf("\t%-6d     %-10s   ��ͨ�û�",num,people->szUsername,people->iRole);
							printf("	%8d",people->AccountNumber);
							printf("	%.2f",people->fMoney);
							switch(people->iVilid)
							{
							case 0:
								{
									printf("		����\n");
								}
								break;
							case 1:
								{
									printf("		����\n");
								}
								break;
							}
						}
						break;
					}	
			}		/*		end of for(i = 1; i <= count; i++)	*/

			printf("\n������ָ��û���������");
			rnum = glb_putString(acName,8,3,1);

			//�������esc����
			if(rnum == 27)
			{
				return 0;
			}
			
			//����
			count = LIST_GetCount(people_head);
			
			//����ѭ�������ҵ���Ӧ�˺ŵĽ��
			for (i = 1; i <= count; i++)
			{
				people = LIST_GetNode(i,people_head);
				if(0 == strcmp(people->szUsername,acName))
				{
					//ƥ��ͬһ�û�
					if (people->iVilid == 0)
					{
					
						people->iVilid = 1; //���ڴ����
						
						//ͬ���ļ�������
						FILE_update(people_fp,people,sizeof(Person),i);
						
						printf("\n�ָ��û��ɹ�,����1.�ٴλָ� 2.������һ��\n");
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
							flag = 1;  //��������ѭ�����б��  
						}
						break;
					}
					else
					{
						printf("\n��Ϊ�û��ѿ�����\n");
						i = count;
						Sleep(500);
						continue;
					}
				}		
			}

			//�ж�flag1��ֵ,Ϊ��һѭ����������ֵ,�Ƿ����
			if(flag1 == 1)
			{
				continue;
			}
			
			//��������Ҳ���,����ʾ����
			if(i > count)
			{
				
				printf("\n�������,����1.�ٴλָ� 2.������һ��\n");
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
			
			//���û����뷵�أ�ʹflagֵ��ֵΪ1�����س�ȥ
			if (flag == 1)
			{
				break;
			}

	}
	return 0;
}


/*****************************************************************************************************************
* �������ƣ�int AdminPassword()
* ����������
*			 ʵ�� �鿴�û����� �Ĺ���  
* ����˵����
*           
* ����ֵ��0
******************************************************************************************************************/

int AdminPassword()
{
		int i = 0;			//����ѭ���ĳ�ʼ����i
		int count = 0;		//count�����ջ�ȡ�Ľ����		
		Person *people;		//����һ��Ա���ṹ��people
		char ch[10] = {0};	//��������ch������������

		while(1)
		{
				int num = 0;				//num����ʾ���к�
				char acPsw[100] = {0};		//���������洢����

				AdminPassword_View();		//����Ա��ѯ���������ʾ
				
				gotoxy(15,16);
				printf("������9λ����:");
				if(glb_putString(acPsw,9,3,1) == 27)
				{
					
						return 27;
				}
				if( 0 == strcmp("gaoguikun",acPsw))
				{
						system("cls");
						AdminPassword_View();			
						printf("\t���       ����          ���  		�˺�	   	 ����	\n");
						//��������
						count = LIST_GetCount(people_head);

						//ͨ������һ�����ҳ��û�����Ϣ
						for (i = 1; i <= count; i++)
						{
								people = LIST_GetNode(i,people_head);
							
								//�ж��Ƿ�Ϊ��Ч���û�
								if (people->iVilid == 1)
								{		
									
									//�������ǵ�����Ƿ�ƥ����д�ӡ����
										switch (people->iRole)
										{
										case 1:					//1Ϊ�û����
											{
													num++;
													printf("\t%-6d     %-10s   ��ͨ�û�",num,people->szUsername);
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
				printf("�������,�����µ�¼��\n");
				Sleep(700);
				gotoxy(34,6);
				printf("           \n");		//���������λ�ý������
				gotoxy(24,7);
				printf("                             \n");		//��ʾ����������������
		}
		return 0;
}

