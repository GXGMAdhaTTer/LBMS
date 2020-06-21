#ifndef DB_ADMIN_H
#define DB_ADMIN_H

#include "DBStruct.h"

// ѡ���ṹ
// ѡ���ṹ��һ����BookExָ�빹�ɵ������Ա������ݿ������з������ļ�¼��ַ
typedef struct book_selection_item  BKSelect;
struct book_selection_item
{
	BookEx* SelectedItem; //ѡ������

	//���Ŷȣ������¼��ɸѡ�ؼ��ֵ����Ƴ̶ȣ������Ż������������
	//  ������and����ʱ��Ӧ�����ŶȽ�����ӣ�����not����ʱ�����or����ȡ���Ŷ����ֵ
	double Confidence;

	BKSelect* Previous;
	BKSelect* Next;
};

// �½�һ��ѡ���ṹ
BKSelect* NewBKSelect(BookEx* SelectedItem, double Confidence, BKSelect* Previous, BKSelect* Next);

// ���ݿ�ṹ��
typedef struct database_books_item  DB_Book;
struct database_books_item
{
	//����
	BKManage* pManageItem; //ָ�����ݿ�Ĺ���ṹ
	BookEx* pBookLink; //ָ�����ݿ����ݣ���Щ������BookEx�������
	BKSelect* pSelection; //ָ��ѡ��������ɸѡʱ����ѡ�񵽵�����

	//����
	//��д��
	void (*ReadFromFile)(DB_Book* This, //�Ӵ��̶�ȡ���ݿ�
		char* direction  //���ݿ��ļ���Ŀ¼
		);
	void (*WriteToFile)(DB_Book* This,  //�����д�����ݿ�
		char* direction
		);
	void (*AddRecord)(DB_Book* This, //���һ����¼
		BookEx* new_line  //�¼�¼��ָ�룬ʵ���Ͼ��ǰ��¼�¼��������ע�������¼һ��Ҫͨ��New�õ������Ǿ�̬��
		);
	void (*AlterRecord)(DB_Book* This, //�޸�һ����¼�����԰�����������ָ������Ҫ�޸ļ�¼��λ�ã�����������0ʱ����ָ������
		Book content, //Ҫ�ĳɵ����ݣ����޸ĵĶ����̳����е�Title/Author/Press/ISBNcode/PublicationDATE/KeyWord/Class�ֶ�
		int bookID, //���������ҵ�ֵ����0������ָ�����
		BookEx* exact_pointer  //��ָ����ҵ�ֵ��c����û��ȱʡemmm
		);

	//����
		/* �������ʹ��pSelection�����棬������Ϊ��ʱ�������������ݿ�����������������Ϣ������ѡ����
		 * ��������������������ʱ���ѡ����û�з��������ļ�¼������ʾ�û������ѡ����
		 * �����Ҫ�����ݿ���������������ǰ��ʹ��ResetSelection()
		 *
		 * �߼��ؼ��ֶ���������ṹ�����ĵط�: LG_AND(0), LG_OR(1), LG_NOT(2)
		 */
	void (*ResetSelection)(DB_Book* This); //����ѡ���Ա�����һ���������������ݿ⿪ʼ
	int (*SelectBy)(DB_Book* This, //�Ը���������ģ�������������������ļ�¼��(�����������ֶΣ�Title��Author��Keyword��Class)
		char* field, //Ҫ�������ֶ�
		char* content, //����������
		int logic_identifier //�߼���ʶ������ʾ�����������ݽ���������������/��/������
		);
	int (*SelectExact)(DB_Book* This, //�Ը��������ݾ�ȷ�����������������ļ�¼��
		char* field, //Ҫ�������ֶ�
		char* content, //����������
		int logic_identifier //�߼���ʶ������ʾ�����������ݽ���������������/��/������
		);
	void (*SelectAll)(DB_Book* This); //ѡ���������ݿ⣬���������ѡȡ�����Ŷ�Ϊ0
	void (*SoltSelection)(DB_Book* This); //�������Ŷ�����ѡ�������Ż��������

	//ת��ʽ
	void (*ImportFromCSV)(DB_Book* This, //��.csv�ļ�����
		char* direction);
	void (*ExportToCSV)(DB_Book* This, //����Ϊ.csv�ļ�
		char* direction);

	//����
	void (*Abandon)(DB_Book* This); //�������ݿ����(�������¶�ȡ�ļ�ʵ��ˢ�£��ᶪ�������Ѷ�ȡ�����޸ĵ�����)
	void (*Close)(DB_Book* This); //�ر����ݿ�
};
#define LG_AND 0
#define LG_OR  1
#define LG_NOT 2

// �Ӵ��̶�ȡ���ݿ⣬��Ӧvoid (*ReadFromFile)
void read_book_database(DB_Book* book_db, char* direction);
// �����д�����ݿ⣬��Ӧvoid (*WriteToFile)
void write_book_database(DB_Book* book_db, char* direction);
// ���һ����¼����Ӧvoid (*AddRecord)
void add_to_data(DB_Book* book_db, BookEx* new_line);
// �޸�һ����¼����Ӧvoid (*AlterRecord)
// ���԰�����������ָ������Ҫ�޸ļ�¼��λ�ã�����������0ʱ����ָ������
void alt_book_record(DB_Book* book_db, Book content, int bookID, BookEx* exact_pointer);
// ����ѡ������Ӧvoid (*ResetSelection)
void reset_book_selection(DB_Book* book_db);
// �Ը���������ģ����������Ӧvoid (*SelectBy)
// �����������ֶΣ�Title��Author��Keyword��Class �����߼�δ��ɡ�
int select_book_record(DB_Book* book_db, char* field, char* content, int logic_identifier);
	//������������õĻص�����
	char* get_author(Book* from_where);
	char* get_press(Book* from_where);
	char* get_keyword(Book* from_where);
	char* get_class(Book* from_where);
// �Ը��������ݾ�ȷ��������Ӧvoid (*SelectExact)  ��δ��ɡ�
int select_exact_book_record(DB_Book* book_db, char* field, char* content, int logic_identifier);
// ѡ���������ݿ⣬��Ӧvoid (*SelectAll)�����������ѡȡ�����Ŷ�Ϊ0
void select_all_book_db(DB_Book* book_db);
//�������Ŷ�����ѡ������Ӧvoid (*SoltSelection)
void solt_selection_with_confidence(DB_Book* book_db);
	// ����鲢����
	// ���������BKSelect�������ŶȴӴ�С����
	BKSelect* MergeSoltSelection(BKSelect* link);
// ��.csv�ļ����룬��Ӧvoid (*ImportFromCSV)
void import_bookdb_from_CSV(DB_Book* book_db, char* direction);
// ����Ϊ.csv�ļ�����Ӧvoid (*ExportToCSV)  ��δ��ɡ�
void export_bookdb_to_CSV(DB_Book* This, char* direction);
// �������ݿ���󣬶�Ӧvoid (*Abandon)
void abandon_book_db(DB_Book* book_db);
// �ر����ݿ⣬��Ӧvoid (*Close)
void close_book_db(DB_Book* book_db);

// �½�һ�����ݿ�ṹ
DB_Book* NewDBBook();

#endif