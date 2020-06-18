#include "demo.h"
/*To load headfiles.*/

// 我爱你

void DisplayClear(void);
void display(void);
void KeyboardEventProcess(int key, int event);
void MouseEventProcess(int x, int y, int button, int event);
void CharEventProcess(char ch);
void ReturnPages();
void ReturnAdministrator();
void ReturnReader();

void Main()
{
	SetWindowTitle("Library Management System");
	SetWindowSize(16, 12);
	InitGraphics();

	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();
	
	registerKeyboardEvent(KeyboardEventProcess);
	registerMouseEvent(MouseEventProcess);
	registerCharEvent(CharEventProcess);
	//InitConsole(); 

	//initiate pages
	menu_flag = 1;
	guide_page_flag = 0;
	login_page_flag = 0;
	about_page_flag = 0;
	password_page_flag = 0;
	initial_Administrator_flag = 0;
	initial_Reader_flag = 0;
	signup_page_flag = 0;
	accountsetting_page_flag = 0;
	bookreserve_page_flag = 0;
	bookedit_page_flag = 0;
	reservation_page_flag = 0;
	borrowing_page_flag = 0;
	checkreservation_page_flag = 0;
	readermanagement_page_flag = 0;
	statistic_page_flag = 0;
}


void drawMenu()
{
	usePredefinedMenuColors(4);
	static char* menuListFile[] = { "Manage",
		"Check | Ctrl-C",
		"Reader | Ctrl-R",
		"Statistic",
		"Quit | Ctrl-E" };
	static char* menuListBooks[] = { "Books",
		"Add | Ctrl-A",
		"Search | Ctrl-F",
		"Modify | Ctrl-T" };
	static char* menuListBorrow[] = { "Borrow",
		"Borrow  | Ctrl-B",
		"Reservation",
		"Renew" };
	static char* menuListUser[] = { "User",
		"Login  | Ctrl-L",
		"Register",
		"Logout | Ctrl-Q"};
	static char* menuListHelp[] = { "Help",
		"Guide",
		"About" };

	static char* selectedLabel = NULL;

	double fH = GetFontHeight();
	
	double x = 0;
	double h = fH * 1.5;
	double y = winheight - h;
	double w = 1;
	double wlist = 2;
	double xindent = winheight / 20;
	int selection;

	selection = menuList(GenUIID(0), x, y - h, w, wlist, h, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
	if (selection > 0) selectedLabel = menuListFile[selection];
	if (selection == 1) {
		if (login_status) {
			if (charactor) {
				sorry_page_flag_administrator = 1;
			}
			if (!charactor) {
				initial_Administrator_flag = 0;
				checkreservation_page_flag = 1;
			}
		}
		if(!login_status) {
			sorry_page_flag = 1;
		}
	}
	if (selection == 2) {
		if (login_status) {
			if (charactor) {
				sorry_page_flag_administrator = 1;
			}
			if (!charactor) {
				initial_Administrator_flag = 0;
				readermanagement_page_flag = 1;
			}
		}
		if (!login_status) {
			sorry_page_flag = 1;
		}
	}
	if (selection == 3) {
		if (login_status) {
			if (charactor) {
				sorry_page_flag_administrator = 1;
			}
			if (!charactor) {
				initial_Administrator_flag = 0;
				statistic_page_flag = 1;
			}
		}
		if (!login_status) {
			sorry_page_flag = 1;
		}
	}
	if (selection == 4)
		exit(-1);

	selection = menuList(GenUIID(0), x + w, y - h, w, wlist, h, menuListBooks, sizeof(menuListBooks) / sizeof(menuListBooks[0]));
	if (selection > 0) selectedLabel = menuListBooks[selection];
	if (selection == 1) {
		if (login_status) {
			if (charactor) {
				sorry_page_flag_administrator = 1;
			}
			if (!charactor) {
				initial_Administrator_flag = 1;
				bookedit_page_flag = 1;
				addbookinformationwindow();
			}
		}
		if (!login_status) {
			sorry_page_flag = 1;
		}
	}
	if (selection == 2) {
		if (login_status) {
			if (charactor) {
				sorry_page_flag_administrator = 1;
			}
			if (!charactor) {
				initial_Administrator_flag = 0;
				bookedit_page_flag = 1;
			}
		}
		if (!login_status) {
			sorry_page_flag = 1;
		}
	}
	if (selection == 3) {
		if (login_status) {
			if (charactor) {
				sorry_page_flag_administrator = 1;
			}
			if (!charactor) {
				initial_Administrator_flag = 0;
				bookedit_page_flag = 1;
			}
		}
		if (!login_status) {
			sorry_page_flag = 1;
		}
	}

	selection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListBorrow, sizeof(menuListBorrow) / sizeof(menuListBorrow[0]));
	if (selection > 0) selectedLabel = menuListBorrow[selection];
	if (selection == 1) {
		if (login_status) {
			if (charactor) {
				initial_Reader_flag = 0;
				bookreserve_page_flag = 1;
			}
			if (!charactor) {
				sorry_page_flag_reader = 1;
			}
		}
		if (!login_status) {
			sorry_page_flag = 1;
		}
	}
	if (selection == 2) {
		if (login_status) {
			if (charactor) {
				initial_Reader_flag = 0;
				reservation_page_flag = 1;
			}
			if (!charactor) {
				sorry_page_flag_reader = 1;
			}
		}
		if (!login_status) {
			sorry_page_flag = 1;
		}
	}
	if (selection == 3) {
		if (login_status) {
			if (charactor) {
				initial_Reader_flag = 0;
				borrowing_page_flag = 1;
			}
			if (!charactor) {
				sorry_page_flag_reader = 1;
			}
		}
		if (!login_status) {
			sorry_page_flag = 1;
		}
	}

	selection = menuList(GenUIID(0), x + 3 * w, y - h, w, wlist, h, menuListUser, sizeof(menuListUser) / sizeof(menuListUser[0]));
	if (selection > 0) selectedLabel = menuListUser[selection];
	if (selection == 1) {
		login_page_flag = 1;
		guide_page_flag = 0;
		about_page_flag = 0;
		signup_page_flag = 0;
		initial_Administrator_flag = 0;
		initial_Reader_flag = 0;
		login_status = 0;
	}
	if (selection == 2) {
		signup_page_flag = 1;
	}
	if (selection == 3) {
		ReturnPages();
	}

	selection = menuList(GenUIID(0), x + 4 * w, y - h, w, wlist, h, menuListHelp, sizeof(menuListHelp) / sizeof(menuListHelp[0]));
	if (selection > 0) selectedLabel = menuListHelp[selection];
	if (selection == 1) {
		guide_page_flag = 1;
		about_page_flag = 0;
		login_page_flag = 0;
		
	}
	if (selection == 2) {
		guide_page_flag = 0;
		about_page_flag = 1;
		login_page_flag = 0;
	}
	
	SetPenColor("Light Gray");
	drawRectangle(x + 5 * w, y - h, winwidth-x-4*w, h, 1);
	drawRectangle(0, winheight, winwidth, -h, 1);
	drawRectangle(0, 0, winwidth, h, 1);
	SetPenColor("Black");
	drawLabel(winwidth/2-1.5,winheight-0.2, "Library management system");
	drawLabel(0.3, 0.1, select_status);
	SetPenColor("Light Gray");

	if (login_status) {//返回主页和登出
		usePredefinedButtonColors(4);
		if (button(GenUIID(0), 13, 11.45, 1, 0.4, "Back")) {
			if (charactor) {
				ReturnReader();
			}
			else if (!charactor) {
				ReturnAdministrator();
			}
		}
		if (button(GenUIID(0), 14.5, 11.45, 1, 0.4, "Logout")) {
			ReturnPages();
		}
	}
}

void display()
{
	DisplayClear();

	//normalwindows
	if (login_page_flag) {
		login_page();
	}
	if (password_page_flag) {
		password_page();
	}
	if (initial_Administrator_flag) {
		initialAdministrator();
	}
	if (initial_Reader_flag) {
		initialReader();
	}
	if (bookreserve_page_flag) {
		bookreserve_page();
	}
	if (bookedit_page_flag) {
		bookedit_page();
	}
	if (reservation_page_flag) {
		reservation_page();
	}
	if (checkreservation_page_flag) {
		checkreservation_page();
	}
	if (borrowing_page_flag) {
		myborrow_page();
	}
	if (readermanagement_page_flag) {
		readermanagement_page();
	}
	if (statistic_page_flag) {
		statistic_page();
	}

	//popupwindows
	if (signup_page_flag) {
		signupwindow();
	}
	if (accountsetting_page_flag) {
		accountsettingwindow();
	}

	if (sorry_page_flag) {
		sorrywindow();
	}
	if (sorry_page_flag_administrator) {
		sorrywindow_administrator();
	}
	if (sorry_page_flag_reader) {
		sorrywindow_reader();
	}
	if (guide_page_flag) {
		guidewindow();
	}
	if (about_page_flag) {
		aboutwindow();
	}
	
	//show menu
	if (menu_flag) {
		drawMenu();
	}
	
}
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event);

	double mx, my;
	mx = ScaleXInches(x);
	my = ScaleYInches(y);
	showstatus(mx, my);
	display();
}
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event); // GUI获取键盘
	display(); // 刷新显示
}
void CharEventProcess(char ch) {
	uiGetChar(ch);
	display();
}

void ReturnPages() {
	login_status = 0;
	login_page_flag = 0;
	guide_page_flag = 0;
	about_page_flag = 0;
	sorry_page_flag = 0;
	sorry_page_flag_reader = 0;
	sorry_page_flag_administrator = 0;
	password_page_flag = 0;
	initial_Administrator_flag = 0;
	initial_Reader_flag = 0;
	signup_page_flag = 0;
	accountsetting_page_flag = 0;
	bookreserve_page_flag = 0;
	bookedit_page_flag = 0;
	readerinformationwindow_page_flag = 0;
	reservation_page_flag = 0;
	checkreservation_page_flag = 0;
	borrowing_page_flag = 0;
	readermanagement_page_flag = 0;
	cover_page_flag = 0;
	statistic_page_flag = 0;
}

void ReturnAdministrator() {
	ReturnPages();
	login_status = 1;
	charactor = 0;
	initial_Administrator_flag = 1;
}

void ReturnReader() {
	ReturnPages();
	login_status = 1;
	charactor = 1;
	initial_Reader_flag = 1;
}



