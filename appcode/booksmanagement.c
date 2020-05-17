#include "booksmanagement.h"
char searchKeyword[20] = "";
double stateinterval = 1.2;
bool showbook_flag = 0;

//state struct
struct statebutton {
	bool state;
}state_isbn, state_title, state_author, state_keyword, state_filter_isbn,state_filter_title,state_filter_author;

//book struct
typedef struct {
	double cx, cy;
	string ISBNcode;
	string Title;
	string Author;
	string Press;
	int Publicationdate;

}*BookT;

void InitBookList();
void DrawBooks(void* curbook);
//BookT FindBook(linkedlistADT alist, int sum);
linkedlistADT booklist;
//BookT curBook = NULL;

void booksearch_page() {
	setTextBoxColors("Light Gray", "Black", "Gray", "Black", 0);
	if (textbox(GenUIID(0), 4, 10, 4.5, 0.5, searchKeyword, sizeof(searchKeyword))) {

	}
	SetPenColor("Black");
	drawLabel(4.5, 9.4, "Search By");
	usePredefinedButtonColors(4);

	booklist = NewLinkedList();
	InitBookList();

	//Search Button
	if (button(GenUIID(0), 9, 10, buttonWidth, buttonHeight, "Search")) {
		select_status = "";
		showbook_flag = 1;
	}

	if (showbook_flag) {
		TraverseLinkedList(booklist, DrawBooks);
	}

	//Search By
	search_by();

	//filters
	order_filter();

	//sheet
	SetPenColor("Light Gray");
	drawRectangle(2, 1, 12, 8, 0);
	drawBox(2, 8.5, 12, 0.5, 1, "Books", 'M', "Black");

	//dividing line
	MovePen(2, 8);
	SetPenColor("Dark Gray");
	DrawLine(12, 0);

	//sheethead
	drawMidLabel(9.5, 8, 2.5, 0.5, "Press", 'M', "Black");
	drawMidLabel(12, 8, 2, 0.5,"Publication date", 'M', "Black");
	
}

void search_by() {
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
void order_filter() {
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

void InitBookList() {
	BookT aptr;
	int i;
	for (i = 0; i < 1; i++) {
		aptr = GetBlock(sizeof(*aptr));
		aptr->cx = 2;
		aptr->cy = 7.5;

		aptr->ISBNcode = "9787100000000";
		aptr->Title = "大威天龙";
		aptr->Author = "法海";
		aptr->Press = "金山寺";
		aptr->Publicationdate = 2020;

		InsertNode(booklist, NULL, aptr);
	}
}

void DrawBooks(void* curbook) {
	BookT aptr = (BookT)curbook;
	double ccx = aptr->cx;
	double ccy = aptr->cy;
	char str[5];
	setButtonColors("white", "White", "Light Gray", "Gray", 1);
	if (button(GenUIID(0), aptr->cx, aptr->cy, 12, buttonHeight, "")) {

	}
	drawMidLabel(ccx, ccy, 2.5, 0.5, aptr->ISBNcode, 'M', "Black");
	drawMidLabel(ccx + 2.5, ccy, 2.5, 0.5, aptr->Title, 'M', "Black");
	drawMidLabel(ccx + 5, ccy, 2.5, 0.5, aptr->Author, 'M', "Black");
	drawMidLabel(ccx + 7.5, ccy, 2.5, 0.5, aptr->Press, 'M', "Black");
	drawMidLabel(ccx + 10, ccy, 2, 0.5, itoa(aptr->Publicationdate, str, 10), 'M', "Black");

}