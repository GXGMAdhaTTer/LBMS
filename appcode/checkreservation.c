#include "checkreservation.h"

struct Request {
	int id;
	double cx, cy;
	string ISBNcode;
	string Title;
	string Applicant;
	string Expirydate;
}myrequest[5];

static int s = 4;

static void initRequest(int x) {
	for (int i = 0; i < x; i++) {
		myrequest[i].id = i;
		myrequest[i].cx = 2;
		myrequest[i].cy = 8.5 - i * 0.5;
		myrequest[i].ISBNcode = "978710000000";
		myrequest[i].Title = "´óÍþÌìÁú";
		myrequest[i].Applicant = "GXG";
		myrequest[i].Expirydate = "2020.05.12";
	}
}

void DrawRequest(int x) {
	for (int i = 0; i < x; i++) {
		drawMidLabel(myrequest[i].cx, myrequest[i].cy, 3, 0.5, myrequest[i].ISBNcode, 'M', "Black");
		drawMidLabel(myrequest[i].cx + 3, myrequest[i].cy, 3, 0.5, myrequest[i].Title, 'M', "Black");
		drawMidLabel(myrequest[i].cx + 6, myrequest[i].cy, 2, 0.5, myrequest[i].Applicant, 'M', "Black");
		drawMidLabel(myrequest[i].cx + 8, myrequest[i].cy, 2, 0.5, myrequest[i].Expirydate, 'M', "Black");
		usePredefinedButtonColors(4);
		if (button(GenUIID(myrequest[i].id), myrequest[i].cx + 10.25, myrequest[i].cy + 0.05, 1.5, buttonHeight - 0.1, "Agree")) {
			DeleteReq(myrequest, i, &s);
		}
		MovePen(myrequest[i].cx + 0.2, myrequest[i].cy);
		SetPenColor("Light Gray");
		DrawLine(11.6, 0);
	}
}

void DeleteReq(struct Request* a, int M, int* n) {
	if (M == 0) {
		for (int i = 1; i < *n; i++) {
			a[i - 1] = a[i];
		}
	}
	if (M > 0) {
		for (int i = M; i < *n; i++) {
			a[i - 1] = a[i];
		}
	}
	*n = *n - 1;
}

void checkreservation_page() {
	initRequest(s);
	DrawRequest(s);

	//sheet
	SetPenColor("Light Gray");
	drawRectangle(2, 2, 12, 8, 0);
	drawBox(2, 9.5, 12, 0.5, 1, "Request", 'M', "Black");

	//dividing line
	MovePen(2, 9);
	SetPenColor("Dark Gray");
	DrawLine(12, 0);

	//sheethead
	drawMidLabel(2, 9, 3, 0.5, "ISBN", 'M', "Black");
	drawMidLabel(5, 9, 3, 0.5, "Title", 'M', "Black");
	drawMidLabel(7.5, 9, 3, 0.5, "hirer", 'M', "Black");
	drawMidLabel(9.5, 9, 3, 0.5, "Expiry Date", 'M', "Black");
}