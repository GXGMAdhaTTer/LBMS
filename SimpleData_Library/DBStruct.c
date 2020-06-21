#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "DBGeneral.h"

#include "DBStruct.h"

/* ͼ��ⲿ�� */
/* ----- DB_Struct ----- */
/* ----- ver 0.0.1 ----- */

/*  < ���� >
 *  ���ģ�鶨�������ݿ�������ļ��ṹ�뷽����
 *  �������װ��αoop����
 *
 *
 *  �������� ����ı��������ޡ�
 *
 *  P.S.�ṹ�嶨���ڶ�Ӧ��.h�ļ���
 */


/* -- ���ڽṹ -- */

	// �������ڽṹ
		//�ṹ��
		/*typedef struct expand_date_item
		{
			unsigned int Year : 12;  //��ݣ�0~4095
			unsigned int Month : 4;  //�£�0~15
			unsigned int Day : 5;  //���ڣ�0~31
			unsigned int Mark : 3;  //��ע�����ո�������3�ֽڣ�
		}DateEx;*/

		//����
			//��ȡ��ǰ���ڽṹ�����µ�����
			int Day_of_Month(DateEx date_input){
				switch (date_input.Month){
					case 1: case 3: case 5: case 7:
					case 8: case 10: case 12:
						return 31;
					case 4: case 6: case 9: case 11:
						return 30;
					case 2:
						if (date_input.Year % 4 == 0
							&& date_input.Year % 100 != 0
							){return 29;}
						else {return 28;}
				}
			}

			//���ڼӷ�
			DateEx DateAdd(DateEx date_input, int day_input){
				//���㼸��֮�������
				int temp = date_input.Day + day_input;
				while (temp > Day_of_Month(date_input)){
					temp -= Day_of_Month(date_input);
					date_input.Month ++;
					if (date_input.Month > 12){
						date_input.Month = 1;
						date_input.Year ++;
					}
				}
				date_input.Day = temp;
				return date_input;
			}


/* -- ����ṹ -- */

	// �������ṹ

		/*
		 *  ����ṹ��¼�����ݿ��������Ϣ��
		 *  �Ա���Ϊ�鼮ע��Ψһ���ʱʹ��
		 */

		// �ṹ��
		/*typedef struct book_management_item
		{
			//���ݿ���Ϣ
			unsigned int BooksStored;  //��¼�鼮����
			unsigned int BookBorrowed;  //����������
			unsigned int BookReserved;  //Ԥ��������
			unsigned int LastBookID;  //������ţ�ע������ʱ���������Ϊ�ú��� +1

			//ͳ��
			unsigned int TotalBookBorrowed;  //�ܽ�����
			unsigned int TotalBookReserved;  //��Ԥ����
		} BKManage;*/

		// ���÷���
		//���BKManage�����ԣ�����0����������1ȱ��
		int BKM_CheckIntegrity(BKManage* book_manage) {
			if (book_manage->BooksStored > book_manage->LastBookID) { Call_Warning("���ݿ�ͷ���ܲ�����."); return 1; }
			if (book_manage->BookReserved > book_manage->BooksStored) { Call_Warning("���ݿ�ͷ���ܲ�����."); return 1; }
			if (book_manage->BookBorrowed > book_manage->BooksStored) { Call_Warning("���ݿ�ͷ���ܲ�����."); return 1; }
			return 0;
		}


/* -- �鼮�ṹ -- */

	//typedef struct expand_book_item BookEx;

	// �����鼮��Ϣ�ṹ
		// �ṹ��
		/*typedef struct book_item
		{
			//������Ϣ
			char Title[64];  //����
			char Author[48];  //���ߣ����ж��ʱ��"/"�Ͽ���
			char Press[48];  //������
			char ISBNcode[24];  //ISBN
			DateEx PublicationDATE; //��������

			//������Ϣ
			char KeyWord[32];  //�ؼ��ʣ����ж��ʱ��"/"�Ͽ���
			char Class[24];  //���ࣨС˵����ѧ�ȣ������ж��ʱ��"/"�Ͽ���

			//�û���Ϣ
			int Stars;  //������
			int TotalBorrow;  //�ܽ�����

			//�ݲ���Ϣ
			unsigned int BookID;  //Ψһ���
			unsigned int Status : 2;  //����״̬���У�����(0)������(1)��Ԥ��(2)��3����
			char UserID[24];  //����/Ԥ���߱��
			DateEx BorrowDATE;  //����/Ԥ������
			DateEx ReturnDATE;  //Ӧ������/Ԥ����������
		} Book;

		// ��Ӧ����
		#define BK_Avaliable 0  // �������״̬
		#define BK_Borrowed  1
		#define BK_Reserved  2*/

	// ��չͼ��ṹ��
	// ʵ��αoop������ͬʱ����ǰ������ָ���Ա����˫������
		// �ṹ��
		/*typedef struct expand_book_item
		{
			//ͼ����Ϣ
			Book Info;

			//���������
			BookEx *Previous;
			BookEx *Next;

			//����
			//c���Բ������ýṹ��������ʼ��ʱ�ǵü�����Щָ��
			void (*Like)(BookEx *This);  //���޴���
			void (*Borrow)(BookEx *This,  //���Ĵ���
				BKManage *bk_manage,  //����ṹ
				User *user,  //�����ߵ��û��ṹ
				DateEx borrow_date  //��������
				);  //ÿ�ν���ӦĬ����30���黹
			void (*Reserve)(BookEx *This,  //Ԥ������
				BKManage *bk_manage,  //����ṹ
				User *user,  //�����ߵ��û��ṹ
				DateEx borrow_date  //Ԥ������
				);
			void (*Renew)(BookEx *This, User *user);  //�������
			void (*Return)(BookEx *This,  //�黹����
				User *user,  //�����ߵ��û��ṹ
				BKManage *bk_manage  //����ṹ
				);
			void (*Regist)(BookEx *This,  //ע�����
				BKManage *bk_manage  //����ṹ
				);  //�ú��������ṹ����һ���µ����
			void (*Destory)(BookEx *This,  //���ٴ���
				BKManage *bk_manage  //����ṹ
				);
		} BookEx;*/

		// �ṹ����
			// 1. ��Ƕ����
			//    ��Ƕ���ֵ�ÿһ��������Ӧ�ṹ���һ��ָ��

			// ���ޣ���Ӧvoid (*Like)
			void like_book( BookEx *ex_book){
				(ex_book -> Info).Stars ++;
			}

			// ���ģ���Ӧvoid (*Borrow)
			void borrow_book( BookEx *ex_book,
				BKManage *bk_manage,  //����ṹ
				User *user,  //�����ߵ��û��ṹ
				DateEx borrow_date  //��������
			){	//ÿ�ν���ӦĬ����30���黹
				char user_id[24];
				TransToStr(user->Info.UserID, user_id); //��ʷ�������⣬ת����ʽ

				//дͼ�����ļ�¼
				(*ex_book).Info.Status = BK_Borrowed;
				strcpy((*ex_book).Info.UserID, user_id);
				(*ex_book).Info.BorrowDATE = borrow_date;
				(*ex_book).Info.ReturnDATE = DateAdd(borrow_date, 30);

				(*ex_book).Info.TotalBorrow ++;
				(*bk_manage).BookBorrowed ++;
				(*bk_manage).TotalBookBorrowed ++;

				//д�û�����ļ�¼
				user->AddRelativeRecord(user, ex_book);
			}

			// Ԥ������Ӧvoid (*Reserve)
			void reserve_book( BookEx *ex_book,  //Ԥ������
				BKManage *bk_manage,  //����ṹ
				User* user,  //�����ߵ��û��ṹ
				DateEx borrow_date  //Ԥ������
			){	//Ĭ����30���黹
				char user_id[24];
				TransToStr(user->Info.UserID, user_id); //��ʷ�������⣬ת����ʽ

				//дͼ�����ļ�¼
				(*ex_book).Info.Status = BK_Reserved;
				strcpy((*ex_book).Info.UserID, user_id);
				(*ex_book).Info.BorrowDATE = borrow_date;
				(*ex_book).Info.ReturnDATE = DateAdd(borrow_date, 30);

				(*bk_manage).BookReserved ++;
				(*bk_manage).TotalBookReserved ++;

				//д�û�����ļ�¼
				user->AddRelativeRecord(user, ex_book);
			}

			// ���裬��Ӧvoid (*Renew)
			void renew_book(BookEx *ex_book, User* user){
				if ((*ex_book).Info.Status != BK_Borrowed){
					Call_Promote("��������δ������鼮.");
					return;
				}
				//����û��Ƿ�ƥ��
				char user_id[24];
				TransToStr(user->Info.UserID, user_id); //��ʷ�������⣬ת����ʽ
				if (strcmp(ex_book->Info.UserID, user_id) != 0) {
					Call_Promote("�û�����ƥ��.");
					return;
				}

				(*ex_book).Info.ReturnDATE = DateAdd(
					(*ex_book).Info.ReturnDATE, 15);  //����15��
				user->DelRelativeRecord(user, ex_book->Info.BookID); //ɾ�ɼ�¼
				user->AddRelativeRecord(user, ex_book); //д�¼�¼
			}

			// �黹����Ӧvoid (*Return)
			void return_book( BookEx *ex_book,  //�黹����
				User* user, //�û�
				BKManage *bk_manage  //����ṹ
			){
				//����û��Ƿ�ƥ��
				char user_id[24];
				TransToStr(user->Info.UserID, user_id); //��ʷ�������⣬ת����ʽ
				if (strcmp(ex_book->Info.UserID, user_id) != 0) {
					Call_Promote("�û�����ƥ��.");
					return;
				}

				switch ((*ex_book).Info.Status){
					case BK_Reserved: 
						(*bk_manage).BookReserved --;
						break;
					case BK_Borrowed:
						(*bk_manage).BookBorrowed --;
						break;
				}
				(*ex_book).Info.Status = BK_Avaliable;

				user->DelRelativeRecord(user, ex_book->Info.BookID); //ɾ�û���¼

				strcpy((*ex_book).Info.UserID, "nil");
				(*ex_book).Info.BorrowDATE = (DateEx){0,0,0,0};
				(*ex_book).Info.ReturnDATE = (DateEx){0,0,0,0};				
			}

			// ע�ᣬ��Ӧvoid (*Regist)
			void regist_book( BookEx *ex_book,
				BKManage *bk_manage  //����ṹ
			){
				if ((*ex_book).Info.BookID > 0){
					Call_Promote("�ظ�ע�����鼮.");
				}
				else{
					(*bk_manage).LastBookID ++;
					(*bk_manage).BooksStored ++;
					(*ex_book).Info.BookID = bk_manage -> LastBookID;
				}
			}

			// ���٣���Ӧvoid (*Destory)
			void destory_book( BookEx *ex_book,
				BKManage *bk_manage  //����ṹ
			){
				if ((*ex_book).Info.BookID > 0)
					(*bk_manage).BooksStored --;
				if (ex_book -> Previous != NULL)
					ex_book -> Previous -> Next = ex_book -> Next;
				if (ex_book -> Next != NULL)
					ex_book -> Next -> Previous = ex_book -> Previous;

				//�ر�Դ��������ݿ��е�ǰ��ΪNULL�����
				if (ex_book->Previous == ex_book->Next 
					&& ex_book->Info.BookID > 0
				){
					Call_Promote("Ϊ��֤���ݿ��ȶ��ԣ��㲻��ɾ�����һ����¼.");
					return;
				}
				
				free(ex_book);
			}


			// 2. ���ò���
			//    ���ò��ֵ���ʹ��

			// �½�һ��Book������ָ��
			Book *NewBook(
				//������Ϣ
				char *Title,  //����
				char *Author,  //����
				char *Press,  //������
				char *ISBNcode,  //ISBN
				DateEx PublicationDATE, //��������
				//������Ϣ
				char *KeyWord,  //�ؼ���
				char *Class  //���ࣨС˵����ѧ�ȣ�
			){
				Book *temp = (Book*)malloc(sizeof(Book));  //����ռ�

				//����ճ��
				strcpy((*temp).Title, Title); strcpy((*temp).Author, Author);
				strcpy((*temp).Press, Press); strcpy((*temp).ISBNcode, ISBNcode);
				(*temp).PublicationDATE = PublicationDATE; strcpy((*temp).KeyWord, KeyWord);
				strcpy((*temp).Class, Class); 

				(*temp).Stars = (*temp).TotalBorrow = 0;

				(*temp).BookID = 0; //���0����δע��
				(*temp).Status = 0;
				strcpy((*temp).UserID, "nil"); 
				(*temp).BorrowDATE = (*temp).ReturnDATE = (DateEx){0,0,0,0};

				return temp;
			}

			// �½�һ��BookEx������ָ��
			BookEx *NewBookEx(Book bookinfo)
			{
				BookEx *temp = (BookEx*)malloc(sizeof(BookEx));
				
				(*temp).Info = bookinfo;

				(*temp).Previous = (*temp).Next = NULL;

				(*temp).Like = like_book;
				(*temp).Borrow = borrow_book; 
				(*temp).Reserve = reserve_book;
				(*temp).Renew = renew_book;
				(*temp).Return = return_book;
				(*temp).Regist = regist_book;
				(*temp).Destory = destory_book;

				return temp;
			}

			// �ҵ�����ͷ
			BookEx* GoToHead(BookEx* here) {
				if (here->Previous == NULL)
					return here;
				else
					return GoToHead(here->Previous);
			}
			// �ҵ�����β
			BookEx* GoToEnd(BookEx* here) {
				if (here->Next == NULL)
					return here;
				else
					return GoToEnd(here->Next);
			}




/* �û��ⲿ�� */
/* ----- DB_User ----- */
/* ----- ver 0.0.1 ----- */

/*  < ���� >
 *  ���ģ�鶨�����û����ݽṹ�뷽����
 *  �������װ��αoop����
 *  �ṩ�û����ݵĴ�����ʹ�÷���
 */

#include "DBSecurity.h"

 /*
 #define MAX_Borrow 30 //һ���û������Խ��ĵ��鼮��


 // �����鼮�ṹ
 typedef struct simplified_book
 {
	 char Title[64];  //����
	 char Author[48];  //���ߣ����ж��ʱ��"/"�Ͽ���
	 char Press[48];  //������

	 unsigned int BookID;  //Ψһ���
	 unsigned int Status : 2;  //����״̬���У�����(0)������(1)��Ԥ��(2)��3����
	 DateEx BorrowDATE;  //����/Ԥ������
	 DateEx ReturnDATE;  //Ӧ������/Ԥ����������
 }S_Book;



 // �û���Ϣ�ṹ
 typedef struct userinfo_item {

	 unsigned int UserID; //�û�ID�������� **��˵����ͼ����ʱ������ֵ���ó�char[24]�ˣ���ͼ���Ƚ��鷳�����õ�ʱ����һ����ֵת������
	 unsigned char UserName[64]; //�û��ǳ�

	 //����
	 unsigned char Salt[16]; //�������ã������
	 unsigned char Password[64]; //����
	 // �û�δ��¼ʱ����������ģ�
	 // ��¼ʱ��Ϊ���ģ�
	 // �û��˳�ʱ���������β����ܣ�
	 // ͬʱ������"\0"����δʹ�õĲ��������������
	 // ���ܷ����ο�����ʾ��

	 unsigned char gender; //�Ա�F��M��S�����ܣ�
	 unsigned char orgnization[128]; //������λ

	 unsigned int bookRelated; //��ǰ�Ľ���/Ԥ��������>=0��������ȷ��relativeBookList������±�
	 S_Book relativeBookList[MAX_Borrow]; //������Ϣ�������ֻ�Ǽ�����Ϣ������������������ҵ�ȫ����Ϣ��
 }UserInfo;



 // ��װ������αoop�û��ṹ
 typedef struct user_oop_item User;
 struct user_oop_item {
	 UserInfo Info; //�û���Ϣ

	 //��������
	 User* Previous;
	 User* Next;

	 //��¼�ǳ�
	 int (*Login)(User* This, unsigned char* password); //�������¼����˺ţ�ʵ�����Ǽ��������ȷ�ԣ�,����1�ɹ���0ʧ��
	 void (*Logout)(User* This); //�ǳ���������ֵ�����м���

	 //��/����
	 void (*AddRelativeRecord)(User* This, BookEx* book); //��¼һ������鼮��Ϣ(���������BookEX��Borrow��ʹ�ã�Borrowʱ�����޸ĺ�BookEx���������ʹ�ñ�����)
	 void (*DelRelativeRecord)(User* This, unsigned int bookID); //ɾ��һ������鼮��Ϣ�����ն�Ӧ��Ų���(���������BookEX��Return��ʹ��)
	 //void (*ShowRelativeList)(User* This, DB_Book* book_db);//�鿴����鼮��Ϣ

	 //�޸��û���Ϣ
	 void (*AlterPassword)(User* This, unsigned char* previous_password, unsigned char* new_password);//�޸����룬previous_password����֤��
	 void (*AlterOtherInfo)(User* This, User* new_info);//�޸�������Ϣ���̳г�����ͽ���Ŀ¼����ֶ�
 };*/

 // ����ṹʹ�õķ���

	 //1. ������

	 /* ���ܲ����㷨�������û���Ϣ�ڵ������Ƿ��Ѿ����ܣ�
	  * ��δ���ܵ������ˢ���λ����ظ�����/���ܿ��ܵ������ݶ�ʧ��
	  * ����ʹ����Щ������ʱ���ȷ�����ݵİ�ȫ��
	  */

	  //���⡿ˢ����ֵ
			void GenerateSalt(User* user) {
				SYSTEMTIME systime = { 0 };
				GetLocalTime(&systime);  //��ȡ��ǰʱ��
				unsigned int seed;
				seed = (unsigned)(systime.wMilliseconds + 1000 * systime.wSecond);
				srand(seed);  //����ʱ��ˢ�����������

				GetLocalTime(&systime);
				int i;
				for (i = 0; i <= systime.wMilliseconds; i++)
					rand();  //�������ǰn����

				for (i = 0; i < 16; i++)
					user->Info.Salt[i] = (unsigned char)(rand() % 256);
				//�������ȡ��ԭ������
			}

			//���⡿�������루���滻ԭ�ģ�
			void EncryptPassword(User* user, unsigned char* password) {
				//�ȼ�������Ƿ���ȷ�������ܵ����뱾��Ҳ�Ǽ��ܵ���Կ���������ͨ����Կ������������֤Կ�׵���ȷ�ԣ�
				//���������Ҫ���ܵ�ԭ�Ĳ�ͬ���������ظ����ܻ������벻��ȷ
				if (strcmp(password, user->Info.Password)) {
					Call_Warning("���벻��ȷ�������ظ�����.");
					return;
				}

				int i;
				unsigned char SEA_buffer[64];
				unsigned char MD5_buffer[16];
				unsigned char SALT_buffer[16];

				//����ԭ��
				SEA_Encrypt(user->Info.Salt, user->Info.Password, 64, SEA_buffer);
				//�������滻ԭ��
				for (i = 0; i < 64; i++)
					user->Info.Password[i] = SEA_buffer[i];

				//������
				GenerateMD(password, strlen(password), MD5_buffer);
				SEA_Encrypt(MD5_buffer, user->Info.Salt, 16, SALT_buffer);
				//�������滻ԭ��
				for (i = 0; i < 16; i++)
					user->Info.Salt[i] = SALT_buffer[i];
			}

			//���⡿�������ģ�����������������Ľ��ܵĽ�����output_buffer�����жϽ�õ�ԭ���Ƿ���ȷ��
			// output_buffer����Ҫ64�ֽڣ�������ı�ԭ�ģ�
			void DecryptPassword(User* user, unsigned char* password, unsigned char* output_buffer) {
				int i;
				unsigned char MD5_buffer[16];
				unsigned char SALT_buffer[16];
				//������Կ��MD5
				GenerateMD(password, strlen(password), MD5_buffer);
				//����
				SEA_Decrypt(MD5_buffer, user->Info.Salt, 16, SALT_buffer);
				//������
				SEA_Decrypt(SALT_buffer, user->Info.Password, 64, output_buffer);
			}

			//2. ��¼�ǳ�

			//���ڡ���¼��ʵ�����Ǽ��������ȷ�ԣ�,����1�ɹ���0ʧ�ܣ���Ӧ int (*Login)
			int login_user(User* user, unsigned char* password) {
				unsigned char  buffer[64]; int i;
				DecryptPassword(user, password, buffer);

				//���������󣬽��ܵõ����ַ�������û�н�������������ȷ�Ͻ������Ƿ����
				for (i = 0; i < 64; i++) {
					if (buffer[i] == 0)
						goto ContinueProcLogin;  //��������XD
				}
				return 0; //���û�д���goto����ô�ͻᴥ������������

				//����goto��������
			ContinueProcLogin:
				if (strcmp(password, buffer) == 0) {
					strcpy(user->Info.Password, buffer); //�����뻻Ϊ����
					return 1;
				}
				else {
					return 0;
				}
			}

			//���ڡ��ǳ�����Ӧvoid (*Logout)(User* This)
			void logout_user(User* user) {
				unsigned char  buffer[64]; int i;
				//�ȼ����������û��\0����Ϊ������Ҫ�������ַ�������
				//�������м���û��\0��������\0����֤����ǰ��δ��¼���Ա����ظ����ܵ��¶�ʧ������Ϣ
				for (i = 0; i < 64; i++) {
					if (user->Info.Password[i] == 0)
						goto ContinueProcLogout;  //��������XD
				}
				Call_Error("���ܵǳ�δ��¼���˻�.");
				return; //���û�д���goto����ô�ͻᴥ���������������

				//����goto��������
			ContinueProcLogout:
				strcpy(buffer, user->Info.Password);
				GenerateSalt(user); //���µ����滻ԭ������
				EncryptPassword(user, buffer);
			}

			//3. ����/����

			//���ڡ���Ӽ�¼����Ӧ void (*AddRelativeRecord)
			void add_rela_rec(User* user, BookEx* book) {
				//���ǰ�BookEx������ݿ�������
				int pos = (user->Info.bookRelated++);
				S_Book tmp;
				strcpy(tmp.Title, book->Info.Title);
				strcpy(tmp.Author, book->Info.Author);
				strcpy(tmp.Press, book->Info.Press);
				tmp.Status = book->Info.Status;
				tmp.BookID = book->Info.BookID;
				tmp.BorrowDATE = book->Info.BorrowDATE;
				tmp.ReturnDATE = book->Info.ReturnDATE;
				user->Info.relativeBookList[pos] = tmp;
			}

			//���ڡ�ɾ����¼����Ӧ void (*DelRelativeRecord)
			void del_rela_rec(User* user, unsigned int bookID) {
				//����û�û�н��ļ�¼
				if (user->Info.bookRelated <= 0) {
					Call_Warning("���û�û�н��ļ�¼.");
					return;
				}

				int i, j;
				for (i = 0; i < user->Info.bookRelated; i++) {
					if (user->Info.relativeBookList[i].BookID == bookID)
						goto ContinueProcDelRec;
				}
				Call_Warning("��ѡ�û�û����Ӧ�鼮�Ľ��ļ�¼.");
				return; //goto��ԭ�������һ��

			ContinueProcDelRec:
				for (j = i + 1; j < user->Info.bookRelated; j++)
					user->Info.relativeBookList[j - 1] = user->Info.relativeBookList[j];
				user->Info.bookRelated--;
			}

			//4. �޸��û���Ϣ

			//���ڡ��޸����룬��Ӧ void (*AlterPassword)
			void alt_password(User* user, unsigned char* previous_password, unsigned char* new_password) {
				//������
			}

			//���ڡ��޸���Ϣ����Ӧ void (*AlterOtherInfo)
			void alt_user_info(User* This, User* new_info) {
				//������
			}


			// �������������ṹ

			//�½��û��ṹ
			User* NewUser(UserInfo info) {
				User* tmp = (User*)malloc(sizeof(User));
				tmp->Info = info;
				tmp->Login = login_user; tmp->Logout = logout_user;
				tmp->AddRelativeRecord = add_rela_rec; tmp->DelRelativeRecord = del_rela_rec;
				tmp->AlterPassword = alt_password; tmp->AlterOtherInfo = alt_user_info;
				tmp->Next = tmp->Previous = NULL;

				return tmp;
			}


			// ����

			//������ת�ַ���������buff
			void TransToStr(unsigned int from, char* buff) {
				if (from == 0) { //���ԭ���־���0
					buff[0] = '0'; buff[1] = 0;
					return;
				}

				int i = 0;
				while (from > 0) { //���ɷ�д������
					buff[i] = from % 10 + '0';
					from /= 10; i++;
				}
				buff[i] = 0;
				char tmp; int j = 0;
				i--;
				while (i > j) { //�������
					tmp = buff[i]; buff[i] = buff[j]; buff[j] = tmp;
					i--; j++;
				}
			}

			//���ַ���תΪ����
			unsigned int TransToInt(char* from) {
				unsigned int res = 0; int i = 0;
				while (from[i] != 0) {
					res = res * 10 + (from[i] - '0');
					i++;
				}
				return res;
			}