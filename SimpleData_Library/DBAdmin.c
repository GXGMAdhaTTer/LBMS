#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "DBGeneral.h"
#include "DBStruct.h"
#include "DBSearch.h"
#include "DBCsv.h"

#include "DBAdmin.h"

/* ----- DB_Admin ----- */
/* ----- ver 0.0.1 ----- */

/*  <介绍>
 *  数据库管理模块
 *  定义了数据库结构并进行封装，
 *  实现从外部读取数据/向外部写数据
 *  以及数据库搜索功能
 */

// 定义在搜索时被认为相关的最小所需置信度
#define LOWEST_CON 0.58


/* -- 数据库结构 -- */

	// 定义选区结构

		// 选区结构
		// 选区结构是一张由BookEx指针构成的链表，以便在数据库链表中非连续的记录地址
		/*typedef struct book_selection_item  BKSelect;
		struct book_selection_item
		{
			BookEx* SelectedItem; //选区内容

			//置信度：这个记录与筛选关键字的相似程度，用来优化搜索结果排序
			//  当进行and运算时，应对置信度进行相加；进行not运算时相减；or运算取置信度最大值
			double Confidence; 

			BKSelect* Previous;
			BKSelect* Next;
		};*/

		// 新建一个选区结构
		BKSelect* NewBKSelect(
			BookEx* SelectedItem,
			double Confidence,
			BKSelect* Previous,
			BKSelect* Next
		) {
			BKSelect* temp = malloc(sizeof(BKSelect));
			temp->SelectedItem = SelectedItem;
			temp->Confidence = Confidence;
			temp->Previous = Previous;
			temp->Next = Next;
			return temp;
		}


	// 定义数据库结构
	
		/* 
		 * 将整个读取到的数据库文件视为一个整体，
		 * 把上面定义的各种结构塞进去封装成伪oop
		 */

		// 数据库结构体
		/*typedef struct database_books_item  DB_Book;
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
				// 搜索结果使用pSelection链表储存，当链表为空时，将从整个数据库搜索，当链表有信息，将在选区内
				// 搜索（二次搜索），此时如果选区内没有符合条件的记录，将提示用户并清空选区。
				// 如果需要从数据库搜索，请在搜索前先使用ResetSelection()
				//
				// 逻辑关键字定义在这个结构结束的地方: LG_AND(0), LG_OR(1), LG_NOT(2)

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
		#define LG_NOT 2 */

		// 方法
		// 内置部分
			// 从磁盘读取数据库，对应void (*ReadFromFile)
			void read_book_database(DB_Book* book_db, 
				const char* direction
			){
				FILE* p_file;
				if ((p_file = fopen(direction, "rb")) == NULL) {
					Call_Error("书籍数据库读取失败或文件不存在.");
					if (fclose(p_file))
						Call_Error("文件没有正常关闭.");
					return; //Exit
				}

				//读取文件头
				book_db->pManageItem = (BKManage*) malloc(sizeof(BKManage)); //申请空间
				//若没有读取出管理结构的信息 
				if (fread(book_db->pManageItem, sizeof(BKManage), 1, p_file) != 1) {
					Call_Error("找不到数据库信息，请检查这是否是一个有效的库.");
					if (fclose(p_file))
						Call_Error("文件没有正常关闭.");
					return; //Exit
				}
				//若读出的管理信息数据异常，可能该数据库没有写入管理结构
				if (BKM_CheckIntegrity(book_db->pManageItem)) {
					Call_Warning("数据库头异常，尝试跳过头部.");
					rewind(p_file); //文件指针回到文件开始				
				}

				//读取内容
				const int size_of_book = sizeof(Book);
				Book temp_book;  //工具人
				BookEx *temp_link, *temp_prev;  //工具人
				//读取第一条记录，如果失败证明数据库为空
				if (fread(&temp_book, size_of_book, 1, p_file) != 1) {
					Call_Warning("数据库为空.");
					book_db->pBookLink = NULL;
					if (fclose(p_file))
						Call_Error("文件没有正常关闭.");
					return;
				}
				book_db->pBookLink = temp_prev = NewBookEx(temp_book);  //数据库结构中的数据指针指向表头
				//因为一次读取一块，只要读取块数为1就代表读取成功
				while (fread(&temp_book, size_of_book, 1, p_file) == 1) {
					//把读取到的数据接入链表
					temp_link = NewBookEx(temp_book);
					temp_link->Previous = temp_prev;
					temp_link->Next = NULL;
					temp_prev->Next = temp_link;
					temp_prev = temp_link;
				}
				//退出时判断是否为正常退出
				if (feof(p_file) != 0) {
					if (ferror(p_file) != 0)
						Call_Error("读取异常中断.");						
					/*else
						Call_Warning("存在多余数据.");*/
					//因为每次都有多余数据的报错所以干脆不报了
				}

				//关闭文件
				if (fclose(p_file))
					Call_Error("文件没有正常关闭.");
			}

			// 向磁盘写入数据库，对应void (*WriteToFile)
			void write_book_database(DB_Book* book_db,
				char* direction
			){
				FILE* p_file;
				if ((p_file = fopen(direction, "wb")) == NULL) {
					Call_Error("未能创建数据库文件.");
					if (fclose(p_file))
						Call_Error("文件没有正常关闭.");
					return; //Exit
				}

				//写文件头
				if (fwrite(book_db->pManageItem, sizeof(BKManage), 1, p_file) != 1) {
					Call_Error("写入异常，跳过文件头部.");
					rewind(p_file); //指针回头部
				}

				//写数据
				if (book_db->pBookLink == NULL)
					Call_Warning("数据库为空."); //当链表指针没有内容时
				else {
					const int size_of_book = sizeof(Book);
					Book* temp_info;
					BookEx* temp_ex; //工具人
					temp_ex = book_db->pBookLink;
					//循环写入
					while (temp_ex != NULL){
						temp_info = &(temp_ex->Info);
						if (fwrite(temp_info, size_of_book, 1, p_file) != 1)
							Call_Error("写入异常.");
						temp_ex = temp_ex->Next;
					}
				}
				if (fclose(p_file))
					Call_Error("文件没有正常关闭.");
			}

			// 添加一条记录，对应void (*AddRecord)
			void add_to_data(DB_Book* book_db,
				BookEx* new_line
			){
				//接上链表就好了
				BookEx* temp; 
				temp = GoToEnd(book_db->pBookLink);
				temp->Next = new_line;
				new_line->Previous = temp;
				//最后把链表尾封上
				new_line->Next = NULL;
				//注册
				(*new_line).Regist(new_line, book_db->pManageItem);
			}

			// 修改一条记录，对应void (*AlterRecord)
			// 可以按照主键或者指针搜索要修改记录的位置，当主键输入0时采用指针搜索
			void alt_book_record(DB_Book* book_db,
				Book content,
				int bookID,
				BookEx* exact_pointer
			) {
					//c居然不能缺省，我******
				//空库的情况
				if (book_db->pBookLink == NULL) {
					Call_Warning("不能搜索空的数据库.");
					return;
				}
				//按主键查找的情况
				if (bookID != 0) {
					BookEx* temp;
					temp = GoToHead(book_db->pBookLink);
					//因为数据库是固定按主键从小到大排序的链表，所以从头开始O(n)
					while (temp->Info.BookID < bookID)
					{
						if (temp->Next != NULL)
							temp = temp->Next;
						else {
							Call_Promote("没有找到相应的记录.");
							return;
						}
					}
					//如果跳出循环
					if (temp->Info.BookID == bookID) {
						//找到时
						//继承Title/Author/Press/ISBNcode/PublicationDATE/KeyWord/Class字段
						strcpy(temp->Info.Title, content.Title);
						strcpy(temp->Info.Author, content.Author);
						strcpy(temp->Info.Press, content.Press);
						strcpy(temp->Info.ISBNcode, content.ISBNcode);
						temp->Info.PublicationDATE = content.PublicationDATE;
						strcpy(temp->Info.KeyWord, content.KeyWord);
						strcpy(temp->Info.Class, content.Class);
							//因为只继承部分，只能逐个赋值XD
						return;
					}
					else {
						Call_Promote("没有找到相应的记录.");
						return;
					}
				 }
				//按指针不用查找的情况
				else {
					strcpy(exact_pointer->Info.Title, content.Title);
					strcpy(exact_pointer->Info.Author, content.Author);
					strcpy(exact_pointer->Info.Press, content.Press);
					strcpy(exact_pointer->Info.ISBNcode, content.ISBNcode);
					exact_pointer->Info.PublicationDATE = content.PublicationDATE;
					strcpy(exact_pointer->Info.KeyWord, content.KeyWord);
					strcpy(exact_pointer->Info.Class, content.Class);
				}
			}			

			// 重置选区，对应void (*ResetSelection)
			void reset_book_selection(DB_Book* book_db) {
				if (book_db->pSelection != NULL) {
					BKSelect* previous, * here;
					here = book_db->pSelection;
					while (here != NULL) {
						previous = here;
						here = here->Next;
						free(previous);
					}
				}
				book_db->pSelection = NULL;
			}

			// 以给定的数据模糊搜索，对应void (*SelectBy)
			// 可以搜索的字段：Title，Author，Keyword，Class 【或逻辑未完成】
			int select_book_record(DB_Book* book_db,
				char* field, char* content,
				int logic_identifier
			) {
				if (book_db->pBookLink == NULL) {
					Call_Promote("数据库为空.");
					return 0;
				}
				int selected_count = 0; //记录选取到数据的数量
				if (strcmp(field, "Title") == 0) { //按标题搜索【模糊搜索】
					switch (logic_identifier) {
					case LG_AND:
						if (book_db->pSelection == NULL) { //空选区，从数据库选择
							BookEx* db_cursor = GoToHead(book_db->pBookLink); //数据库记录指针
							BKSelect* temp_rec; //暂存新选区的指针
							BKSelect* prev_rec = NULL; //暂存上一个选区的指针
							double conv; //置信度
							//枚举数据库
							while (db_cursor != NULL) {
								conv = Similarity(content, db_cursor->Info.Title);
								if (conv > LOWEST_CON) {
									selected_count++;
									temp_rec = NewBKSelect(db_cursor, conv, prev_rec, NULL); //写一个反向链表（只有previous，而next为空）
									prev_rec = temp_rec;
								}
								db_cursor = db_cursor->Next; //移动到下一条记录
							}
							//检索完成后，回溯链表写入next参数，并得到链表头
							if (prev_rec == NULL) { //没有选到数据
								Call_Promote("没有符合条件的记录.");
								return 0;
							}
							temp_rec = prev_rec;
							prev_rec = prev_rec->Previous;
							while (prev_rec != NULL) {
								prev_rec->Next = temp_rec;
								temp_rec = prev_rec;
								prev_rec = prev_rec->Previous;
							}
							//写入数据库的pSelection
							book_db->pSelection = temp_rec;
							return selected_count;
						}
						else { //有选区，从选区选择
							BKSelect* slc_cursor = book_db->pSelection; //选区记录指针
							BKSelect* temp; //暂存指针
							double conv; //置信度
							//处理除了最后一条的数据
							while (slc_cursor->Next != NULL) {
								conv = Similarity(content, slc_cursor->SelectedItem->Info.Title);
								selected_count++;
								if (conv < LOWEST_CON) { //如果相似度不足，则从选区中删除这条记录
									selected_count--;
									if (slc_cursor->Previous != NULL)
										slc_cursor->Previous->Next = slc_cursor->Next;
									if (slc_cursor->Next != NULL)
										slc_cursor->Next->Previous = slc_cursor->Previous;
									temp = slc_cursor;
									slc_cursor = slc_cursor->Next;
									free(temp);
								}
								else {
									slc_cursor->Confidence += conv; //在与运算中，置信度求和
									slc_cursor = slc_cursor->Next; //移动到下一条记录
								}
							}
							//特别处理最后一条记录避免重复判断指针为NULL的情况
							conv = Similarity(content, slc_cursor->SelectedItem->Info.Title);
							selected_count++;
							if (conv < LOWEST_CON) { //如果相似度不足，则从选区中删除这条记录
								selected_count--;
								if (slc_cursor->Previous != NULL) {
									slc_cursor->Previous->Next = NULL;
									temp = slc_cursor;
									slc_cursor = slc_cursor->Previous;
									free(temp);
								}
								else { //前后都为NULL，返回选区为空
									free(slc_cursor);
									book_db->pSelection = NULL;
									Call_Promote("没有符合条件的记录.");
									return 0; //弹出
								}
							}
							else
								slc_cursor->Confidence += conv; //在与运算中，置信度求和
							//检索完成后，回溯到链表头，填写book_db
							while (slc_cursor->Previous != NULL)
								slc_cursor = slc_cursor->Previous;
							book_db->pSelection = slc_cursor;//写入数据库的pSelection
							return selected_count;
						}
					case LG_NOT:
						if (book_db->pSelection == NULL) { //空选区，从数据库选择
							BookEx* db_cursor = GoToHead(book_db->pBookLink); //数据库记录指针
							BKSelect* temp_rec; //暂存新选区的指针
							BKSelect* prev_rec = NULL; //暂存上一个选区的指针
							double conv; //置信度
							//枚举数据库
							while (db_cursor != NULL) {
								conv = Similarity(content, db_cursor->Info.Title);
								if (conv < LOWEST_CON) { //非逻辑，取不符合的即可
									selected_count++;
									temp_rec = NewBKSelect(db_cursor, -1 * conv, prev_rec, NULL); //写一个反向链表（只有previous，而next为空）
									prev_rec = temp_rec;
								}
								db_cursor = db_cursor->Next; //移动到下一条记录
							}
							//检索完成后，回溯链表写入next参数，并得到链表头
							if (prev_rec == NULL) { //没有选到数据
								Call_Promote("没有符合条件的记录.");
								return 0;
							}
							temp_rec = prev_rec;
							prev_rec = prev_rec->Previous;
							while (prev_rec != NULL) {
								prev_rec->Next = temp_rec;
								temp_rec = prev_rec;
								prev_rec = prev_rec->Previous;
							}
							//写入数据库的pSelection
							book_db->pSelection = temp_rec;
							return selected_count;
						}
						else { //有选区，从选区选择
							BKSelect* slc_cursor = book_db->pSelection; //选区记录指针
							BKSelect* temp; //暂存指针
							double conv; //置信度
							//处理除了最后一条的数据
							while (slc_cursor->Next != NULL) {
								conv = Similarity(content, slc_cursor->SelectedItem->Info.Title);
								selected_count++;
								if (conv > LOWEST_CON) { //如果相似度满足，则从选区中删除这条记录
									selected_count--;
									if (slc_cursor->Previous != NULL)
										slc_cursor->Previous->Next = slc_cursor->Next;
									if (slc_cursor->Next != NULL)
										slc_cursor->Next->Previous = slc_cursor->Previous;
									temp = slc_cursor;
									slc_cursor = slc_cursor->Next;
									free(temp);
								}
								else {
									slc_cursor->Confidence -= conv; //在非运算中，置信度求差
									slc_cursor = slc_cursor->Next; //移动到下一条记录
								}
							}
							//特别处理最后一条记录避免重复判断指针为NULL的情况
							conv = Similarity(content, slc_cursor->SelectedItem->Info.Title);
							selected_count++;
							if (conv > LOWEST_CON) { //如果相似度满足，则从选区中删除这条记录
								selected_count--;
								if (slc_cursor->Previous != NULL) {
									slc_cursor->Previous->Next = NULL;
									temp = slc_cursor;
									slc_cursor = slc_cursor->Previous;
									free(temp);
								}
								else { //前后都为NULL，返回选区为空
									free(slc_cursor);
									book_db->pSelection = NULL;
									Call_Promote("没有符合条件的记录.");
									return 0; //弹出
								}
							}
							else
								slc_cursor->Confidence -= conv; //在非运算中，置信度求差
							//检索完成后，回溯到链表头，填写book_db
							while (slc_cursor->Previous != NULL)
								slc_cursor = slc_cursor->Previous;
							book_db->pSelection = slc_cursor;//写入数据库的pSelection
							return selected_count;
						}
					case LG_OR:
						Call_Promote("未实现的功能.");
						return 0;
					default:
						Call_Warning("不正确的逻辑表达式.");
						return 0;
					}				
				}
				else { //按作者/出版社/关键词/分类搜索【精确搜索】
					char* (*get_info)(Book* from_where); //获取需要信息的回调函数
					//根据不同情况赋值回调函数
					if (strcmp(field, "Author") == 0)
						get_info = get_author;
					else if (strcmp(field, "Press") == 0)
						get_info = get_press;
					else if (strcmp(field, "Keyword") == 0)
						get_info = get_keyword;
					else if (strcmp(field, "Class") == 0)
						get_info = get_class;
					else {
						Call_Warning("不正确的字段名.");
						return 0;
					}
					//精确搜索，方法同上
					switch (logic_identifier) {
					case LG_AND:
						if (book_db->pSelection == NULL) { //空选区，从数据库选择
							BookEx* db_cursor = GoToHead(book_db->pBookLink); //数据库记录指针
							BKSelect* temp_rec; //暂存新选区的指针
							BKSelect* prev_rec = NULL; //暂存上一个选区的指针
							int conv; //置信度，精确搜索时置信度只有0和1
							//枚举数据库
							while (db_cursor != NULL) {
								conv = IfSubset(content, get_info(&(db_cursor->Info))); //判断子串关系
								if (conv == 1) {
									selected_count++;
									temp_rec = NewBKSelect(db_cursor, (double)conv, prev_rec, NULL); //写一个反向链表（只有previous，而next为空）
									prev_rec = temp_rec;
								}
								db_cursor = db_cursor->Next; //移动到下一条记录
							}
							//检索完成后，回溯链表写入next参数，并得到链表头
							if (prev_rec == NULL) { //没有选到数据
								Call_Promote("没有符合条件的记录.");
								return 0;
							}
							temp_rec = prev_rec;
							prev_rec = prev_rec->Previous;
							while (prev_rec != NULL) {
								prev_rec->Next = temp_rec;
								temp_rec = prev_rec;
								prev_rec = prev_rec->Previous;
							}
							//写入数据库的pSelection
							book_db->pSelection = temp_rec;
							return selected_count;
						}
						else { //有选区，从选区选择
							BKSelect* slc_cursor = book_db->pSelection; //选区记录指针
							BKSelect* temp; //暂存指针
							int conv; //置信度，精确搜索时置信度只有0和1
							//处理除了最后一条的数据
							while (slc_cursor->Next != NULL) {
								conv = IfSubset(content, get_info(&(slc_cursor->SelectedItem->Info)));
								selected_count++;
								if (conv == 0) { //如果相似度不足，则从选区中删除这条记录
									selected_count--;
									if (slc_cursor->Previous != NULL)
										slc_cursor->Previous->Next = slc_cursor->Next;
									if (slc_cursor->Next != NULL)
										slc_cursor->Next->Previous = slc_cursor->Previous;
									temp = slc_cursor;
									slc_cursor = slc_cursor->Next;
									free(temp);
								}
								else {
									slc_cursor->Confidence += (double)conv; //在与运算中，置信度求和
									slc_cursor = slc_cursor->Next; //移动到下一条记录
								}
							}
							//特别处理最后一条记录避免重复判断指针为NULL的情况
							conv = IfSubset(content, get_info(&(slc_cursor->SelectedItem->Info)));
							selected_count++;
							if (conv == 0) { //如果相似度不足，则从选区中删除这条记录
								selected_count--;
								if (slc_cursor->Previous != NULL) {
									slc_cursor->Previous->Next = NULL;
									temp = slc_cursor;
									slc_cursor = slc_cursor->Previous;
									free(temp);
								}
								else { //前后都为NULL，返回选区为空
									free(slc_cursor);
									book_db->pSelection = NULL;
									Call_Promote("没有符合条件的记录.");
									return 0; //弹出
								}
							}
							else
								slc_cursor->Confidence += (double)conv; //在与运算中，置信度求和
							//检索完成后，回溯到链表头，填写book_db
							while (slc_cursor->Previous != NULL)
								slc_cursor = slc_cursor->Previous;
							book_db->pSelection = slc_cursor;//写入数据库的pSelection
							return selected_count;
						}
					case LG_NOT:
						if (book_db->pSelection == NULL) { //空选区，从数据库选择
							BookEx* db_cursor = GoToHead(book_db->pBookLink); //数据库记录指针
							BKSelect* temp_rec; //暂存新选区的指针
							BKSelect* prev_rec = NULL; //暂存上一个选区的指针
							int conv; //置信度，精确搜索时置信度只有0和1
							//枚举数据库
							while (db_cursor != NULL) {
								conv = IfSubset(content, get_info(&(db_cursor->Info)));
								if (conv == 0) { //非逻辑，取不符合的即可
									selected_count++;
									temp_rec = NewBKSelect(db_cursor, 0, prev_rec, NULL); //写一个反向链表（只有previous，而next为空）
									prev_rec = temp_rec;
								}
								db_cursor = db_cursor->Next; //移动到下一条记录
							}
							//检索完成后，回溯链表写入next参数，并得到链表头
							if (prev_rec == NULL) { //没有选到数据
								Call_Promote("没有符合条件的记录.");
								return 0;
							}
							temp_rec = prev_rec;
							prev_rec = prev_rec->Previous;
							while (prev_rec != NULL) {
								prev_rec->Next = temp_rec;
								temp_rec = prev_rec;
								prev_rec = prev_rec->Previous;
							}
							//写入数据库的pSelection
							book_db->pSelection = temp_rec;
							return selected_count;
						}
						else { //有选区，从选区选择
							BKSelect* slc_cursor = book_db->pSelection; //选区记录指针
							BKSelect* temp; //暂存指针
							int conv; //置信度，精确搜索时置信度只有0和1
							//处理除了最后一条的数据
							while (slc_cursor->Next != NULL) {
								conv = IfSubset(content, get_info(&(slc_cursor->SelectedItem->Info)));
								selected_count++;
								if (conv == 1) { //如果相似度满足，则从选区中删除这条记录
									selected_count--;
									if (slc_cursor->Previous != NULL)
										slc_cursor->Previous->Next = slc_cursor->Next;
									if (slc_cursor->Next != NULL)
										slc_cursor->Next->Previous = slc_cursor->Previous;
									temp = slc_cursor;
									slc_cursor = slc_cursor->Next;
									free(temp);
								}
								else {
									//精确搜索在非运算中置信度为0，这里就不动链表里的置信度数据了
									slc_cursor = slc_cursor->Next; //移动到下一条记录
								}
							}
							//特别处理最后一条记录避免重复判断指针为NULL的情况
							conv = IfSubset(content, get_info(&(slc_cursor->SelectedItem->Info)));
							selected_count++;
							if (conv == 1) { //如果相似度满足，则从选区中删除这条记录
								selected_count--;
								if (slc_cursor->Previous != NULL) {
									slc_cursor->Previous->Next = NULL;
									temp = slc_cursor;
									slc_cursor = slc_cursor->Previous;
									free(temp);
								}
								else { //前后都为NULL，返回选区为空
									free(slc_cursor);
									book_db->pSelection = NULL;
									Call_Promote("没有符合条件的记录.");
									return 0; //弹出
								}
							}
							//else
								//精确搜索在非运算中置信度为0，这里就不动链表里的置信度数据了
							//检索完成后，回溯到链表头，填写book_db
							while (slc_cursor->Previous != NULL)
								slc_cursor = slc_cursor->Previous;
							book_db->pSelection = slc_cursor;//写入数据库的pSelection
							return selected_count;
						}
					case LG_OR:
						Call_Promote("未实现的功能.");
						return 0;
					default:
						Call_Warning("不正确的逻辑表达式.");
						return 0;
					}
				}
			}
				//上面这个函数用的回调函数
				char* get_author(Book* from_where) { return from_where->Author; }
				char* get_press(Book* from_where) { return from_where->Press; }
				char* get_keyword(Book* from_where) { return from_where->KeyWord; }
				char* get_class(Book* from_where) { return from_where->Class; }

			// 以给定的数据精确搜索，对应void (*SelectExact)  【未完成】
			int select_exact_book_record(DB_Book* book_db,
				char* field, char* content, //搜索的内容
				int logic_identifier
			) {
				Call_Promote("函数未完成，这个定义留作后续拓展.");
			}

			// 选择整个数据库，对应void (*SelectAll)，用这个方法选取的置信度为0
			void select_all_book_db(DB_Book* book_db) {
				if (book_db->pBookLink == NULL) {
					Call_Promote("数据库为空.");
					return;
				}
				(*book_db).ResetSelection(book_db); //先释放已选内容避免冲突
				BKSelect* temp, * last_selected;
				BookEx* this_selected;
				this_selected = book_db->pBookLink;
				last_selected = (BKSelect*) malloc(sizeof(BKSelect));
				last_selected->SelectedItem = this_selected;
				last_selected->Confidence = 0;
				last_selected->Previous = NULL;
				last_selected->Next = NULL;
				this_selected = this_selected->Next;
				book_db->pSelection = last_selected;
				while (this_selected != NULL) {
					temp = (BKSelect*) malloc(sizeof(BKSelect));
					temp->SelectedItem = this_selected;
					temp->Confidence = 0;
					temp->Previous = last_selected;
					temp->Next = NULL;
					last_selected->Next = temp;
					last_selected = temp;
					this_selected = this_selected->Next;
				}
			}

			//按照置信度排序选区，对应void (*SoltSelection)
			void solt_selection_with_confidence(DB_Book* book_db) {
				book_db->pSelection = MergeSoltSelection(book_db->pSelection);
			}
				// 链表归并排序
				// 这个函数对BKSelect链表按置信度从大到小排序
				BKSelect* MergeSoltSelection(BKSelect* link) {
					//无需排序的情况（递归终点）
					if (link == NULL || link->Next == NULL)
						return link; //话说只要一开始给出的参数指针不是NULL，在递归过程中就不会出现参数为的情况NULL

					//快慢指针法查找链表中点
					BKSelect* p_slow, * p_fast;
					p_fast = p_slow = link;
					while (p_fast != NULL && p_fast->Next != NULL) { //&&的左右顺序不能换
						p_fast = p_fast->Next->Next;
						p_slow = p_slow->Next;
					} //最后slow达到中点右侧（至少是第二条记录）

					//按照中点截断链表
					BKSelect* left, * right;
					left = link;
					right = p_slow;
					right->Previous->Next = NULL;
					right->Previous = NULL;

					//递归左右两个链表
					left = MergeSoltSelection(left);
					right = MergeSoltSelection(right);

					//归并链表，将右表插入左表
					BKSelect* temp; //暂存用
					while (1) { //左表结束以前，向左插入记录（情况复杂，用break弹出）
						if (right->Confidence > left->Confidence) {
							//右值较大，向前插入
							if (left->Previous != NULL) {
								temp = right; right = right->Next;
								//修改插入项前后的4条字段
								temp->Previous = left->Previous;
								temp->Next = left;
								left->Previous->Next = temp;
								left->Previous = temp;								
							}
							else {
								temp = right; right = right->Next;
								//修改插入项前后的2条字段
								temp->Previous = NULL;
								temp->Next = left;
								left->Previous = temp;
							}
							//如果此时右表结束
							if (right == NULL)
								break; //结束情况：左表有余，右表结束
						}
						else {
							//左值较大，左指针后移
							if (left->Next != NULL)
								left = left->Next;
							else
								break; //结束情况：左表结束，右表有余且右表所有记录小于左表最小记录
						}							
					}
					//弹出循环有两种情况：1.右表已经结束；2.左表已经结束
					while (right != NULL){ //第二种情况时
						//把右表整个接到左表尾
						left->Next = right;
						right->Previous = left;
					}
					//找到归并后的表头
					while (left->Previous != NULL)
						left = left->Previous;

					//返回排序后的表头
					return left;
				}

			// 从.csv文件导入，对应void (*ImportFromCSV)
			void import_bookdb_from_CSV(DB_Book* book_db, char* direction) {
				TransformToBDB(direction, "temp_trans.bdb");
				(*book_db).ReadFromFile(book_db, "temp_trans.bdb");
			}

			// 导出为.csv文件，对应void (*ExportToCSV)  【未完成】
			void export_bookdb_to_CSV(DB_Book* This, char* direction) {
				Call_Promote("函数未完成，这个定义留作后续拓展.");
			}

			// 重置数据库对象，对应void (*Abandon)
			void abandon_book_db(DB_Book* book_db) {
				//清除管理部分内存
				if (book_db->pManageItem != NULL)
					free(book_db->pManageItem);
				book_db->pManageItem = NULL;
				//清除数据库内存
				if (book_db->pBookLink != NULL) {
					BookEx* here, * previous;
					here = GoToHead(book_db->pBookLink);
					while (here != NULL) {
						previous = here;
						here = here->Next;
						free(previous);
					}
				}
				book_db->pBookLink = NULL;
				//清除选区内存
				if (book_db->pSelection != NULL) {
					BKSelect* here, * previous;
					here = book_db->pSelection;
					while (here->Previous != NULL) {
						here = here->Previous;
					}
					while (here != NULL) {
						previous = here;
						here = here->Next;
						free(previous);
					}
				}
				book_db->pSelection = NULL;
			}

			// 关闭数据库，对应void (*Close)
			void close_book_db(DB_Book* book_db) {		
				(*book_db).Abandon(book_db); //清除数据			
				free(book_db); //清除数据库结构内存
			}

		// 外置部分
			// 新建一个数据库结构
			DB_Book* NewDBBook() {
				DB_Book* temp = malloc(sizeof(DB_Book));
				temp->pManageItem = NULL;
				temp->pBookLink = NULL;
				temp->pSelection = NULL;
				temp->ReadFromFile = read_book_database;
				temp->WriteToFile = write_book_database;
				temp->AddRecord = add_to_data;
				temp->AlterRecord = alt_book_record;
				temp->ResetSelection = reset_book_selection;
				temp->SelectBy = select_book_record;
				temp->SelectExact = select_exact_book_record;
				temp->SelectAll = select_all_book_db;
				temp->SoltSelection = solt_selection_with_confidence;
				temp->ImportFromCSV = import_bookdb_from_CSV;
				temp->ExportToCSV = export_bookdb_to_CSV;
				temp->Abandon = abandon_book_db;
				temp->Close = close_book_db;
				return temp;
			}
