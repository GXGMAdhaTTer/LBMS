#include "readermanagement.h"
struct Reader {
	string IDcode;
	string Name;
	int Gender;
	string Employer;
	int BorrowedNum;
	string BorrowedBooks;
}myReader;

bool showreaderinfo_flag = 0;

bool state_ID, state_Name;

//book struct

void readermanagement_page() {
	static char searchKeyword[20] = "";

	setTextBoxColors("Light Gray", "Black", "Gray", "Black", 0);
	if (textbox(GenUIID(0), 4, 10, 4.5, 0.5, searchKeyword, sizeof(searchKeyword))) {

	}
	SetPenColor("Black");
	drawLabel(4.5, 9.4, "Search By");
	usePredefinedButtonColors(4);

	//Search Button
	if (button(GenUIID(0), 9, 10, buttonWidth, buttonHeight, "Search")) {
		select_status = "";
		showreaderinfo_flag = 1;
	}

	//double cx, cy;
	//string IDcode;
	//string Name;
	//int Gender;
	//string Employer;
	//int BorrowedNum;
	//string BorrowedBooks;

	//initial readerinfo
	initreaderinfor();


	//Search By
	searchreaders_by();
	if(showreaderinfo_flag)
		showreaderinformationwindow();

}

static void initreaderinfor() {
	myReader.IDcode = "3160102712";
	myReader.Name = "GXG";
	myReader.Gender = 1;
	myReader.Employer = "ZJU";
	myReader.BorrowedNum = 3;
	myReader.BorrowedBooks = "������������Ʒ÷��ʥ�߷���";
}

void searchreaders_by() {
	//state_isbn
	if (state_ID)setButtonColors("Gray", "Red", "Dark Gray", "Yellow", 1);
	else if (!state_ID)usePredefinedButtonColors(4);
	if (button(GenUIID(0), 5.8, 9.25, buttonWidth / 2, buttonHeight, "ID")) {
		select_status = "";
		state_ID = !state_ID;
	}

	//state_title
	if (state_Name)setButtonColors("Gray", "Red", "Dark Gray", "Yellow", 1);
	else if (!state_Name)usePredefinedButtonColors(4);
	if (button(GenUIID(0), 6.8, 9.25, buttonWidth / 2, buttonHeight, "Name")) {
		select_status = "";
		state_Name = !state_Name;
	}
}

void showreaderinformationwindow() {
	double infox = 4;
	double infoy = 8.7;
	double infowid = 2;
	double infointerval = 0.7;
	char str[5];
	drawMidLabel(infox, infoy, infowid, 0.5, "ID", 'R', "Black");
	drawMidLabel(infox, infoy - infointerval * 1, infowid, 0.5, "Name", 'R', "Black");
	drawMidLabel(infox, infoy - infointerval * 2, infowid, 0.5, "Gender", 'R', "Black");
	drawMidLabel(infox, infoy - infointerval * 3, infowid, 0.5, "Employer", 'R', "Black");
	drawMidLabel(infox, infoy - infointerval * 4, infowid, 0.5, "Borrowed", 'R', "Black");

	//strcpy Gender
	string myGender;
	switch (myReader.Gender)
	{
	case 1:
		myGender = "Male";
		break;
	case 0:
		myGender = "Female";
		break;
	default:
		break;
	}

	//show infomaiton
	drawMidLabel(infox + 2.5, infoy - infointerval * 0, infowid * 2, 0.5, myReader.IDcode, 'L', "Black");
	drawMidLabel(infox + 2.5, infoy - infointerval * 1, infowid * 2, 0.5, myReader.Name, 'L', "Black");
	drawMidLabel(infox + 2.5, infoy - infointerval * 2, infowid * 2, 0.5, myGender, 'L', "Black");
	drawMidLabel(infox + 2.5, infoy - infointerval * 3, infowid * 2, 0.5, myReader.Employer, 'L', "Black");
	drawMidLabel(infox + 2.5, infoy - infointerval * 4, infowid * 2, 0.5, _itoa(myReader.BorrowedNum, str, 10), 'L', "Black");
	drawMidLabel(infox + 2.5, infoy - infointerval * 5, infowid * 2, 0.5, myReader.BorrowedBooks, 'L', "Black");

}