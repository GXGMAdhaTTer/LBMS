#define _CRT_SECURE_NO_WARNINGS

/*  不要编译   */

#include <stdlib.h>
#include <stdio.h>

#include "DBAdmin.h"

//#include "DBStruct.h"
//#include "DBGeneral.h"
//#include "DBCsv.h"

/* ------ 测试用例 ------ */


int main() {
	//Call_Error("测试文字");
	DB_Book* book_db = NewDBBook();
	//TransformToBDB("tstdb.csv", "tstdb.bdb");
	//book_db->ImportFromCSV(book_db, "tstdb.csv");
	//book_db->WriteToFile(book_db, "tstdb.bdb");
	//book_db->Abandon(book_db);
	book_db->ReadFromFile(book_db, "tstdb.bdb");

	book_db->SelectBy(book_db, "Title", "人类", LG_AND);
	BKSelect* slc;
	slc = book_db->pSelection;
	while (slc != NULL) {
		printf("%s\n", slc->SelectedItem->Info.Title);
		slc = slc->Next;
	}
	Book tpbook = (Book){ "银河帝国","[美]阿西莫夫","UndefPress","ISBN0000",
		(DateEx) {2010,11,2,0},"现代/科幻","外国文学/科幻小说",
		0,0,0,0,"nil",(DateEx) { 2000,1,1,0 },(DateEx) { 2000,1,1,0 } };
	BookEx* tpbookex = NewBookEx(tpbook);
	book_db->AddRecord(book_db, tpbookex);
	tpbookex->Regist(tpbookex, book_db->pManageItem);
	book_db->ResetSelection(book_db);

	//搜索
	book_db->SelectBy(book_db, "Title", "银河", LG_AND);

	//列出所有搜索到的结果
	slc = book_db->pSelection;
	while (slc != NULL) {
		printf("%s\n", slc->SelectedItem->Info.Title);
		slc = slc->Next;
	}

	/*
	BookEx* bk_tmp = book_db->pBookLink;
	while (bk_tmp != NULL) {
		printf("%s\n", bk_tmp->Info.Title);
		bk_tmp=bk_tmp->Next;
	}
	/*FILE* csv_doc;
	if ((csv_doc = fopen("tstdb.csv", "r")) == NULL) {
		Call_Error("CSV文件读取失败或文件不存在.");
		return; //Exit
	}
	//BKManage* temp_manage = malloc(sizeof(BKManage));
	int tp[6];
	char q=(char)fgetc(csv_doc);
	//fscanf(csv_doc, "%d",tp);*/
}