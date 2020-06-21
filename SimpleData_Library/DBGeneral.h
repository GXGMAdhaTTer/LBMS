#ifndef DB_GENERAL_H
#define DB_GENERAL_H

#define MAX(x,y) ((x)>=(y)?(x):(y))
#define MIN(x,y) ((x)<=(y)?(x):(y))

// 报错，输出err_detail的内容
void Call_Error(char *err_detail);
// 警告，输出wrn_detail的内容
void Call_Warning(char* wrn_detail);
// 提示，输出pro_detail的内容
void Call_Promote(char* pro_detail);

#endif
