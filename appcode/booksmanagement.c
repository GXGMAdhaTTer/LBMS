#include "booksmanagement.h"
void booksearch_page() {
	char searchKeyword[20] = "";
	setTextBoxColors("Light Gray", "Black", "Gray", "Black", 0);
	if (textbox(GenUIID(0), 4, 10, 4.5, 0.5, searchKeyword, sizeof(searchKeyword))) {

	}
	SetPenColor("Black");
	drawLabel(3.5, 9.4, "Search By");
	usePredefinedButtonColors(4);

	//Search Button
	if (button(GenUIID(0), 9, 10, buttonWidth, buttonHeight, "Search")) {
		select_status = "";
	}

	//Search By
	if (button(GenUIID(0), 4.8, 9.25, buttonWidth/2, buttonHeight, "All")) {
		select_status = "";
	}

}

bool dotSelector() {

}