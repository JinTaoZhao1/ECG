#ifndef __OLED_H__
#define __OLED_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "i2c.h"


#define OLED_ADDRESS 0x78
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_PAGE OLED_HEIGHT/8

#define OLED_CMD 0x00
#define OLED_DATA 0x40

#define ASC2_1206 12
#define ASC2_1608 16
#define ASC2_2412 24

extern uint8_t OLED_GRAM[OLED_PAGE][OLED_WIDTH];

void OLED_WR_Byte(uint8_t byte,uint8_t mode);
void OLED_Init(void);
void OLED_Refresh(void);
void OLED_GraChange(uint8_t dir,uint8_t maskbit);
void OLED_Clear(void);
void OLED_DrawPixel(uint8_t x,uint8_t y);
void OLED_DrawLine(int16_t x0,int16_t y0,int16_t x1,int16_t y1);
void OLED_DrawTriangle(int16_t x0,int16_t y0,int16_t x1,int16_t y1,int16_t x2,int16_t y2);
void OLED_DrawCircle(int16_t x0,int16_t y0,int16_t radius);
void OLED_DrawRectangle(int16_t x0,int16_t y0,int16_t x1,int16_t y1);
int16_t OLED_DrawChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1);
void OLED_DrawString(uint8_t x0,uint8_t y0,char* str,uint8_t size);
void OLED_DrawNumber(uint8_t x0,uint8_t y0,int number,uint8_t size);
void OLED_DrawXBM(uint8_t x0,uint8_t y0,uint8_t width,uint8_t height,const uint8_t *img);

#endif
