#ifndef _WIFI_H__
#define _WIFI_H__

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "serial.h"

#include "FreeRTOS.h"
#include "task.h"

typedef struct {
	char ssid[30];
	char pwd[30];
	char mqtthost[30];
	int mqttport;
}WIFI;

#define WIFI_DEBUG

extern WIFI wifi;

void WIFI_Init(void);

void WIFI_SetWifiMode(int mode);
void WIFI_ConnectWifi(char* ssid,char* pwd);
void WIFI_GetWifiState(void);

void WIFI_MQTT_ConfigUser(char* clientid, char* username, char* password);
void WIFI_MQTT_Connect(char* host,int port);
void WIFI_MQTT_GetState(void);
void WIFI_MQTT_Disconnect(void);
void WIFI_MQTT_PublishStr(char* topic,char* data);
void WIFI_MQTT_PublishNum(char* topic,int data);

void WIFI_ReadReply(void);
void WIFI_Prompt(void);
#endif
