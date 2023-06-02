#include "rocker.h"

Rocker_Info rocker_info = {0,0,0,0,0,{0,0}};

uint8_t Rocker_GetState()
{


}

void Rocker_GetKey()
{ 
  Rocker_GetValue();
  
  while(rocker_info.completeflag != 1);
  
  rocker_info.x = rocker_info.adcvalue[0];
  rocker_info.y = rocker_info.adcvalue[1];
  rocker_info.z = HAL_GPIO_ReadPin(SWITCH_Z_GPIO_Port,SWITCH_Z_Pin);
  rocker_info.completeflag = 0;
  rocker_info.readflag = 1;
}

uint8_t Rocker_ReadAvailable()
{
  return rocker_info.readflag;
}

void Rocker_GetValue()
{
  HAL_ADC_Start_DMA(&hadc2,(uint32_t *)rocker_info.adcvalue,2);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  if(hadc->Instance == ADC2){
    rocker_info.completeflag = 1;
  }
}  