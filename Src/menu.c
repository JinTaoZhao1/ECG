#include "menu.h"

void Menu_InitCtrl(Menu_Ctrl* menu_ctrl)
{
	menu_ctrl->menu_items[0].menulevel = Menu_Level0; /* ���˵��ȼ�Ϊ0 */	
	menu_ctrl->menu_items[0].name = "root"; /* ���˵���λroot */
	menu_ctrl->menu_items[0].order = 0; /* ���˵�λ�� */
	menu_ctrl->menu_items[0].parent_menu = NULL; /* ���˵� */
	menu_ctrl->menu_items[0].peer_menu_last = NULL; /* ͬ���˵���һ�� */
	menu_ctrl->menu_items[0].peer_menu_next = NULL; /* ͬ���˵���һ�� */
	menu_ctrl->menu_items[0].sub_menu_first = NULL; /* �Ӳ˵���һ�� */
	menu_ctrl->menu_items[0].sub_menu_last = NULL; /* �Ӳ˵��ڶ��� */ 
	
	menu_ctrl->menu_item_now = 0; /* ��ǰ�˵��� */
	menu_ctrl->menu_items_index = 1; /* ��ǰ�˵�����ʹ�ó��� */
}

void Menu_Start(Menu_Ctrl *menu_ctrl)
{
	menu_ctrl->menu_item_now = 1;
	Menu_Item *menu_cur_item = &(menu_ctrl->menu_items[menu_ctrl->menu_item_now]);
	menu_cur_item->menu_show->menu_load(menu_cur_item->name);
}

uint8_t Menu_CreateNewSubMenu(Menu_Ctrl* menu_ctrl,char *name,MenuLevel maxlevel,Menu_Show* menu_show,Menu_Task* menu_task)
{
  /* ʹ�ó��ȴ����ܳ��� */
	if(menu_ctrl->menu_items_index >= MAX_MENU_LENGTH)
		return 0;
	
  /* ��ȡ�����븸��˵� */
	Menu_Item *menu_sub_item = &(menu_ctrl->menu_items[menu_ctrl->menu_items_index]);
	Menu_Item *menu_par_item = &(menu_ctrl->menu_items[menu_ctrl->menu_item_now]);
	
  /*
	if(maxlevel > 0)
		menu_new_item->maxlevel = maxlevel;
	else
		menu_new_item->maxlevel = menu_cur_item->maxlevel;
	*/
  
	menu_sub_item->menulevel = menu_par_item->menulevel + 1; /* �Ӳ˵��ȼ�Ϊ���˵��ȼ� + 1 */
	menu_sub_item->name = name; /* �Ӳ˵��� */
	menu_sub_item->order = menu_ctrl->menu_items_index; /* �Ӳ˵�λ�� */
	menu_sub_item->parent_menu = menu_par_item; /* ָ�����˵� */
	menu_sub_item->peer_menu_last = menu_sub_item->peer_menu_next = NULL; /* ��ʼ��ͬ�����ڲ˵���Ϊ�� */
	menu_sub_item->sub_menu_first = menu_sub_item->sub_menu_last = NULL; /* ��ʼ����β�Ӳ˵���Ϊ�� */
	
  menu_sub_item->menu_show = menu_show; /* ���ò˵���ʾ */
	menu_sub_item->menu_task = menu_task; /* ����ĩ������ */
  
	if(menu_par_item->sub_menu_first == NULL) /* �˵������� */
		menu_par_item->sub_menu_first = menu_par_item->sub_menu_last = menu_sub_item;
	else{ /* �˵������� */
		menu_par_item->sub_menu_last->peer_menu_next = menu_sub_item;
		menu_sub_item->peer_menu_last = menu_par_item->sub_menu_last;
		menu_par_item->sub_menu_last = menu_sub_item;
	}
  
	menu_ctrl->menu_items_index++;
	return 1;
}
/*
*Function:Menu_Enter
*Brief:������Ŀ¼
*/
void Menu_Enter(Menu_Ctrl *menu_ctrl)
{
	Menu_Item *menu_cur_item = &(menu_ctrl->menu_items[menu_ctrl->menu_item_now]);
  
  if(menu_cur_item->sub_menu_first == NULL && menu_cur_item->menu_task->isRun == 0){ /* ���Ӳ˵�Ϊĩ��������δ����*/
    menu_cur_item->menu_show->menu_exit(menu_cur_item->name); /* �˳���ǰ�˵����� */
    menu_cur_item->menu_task->menu_run(menu_cur_item->name); /* ִ�е�ǰ������ */
    menu_cur_item->menu_task->isRun = 1;
  }else if(menu_cur_item->sub_menu_first != NULL){ /* ���Ӳ˵� */
    menu_cur_item->menu_show->menu_exit(menu_cur_item->name); /* �˳���ǰ�˵����� */
    menu_cur_item->sub_menu_first->menu_show->menu_load(menu_cur_item->sub_menu_first->name); /* �����Ӳ˵���һ������ */
    menu_ctrl->menu_item_now = menu_cur_item->sub_menu_first->order; /* ָ���Ӳ˵���һ�� */
  }
}

void Menu_Exit(Menu_Ctrl *menu_ctrl)
{
	Menu_Item *menu_cur_item = &(menu_ctrl->menu_items[menu_ctrl->menu_item_now]);
	
	if(menu_cur_item->sub_menu_first == NULL && menu_cur_item->menu_task->isRun == 1){ /* ���Ӳ˵�Ϊĩ����������ִ�� */
		menu_cur_item->menu_task->menu_stop(menu_cur_item->name); /* ֹͣ��ǰ������ */
		menu_cur_item->menu_show->menu_load(menu_cur_item->parent_menu->name); /* ���ص�ǰ�˵����� */
    
	} else if(menu_cur_item->parent_menu != NULL){
    menu_cur_item->menu_show->menu_exit(menu_cur_item->name); /* �˳���ǰ�˵����� */
    menu_cur_item->parent_menu->menu_show->menu_exit(menu_cur_item->parent_menu->name); /* ���ظ��˵����� */
    menu_ctrl->menu_item_now = menu_cur_item->parent_menu->order; /* ָ�򸸲˵� */
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
