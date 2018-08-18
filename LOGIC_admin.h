#ifndef _ADMIN_H_
#define _ADMIN_H_

int Admin();				//管理员用户功能函数封装

int AdminAdd();				//管理员用户添加功能函数封装

int AdminAllquery();		//管理员用户查询功能函数封装

void query();				//查询用户功能函数封装

int AdminAquery();			//管理分类查询管理员函数封装

int AdminUquery();			//管理分类查询普通用户

int AdminExactsearch();		//管理员精确查询	

int AdminVaguesearch();		//管理员用户模糊查询

int AdminDel();				//管理员用户删除功能函数封装

int AdminUpdpsw();			//管理员用户修改密码函数封装

int AdminRecover();			//管理员恢复用户函数封装

int AdminPassword();		//管理员密码查询函数封装

#endif _ADMIN_H_