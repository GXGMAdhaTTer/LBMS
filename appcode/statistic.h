#pragma once
#ifndef STATISTIC_H_INCLUDED
#define STATISTIC_H_INCLUDED
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
#include "global.h"

void statistic_page(DB_Book* library);
void initClassDate(DB_Book* library);
void drawDateLine(int n, int t);
void drawHistogram(int dtype, DB_Book* library);
void drawPiechart(double cx, double cy, int nummale, int numfemale);
void showPopular(char* popularformen, char* popularforwomen);
#endif