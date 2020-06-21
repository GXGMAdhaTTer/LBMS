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

/*  < ���� >
 *  �������û����ݿ��װ��һ������
 */

// �û����ݿ�ṹ
/*typedef struct user_db DB_User;
struct user_db {
    //ͳ�ƣ�����������д�����ݿ�ͷ��
    unsigned int LatestUID; //���µ�UID����ע����û�IDΪ��ֵ+1
    unsigned int TotalUser; //���û���

    //����
    User* UserList; //�û���¼����
    User* OperatingUser; //��ѡ�е��û�����ͬ���鼮�⣬�û���һ��ֻ�����һ���û������ָ��ָ��ǰ�������û���
    unsigned int LoginStatus : 1; //��¼״̬��0Ϊδ��¼��1Ϊ�ѵ�¼���ѵ�¼ʱ�޷��ƶ�OperatingUserָ��

    //��¼�ǳ�
    //��ע����¼�ǳ��û�ʱ��ʹ�����ݿ�ṹ��Login/out����Ҫ���û�����ķ���
    int (*Login)(DB_User* This, unsigned char* UName, unsigned char* password); //��UID�������¼�û�������1�ɹ���0ʧ��
    void (*Logout)(DB_User* This); //�ǳ�

    //�û�����
    void (*Regist)(DB_User* This, User* new_user); //ע���û�(������������ע��)

    //���ݿ����
    void (*ReadFromFile)(DB_User* This, char* direction); //���ļ���ȡ
    void (*WriteToFile)(DB_User* This, char* direction); //д���ļ�
    void (*Abandom)(DB_User* This); //�������ݿ����(�������¶�ȡ�ļ�ʵ��ˢ�£��ᶪ�������Ѷ�ȡ�����޸ĵ�����)
};*/


// ���������ĺ��������鼮�����ƣ�����Ͳ��ظ�ע����
int loginDB(DB_User* This, unsigned char* UName, unsigned char* password) {
    if (This->LoginStatus == 1) {
        Call_Warning("��ǰ�û��ѵ�¼.");
        return 0;
    }

    User* cursor = This->UserList;
    while (cursor != NULL) {
        if (strcmp(cursor->Info.UserName, UName) == 0)
            goto ContinueLoginDB;
        cursor = cursor->Next;
    }
    Call_Promote("�û�������.");
    return 0;

    ContinueLoginDB:
    if (cursor->Login(cursor, password)) {
        Call_Promote("��¼�ɹ�.");
        This->OperatingUser = cursor;
        This->LoginStatus = 1;
        return 1;
    }
    else {
        Call_Promote("�������.");
        return 0;
    }
}

void logoutDB(DB_User* This) {
    if (This->LoginStatus == 0) {
        Call_Warning("��ǰ�û�δ��¼.");
        return;
    }

    This->LoginStatus = 0;
    This->OperatingUser->Logout(This->OperatingUser);

    Call_Promote("�ǳ��ɹ�.");
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
        Call_Error("�û����ݿ��ȡʧ�ܻ��ļ�������.");
        if (fclose(p_file))
            Call_Error("�ļ�û�������ر�.");
        return; //Exit
    }

    //�ļ�ͷ
    fread(&(This->LatestUID), sizeof(int), 1, p_file);
    fread(&(This->TotalUser), sizeof(int), 1, p_file);
    if (This->TotalUser == 0) {
        Call_Warning("��ǰ���ݿ�û���û�.");
        This->UserList = NULL;
        //�ر��ļ�
        if (fclose(p_file))
            Call_Error("�ļ�û�������ر�.");
        return;
    }

    //��ȡ����
    const int size_of_userinfo = sizeof(UserInfo);
    UserInfo temp_ui;  //������
    User* temp_link, * temp_prev;  //������
    int count = 0;
    //��ȡ��һ����¼�����ʧ��֤�����ݿ�Ϊ��
    if (fread(&temp_ui, size_of_userinfo, 1, p_file) != 1) {
        Call_Error("���ݿ�Ϊ�գ������ݿ�ͷ����¼�ǿգ����ܳ��ּ�¼��.");
        This->UserList = NULL;
        //�ر��ļ�
        if (fclose(p_file))
            Call_Error("�ļ�û�������ر�.");
        return;
    } 
    This->UserList = temp_prev = NewUser(temp_ui);  //���ݿ�ṹ�е�����ָ��ָ���ͷ
    count++;
    //��Ϊһ�ζ�ȡһ�飬ֻҪ��ȡ����Ϊ1�ʹ����ȡ�ɹ�
    while (fread(&temp_ui, size_of_userinfo, 1, p_file) == 1) {
        //�Ѷ�ȡ�������ݽ�������
        temp_link = NewUser(temp_ui);
        temp_link->Previous = temp_prev;
        temp_link->Next = NULL;
        temp_prev->Next = temp_link;
        temp_prev = temp_link;
        count++;
    }
    //�˳�ʱ�ж��Ƿ�Ϊ�����˳�
    if (count == This->TotalUser) {
        //�ر��ļ�
        if (fclose(p_file))
            Call_Error("�ļ�û�������ر�.");
        return;
    }
    else if (ferror(p_file) != 0)
        Call_Error("��ȡ�쳣�ж�.");
    else
        Call_Error("�û����ݿ��ܲ�����.");

    //�ر��ļ�
    if (fclose(p_file))
        Call_Error("�ļ�û�������ر�.");
}

void write_user_bdb(DB_User* This, char* direction) {
    Call_Promote("δ��ɵĹ���.");
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

// ����

// �½�һ�����ݿ�
//������û�ж�ȡ����Ҳ�ᱻ��ʼ��Ϊһ���Ϸ��Ŀտ⣬����ֱ���½��û���ʹ�ã�
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