#define _CRT_SECURE_NO_WARNINGS

/*  ��Ҫ����   */

#include <stdlib.h>
#include <stdio.h>

#include "DBAdmin.h"

//#include "DBStruct.h"
//#include "DBGeneral.h"
//#include "DBCsv.h"

/* ------ �������� ------ */


int main() {
	//Call_Error("��������");
	DB_Book* book_db = NewDBBook();
	//TransformToBDB("tstdb.csv", "tstdb.bdb");
	//book_db->ImportFromCSV(book_db, "tstdb.csv");
	//book_db->WriteToFile(book_db, "tstdb.bdb");
	//book_db->Abandon(book_db);
	book_db->ReadFromFile(book_db, "tstdb.bdb");

	book_db->SelectBy(book_db, "Title", "����", LG_AND);
	BKSelect* slc;
	slc = book_db->pSelection;
	while (slc != NULL) {
		printf("%s\n", slc->SelectedItem->Info.Title);
		slc = slc->Next;
	}
	Book tpbook = (Book){ "���ӵ۹�","[��]����Ī��","UndefPress","ISBN0000",
		(DateEx) {2010,11,2,0},"�ִ�/�ƻ�","�����ѧ/�ƻ�С˵",
		0,0,0,0,"nil",(DateEx) { 2000,1,1,0 },(DateEx) { 2000,1,1,0 } };
	BookEx* tpbookex = NewBookEx(tpbook);
	book_db->AddRecord(book_db, tpbookex);
	tpbookex->Regist(tpbookex, book_db->pManageItem);
	book_db->ResetSelection(book_db);

	//����
	book_db->SelectBy(book_db, "Title", "����", LG_AND);

	//�г������������Ľ��
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
		Call_Error("CSV�ļ���ȡʧ�ܻ��ļ�������.");
		return; //Exit
	}
	//BKManage* temp_manage = malloc(sizeof(BKManage));
	int tp[6];
	char q=(char)fgetc(csv_doc);
	//fscanf(csv_doc, "%d",tp);*/
}