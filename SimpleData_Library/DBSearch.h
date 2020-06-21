#ifndef DB_SEARCH_H
#define DB_SEARCH_H

/* < 获取字符串相关度 >
 *
 * 这个函数输出字符串str_search在字符串str_target中的相似程度
 *
 * 相似程度的计算公式：double Similarity = ((LenLCS / Len(target)) + CosSml) * 0.5
 * 其中LenLCS是最长连续共同子串的长度，反映字符串在连续性上关联度，
 * CosSml是字符串余弦相似度，反映search中字符在target中的重复出现率
 *
 * Similarity为一个[0,1]间的浮点数，作为search与target相关的置信度
 * 在DBAdmin中使用时，我们认为置信度>0.6代表两字符串相关
 */
double Similarity(char* str_search, char* str_target);
// < 求最长子串 >
// 这个函数输出字符串str_search在字符串str_target中的最长连续子串长度 
int LenLCS(char* str_search, char* str_target);
// < 求余弦相似度 >
// 这个函数输出字符串str_search在字符串str_target中的求余弦相似度
double CosSml(char* str_search, char* str_target);

// < 求search是否为target的子串 >
// 这个函数求子串关系，返回1代表是，0代表不是
// [ Ver0.0.2 ] 使用BM算法更新了这个函数，现在它可以返回确定的值了（虽然如此，这里只判断坏字符）
int IfSubset(char* str_search, char* str_target);

#endif