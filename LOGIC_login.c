#include "head.h"
#include "CACHE_list.h"
#include "VIEW_login.h"
#include "LOGIC_login.h"
#include "LOGIC_public.h"

extern Person *p;		//������Ա�ṹ���ȫ�ֱ������������Ա�����ݱض��õ�
extern pNode *people_head;		//���������ȫ�ֱ���������������ض��õ�ͷ���

extern Person g_currentUser;	////����½�ɹ�ʱ����¼��ǰ����ĵ�½�����û�

/*****************************************************************************************************************
* �������ƣ�int Login()
* ����������
*			 ʵ�� ��½ �Ĺ���  
* ����˵����
*           
* ����ֵ��
******************************************************************************************************************/

int Login()
{
		Person *people;		//����һ���û��ṹ��people	����ƥ���¼ʱ����Ϣ

		while(1)
		{	
			
				char acStr[100] = {0};		//������ַ��洢����
				char acName[100] = {0};		//����������洢����
				char acPsw[100] = {0};		//���������洢����
				int num = 0;				//����num������������û������˺�
				int count = 0;				//������������ĸ���
				int i = 0;		//ѭ������ʹ�õĳ�ʼ����

				Banktips();
				gotoxy(34,5);
			
				//������ַ�����acAcount,���������Ϊ��8����,������������Ϊ���֣�1��,Ϊ���ģ�1��
				if(glb_putString(acName,8,3,1) == 0	)
				{
					
						printf("");
				}

				count = LIST_GetCount(people_head);
				num = atoi(acName);
				//���б��������û��������Ƿ�������������Ƿ�ƥ��
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


				//�ж�������ַ��Ƿ�Ϊ��
				if( 0 == strlen(acName))
				{
						printf("���벻��Ϊ�գ�");
						Sleep(500);
						gotoxy(34,5);
						printf("               ");
						continue;
				}

				//����Ҳ��� ����ʾ�û�������
				if(i > count)
				{
						
						gotoxy(34,7);
						printf("�û��������ڣ�\n");	
						Sleep(300);
						gotoxy(34,7);
						printf("              \n");		//�û�����ʾ�����ڽ������
						gotoxy(34,5);
						printf("              \n");		//�û����������
						continue;
				}
				
				//��һ��ѭ����֮ǰ�û�ƥ�����,������֤
				while(1)
				{
					gotoxy(34,6);
					
					//������ַ�����acPsw,���������Ϊ��6����,������������Ϊ���ֺ���ĸ��3��,Ϊ���ģ�0��
					if(27 == glb_putString(acPsw,6,1,0))
					{
						system("cls");
						return main();
					}
					
					////���б��������û��������������Ƿ�������������������Ƿ�ƥ��
					for(i = 0; i < count; i++)
					{
						p =  (Person *)LIST_GetNode(i,people_head);

						//����ҵ�ƥ�������������,����ʾ�ɹ�,���س�ȥ���û������,������Ӧ�Ľ���
						if((0 == strcmp(people->szUsername,acName)|| people->AccountNumber == num )&& 0 == strcmp(people->szPassword,acPsw)&&people->iVilid == 1)
						{	
								gotoxy(20,7);
								printf("��½�ɹ�,");
								memcpy(&g_currentUser,people,sizeof(Person));
								Sleep(200);
								printf("���Ե�>");
								for (i=0;i<10;i++)
								{
										printf(">");
										Sleep(50);
								}
								Sleep(300);
								num = people->iRole;	//���������Ϣ,������֤����,�����Ӧ�Ľ���
								return num;
						}
					}
				
					gotoxy(24,7);
					printf("�������,�����µ�¼��\n");
					Sleep(700);
					gotoxy(34,6);
					printf("           \n");		//���������λ�ý������
					gotoxy(24,7);
					printf("                             \n");		//��ʾ����������������
				}
		}
}