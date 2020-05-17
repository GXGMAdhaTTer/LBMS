#include "loginpage.h"
void signupwindow() {
	double textboxstart = 7.8;
	double textboxinterval = 0.8;
	//draw white board
	SetPenColor("White");
	drawRectangle(3, 2.6, 10, 6.8, 1);
	SetPenColor("Black");
	drawRectangle(3, 2.6, 10, 6.8, 0);

	drawLabel(7.6, 8.8, "Sign up");

	drawLabel(5.8, textboxstart, "ID");
	drawLabel(5.4, textboxstart - textboxinterval * 1, "Password");
	drawLabel(5.6, textboxstart - textboxinterval * 2, "Name");
	drawLabel(5.5, textboxstart - textboxinterval * 3, "Gender");
	drawLabel(5.4, textboxstart - textboxinterval * 4, "Employer");


	setTextBoxColors("Light Gray", "Black", "Gray", "Black", 0);
	if (textbox(GenUIID(0), 7.1, textboxstart-0.15, 3, 0.5, Reader_ID, sizeof(Reader_ID))) {

	}

	if (textbox(GenUIID(0), 7.1, textboxstart - textboxinterval*1-0.15, 3, 0.5, Reader_Password, sizeof(Reader_Password))) {

	}
	if (textbox(GenUIID(0), 7.1, textboxstart - textboxinterval*2 - 0.15, 3, 0.5, Reader_Name, sizeof(Reader_Name))) {

	}
	if (textbox(GenUIID(0), 7.1, textboxstart - textboxinterval*3 - 0.15, 3, 0.5, Reader_Gender, sizeof(Reader_Gender))) {

	}
	if (textbox(GenUIID(0), 7.1, textboxstart - textboxinterval*4 - 0.15, 3, 0.5, Reader_Employer, sizeof(Reader_Employer))) {

	}


	usePredefinedButtonColors(4);
	if (button(GenUIID(0), 5.6, 3.2, buttonWidth, buttonHeight, "Comfirm")) {
		signup_page_flag = 0;
	}

	if (button(GenUIID(0), 8.4, 3.2, buttonWidth, buttonHeight, "Cancel")) {
		signup_page_flag = 0;
	}

}
void accountsettingwindow() {
	double textboxstart = 7.8;
	double textboxinterval = 0.8;
	//draw white board
	SetPenColor("White");
	drawRectangle(3, 2.6, 10, 6.8, 1);
	SetPenColor("Black");
	drawRectangle(3, 2.6, 10, 6.8, 0);

	drawLabel(7.6, 8.8, "Account Setting");

	drawLabel(5.8, textboxstart, "ID");
	drawLabel(5.4, textboxstart - textboxinterval * 1, "Password");
	drawLabel(5.6, textboxstart - textboxinterval * 2, "Name");
	drawLabel(5.5, textboxstart - textboxinterval * 3, "Gender");
	drawLabel(5.4, textboxstart - textboxinterval * 4, "Employer");


	setTextBoxColors("Light Gray", "Black", "Gray", "Black", 0);
	if (textbox(GenUIID(0), 7.1, textboxstart - 0.15, 3, 0.5, Reader_ID, sizeof(Reader_ID))) {

	}

	if (textbox(GenUIID(0), 7.1, textboxstart - textboxinterval * 1 - 0.15, 3, 0.5, Reader_Password, sizeof(Reader_Password))) {

	}
	if (textbox(GenUIID(0), 7.1, textboxstart - textboxinterval * 2 - 0.15, 3, 0.5, Reader_Name, sizeof(Reader_Name))) {

	}
	if (textbox(GenUIID(0), 7.1, textboxstart - textboxinterval * 3 - 0.15, 3, 0.5, Reader_Gender, sizeof(Reader_Gender))) {

	}
	if (textbox(GenUIID(0), 7.1, textboxstart - textboxinterval * 4 - 0.15, 3, 0.5, Reader_Employer, sizeof(Reader_Employer))) {

	}


	usePredefinedButtonColors(4);
	if (button(GenUIID(0), 5.6, 3.2, buttonWidth, buttonHeight, "Comfirm")) {
		accountsetting_page_flag = 0;
	}

	if (button(GenUIID(0), 8.4, 3.2, buttonWidth, buttonHeight, "Cancel")) {
		accountsetting_page_flag = 0;
	}
}
void guidewindow() {
	SetPenColor("White");
	drawRectangle(3, 2.6, 10, 6.8, 1);
	SetPenColor("Black");
	drawRectangle(3, 2.6, 10, 6.8, 0);

	drawLabel(7.8, 8.8, "Guide");

	usePredefinedButtonColors(4);
	if (button(GenUIID(0), 7, 3.2, buttonWidth, buttonHeight, "Cancel")) {
		guide_page_flag = 0;
	}
}
void aboutwindow() {
	SetPenColor("White");
	drawRectangle(3, 2.6, 10, 6.8, 1);
	SetPenColor("Black");
	drawRectangle(3, 2.6, 10, 6.8, 0);

	drawLabel(7.8, 8.8, "About");

	usePredefinedButtonColors(4);
	if (button(GenUIID(0), 7, 3.2, buttonWidth, buttonHeight, "Cancel")) {
		about_page_flag = 0;
	}
}


