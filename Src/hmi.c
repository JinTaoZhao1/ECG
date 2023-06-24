#include "hmi.h"
const uint8_t pages_txt_length[PAGE_NUM]={PAGE0_TXT_LENGTH,PAGE1_TXT_LENGTH,PAGE2_TXT_LENGTH,PAGE3_TXT_LENGTH,PAGE4_TXT_LENGTH};
const uint8_t pages_num_length[PAGE_NUM]={PAGE0_NUM_LENGTH,PAGE1_NUM_LENGTH,PAGE2_NUM_LENGTH,PAGE3_NUM_LENGTH,PAGE4_NUM_LENGTH};
const uint8_t pages_btn_length[PAGE_NUM]={PAGE0_BTN_LENGTH,PAGE1_BTN_LENGTH,PAGE2_BTN_LENGTH,PAGE3_BTN_LENGTH,PAGE4_BTN_LENGTH};
Page pages[PAGE_NUM];
uint8_t currentPage;
/***********
ҳ���ʼ��
***********/
void HMI_Init(void)
{
	uint8_t i;
	
	//��ʼ��
	for(i=0;i<PAGE_NUM;i++)
	{
		pages[i].txt_length=pages_txt_length[i];
		pages[i].num_length=pages_num_length[i];
		pages[i].btn_length=pages_btn_length[i];
	}
	//�Զ��л���ҳ
	HMI_ChangePage(PAGE_DEFAULT);
}
/***********
��ҳ
***********/
void HMI_ChangePage(uint8_t page)
{
	char cmd[20];
	
	if(page>=PAGE_NUM||currentPage==page)
		return;
	currentPage=page;
	
	sprintf(cmd,"page page%d\xff\xff\xff",page);
	Serial_SendString(huart2,cmd);
}
/***********
�޸��ı�
***********/
void HMI_ChangeTxt(uint8_t page,uint8_t txt,char *text)
{
	char cmd[30];
	if(page>=PAGE_NUM||txt>pages[page].txt_length)
		return;
	sprintf(cmd,"page%d.t%d.txt=\"%s\"\xff\xff\xff",page,txt,text);
	//printf(cmd,"%s");
	Serial_SendString(huart2,cmd);
}
/***********
�޸ĸ�����
***********/
void HMI_ChangeTxtFloat(uint8_t page,uint8_t txt,float value)
{
	char cmd[30];
	if(page>PAGE_NUM-1||txt>pages[page].txt_length)
		return;
	sprintf(cmd,"page%d.t%d.txt=\"%.4f\"\xff\xff\xff",page,txt,value);
	Serial_SendString(huart2,cmd);
}
/***********
�޸�����
***********/
void HMI_ChangeNum(uint8_t page,uint8_t num,uint16_t value)
{
	char cmd[30];
	if(page>PAGE_NUM-1||num>pages[page].num_length)
		return;
	sprintf(cmd,"page%d.n%d.val=%d\xff\xff\xff",page,num,value);
	Serial_SendString(huart2,cmd);
}
/***********
ĳҳ�ɲ����ؼ���0
***********/
void HMI_ClearAll(uint8_t page)
{
	char cmd[30];
	uint8_t i;
	
	for(i=0;i<pages[page].num_length;i++)
	{
		sprintf(cmd,"page%d.n%d.val=%d\xff\xff\xff",page,i,0);
		Serial_SendString(huart2,cmd);
		HAL_Delay(20);
	}
	for(i=0;i<pages[page].txt_length-1;i++)
	{
		sprintf(cmd,"page%d.t%d.txt=\"%s\"\xff\xff\xff",page,i,"none");
		Serial_SendString(huart2,cmd);
		HAL_Delay(20);
	}
}
