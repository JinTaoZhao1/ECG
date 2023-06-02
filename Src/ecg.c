#include "ecg.h"

uint16_t data[30] = {0};
int completeflag = 0;

void ECG_GetValue()
{
  HAL_ADC_Start_DMA(&hadc1,(uint32_t*)data,30);
}

void ECG_RwaveDetect()
{
  

}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
 
  completeflag++;
}  