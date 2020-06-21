#include <stdio.h>
#include <string.h>
#include <Windows.h>

#include "MD5/MD5.h"

#include "DBSecurity.h"

/* ----- UDB_Security ----- */
/* ----- ver 0.0.1 ----- */

/*  < 介绍 >
 *  负责用户信息（主要是密码）加密的模块
 */

// 获取char的半字节
/*#define HighHalf(ch) (~((~ch)|0xF0))
#define LowHalf(ch) (~((~ch)|0x0F))*/

// 生成消息摘要
// 这个函数调用现有的MD5模块，将16字节的MD5结果传到output_buffer
// 故output_buffer需要至少16字节
void GenerateMD(unsigned char* origin_message, int message_length, unsigned char* output_buffer) {		
    MD5_CTX temp_md5;	
    MD5Init(&temp_md5);         			
    MD5Update(&temp_md5, origin_message, message_length);
    MD5Final(&temp_md5,output_buffer);
}

// 一个非常简单的对称加密算法
// 密钥固定为128位（16字节），结果输出到output_buffer
// P.S.原本打算用AES的，被它千层饼式的密钥算法劝退了
void SEA_Encrypt(
    unsigned char* key, //采用的密钥
    unsigned char* origin_message, //要加密的数据
    int message_length, //加密数据的长度
    unsigned char* output_buffer //输出缓冲区
) {
    int i, j; unsigned char tmp;
    //第一步：翻转被加密串
    i = 0; j = message_length - 1;
    while (i < j) {
        output_buffer[j] = origin_message[i];
        output_buffer[i] = origin_message[j];
        i++; j--;
    }
    if (i == j)
        output_buffer[i] = origin_message[i];
    //第二步：与key循环异或
    i = j = 0;
    while (i < message_length) {
        if (j >= 16)
            j = 0;
        tmp = output_buffer[i] ^ key[j];
        output_buffer[i] = tmp;
        i++; j++;
    }
    //第三步：半字节交换
    i = 0; j = message_length - 1;
    while (i < j) {
        tmp = HighHalf(output_buffer[i]) + LowHalf(output_buffer[j]);
        output_buffer[j] = ~(HighHalf(output_buffer[j]) + LowHalf(output_buffer[i]));
        output_buffer[i] = ~tmp;
        i++; j--;
    }
}

// 解密算法
// 密钥固定为128位（16字节），结果输出到output_buffer
// （其实就是加密过程反序）
void SEA_Decrypt(
    unsigned char* key, //采用的密钥
    unsigned char* origin_message, //要解密的数据
    int message_length, //加密数据的长度
    unsigned char* output_buffer //输出缓冲区
) {
    int i, j; unsigned char tmp;
    //第一步：半字节交换
    i = 0; j = message_length - 1;
    while (i < j) {
        output_buffer[j] = ~(HighHalf(origin_message[j]) + LowHalf(origin_message[i]));
        output_buffer[i] = ~(HighHalf(origin_message[i]) + LowHalf(origin_message[j]));
        i++; j--;
    }
    if (i == j)
        output_buffer[i] = origin_message[i];
    //第二步：与key循环异或
    i = j = 0;
    while (i < message_length) {
        if (j >= 16)
            j = 0;
        output_buffer[i] = output_buffer[i] ^ key[j];
        i++; j++;
    }
    //第三步：翻转被加密串
    i = 0; j = message_length - 1;
    while (i < j) {
        tmp = output_buffer[j];
        output_buffer[j] = output_buffer[i];
        output_buffer[i] = tmp;
        i++; j--;
    }
}