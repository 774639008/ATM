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
	
pNode *head;				//����һ��ͷ���

pNode *people_head = NULL;	//����һ���û�ͷ���
FILE *people_fp;			//����һ���û��ļ�ָ��

extern pNode *trade_head;	//����һ���˵�ͷ���
FILE *trade_fp;				//����һ���˵��ļ�ָ��

int glb_people_id = 0;		//ȫ�ֱ����û�ID
int glb_trade_id = 0;		//ȫ�ֱ����˵�ID

Person g_currentUser;		//��¼��ǰ����ĵ�½�����û�
		
int main()
{
		Person *ps;			//����һ���û��ṹ��ps

		int result = 0;		//����һ��result�����������

		//�û����ݳ�ʼ��
		people_fp = FILE_open("data/user/people.txt");
		people_head=FILE_read(people_fp,sizeof(Person));
		if(	people_head->next == NULL)
		{
				people_head = USER_Data(people_fp);		//�û���ʼ����ͷ��㴫��people_head
		}
	
		trade_fp = FILE_open("data/trade/trade.txt");
		trade_head=FILE_read(trade_fp,sizeof(Trade));
		if(	trade_head->next == NULL)
		{
				trade_head = TRADE_Data(trade_fp);		
		}
		
		//��½������ʾ
		LoginView();	
		result = Login();		//result����ͨ����¼�������ص����ֵ

		//����Ƕ��,��ȡ�ĸ�������������һ��
		ps = LIST_GetNode(LIST_GetCount(people_head),people_head);  
		glb_people_id = ps->ID;
		

		ps = LIST_GetNode(LIST_GetCount(people_head),people_head); 
		glb_trade_id = ps->ID;

		//�ж������Ϣ,��������Ա���滹���û�����
		switch(result)
		{
		case 0:
			{
					Admin();	//�������Աģʽ
			}
			break;
		case 1:
			{
					User();		//�����û�ģʽ		
			}
			break;
		default:
			break;
		}

		fclose(people_fp);			//�ر��û��ļ�
		LIST_Free(people_head);		//�ͷ��û�����

		fclose(trade_fp);			//�ر��˵��ļ�
		LIST_Free(trade_head);		//�ͷ��˵�����

		return 0;
}