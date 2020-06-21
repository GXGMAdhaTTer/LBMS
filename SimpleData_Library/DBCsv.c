#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <Windows.h>

#include "DBGeneral.h"
#include "DBStruct.h"

#include "DBCsv.h"

/* ----- DB_Csv ----- */
/* ----- ver 0.0.1 ----- */

/*  <����>
 *  Csv�ļ�����ģ��
 *  ������.csv�ļ���
 *  ���ֽ����ݿ�(.bitDB)ת��Ϊ.csv����ת��
 */

// ���ļ��ж�ȡ�ַ�������",","\0","\n","\t",EOF����������߽����Ķ��ţ������ַ�������0��β��
void fgetCommaEndString(FILE* from_file, char* buffer) {
    int temp; //fgetc���ظ�intʱ���ܻ��EOF
    temp = fgetc(from_file);
    while (temp != ',' && temp != '\n' && temp != '\t' && temp != 0 && temp != EOF) {
        *buffer = (char)temp;
        buffer++;
        temp = fgetc(from_file);
    }
    *(buffer) = 0;
}

// ��Y/M/D��ʽ���ַ���ת��Ϊ����
DateEx TranslateToDate(char* from_str) {
    unsigned int year, month, day;
    year = month = day = 0;
    while (*from_str != '/') {
        year = year * 10 + (*from_str - '0');
        from_str++;
    }
    from_str++;
    while (*from_str != '/') {
        month = month * 10 + (*from_str - '0');
        from_str++;
    }
    from_str++;
    while (*from_str != 0) {
        day = day * 10 + (*from_str - '0');
        from_str++;
    }
    //������
    if (year > 4095 || month > 12 || day > 31) {
        Call_Error("����ȷ�����ڸ�ʽ.");
        return (DateEx) { 0, 0, 0, 0 };
    }
    return (DateEx) { year, month, day, 0 };
}

// ���ַ���ת��Ϊint
// Ϊ�˳����ȶ��ԣ�����fscanf
int TranslateToInt(char* from_str) {
    int temp; temp = 0;
    while (*from_str != 0) {
        temp *= 10;
        temp += (*from_str - '0');
        from_str++;
    }
    return temp;
}

// ��csvתbitDB
void TransformToBDB(char* from_where, char* to_where) {
    FILE* csv_doc, * bdb_doc; //Ҫ��ȡ��csv��Ҫд��bdb
    if ((csv_doc = fopen(from_where, "r")) == NULL) { //��ֵ���ȼ�С�ں�Ⱥţ��ǵü�����
        Call_Error("CSV�ļ���ȡʧ�ܻ��ļ�������.");
        return; //Exit
    }
    if ((bdb_doc = fopen(to_where, "wb")) == NULL) {
        Call_Error("δ�ܴ������������ݿ��ļ�.");
        return; //Exit
    }
    //ת��������
    BKManage* temp_manage = malloc(sizeof(BKManage));
    if (fscanf(csv_doc, "%d,%d,%d,%d,%d,%d\n",
            &(temp_manage->BooksStored),
            &(temp_manage->BookBorrowed),
            &(temp_manage->BookReserved),
            &(temp_manage->LastBookID),
            &(temp_manage->TotalBookBorrowed),
            &(temp_manage->TotalBookReserved))
        == EOF) {
        Call_Error("��ȡͷ���쳣.");
        free(temp_manage);
        fclose(csv_doc);
        fclose(bdb_doc);
        return; //Exit
    }
    if (fwrite(temp_manage, sizeof(BKManage), 1, bdb_doc) != 1) {
        Call_Error("д��ͷ���쳣.");
        free(temp_manage);
        fclose(csv_doc);
        fclose(bdb_doc);
        return; //Exit
    }
    free(temp_manage);
    //ת������
    Book* temp_book; temp_book = malloc(sizeof(Book));
    char buffer[48]; unsigned int bitint;
    while (feof(csv_doc) == 0) {
        fgetCommaEndString(csv_doc, &(temp_book->Title));
        fgetCommaEndString(csv_doc, &(temp_book->Author));
        fgetCommaEndString(csv_doc, &(temp_book->Press));
        fgetCommaEndString(csv_doc, &(temp_book->ISBNcode));
        fgetCommaEndString(csv_doc, buffer); temp_book->PublicationDATE = TranslateToDate(buffer);
        fgetCommaEndString(csv_doc, &(temp_book->KeyWord));
        fgetCommaEndString(csv_doc, &(temp_book->Class));
        fgetCommaEndString(csv_doc, buffer); temp_book->Stars = TranslateToInt(buffer);
        fgetCommaEndString(csv_doc, buffer); temp_book->TotalBorrow = TranslateToInt(buffer);
        fgetCommaEndString(csv_doc, buffer); temp_book->BookID = TranslateToInt(buffer);
        fgetCommaEndString(csv_doc, buffer); bitint = TranslateToInt(buffer);
        if (bitint > 3) { Call_Error("����״̬������."); bitint = 0; }
        temp_book->Status = bitint;
        fgetCommaEndString(csv_doc, &(temp_book->UserID));
        fgetCommaEndString(csv_doc, buffer); temp_book->BorrowDATE = TranslateToDate(buffer);
        fgetCommaEndString(csv_doc, buffer); temp_book->ReturnDATE = TranslateToDate(buffer);

        if (fwrite(temp_book, sizeof(Book), 1, bdb_doc) != 1) {
            Call_Error("д���¼�쳣.");
            free(temp_book);
            fclose(csv_doc);
            fclose(bdb_doc);
            return; //Exit
        }
    }
    fclose(csv_doc);
    fclose(bdb_doc);
    free(temp_book);
}