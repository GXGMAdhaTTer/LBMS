#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "DBGeneral.h"

#include "DBStruct.h"

/* 图书库部分 */
/* ----- DB_Struct ----- */
/* ----- ver 0.0.1 ----- */

/*  < 介绍 >
 *  这个模块定义了数据库所需的文件结构与方法，
 *  并将其封装成伪oop对象
 *
 *
 *  ———— 人类的本质是套娃。
 *
 *  P.S.结构体定义在对应的.h文件里
 */


/* -- 日期结构 -- */

	// 定义日期结构
		//结构体
		/*typedef struct expand_date_item
		{
			unsigned int Year : 12;  //年份：0~4095
			unsigned int Month : 4;  //月：0~15
			unsigned int Day : 5;  //日期：0~31
			unsigned int Mark : 3;  //备注（随便凑个数凑齐3字节）
		}DateEx;*/

		//方法
			//获取当前日期结构所在月的天数
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

			//日期加法
			DateEx DateAdd(DateEx date_input, int day_input){
				//计算几天之后的日期
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


/* -- 管理结构 -- */

	// 定义管理结构

		/*
		 *  管理结构记录了数据库的总体信息，
		 *  以便在为书籍注册唯一书号时使用
		 */

		// 结构体
		/*typedef struct book_management_item
		{
			//数据库信息
			unsigned int BooksStored;  //收录书籍总数
			unsigned int BookBorrowed;  //借阅中总数
			unsigned int BookReserved;  //预定中总数
			unsigned int LastBookID;  //最新书号，注册新书时，新书书号为该号码 +1

			//统计
			unsigned int TotalBookBorrowed;  //总借阅数
			unsigned int TotalBookReserved;  //总预定数
		} BKManage;*/

		// 外置方法
		//检查BKManage完整性，返回0完整，返回1缺损
		int BKM_CheckIntegrity(BKManage* book_manage) {
			if (book_manage->BooksStored > book_manage->LastBookID) { Call_Warning("数据库头可能不完整."); return 1; }
			if (book_manage->BookReserved > book_manage->BooksStored) { Call_Warning("数据库头可能不完整."); return 1; }
			if (book_manage->BookBorrowed > book_manage->BooksStored) { Call_Warning("数据库头可能不完整."); return 1; }
			return 0;
		}


/* -- 书籍结构 -- */

	//typedef struct expand_book_item BookEx;

	// 定义书籍信息结构
		// 结构体
		/*typedef struct book_item
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

		// 对应数据
		#define BK_Avaliable 0  // 定义借阅状态
		#define BK_Borrowed  1
		#define BK_Reserved  2*/

	// 拓展图书结构，
	// 实现伪oop操作，同时它有前后两个指针以便组成双向链表
		// 结构体
		/*typedef struct expand_book_item
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
				User *user,  //借书者的用户结构
				DateEx borrow_date  //借阅日期
				);  //每次借阅应默认在30天后归还
			void (*Reserve)(BookEx *This,  //预定此书
				BKManage *bk_manage,  //管理结构
				User *user,  //借书者的用户结构
				DateEx borrow_date  //预定日期
				);
			void (*Renew)(BookEx *This, User *user);  //续借此书
			void (*Return)(BookEx *This,  //归还此书
				User *user,  //借书者的用户结构
				BKManage *bk_manage  //管理结构
				);
			void (*Regist)(BookEx *This,  //注册此书
				BKManage *bk_manage  //管理结构
				);  //该函数向管理结构申请一个新的书号
			void (*Destory)(BookEx *This,  //销毁此书
				BKManage *bk_manage  //管理结构
				);
		} BookEx;*/

		// 结构方法
			// 1. 内嵌部分
			//    内嵌部分的每一个函数对应结构体的一个指针

			// 点赞，对应void (*Like)
			void like_book( BookEx *ex_book){
				(ex_book -> Info).Stars ++;
			}

			// 借阅，对应void (*Borrow)
			void borrow_book( BookEx *ex_book,
				BKManage *bk_manage,  //管理结构
				User *user,  //借书者的用户结构
				DateEx borrow_date  //借阅日期
			){	//每次借阅应默认在30天后归还
				char user_id[24];
				TransToStr(user->Info.UserID, user_id); //历史遗留问题，转换格式

				//写图书对象的记录
				(*ex_book).Info.Status = BK_Borrowed;
				strcpy((*ex_book).Info.UserID, user_id);
				(*ex_book).Info.BorrowDATE = borrow_date;
				(*ex_book).Info.ReturnDATE = DateAdd(borrow_date, 30);

				(*ex_book).Info.TotalBorrow ++;
				(*bk_manage).BookBorrowed ++;
				(*bk_manage).TotalBookBorrowed ++;

				//写用户对象的记录
				user->AddRelativeRecord(user, ex_book);
			}

			// 预定，对应void (*Reserve)
			void reserve_book( BookEx *ex_book,  //预定此书
				BKManage *bk_manage,  //管理结构
				User* user,  //借书者的用户结构
				DateEx borrow_date  //预定日期
			){	//默认在30天后归还
				char user_id[24];
				TransToStr(user->Info.UserID, user_id); //历史遗留问题，转换格式

				//写图书对象的记录
				(*ex_book).Info.Status = BK_Reserved;
				strcpy((*ex_book).Info.UserID, user_id);
				(*ex_book).Info.BorrowDATE = borrow_date;
				(*ex_book).Info.ReturnDATE = DateAdd(borrow_date, 30);

				(*bk_manage).BookReserved ++;
				(*bk_manage).TotalBookReserved ++;

				//写用户对象的记录
				user->AddRelativeRecord(user, ex_book);
			}

			// 续借，对应void (*Renew)
			void renew_book(BookEx *ex_book, User* user){
				if ((*ex_book).Info.Status != BK_Borrowed){
					Call_Promote("不能续借未借出的书籍.");
					return;
				}
				//检测用户是否匹配
				char user_id[24];
				TransToStr(user->Info.UserID, user_id); //历史遗留问题，转换格式
				if (strcmp(ex_book->Info.UserID, user_id) != 0) {
					Call_Promote("用户名不匹配.");
					return;
				}

				(*ex_book).Info.ReturnDATE = DateAdd(
					(*ex_book).Info.ReturnDATE, 15);  //续期15天
				user->DelRelativeRecord(user, ex_book->Info.BookID); //删旧记录
				user->AddRelativeRecord(user, ex_book); //写新记录
			}

			// 归还，对应void (*Return)
			void return_book( BookEx *ex_book,  //归还此书
				User* user, //用户
				BKManage *bk_manage  //管理结构
			){
				//检测用户是否匹配
				char user_id[24];
				TransToStr(user->Info.UserID, user_id); //历史遗留问题，转换格式
				if (strcmp(ex_book->Info.UserID, user_id) != 0) {
					Call_Promote("用户名不匹配.");
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

				user->DelRelativeRecord(user, ex_book->Info.BookID); //删用户记录

				strcpy((*ex_book).Info.UserID, "nil");
				(*ex_book).Info.BorrowDATE = (DateEx){0,0,0,0};
				(*ex_book).Info.ReturnDATE = (DateEx){0,0,0,0};				
			}

			// 注册，对应void (*Regist)
			void regist_book( BookEx *ex_book,
				BKManage *bk_manage  //管理结构
			){
				if ((*ex_book).Info.BookID > 0){
					Call_Promote("重复注册了书籍.");
				}
				else{
					(*bk_manage).LastBookID ++;
					(*bk_manage).BooksStored ++;
					(*ex_book).Info.BookID = bk_manage -> LastBookID;
				}
			}

			// 销毁，对应void (*Destory)
			void destory_book( BookEx *ex_book,
				BKManage *bk_manage  //管理结构
			){
				if ((*ex_book).Info.BookID > 0)
					(*bk_manage).BooksStored --;
				if (ex_book -> Previous != NULL)
					ex_book -> Previous -> Next = ex_book -> Next;
				if (ex_book -> Next != NULL)
					ex_book -> Next -> Previous = ex_book -> Previous;

				//特别对待已在数据库中的前后都为NULL的情况
				if (ex_book->Previous == ex_book->Next 
					&& ex_book->Info.BookID > 0
				){
					Call_Promote("为保证数据库稳定性，你不能删除最后一条记录.");
					return;
				}
				
				free(ex_book);
			}


			// 2. 外置部分
			//    外置部分单独使用

			// 新建一个Book，返回指针
			Book *NewBook(
				//基本信息
				char *Title,  //书名
				char *Author,  //作者
				char *Press,  //出版社
				char *ISBNcode,  //ISBN
				DateEx PublicationDATE, //出版日期
				//分类信息
				char *KeyWord,  //关键词
				char *Class  //分类（小说、科学等）
			){
				Book *temp = (Book*)malloc(sizeof(Book));  //申请空间

				//复制粘贴
				strcpy((*temp).Title, Title); strcpy((*temp).Author, Author);
				strcpy((*temp).Press, Press); strcpy((*temp).ISBNcode, ISBNcode);
				(*temp).PublicationDATE = PublicationDATE; strcpy((*temp).KeyWord, KeyWord);
				strcpy((*temp).Class, Class); 

				(*temp).Stars = (*temp).TotalBorrow = 0;

				(*temp).BookID = 0; //书号0代表未注册
				(*temp).Status = 0;
				strcpy((*temp).UserID, "nil"); 
				(*temp).BorrowDATE = (*temp).ReturnDATE = (DateEx){0,0,0,0};

				return temp;
			}

			// 新建一个BookEx，返回指针
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

			// 找到链表头
			BookEx* GoToHead(BookEx* here) {
				if (here->Previous == NULL)
					return here;
				else
					return GoToHead(here->Previous);
			}
			// 找到链表尾
			BookEx* GoToEnd(BookEx* here) {
				if (here->Next == NULL)
					return here;
				else
					return GoToEnd(here->Next);
			}




/* 用户库部分 */
/* ----- DB_User ----- */
/* ----- ver 0.0.1 ----- */

/*  < 介绍 >
 *  这个模块定义了用户数据结构与方法，
 *  并将其封装成伪oop对象，
 *  提供用户数据的储存与使用方法
 */

#include "DBSecurity.h"

 /*
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
	 // 用户未登录时储存的是密文，
	 // 登录时解为明文，
	 // 用户退出时重新生成盐并加密，
	 // 同时将密码"\0"后面未使用的部分用随机数覆盖
	 // 加密方法参考加密示意

	 unsigned char gender; //性别，F，M，S（保密）
	 unsigned char orgnization[128]; //工作单位

	 unsigned int bookRelated; //当前的借阅/预定书数（>=0），用来确定relativeBookList的最大下标
	 S_Book relativeBookList[MAX_Borrow]; //借阅信息（这里就只记简略信息，可以搜索书库主键找到全部信息）
 }UserInfo;



 // 封装出来的伪oop用户结构
 typedef struct user_oop_item User;
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
 };*/

 // 上面结构使用的方法

	 //1. 加密用

	 /* 加密部分算法不会检测用户信息内的密码是否已经解密，
	  * 在未解密的情况下刷新盐或者重复加密/解密可能导致数据丢失，
	  * 请在使用这些函数的时候就确保数据的安全性
	  */

	  //【外】刷新盐值
			void GenerateSalt(User* user) {
				SYSTEMTIME systime = { 0 };
				GetLocalTime(&systime);  //获取当前时间
				unsigned int seed;
				seed = (unsigned)(systime.wMilliseconds + 1000 * systime.wSecond);
				srand(seed);  //按照时间刷新随机数种子

				GetLocalTime(&systime);
				int i;
				for (i = 0; i <= systime.wMilliseconds; i++)
					rand();  //随机抛弃前n个数

				for (i = 0; i < 16; i++)
					user->Info.Salt[i] = (unsigned char)(rand() % 256);
				//用随机数取代原来的盐
			}

			//【外】加密密码（会替换原文）
			void EncryptPassword(User* user, unsigned char* password) {
				//先检查密码是否正确（被加密的密码本身也是加密的密钥，这个方法通过把钥匙锁门里来验证钥匙的正确性）
				//如果密码与要加密的原文不同，可能是重复加密或者密码不正确
				if (strcmp(password, user->Info.Password)) {
					Call_Warning("密码不正确或发生了重复加密.");
					return;
				}

				int i;
				unsigned char SEA_buffer[64];
				unsigned char MD5_buffer[16];
				unsigned char SALT_buffer[16];

				//加密原文
				SEA_Encrypt(user->Info.Salt, user->Info.Password, 64, SEA_buffer);
				//用密文替换原文
				for (i = 0; i < 64; i++)
					user->Info.Password[i] = SEA_buffer[i];

				//加密盐
				GenerateMD(password, strlen(password), MD5_buffer);
				SEA_Encrypt(MD5_buffer, user->Info.Salt, 16, SALT_buffer);
				//用密文替换原文
				for (i = 0; i < 16; i++)
					user->Info.Salt[i] = SALT_buffer[i];
			}

			//【外】解密密文（这个函数仅仅把密文解密的结果输出output_buffer，不判断解得的原文是否正确）
			// output_buffer至少要64字节！（不会改变原文）
			void DecryptPassword(User* user, unsigned char* password, unsigned char* output_buffer) {
				int i;
				unsigned char MD5_buffer[16];
				unsigned char SALT_buffer[16];
				//生成密钥的MD5
				GenerateMD(password, strlen(password), MD5_buffer);
				//解盐
				SEA_Decrypt(MD5_buffer, user->Info.Salt, 16, SALT_buffer);
				//解密文
				SEA_Decrypt(SALT_buffer, user->Info.Password, 64, output_buffer);
			}

			//2. 登录登出

			//【内】登录（实际上是检测密码正确性）,返回1成功，0失败，对应 int (*Login)
			int login_user(User* user, unsigned char* password) {
				unsigned char  buffer[64]; int i;
				DecryptPassword(user, password, buffer);

				//如果密码错误，解密得到的字符串可能没有结束符，这里先确认结束符是否存在
				for (i = 0; i < 64; i++) {
					if (buffer[i] == 0)
						goto ContinueProcLogin;  //反复横跳XD
				}
				return 0; //如果没有触发goto，那么就会触发这句结束函数

				//上面goto跳到这里
			ContinueProcLogin:
				if (strcmp(password, buffer) == 0) {
					strcpy(user->Info.Password, buffer); //将密码换为明文
					return 1;
				}
				else {
					return 0;
				}
			}

			//【内】登出，对应void (*Logout)(User* This)
			void logout_user(User* user) {
				unsigned char  buffer[64]; int i;
				//先检查密码里有没有\0，因为加密需要经过半字符交换，
				//在密文中几乎没有\0，不存在\0即可证明当前尚未登录，以避免重复加密导致丢失密码信息
				for (i = 0; i < 64; i++) {
					if (user->Info.Password[i] == 0)
						goto ContinueProcLogout;  //反复横跳XD
				}
				Call_Error("不能登出未登录的账户.");
				return; //如果没有触发goto，那么就会触发这两句结束函数

				//上面goto跳到这里
			ContinueProcLogout:
				strcpy(buffer, user->Info.Password);
				GenerateSalt(user); //用新的盐替换原来的盐
				EncryptPassword(user, buffer);
			}

			//3. 借阅/还书

			//【内】添加记录，对应 void (*AddRelativeRecord)
			void add_rela_rec(User* user, BookEx* book) {
				//就是把BookEx里的数据拷贝过来
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

			//【内】删除记录，对应 void (*DelRelativeRecord)
			void del_rela_rec(User* user, unsigned int bookID) {
				//如果用户没有借阅记录
				if (user->Info.bookRelated <= 0) {
					Call_Warning("该用户没有借阅记录.");
					return;
				}

				int i, j;
				for (i = 0; i < user->Info.bookRelated; i++) {
					if (user->Info.relativeBookList[i].BookID == bookID)
						goto ContinueProcDelRec;
				}
				Call_Warning("所选用户没有相应书籍的借阅记录.");
				return; //goto的原理和上面一样

			ContinueProcDelRec:
				for (j = i + 1; j < user->Info.bookRelated; j++)
					user->Info.relativeBookList[j - 1] = user->Info.relativeBookList[j];
				user->Info.bookRelated--;
			}

			//4. 修改用户信息

			//【内】修改密码，对应 void (*AlterPassword)
			void alt_password(User* user, unsigned char* previous_password, unsigned char* new_password) {
				//完善中
			}

			//【内】修改信息，对应 void (*AlterOtherInfo)
			void alt_user_info(User* This, User* new_info) {
				//完善中
			}


			// 建立上述各个结构

			//新建用户结构
			User* NewUser(UserInfo info) {
				User* tmp = (User*)malloc(sizeof(User));
				tmp->Info = info;
				tmp->Login = login_user; tmp->Logout = logout_user;
				tmp->AddRelativeRecord = add_rela_rec; tmp->DelRelativeRecord = del_rela_rec;
				tmp->AlterPassword = alt_password; tmp->AlterOtherInfo = alt_user_info;
				tmp->Next = tmp->Previous = NULL;

				return tmp;
			}


			// 附带

			//将数字转字符串，传到buff
			void TransToStr(unsigned int from, char* buff) {
				if (from == 0) { //如果原数字就是0
					buff[0] = '0'; buff[1] = 0;
					return;
				}

				int i = 0;
				while (from > 0) { //生成反写的数字
					buff[i] = from % 10 + '0';
					from /= 10; i++;
				}
				buff[i] = 0;
				char tmp; int j = 0;
				i--;
				while (i > j) { //反序回来
					tmp = buff[i]; buff[i] = buff[j]; buff[j] = tmp;
					i--; j++;
				}
			}

			//将字符串转为数字
			unsigned int TransToInt(char* from) {
				unsigned int res = 0; int i = 0;
				while (from[i] != 0) {
					res = res * 10 + (from[i] - '0');
					i++;
				}
				return res;
			}