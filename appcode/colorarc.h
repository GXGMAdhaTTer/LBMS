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

#include "HSL2RGB.h"

#include "linkedlist.h"

#define PI 3.1415926535

int ins = 0;

void KeyboardEventProcess(int button, int event);

typedef struct {
	double cx, cy;
	double r;
	double start, sweep;
	double density;
	string color;
} *ArcT;

void Initcolor();
void InitArcList();
void Drawarcs(void* curarc);
ArcT FindArc(linkedlistADT alist, int sum);
string color[180];
linkedlistADT arclist;
ArcT curArc = NULL;
double winWid = 0, winHei = 0;

void Main()
{
	InitGraphics();
	registerKeyboardEvent(KeyboardEventProcess);
	winWid = GetWindowWidth(), winHei = GetWindowHeight();
	SetPenColor("Black");
	SetPenSize(1);
	Initcolor();
	arclist = NewLinkedList();
	InitArcList();
	TraverseLinkedList(arclist, Drawarcs);
}

void KeyboardEventProcess(int button, int event) {
	curArc = FindArc(arclist, ins);
	switch (event) {
	case KEY_DOWN:
		switch (button) {
		case VK_RIGHT:
			if (ins > 0) {
				ins--;
				curArc->density = 1;
			}
			TraverseLinkedList(arclist, Drawarcs);
			break;
		case VK_LEFT:
			if (ins < 180) {
				ins++;
				curArc->density = 0;
			}
			TraverseLinkedList(arclist, Drawarcs);
			break;
		}
	case KEY_UP:
		break;
	}
}

void InitArcList() {
	ArcT aptr;
	int i;
	for (i = 0; i < 180; i++) {
		aptr = GetBlock(sizeof(*aptr));
		aptr->cx = winWid / 2.0;
		aptr->cy = winHei / 2.0;
		aptr->r = 3;
		aptr->start = 1.0 * i;
		aptr->sweep = 1;
		aptr->density = 1;
		aptr->color = color[i];
		InsertNode(arclist, NULL, aptr);
	}
}

void Drawarcs(void* curarc) {
	ArcT aptr = (ArcT)curarc;
	string color = GetPenColor();
	StartFilledRegion(aptr->density);
	SetPenColor(aptr->color);
	MovePen(aptr->cx, aptr->cy);
	DrawLine(aptr->r * cos(aptr->start * PI / 180), aptr->r * sin(aptr->start * PI / 180));
	DrawArc(aptr->r, aptr->start, aptr->sweep);
	DrawLine(-aptr->r * cos((aptr->start + aptr->sweep) * PI / 180),
		-aptr->r * sin((aptr->start + aptr->sweep) * PI / 180));
	EndFilledRegion();
	SetPenColor(color);
}

ArcT FindArc(linkedlistADT alist, int sum) {
	linkedlistADT Fnode = NULL, ptr;
	ptr = NextNode(alist, alist);
	if (ptr == NULL) return NULL;
	double angle;
	angle = sum * 1.0;
	Fnode = ptr;
	while (NextNode(alist, ptr) != NULL) {
		ptr = NextNode(arclist, ptr);
		if (angle > ((ArcT)NodeObj(alist, ptr))->start)
			Fnode = ptr;
	}

	return (ArcT)NodeObj(alist, Fnode);
}

void Initcolor() {
	double r = 0, g = 0, b = 0;
	int i = 0;
	double* rr, * gg, * bb;
	double h = 0, s = 1, l = 0.5;
	rr = &r, gg = &g, bb = &b;

	for (i = 0; i < 180; i++) {
		h = i * 1.0 / 180;
		HSL2RGB(h, s, l, rr, gg, bb);
		color[i] = GetBlock(sizeof(*color[i]));
		sprintf(color[i], "%d", i);
		DefineColor(color[i], *rr, *gg, *bb);
	}
}