#ifndef DB_SEARCH_H
#define DB_SEARCH_H

/* < ��ȡ�ַ�����ض� >
 *
 * �����������ַ���str_search���ַ���str_target�е����Ƴ̶�
 *
 * ���Ƴ̶ȵļ��㹫ʽ��double Similarity = ((LenLCS / Len(target)) + CosSml) * 0.5
 * ����LenLCS���������ͬ�Ӵ��ĳ��ȣ���ӳ�ַ������������Ϲ����ȣ�
 * CosSml���ַ����������ƶȣ���ӳsearch���ַ���target�е��ظ�������
 *
 * SimilarityΪһ��[0,1]��ĸ���������Ϊsearch��target��ص����Ŷ�
 * ��DBAdmin��ʹ��ʱ��������Ϊ���Ŷ�>0.6�������ַ������
 */
double Similarity(char* str_search, char* str_target);
// < ����Ӵ� >
// �����������ַ���str_search���ַ���str_target�е�������Ӵ����� 
int LenLCS(char* str_search, char* str_target);
// < ���������ƶ� >
// �����������ַ���str_search���ַ���str_target�е����������ƶ�
double CosSml(char* str_search, char* str_target);

// < ��search�Ƿ�Ϊtarget���Ӵ� >
// ����������Ӵ���ϵ������1�����ǣ�0������
// [ Ver0.0.2 ] ʹ��BM�㷨������������������������Է���ȷ����ֵ�ˣ���Ȼ��ˣ�����ֻ�жϻ��ַ���
int IfSubset(char* str_search, char* str_target);

#endif