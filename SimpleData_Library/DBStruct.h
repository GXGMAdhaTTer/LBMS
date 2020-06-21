#ifndef DB_STRUCT_H
#define DB_STRUCT_H

typedef struct user_oop_item User;

//������չ�ṹ
typedef struct expand_date_item
{
	unsigned int Year : 12;  //��ݣ�0~4095
	unsigned int Month : 4;  //�£�0~15
	unsigned int Day : 5;  //���ڣ�0~31
	unsigned int Mark : 3;  //��ע�����ո�������3�ֽڣ�
} DateEx; 

//ͼ�����ṹ
typedef struct book_management_item
{
	//���ݿ���Ϣ
	unsigned int BooksStored;  //��¼�鼮����
	unsigned int BookBorrowed;  //����������
	unsigned int BookReserved;  //Ԥ��������
	unsigned int LastBookID;  //������ţ�ע������ʱ���������Ϊ�ú��� +1

	//ͳ��
	unsigned int TotalBookBorrowed;  //�ܽ�����
	unsigned int TotalBookReserved;  //��Ԥ����
} BKManage;

//�����鼮�ṹ
typedef struct book_item
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

//�����γ�������װ�˷������鼮�ṹ
typedef struct expand_book_item BookEx;
struct expand_book_item
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
		User* user,  //�����ߵ��û��ṹ
		DateEx borrow_date  //��������
		);  //ÿ�ν���ӦĬ����30���黹
	void (*Reserve)(BookEx *This,  //Ԥ������
		BKManage *bk_manage,  //����ṹ
		User* user,  //�����ߵ��û��ṹ
		DateEx borrow_date  //Ԥ������
		);
	void (*Renew)(BookEx *This, User* user);  //�������
	void (*Return)(BookEx *This,  //�黹����
		User* user,  //�����ߵ��û��ṹ
		BKManage *bk_manage  //����ṹ
		);
	void (*Regist)(BookEx *This,  //ע�����
		BKManage *bk_manage  //����ṹ
		);  //�ú��������ṹ����һ���µ����
	void (*Destory)(BookEx *This,  //���ٴ���
		BKManage *bk_manage  //����ṹ
		);
};

//��ȡ��ǰ���ڽṹ�����µ�����
int Day_of_Month(DateEx date_input);
//���ڼӷ�
DateEx DateAdd(DateEx date_input, int day_input); 

//���BKManage�����ԣ�����0����������1ȱ��
int BKM_CheckIntegrity(BKManage* book_manage);

#define BK_Avaliable 0  
#define BK_Borrowed  1
#define BK_Reserved  2

// ���ޣ���Ӧvoid (*Like)
void like_book(BookEx *ex_book); 
// ���ģ���Ӧvoid (*Borrow)
void borrow_book(BookEx *ex_book, BKManage *bk_manage, User* user, DateEx borrow_date);
// Ԥ������Ӧvoid (*Reserve)
void reserve_book(BookEx *ex_book, BKManage *bk_manage, User* user, DateEx borrow_date);
// ���裬��Ӧvoid (*Renew)
void renew_book(BookEx *ex_book, User* user);
// �黹����Ӧvoid (*Return)
void return_book(BookEx *ex_book, User* user, BKManage *bk_manage);
// ע�ᣬ��Ӧvoid (*Regist)
void regist_book( BookEx *ex_book, BKManage *bk_manage);
// ���٣���Ӧvoid (*Destory)
void destory_book( BookEx *ex_book, BKManage *bk_manage); 

// �½�һ��Book������ָ��
Book *NewBook(char *Title, char *Author, char *Press, char *ISBNcode, DateEx PublicationDATE,
			  char *KeyWord, char *Class);
// �½�һ��BookEx������ָ��
BookEx *NewBookEx(Book bookinfo); 
// �ҵ�����ͷ
BookEx* GoToHead(BookEx* here);
// �ҵ�����β
BookEx* GoToEnd(BookEx* here);




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
	/* �û�δ��¼ʱ����������ģ�
	 * ��¼ʱ��Ϊ���ģ�
	 * �û��˳�ʱ���������β����ܣ�
	 * ͬʱ������"\0"����δʹ�õĲ��������������
	 * ���ܷ����ο�����ʾ�� */

	unsigned char gender; //�Ա�F��M��S�����ܣ�
	unsigned char orgnization[128]; //������λ

	unsigned int bookRelated; //��ǰ�Ľ���/Ԥ��������>=0��������ȷ��relativeBookList������±�
	S_Book relativeBookList[MAX_Borrow]; //������Ϣ�������ֻ�Ǽ�����Ϣ������������������ҵ�ȫ����Ϣ��
}UserInfo;



// ��װ������αoop�û��ṹ
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
};

//���⡿ˢ����ֵ
void GenerateSalt(User* user);
//���⡿�������루���滻ԭ�ģ�
void EncryptPassword(User* user, unsigned char* password);
//���⡿�������ģ�����������������Ľ��ܵĽ�����output_buffer�����жϽ�õ�ԭ���Ƿ���ȷ��
// output_buffer����Ҫ64�ֽڣ�������ı�ԭ�ģ�
void DecryptPassword(User* user, unsigned char* password, unsigned char* output_buffer);
// ���ڡ���¼��ʵ�����Ǽ��������ȷ�ԣ�, ����1�ɹ���0ʧ�ܣ���Ӧ int(*Login)
int login_user(User* user, unsigned char* password);
//���ڡ��ǳ�����Ӧvoid (*Logout)(User* This)
void logout_user(User* user);
//���ڡ���Ӽ�¼����Ӧ void (*AddRelativeRecord)
void add_rela_rec(User* user, BookEx* book);
//���ڡ�ɾ����¼����Ӧ void (*DelRelativeRecord)
void del_rela_rec(User* user, unsigned int bookID);
//���ڡ��޸����룬��Ӧ void (*AlterPassword)
void alt_password(User* user, unsigned char* previous_password, unsigned char* new_password);
//���ڡ��޸���Ϣ����Ӧ void (*AlterOtherInfo)
void alt_user_info(User* This, User* new_info);

//�½��û��ṹ
User* NewUser(UserInfo info);

// ����

//������ת�ַ���������buff
void TransToStr(unsigned int from, char* buff);
//���ַ���תΪ����
unsigned int TransToInt(char* from);


#endif
