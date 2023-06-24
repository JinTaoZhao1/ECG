#ifndef __HMI_H__
#define __HMI_H__

#include "serial.h"
#include "stdint.h"
#include "stdio.h"

#define PAGE_NUM 5

#define PAGE_DEFAULT 1

#define PAGE0_TXT_LENGTH 1
#define PAGE1_TXT_LENGTH 1
#define PAGE2_TXT_LENGTH 1
#define PAGE3_TXT_LENGTH 1
#define PAGE4_TXT_LENGTH 1

#define PAGE0_NUM_LENGTH 1 
#define PAGE1_NUM_LENGTH 1
#define PAGE2_NUM_LENGTH 1
#define PAGE3_NUM_LENGTH 1
#define PAGE4_NUM_LENGTH 1

#define PAGE0_BTN_LENGTH 1 
#define PAGE1_BTN_LENGTH 1
#define PAGE2_BTN_LENGTH 1
#define PAGE3_BTN_LENGTH 1
#define PAGE4_BTN_LENGTH 1
typedef struct{
	uint8_t txt_length;
	uint8_t num_length;
	uint8_t btn_length;
}Page;


void HMI_Init(void);
void HMI_ChangePage(uint8_t page);
void HMI_ChangeTxt(uint8_t page,uint8_t txt,char *text);
void HMI_ChangeTxtFloat(uint8_t page,uint8_t txt,float value);
void HMI_ChangeNum(uint8_t page,uint8_t num,uint16_t value);
void HMI_ClearAll(uint8_t page);

#endif
