#include "img.h"
#include "xbm.h"

IMG_Info IMG_XBMImgs[] = {
	{"delete",48,48,0,0,Menu_InfoIcon},
	{"home",128,64,0,0,Menu_Homeicon},
	{"info",48,48,39,1,Menu_InfoIcon},
	{"setting",48,48,0,0,Menu_Homeicon},	
	{"shell",48,48,39,1,Menu_ShellIcon},
	{"wifi",48,48,39,1,Menu_WIFIIcon},
};

#define IMG_XBM_NUM sizeof(IMG_XBMImgs)/sizeof(IMG_Info) 

static int IMG_ImgCompare(const void *c1,const void *c2)
{
	const IMG_Info *img1 = c1,*img2 = c2;
	return strncasecmp(img1->name,img2->name,strlen(img2->name));
}

static IMG_Info* IMG_FindImg(char *name)
{
	IMG_Info img_tmp = {name};
	return bsearch(&img_tmp,IMG_XBMImgs,IMG_XBM_NUM,sizeof(IMG_XBMImgs[0]),IMG_ImgCompare);
}

void IMG_LoadImg(char *name)
{
	IMG_Info *img_info = IMG_FindImg(name);
	OLED_DrawXBM(img_info->x0,img_info->y0,img_info->width,img_info->height,img_info->data);
}
