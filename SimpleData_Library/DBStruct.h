#ifndef DB_STRUCT_H
#define DB_STRUCT_H

typedef struct user_oop_item User;

//日期拓展结构
typedef struct expand_date_item
{
	unsigned int Year : 12;  //年份：0~4095
	unsigned int Month : 4;  //月：0~15
	unsigned int Day : 5;  //日期：0~31
	unsigned int Mark : 3;  //备注（随便凑个数凑齐3字节）
} DateEx; 

//图书管理结构
typedef struct book_management_item
{
	//数据库信息
	unsigned int BooksStored;  //收录书籍总数
	unsigned int BookBorrowed;  //借阅中总数
	unsigned int BookReserved;  //预定中总数
	unsigned int LastBookID;  //最新书号，注册新书时，新书书号为该号码 +1

	//统计
	unsigned int TotalBookBorrowed;  //总借阅数
	unsigned int TotalBookReserved;  //总预定数
} BKManage;

//单个书籍结构
typedef struct book_item
{
	//基本信息
	char Title[64];  //书名
	char Author[48];  //作者（当有多个时用"/"断开）
	char Press[48];  //出版社
	char ISBNcode[24];  //ISBN
	DateEx PublicationDATE; //出版日期

	//分类信息
	char KeyWord[32];  //关键词（当有多个时用"/"断开）
	char Class[24];  //分类（小说、科学等）（当有多个时用"/"断开）

	//用户信息
	int Stars;  //点赞数
	int TotalBorrow;  //总借阅数

	//馆藏信息
	unsigned int BookID;  //唯一书号
	unsigned int Status : 2;  //借阅状态，有：空闲(0)，借走(1)，预定(2)，3保留
	char UserID[24];  //借阅/预定者编号
	DateEx BorrowDATE;  //借阅/预定日期
	DateEx ReturnDATE;  //应还日期/预定到期日期
} Book;

//可以形成链表并封装了方法的书籍结构
typedef struct expand_book_item BookEx;
struct expand_book_item
{
	//图书信息
	Book Info;

	//组成链表用
	BookEx *Previous;
	BookEx *Next;

	//方法
	//c语言不能内置结构函数，初始化时记得激活这些指针
	void (*Like)(BookEx *This);  //点赞此书
	void (*Borrow)(BookEx *This,  //借阅此书
		BKManage *bk_manage,  //管理结构
		User* user,  //借书者的用户结构
		DateEx borrow_date  //借阅日期
		);  //每次借阅应默认在30天后归还
	void (*Reserve)(BookEx *This,  //预定此书
		BKManage *bk_manage,  //管理结构
		User* user,  //借书者的用户结构
		DateEx borrow_date  //预定日期
		);
	void (*Renew)(BookEx *This, User* user);  //续借此书
	void (*Return)(BookEx *This,  //归还此书
		User* user,  //借书者的用户结构
		BKManage *bk_manage  //管理结构
		);
	void (*Regist)(BookEx *This,  //注册此书
		BKManage *bk_manage  //管理结构
		);  //该函数向管理结构申请一个新的书号
	void (*Destory)(BookEx *This,  //销毁此书
		BKManage *bk_manage  //管理结构
		);
};

//获取当前日期结构所在月的天数
int Day_of_Month(DateEx date_input);
//日期加法
DateEx DateAdd(DateEx date_input, int day_input); 

//检查BKManage完整性，返回0完整，返回1缺损
int BKM_CheckIntegrity(BKManage* book_manage);

#define BK_Avaliable 0  
#define BK_Borrowed  1
#define BK_Reserved  2

// 点赞，对应void (*Like)
void like_book(BookEx *ex_book); 
// 借阅，对应void (*Borrow)
void borrow_book(BookEx *ex_book, BKManage *bk_manage, User* user, DateEx borrow_date);
// 预定，对应void (*Reserve)
void reserve_book(BookEx *ex_book, BKManage *bk_manage, User* user, DateEx borrow_date);
// 续借，对应void (*Renew)
void renew_book(BookEx *ex_book, User* user);
// 归还，对应void (*Return)
void return_book(BookEx *ex_book, User* user, BKManage *bk_manage);
// 注册，对应void (*Regist)
void regist_book( BookEx *ex_book, BKManage *bk_manage);
// 销毁，对应void (*Destory)
void destory_book( BookEx *ex_book, BKManage *bk_manage); 

// 新建一个Book，返回指针
Book *NewBook(char *Title, char *Author, char *Press, char *ISBNcode, DateEx PublicationDATE,
			  char *KeyWord, char *Class);
// 新建一个BookEx，返回指针
BookEx *NewBookEx(Book bookinfo); 
// 找到链表头
BookEx* GoToHead(BookEx* here);
// 找到链表尾
BookEx* GoToEnd(BookEx* here);




#define MAX_Borrow 30 //一个用户最大可以借阅的书籍数


// 精简书籍结构
typedef struct simplified_book
{
	char Title[64];  //书名
	char Author[48];  //作者（当有多个时用"/"断开）
	char Press[48];  //出版社

	unsigned int BookID;  //唯一书号
	unsigned int Status : 2;  //借阅状态，有：空闲(0)，借走(1)，预定(2)，3保留
	DateEx BorrowDATE;  //借阅/预定日期
	DateEx ReturnDATE;  //应还日期/预定到期日期
}S_Book;



// 用户信息结构
typedef struct userinfo_item {

	unsigned int UserID; //用户ID（主键） **话说在做图书库的时候把这个值设置成char[24]了，修图书库比较麻烦还是用的时候做一下数值转换好了
	unsigned char UserName[64]; //用户昵称

	//密码
	unsigned char Salt[16]; //（加密用）随机盐
	unsigned char Password[64]; //密码
	/* 用户未登录时储存的是密文，
	 * 登录时解为明文，
	 * 用户退出时重新生成盐并加密，
	 * 同时将密码"\0"后面未使用的部分用随机数覆盖
	 * 加密方法参考加密示意 */

	unsigned char gender; //性别，F，M，S（保密）
	unsigned char orgnization[128]; //工作单位

	unsigned int bookRelated; //当前的借阅/预定书数（>=0），用来确定relativeBookList的最大下标
	S_Book relativeBookList[MAX_Borrow]; //借阅信息（这里就只记简略信息，可以搜索书库主键找到全部信息）
}UserInfo;



// 封装出来的伪oop用户结构
struct user_oop_item {
	UserInfo Info; //用户信息

	//成链表用
	User* Previous;
	User* Next;

	//登录登出
	int (*Login)(User* This, unsigned char* password); //用密码登录这个账号（实际上是检测密码正确性）,返回1成功，0失败
	void (*Logout)(User* This); //登出，重置盐值并进行加密

	//借/还书
	void (*AddRelativeRecord)(User* This, BookEx* book); //记录一条相关书籍信息(这个函数在BookEX的Borrow里使用，Borrow时请先修改好BookEx里的数据再使用本函数)
	void (*DelRelativeRecord)(User* This, unsigned int bookID); //删除一条相关书籍信息，按照对应书号查找(这个函数在BookEX的Return里使用)
	//void (*ShowRelativeList)(User* This, DB_Book* book_db);//查看相关书籍信息

	//修改用户信息
	void (*AlterPassword)(User* This, unsigned char* previous_password, unsigned char* new_password);//修改密码，previous_password作验证用
	void (*AlterOtherInfo)(User* This, User* new_info);//修改其他信息，继承除密码和借阅目录外的字段
};

//【外】刷新盐值
void GenerateSalt(User* user);
//【外】加密密码（会替换原文）
void EncryptPassword(User* user, unsigned char* password);
//【外】解密密文（这个函数仅仅把密文解密的结果输出output_buffer，不判断解得的原文是否正确）
// output_buffer至少要64字节！（不会改变原文）
void DecryptPassword(User* user, unsigned char* password, unsigned char* output_buffer);
// 【内】登录（实际上是检测密码正确性）, 返回1成功，0失败，对应 int(*Login)
int login_user(User* user, unsigned char* password);
//【内】登出，对应void (*Logout)(User* This)
void logout_user(User* user);
//【内】添加记录，对应 void (*AddRelativeRecord)
void add_rela_rec(User* user, BookEx* book);
//【内】删除记录，对应 void (*DelRelativeRecord)
void del_rela_rec(User* user, unsigned int bookID);
//【内】修改密码，对应 void (*AlterPassword)
void alt_password(User* user, unsigned char* previous_password, unsigned char* new_password);
//【内】修改信息，对应 void (*AlterOtherInfo)
void alt_user_info(User* This, User* new_info);

//新建用户结构
User* NewUser(UserInfo info);

// 附带

//将数字转字符串，传到buff
void TransToStr(unsigned int from, char* buff);
//将字符串转为数字
unsigned int TransToInt(char* from);


#endif
