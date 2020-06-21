#include "../SimpleData_Library/DBAdmin.h"

#include "statistic.h"
int collectionSum;
int borrowSum;
int likeSum;
struct ClassCount {
	string className;
	int numcollection;
	int numborrow;
	int numlike;
}MyClassCount[15];


void statistic_page(DB_Book* library) {
	//initial sums;
	collectionSum = library->pManageItem->BooksStored;
	borrowSum = library->pManageItem->TotalBookBorrowed;
	likeSum = 20;
	static int dtype = 0;
	char str[5];

	//3 buttons
	setButtonColors("Light Gray", "Light Gray", "Light Gray", "Light Gray", 1);
	double buttonx, buttony, buttoninterval;
	buttonx = 1.5;
	buttony = 9.3;
	buttoninterval = 1.9;

	//Collection
	if (button(GenUIID(0), buttonx, buttony, 2.2, 1.4, "")) {
		dtype = 1;
	}
	drawMidLabel(buttonx, buttony + 0.6, 2.2, 0.5, "Collection", 'M', "Black");
	drawMidLabel(buttonx, buttony + 0.2, 2.2, 0.5, _itoa(collectionSum, str, 10), 'M', "Black");

	//Borrowed
	if (button(GenUIID(0), buttonx, buttony-buttoninterval, 2.2, 1.4, "")) {
		dtype = 2;
	}
	drawMidLabel(buttonx, buttony - buttoninterval + 0.6, 2.2, 0.5, "Borrowed", 'M', "Black");
	drawMidLabel(buttonx, buttony - buttoninterval + 0.2, 2.2, 0.5, _itoa(borrowSum, str, 10), 'M', "Black");

	//Like
	if (button(GenUIID(0), buttonx, buttony - buttoninterval*2, 2.2, 1.4, "")) {
		dtype = 3;
	}
	drawMidLabel(buttonx, buttony - buttoninterval*2 + 0.6, 2.2, 0.5, "Like", 'M', "Black");
	drawMidLabel(buttonx, buttony - buttoninterval*2 + 0.2, 2.2, 0.5, _itoa(likeSum, str, 10), 'M', "Black");
	
	//show Histogram
	if (dtype != 0) {
		drawHistogram(dtype,library);
	}

	//show Piechart
	drawPiechart(3,3, 14,82);

	//show Popular
	showPopular("大威天龙", "JOJO的奇幻冒险");
}

void initClassDate(DB_Book* library) {
	//因为数据库不全，所以这里只有有限的书籍种类
	int default_col, default_borr, default_like;
	int fiction_col, fiction_borr, fiction_like;
	int history_col, history_borr, history_like;
	int science_col, science_borr, science_like;
	default_col = default_borr = default_like
		= fiction_col = fiction_borr = fiction_like
		= history_col = history_borr = history_like
		= science_col = science_borr = science_like = 0;
	BookEx* cursor = library->pBookLink;
	while (cursor != NULL) {
		if (strcmp(cursor->Info.Class, "Default") == 0) {
			default_col++;
			default_borr += (cursor->Info.TotalBorrow);
			default_like += (cursor->Info.Stars);
		}
		else if (strcmp(cursor->Info.Class, "Fiction") == 0) {
			fiction_col++;
			fiction_borr += (cursor->Info.TotalBorrow);
			fiction_like += (cursor->Info.Stars);
		}
		else if (strcmp(cursor->Info.Class, "History") == 0) {
			history_col++;
			history_borr += (cursor->Info.TotalBorrow);
			history_like += (cursor->Info.Stars);
		}
		else if (strcmp(cursor->Info.Class, "Science") == 0) {
			science_col++;
			science_borr += (cursor->Info.TotalBorrow);
			science_like += (cursor->Info.Stars);
		}
		cursor = cursor->Next;
	}
	//这里需要给所有的书的种类赋值
	//先赋值知道的几个
	MyClassCount[0].numcollection = default_col;
	MyClassCount[0].numborrow = default_borr;
	MyClassCount[0].numlike = default_like;
	MyClassCount[0].className = "Default";
	MyClassCount[1].numcollection = fiction_col;
	MyClassCount[1].numborrow = fiction_borr;
	MyClassCount[1].numlike = fiction_like;
	MyClassCount[1].className = "Fiction";
	MyClassCount[2].numcollection = history_col;
	MyClassCount[2].numborrow = history_borr;
	MyClassCount[2].numlike = history_like;
	MyClassCount[2].className = "History";
	MyClassCount[3].numcollection = science_col;
	MyClassCount[3].numborrow = science_borr;
	MyClassCount[3].numlike = science_like;
	MyClassCount[3].className = "Science";
	//剩下的凑字数
	for (int i = 4; i < 15; i++) {
		MyClassCount[i].numcollection = 30;
		MyClassCount[i].numborrow = 40;
		MyClassCount[i].numlike = 50;
		MyClassCount[i].className = "Tools";
	}
}

void drawDateLine(int n, int t) {
	double dy = 0.37;
	char str[3];
	int tmp;
	drawMidLabel(5, 10.5 - n * dy, 1, 0.3, MyClassCount[n].className, 'R', "BLACK");
	MovePen(6.0, 10.65 - n * dy);
	switch (t) {//t代表展示的属性
	case 0:
		break;
	case 1:
		tmp = (MyClassCount[n].numcollection) > 80 ? 80 : (MyClassCount[n].numcollection);
		DrawLine(tmp / 10, 0);		
		MovePen(tmp / 10 + 6.2, 10.57 - n * dy);
		DrawTextString(_itoa(tmp, str, 10));
		break;
	case 2:
		tmp = MyClassCount[n].numborrow > 80 ? 80 : MyClassCount[n].numborrow;
		DrawLine(tmp / 10, 0);
		MovePen(tmp / 10 + 6.2, 10.57 - n * dy);
		DrawTextString(_itoa(tmp, str, 10));
		break;
	case 3:
		tmp = MyClassCount[n].numlike > 80 ? 80 : MyClassCount[n].numlike;
		DrawLine(tmp / 10, 0);
		MovePen(tmp / 10 + 6.2, 10.57 - n * dy);
		DrawTextString(_itoa(tmp, str, 10));
		break;
	}
}

void drawHistogram(int dtype, DB_Book* library) {
	MovePen(6.0, 10.9);
	DrawLine(0, -5.7);
	initClassDate(library);
	for (int j = 0; j < 15; j++) {
		drawDateLine(j, dtype);
	}
}

void drawPiechart(double cx, double cy, int nummale, int numfemale) {
	double PI = 3.1415;
	double anglemale, anglefemale;
	int percentmale, percentfemale;
	double ir = 1;
	double or = 1.5;
	double ors_male = 1.5;
	double ors_female = 1.5;
	double sym = 0.5;
	anglemale = 360.0 * nummale / (nummale + numfemale);
	anglefemale = 360.0 * numfemale / (nummale + numfemale);
	percentmale = (int)(100.0 * nummale / (nummale + numfemale));
	percentfemale = 100 - percentmale;

	double mmx, mmy;
	mmx = GetMouseX() - cx;
	mmy = GetMouseY() - cy;
	
	double sita;
	sita = atan2(mmy, mmx);
	if (mmx*mmx+mmy*mmy>ir*ir && mmx * mmx + mmy * mmy<or*or) {
		if (sita > -PI && sita < -PI + angle2rad(anglemale)) {
			ors_male = or + sym;
		}
		if (sita > -PI + angle2rad(anglemale) && sita < PI) {
			ors_female = or + sym;
		}
	}

	//Piemale
	MovePen(cx, cy);
	StartFilledRegion(1);
	SetPenColor("Violet");
	DrawLine(-ors_male, 0);
	DrawArc(ors_male , 180, anglemale);
	DrawLine(ors_male* cos(angle2rad(anglemale)), ors_male * sin(angle2rad(anglemale)));
	EndFilledRegion();

	//Piefemale
	MovePen(cx, cy);
	StartFilledRegion(1);
	SetPenColor("Cyan");
	DrawLine(-ors_female *cos(angle2rad(anglemale)), -ors_female *sin(angle2rad(anglemale)));
	DrawArc(ors_female , -180+anglemale, anglefemale);
	DrawLine(ors_female, 0);
	EndFilledRegion();

	//覆盖
	MovePen(cx + ir, cy);
	StartFilledRegion(1);
	SetPenColor("WHITE");
	DrawArc(ir, 0, 360);
	EndFilledRegion();

	char str[3];
	MovePen(cx + 2, cy + 0.5);
	SetPenColor("Violet");
	drawRectangle(cx + 2.5, cy + 0.5, 0.3, 0.3, 1);
	drawMidLabel(cx + 3, cy+0.52, 1, 0.3, "Male", 'L', "Black");
	drawMidLabel(cx + 3.6, cy + 0.52, 1, 0.3, _itoa(percentmale, str, 10), 'R', "Black");
	DrawTextString("%");
	
	SetPenColor("Cyan");
	drawRectangle(cx + 2.5, cy - 0.5, 0.3, 0.3, 1);
	drawMidLabel(cx + 3, cy - 0.48, 1, 0.3, "Female", 'L', "Black");
	drawMidLabel(cx + 3.6, cy - 0.48, 1, 0.3, _itoa(percentfemale, str, 10), 'R', "Black");
	DrawTextString("%");
}

void showPopular(char *popularformen, char *popularforwomen) {
	double cx, cy, interval;
	cx = 10;
	cy = 4;
	interval = 1.5;
	drawLabel(cx, cy, "The most popular book for men:");
	drawLabel(cx, cy-0.5, popularformen);
	drawLabel(cx, cy-interval, "The most popular book for women:");
	drawLabel(cx, cy - interval - 0.5, popularforwomen);
}
