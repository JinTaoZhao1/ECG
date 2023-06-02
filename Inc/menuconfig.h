#ifndef __MENUSHOW_H__
#define __MENUSHOW_H__

#include "menu.h"
#include "oled.h"
#include "img.h"

extern Menu_Show menu_show_wifi;
extern Menu_Task menu_task_wifi;

extern Menu_Show menu_show_info;
extern Menu_Task menu_task_info;

extern Menu_Show menu_show_shell;
extern Menu_Task menu_task_shell;

extern Menu_Task menu_general_task;

void MenuShow_Load_WiFi(void *params);
void MenuShow_Exit_WiFi(void *params);
void MenuShow_Run_WiFi(void* params);
void MenuShow_Stop_WiFi(void *params);

void MenuShow_Load_Info(void* params);
void MenuShow_Exit_Info(void* params);
void MenuShow_Run_Info(void* params);
void MenuShow_Stop_Info(void *params);

void MenuShow_Load_Shell(void* params);
void MenuShow_Exit_Shell(void* params);
void MenuShow_Run_Shell(void* params);
void MenuShow_Stop_Shell(void *params);

#endif
