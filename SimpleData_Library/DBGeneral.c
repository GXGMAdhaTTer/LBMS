#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "DBGeneral.h"

/* ----- DB_General ----- */
/* ----- ver 0.0.1 ----- */

/*  介绍
 * 通用模块
 *
 * 【中文乱码问题】
 * 如果发生中文乱码，请将项目->属性->高级->字符集设置为“未设置”
 */


/* --- 通用部分 --- */

/*#define MAX(x,y) ((x)>=(y)?(x):(y))
#define MIN(x,y) ((x)<=(y)?(x):(y))*/

// 报错，输出err_detail的内容
void Call_Error(char *err_detail){
	char err_text[512] = "An ERROR Occured at:\n";
	strcat(err_text, err_detail);

	MessageBox(
		NULL,
		(LPCTSTR)(LPTSTR)err_text,
		TEXT("DBManageSystem"),
		MB_OK | MB_ICONERROR
		);
}

// 警告，输出wrn_detail的内容
void Call_Warning(char* wrn_detail) {
	char wrn_text[512] = "Warning:\n";
	strcat(wrn_text, wrn_detail);

	MessageBox(
		NULL,
		(LPCTSTR)(LPTSTR)wrn_text,
		TEXT("DBManageSystem"),
		MB_OK | MB_ICONWARNING
	);
}

// 提示，输出pro_detail的内容
void Call_Promote(char* pro_detail) {
	MessageBox(
		NULL,
		(LPCTSTR)(LPTSTR)pro_detail,
		TEXT("DBManageSystem"),
		MB_OK | MB_ICONASTERISK
	);
}