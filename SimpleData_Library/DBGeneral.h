#ifndef DB_GENERAL_H
#define DB_GENERAL_H

#define MAX(x,y) ((x)>=(y)?(x):(y))
#define MIN(x,y) ((x)<=(y)?(x):(y))

// �������err_detail������
void Call_Error(char *err_detail);
// ���棬���wrn_detail������
void Call_Warning(char* wrn_detail);
// ��ʾ�����pro_detail������
void Call_Promote(char* pro_detail);

#endif
