#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <Windows.h>

#include "DBGeneral.h"

#include "DBSearch.h"

/* ----- DB_Search ----- */
/* ----- ver 0.0.2 ----- */

/*  < 介绍 >
 *  在数据库搜索中需要用到的模块
 */


/* < Step 1 > 模糊搜索 */

/* < 获取字符串相关度 >
 *
 * 这个函数输出字符串str_search在字符串str_target中的相似程度
 *
 * 相似程度的计算公式：double Similarity = ((LenLCS / Len(target)) + CosSml) * 0.5
 * 其中LenLCS是最长连续共同子串的长度，反映search中字符在target中的复现完整度，
 * CosSml是字符串余弦相似度，反映search中字符在target中的重复出现率
 *
 * Similarity为一个[0,1]间的浮点数，作为search与target相关的置信度
 * 在DBAdmin中使用时，我们认为置信度>0.6代表两字符串相关
 */
double Similarity(char* str_search, char* str_target) {    
    double cossimi = CosSml(str_search, str_target);
    if (cossimi < 0.20)
        return 0.0; //CosSml时间复杂度O(n)，如果低于一定值，可以确定两个字符串无关，不必再进行O(m*n)的后续计算
    int lcs = LenLCS(str_search, str_target);
    return ((double)lcs / strlen(str_target) + cossimi) * 0.5;
}


// < 求最长子串 >
// 这个函数输出字符串str_search在字符串str_target中的最长连续子串长度 
    // 逐个比较法
    int LenLCS(char* str_search, char* str_target) {
        int maxCSlen = 0; //储存最大子串长度
        int len_s = strlen(str_search);
        int len_t = strlen(str_target);
        //下面构造数组CSlen[len_t + 1][len_s + 1]，多定义的[0][]行和[][0]列为了方便后面计算
        int** CSlen = (int**) calloc((len_t + 1) , sizeof(int*));
        for (int i = 0; i <= len_t; ++i) {
            CSlen[i] = (int*) calloc((len_s + 1) , sizeof(int)); //calloc自带初始化
        } //VS不能定义动态数组我也很无奈啊

        //下面枚举所有m*n种子串存在情况
        int pos_s, pos_t; //记录正在处理的两个字符串分别的位置
        for (pos_t = 1; pos_t <= len_t; ++pos_t) {
            for (pos_s = 1; pos_s <= len_s; ++pos_s) {
                if (str_target[pos_t - 1] == str_search[pos_s - 1]) {
                    CSlen[pos_t][pos_s] = CSlen[pos_t - 1][pos_s - 1] + 1;
                    maxCSlen = CSlen[pos_t][pos_s] > maxCSlen ? CSlen[pos_t][pos_s] : maxCSlen;
                }
            }
        }  //这玩意O(m*n)好像是最快了
    
        //下面释放之前定义的动态数组
        for (int i = 0; i <= len_t; ++i)
            free(CSlen[i]);
        free(CSlen);

        return maxCSlen;
    }
    // 递归法（效率太低，已弃用）
    /* 
    int LenLCS_R(char* str_search, char* str_target) {
        if (strcmp(str_search, str_target) == 0)
            return strlen(str_search);
        else if (*str_search == 0 || *str_target == 0)
                return 0;
        else{
            if (strlen(str_search) == strlen(str_target)) {
                //生成一个由str_search去掉最后一位得到的字符串
                char search_cut_end[64]; strcpy(search_cut_end, str_search);
                search_cut_end[strlen(str_search) - 1] = 0;
                //生成一个由str_target去掉最后一位得到的字符串
                char target_cut_end[64]; strcpy(target_cut_end, str_search);
                target_cut_end[strlen(str_target) - 1] = 0;

                int s1t1, s1t0, s0t1, s0t0;
                s1t1 = LenLCS_R(str_search + 1, str_target + 1); s1t0 = LenLCS_R(str_search + 1, target_cut_end);
                s0t1 = LenLCS_R(search_cut_end, str_target + 1); s0t0 = LenLCS_R(search_cut_end, target_cut_end);
                return MAX(MAX(s1t1, s0t0), MAX(s0t1, s1t0));
            }
            else if (strlen(str_search) < strlen(str_target)) {
                //生成一个由str_target去掉最后一位得到的字符串
                char target_cut_end[64]; strcpy(target_cut_end, str_search);
                target_cut_end[strlen(str_target) - 1] = 0;

                int t1, t0;
                t1 = LenLCS_R(str_search, str_target + 1); t0 = LenLCS_R(str_search, target_cut_end);
                return MAX(t1, t0);
            }
            else {
                //生成一个由str_search去掉最后一位得到的字符串
                char search_cut_end[64]; strcpy(search_cut_end, str_search);

                int s1, s0;
                s0 = LenLCS_R(search_cut_end, str_target); s1 = LenLCS_R(search_cut_end, str_target);
                return MAX(s0, s1);
            }
        
        }
    }*/

// < 求余弦相似度 >
// 这个函数输出字符串str_search在字符串str_target中的求余弦相似度
    double CosSml(char* str_search, char* str_target) {
        int i;
        //建立两个字符串向量与一个内积
        int vector_search[256] = { 0 }; //search的向量
        int vector_target[256] = { 0 }; //target的向量
        int inner_product = 0; //内积
            //因为按照并集定义维数浪费时间所以干脆牺牲内存把一个字符所有情况都拿出来了
        //获取向量
        for (; *str_search != 0; str_search++)
            vector_search[(unsigned char)*str_search]++;
        for (; *str_target != 0; str_target++)
            vector_target[(unsigned char)*str_target]++;
            //注意必须转为无符号字符（中文字符的符号位为1）
        //计算内积
        for (i = 1; i < 256; i++)
            inner_product += (vector_search[i] * vector_target[i]);
        //计算向量的模
        double mod_search, mod_target;
        mod_search = mod_target = 0.0;
        for (i = 1; i < 256; i++)
            mod_search += pow((double)vector_search[i], 2);
        mod_search = sqrt(mod_search);
        for (i = 1; i < 256; i++)
            mod_target += pow((double)vector_target[i], 2);
        mod_target = sqrt(mod_target);
        double tst= (double)inner_product / (mod_search * mod_target);
        //输出
        return (double)inner_product / (mod_search * mod_target);
    }


/* < Step 2 > 精确搜索 */

// < 求search是否为target的子串 >
// 这个函数求子串关系，返回1代表是，0代表不是
// [ Ver0.0.2 ] 使用BM算法更新了这个函数，现在它可以返回确定的值了（虽然如此，这里只判断坏字符）
int IfSubset(char* str_search, char* str_target) {
    int len_t = strlen(str_target);
    int len_s = strlen(str_search);
    int i, j, k;
    for (i = 0; i <= len_t - len_s;) {
        BreakFromBadCharJudge: //从坏字符判断中跳两个循环出来的位置
        j = len_s - 1;
        //当前s字符与t字符是否相同
        //从s的最后一个字符开始比较
        if (*(str_search + j) == *(str_target + i + j)) {
            j--;
            //判断s与t是否重合
            while (*(str_search + j) == *(str_target + i + j)) { 
                j--;
                if (j < 0)
                    return 1;
            }
        }
        //坏字符判断
        for (k = 1; j - k >= 0; k++) { //没有进入上一个if时j = len_s
            if (*(str_search + j - k) == *(str_target + i + j)) { //找到匹配
                i += k;
                if (i <= len_t - len_s)
                    goto BreakFromBadCharJudge; //因为要跳两个循环所以只能goto了
                else
                    return 0;
            }
        }
        //弹出，是坏字符
        i += (j + 1);
    }
    //循环结束，证明不是子串
    return 0;
}



// 测试用例
/*
int main() {
    char ss[] = "剑桥中国简史";

    char st1[] = "中国近代简史";
    printf("%lf\n", Similarity(ss, st1)); //返回0.59

    char st2[] = "剑桥少儿英语";
    printf("%lf\n", Similarity(ss, st2)); //返回0.32

    char st3[] = "史简国中桥剑";
    printf("%lf\n", Similarity(ss, st3)); //返回0.58

    char st4[] = "图解剑桥中国简史";
    printf("%lf\n", Similarity(ss, st4)); //返回0.82

    //压力测试，好像跑了5秒，实际搜索不太可能每条记录都求LenLCS，应该会短很多
    //int i, j;
    //for (i = 1; i <= 100000; i++) {
    //    Similarity(st1, ss);
    //}
}*/
