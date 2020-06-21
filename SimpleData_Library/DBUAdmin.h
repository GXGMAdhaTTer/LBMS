#ifndef DB_UADMIN_H
#define DB_UADMIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "DBStruct.h"
#include "DBGeneral.h"

// 用户数据库结构
typedef struct user_db DB_User;
struct user_db {
    //统计（这两个数据写在数据库头）
    unsigned int LatestUID; //最新的UID，新注册的用户ID为该值+1
    unsigned int TotalUser; //总用户数

    //数据
    User* UserList; //用户记录链表
    User* OperatingUser; //被选中的用户（不同于书籍库，用户库一次只会操作一个用户，这个指针指向当前操作的用户）
    unsigned int LoginStatus : 1; //登录状态，0为未登录，1为已登录，已登录时无法移动OperatingUser指针

    //登录登出
    //【注】登录登出用户时请使用数据库结构的Login/out而不要用用户对象的方法
    int (*Login)(DB_User* This, unsigned char* UName, unsigned char* password); //用UID和密码登录用户，返回1成功，0失败
    void (*Logout)(DB_User* This); //登出

    //用户操作
    void (*Regist)(DB_User* This, User* new_user); //注册用户(请用明文密码注册)

    //数据库操作
    void (*ReadFromFile)(DB_User* This, char* direction); //从文件读取
    void (*WriteToFile)(DB_User* This, char* direction); //写到文件
    void (*Abandom)(DB_User* This); //重置数据库对象(用来重新读取文件实现刷新，会丢弃所有已读取和已修改的数据)
};

int loginDB(DB_User* This, unsigned char* UName, unsigned char* password);
void logoutDB(DB_User* This);
void registUser(DB_User* This, User* new_user);
void read_user_bdb(DB_User* This, char* direction);
void write_user_bdb(DB_User* This, char* direction);
void abandom_user_db(DB_User* This);

// 新建一个数据库
//（就算没有读取，它也会被初始化为一个合法的空库，允许直接新建用户来使用）
DB_User* NewUserDB();

#endif