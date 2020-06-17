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

	//content
	drawLabel(5.2, 8, "We simulates the library management system of the real online ");
	drawLabel(5.2, 7.5, "library, and stores information for the attributes such as ISBN, title, ");
	drawLabel(5.2, 7, "author, press, publication date, and reader account, gender, unit, etc. ");
	drawLabel(5.2, 6.5, "to realize the entry, modification, and search of book information. ");
	drawLabel(5.2, 6, "Account information creation, modification, loan and return records, ");
	drawLabel(5.2, 5.5, "etc. Using the current coding capabilities, a simple procedure similar");
	drawLabel(5.2, 5, "to a library management system is basically restored.");

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

	//Titile
	drawLabel(7.8, 8.8, "About");

	//content
	drawLabel(6, 8, "这是一个蛮简陋的图书馆，");
	drawLabel(6, 7.5, "虽然不能真的借到书，");
	drawLabel(6, 7, "但是稍微模拟一下操作，");
	drawLabel(6, 6.5, "求老师给过~");

	drawLabel(6, 5.5, "小组成员：王湘杰，张锟，高孝国。");

	usePredefinedButtonColors(4);
	if (button(GenUIID(0), 7, 3.2, buttonWidth, buttonHeight, "Cancel")) {
		about_page_flag = 0;
	}
}

void sorrywindow() {
	SetPenColor("White");
	drawRectangle(4, 4, 8, 4, 1);
	SetPenColor("Black");
	drawRectangle(4, 4, 8, 4, 0);

	//Titile
	drawLabel(7.7, 7.2, "Warning");

	//content
	drawLabel(7.2, 6.4, "Please Login first.");

	usePredefinedButtonColors(4);
	if (button(GenUIID(0), 7, 4.5, buttonWidth, buttonHeight, "Cancel")) {
		sorry_page_flag = 0;
	}
}

void sorrywindow_reader() {
	SetPenColor("White");
	drawRectangle(4, 4, 8, 4, 1);
	SetPenColor("Black");
	drawRectangle(4, 4, 8, 4, 0);

	//Titile
	drawLabel(7.7, 7.2, "Warning");

	//content
	drawLabel(7, 6.4, "Please Login as Reader.");

	usePredefinedButtonColors(4);
	if (button(GenUIID(0), 7, 4.5, buttonWidth, buttonHeight, "Cancel")) {
		sorry_page_flag_reader = 0;
	}
}

void sorrywindow_administrator() {
	SetPenColor("White");
	drawRectangle(4, 4, 8, 4, 1);
	SetPenColor("Black");
	drawRectangle(4, 4, 8, 4, 0);

	//Titile
	drawLabel(7.7, 7.2, "Warning");

	//content
	drawLabel(6.7, 6.4, "Please Login as Administrator.");

	usePredefinedButtonColors(4);
	if (button(GenUIID(0), 7, 4.5, buttonWidth, buttonHeight, "Cancel")) {
		sorry_page_flag_administrator = 0;
	}
}


