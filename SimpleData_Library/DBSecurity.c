#include <stdio.h>
#include <string.h>
#include <Windows.h>

#include "MD5/MD5.h"

#include "DBSecurity.h"

/* ----- UDB_Security ----- */
/* ----- ver 0.0.1 ----- */

/*  < ���� >
 *  �����û���Ϣ����Ҫ�����룩���ܵ�ģ��
 */

// ��ȡchar�İ��ֽ�
/*#define HighHalf(ch) (~((~ch)|0xF0))
#define LowHalf(ch) (~((~ch)|0x0F))*/

// ������ϢժҪ
// ��������������е�MD5ģ�飬��16�ֽڵ�MD5�������output_buffer
// ��output_buffer��Ҫ����16�ֽ�
void GenerateMD(unsigned char* origin_message, int message_length, unsigned char* output_buffer) {		
    MD5_CTX temp_md5;	
    MD5Init(&temp_md5);         			
    MD5Update(&temp_md5, origin_message, message_length);
    MD5Final(&temp_md5,output_buffer);
}

// һ���ǳ��򵥵ĶԳƼ����㷨
// ��Կ�̶�Ϊ128λ��16�ֽڣ�����������output_buffer
// P.S.ԭ��������AES�ģ�����ǧ���ʽ����Կ�㷨Ȱ����
void SEA_Encrypt(
    unsigned char* key, //���õ���Կ
    unsigned char* origin_message, //Ҫ���ܵ�����
    int message_length, //�������ݵĳ���
    unsigned char* output_buffer //���������
) {
    int i, j; unsigned char tmp;
    //��һ������ת�����ܴ�
    i = 0; j = message_length - 1;
    while (i < j) {
        output_buffer[j] = origin_message[i];
        output_buffer[i] = origin_message[j];
        i++; j--;
    }
    if (i == j)
        output_buffer[i] = origin_message[i];
    //�ڶ�������keyѭ�����
    i = j = 0;
    while (i < message_length) {
        if (j >= 16)
            j = 0;
        tmp = output_buffer[i] ^ key[j];
        output_buffer[i] = tmp;
        i++; j++;
    }
    //�����������ֽڽ���
    i = 0; j = message_length - 1;
    while (i < j) {
        tmp = HighHalf(output_buffer[i]) + LowHalf(output_buffer[j]);
        output_buffer[j] = ~(HighHalf(output_buffer[j]) + LowHalf(output_buffer[i]));
        output_buffer[i] = ~tmp;
        i++; j--;
    }
}

// �����㷨
// ��Կ�̶�Ϊ128λ��16�ֽڣ�����������output_buffer
// ����ʵ���Ǽ��ܹ��̷���
void SEA_Decrypt(
    unsigned char* key, //���õ���Կ
    unsigned char* origin_message, //Ҫ���ܵ�����
    int message_length, //�������ݵĳ���
    unsigned char* output_buffer //���������
) {
    int i, j; unsigned char tmp;
    //��һ�������ֽڽ���
    i = 0; j = message_length - 1;
    while (i < j) {
        output_buffer[j] = ~(HighHalf(origin_message[j]) + LowHalf(origin_message[i]));
        output_buffer[i] = ~(HighHalf(origin_message[i]) + LowHalf(origin_message[j]));
        i++; j--;
    }
    if (i == j)
        output_buffer[i] = origin_message[i];
    //�ڶ�������keyѭ�����
    i = j = 0;
    while (i < message_length) {
        if (j >= 16)
            j = 0;
        output_buffer[i] = output_buffer[i] ^ key[j];
        i++; j++;
    }
    //����������ת�����ܴ�
    i = 0; j = message_length - 1;
    while (i < j) {
        tmp = output_buffer[j];
        output_buffer[j] = output_buffer[i];
        output_buffer[i] = tmp;
        i++; j--;
    }
}