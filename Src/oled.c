#include "oled.h"
#include "oledfont.h"

extern I2C_HandleTypeDef hi2c2;
uint8_t OLED_GRAM[OLED_PAGE][OLED_WIDTH];

/*
*Function:OLED_WR_Byte
*Brief:��OLED��Ļд������
*Params:
*@byte д���ֽ�
*@mode �ֽ�����	
	OLED_CMD ָ��
	OLED_DATA ����
*/
void OLED_WR_Byte(uint8_t byte,uint8_t mode)
{
	uint8_t data[2] = {mode,byte};
	HAL_I2C_Master_Transmit(&hi2c2,OLED_ADDRESS,data,2,50);
}

/*
*Function:OLED_Init
*Brief:��ʼ��OLED��Ļ
*Params:None
*/
void OLED_Init()
{
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD);// Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);
	
	OLED_Clear();
	
}
/*
*Function:OLED_Refresh
*Brief:ˢ��OLED��Ļ
*Params:None
*/
void OLED_Refresh()
{
	for(uint8_t i = 0;i < OLED_PAGE;i++){
		OLED_WR_Byte(0xB0 + i,OLED_CMD);
		OLED_WR_Byte(0x00,OLED_CMD);
		OLED_WR_Byte(0x10,OLED_CMD);
		
		for(uint8_t j = 0;j < OLED_WIDTH;j++)
			OLED_WR_Byte(OLED_GRAM[i][j],OLED_DATA);
	}
}
/*
*Function:OLED_Clear
*Brief:���OLED��Ļ
*Params:None
*/
void OLED_Clear()
{
	for(uint8_t i = 0;i < OLED_PAGE;i++)
	   for(uint8_t j = 0;j < 128;j++)
			 OLED_GRAM[i][j] = 0x00;
}
/*
*Function:OLED_Random
*Brief:��ȡ�����
*Params:None
*/
static uint8_t OLED_Random(void)
{
	srand(0);
	return rand()%0xff;
}
/*
*Function:OLED_GraChange
*Brief:ʹOLED�Դ潥��
*Params:
*@dir ����
	1 ����
	0 ��ʧ
*@maskbit �仯λ��
*/
void OLED_GraChange(uint8_t dir,uint8_t maskbit)
{
	if(dir){
		for(int i = 0;i <OLED_PAGE;i++)
			for(int j = 0;j <OLED_WIDTH;j++)
				OLED_GRAM[i][j] = OLED_GRAM[i][j] &(OLED_Random()>>(8-maskbit));
	}
	else{
		for(int i = 0;i <OLED_PAGE;i++)
			for(int j = 0;j <OLED_WIDTH;j++)
				OLED_GRAM[i][j] = OLED_GRAM[i][j] &(OLED_Random()>>(maskbit));
	}
}
/*
*Function:OLED_DrawPixel
*Brief:���Ƶ������ص�
*Params:
*@x x��λ��
*@y y��λ��
*/
void OLED_DrawPixel(uint8_t x,uint8_t y)
{
	uint8_t page = y/8;
	uint8_t page_y = y%8;
	uint8_t page_x = x;
	
	OLED_GRAM[page][page_x] = OLED_GRAM[page][page_x]|(0x01<<page_y);

}

/*
*Function:OLED_ClearPixel
*Brief:����������ص�
*Params:
*@x x��λ��
*@y y��λ��
*/
void OLED_ClearPixel(uint8_t x,uint8_t y)
{
	uint8_t page = y/8;
	uint8_t page_y = y%8;
	uint8_t page_x = x;
	
	OLED_GRAM[page][page_x] = OLED_GRAM[page][page_x]&(~(0x01<<page_y));

}
/*
*Function:OLED_DrawVerticalLine
*Brief:���ƴ�ֱ�߶�
*Params:
*@x ��� x��λ��
*@y ��� y��λ��
*@length ����
*/
void OLED_DrawVerticalLine(int16_t x,int16_t y,int16_t length)
{
	for(int i = 0;i < length;i++)
		OLED_DrawPixel(x,y + i);
}
/*
*Function:OLED_DrawVerticalLine
*Brief:����ˮƽ�߶�
*Params: 
*@x ��� x��λ��
*@y ��� y��λ��
*@length ����
*/
void OLED_DrawHorizontalLine(int16_t x,int16_t y,int16_t length)
{
	for(int i = 0;i < length;i++)
		OLED_DrawPixel(x + i,y);
}

/*
*Function:OLED_DrawSlashLine
*Brief:������б�߶�
*Params:
*@x0 ��� x��λ��
*@y0 ��� y��λ��
*@x1 �յ� x��λ��
*@y1 �յ� y��λ��
*/
void OLED_DrawSlashLine(int16_t x0,int16_t y0,int16_t x1,int16_t y1)
{
	int dx = (x1 > x0)?x1 - x0:x0 - x1;
	int dy = (y1 > y0)?y1 - y0:y0 - y1;
	int sx,sy,err,e2;
	
	if(x0 < x1)
		sx = 1;
	else
		sx = -1;
	
	if(y0 < y1)
		sy = 1;
	else 
		sy = -1;
	
	err = dx - dy;
	
	while (1) {
        OLED_DrawPixel(x0, y0);
        
        if (x0 == x1 && y0 == y1) {
            break;
        }
        
        e2 = 2 * err;
        
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}
/*
*Function:OLED_DrawLine
*Brief:�����߶�
*Params:
*@x0 ��� x��λ��
*@y0 ��� y��λ��
*@x1 �յ� x��λ��
*@y1 �յ� y��λ��
*/
void OLED_DrawLine(int16_t x0,int16_t y0,int16_t x1,int16_t y1)
{
	if(y0 == y1){
		OLED_DrawHorizontalLine(x0 < x1?x0:x1,y0,abs(x1 - x0 + 1));
		return;
	}else if(x0 == x1){
		OLED_DrawVerticalLine(x0,y0 < y1?y0:y1,abs(y1 - y0 + 1));
		return;
	}else{
		OLED_DrawSlashLine(x0,y0,x1,y1);
	}
}
/*
*Function:OLED_DrawTriangle
*Brief:����������
*Params:
*@x0 ����0 x��λ��
*@y0 ����0 y��λ��
*@x1 ����1 x��λ��
*@y1 ����1 y��λ��
*@x2 ����2 x��λ��
*@y2 ����2 y��λ��
*/
void OLED_DrawTriangle(int16_t x0,int16_t y0,int16_t x1,int16_t y1,int16_t x2,int16_t y2)
{
	OLED_DrawLine(x0,y0,x1,y1);
	OLED_DrawLine(x1,y1,x2,y2);
	OLED_DrawLine(x2,y2,x0,y0);
}

/*
*Function:OLED_DrawCircle
*Brief:����Բ
*Params:
*@x0 Բ�� x��λ��
*@y0 Բ�� y��λ��
*@radius �뾶����
*/
void OLED_DrawCircle(int16_t x0,int16_t y0,int16_t radius)
{
	int16_t dx,dy,dr2;
	dx = 0;
	dy = radius;
	
	while(2*dy*dy - radius >= 0){
		OLED_DrawPixel(x0 + dx,y0 + dy);
		OLED_DrawPixel(x0 - dx,y0 + dy);
		OLED_DrawPixel(x0 + dx,y0 - dy);
		OLED_DrawPixel(x0 - dx,y0 - dy);
		
		OLED_DrawPixel(x0 + dy,y0 + dx);
		OLED_DrawPixel(x0 - dy,y0 + dx);
		OLED_DrawPixel(x0 + dy,y0 - dx);
		OLED_DrawPixel(x0 - dy,y0 - dx);
		
		dx++;
		dr2 = (dx*dx + dy*dy) - radius*radius;
		if(dr2 > 0){
			dx--;
			dy--;
		}	
	}
}
/*
*Function:OLED_DrawRectangle
*Brief:���ƾ���
*Params:
*@x0 ����0 x��λ��
*@y0 ����0 y��λ��
*@x1 ����1 x��λ��
*@y1 ����1 y��λ��
*/
void OLED_DrawRectangle(int16_t x0,int16_t y0,int16_t x1,int16_t y1)
{
	OLED_DrawHorizontalLine(x0 < x1?x0:x1,y0,abs(x1 - x0));
	OLED_DrawHorizontalLine(x0 < x1?x0:x1,y1,abs(x1 - x0));
	OLED_DrawVerticalLine(x0,y0 < y1?y0:y1,abs(y1 - y0));
	OLED_DrawVerticalLine(x1,y0 < y1?y0:y1,abs(y1 - y0));
}
/*
*Function:OLED_DrawChar
*Brief:�����ַ�
*Params:
*@x0 ��� x��λ��
*@y0 ��� y��λ��
*@chr �ַ�
*@size �ַ���С
	ASC2_1206 12 12*6
	ASC2_1608 16 16*8
	ASC2_2412 24 24*12
*/
int16_t OLED_DrawChar(uint8_t x0,uint8_t y0,uint8_t chr,uint8_t size)
{
	uint8_t byteCount = (size/8+((size%8)?1:0))*(size/2);
	uint8_t orderChar = chr - ' ';
	uint8_t byte,y = y0,x = x0;
	
	for(uint8_t i = 0;i < byteCount;i++)
	{
		switch(size){
			case ASC2_1206:
				byte = asc2_1206[orderChar][i];
				break;
			case ASC2_1608:
				byte = asc2_1608[orderChar][i];
				break;
			case ASC2_2412:
				byte = asc2_1608[orderChar][i];
				break;
			default:
				return -1;
		}
		
		for(uint8_t j = 0;j < 8;j++){
			if(byte&(0x80>>j))
				OLED_DrawPixel(x,y);
			else
				OLED_ClearPixel(x,y);
			y++;
			if(y - y0 >= size){
				y = y0;
				x++;
				break;
			}
		}
	}
	
	return x;
}

/*
*Function:OLED_DrawString
*Brief:�����ַ���
*Params:
*@x0 ��� x��λ��
*@y0 ��� y��λ��
*@str �ַ���
*@size �ַ���С
	ASC2_1206 12 12*6
	ASC2_1608 16 16*8
	ASC2_2412 24 24*12
*/
void OLED_DrawString(uint8_t x0,uint8_t y0,char* str,uint8_t size)
{	
	while(*str){
		x0 = OLED_DrawChar(x0,y0,*(str++),size);
		if(x0 >= OLED_WIDTH - 5){
			y0 = y0 + size;
			x0 = 0;
		}
	}		
}

/*
*Function:OLED_DrawNumber
*Brief:��������
*Params:
*@x0 ��� x��λ��
*@y0 ��� y��λ��
*@num ����
*@size �ַ���С
	ASC2_1206 12 12*6
	ASC2_1608 16 16*8
	ASC2_2412 24 24*12
*/
void OLED_DrawNumber(uint8_t x0,uint8_t y0,int number,uint8_t size)
{
	char num[10];
	sprintf(num,"%d",number);
	OLED_DrawString(x0,y0,num,size);
}
/*
*Function:OLED_DrawXBM
*Brief:��������
*Params:
*@x0 ��� x��λ��
*@y0 ��� y��λ��
*@width ͼƬ���
*@height ͼƬ�߶�
*@img ͼƬ����
*/
void OLED_DrawXBM(uint8_t x0,uint8_t y0,uint8_t width,uint8_t height,const uint8_t *img)
{
	char data[30];
	uint8_t byte_height = height/8 + (height%8 == 0?0:1);
	uint8_t byte_width = width/8 + (width%8 == 0?0:1);

	for(int i = 0;i <= height;i++){
		for(int j = 0;j < byte_width;j++){
			uint8_t byte = img[i * byte_width + j];
			for(int k = 0;k < 8;k++){
				if(((0x01<<k)& byte) == 0)
					OLED_ClearPixel(x0 + j*8 + k,y0 + i);
				else
					OLED_DrawPixel(x0 + j*8 + k,y0 + i);
			}
		}
	}
}
