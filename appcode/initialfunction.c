#include "initialfunction.h"
void initialAdministrator() {
	SetPenColor("Gray");
	icon_Editbook(2.7, 6.8);
	usePredefinedButtonColors(4);
	SetPenSize(1);
	if (button(GenUIID(0), 1.7, 5.2, buttonWidth, buttonHeight, "Edit Books")) {
		bookedit_page_flag = 1;
		initial_Administrator_flag = 0;
		select_status = "";
	}

	SetPenColor("Gray");
	icon_CheckRequests(6.1, 6.8);
	usePredefinedButtonColors(4);
	SetPenSize(1);
	if (button(GenUIID(0), 1.7+interval, 5.2, buttonWidth, buttonHeight, "Check Requests")) {
		checkreservation_page_flag = 1;
		initial_Administrator_flag = 0;
		select_status = "";
	}

	SetPenColor("Gray");
	icon_Readers(9.5, 6.8);
	usePredefinedButtonColors(4);
	SetPenSize(1);
	if (button(GenUIID(0), 1.7+2*interval, 5.2, buttonWidth, buttonHeight, "Readers")) {
		readermanagement_page_flag = 1;
		initial_Administrator_flag = 0;
		select_status = "";
	}

	SetPenColor("Gray");
	icon_Statistics(12.8, 6.8);
	usePredefinedButtonColors(4);
	SetPenSize(1);
	if (button(GenUIID(0), 1.7+3*interval, 5.2, buttonWidth, buttonHeight, "Statistics")) {
		select_status = "";
	}
}

void initialReader() {
	SetPenColor("Gray");
	icon_Reserve(2.7, 6.8);
	usePredefinedButtonColors(4);
	SetPenSize(1);
	if (button(GenUIID(0), 1.7, 5.2, buttonWidth, buttonHeight, "Reserve")) {
		bookreserve_page_flag = 1;
		initial_Reader_flag = 0;
		select_status = "";
	}

	SetPenColor("Gray");
	icon_Reservation(6.1, 6.8);
	usePredefinedButtonColors(4);
	SetPenSize(1);
	if (button(GenUIID(0), 1.7 + interval, 5.2, buttonWidth, buttonHeight, "Reservation")) {
		reservation_page_flag = 1;
		initial_Reader_flag = 0;
		select_status = "";
	}

	SetPenColor("Gray");
	icon_Return(9.5, 6.8);
	usePredefinedButtonColors(4);
	SetPenSize(1);
	if (button(GenUIID(0), 1.7 + 2 * interval, 5.2, buttonWidth, buttonHeight, "Renew")) {
		borrowing_page_flag = 1;
		initial_Reader_flag = 0;
		select_status = "";
	}

	SetPenColor("Gray");
	icon_Account(12.9, 6.8);
	usePredefinedButtonColors(4);
	SetPenSize(1);
	if (button(GenUIID(0), 1.7 + 3 * interval, 5.2, buttonWidth, buttonHeight, "Account")) {
		accountsetting_page_flag = 1;
		select_status = "";
	}
}