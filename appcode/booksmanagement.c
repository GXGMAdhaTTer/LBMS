#include "booksmanagement.h"
char searchKeyword[20] = "";
double stateinterval = 1.2;
struct statebutton {
	bool pre, val, state;
}state_isbn, state_title, state_author, state_keyword;
void booksearch_page() {
	setTextBoxColors("Light Gray", "Black", "Gray", "Black", 0);
	if (textbox(GenUIID(0), 4, 10, 4.5, 0.5, searchKeyword, sizeof(searchKeyword))) {

	}
	SetPenColor("Black");
	drawLabel(4.5, 9.4, "Search By");
	usePredefinedButtonColors(4);

	//Search Button
	if (button(GenUIID(0), 9, 10, buttonWidth, buttonHeight, "Search")) {
		select_status = "";
	}
	
	//Search By
	search_by();

	//sheet
	SetPenColor("White");
	drawRectangle(2, 1, 12, 8, 1);
	SetPenColor("Light Gray");
	drawRectangle(2, 1, 12, 8, 0);
	drawBox(2, 8.5, 12, 0.5, 1, "Books", "", "Black");


}

void search_by() {
	//state_isbn
	state_isbn.val = 0;
	if (state_isbn.state)setButtonColors("Gray", "Red", "Dark Gray", "Yellow", 1);
	else if (!state_isbn.state)usePredefinedButtonColors(4);
	if (button(GenUIID(0), 5.8, 9.25, buttonWidth / 2, buttonHeight, "ISBN")) {
		select_status = "";
		state_isbn.val = 1;
	}
	if (state_isbn.pre && !state_isbn.val)state_isbn.state = !state_isbn.state;
	state_isbn.pre = state_isbn.val;

	//state_title
	state_title.val = 0;
	if (state_title.state)setButtonColors("Gray", "Red", "Dark Gray", "Yellow", 1);
	else if (!state_title.state)usePredefinedButtonColors(4);
	if (button(GenUIID(0), 5.8 + stateinterval * 1, 9.25, buttonWidth / 2, buttonHeight, "Title")) {
		select_status = "";
		state_title.val = 1;
	}
	if (state_title.pre && !state_title.val)state_title.state = !state_title.state;
	state_title.pre = state_title.val;

	//state_author
	state_author.val = 0;
	if (state_author.state)setButtonColors("Gray", "Red", "Dark Gray", "Yellow", 1);
	else if (!state_author.state)usePredefinedButtonColors(4);
	if (button(GenUIID(0), 5.8 + stateinterval * 2, 9.25, buttonWidth / 2, buttonHeight, "Author")) {
		select_status = "";
		state_author.val = 1;
	}
	if (state_author.pre && !state_author.val)state_author.state = !state_author.state;
	state_author.pre = state_author.val;

	//state_keyword
	state_keyword.val = 0;
	if (state_keyword.state)setButtonColors("Gray", "Red", "Dark Gray", "Yellow", 1);
	else if (!state_keyword.state)usePredefinedButtonColors(4);
	if (button(GenUIID(0), 5.8 + stateinterval * 3, 9.25, buttonWidth / 2, buttonHeight, "Keyword")) {
		select_status = "";
		state_keyword.val = 1;
	}
	if (state_keyword.pre && !state_keyword.val)state_keyword.state = !state_keyword.state;
	state_keyword.pre = state_keyword.val;
}