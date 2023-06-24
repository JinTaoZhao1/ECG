#include "ui.h"

extern uint8_t OLED_GRAM[OLED_PAGE][OLED_WIDTH];

Menu_Ctrl *menu_ctrl = NULL;
uint8_t operation = 2;

void UI_Init()
{
  /* 初始化OLED屏幕 */
  OLED_Init();
  
  OLED_Clear();
  //OLED_DrawString(0,0,"122056",ASC2_1206);
  OLED_Refresh();
  /* 初始化菜单栏 */
  
	//UI_InitMenu();
}

void UI_InitMenu()
{
  menu_ctrl = malloc(sizeof(Menu_Ctrl));
	
  Menu_InitCtrl(menu_ctrl);

	Menu_CreateNewSubMenu(menu_ctrl,"Wifi",1,&menu_show_wifi,&menu_task_wifi);
	Menu_CreateNewSubMenu(menu_ctrl,"Shell",1,&menu_show_shell,&menu_task_shell);
	Menu_CreateNewSubMenu(menu_ctrl,"Info",1,&menu_show_info,&menu_task_info);
	//Menu_CreateNewSubMenu(menu_ctrl,"Home",1,&menu_show_info,&menu_general_task);
  
  //Menu_Enter_t_byname(menu_ctrl,"Wifi");
  
	Menu_Start(menu_ctrl);
}

void UI_EnterMenu(){
  Menu_Enter(menu_ctrl);
}

void UI_ExitMenu(){
  Menu_Exit(menu_ctrl);
}

void UI_SwitchMenu(uint8_t dir){
  Menu_Switch(menu_ctrl,dir);
}

