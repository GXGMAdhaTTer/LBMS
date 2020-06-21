#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <Windows.h>

#include "DBGeneral.h"
#include "DBStruct.h"

#include "DBCsv.h"

/* ----- DB_Csv ----- */
/* ----- ver 0.0.1 ----- */

/*  <介绍>
 *  Csv文件处理模块
 *  负责处理.csv文件，
 *  将字节数据库(.bitDB)转化为.csv或反向转化
 */

// 从文件中读取字符串，到",","\0","\n","\t",EOF结束（会读走结束的逗号，并给字符串加上0结尾）
void fgetCommaEndString(FILE* from_file, char* buffer) {
    int temp; //fgetc返回给int时才能获得EOF
    temp = fgetc(from_file);
    while (temp != ',' && temp != '\n' && temp != '\t' && temp != 0 && temp != EOF) {
        *buffer = (char)temp;
        buffer++;
        temp = fgetc(from_file);
    }
    *(buffer) = 0;
}

// 把Y/M/D格式的字符串转化为日期
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
    //检查错误
    if (year > 4095 || month > 12 || day > 31) {
        Call_Error("不正确的日期格式.");
        return (DateEx) { 0, 0, 0, 0 };
    }
    return (DateEx) { year, month, day, 0 };
}

// 把字符串转化为int
// 为了程序稳定性，少用fscanf
int TranslateToInt(char* from_str) {
    int temp; temp = 0;
    while (*from_str != 0) {
        temp *= 10;
        temp += (*from_str - '0');
        from_str++;
    }
    return temp;
}

// 将csv转bitDB
void TransformToBDB(char* from_where, char* to_where) {
    FILE* csv_doc, * bdb_doc; //要读取的csv，要写的bdb
    if ((csv_doc = fopen(from_where, "r")) == NULL) { //赋值优先级小于恒等号，记得加括号
        Call_Error("CSV文件读取失败或文件不存在.");
        return; //Exit
    }
    if ((bdb_doc = fopen(to_where, "wb")) == NULL) {
        Call_Error("未能创建二进制数据库文件.");
        return; //Exit
    }
    //转化管理部分
    BKManage* temp_manage = malloc(sizeof(BKManage));
    if (fscanf(csv_doc, "%d,%d,%d,%d,%d,%d\n",
            &(temp_manage->BooksStored),
            &(temp_manage->BookBorrowed),
            &(temp_manage->BookReserved),
            &(temp_manage->LastBookID),
            &(temp_manage->TotalBookBorrowed),
            &(temp_manage->TotalBookReserved))
        == EOF) {
        Call_Error("读取头部异常.");
        free(temp_manage);
        fclose(csv_doc);
        fclose(bdb_doc);
        return; //Exit
    }
    if (fwrite(temp_manage, sizeof(BKManage), 1, bdb_doc) != 1) {
        Call_Error("写入头部异常.");
        free(temp_manage);
        fclose(csv_doc);
        fclose(bdb_doc);
        return; //Exit
    }
    free(temp_manage);
    //转化数据
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
        if (bitint > 3) { Call_Error("借阅状态不正常."); bitint = 0; }
        temp_book->Status = bitint;
        fgetCommaEndString(csv_doc, &(temp_book->UserID));
        fgetCommaEndString(csv_doc, buffer); temp_book->BorrowDATE = TranslateToDate(buffer);
        fgetCommaEndString(csv_doc, buffer); temp_book->ReturnDATE = TranslateToDate(buffer);

        if (fwrite(temp_book, sizeof(Book), 1, bdb_doc) != 1) {
            Call_Error("写入记录异常.");
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