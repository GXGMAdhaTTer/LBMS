#include "myborrow.h"

struct Borrow {
	int id;
	double cx, cy;
	string ISBNcode;
	string Title;
	string Expirydate;
	bool renewright;
}myborrow[5];

struct Date {
	int year;
	int month;
	int day;
};

bool isrenewed = 0;

static int s = 3;

void initBorrow(int x) {
	for (int i = 0; i < x; i++) {
		if (!isrenewed) {
			myborrow[i].id = i;
			myborrow[i].cx = 2;
			myborrow[i].cy = 8.5 - i * 0.5;
			myborrow[i].ISBNcode = "978710000000";
			myborrow[i].Title = "大威天龙";
			myborrow[i].Expirydate = "2020.05.12";
			myborrow[i].renewright = 1;
		}
	}
}

void DrawBorrow(int x) {
	for (int i = 0; i < x; i++) {
		drawMidLabel(myborrow[i].cx, myborrow[i].cy, 3, 0.5, myborrow[i].ISBNcode, 'M', "Black");
		drawMidLabel(myborrow[i].cx + 3, myborrow[i].cy, 3, 0.5, myborrow[i].Title, 'M', "Black");
		drawMidLabel(myborrow[i].cx + 6, myborrow[i].cy, 3, 0.5, myborrow[i].Expirydate, 'M', "Black");
		usePredefinedButtonColors(4);
		if (myborrow[i].renewright) {
			if (button(GenUIID(myborrow[i].id), myborrow[i].cx + 9.5, myborrow[i].cy + 0.05, 2, buttonHeight - 0.1, "Renew")) {
				isrenewed = 1;
				myborrow[i].Expirydate = "2020.05.22";//这个地方就。。如果能改成三个日期相加或许好些。之后再改吧。
				myborrow[i].renewright = 0;
			}
		}
		else if (!myborrow[i].renewright) {
			SetPenColor("Gray");
			drawBox(myborrow[i].cx + 9.5, myborrow[i].cy+0.05, 2, 0.4, 1, "Renewed", 'M', "White");
		}
		MovePen(myborrow[i].cx + 0.2, myborrow[i].cy);
		SetPenColor("Light Gray");
		DrawLine(11.6, 0);
	}
}

void myborrow_page() {
	initBorrow(s);
	DrawBorrow(s);

	//sheet
	SetPenColor("Light Gray");
	drawRectangle(2, 2, 12, 8, 0);
	drawBox(2, 9.5, 12, 0.5, 1, "Borrow", 'M', "Black");

	//dividing line
	MovePen(2, 9);
	SetPenColor("Dark Gray");
	DrawLine(12, 0);

	//sheethead
	drawMidLabel(2, 9, 3, 0.5, "ISBN", 'M', "Black");
	drawMidLabel(5, 9, 3, 0.5, "Title", 'M', "Black");
	drawMidLabel(8, 9, 3, 0.5, "Expiry Date", 'M', "Black");
}