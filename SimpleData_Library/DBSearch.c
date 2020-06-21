#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <Windows.h>

#include "DBGeneral.h"

#include "DBSearch.h"

/* ----- DB_Search ----- */
/* ----- ver 0.0.2 ----- */

/*  < ���� >
 *  �����ݿ���������Ҫ�õ���ģ��
 */


/* < Step 1 > ģ������ */

/* < ��ȡ�ַ�����ض� >
 *
 * �����������ַ���str_search���ַ���str_target�е����Ƴ̶�
 *
 * ���Ƴ̶ȵļ��㹫ʽ��double Similarity = ((LenLCS / Len(target)) + CosSml) * 0.5
 * ����LenLCS���������ͬ�Ӵ��ĳ��ȣ���ӳsearch���ַ���target�еĸ��������ȣ�
 * CosSml���ַ����������ƶȣ���ӳsearch���ַ���target�е��ظ�������
 *
 * SimilarityΪһ��[0,1]��ĸ���������Ϊsearch��target��ص����Ŷ�
 * ��DBAdmin��ʹ��ʱ��������Ϊ���Ŷ�>0.6�������ַ������
 */
double Similarity(char* str_search, char* str_target) {    
    double cossimi = CosSml(str_search, str_target);
    if (cossimi < 0.20)
        return 0.0; //CosSmlʱ�临�Ӷ�O(n)���������һ��ֵ������ȷ�������ַ����޹أ������ٽ���O(m*n)�ĺ�������
    int lcs = LenLCS(str_search, str_target);
    return ((double)lcs / strlen(str_target) + cossimi) * 0.5;
}


// < ����Ӵ� >
// �����������ַ���str_search���ַ���str_target�е�������Ӵ����� 
    // ����ȽϷ�
    int LenLCS(char* str_search, char* str_target) {
        int maxCSlen = 0; //��������Ӵ�����
        int len_s = strlen(str_search);
        int len_t = strlen(str_target);
        //���湹������CSlen[len_t + 1][len_s + 1]���ඨ���[0][]�к�[][0]��Ϊ�˷���������
        int** CSlen = (int**) calloc((len_t + 1) , sizeof(int*));
        for (int i = 0; i <= len_t; ++i) {
            CSlen[i] = (int*) calloc((len_s + 1) , sizeof(int)); //calloc�Դ���ʼ��
        } //VS���ܶ��嶯̬������Ҳ�����ΰ�

        //����ö������m*n���Ӵ��������
        int pos_s, pos_t; //��¼���ڴ���������ַ����ֱ��λ��
        for (pos_t = 1; pos_t <= len_t; ++pos_t) {
            for (pos_s = 1; pos_s <= len_s; ++pos_s) {
                if (str_target[pos_t - 1] == str_search[pos_s - 1]) {
                    CSlen[pos_t][pos_s] = CSlen[pos_t - 1][pos_s - 1] + 1;
                    maxCSlen = CSlen[pos_t][pos_s] > maxCSlen ? CSlen[pos_t][pos_s] : maxCSlen;
                }
            }
        }  //������O(m*n)�����������
    
        //�����ͷ�֮ǰ����Ķ�̬����
        for (int i = 0; i <= len_t; ++i)
            free(CSlen[i]);
        free(CSlen);

        return maxCSlen;
    }
    // �ݹ鷨��Ч��̫�ͣ������ã�
    /* 
    int LenLCS_R(char* str_search, char* str_target) {
        if (strcmp(str_search, str_target) == 0)
            return strlen(str_search);
        else if (*str_search == 0 || *str_target == 0)
                return 0;
        else{
            if (strlen(str_search) == strlen(str_target)) {
                //����һ����str_searchȥ�����һλ�õ����ַ���
                char search_cut_end[64]; strcpy(search_cut_end, str_search);
                search_cut_end[strlen(str_search) - 1] = 0;
                //����һ����str_targetȥ�����һλ�õ����ַ���
                char target_cut_end[64]; strcpy(target_cut_end, str_search);
                target_cut_end[strlen(str_target) - 1] = 0;

                int s1t1, s1t0, s0t1, s0t0;
                s1t1 = LenLCS_R(str_search + 1, str_target + 1); s1t0 = LenLCS_R(str_search + 1, target_cut_end);
                s0t1 = LenLCS_R(search_cut_end, str_target + 1); s0t0 = LenLCS_R(search_cut_end, target_cut_end);
                return MAX(MAX(s1t1, s0t0), MAX(s0t1, s1t0));
            }
            else if (strlen(str_search) < strlen(str_target)) {
                //����һ����str_targetȥ�����һλ�õ����ַ���
                char target_cut_end[64]; strcpy(target_cut_end, str_search);
                target_cut_end[strlen(str_target) - 1] = 0;

                int t1, t0;
                t1 = LenLCS_R(str_search, str_target + 1); t0 = LenLCS_R(str_search, target_cut_end);
                return MAX(t1, t0);
            }
            else {
                //����һ����str_searchȥ�����һλ�õ����ַ���
                char search_cut_end[64]; strcpy(search_cut_end, str_search);

                int s1, s0;
                s0 = LenLCS_R(search_cut_end, str_target); s1 = LenLCS_R(search_cut_end, str_target);
                return MAX(s0, s1);
            }
        
        }
    }*/

// < ���������ƶ� >
// �����������ַ���str_search���ַ���str_target�е����������ƶ�
    double CosSml(char* str_search, char* str_target) {
        int i;
        //���������ַ���������һ���ڻ�
        int vector_search[256] = { 0 }; //search������
        int vector_target[256] = { 0 }; //target������
        int inner_product = 0; //�ڻ�
            //��Ϊ���ղ�������ά���˷�ʱ�����Ըɴ������ڴ��һ���ַ�����������ó�����
        //��ȡ����
        for (; *str_search != 0; str_search++)
            vector_search[(unsigned char)*str_search]++;
        for (; *str_target != 0; str_target++)
            vector_target[(unsigned char)*str_target]++;
            //ע�����תΪ�޷����ַ��������ַ��ķ���λΪ1��
        //�����ڻ�
        for (i = 1; i < 256; i++)
            inner_product += (vector_search[i] * vector_target[i]);
        //����������ģ
        double mod_search, mod_target;
        mod_search = mod_target = 0.0;
        for (i = 1; i < 256; i++)
            mod_search += pow((double)vector_search[i], 2);
        mod_search = sqrt(mod_search);
        for (i = 1; i < 256; i++)
            mod_target += pow((double)vector_target[i], 2);
        mod_target = sqrt(mod_target);
        double tst= (double)inner_product / (mod_search * mod_target);
        //���
        return (double)inner_product / (mod_search * mod_target);
    }


/* < Step 2 > ��ȷ���� */

// < ��search�Ƿ�Ϊtarget���Ӵ� >
// ����������Ӵ���ϵ������1�����ǣ�0������
// [ Ver0.0.2 ] ʹ��BM�㷨������������������������Է���ȷ����ֵ�ˣ���Ȼ��ˣ�����ֻ�жϻ��ַ���
int IfSubset(char* str_search, char* str_target) {
    int len_t = strlen(str_target);
    int len_s = strlen(str_search);
    int i, j, k;
    for (i = 0; i <= len_t - len_s;) {
        BreakFromBadCharJudge: //�ӻ��ַ��ж���������ѭ��������λ��
        j = len_s - 1;
        //��ǰs�ַ���t�ַ��Ƿ���ͬ
        //��s�����һ���ַ���ʼ�Ƚ�
        if (*(str_search + j) == *(str_target + i + j)) {
            j--;
            //�ж�s��t�Ƿ��غ�
            while (*(str_search + j) == *(str_target + i + j)) { 
                j--;
                if (j < 0)
                    return 1;
            }
        }
        //���ַ��ж�
        for (k = 1; j - k >= 0; k++) { //û�н�����һ��ifʱj = len_s
            if (*(str_search + j - k) == *(str_target + i + j)) { //�ҵ�ƥ��
                i += k;
                if (i <= len_t - len_s)
                    goto BreakFromBadCharJudge; //��ΪҪ������ѭ������ֻ��goto��
                else
                    return 0;
            }
        }
        //�������ǻ��ַ�
        i += (j + 1);
    }
    //ѭ��������֤�������Ӵ�
    return 0;
}



// ��������
/*
int main() {
    char ss[] = "�����й���ʷ";

    char st1[] = "�й�������ʷ";
    printf("%lf\n", Similarity(ss, st1)); //����0.59

    char st2[] = "�����ٶ�Ӣ��";
    printf("%lf\n", Similarity(ss, st2)); //����0.32

    char st3[] = "ʷ������Ž�";
    printf("%lf\n", Similarity(ss, st3)); //����0.58

    char st4[] = "ͼ�⽣���й���ʷ";
    printf("%lf\n", Similarity(ss, st4)); //����0.82

    //ѹ�����ԣ���������5�룬ʵ��������̫����ÿ����¼����LenLCS��Ӧ�û�̺ܶ�
    //int i, j;
    //for (i = 1; i <= 100000; i++) {
    //    Similarity(st1, ss);
    //}
}*/
