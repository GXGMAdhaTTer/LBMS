#pragma once
#ifndef ICONS_H_INCLUDED
#define ICONS_H_INCLUDED
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

void icon_Administrator(double cx, double cy);
void icon_Reader(double rx, double ry);
void icon_Editbook(double ex, double ey);
void icon_CheckRequests(double cx, double cy);
void icon_Readers(double rx, double ry);
void icon_Statistics(double sx, double sy);
void icon_Reserve(double bx, double by);
void icon_Reservation(double rx, double ry);
void icon_Return(double bx, double by);
void icon_Account(double rx, double ry);
void icon_Front(double fx, double fy);

#endif