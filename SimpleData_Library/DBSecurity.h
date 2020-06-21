#ifndef DBSECURITY_H
#define DBSECURITY_H 

// 获取char的半字节
#define HighHalf(ch) (~((~ch)|0xF0))
#define LowHalf(ch) (~((~ch)|0x0F))

// 生成消息摘要
// 这个函数调用现有的MD5模块，将16字节的MD5结果传到output_buffer
// 故output_buffer需要至少16字节
void GenerateMD(unsigned char* origin_message, int message_length, unsigned char* output_buffer);

// 一个非常简单的对称加密算法
// 密钥固定为128位（16字节），结果输出到output_buffer
// P.S.原本打算用AES的，被它千层饼式的密钥算法劝退了
void SEA_Encrypt(unsigned char* key, unsigned char* origin_message, int message_length, unsigned char* output_buffer);
// 解密算法
// 密钥固定为128位（16字节），结果输出到output_buffer
// （其实就是加密过程反序）
void SEA_Decrypt(unsigned char* key, unsigned char* origin_message, int message_length, unsigned char* output_buffer);

#endif