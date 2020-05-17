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
bool signup_page_flag;
bool accountsetting_page_flag;
bool booksearch_page_flag;
bool bookeditwindow_page_flag;
bool readerinformationwindow_page_flag;


bool charactor;

string select_status;

static char Administrator_AccountName[10] = "";
static char Administrator_Password[10] = "";

static char Reader_ID[10] = "";
static char Reader_Password[10] = "";
static char Reader_Name[10] = "";
static char Reader_Gender[10] = "";
static char Reader_Employer[10] = "";

