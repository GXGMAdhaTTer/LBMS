#ifndef DB_CSV_H
#define DB_CSV_H

// 从文件中读取字符串，到",","\0","\n","\t",EOF结束（会读走结束的逗号，并给字符串加上0结尾）
void fgetCommaEndString(FILE* from_file, char* buffer);
// 把Y/M/D格式的字符串转化为日期
DateEx TranslateToDate(char* from_str);
// 把字符串转化为int
// 为了程序稳定性，少用fscanf
int TranslateToInt(char* from_str);
// 将csv转bitDB
void TransformToBDB(char* from_where, char* to_where);

#endif