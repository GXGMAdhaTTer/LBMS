#include "icons.h"

void icon_Administrator(double cx, double cy) {
	string color = GetPenColor();
	SetPenColor("Gray");
	SetPenSize(4);
	MovePen(cx, cy);
	DrawArc(0.3, 0, 360);
	MovePen(cx - 0.3, cy - 0.3);
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

void icon_Reader(double rx, double ry) {
	string color = GetPenColor();
	SetPenColor("Gray");
	SetPenSize(4);
	MovePen(rx, ry);
	DrawArc(0.3, 0, 360);
	MovePen(rx + 0.2, ry - 0.8);
	DrawArc(0.5, 0, 180);
}

void icon_Editbook(double ex, double ey) {
	string color = GetPenColor();
	SetPenColor("Gray");
	SetPenSize(4);
	MovePen(ex, ey + 0.5);
	DrawLine(-0.5, 0);
	MovePen(ex - 0.5, ey + 0.5);
	DrawLine(0, -1.0);
	MovePen(ex - 0.5, ey - 0.5);
	DrawLine(1, 0);
	MovePen(ex + 0.5, ey - 0.5);
	DrawLine(0, 0.5);
	MovePen(ex + 0.5, ey + 0.5);
	DrawLine(-0.5, -0.5);
}

void icon_CheckRequests(double cx, double cy) {
	string color = GetPenColor();
	SetPenColor("Gray");
	SetPenSize(4);
	MovePen(cx - 0.25, cy);
	DrawLine(0.25, -0.25);
	MovePen(cx, cy - 0.25);
	DrawLine(0.5, 0.5);
	MovePen(cx + 0.5, cy + 0.25);
	DrawLine(0, 0.25);
	MovePen(cx + 0.5, cy + 0.5);
	DrawLine(-1.0, 0);
	MovePen(cx - 0.5, cy - 0.5);
	DrawLine(0, 1.0);
	MovePen(cx - 0.5, cy - 0.5);
	DrawLine(1.0, 0);
	MovePen(cx + 0.5, cy - 0.5);
	DrawLine(0, 0.25);
}

void icon_Readers(double rx, double ry) {
	string color = GetPenColor();
	SetPenColor("Gray");
	SetPenSize(4);
	MovePen(rx + 0.3, ry + 0.3);
	DrawArc(0.3, 0, 360);
	MovePen(rx + 0.5, ry - 0.5);
	DrawArc(0.5, 0, 180);
	MovePen(rx - 0.15, ry - 0.2);
	DrawLine(0.3, 0);
	MovePen(rx - 0.15, ry - 0.4);
	DrawLine(0.3, 0);
}

void icon_Statistics(double sx, double sy) {
	string color = GetPenColor();
	SetPenColor("Gray");
	SetPenSize(4);
	MovePen(sx, sy);
	DrawLine(0.5, 0);
	MovePen(sx, sy);
	DrawLine(0, 0.5);
	MovePen(sx + 0.5, sy);
	DrawArc(0.5, 0, 90);
	MovePen(sx - 0.25, sy + 0.25 * 1.732);
	DrawArc(0.5, 120, 210);
}

void icon_Reserve(double bx, double by) {
	string color = GetPenColor();
	SetPenColor("Gray");
	SetPenSize(4);
	MovePen(bx - 0.5, by + 0.5);
	DrawLine(1.0, 0);
	MovePen(bx - 0.5, by + 0.5);
	DrawLine(0, -1.0);
	MovePen(bx - 0.5, by - 0.5);
	DrawLine(0.5, 0);
	MovePen(bx + 0.5, by);
	DrawLine(0, 0.5);
	MovePen(bx - 0.25, by + 0.25);
	DrawLine(0.25, 0);
	MovePen(bx - 0.25, by);
	DrawLine(0.5, 0);
	MovePen(bx, by - 0.25);
	DrawLine(0.5, 0);
	MovePen(bx + 0.5, by - 0.25);
	DrawLine(-0.1, 0.1);
	MovePen(bx + 0.5, by - 0.25);
	DrawLine(-0.1, -0.1);
}

void icon_Reservation(double rx, double ry) {
	string color = GetPenColor();
	SetPenColor("Gray");
	SetPenSize(4);
	MovePen(rx, ry);
	DrawLine(0, 0.35);
	MovePen(rx, ry);
	DrawLine(0.25, -0.25);
	MovePen(rx + 0.5, ry);
	DrawArc(0.5, 0, 360);
}

void icon_Return(double bx, double by) {
	string color = GetPenColor();
	SetPenColor("Gray");
	SetPenSize(4);
	MovePen(bx - 0.5, by + 0.5);
	DrawLine(1.0, 0);
	MovePen(bx - 0.5, by + 0.5);
	DrawLine(0, -1.0);
	MovePen(bx - 0.5, by - 0.5);
	DrawLine(0.5, 0);
	MovePen(bx + 0.5, by);
	DrawLine(0, 0.5);
	MovePen(bx - 0.25, by + 0.25);
	DrawLine(0.25, 0);
	MovePen(bx - 0.25, by);
	DrawLine(0.5, 0);
	MovePen(bx, by - 0.25);
	DrawLine(0.5, 0);
	MovePen(bx, by - 0.25);
	DrawLine(0.1, 0.1);
	MovePen(bx, by - 0.25);
	DrawLine(0.1, -0.1);
}

void icon_Account(double rx, double ry) {
	string color = GetPenColor();
	SetPenColor("Gray");
	SetPenSize(4);
	MovePen(rx + 0.3, ry + 0.3);
	DrawArc(0.3, 0, 360);
	MovePen(rx, ry);
	DrawArc(0.5, 90, 90);
	MovePen(rx, ry - 0.5 / 3);
	DrawLine(0.5, 0);
	MovePen(rx, ry - 1.0 / 3);
	DrawLine(0.5, 0);
	MovePen(rx, ry - 0.5);
	DrawLine(0.5, 0);
}

void icon_Front(double fx, double fy) {
	string color = GetPenColor();
	SetPenColor("Gray");
	SetPenSize(4);
	MovePen(fx, fy);
	DrawArc(0.5, 90, 180);
	MovePen(fx, fy);
	DrawLine(2, 0);
	MovePen(fx - 0.924 / 3, fy - 0.333);
	DrawLine(2 + 0.924 / 3, 0);
	MovePen(fx - 0.924 / 3, fy - 0.667);
	DrawLine(2 + 0.924 / 3, 0);
	MovePen(fx, fy - 1);
	DrawLine(2.5, 0);
	MovePen(fx + 2, fy);
	DrawLine(0, -1);
	MovePen(fx - 0.5, fy - 0.5);
	DrawLine(0, -4);
	MovePen(fx, fy - 1.5);
	DrawLine(0, -3);
	MovePen(fx - 0.5, fy - 4.5);
	DrawArc(0.5, 180, 90);
	MovePen(fx, fy - 5);
	DrawLine(2.5, 0);
	MovePen(fx + 2.5, fy - 1);
	DrawLine(0, -4);
	MovePen(fx + 1.5, fy - 1.25);
	DrawLine(0, -1);
	MovePen(fx + 1.5, fy - 1.25);
	DrawLine(0.5, 0);
	MovePen(fx + 2, fy - 2.25);
	DrawLine(0, 1);
	MovePen(fx + 2, fy - 2.25);
	DrawLine(-0.5, 0);
}



