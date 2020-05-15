#include "icons.h"
#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <math.h>

#include "linkedlist.h"
#include "imgui.h"
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