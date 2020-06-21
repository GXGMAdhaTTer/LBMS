#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "DBGeneral.h"

/* ----- DB_General ----- */
/* ----- ver 0.0.1 ----- */

/*  ����
 * ͨ��ģ��
 *
 * �������������⡿
 * ��������������룬�뽫��Ŀ->����->�߼�->�ַ�������Ϊ��δ���á�
 */


/* --- ͨ�ò��� --- */

/*#define MAX(x,y) ((x)>=(y)?(x):(y))
#define MIN(x,y) ((x)<=(y)?(x):(y))*/

// �������err_detail������
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

// ���棬���wrn_detail������
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

// ��ʾ�����pro_detail������
void Call_Promote(char* pro_detail) {
	MessageBox(
		NULL,
		(LPCTSTR)(LPTSTR)pro_detail,
		TEXT("DBManageSystem"),
		MB_OK | MB_ICONASTERISK
	);
}