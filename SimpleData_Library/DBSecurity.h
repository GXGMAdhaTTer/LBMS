#ifndef DBSECURITY_H
#define DBSECURITY_H 

// ��ȡchar�İ��ֽ�
#define HighHalf(ch) (~((~ch)|0xF0))
#define LowHalf(ch) (~((~ch)|0x0F))

// ������ϢժҪ
// ��������������е�MD5ģ�飬��16�ֽڵ�MD5�������output_buffer
// ��output_buffer��Ҫ����16�ֽ�
void GenerateMD(unsigned char* origin_message, int message_length, unsigned char* output_buffer);

// һ���ǳ��򵥵ĶԳƼ����㷨
// ��Կ�̶�Ϊ128λ��16�ֽڣ�����������output_buffer
// P.S.ԭ��������AES�ģ�����ǧ���ʽ����Կ�㷨Ȱ����
void SEA_Encrypt(unsigned char* key, unsigned char* origin_message, int message_length, unsigned char* output_buffer);
// �����㷨
// ��Կ�̶�Ϊ128λ��16�ֽڣ�����������output_buffer
// ����ʵ���Ǽ��ܹ��̷���
void SEA_Decrypt(unsigned char* key, unsigned char* origin_message, int message_length, unsigned char* output_buffer);

#endif