#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "DBStruct.h"
#include "DBGeneral.h"

#include "DBUAdmin.h"

/* ----- UDB_Admin ----- */
/* ----- ver 0.0.1 ----- */

/*  < 介绍 >
 *  把整个用户数据库封装成一个对象
 */

// 用户数据库结构
/*typedef struct user_db DB_User;
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
};*/


// 几个方法的函数，与书籍库类似，这里就不重复注释了
int loginDB(DB_User* This, unsigned char* UName, unsigned char* password) {
    if (This->LoginStatus == 1) {
        Call_Warning("当前用户已登录.");
        return 0;
    }

    User* cursor = This->UserList;
    while (cursor != NULL) {
        if (strcmp(cursor->Info.UserName, UName) == 0)
            goto ContinueLoginDB;
        cursor = cursor->Next;
    }
    Call_Promote("用户不存在.");
    return 0;

    ContinueLoginDB:
    if (cursor->Login(cursor, password)) {
        Call_Promote("登录成功.");
        This->OperatingUser = cursor;
        This->LoginStatus = 1;
        return 1;
    }
    else {
        Call_Promote("密码错误.");
        return 0;
    }
}

void logoutDB(DB_User* This) {
    if (This->LoginStatus == 0) {
        Call_Warning("当前用户未登录.");
        return;
    }

    This->LoginStatus = 0;
    This->OperatingUser->Logout(This->OperatingUser);

    Call_Promote("登出成功.");
}

void registUser(DB_User* This, User* new_user) {
    This->TotalUser++;
    new_user->Info.UserID = ++(This->LatestUID);

    User* tmp = This->UserList;
    if (tmp == NULL) {
        new_user->Previous = new_user->Next = NULL;       
        This->UserList = new_user;
    }
    else {
        while (tmp->Next != NULL)
            tmp = tmp->Next;

        tmp->Next = new_user;
        new_user->Previous = tmp;
        new_user->Next = NULL;
    }

    new_user->Logout(new_user);
}

void read_user_bdb(DB_User* This, char* direction) {
    FILE* p_file;
    if ((p_file = fopen(direction, "rb")) == NULL) {
        Call_Error("用户数据库读取失败或文件不存在.");
        if (fclose(p_file))
            Call_Error("文件没有正常关闭.");
        return; //Exit
    }

    //文件头
    fread(&(This->LatestUID), sizeof(int), 1, p_file);
    fread(&(This->TotalUser), sizeof(int), 1, p_file);
    if (This->TotalUser == 0) {
        Call_Warning("当前数据库没有用户.");
        This->UserList = NULL;
        //关闭文件
        if (fclose(p_file))
            Call_Error("文件没有正常关闭.");
        return;
    }

    //读取内容
    const int size_of_userinfo = sizeof(UserInfo);
    UserInfo temp_ui;  //工具人
    User* temp_link, * temp_prev;  //工具人
    int count = 0;
    //读取第一条记录，如果失败证明数据库为空
    if (fread(&temp_ui, size_of_userinfo, 1, p_file) != 1) {
        Call_Error("数据库为空，但数据库头部记录非空，可能出现记录损坏.");
        This->UserList = NULL;
        //关闭文件
        if (fclose(p_file))
            Call_Error("文件没有正常关闭.");
        return;
    } 
    This->UserList = temp_prev = NewUser(temp_ui);  //数据库结构中的数据指针指向表头
    count++;
    //因为一次读取一块，只要读取块数为1就代表读取成功
    while (fread(&temp_ui, size_of_userinfo, 1, p_file) == 1) {
        //把读取到的数据接入链表
        temp_link = NewUser(temp_ui);
        temp_link->Previous = temp_prev;
        temp_link->Next = NULL;
        temp_prev->Next = temp_link;
        temp_prev = temp_link;
        count++;
    }
    //退出时判断是否为正常退出
    if (count == This->TotalUser) {
        //关闭文件
        if (fclose(p_file))
            Call_Error("文件没有正常关闭.");
        return;
    }
    else if (ferror(p_file) != 0)
        Call_Error("读取异常中断.");
    else
        Call_Error("用户数据可能不完整.");

    //关闭文件
    if (fclose(p_file))
        Call_Error("文件没有正常关闭.");
}

void write_user_bdb(DB_User* This, char* direction) {
    Call_Promote("未完成的功能.");
}

void abandom_user_db(DB_User* This) {
    This->LatestUID = 0;
    This->TotalUser = 0;
    User* tmp = This->UserList;
    User* prev;
    while (tmp != NULL) {
        prev = tmp;
        tmp = tmp->Next;
        free(prev);
    }
    This->UserList = NULL;
    This->OperatingUser = NULL;
}

// 外置

// 新建一个数据库
//（就算没有读取，它也会被初始化为一个合法的空库，允许直接新建用户来使用）
DB_User* NewUserDB() {
    DB_User* tmp = malloc(sizeof(DB_User));
    tmp->LatestUID = 0; tmp->TotalUser = 0;
    tmp->UserList = tmp->OperatingUser = NULL;
    tmp->LoginStatus = 0;

    tmp->Login = loginDB;
    tmp->Logout = logoutDB;
    tmp->Regist = registUser;
    tmp->ReadFromFile = read_user_bdb;
    tmp->WriteToFile = write_user_bdb;
    tmp->Abandom = abandom_user_db;

    return tmp;
}