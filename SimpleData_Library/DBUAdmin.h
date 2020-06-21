#ifndef DB_UADMIN_H
#define DB_UADMIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "DBStruct.h"
#include "DBGeneral.h"

// �û����ݿ�ṹ
typedef struct user_db DB_User;
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
};

int loginDB(DB_User* This, unsigned char* UName, unsigned char* password);
void logoutDB(DB_User* This);
void registUser(DB_User* This, User* new_user);
void read_user_bdb(DB_User* This, char* direction);
void write_user_bdb(DB_User* This, char* direction);
void abandom_user_db(DB_User* This);

// �½�һ�����ݿ�
//������û�ж�ȡ����Ҳ�ᱻ��ʼ��Ϊһ���Ϸ��Ŀտ⣬����ֱ���½��û���ʹ�ã�
DB_User* NewUserDB();

#endif