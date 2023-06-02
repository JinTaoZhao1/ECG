#ifndef __DOCKER_H__
#define __DOCKER_H__

#include <stdint.h>

#include "adc.h"
#include "gpio.h"

#include "FreeRTOS.h"
#include "task.h"

typedef struct{
  uint16_t x;
  uint16_t y;
  uint8_t z; 
  uint8_t readflag;
  uint8_t completeflag;
  uint16_t adcvalue[2];
}Rocker_Info;

typedef enum{
  ROCKER_LEFT,
  ROCKER_RIGHT,
  ROCKER_UP,
  ROCKER_DOWN,
  ROCKER_ENTER,
}Rocker_State;

void Rocker_GetKey(void);
void Rocker_GetValue(void);

#endif