#ifndef __UI_H__
#define __UI_H__

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "menu.h"
#include "menuconfig.h"

void UI_Init(void);
void UI_InitMenu(void);

void UI_EnterMenu(void);
void UI_ExitMenu(void);
void UI_SwitchMenu(uint8_t dir);

#endif
