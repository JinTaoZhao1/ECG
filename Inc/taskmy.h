#ifndef __TASK_H__
#define __TASK_H__

#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "gpio.h"
#include "usart.h"
#include "ecg.h"
#include "oled.h"

#include "ui.h"
#include "wifi.h"
#include "cli.h"


void AppTaskCreateStart(void);
static void AppTaskCreate(void);

static void LED_Task(void);
static void UI_Task(void);
static void ECG_Task(void);
static void CLI_Task(void);
static void MQTT_Task(void);
#endif
