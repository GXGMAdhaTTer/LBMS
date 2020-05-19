#include "myreservation.h"

struct Reservation{
	int id;
	double cx, cy;
	string ISBNcode;
	string Title;
	string Expirydate;
}myreservation[5];

static int s = 3;

static void initReservation(int x) {
	for (int i = 0; i < x; i++) {
		myreservation[i].id = i;
		myreservation[i].cx = 2;
		myreservation[i].cy = 8.5 - i * 0.5;
		myreservation[i].ISBNcode = "978710000000";
		myreservation[i].Title = "´óÍþÌìÁú";
		myreservation[i].Expirydate = "2020.05.12";
	}
}

void DrawReservation(int x) {
	for (int i = 0; i < x; i++) {
		drawMidLabel(myreservation[i].cx, myreservation[i].cy, 3, 0.5, myreservation[i].ISBNcode, 'M', "Black");
		drawMidLabel(myreservation[i].cx + 3, myreservation[i].cy, 3, 0.5, myreservation[i].Title, 'M', "Black");
		drawMidLabel(myreservation[i].cx + 6, myreservation[i].cy, 3, 0.5, myreservation[i].Expirydate, 'M', "Black");
		usePredefinedButtonColors(4);
		if (button(GenUIID(myreservation[i].id), myreservation[i].cx + 9.5, myreservation[i].cy + 0.05, 2, buttonHeight - 0.1, "Cancel")) {
			DeleteRes(myreservation, i, &s);
		}
		MovePen(myreservation[i].cx + 0.2, myreservation[i].cy);
		SetPenColor("Light Gray");
		DrawLine(11.6, 0);
	}
}

void DeleteRes(struct Reservation* a, int M, int* n) {
	for (int i = M; i < *n; i++) {
		a[i - 1] = a[i];
	}
	*n = *n - 1;
}

void reservation_page() {
	initReservation(s);
	DrawReservation(s);

	//sheet
	SetPenColor("Light Gray");
	drawRectangle(2, 2, 12, 8, 0);
	drawBox(2, 9.5, 12, 0.5, 1, "Reservation", 'M', "Black");

	//dividing line
	MovePen(2, 9);
	SetPenColor("Dark Gray");
	DrawLine(12, 0);

	//sheethead
	drawMidLabel(2, 9, 3, 0.5, "ISBN", 'M', "Black");
	drawMidLabel(5, 9, 3, 0.5, "Title", 'M', "Black");
	drawMidLabel(8, 9, 3, 0.5, "Expiry Date", 'M', "Black");
}