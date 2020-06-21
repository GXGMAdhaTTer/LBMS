#include "loginpage.h"
#include "../SimpleData_Library/DBUAdmin.h"

void login_page() {
	icon_Administrator(5, 7);
	usePredefinedButtonColors(4);
	SetPenSize(1);
	if (button(GenUIID(0), 3.7, 5.4, buttonWidth, buttonHeight, "Administrator")) {
		login_page_flag = 0;
		charactor = 0;
		password_page_flag = 1;
		select_status = "";
	}
	
	
	icon_Reader(11, 7);
	usePredefinedButtonColors(4);
	SetPenSize(1);
	if (button(GenUIID(0), 9.7, 5.4, buttonWidth, buttonHeight, "Reader")) {
		login_page_flag = 0;
		charactor = 1;
		password_page_flag = 1;
		select_status = "";
	}
}

void password_page(DB_User* database) {

	static int ismodified_accname;
	static int ismodified_password;

	SetPenColor("Black");
	drawLabel(5.5, 7, "Account Name");
	drawLabel(5.8, 6, "Password");

	if (ismodified_accname != 1)
		strcpy(Administrator_AccountName, "default");
	if (ismodified_password != 1)
		strcpy(Administrator_Password, "password");

	setTextBoxColors("Light Gray", "Black", "Gray", "Black", 0);
	if (textbox(GenUIID(0), 7.1, 6.85, 3, 0.5, Administrator_AccountName, sizeof(Administrator_AccountName))) {
		ismodified_accname = 1;
	}

	if (textbox(GenUIID(0), 7.1, 5.85, 3, 0.5, Administrator_Password, sizeof(Administrator_Password))) {
		ismodified_password = 1;
	}

	if (button(GenUIID(0), 5.6, 4.8, buttonWidth, buttonHeight, "Sign In")) {
		if (database->Login(database, Administrator_AccountName, Administrator_Password) == 1) {
			login_status = 1;
			select_status = "";
			password_page_flag = 0;
			if (charactor)
				initial_Reader_flag = 1;
			else if (!charactor)
				initial_Administrator_flag = 1;
		}
	}

	if (button(GenUIID(0), 8.4, 4.8, buttonWidth, buttonHeight, "Sign Up")) {
		select_status = "";
		signup_page_flag = 1;
	}

}