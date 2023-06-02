/*
* Filename: wifi.c
* Author: ZJT
* Brief: ESP32 AT Command Control
* Date: 2023/5/11
*/

#include "wifi.h"

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef hlpuart1;

WIFI wifi = {
	.ssid = "Mi 10",
	.pwd = "7755883311ay",
	.mqtthost = "47.113.218.238",
	.mqttport = 1883,
};

char wifi_replybuffer[100];
char atcmd[100];
uint8_t wifi_replybufferIndex = 0;

void WIFI_Init(void)
{
	WIFI_MQTT_ConfigUser("ECG_STM32","","");
	HAL_Delay(500);
	WIFI_MQTT_Connect("47.113.218.238",1883);
	HAL_Delay(1000);
	WIFI_GetWifiState();
	HAL_Delay(500);
	WIFI_MQTT_GetState();
	HAL_Delay(500);
}

/*
* Function: WIFI_SetMode
* Brief: Set WIFI Mode
* Params:
*		@mode 	0: None WIFI
*				1: Station Mode
*				2: SoftAP Mode
*				3: Station + SoftAP Mode
* Return: None
*/
void WIFI_SetWifiMode(int mode)
{
	sprintf(atcmd,"AT+CWMODE=%d\r\n",mode);
	
	Serial_SendString(huart2,atcmd);
	WIFI_ReadReply();
}	
/*
* Function: WIFI_ConnectWifi
* Brief: Connect WIFI
* Params:
*		@ssid WIFI SSID
*		@pwd WIFI Password
* Return: None
*/
void WIFI_ConnectWifi(char* ssid,char* pwd)
{
	sprintf(atcmd,"AT+CWJAP=\"%s\",\"%s\"\r\n",ssid,pwd);
	
	Serial_SendString(huart2,atcmd);
	WIFI_ReadReply();
}	
/*
* Function: WIFI_GetState
* Brief: Get WIFI State
* Params: None
* Return: None
*/
void WIFI_GetWifiState(void)
{	
	sprintf(atcmd,"AT+CWSTATE?\r\n");
	
	Serial_SendString(huart2,atcmd);
	WIFI_ReadReply();
}
/*
* Function: WIFI_MQTT_ConfigUser
* Brief: Config User Infomation
* Params:
*		@clientid MQTT clientID
*		@username MQTT username
*		@password MQTT password
* Return: None
*/
void WIFI_MQTT_ConfigUser(char* clientid, char* username, char* password)
{
	sprintf(atcmd,"AT+MQTTUSERCFG=0,1,\"%s\",\"%s\",\"%s\",0,0,\"\"\r\n",clientid,username,password);
	
	Serial_SendString(huart2,atcmd);
	WIFI_ReadReply();
}
/*
* Function: WIFI_MQTT_Connect
* Brief: Connect MQTT Broker
* Params:
*		@host Host IP
*		@port Host Port
* Return: None
*/
void WIFI_MQTT_Connect(char* host,int port)
{
	sprintf(atcmd,"AT+MQTTCONN=0,\"%s\",%d,1\r\n",host,port);
	
	Serial_SendString(huart2,atcmd);
	WIFI_ReadReply();
}
/*
* Function: WIFI_MQTT_GetState
* Brief: Get MQTT State
* Params: None
* Return: None
*/
void WIFI_MQTT_GetState(void)
{
	sprintf(atcmd,"AT+MQTTCONN?\r\n");

	Serial_SendString(huart2,atcmd);
	WIFI_ReadReply();
}
/*
* Function: WIFI_MQTT_Disconnect
* Brief: Disconnect MQTT
* Params: None
* Return: None
*/
void WIFI_MQTT_Disconnect(void)
{
	sprintf(atcmd,"AT+MQTTCLEAN=0\r\n");
	
	Serial_SendString(huart2,atcmd);
	WIFI_ReadReply();
}
/*
* Function: WIFI_MQTT_PublishStr
* Brief: Publish Topic String
* Params:
*		@topic Publish Topic
*		@data Publish Str
* Return: None
*/
void WIFI_MQTT_PublishStr(char* topic,char* data)
{
	sprintf(atcmd,"AT+MQTTPUB=0,\"%s\",\"%s\",0,0\r\n",topic,data);
	
	Serial_SendString(huart2,atcmd);
	WIFI_ReadReply();
}
/*
* Function: WIFI_MQTT_PublishData
* Brief: Publish Topic Num
* Params:
*		@topic Publish Topic
*		@data Publish Num
* Return: None
*/
void WIFI_MQTT_PublishNum(char* topic,int data)
{
	sprintf(atcmd,"AT+MQTTPUB=0,\"%s\",\"{\"data\":%d}\",0,0\r\n",topic,data);
	
	Serial_SendString(huart2,atcmd);
	WIFI_ReadReply();
}
/*
* Function: WIFI_ReadReply
* Brief: Get AT Command reply And restore it in wifi_replybuffer
* Params: None
* Return: None
*/
void WIFI_ReadReply(void)
{
	HAL_Delay(500);
#ifdef WIFI_DEBUG
	while(Serial_ReadAvailable(huart2))
    {
		uint8_t data = Serial_ReadChar(huart2);
		wifi_replybuffer[wifi_replybufferIndex++] = data;;
	}

	Serial_SendString(hlpuart1,wifi_replybuffer);
#endif
	WIFI_Prompt();

}
/*
* Function: WIFI_Prompt
* Brief: Reset wifi_replybuffer and index
* Params: None
* Return: None
*/
void WIFI_Prompt(void)
{
	memset(wifi_replybuffer,0,sizeof(wifi_replybuffer));
	memset(atcmd,0,sizeof(atcmd));
	wifi_replybufferIndex = 0;
}
