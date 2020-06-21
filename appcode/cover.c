#include "cover.h"
void cover_page() {
	icon_Front(7, 10);
	drawMidLabel(6, 4, 4, 0.5, "¤È¤¢¤ëÄ§Ðg¤Î½û‡í•øð^ v1.0",'C',"Black");

	//login button
	SetPenSize(1);
	usePredefinedButtonColors(4);
	if (button(GenUIID(0), 7, 3, 2, 0.6, "Login")) {
		select_status = "";
		cover_page_flag = 0;
		login_page_flag = 1;
	}
}