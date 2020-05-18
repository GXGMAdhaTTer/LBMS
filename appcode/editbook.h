#pragma once
#ifndef EDITBOOK_H_INCLUDED
#define EDITBOOK_H_INCLUDED
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
#include "reservebook.h"

void editbook_page();
//void search_by();
//void order_filter();
//void DrawBooks(int x);
void editbookinformationwindow(int x);
#endif