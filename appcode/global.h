#pragma once
static double winwidth, winheight;

static double buttonWidth = 2.0;
static double buttonHeight = 0.5;
static double interval = 3.4;

bool menu_flag;
bool login_page_flag;
bool guide_page_flag;
bool about_page_flag;
bool password_page_flag;
bool initial_Administrator_flag;
bool initial_Reader_flag;

bool charactor;

string select_status;

static char Administrator_AccountName[20] = "";
static char Administrator_Password[20] = "";