#ifndef __CLI_H__
#define __CLI_H__

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "oled.h"
#include "wifi.h"
#include "serial.h"

typedef struct {
    char *name;
    char *params;
    void (*cmdFunc)(void *cmd, char *cmdLine);
}cli_Command; 

void cli_Test(void *cmd, char *cmdLine);

void cli_ConnectWifi(void *cmd, char *cmdLine);
void cli_GetWifiState(void *cmd, char *cmdLine);
void cli_SetWifiMode(void *cmd, char *cmdLine);

void cli_SetMQTTConfigUser(void *cmd, char *cmdLine);
void cli_ConnectMQTTServer(void *cmd, char *cmdLine);
void cli_GetMQTTState(void *cmd, char *cmdLine);
void cli_DisconnectMQTTServer(void *cmd, char *cmdLine);
void cli_PublishMQTT(void *cmd, char *cmdLine);


void cli_Check(void);
#endif
