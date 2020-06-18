#pragma once
static double winwidth, winheight;

static double buttonWidth = 2.0;
static double buttonHeight = 0.5;
static double interval = 3.4;

bool menu_flag;
bool login_status;//登录状态

//控制每个页面是否显示
bool login_page_flag;
bool guide_page_flag;
bool about_page_flag;
bool sorry_page_flag;
bool sorry_page_flag_reader;
bool sorry_page_flag_administrator;

bool password_page_flag;
bool initial_Administrator_flag;
bool initial_Reader_flag;
bool signup_page_flag;
bool accountsetting_page_flag;
bool bookreserve_page_flag;
bool bookedit_page_flag;
bool readerinformationwindow_page_flag;
bool reservation_page_flag;
bool checkreservation_page_flag;
bool borrowing_page_flag;
bool readermanagement_page_flag;
bool cover_page_flag;
bool statistic_page_flag;


bool charactor;//判断是什么身份,1是读者，0是管理者

string select_status;

static char Administrator_AccountName[10] = "";
static char Administrator_Password[10] = "";

static char Reader_ID[11] = "";
static char Reader_Password[10] = "";
static char Reader_Name[10] = "";
static char Reader_Gender[10] = "";
static char Reader_Employer[10] = "";

