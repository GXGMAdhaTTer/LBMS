#ifndef DB_ADMIN_H
#define DB_ADMIN_H

#include "DBStruct.h"

// 选区结构
// 选区结构是一张由BookEx指针构成的链表，以便在数据库链表中非连续的记录地址
typedef struct book_selection_item  BKSelect;
struct book_selection_item
{
	BookEx* SelectedItem; //选区内容

	//置信度：这个记录与筛选关键字的相似程度，用来优化搜索结果排序
	//  当进行and运算时，应对置信度进行相加；进行not运算时相减；or运算取置信度最大值
	double Confidence;

	BKSelect* Previous;
	BKSelect* Next;
};

// 新建一个选区结构
BKSelect* NewBKSelect(BookEx* SelectedItem, double Confidence, BKSelect* Previous, BKSelect* Next);

// 数据库结构体
typedef struct database_books_item  DB_Book;
struct database_books_item
{
	//数据
	BKManage* pManageItem; //指向数据库的管理结构
	BookEx* pBookLink; //指向数据库内容，这些内容以BookEx链表存在
	BKSelect* pSelection; //指向选区链表，在筛选时储存选择到的内容

	//方法
	//读写改
	void (*ReadFromFile)(DB_Book* This, //从磁盘读取数据库
		char* direction  //数据库文件的目录
		);
	void (*WriteToFile)(DB_Book* This,  //向磁盘写入数据库
		char* direction
		);
	void (*AddRecord)(DB_Book* This, //添加一条记录
		BookEx* new_line  //新记录的指针，实际上就是把新记录接上链表，注意这个记录一定要通过New得到或者是静态的
		);
	void (*AlterRecord)(DB_Book* This, //修改一条记录，可以按照主键或者指针搜索要修改记录的位置，当主键输入0时采用指针搜索
		Book content, //要改成的内容，被修改的对象会继承其中的Title/Author/Press/ISBNcode/PublicationDATE/KeyWord/Class字段
		int bookID, //按主键查找的值，填0将采用指针查找
		BookEx* exact_pointer  //按指针查找的值，c语言没法缺省emmm
		);

	//搜索
		/* 搜索结果使用pSelection链表储存，当链表为空时，将从整个数据库搜索，当链表有信息，将在选区内
		 * 搜索（二次搜索），此时如果选区内没有符合条件的记录，将提示用户并清空选区。
		 * 如果需要从数据库搜索，请在搜索前先使用ResetSelection()
		 *
		 * 逻辑关键字定义在这个结构结束的地方: LG_AND(0), LG_OR(1), LG_NOT(2)
		 */
	void (*ResetSelection)(DB_Book* This); //重置选区以便让下一次搜索从整个数据库开始
	int (*SelectBy)(DB_Book* This, //以给定的数据模糊搜索，返回搜索到的记录数(可以搜索的字段：Title，Author，Keyword，Class)
		char* field, //要搜索的字段
		char* content, //搜索的内容
		int logic_identifier //逻辑标识符，表示搜索到的数据将与现有数据做并/交/补运算
		);
	int (*SelectExact)(DB_Book* This, //以给定的数据精确搜索，返回搜索到的记录数
		char* field, //要搜索的字段
		char* content, //搜索的内容
		int logic_identifier //逻辑标识符，表示搜索到的数据将与现有数据做并/交/补运算
		);
	void (*SelectAll)(DB_Book* This); //选择整个数据库，用这个方法选取的置信度为0
	void (*SoltSelection)(DB_Book* This); //按照置信度排序选区，来优化搜索结果

	//转格式
	void (*ImportFromCSV)(DB_Book* This, //从.csv文件导入
		char* direction);
	void (*ExportToCSV)(DB_Book* This, //导出为.csv文件
		char* direction);

	//其他
	void (*Abandon)(DB_Book* This); //重置数据库对象(用来重新读取文件实现刷新，会丢弃所有已读取和已修改的数据)
	void (*Close)(DB_Book* This); //关闭数据库
};
#define LG_AND 0
#define LG_OR  1
#define LG_NOT 2

// 从磁盘读取数据库，对应void (*ReadFromFile)
void read_book_database(DB_Book* book_db, char* direction);
// 向磁盘写入数据库，对应void (*WriteToFile)
void write_book_database(DB_Book* book_db, char* direction);
// 添加一条记录，对应void (*AddRecord)
void add_to_data(DB_Book* book_db, BookEx* new_line);
// 修改一条记录，对应void (*AlterRecord)
// 可以按照主键或者指针搜索要修改记录的位置，当主键输入0时采用指针搜索
void alt_book_record(DB_Book* book_db, Book content, int bookID, BookEx* exact_pointer);
// 重置选区，对应void (*ResetSelection)
void reset_book_selection(DB_Book* book_db);
// 以给定的数据模糊搜索，对应void (*SelectBy)
// 可以搜索的字段：Title，Author，Keyword，Class 【或逻辑未完成】
int select_book_record(DB_Book* book_db, char* field, char* content, int logic_identifier);
	//上面这个函数用的回调函数
	char* get_author(Book* from_where);
	char* get_press(Book* from_where);
	char* get_keyword(Book* from_where);
	char* get_class(Book* from_where);
// 以给定的数据精确搜索，对应void (*SelectExact)  【未完成】
int select_exact_book_record(DB_Book* book_db, char* field, char* content, int logic_identifier);
// 选择整个数据库，对应void (*SelectAll)，用这个方法选取的置信度为0
void select_all_book_db(DB_Book* book_db);
//按照置信度排序选区，对应void (*SoltSelection)
void solt_selection_with_confidence(DB_Book* book_db);
	// 链表归并排序
	// 这个函数对BKSelect链表按置信度从大到小排序
	BKSelect* MergeSoltSelection(BKSelect* link);
// 从.csv文件导入，对应void (*ImportFromCSV)
void import_bookdb_from_CSV(DB_Book* book_db, char* direction);
// 导出为.csv文件，对应void (*ExportToCSV)  【未完成】
void export_bookdb_to_CSV(DB_Book* This, char* direction);
// 重置数据库对象，对应void (*Abandon)
void abandon_book_db(DB_Book* book_db);
// 关闭数据库，对应void (*Close)
void close_book_db(DB_Book* book_db);

// 新建一个数据库结构
DB_Book* NewDBBook();

#endif