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

/*  <����>
 *  ���ݿ����ģ��
 *  ���������ݿ�ṹ�����з�װ��
 *  ʵ�ִ��ⲿ��ȡ����/���ⲿд����
 *  �Լ����ݿ���������
 */

// ����������ʱ����Ϊ��ص���С�������Ŷ�
#define LOWEST_CON 0.58


/* -- ���ݿ�ṹ -- */

	// ����ѡ���ṹ

		// ѡ���ṹ
		// ѡ���ṹ��һ����BookExָ�빹�ɵ������Ա������ݿ������з������ļ�¼��ַ
		/*typedef struct book_selection_item  BKSelect;
		struct book_selection_item
		{
			BookEx* SelectedItem; //ѡ������

			//���Ŷȣ������¼��ɸѡ�ؼ��ֵ����Ƴ̶ȣ������Ż������������
			//  ������and����ʱ��Ӧ�����ŶȽ�����ӣ�����not����ʱ�����or����ȡ���Ŷ����ֵ
			double Confidence; 

			BKSelect* Previous;
			BKSelect* Next;
		};*/

		// �½�һ��ѡ���ṹ
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


	// �������ݿ�ṹ
	
		/* 
		 * ��������ȡ�������ݿ��ļ���Ϊһ�����壬
		 * �����涨��ĸ��ֽṹ����ȥ��װ��αoop
		 */

		// ���ݿ�ṹ��
		/*typedef struct database_books_item  DB_Book;
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
				// �������ʹ��pSelection�����棬������Ϊ��ʱ�������������ݿ�����������������Ϣ������ѡ����
				// ��������������������ʱ���ѡ����û�з��������ļ�¼������ʾ�û������ѡ����
				// �����Ҫ�����ݿ���������������ǰ��ʹ��ResetSelection()
				//
				// �߼��ؼ��ֶ���������ṹ�����ĵط�: LG_AND(0), LG_OR(1), LG_NOT(2)

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
		#define LG_NOT 2 */

		// ����
		// ���ò���
			// �Ӵ��̶�ȡ���ݿ⣬��Ӧvoid (*ReadFromFile)
			void read_book_database(DB_Book* book_db, 
				const char* direction
			){
				FILE* p_file;
				if ((p_file = fopen(direction, "rb")) == NULL) {
					Call_Error("�鼮���ݿ��ȡʧ�ܻ��ļ�������.");
					if (fclose(p_file))
						Call_Error("�ļ�û�������ر�.");
					return; //Exit
				}

				//��ȡ�ļ�ͷ
				book_db->pManageItem = (BKManage*) malloc(sizeof(BKManage)); //����ռ�
				//��û�ж�ȡ������ṹ����Ϣ 
				if (fread(book_db->pManageItem, sizeof(BKManage), 1, p_file) != 1) {
					Call_Error("�Ҳ������ݿ���Ϣ���������Ƿ���һ����Ч�Ŀ�.");
					if (fclose(p_file))
						Call_Error("�ļ�û�������ر�.");
					return; //Exit
				}
				//�������Ĺ�����Ϣ�����쳣�����ܸ����ݿ�û��д�����ṹ
				if (BKM_CheckIntegrity(book_db->pManageItem)) {
					Call_Warning("���ݿ�ͷ�쳣����������ͷ��.");
					rewind(p_file); //�ļ�ָ��ص��ļ���ʼ				
				}

				//��ȡ����
				const int size_of_book = sizeof(Book);
				Book temp_book;  //������
				BookEx *temp_link, *temp_prev;  //������
				//��ȡ��һ����¼�����ʧ��֤�����ݿ�Ϊ��
				if (fread(&temp_book, size_of_book, 1, p_file) != 1) {
					Call_Warning("���ݿ�Ϊ��.");
					book_db->pBookLink = NULL;
					if (fclose(p_file))
						Call_Error("�ļ�û�������ر�.");
					return;
				}
				book_db->pBookLink = temp_prev = NewBookEx(temp_book);  //���ݿ�ṹ�е�����ָ��ָ���ͷ
				//��Ϊһ�ζ�ȡһ�飬ֻҪ��ȡ����Ϊ1�ʹ����ȡ�ɹ�
				while (fread(&temp_book, size_of_book, 1, p_file) == 1) {
					//�Ѷ�ȡ�������ݽ�������
					temp_link = NewBookEx(temp_book);
					temp_link->Previous = temp_prev;
					temp_link->Next = NULL;
					temp_prev->Next = temp_link;
					temp_prev = temp_link;
				}
				//�˳�ʱ�ж��Ƿ�Ϊ�����˳�
				if (feof(p_file) != 0) {
					if (ferror(p_file) != 0)
						Call_Error("��ȡ�쳣�ж�.");						
					/*else
						Call_Warning("���ڶ�������.");*/
					//��Ϊÿ�ζ��ж������ݵı������Ըɴ಻����
				}

				//�ر��ļ�
				if (fclose(p_file))
					Call_Error("�ļ�û�������ر�.");
			}

			// �����д�����ݿ⣬��Ӧvoid (*WriteToFile)
			void write_book_database(DB_Book* book_db,
				char* direction
			){
				FILE* p_file;
				if ((p_file = fopen(direction, "wb")) == NULL) {
					Call_Error("δ�ܴ������ݿ��ļ�.");
					if (fclose(p_file))
						Call_Error("�ļ�û�������ر�.");
					return; //Exit
				}

				//д�ļ�ͷ
				if (fwrite(book_db->pManageItem, sizeof(BKManage), 1, p_file) != 1) {
					Call_Error("д���쳣�������ļ�ͷ��.");
					rewind(p_file); //ָ���ͷ��
				}

				//д����
				if (book_db->pBookLink == NULL)
					Call_Warning("���ݿ�Ϊ��."); //������ָ��û������ʱ
				else {
					const int size_of_book = sizeof(Book);
					Book* temp_info;
					BookEx* temp_ex; //������
					temp_ex = book_db->pBookLink;
					//ѭ��д��
					while (temp_ex != NULL){
						temp_info = &(temp_ex->Info);
						if (fwrite(temp_info, size_of_book, 1, p_file) != 1)
							Call_Error("д���쳣.");
						temp_ex = temp_ex->Next;
					}
				}
				if (fclose(p_file))
					Call_Error("�ļ�û�������ر�.");
			}

			// ���һ����¼����Ӧvoid (*AddRecord)
			void add_to_data(DB_Book* book_db,
				BookEx* new_line
			){
				//��������ͺ���
				BookEx* temp; 
				temp = GoToEnd(book_db->pBookLink);
				temp->Next = new_line;
				new_line->Previous = temp;
				//��������β����
				new_line->Next = NULL;
				//ע��
				(*new_line).Regist(new_line, book_db->pManageItem);
			}

			// �޸�һ����¼����Ӧvoid (*AlterRecord)
			// ���԰�����������ָ������Ҫ�޸ļ�¼��λ�ã�����������0ʱ����ָ������
			void alt_book_record(DB_Book* book_db,
				Book content,
				int bookID,
				BookEx* exact_pointer
			) {
					//c��Ȼ����ȱʡ����******
				//�տ�����
				if (book_db->pBookLink == NULL) {
					Call_Warning("���������յ����ݿ�.");
					return;
				}
				//���������ҵ����
				if (bookID != 0) {
					BookEx* temp;
					temp = GoToHead(book_db->pBookLink);
					//��Ϊ���ݿ��ǹ̶���������С����������������Դ�ͷ��ʼO(n)
					while (temp->Info.BookID < bookID)
					{
						if (temp->Next != NULL)
							temp = temp->Next;
						else {
							Call_Promote("û���ҵ���Ӧ�ļ�¼.");
							return;
						}
					}
					//�������ѭ��
					if (temp->Info.BookID == bookID) {
						//�ҵ�ʱ
						//�̳�Title/Author/Press/ISBNcode/PublicationDATE/KeyWord/Class�ֶ�
						strcpy(temp->Info.Title, content.Title);
						strcpy(temp->Info.Author, content.Author);
						strcpy(temp->Info.Press, content.Press);
						strcpy(temp->Info.ISBNcode, content.ISBNcode);
						temp->Info.PublicationDATE = content.PublicationDATE;
						strcpy(temp->Info.KeyWord, content.KeyWord);
						strcpy(temp->Info.Class, content.Class);
							//��Ϊֻ�̳в��֣�ֻ�������ֵXD
						return;
					}
					else {
						Call_Promote("û���ҵ���Ӧ�ļ�¼.");
						return;
					}
				 }
				//��ָ�벻�ò��ҵ����
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

			// ����ѡ������Ӧvoid (*ResetSelection)
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

			// �Ը���������ģ����������Ӧvoid (*SelectBy)
			// �����������ֶΣ�Title��Author��Keyword��Class �����߼�δ��ɡ�
			int select_book_record(DB_Book* book_db,
				char* field, char* content,
				int logic_identifier
			) {
				if (book_db->pBookLink == NULL) {
					Call_Promote("���ݿ�Ϊ��.");
					return 0;
				}
				int selected_count = 0; //��¼ѡȡ�����ݵ�����
				if (strcmp(field, "Title") == 0) { //������������ģ��������
					switch (logic_identifier) {
					case LG_AND:
						if (book_db->pSelection == NULL) { //��ѡ���������ݿ�ѡ��
							BookEx* db_cursor = GoToHead(book_db->pBookLink); //���ݿ��¼ָ��
							BKSelect* temp_rec; //�ݴ���ѡ����ָ��
							BKSelect* prev_rec = NULL; //�ݴ���һ��ѡ����ָ��
							double conv; //���Ŷ�
							//ö�����ݿ�
							while (db_cursor != NULL) {
								conv = Similarity(content, db_cursor->Info.Title);
								if (conv > LOWEST_CON) {
									selected_count++;
									temp_rec = NewBKSelect(db_cursor, conv, prev_rec, NULL); //дһ����������ֻ��previous����nextΪ�գ�
									prev_rec = temp_rec;
								}
								db_cursor = db_cursor->Next; //�ƶ�����һ����¼
							}
							//������ɺ󣬻�������д��next���������õ�����ͷ
							if (prev_rec == NULL) { //û��ѡ������
								Call_Promote("û�з��������ļ�¼.");
								return 0;
							}
							temp_rec = prev_rec;
							prev_rec = prev_rec->Previous;
							while (prev_rec != NULL) {
								prev_rec->Next = temp_rec;
								temp_rec = prev_rec;
								prev_rec = prev_rec->Previous;
							}
							//д�����ݿ��pSelection
							book_db->pSelection = temp_rec;
							return selected_count;
						}
						else { //��ѡ������ѡ��ѡ��
							BKSelect* slc_cursor = book_db->pSelection; //ѡ����¼ָ��
							BKSelect* temp; //�ݴ�ָ��
							double conv; //���Ŷ�
							//����������һ��������
							while (slc_cursor->Next != NULL) {
								conv = Similarity(content, slc_cursor->SelectedItem->Info.Title);
								selected_count++;
								if (conv < LOWEST_CON) { //������ƶȲ��㣬���ѡ����ɾ��������¼
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
									slc_cursor->Confidence += conv; //���������У����Ŷ����
									slc_cursor = slc_cursor->Next; //�ƶ�����һ����¼
								}
							}
							//�ر������һ����¼�����ظ��ж�ָ��ΪNULL�����
							conv = Similarity(content, slc_cursor->SelectedItem->Info.Title);
							selected_count++;
							if (conv < LOWEST_CON) { //������ƶȲ��㣬���ѡ����ɾ��������¼
								selected_count--;
								if (slc_cursor->Previous != NULL) {
									slc_cursor->Previous->Next = NULL;
									temp = slc_cursor;
									slc_cursor = slc_cursor->Previous;
									free(temp);
								}
								else { //ǰ��ΪNULL������ѡ��Ϊ��
									free(slc_cursor);
									book_db->pSelection = NULL;
									Call_Promote("û�з��������ļ�¼.");
									return 0; //����
								}
							}
							else
								slc_cursor->Confidence += conv; //���������У����Ŷ����
							//������ɺ󣬻��ݵ�����ͷ����дbook_db
							while (slc_cursor->Previous != NULL)
								slc_cursor = slc_cursor->Previous;
							book_db->pSelection = slc_cursor;//д�����ݿ��pSelection
							return selected_count;
						}
					case LG_NOT:
						if (book_db->pSelection == NULL) { //��ѡ���������ݿ�ѡ��
							BookEx* db_cursor = GoToHead(book_db->pBookLink); //���ݿ��¼ָ��
							BKSelect* temp_rec; //�ݴ���ѡ����ָ��
							BKSelect* prev_rec = NULL; //�ݴ���һ��ѡ����ָ��
							double conv; //���Ŷ�
							//ö�����ݿ�
							while (db_cursor != NULL) {
								conv = Similarity(content, db_cursor->Info.Title);
								if (conv < LOWEST_CON) { //���߼���ȡ�����ϵļ���
									selected_count++;
									temp_rec = NewBKSelect(db_cursor, -1 * conv, prev_rec, NULL); //дһ����������ֻ��previous����nextΪ�գ�
									prev_rec = temp_rec;
								}
								db_cursor = db_cursor->Next; //�ƶ�����һ����¼
							}
							//������ɺ󣬻�������д��next���������õ�����ͷ
							if (prev_rec == NULL) { //û��ѡ������
								Call_Promote("û�з��������ļ�¼.");
								return 0;
							}
							temp_rec = prev_rec;
							prev_rec = prev_rec->Previous;
							while (prev_rec != NULL) {
								prev_rec->Next = temp_rec;
								temp_rec = prev_rec;
								prev_rec = prev_rec->Previous;
							}
							//д�����ݿ��pSelection
							book_db->pSelection = temp_rec;
							return selected_count;
						}
						else { //��ѡ������ѡ��ѡ��
							BKSelect* slc_cursor = book_db->pSelection; //ѡ����¼ָ��
							BKSelect* temp; //�ݴ�ָ��
							double conv; //���Ŷ�
							//����������һ��������
							while (slc_cursor->Next != NULL) {
								conv = Similarity(content, slc_cursor->SelectedItem->Info.Title);
								selected_count++;
								if (conv > LOWEST_CON) { //������ƶ����㣬���ѡ����ɾ��������¼
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
									slc_cursor->Confidence -= conv; //�ڷ������У����Ŷ����
									slc_cursor = slc_cursor->Next; //�ƶ�����һ����¼
								}
							}
							//�ر������һ����¼�����ظ��ж�ָ��ΪNULL�����
							conv = Similarity(content, slc_cursor->SelectedItem->Info.Title);
							selected_count++;
							if (conv > LOWEST_CON) { //������ƶ����㣬���ѡ����ɾ��������¼
								selected_count--;
								if (slc_cursor->Previous != NULL) {
									slc_cursor->Previous->Next = NULL;
									temp = slc_cursor;
									slc_cursor = slc_cursor->Previous;
									free(temp);
								}
								else { //ǰ��ΪNULL������ѡ��Ϊ��
									free(slc_cursor);
									book_db->pSelection = NULL;
									Call_Promote("û�з��������ļ�¼.");
									return 0; //����
								}
							}
							else
								slc_cursor->Confidence -= conv; //�ڷ������У����Ŷ����
							//������ɺ󣬻��ݵ�����ͷ����дbook_db
							while (slc_cursor->Previous != NULL)
								slc_cursor = slc_cursor->Previous;
							book_db->pSelection = slc_cursor;//д�����ݿ��pSelection
							return selected_count;
						}
					case LG_OR:
						Call_Promote("δʵ�ֵĹ���.");
						return 0;
					default:
						Call_Warning("����ȷ���߼����ʽ.");
						return 0;
					}				
				}
				else { //������/������/�ؼ���/������������ȷ������
					char* (*get_info)(Book* from_where); //��ȡ��Ҫ��Ϣ�Ļص�����
					//���ݲ�ͬ�����ֵ�ص�����
					if (strcmp(field, "Author") == 0)
						get_info = get_author;
					else if (strcmp(field, "Press") == 0)
						get_info = get_press;
					else if (strcmp(field, "Keyword") == 0)
						get_info = get_keyword;
					else if (strcmp(field, "Class") == 0)
						get_info = get_class;
					else {
						Call_Warning("����ȷ���ֶ���.");
						return 0;
					}
					//��ȷ����������ͬ��
					switch (logic_identifier) {
					case LG_AND:
						if (book_db->pSelection == NULL) { //��ѡ���������ݿ�ѡ��
							BookEx* db_cursor = GoToHead(book_db->pBookLink); //���ݿ��¼ָ��
							BKSelect* temp_rec; //�ݴ���ѡ����ָ��
							BKSelect* prev_rec = NULL; //�ݴ���һ��ѡ����ָ��
							int conv; //���Ŷȣ���ȷ����ʱ���Ŷ�ֻ��0��1
							//ö�����ݿ�
							while (db_cursor != NULL) {
								conv = IfSubset(content, get_info(&(db_cursor->Info))); //�ж��Ӵ���ϵ
								if (conv == 1) {
									selected_count++;
									temp_rec = NewBKSelect(db_cursor, (double)conv, prev_rec, NULL); //дһ����������ֻ��previous����nextΪ�գ�
									prev_rec = temp_rec;
								}
								db_cursor = db_cursor->Next; //�ƶ�����һ����¼
							}
							//������ɺ󣬻�������д��next���������õ�����ͷ
							if (prev_rec == NULL) { //û��ѡ������
								Call_Promote("û�з��������ļ�¼.");
								return 0;
							}
							temp_rec = prev_rec;
							prev_rec = prev_rec->Previous;
							while (prev_rec != NULL) {
								prev_rec->Next = temp_rec;
								temp_rec = prev_rec;
								prev_rec = prev_rec->Previous;
							}
							//д�����ݿ��pSelection
							book_db->pSelection = temp_rec;
							return selected_count;
						}
						else { //��ѡ������ѡ��ѡ��
							BKSelect* slc_cursor = book_db->pSelection; //ѡ����¼ָ��
							BKSelect* temp; //�ݴ�ָ��
							int conv; //���Ŷȣ���ȷ����ʱ���Ŷ�ֻ��0��1
							//����������һ��������
							while (slc_cursor->Next != NULL) {
								conv = IfSubset(content, get_info(&(slc_cursor->SelectedItem->Info)));
								selected_count++;
								if (conv == 0) { //������ƶȲ��㣬���ѡ����ɾ��������¼
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
									slc_cursor->Confidence += (double)conv; //���������У����Ŷ����
									slc_cursor = slc_cursor->Next; //�ƶ�����һ����¼
								}
							}
							//�ر������һ����¼�����ظ��ж�ָ��ΪNULL�����
							conv = IfSubset(content, get_info(&(slc_cursor->SelectedItem->Info)));
							selected_count++;
							if (conv == 0) { //������ƶȲ��㣬���ѡ����ɾ��������¼
								selected_count--;
								if (slc_cursor->Previous != NULL) {
									slc_cursor->Previous->Next = NULL;
									temp = slc_cursor;
									slc_cursor = slc_cursor->Previous;
									free(temp);
								}
								else { //ǰ��ΪNULL������ѡ��Ϊ��
									free(slc_cursor);
									book_db->pSelection = NULL;
									Call_Promote("û�з��������ļ�¼.");
									return 0; //����
								}
							}
							else
								slc_cursor->Confidence += (double)conv; //���������У����Ŷ����
							//������ɺ󣬻��ݵ�����ͷ����дbook_db
							while (slc_cursor->Previous != NULL)
								slc_cursor = slc_cursor->Previous;
							book_db->pSelection = slc_cursor;//д�����ݿ��pSelection
							return selected_count;
						}
					case LG_NOT:
						if (book_db->pSelection == NULL) { //��ѡ���������ݿ�ѡ��
							BookEx* db_cursor = GoToHead(book_db->pBookLink); //���ݿ��¼ָ��
							BKSelect* temp_rec; //�ݴ���ѡ����ָ��
							BKSelect* prev_rec = NULL; //�ݴ���һ��ѡ����ָ��
							int conv; //���Ŷȣ���ȷ����ʱ���Ŷ�ֻ��0��1
							//ö�����ݿ�
							while (db_cursor != NULL) {
								conv = IfSubset(content, get_info(&(db_cursor->Info)));
								if (conv == 0) { //���߼���ȡ�����ϵļ���
									selected_count++;
									temp_rec = NewBKSelect(db_cursor, 0, prev_rec, NULL); //дһ����������ֻ��previous����nextΪ�գ�
									prev_rec = temp_rec;
								}
								db_cursor = db_cursor->Next; //�ƶ�����һ����¼
							}
							//������ɺ󣬻�������д��next���������õ�����ͷ
							if (prev_rec == NULL) { //û��ѡ������
								Call_Promote("û�з��������ļ�¼.");
								return 0;
							}
							temp_rec = prev_rec;
							prev_rec = prev_rec->Previous;
							while (prev_rec != NULL) {
								prev_rec->Next = temp_rec;
								temp_rec = prev_rec;
								prev_rec = prev_rec->Previous;
							}
							//д�����ݿ��pSelection
							book_db->pSelection = temp_rec;
							return selected_count;
						}
						else { //��ѡ������ѡ��ѡ��
							BKSelect* slc_cursor = book_db->pSelection; //ѡ����¼ָ��
							BKSelect* temp; //�ݴ�ָ��
							int conv; //���Ŷȣ���ȷ����ʱ���Ŷ�ֻ��0��1
							//����������һ��������
							while (slc_cursor->Next != NULL) {
								conv = IfSubset(content, get_info(&(slc_cursor->SelectedItem->Info)));
								selected_count++;
								if (conv == 1) { //������ƶ����㣬���ѡ����ɾ��������¼
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
									//��ȷ�����ڷ����������Ŷ�Ϊ0������Ͳ�������������Ŷ�������
									slc_cursor = slc_cursor->Next; //�ƶ�����һ����¼
								}
							}
							//�ر������һ����¼�����ظ��ж�ָ��ΪNULL�����
							conv = IfSubset(content, get_info(&(slc_cursor->SelectedItem->Info)));
							selected_count++;
							if (conv == 1) { //������ƶ����㣬���ѡ����ɾ��������¼
								selected_count--;
								if (slc_cursor->Previous != NULL) {
									slc_cursor->Previous->Next = NULL;
									temp = slc_cursor;
									slc_cursor = slc_cursor->Previous;
									free(temp);
								}
								else { //ǰ��ΪNULL������ѡ��Ϊ��
									free(slc_cursor);
									book_db->pSelection = NULL;
									Call_Promote("û�з��������ļ�¼.");
									return 0; //����
								}
							}
							//else
								//��ȷ�����ڷ����������Ŷ�Ϊ0������Ͳ�������������Ŷ�������
							//������ɺ󣬻��ݵ�����ͷ����дbook_db
							while (slc_cursor->Previous != NULL)
								slc_cursor = slc_cursor->Previous;
							book_db->pSelection = slc_cursor;//д�����ݿ��pSelection
							return selected_count;
						}
					case LG_OR:
						Call_Promote("δʵ�ֵĹ���.");
						return 0;
					default:
						Call_Warning("����ȷ���߼����ʽ.");
						return 0;
					}
				}
			}
				//������������õĻص�����
				char* get_author(Book* from_where) { return from_where->Author; }
				char* get_press(Book* from_where) { return from_where->Press; }
				char* get_keyword(Book* from_where) { return from_where->KeyWord; }
				char* get_class(Book* from_where) { return from_where->Class; }

			// �Ը��������ݾ�ȷ��������Ӧvoid (*SelectExact)  ��δ��ɡ�
			int select_exact_book_record(DB_Book* book_db,
				char* field, char* content, //����������
				int logic_identifier
			) {
				Call_Promote("����δ��ɣ������������������չ.");
			}

			// ѡ���������ݿ⣬��Ӧvoid (*SelectAll)�����������ѡȡ�����Ŷ�Ϊ0
			void select_all_book_db(DB_Book* book_db) {
				if (book_db->pBookLink == NULL) {
					Call_Promote("���ݿ�Ϊ��.");
					return;
				}
				(*book_db).ResetSelection(book_db); //���ͷ���ѡ���ݱ����ͻ
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

			//�������Ŷ�����ѡ������Ӧvoid (*SoltSelection)
			void solt_selection_with_confidence(DB_Book* book_db) {
				book_db->pSelection = MergeSoltSelection(book_db->pSelection);
			}
				// ����鲢����
				// ���������BKSelect�������ŶȴӴ�С����
				BKSelect* MergeSoltSelection(BKSelect* link) {
					//���������������ݹ��յ㣩
					if (link == NULL || link->Next == NULL)
						return link; //��˵ֻҪһ��ʼ�����Ĳ���ָ�벻��NULL���ڵݹ�����оͲ�����ֲ���Ϊ�����NULL

					//����ָ�뷨���������е�
					BKSelect* p_slow, * p_fast;
					p_fast = p_slow = link;
					while (p_fast != NULL && p_fast->Next != NULL) { //&&������˳���ܻ�
						p_fast = p_fast->Next->Next;
						p_slow = p_slow->Next;
					} //���slow�ﵽ�е��Ҳࣨ�����ǵڶ�����¼��

					//�����е�ض�����
					BKSelect* left, * right;
					left = link;
					right = p_slow;
					right->Previous->Next = NULL;
					right->Previous = NULL;

					//�ݹ�������������
					left = MergeSoltSelection(left);
					right = MergeSoltSelection(right);

					//�鲢�������ұ�������
					BKSelect* temp; //�ݴ���
					while (1) { //��������ǰ����������¼��������ӣ���break������
						if (right->Confidence > left->Confidence) {
							//��ֵ�ϴ���ǰ����
							if (left->Previous != NULL) {
								temp = right; right = right->Next;
								//�޸Ĳ�����ǰ���4���ֶ�
								temp->Previous = left->Previous;
								temp->Next = left;
								left->Previous->Next = temp;
								left->Previous = temp;								
							}
							else {
								temp = right; right = right->Next;
								//�޸Ĳ�����ǰ���2���ֶ�
								temp->Previous = NULL;
								temp->Next = left;
								left->Previous = temp;
							}
							//�����ʱ�ұ����
							if (right == NULL)
								break; //���������������࣬�ұ����
						}
						else {
							//��ֵ�ϴ���ָ�����
							if (left->Next != NULL)
								left = left->Next;
							else
								break; //������������������ұ��������ұ����м�¼С�������С��¼
						}							
					}
					//����ѭ�������������1.�ұ��Ѿ�������2.����Ѿ�����
					while (right != NULL){ //�ڶ������ʱ
						//���ұ������ӵ����β
						left->Next = right;
						right->Previous = left;
					}
					//�ҵ��鲢��ı�ͷ
					while (left->Previous != NULL)
						left = left->Previous;

					//���������ı�ͷ
					return left;
				}

			// ��.csv�ļ����룬��Ӧvoid (*ImportFromCSV)
			void import_bookdb_from_CSV(DB_Book* book_db, char* direction) {
				TransformToBDB(direction, "temp_trans.bdb");
				(*book_db).ReadFromFile(book_db, "temp_trans.bdb");
			}

			// ����Ϊ.csv�ļ�����Ӧvoid (*ExportToCSV)  ��δ��ɡ�
			void export_bookdb_to_CSV(DB_Book* This, char* direction) {
				Call_Promote("����δ��ɣ������������������չ.");
			}

			// �������ݿ���󣬶�Ӧvoid (*Abandon)
			void abandon_book_db(DB_Book* book_db) {
				//����������ڴ�
				if (book_db->pManageItem != NULL)
					free(book_db->pManageItem);
				book_db->pManageItem = NULL;
				//������ݿ��ڴ�
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
				//���ѡ���ڴ�
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

			// �ر����ݿ⣬��Ӧvoid (*Close)
			void close_book_db(DB_Book* book_db) {		
				(*book_db).Abandon(book_db); //�������			
				free(book_db); //������ݿ�ṹ�ڴ�
			}

		// ���ò���
			// �½�һ�����ݿ�ṹ
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
