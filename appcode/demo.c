#include "demo.h"
/*To load headfiles.*/

static double winwidth, winheight;   // 窗口尺寸

// 清屏函数，provided in libgraphics
void DisplayClear(void);

// 用户的显示函数
void display(void);

// 用户的键盘事件响应函数
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event); // GUI获取键盘
	display(); // 刷新显示
}

// 用户的鼠标事件响应函数
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event); //GUI获取鼠标
	display(); // 刷新显示
}

// 用户主程序入口
// 仅初始化执行一次
void Main()
{
	SetWindowTitle("Graphics User Interface Demo");
	InitGraphics(16,12);

	// 获得窗口尺寸
	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();

	// 注册时间响应函数
	registerKeyboardEvent(KeyboardEventProcess);// 键盘
	registerMouseEvent(MouseEventProcess);      // 鼠标
	//InitConsole(); 
}


// 菜单演示程序
void drawMenu()
{
	usePredefinedMenuColors(4);
	static char* menuListFile[] = { "File",
		"Open  | Ctrl-O",
		"New  | Ctrl-N",
		"Quit   | Ctrl-Q" };
	static char* menuListBooks[] = { "Books",
		"Add",
		"Search",
		"Modify | Ctrl-T" };
	static char* menuListBorrowing[] = { "Borrowing",
		"Reserve  | Ctrl-M",
		"Return" };
	static char* menuListUser[] = { "User",
		"Login  | Ctrl-L",
		"Register",
		"logout | Ctrl-Shift-Q "};
	static char* menuListHelp[] = { "Help",
		"Guide",
		"About" };

	static char* selectedLabel = NULL;

	double fH = GetFontHeight();
	
	double x = 0; //fH/8;
	double h = fH * 1.5; // 控件高度
	double y = winheight - h;
	double w = 0.8; // 控件宽度
	double wlist = 1.6;
	double xindent = winheight / 20; // 缩进
	int    selection;

	// File 菜单
	selection = menuList(GenUIID(0), x, y - h, w, wlist, h, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
	if (selection > 0) selectedLabel = menuListFile[selection];
	if (selection == 3)
		exit(-1);

	// Books 菜单
	selection = menuList(GenUIID(0), x + w, y - h, w, wlist, h, menuListBooks, sizeof(menuListBooks) / sizeof(menuListBooks[0]));
	if (selection > 0) selectedLabel = menuListBooks[selection];

	// Borrowing 菜单
	selection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListBorrowing, sizeof(menuListBorrowing) / sizeof(menuListBorrowing[0]));
	if (selection > 0) selectedLabel = menuListBorrowing[selection];

	// User 菜单
	selection = menuList(GenUIID(0), x + 3 * w, y - h, w, wlist, h, menuListUser, sizeof(menuListUser) / sizeof(menuListUser[0]));
	if (selection > 0) selectedLabel = menuListUser[selection];

	// Help 菜单
	selection = menuList(GenUIID(0), x + 4 * w, y - h, w, wlist, h, menuListHelp, sizeof(menuListHelp) / sizeof(menuListHelp[0]));
	if (selection > 0) selectedLabel = menuListHelp[selection];
	
	SetPenColor("Light Gray");
	drawRectangle(x + 5 * w, y - h, winwidth-x-4*w, h, 1);
	drawRectangle(0, winheight, winwidth, -h, 1);
	SetPenColor("Black");
	drawLabel(4,winheight-0.2, "Library management system");
	SetPenColor("Light Gray");
}

void display()
{
	DisplayClear();
	drawMenu();
	icon_Administrator(5, 5);
}



