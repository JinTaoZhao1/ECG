#ifndef __ECG_H__
#define __ECG_H__

#include "adc.h"

extern uint16_t data[];
extern int completeflag;

void ECG_GetValue(void);

#endif