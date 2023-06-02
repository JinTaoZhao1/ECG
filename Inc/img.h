#ifndef __IMG_H__
#define __IMG_H__

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "oled.h"

typedef struct{
	char* name;
	uint8_t height;
	uint8_t width;
	uint8_t x0;
	uint8_t y0;
	uint8_t *data;
}IMG_Info;

void IMG_LoadImg(char *name);
#endif
