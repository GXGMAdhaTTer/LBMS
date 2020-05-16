#include "statusbar.h"
void showstatus(double mmx, double mmy) {
	//Show login status;
	if (login_page_flag) {
		if (mmx > 3.7 && mmx < 3.7 + buttonWidth && mmy>5.4 && mmy < 5.4 + buttonHeight) {
			select_status = "Login as Administrator";
		}
		else if (mmx > 9.7 && mmx < 9.7 + buttonWidth && mmy>5.4 && mmy < 5.4 + buttonHeight) {
			select_status = "Login as Reader";
		}
		else {
			select_status = "";
		}
	}
	//Show password status;
	if (password_page_flag) {
		if (mmx > 5.6 && mmx < 5.6 + buttonWidth && mmy>4.8 && mmy < 4.8 + buttonHeight) {
			select_status = "Sign in";
		}
		else if (mmx > 8.4 && mmx < 8.4 + buttonWidth && mmy>4.8 && mmy < 4.8 + buttonHeight) {
			select_status = "Sign up";
		}
		else {
			select_status = "";
		}
	}

	//Show Administrator status;
	if (initial_Administrator_flag) {
		if (mmx > 1.7 && mmx < 1.7 + buttonWidth && mmy>5.2 && mmy < 5.2 + buttonHeight) select_status = "Edit books";
		else if (mmx > 1.7 + interval && mmx < 1.7 + interval + buttonWidth && mmy>5.2 && mmy < 5.2 + buttonHeight) select_status = "Check reader's requests";
		else if (mmx > 1.7 + interval * 2 && mmx < 1.7 + interval * 2 + buttonWidth && mmy>5.2 && mmy < 5.2 + buttonHeight) select_status = "View reader's infomation";
		else if (mmx > 1.7 + interval * 3 && mmx < 1.7 + interval * 3 + buttonWidth && mmy>5.2 && mmy < 5.2 + buttonHeight) select_status = "Show resource statistic";
		else {
			select_status = "";
		}
	}

	if (initial_Reader_flag) {
		if (mmx > 1.7 && mmx < 1.7 + buttonWidth && mmy>5.2 && mmy < 5.2 + buttonHeight) select_status = "Reserve books";
		else if (mmx > 1.7 + interval && mmx < 1.7 + interval + buttonWidth && mmy>5.2 && mmy < 5.2 + buttonHeight) select_status = "View record of reservation";
		else if (mmx > 1.7 + interval * 2 && mmx < 1.7 + interval * 2 + buttonWidth && mmy>5.2 && mmy < 5.2 + buttonHeight) select_status = "Return books";
		else if (mmx > 1.7 + interval * 3 && mmx < 1.7 + interval * 3 + buttonWidth && mmy>5.2 && mmy < 5.2 + buttonHeight) select_status = "Modify your account information";
		else {
			select_status = "";
		}
	}
}