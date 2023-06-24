#ifndef __ECG_H__
#define __ECG_H__

#include "adc.h"

extern uint16_t data[];
extern int completeflag;

extern uint16_t mqttdata[];
extern uint8_t mqttindex;
extern uint8_t mqttcompleteflag;

extern int16_t ecgdata[];

void ECG_GetValue(void);

#endif
