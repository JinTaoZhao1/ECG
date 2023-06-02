#include "menuconfig.h"

Menu_Task menu_general_task = {
	.menu_run = NULL,
	.menu_stop = NULL,
};

//
Menu_Show menu_show_wifi = {
	.menu_load = MenuShow_Load_WiFi,
	.menu_exit = MenuShow_Exit_WiFi,
};

Menu_Task menu_task_wifi = {
  .menu_run = MenuShow_Run_WiFi,
  .menu_stop = MenuShow_Stop_WiFi,
};

void MenuShow_Load_WiFi(void *params)
{	
	OLED_Clear();
	
	for(uint8_t i = 0;i <= 8;i+=2){
		OLED_DrawString(50,50,"WIFI",ASC2_1206);
		IMG_LoadImg("wifi");
		OLED_GraChange(1,i);
		OLED_Refresh();
	}
		
	OLED_Clear();
	OLED_DrawString(50,50,"WIFI",ASC2_1206);
	IMG_LoadImg("wifi");
	OLED_Refresh();
}

void MenuShow_Exit_WiFi(void *params)
{
	for(uint8_t i = 0;i <= 8;i+=2){
		OLED_DrawString(50,50,"WIFI",ASC2_1206);
		IMG_LoadImg("wifi");
		OLED_GraChange(0,i);
		OLED_Refresh();
	}
	
	OLED_Clear();
}

void MenuShow_Run_WiFi(void* params)
{
  OLED_Clear();
	
	for(uint8_t i = 0;i <= 8;i+=2){
		OLED_DrawString(0,0,"WIFI:SJTU",ASC2_1206);
		OLED_DrawString(0,12,"PWD:7755883311ay",ASC2_1206);
		OLED_DrawString(0,24,"IP:127.0.0.1",ASC2_1206);
		OLED_DrawString(0,36,"STATE:CONNECTED",ASC2_1206);
		OLED_Refresh();
	}
	OLED_Clear();
	
  OLED_DrawString(0,0,"WIFI:SJTU",ASC2_1206);
	OLED_DrawString(0,12,"PWD:7755883311ay",ASC2_1206);
	OLED_DrawString(0,24,"IP:127.0.0.1",ASC2_1206);
	OLED_DrawString(0,36,"STATE:CONNECTED",ASC2_1206);
	OLED_Refresh();
}

void MenuShow_Stop_WiFi(void *params)
{  
  for(uint8_t i = 0;i <= 8;i+=2){
		OLED_DrawString(0,0,"WIFI:SJTU",ASC2_1206);
		OLED_DrawString(0,6,"PWD:7755883311ay",ASC2_1206);
		OLED_DrawString(0,12,"IP:127.0.0.1",ASC2_1206);
		OLED_DrawString(0,12,"STATE:CONNECTED",ASC2_1206);
		OLED_GraChange(0,i);
		OLED_Refresh();
	}
	
	OLED_Clear();
}


Menu_Show menu_show_info = {
	.menu_load = MenuShow_Load_Info,
	.menu_exit = MenuShow_Exit_Info,
};
Menu_Task menu_task_info = {
  .menu_run = MenuShow_Run_Info,
  .menu_stop = MenuShow_Stop_Info,
};
void MenuShow_Load_Info(void* params)
{
  OLED_Clear();
	
	for(uint8_t i = 0;i <= 8;i+=2){
		OLED_DrawString(50,50,"Info",ASC2_1206);
		IMG_LoadImg("info");
		OLED_GraChange(1,i);
		OLED_Refresh();
	}
		
	OLED_Clear();
	OLED_DrawString(50,50,"Info",ASC2_1206);
	IMG_LoadImg("info");
	OLED_Refresh();
}

void MenuShow_Exit_Info(void* params)
{
	for(uint8_t i = 0;i <= 8;i+=2){
		OLED_DrawString(50,50,"Info",ASC2_1206);
		IMG_LoadImg("info");
		OLED_GraChange(0,i);
		OLED_Refresh();
	}
	
	OLED_Clear();
}

void MenuShow_Run_Info(void* params)
{
	OLED_Clear();
	
	for(uint8_t i = 0;i <= 8;i+=2){
		OLED_DrawString(0,0,"MCU:STM32L496",ASC2_1206);
		OLED_DrawString(0,12,"ARM:Cortex-M4",ASC2_1206);
		OLED_DrawString(0,24,"SRAM:320KB",ASC2_1206);
		OLED_DrawString(0,36,"FLASH:1MB",ASC2_1206);
		OLED_GraChange(1,i);
		OLED_Refresh();
	}
	
	OLED_Clear();
  
	OLED_DrawString(0,0,"MCU:STM32L496",ASC2_1206);
	OLED_DrawString(0,12,"ARM:Cortex-M4",ASC2_1206);
	OLED_DrawString(0,24,"SRAM:320KB",ASC2_1206);
	OLED_DrawString(0,36,"FLASH:1MB",ASC2_1206);
	OLED_Refresh();
}
void MenuShow_Stop_Info(void *params)
{  
  	for(uint8_t i = 0;i <= 8;i+=2){
		OLED_DrawString(0,0,"MCU:STM32L496",ASC2_1206);
		OLED_DrawString(0,12,"ARM:Cortex-M4",ASC2_1206);
		OLED_DrawString(0,24,"SRAM:320KB",ASC2_1206);
		OLED_DrawString(0,36,"FLASH:1MB",ASC2_1206);
		OLED_GraChange(0,i);
		OLED_Refresh();
	}
	
	OLED_Clear();
}


Menu_Show menu_show_shell = {
	.menu_load = MenuShow_Load_Shell,
	.menu_exit = MenuShow_Exit_Shell,
};
Menu_Task menu_task_shell = {
  .menu_run = MenuShow_Run_Shell,
  .menu_stop = MenuShow_Stop_Shell,
};
void MenuShow_Load_Shell(void* params)
{
	OLED_Clear();
	
	for(uint8_t i = 0;i <= 8;i+=2){
		OLED_DrawString(50,50,"Shell",ASC2_1206);
		IMG_LoadImg("shell");
		OLED_GraChange(1,i);
		OLED_Refresh();
	}
		
	OLED_Clear();
	OLED_DrawString(50,50,"Shell",ASC2_1206);
	IMG_LoadImg("shell");
	OLED_Refresh();

}
void MenuShow_Exit_Shell(void* params)
{  
  for(uint8_t i = 0;i <= 8;i+=2){
		OLED_DrawString(50,50,"Shell",ASC2_1206);
		IMG_LoadImg("shell");
		OLED_GraChange(0,i);
		OLED_Refresh();
	}
	
	OLED_Clear();
}

void MenuShow_Run_Shell(void* params)
{
	OLED_Clear();
	
	for(uint8_t i = 0;i <= 8;i+=2){
		OLED_DrawString(0,0,">>",ASC2_1206);
		OLED_GraChange(1,i);
		OLED_Refresh();
	}
	
	OLED_Clear();
	OLED_DrawString(0,0,">>",ASC2_1206);
	OLED_Refresh();
}

void MenuShow_Stop_Shell(void *params)
{
	OLED_Clear();
	
	for(uint8_t i = 0;i <= 8;i+=2){
		OLED_DrawString(0,0,">>",ASC2_1206);
		OLED_GraChange(0,i);
		OLED_Refresh();
	}
	
	OLED_Clear();
}



