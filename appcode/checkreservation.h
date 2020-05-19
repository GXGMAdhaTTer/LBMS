#pragma once
#ifndef CHECKRESERVATION_H_INCLUDED
#define CHECKRESERVATION_H_INCLUDED
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
void DeleteReq(struct Request* a, int M, int* n);
static void initRequest(int x);
void DrawRequest(int x);
void checkreservation_page();

#endif