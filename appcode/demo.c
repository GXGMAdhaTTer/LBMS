#include "demo.h"
/*To load headfiles.*/

static double winwidth, winheight;   // ���ڳߴ�

// ����������provided in libgraphics
void DisplayClear(void);

// �û�����ʾ����
void display(void);

// �û��ļ����¼���Ӧ����
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event); // GUI��ȡ����
	display(); // ˢ����ʾ
}

// �û�������¼���Ӧ����
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event); //GUI��ȡ���
	display(); // ˢ����ʾ
}

// �û����������
// ����ʼ��ִ��һ��
void Main()
{
	SetWindowTitle("Graphics User Interface Demo");
	InitGraphics(16,12);

	// ��ô��ڳߴ�
	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();

	// ע��ʱ����Ӧ����
	registerKeyboardEvent(KeyboardEventProcess);// ����
	registerMouseEvent(MouseEventProcess);      // ���
	//InitConsole(); 
}


// �˵���ʾ����
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
	double h = fH * 1.5; // �ؼ��߶�
	double y = winheight - h;
	double w = 0.8; // �ؼ����
	double wlist = 1.6;
	double xindent = winheight / 20; // ����
	int    selection;

	// File �˵�
	selection = menuList(GenUIID(0), x, y - h, w, wlist, h, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
	if (selection > 0) selectedLabel = menuListFile[selection];
	if (selection == 3)
		exit(-1);

	// Books �˵�
	selection = menuList(GenUIID(0), x + w, y - h, w, wlist, h, menuListBooks, sizeof(menuListBooks) / sizeof(menuListBooks[0]));
	if (selection > 0) selectedLabel = menuListBooks[selection];

	// Borrowing �˵�
	selection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListBorrowing, sizeof(menuListBorrowing) / sizeof(menuListBorrowing[0]));
	if (selection > 0) selectedLabel = menuListBorrowing[selection];

	// User �˵�
	selection = menuList(GenUIID(0), x + 3 * w, y - h, w, wlist, h, menuListUser, sizeof(menuListUser) / sizeof(menuListUser[0]));
	if (selection > 0) selectedLabel = menuListUser[selection];

	// Help �˵�
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



