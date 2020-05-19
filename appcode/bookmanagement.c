#include "bookmanagement.h"
struct myBook {
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

}GXGBook[10];
char searchKeyword[20] = "";
double stateinterval = 1.2;
bool showbook_flag = 0;
bool isaddbookinformationshow = 0;
int k = 10;//k<=12
//state struct
int pagemax;
bool modifyStatus = FALSE;
int flappage = 0;

struct statebutton {
	bool state;
}state_isbn, state_title, state_author, state_keyword, state_filter_isbn, state_filter_title, state_filter_author, iscollect;

//book struct

void bookreserve_page() {
	setTextBoxColors("Light Gray", "Black", "Gray", "Black", 0);
	if (textbox(GenUIID(0), 4, 10, 4.5, 0.5, searchKeyword, sizeof(searchKeyword))) {

	}
	SetPenColor("Black");
	drawLabel(4.5, 9.4, "Search By");
	usePredefinedButtonColors(4);

	//Search Button
	if (button(GenUIID(0), 9, 10, buttonWidth, buttonHeight, "Search")) {
		select_status = "";
		showbook_flag = 1;
	}

	//initial booklist
	for (int x = 0; x < k; x++) {
		GXGBook[x].cx = 2;
		GXGBook[x].cy = 7.5 - x * 0.5;

		GXGBook[x].ISBNcode = "9787100000000";
		GXGBook[x].Title = "大威天龙";
		GXGBook[x].Author = "法海";
		GXGBook[x].Press = "金山寺";
		GXGBook[x].Publicationdate = 2020;
		GXGBook[x].Class = "Fiction";
		GXGBook[x].Keywords = "大威天龙 大罗法咒 世尊地藏";
		GXGBook[x].State = 1;

		GXGBook[x].collectnum = 56;
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
	if (state_isbn.state)setButtonColors("Gray", "Red", "Dark Gray", "Yellow", 1);
	else if (!state_isbn.state)usePredefinedButtonColors(4);
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
			case 2:
				Statestring = "Reserved";
				break;
			case 3:
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
			int collected = GXGBook[n].collectnum + 1;
			if (iscollect.state) {
				setButtonColors("Light Gray", "Orange", "Gray", "Red", 1);
			}
			else if (!iscollect.state) {
				setButtonColors("White", "Light Gray", "Light Gray", "Gray", 1);
			}
			if (star_button(GenUIID(0), 11.5, 9, 0.25)) {
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

void bookedit_page() {
	setTextBoxColors("Light Gray", "Black", "Gray", "Black", 0);
	if (textbox(GenUIID(0), 3, 10, 4.5, 0.5, searchKeyword, sizeof(searchKeyword))) {

	}
	SetPenColor("Black");
	drawLabel(4.5, 9.4, "Search By");
	usePredefinedButtonColors(4);

	//Search Button
	if (button(GenUIID(0), 8, 10, buttonWidth, buttonHeight, "Search")) {
		select_status = "";
		showbook_flag = 1;
	}

	//Add Button
	if (button(GenUIID(0), 11, 10, buttonWidth, buttonHeight, "Add")) {
		isaddbookinformationshow = 1;
		select_status = "";
	}


	//initial booklist

	for (int x = 0; x < k; x++) {
		GXGBook[x].cx = 2;
		GXGBook[x].cy = 7.5 - x * 0.5;

		GXGBook[x].ISBNcode = "9787100000000";
		GXGBook[x].Title = "大威天龙";
		GXGBook[x].Author = "法海";
		GXGBook[x].Press = "金山寺";
		GXGBook[x].Publicationdate = 2020;
		GXGBook[x].Class = "Fiction";
		GXGBook[x].Keywords = "大威天龙 大罗法咒 世尊地藏";
		GXGBook[x].State = 1;

		GXGBook[x].collectnum = 56;
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

			////edit infomaiton

			//edit publicationdate 注意这里修改的是整形值和字符数组，其他的只要使用字符数组即可。
			static char mystr[5];
			if (modifyStatus == FALSE)
				_itoa(GXGBook[n].Publicationdate, mystr, 10);

			if (textbox(GenUIID(0), infox + 2.5, infoy - infointerval * 4, infowid * 2, 0.5, mystr, sizeof(mystr))) {
				modifyStatus = TRUE;
				GXGBook[n].Publicationdate = atoi(mystr);
			}


			if (textbox(GenUIID(0), infox + 2.5, infoy, infowid * 2, 0.5, GXGBook[n].ISBNcode, sizeof(GXGBook[n].ISBNcode))) {

			}
			if (textbox(GenUIID(0), infox + 2.5, infoy - infointerval * 1, infowid * 2, 0.5, GXGBook[n].Title, sizeof(GXGBook[n].Title))) {

			}
			if (textbox(GenUIID(0), infox + 2.5, infoy - infointerval * 2, infowid * 2, 0.5, GXGBook[n].Author, sizeof(GXGBook[n].Author))) {

			}
			if (textbox(GenUIID(0), infox + 2.5, infoy - infointerval * 3, infowid * 2, 0.5, GXGBook[n].Press, sizeof(GXGBook[n].Press))) {

			}
			if (textbox(GenUIID(0), infox + 2.5, infoy - infointerval * 5, infowid * 2, 0.5, GXGBook[n].Class, sizeof(GXGBook[n].Class))) {

			}
			if (textbox(GenUIID(0), infox + 2.5, infoy - infointerval * 6, infowid * 2, 0.5, GXGBook[n].Keywords, sizeof(GXGBook[n].Keywords))) {

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