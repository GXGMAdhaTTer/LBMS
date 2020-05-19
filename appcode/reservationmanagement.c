#include "reservationmanagement.h"

typedef struct {
	int id;
	double cx, cy;
	string ISBNcode;
	string Title;
	string Expirydate;
} *ReservationT;

int l = 5;

linkedlistADT reservationlist;

void reservation_page() {
	reservationlist = NewLinkedList();
	InitReservationList();
	TraverseLinkedList(reservationlist, DrawReservations);
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

static void InitReservationList() {
	ReservationT aptr;
	int i;
	for (i = 0; i < l; i++) {	
		aptr = GetBlock(sizeof(*aptr));
		aptr->id = i;
		aptr->cx = 2;
		aptr->cy = 8.5 - i * 0.5;
		aptr->ISBNcode = "978710000000";
		aptr->Title = "´óÍþÌìÁú";
		aptr->Expirydate = "2020.05.12";
		InsertNode(reservationlist, NULL, aptr);
	}
}

void DrawReservations(void* curreservation) {
	
	ReservationT aptr = (ReservationT)curreservation;
	double ccx = aptr->cx;
	double ccy = aptr->cy;

	drawMidLabel(ccx, ccy, 3, 0.5, aptr->ISBNcode, 'M', "Black");
	drawMidLabel(ccx + 3, ccy, 3, 0.5, aptr->Title, 'M', "Black");
	drawMidLabel(ccx + 6, ccy, 3, 0.5, aptr->Expirydate, 'M', "Black");
	
	usePredefinedButtonColors(4);
	if (button(GenUIID(aptr->id), aptr->cx+9.5, aptr->cy+0.05, 2, buttonHeight-0.1, "Cancel")) {
		DeleteNode(reservationlist, aptr, compare);
	}
	MovePen(ccx + 0.2, ccy);
	SetPenColor("Light Gray");
	DrawLine(11.6, 0);

}

void DrawButton(void* curreservation) {
	ReservationT aptr = (ReservationT)curreservation;
}

bool compare(void* list, void* curreservation) {
	return TRUE;
}


