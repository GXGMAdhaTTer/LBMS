#include "icons.h"

void icon_Administrator(double cx, double cy) {
	string color = GetPenColor();
	SetPenColor("Gray");
	SetPenSize(4);
	MovePen(cx, cy);
	DrawArc(0.3,0, 360);
	MovePen(cx-0.3, cy - 0.3);
	DrawArc(0.5, 90, 90);
	MovePen(cx + 0.15, cy - 0.7);
	DrawArc(0.1, 0, 360);
	MovePen(cx + 0.05, cy - 0.6);
	DrawLine(0, 0.3);
	MovePen(cx + 0.05, cy - 0.4);
	DrawLine(0.1, 0);
	MovePen(cx + 0.05, cy - 0.5);
	DrawLine(0.1, 0);
	SetPenColor(color);
}