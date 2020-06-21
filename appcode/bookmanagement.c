#include "bookmanagement.h"
#include "../SimpleData_Library/DBAdmin.h"
#include "../SimpleData_Library/DBGeneral.h"

//myBook info struct
static struct myBook {
	double cx, cy;
	string ISBNcode;
	string Title;
	string Author;
	string Press;
	int Publicationdate;
	string Class;
	string Keywords;
	int State;
	bool isbookinformationshow;
	int collectnum;

	//储存书在数据库里的指针
	BookEx* route;

}GXGBook[10];
char searchKeyword[64] = "";
double stateinterval = 1.2;
bool showbook_flag = 0;
bool isaddbookinformationshow = 0;
int k = 10;//k<=12

//state struct
int pagemax;

//modify status
bool ismodified_Publicationdate = FALSE;
bool ismodified_ISBN = FALSE;
bool ismodified_Title = FALSE;
bool ismodified_Author = FALSE;
bool ismodified_Press = FALSE;
bool ismodified_Class = FALSE;
bool ismodified_Keywords = FALSE;

int flappage = 0;

struct statebutton {
	bool state;
}state_isbn, state_title, state_author, state_keyword, state_filter_isbn, state_filter_title, state_filter_author, iscollect;

//book struct

void bookreserve_page(DB_Book* Library, BKSelect* SLC) {

	SLC = Library->pSelection;

	setTextBoxColors("Light Gray", "Black", "Gray", "Black", 0);
	if (textbox(GenUIID(0), 4, 10, 4.5, 0.5, searchKeyword, sizeof(searchKeyword))) {

	}
	SetPenColor("Black");
	drawLabel(4.5, 9.4, "Search By");
	usePredefinedButtonColors(4);

	//Search Button
	int selected_count;
	if (button(GenUIID(0), 9, 10, buttonWidth, buttonHeight, "Search")) {
		select_status = "";
		showbook_flag = 1;

		//实现查找
		if (searchKeyword[0] != 0) {
			Library->ResetSelection(Library);
			if (state_title.state) {
				selected_count = Library->SelectBy(Library, "Title", searchKeyword, LG_AND);
				Library->SoltSelection(Library);
			}
			else if (state_author.state)
				selected_count = Library->SelectBy(Library, "Author", searchKeyword, LG_AND);
			else if (state_keyword.state)
				selected_count = Library->SelectBy(Library, "Keyword", searchKeyword, LG_AND);
			else
				selected_count = Library->SelectBy(Library, "Title", searchKeyword, LG_AND);//不选择默认Title
			SLC = Library->pSelection;
			if (selected_count > 0) {
				char num[16]; char notic[64] = "找到了";
				TransToStr(selected_count, num);
				strcat(notic, num); strcat(notic, "条结果.");
				Call_Promote(notic);
			}
		}
		else {
			Library->SelectAll(Library);
			SLC = Library->pSelection;
		}
	}

	//initial booklist
	int all_book_selected = 0;
	for (int x = 0; x < k && SLC != NULL; x++) {
		all_book_selected++;

		GXGBook[x].cx = 2;
		GXGBook[x].cy = 7.5 - x * 0.5;

		GXGBook[x].ISBNcode = SLC->SelectedItem->Info.ISBNcode;
		GXGBook[x].Title = SLC->SelectedItem->Info.Title;
		GXGBook[x].Author = SLC->SelectedItem->Info.Author;
		GXGBook[x].Press = SLC->SelectedItem->Info.Press;
		GXGBook[x].Publicationdate = SLC->SelectedItem->Info.PublicationDATE.Year;
		GXGBook[x].Class = SLC->SelectedItem->Info.Class;
		GXGBook[x].Keywords = SLC->SelectedItem->Info.KeyWord;
		//数据转接
		switch (SLC->SelectedItem->Info.Status)
		{
		case BK_Avaliable:
			GXGBook[x].State = 1;
			break;
		case BK_Reserved:
			GXGBook[x].State = 0;
			break;
		case BK_Borrowed:
			GXGBook[x].State = 2;
			break;
		}
		GXGBook[x].collectnum = SLC->SelectedItem->Info.Stars;
		GXGBook[x].route = SLC->SelectedItem;

		SLC = SLC->Next;	
	}

	//show booklist
	if (showbook_flag) {
		DrawBooks(all_book_selected);
	}

	//Search By
	searchbooks_by();

	//filters
	booksorder_filter();
	
	//sheet
	SetPenColor("Light Gray");
	drawRectangle(2, 2, 12, 7, 0);
	drawBox(2, 8.5, 12, 0.5, 1, "Books", 'M', "Black");

	//dividing line
	MovePen(2, 8);
	SetPenColor("Dark Gray");
	DrawLine(12, 0);

	//sheethead
	drawMidLabel(9.5, 8, 2.5, 0.5, "Press", 'M', "Black");
	drawMidLabel(12, 8, 2, 0.5, "Publication date", 'M', "Black");

	showbookinformationwindow(k);

	pagemax = k / 12 + 1;

	if (flappage >= 0) {
		usePredefinedButtonColors(4);
		if (flappage > 0) {
			if (button(GenUIID(0), 5.6, 1.2, buttonWidth, buttonHeight, "<   Previous")) {
				flappage--;
			}
		}
		if (flappage < pagemax) {
			if (button(GenUIID(0), 8.4, 1.2, buttonWidth, buttonHeight, "Next   >")) {
				flappage++;
			}
		}
	}

}

void searchbooks_by() {
	//state_isbn
	if (state_isbn.state)
		setButtonColors("Gray", "Red", "Dark Gray", "Yellow", 1);
	else if (!state_isbn.state) 
		usePredefinedButtonColors(4);
	if (button(GenUIID(0), 5.8, 9.25, buttonWidth / 2, buttonHeight, "ISBN")) {
		select_status = "";
		state_isbn.state = !state_isbn.state;
	}

	//state_title
	if (state_title.state)setButtonColors("Gray", "Red", "Dark Gray", "Yellow", 1);
	else if (!state_title.state)usePredefinedButtonColors(4);
	if (button(GenUIID(0), 5.8 + stateinterval * 1, 9.25, buttonWidth / 2, buttonHeight, "Title")) {
		select_status = "";
		state_title.state = !state_title.state;
	}

	//state_author
	if (state_author.state)setButtonColors("Gray", "Red", "Dark Gray", "Yellow", 1);
	else if (!state_author.state)usePredefinedButtonColors(4);
	if (button(GenUIID(0), 5.8 + stateinterval * 2, 9.25, buttonWidth / 2, buttonHeight, "Author")) {
		select_status = "";
		state_author.state = !state_author.state;
	}

	//state_keyword
	if (state_keyword.state)setButtonColors("Gray", "Red", "Dark Gray", "Yellow", 1);
	else if (!state_keyword.state)usePredefinedButtonColors(4);
	if (button(GenUIID(0), 5.8 + stateinterval * 3, 9.25, buttonWidth / 2, buttonHeight, "Keyword")) {
		select_status = "";
		state_keyword.state = !state_keyword.state;
	}
}
void booksorder_filter() {
	if (state_filter_isbn.state)setButtonColors("Light Gray", "Black", "Gray", "Black", 1);
	else if (!state_filter_isbn.state)setButtonColors("White", "Black", "Light Gray", "Black", 1);
	if (button(GenUIID(0), 2, 8, buttonWidth + 0.5, buttonHeight, state_filter_isbn.state ? "ISBN  v" : "ISBN")) {
		select_status = "";
		state_filter_isbn.state = !state_filter_isbn.state;
	}

	if (state_filter_title.state)setButtonColors("Light Gray", "Black", "Gray", "Black", 1);
	else if (!state_filter_title.state)setButtonColors("White", "Black", "Light Gray", "Black", 1);
	if (button(GenUIID(0), 4.5, 8, buttonWidth + 0.5, buttonHeight, state_filter_title.state ? "Title  v" : "Title")) {
		select_status = "";
		state_filter_title.state = !state_filter_title.state;
	}

	if (state_filter_author.state)setButtonColors("Light Gray", "Black", "Gray", "Black", 1);
	else if (!state_filter_author.state)setButtonColors("White", "Black", "Light Gray", "Black", 1);
	if (button(GenUIID(0), 7, 8, buttonWidth + 0.5, buttonHeight, state_filter_author.state ? "Author  v" : "Author")) {
		select_status = "";
		state_filter_author.state = !state_filter_author.state;
	}
}

void DrawBooks(int x) {
	for (int m = 0; m < x; m++) {
		double ccx = GXGBook[m].cx;
		double ccy = GXGBook[m].cy;
		char str[5];
		setButtonColors("white", "White", "Light Gray", "Gray", 1);
		if (button(GenUIID(m), ccx, ccy, 12, buttonHeight, " ")) {
			GXGBook[m].isbookinformationshow = 1;
		}

		drawMidLabel(ccx, ccy, 2.5, 0.5, GXGBook[m].ISBNcode, 'M', "Black");
		drawMidLabel(ccx + 2.5, ccy, 2.5, 0.5, GXGBook[m].Title, 'M', "Black");
		drawMidLabel(ccx + 5, ccy, 2.5, 0.5, GXGBook[m].Author, 'M', "Black");
		drawMidLabel(ccx + 7.5, ccy, 2.5, 0.5, GXGBook[m].Press, 'M', "Black");
		drawMidLabel(ccx + 10, ccy, 2, 0.5, _itoa(GXGBook[m].Publicationdate, str, 10), 'M', "Black");

		MovePen(ccx + 0.2, ccy + 0.01);
		SetPenSize(2);
		SetPenColor("Light Gray");
		DrawLine(11.6, 0);
		SetPenSize(1);
	}

}

void showbookinformationwindow(int x) {
	for (int n = 0; n < x; n++) {
		if (GXGBook[n].isbookinformationshow) {
			SetPenColor("White");
			drawRectangle(3, 2, 10, 8, 1);
			SetPenColor("Black");
			drawRectangle(3, 2, 10, 8, 0);

			double infox = 4;
			double infoy = 8.7;
			double infowid = 2;
			double infointerval = 0.7;
			char str[5];
			drawMidLabel(infox, infoy, infowid, 0.5, "ISBN", 'R', "Black");
			drawMidLabel(infox, infoy - infointerval * 1, infowid, 0.5, "Title", 'R', "Black");
			drawMidLabel(infox, infoy - infointerval * 2, infowid, 0.5, "Author", 'R', "Black");
			drawMidLabel(infox, infoy - infointerval * 3, infowid, 0.5, "Press", 'R', "Black");
			drawMidLabel(infox, infoy - infointerval * 4, infowid, 0.5, "Publication date", 'R', "Black");
			drawMidLabel(infox, infoy - infointerval * 5, infowid, 0.5, "Class", 'R', "Black");
			drawMidLabel(infox, infoy - infointerval * 6, infowid, 0.5, "Keywords", 'R', "Black");
			drawMidLabel(infox, infoy - infointerval * 7, infowid, 0.5, "State", 'R', "Black");


			//strcpy Statestring
			string Statestring;
			switch (GXGBook[n].State)
			{
			case 1:
				Statestring = "Reservable";
				break;
			case 0:
				Statestring = "Reserved";
				break;
			case 2:
				Statestring = "Borrowed";
				break;
			default:
				break;
			}

			//show infomaiton
			drawMidLabel(infox + 2.5, infoy - infointerval * 0, infowid * 2, 0.5, GXGBook[n].ISBNcode, 'L', "Black");
			drawMidLabel(infox + 2.5, infoy - infointerval * 1, infowid * 2, 0.5, GXGBook[n].Title, 'L', "Black");
			drawMidLabel(infox + 2.5, infoy - infointerval * 2, infowid * 2, 0.5, GXGBook[n].Author, 'L', "Black");
			drawMidLabel(infox + 2.5, infoy - infointerval * 3, infowid * 2, 0.5, GXGBook[n].Press, 'L', "Black");
			drawMidLabel(infox + 2.5, infoy - infointerval * 4, infowid * 2, 0.5, _itoa(GXGBook[n].Publicationdate, str, 10), 'L', "Black");
			drawMidLabel(infox + 2.5, infoy - infointerval * 5, infowid * 2, 0.5, GXGBook[n].Class, 'L', "Black");
			drawMidLabel(infox + 2.5, infoy - infointerval * 6, infowid * 2, 0.5, GXGBook[n].Keywords, 'L', "Black");
			drawMidLabel(infox + 2.5, infoy - infointerval * 7, infowid * 2, 0.5, Statestring, 'L', "Black");

			setButtonColors("White", "Light Gray", "Light Gray", "Gray", 1);
			int collected = GXGBook[n].collectnum;
			if (iscollect.state) {
				setButtonColors("Light Gray", "Orange", "Gray", "Red", 1);
			}
			else if (!iscollect.state) {
				setButtonColors("White", "Light Gray", "Light Gray", "Gray", 1);
			}
			if (star_button(GenUIID(0), 11.5, 9, 0.25)) {
				if (!iscollect.state) {
					GXGBook[n].route->Like(GXGBook[n].route);
					Sleep(100);
				}
				else {
					GXGBook[n].route->Info.Stars--;
				}
				select_status = "";
				iscollect.state = !iscollect.state;
			}

			drawMidLabel(11.25, 8.2, 0.5, 0.5, iscollect.state ? _itoa(collected, str, 10) : _itoa(GXGBook[n].collectnum, str, 10), 'M', "Black");

			usePredefinedButtonColors(4);
			if (GXGBook[n].State == 1) {
				if (button(GenUIID(0), 5.6, 2.3, buttonWidth, buttonHeight, "Reserve")) {
					GXGBook[n].isbookinformationshow = 0;
				}
			}

			if (button(GenUIID(0), 8.4, 2.3, buttonWidth, buttonHeight, "Cancel")) {
				GXGBook[n].isbookinformationshow = 0;
			}

		}
	}

}

void bookedit_page(DB_Book* Library, BKSelect* SLC) {

	SLC = Library->pSelection;

	setTextBoxColors("Light Gray", "Black", "Gray", "Black", 0);
	if (textbox(GenUIID(0), 3, 10, 4.5, 0.5, searchKeyword, sizeof(searchKeyword))) {

	}
	SetPenColor("Black");
	drawLabel(4.5, 9.4, "Search By");
	usePredefinedButtonColors(4);

	//Search Button
	int selected_count;
	if (button(GenUIID(0), 8, 10, buttonWidth, buttonHeight, "Search")) {
		select_status = "";
		showbook_flag = 1;

		//实现查找
		if (searchKeyword[0] != 0) {
			Library->ResetSelection(Library);
			if (state_title.state) {
				selected_count = Library->SelectBy(Library, "Title", searchKeyword, LG_AND);
				Library->SoltSelection(Library);
			}
			else if (state_author.state)
				selected_count = Library->SelectBy(Library, "Author", searchKeyword, LG_AND);
			else if (state_keyword.state)
				selected_count = Library->SelectBy(Library, "Keyword", searchKeyword, LG_AND);
			else
				selected_count = Library->SelectBy(Library, "Title", searchKeyword, LG_AND);//不选择默认Title
			SLC = Library->pSelection;
			if (selected_count > 0) {
				char num[16]; char notic[64] = "找到了";
				TransToStr(selected_count, num);
				strcat(notic, num); strcat(notic, "条结果.");
				Call_Promote(notic);
			}
		}
		else {
			Library->SelectAll(Library);
			SLC = Library->pSelection;
		}
	}

	//Add Button
	if (button(GenUIID(0), 11, 10, buttonWidth, buttonHeight, "Add")) {
		isaddbookinformationshow = 1;
		select_status = "";
	}


	//initial booklist
	int all_book_selected = 0;
	for (int x = 0; x < k && SLC != NULL; x++) {
		all_book_selected++;

		GXGBook[x].cx = 2;
		GXGBook[x].cy = 7.5 - x * 0.5;

		GXGBook[x].ISBNcode = SLC->SelectedItem->Info.ISBNcode;
		GXGBook[x].Title = SLC->SelectedItem->Info.Title;
		GXGBook[x].Author = SLC->SelectedItem->Info.Author;
		GXGBook[x].Press = SLC->SelectedItem->Info.Press;
		GXGBook[x].Publicationdate = SLC->SelectedItem->Info.PublicationDATE.Year;
		GXGBook[x].Class = SLC->SelectedItem->Info.Class;
		GXGBook[x].Keywords = SLC->SelectedItem->Info.KeyWord;
		//数据转接
		switch (SLC->SelectedItem->Info.Status)
		{
		case BK_Avaliable:
			GXGBook[x].State = 1;
			break;
		case BK_Reserved:
			GXGBook[x].State = 0;
			break;
		case BK_Borrowed:
			GXGBook[x].State = 2;
			break;
		}
		GXGBook[x].collectnum = SLC->SelectedItem->Info.Stars;
		GXGBook[x].route = SLC->SelectedItem;

		SLC = SLC->Next;
	}

	//show booklist
	if (showbook_flag) {
		DrawBooks(k);
	}

	//Search By
	searchbooks_by();

	//filters
	booksorder_filter();

	//sheet
	SetPenColor("Light Gray");
	drawRectangle(2, 2, 12, 7, 0);
	drawBox(2, 8.5, 12, 0.5, 1, "Books", 'M', "Black");

	//dividing line
	MovePen(2, 8);
	SetPenColor("Dark Gray");
	DrawLine(12, 0);

	//sheethead
	drawMidLabel(9.5, 8, 2.5, 0.5, "Press", 'M', "Black");
	drawMidLabel(12, 8, 2, 0.5, "Publication date", 'M', "Black");

	editbookinformationwindow(k);
	if (isaddbookinformationshow) {
		addbookinformationwindow();
	}

	//flappage
	pagemax = k / 12 + 1;

	if (flappage >= 0) {
		usePredefinedButtonColors(4);
		if (flappage > 0) {
			if (button(GenUIID(0), 5.6, 1.2, buttonWidth, buttonHeight, "<   Previous")) {
				flappage--;
			}
		}
		if (flappage < pagemax) {
			if (button(GenUIID(0), 8.4, 1.2, buttonWidth, buttonHeight, "Next   >")) {
				flappage++;
			}
		}
	}

}

void editbookinformationwindow(int x) {
	for (int n = 0; n < x; n++) {
		if (GXGBook[n].isbookinformationshow) {
			SetPenColor("White");
			drawRectangle(3, 2, 10, 8, 1);
			SetPenColor("Black");
			drawRectangle(3, 2, 10, 8, 0);

			double infox = 4;
			double infoy = 8.7;
			double infowid = 2;
			double infointerval = 0.7;
			
			drawMidLabel(infox, infoy, infowid, 0.5, "ISBN", 'R', "Black");
			drawMidLabel(infox, infoy - infointerval * 1, infowid, 0.5, "Title", 'R', "Black");
			drawMidLabel(infox, infoy - infointerval * 2, infowid, 0.5, "Author", 'R', "Black");
			drawMidLabel(infox, infoy - infointerval * 3, infowid, 0.5, "Press", 'R', "Black");
			drawMidLabel(infox, infoy - infointerval * 4, infowid, 0.5, "Publication date", 'R', "Black");
			drawMidLabel(infox, infoy - infointerval * 5, infowid, 0.5, "Class", 'R', "Black");
			drawMidLabel(infox, infoy - infointerval * 6, infowid, 0.5, "Keywords", 'R', "Black");
			drawMidLabel(infox, infoy - infointerval * 7, infowid, 0.5, "State", 'R', "Black");


			//strcpy Statestring
			string Statestring;
			switch (GXGBook[n].State)
			{
			case 1:
				Statestring = "Reservable";
				break;
			case 2:
				Statestring = "Reserved";
				break;
			case 3:
				Statestring = "Borrowed";
				break;
			default:
				break;
			}

			//edit mystr 注意这里修改的是整形值和字符数组，其他的只要使用字符数组即可。
			static char mystr_Publicationdate[5];
			static char mystr_ISBN[15];
			static char mystr_Title[20];
			static char mystr_Author[10];
			static char mystr_Press[10];
			static char mystr_Class[10];
			static char mystr_Keywords[30];

			//initial modify status
			if (ismodified_Publicationdate == FALSE)
				_itoa(GXGBook[n].Publicationdate, mystr_Publicationdate, 10);
			if (ismodified_ISBN == FALSE)
				strcpy(mystr_ISBN, GXGBook[n].ISBNcode);
			if (ismodified_Title == FALSE)
				strcpy(mystr_Title, GXGBook[n].Title);
			if (ismodified_Author == FALSE)
				strcpy(mystr_Author, GXGBook[n].Author);
			if (ismodified_Press == FALSE)
				strcpy(mystr_Press, GXGBook[n].Press);
			if (ismodified_Class == FALSE)
				strcpy(mystr_Class, GXGBook[n].Class);
			if (ismodified_Keywords == FALSE)
				strcpy(mystr_Keywords, GXGBook[n].Keywords);


			//show textboxs
			if (textbox(GenUIID(0), infox + 2.5, infoy - infointerval * 4, infowid * 2, 0.5, mystr_Publicationdate, sizeof(mystr_Publicationdate))) {
				ismodified_Publicationdate = TRUE;
			}

			if (textbox(GenUIID(0), infox + 2.5, infoy, infowid * 2, 0.5, mystr_ISBN, sizeof(mystr_ISBN))) {
				ismodified_ISBN = TRUE;
			}

			if (textbox(GenUIID(0), infox + 2.5, infoy - infointerval * 1, infowid * 2, 0.5, mystr_Title, sizeof(mystr_Title))) {
				ismodified_Title = TRUE;
			}
			if (textbox(GenUIID(0), infox + 2.5, infoy - infointerval * 2, infowid * 2, 0.5, mystr_Author, sizeof(mystr_Author))) {
				ismodified_Author = TRUE;
			}
			if (textbox(GenUIID(0), infox + 2.5, infoy - infointerval * 3, infowid * 2, 0.5, mystr_Press, sizeof(mystr_Press))) {
				ismodified_Press = TRUE;
			}
			if (textbox(GenUIID(0), infox + 2.5, infoy - infointerval * 5, infowid * 2, 0.5, mystr_Class, sizeof(mystr_Class))) {
				ismodified_Class = TRUE;
			}
			if (textbox(GenUIID(0), infox + 2.5, infoy - infointerval * 6, infowid * 2, 0.5, mystr_Keywords, sizeof(mystr_Keywords))) {
				ismodified_Keywords = TRUE;
			}

			drawMidLabel(infox + 2.5, infoy - infointerval * 7, infowid * 2, 0.5, Statestring, 'L', "Black");

			usePredefinedButtonColors(4);
			if (GXGBook[n].State == 1) {
				if (button(GenUIID(0), 5.6, 2.3, buttonWidth, buttonHeight, "Confirm")) {
					GXGBook[n].isbookinformationshow = 0;
				}
			}

			if (button(GenUIID(0), 8.4, 2.3, buttonWidth, buttonHeight, "Cancel")) {
				GXGBook[n].isbookinformationshow = 0;
			}

		}
	}

}

void addbookinformationwindow() {
	SetPenColor("White");
	drawRectangle(3, 2, 10, 8, 1);
	SetPenColor("Black");
	drawRectangle(3, 2, 10, 8, 0);

	double infox = 4;
	double infoy = 8.7;
	double infowid = 2;
	double infointerval = 0.7;
	char str[5];
	drawMidLabel(infox, infoy, infowid, 0.5, "ISBN", 'R', "Black");
	drawMidLabel(infox, infoy - infointerval * 1, infowid, 0.5, "Title", 'R', "Black");
	drawMidLabel(infox, infoy - infointerval * 2, infowid, 0.5, "Author", 'R', "Black");
	drawMidLabel(infox, infoy - infointerval * 3, infowid, 0.5, "Press", 'R', "Black");
	drawMidLabel(infox, infoy - infointerval * 4, infowid, 0.5, "Publication date", 'R', "Black");
	drawMidLabel(infox, infoy - infointerval * 5, infowid, 0.5, "Class", 'R', "Black");
	drawMidLabel(infox, infoy - infointerval * 6, infowid, 0.5, "Keywords", 'R', "Black");
	//drawMidLabel(infox, infoy - infointerval * 7, infowid, 0.5, "State", 'R', "Black");


	struct myBook tempBook;

	tempBook.ISBNcode = "";
	tempBook.Title = "";
	tempBook.Author = "";
	tempBook.Press = "";
	tempBook.Publicationdate = 0;
	tempBook.Class = "";
	tempBook.Keywords = "";
	tempBook.State = 1;

	tempBook.collectnum = 0;
	////edit infomaiton

	if (textbox(GenUIID(0), infox + 2.5, infoy, infowid * 2, 0.5, tempBook.ISBNcode, sizeof(tempBook.ISBNcode))) {

	}
	if (textbox(GenUIID(0), infox + 2.5, infoy - infointerval * 1, infowid * 2, 0.5, tempBook.Title, sizeof(tempBook.Title))) {

	}
	if (textbox(GenUIID(0), infox + 2.5, infoy - infointerval * 2, infowid * 2, 0.5, tempBook.Author, sizeof(tempBook.Author))) {

	}
	if (textbox(GenUIID(0), infox + 2.5, infoy - infointerval * 3, infowid * 2, 0.5, tempBook.Press, sizeof(tempBook.Press))) {

	}
	if (textbox(GenUIID(0), infox + 2.5, infoy - infointerval * 4, infowid * 2, 0.5, _itoa(tempBook.Publicationdate, str, 10), sizeof(_itoa(tempBook.Publicationdate, str, 10)))) {

	}
	if (textbox(GenUIID(0), infox + 2.5, infoy - infointerval * 5, infowid * 2, 0.5, tempBook.Class, sizeof(tempBook.Class))) {

	}
	if (textbox(GenUIID(0), infox + 2.5, infoy - infointerval * 6, infowid * 2, 0.5, tempBook.Keywords, sizeof(tempBook.Keywords))) {

	}

	usePredefinedButtonColors(4);
	if (button(GenUIID(0), 5.6, 2.3, buttonWidth, buttonHeight, "Confirm")) {
		isaddbookinformationshow = 0;
	}

	if (button(GenUIID(0), 8.4, 2.3, buttonWidth, buttonHeight, "Cancel")) {
		isaddbookinformationshow = 0;
	}

}