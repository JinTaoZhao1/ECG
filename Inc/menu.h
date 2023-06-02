#ifndef __MENU_H__
#define __MENU_H__

#include <stdint.h>
#include <stdio.h>
#include "string.h"

#define MAX_MENU_LENGTH 10

typedef enum{
	Menu_Level0,
	Menu_Level1,
	Menu_Level2,
	Menu_Level3,
} MenuLevel;

#define MAX_MENU_LEVEL Menu_Level3
typedef void (*Menu_CallFunc)(void* params);

typedef struct{
  uint8_t isRun;//运行状态
	Menu_CallFunc menu_run;//菜单项运行函数
	Menu_CallFunc menu_stop;//菜单项停止函数
}Menu_Task;
typedef struct{
	Menu_CallFunc menu_load;//菜单加载函数 
	Menu_CallFunc menu_exit;//菜单退出函数
}Menu_Show;

typedef struct _Menu_Item_t{
	MenuLevel menulevel;//菜单等级
	
	char *name;//菜单名
	
	uint8_t order;//序号 

	struct _Menu_Item_t *parent_menu;//父菜单
	struct _Menu_Item_t *peer_menu_last;
	struct _Menu_Item_t *peer_menu_next;//同级菜单链表 	
	struct _Menu_Item_t *sub_menu_first;//子菜单指向条目
	struct _Menu_Item_t *sub_menu_last;
	
	Menu_Show *menu_show;
	Menu_Task *menu_task;
}Menu_Item;

typedef struct _Menu_Ctrl_t{
	Menu_Item menu_items[MAX_MENU_LENGTH];
	uint8_t menu_item_now;
	uint8_t menu_items_index;
}Menu_Ctrl;


#define MENU_DEBUG

#ifdef MENU_DEBUG
static void Menu_Print(Menu_Item* menu_item);
void Menu_Ergodic(Menu_Item* menu_item);
#endif

void Menu_InitCtrl(Menu_Ctrl* menu_ctrl);
void Menu_Start(Menu_Ctrl *menu_ctrl);
uint8_t Menu_CreateNewSubMenu(Menu_Ctrl* menu_ctrl,char *name,MenuLevel maxlevel,Menu_Show* menu_show,Menu_Task* menu_task);
void Menu_Enter(Menu_Ctrl *menu_ctrl);
void Menu_Exit(Menu_Ctrl *menu_ctrl);
void Menu_Switch(Menu_Ctrl *menu_ctrl,uint8_t dir);
void Menu_Enter_t(Menu_Ctrl *menu_ctrl);
uint8_t Menu_Enter_t_byname(Menu_Ctrl *menu_ctrl,char *name);
void Menu_Exit_t(Menu_Ctrl *menu_ctrl);
void Menu_Switch_t(Menu_Ctrl *menu_ctrl,uint8_t dir);
#endif
