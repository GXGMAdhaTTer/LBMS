#ifndef DB_CSV_H
#define DB_CSV_H

// ���ļ��ж�ȡ�ַ�������",","\0","\n","\t",EOF����������߽����Ķ��ţ������ַ�������0��β��
void fgetCommaEndString(FILE* from_file, char* buffer);
// ��Y/M/D��ʽ���ַ���ת��Ϊ����
DateEx TranslateToDate(char* from_str);
// ���ַ���ת��Ϊint
// Ϊ�˳����ȶ��ԣ�����fscanf
int TranslateToInt(char* from_str);
// ��csvתbitDB
void TransformToBDB(char* from_where, char* to_where);

#endif