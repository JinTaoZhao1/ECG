#include "menu.h"

void Menu_InitCtrl(Menu_Ctrl* menu_ctrl)
{
	menu_ctrl->menu_items[0].menulevel = Menu_Level0; /* 根菜单等级为0 */	
	menu_ctrl->menu_items[0].name = "root"; /* 根菜单名位root */
	menu_ctrl->menu_items[0].order = 0; /* 根菜单位置 */
	menu_ctrl->menu_items[0].parent_menu = NULL; /* 父菜单 */
	menu_ctrl->menu_items[0].peer_menu_last = NULL; /* 同级菜单上一项 */
	menu_ctrl->menu_items[0].peer_menu_next = NULL; /* 同级菜单下一项 */
	menu_ctrl->menu_items[0].sub_menu_first = NULL; /* 子菜单第一项 */
	menu_ctrl->menu_items[0].sub_menu_last = NULL; /* 子菜单第二项 */ 
	
	menu_ctrl->menu_item_now = 0; /* 当前菜单项 */
	menu_ctrl->menu_items_index = 1; /* 当前菜单数组使用长度 */
}

void Menu_Start(Menu_Ctrl *menu_ctrl)
{
	menu_ctrl->menu_item_now = 1;
	Menu_Item *menu_cur_item = &(menu_ctrl->menu_items[menu_ctrl->menu_item_now]);
	menu_cur_item->menu_show->menu_load(menu_cur_item->name);
}

uint8_t Menu_CreateNewSubMenu(Menu_Ctrl* menu_ctrl,char *name,MenuLevel maxlevel,Menu_Show* menu_show,Menu_Task* menu_task)
{
  /* 使用长度大于总长度 */
	if(menu_ctrl->menu_items_index >= MAX_MENU_LENGTH)
		return 0;
	
  /* 获取子项与父项菜单 */
	Menu_Item *menu_sub_item = &(menu_ctrl->menu_items[menu_ctrl->menu_items_index]);
	Menu_Item *menu_par_item = &(menu_ctrl->menu_items[menu_ctrl->menu_item_now]);
	
  /*
	if(maxlevel > 0)
		menu_new_item->maxlevel = maxlevel;
	else
		menu_new_item->maxlevel = menu_cur_item->maxlevel;
	*/
  
	menu_sub_item->menulevel = menu_par_item->menulevel + 1; /* 子菜单等级为父菜单等级 + 1 */
	menu_sub_item->name = name; /* 子菜单名 */
	menu_sub_item->order = menu_ctrl->menu_items_index; /* 子菜单位置 */
	menu_sub_item->parent_menu = menu_par_item; /* 指定父菜单 */
	menu_sub_item->peer_menu_last = menu_sub_item->peer_menu_next = NULL; /* 初始化同级相邻菜单项为空 */
	menu_sub_item->sub_menu_first = menu_sub_item->sub_menu_last = NULL; /* 初始化首尾子菜单项为空 */
	
  menu_sub_item->menu_show = menu_show; /* 设置菜单显示 */
	menu_sub_item->menu_task = menu_task; /* 设置末级任务 */
  
	if(menu_par_item->sub_menu_first == NULL) /* 菜单无子项 */
		menu_par_item->sub_menu_first = menu_par_item->sub_menu_last = menu_sub_item;
	else{ /* 菜单有子项 */
		menu_par_item->sub_menu_last->peer_menu_next = menu_sub_item;
		menu_sub_item->peer_menu_last = menu_par_item->sub_menu_last;
		menu_par_item->sub_menu_last = menu_sub_item;
	}
  
	menu_ctrl->menu_items_index++;
	return 1;
}
/*
*Function:Menu_Enter
*Brief:进入子目录
*/
void Menu_Enter(Menu_Ctrl *menu_ctrl)
{
	Menu_Item *menu_cur_item = &(menu_ctrl->menu_items[menu_ctrl->menu_item_now]);
  
  if(menu_cur_item->sub_menu_first == NULL && menu_cur_item->menu_task->isRun == 0){ /* 无子菜单为末项且任务未运行*/
    menu_cur_item->menu_show->menu_exit(menu_cur_item->name); /* 退出当前菜单内容 */
    menu_cur_item->menu_task->menu_run(menu_cur_item->name); /* 执行当前项任务 */
    menu_cur_item->menu_task->isRun = 1;
  }else if(menu_cur_item->sub_menu_first != NULL){ /* 有子菜单 */
    menu_cur_item->menu_show->menu_exit(menu_cur_item->name); /* 退出当前菜单内容 */
    menu_cur_item->sub_menu_first->menu_show->menu_load(menu_cur_item->sub_menu_first->name); /* 加载子菜单第一项内容 */
    menu_ctrl->menu_item_now = menu_cur_item->sub_menu_first->order; /* 指向子菜单第一项 */
  }
}

void Menu_Exit(Menu_Ctrl *menu_ctrl)
{
	Menu_Item *menu_cur_item = &(menu_ctrl->menu_items[menu_ctrl->menu_item_now]);
	
	if(menu_cur_item->sub_menu_first == NULL && menu_cur_item->menu_task->isRun == 1){ /* 无子菜单为末项且任务在执行 */
		menu_cur_item->menu_task->menu_stop(menu_cur_item->name); /* 停止当前项任务 */
		menu_cur_item->menu_show->menu_load(menu_cur_item->parent_menu->name); /* 加载当前菜单内容 */
    
	} else if(menu_cur_item->parent_menu != NULL){
    menu_cur_item->menu_show->menu_exit(menu_cur_item->name); /* 退出当前菜单内容 */
    menu_cur_item->parent_menu->menu_show->menu_exit(menu_cur_item->parent_menu->name); /* 加载父菜单内容 */
    menu_ctrl->menu_item_now = menu_cur_item->parent_menu->order; /* 指向父菜单 */
  }
}

void Menu_Switch(Menu_Ctrl *menu_ctrl,uint8_t dir)
{	
	Menu_Item *menu_last_item = &(menu_ctrl->menu_items[menu_ctrl->menu_item_now]);
	
	if(dir){
    if(menu_last_item->peer_menu_next != NULL){
      menu_ctrl->menu_item_now = menu_last_item->peer_menu_next->order;
      menu_last_item->menu_show->menu_exit(menu_last_item->name);
      menu_last_item->peer_menu_next->menu_show->menu_load(menu_last_item->peer_menu_next->name);
    }
  }
	else{
    if(menu_last_item->peer_menu_last != NULL){
      menu_ctrl->menu_item_now = menu_last_item->peer_menu_last->order;
      menu_last_item->menu_show->menu_exit(menu_last_item->name);
      menu_last_item->peer_menu_last->menu_show->menu_load(menu_last_item->peer_menu_last->name);
     }
	}
}

void Menu_Enter_t(Menu_Ctrl *menu_ctrl)
{
	Menu_Item *menu_cur_item = &(menu_ctrl->menu_items[menu_ctrl->menu_item_now]);
	menu_ctrl->menu_item_now = menu_cur_item->sub_menu_first->order;
}

uint8_t Menu_Enter_t_byname(Menu_Ctrl *menu_ctrl,char *name)
{
	Menu_Item *menu_cur_item = &(menu_ctrl->menu_items[menu_ctrl->menu_item_now]);
	Menu_Item *menu_sub_item = menu_cur_item->sub_menu_first;
	while(strcmp(name,menu_sub_item->name)!=0 && menu_sub_item->peer_menu_next!=NULL)
		menu_sub_item = menu_sub_item->peer_menu_next;
	
	if(strcmp(name,menu_sub_item->name) == 0){
		menu_ctrl->menu_item_now = menu_sub_item->order;
		return 1;
	}
	
	return 0;
}

void Menu_Exit_t(Menu_Ctrl *menu_ctrl)
{
	Menu_Item *menu_cur_item = &(menu_ctrl->menu_items[menu_ctrl->menu_item_now]);
	menu_ctrl->menu_item_now = menu_cur_item->parent_menu->order;
}

void Menu_Switch_t(Menu_Ctrl *menu_ctrl,uint8_t dir)
{
	Menu_Item *menu_last_item = &(menu_ctrl->menu_items[menu_ctrl->menu_item_now]);
	if(dir){
    if(menu_last_item->peer_menu_next != NULL)
      menu_ctrl->menu_item_now = menu_last_item->peer_menu_next->order;
	}
  else{
    if(menu_last_item->peer_menu_last != NULL)
		menu_ctrl->menu_item_now = menu_last_item->peer_menu_last->order;
  }
}

#ifdef MENU_DEBUG
static void Menu_Print(Menu_Item* menu_item)
{
    while(menu_item!=NULL){
        printf("%s/",menu_item->name);
        menu_item = menu_item->parent_menu;
    }
    printf("\n");
}


void Menu_Ergodic(Menu_Item* menu_item)
{
    Menu_Print(menu_item);

    Menu_Item *menu_sub_item = menu_item->sub_menu_first;

    while(menu_sub_item!=NULL){
        Menu_Ergodic(menu_sub_item);
        menu_sub_item = menu_sub_item->peer_menu_next;
    }
}
#endif
