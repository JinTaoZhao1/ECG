#include "cli.h"

extern UART_HandleTypeDef hlpuart1;


cli_Command cli_Commandlist[] = {
	{"connectWifi","<ssid><pwd>",cli_ConnectWifi},
	{"connectMQTTServer","<host><port>",cli_ConnectMQTTServer},
	{"disconnectMQTTServer","",cli_DisconnectMQTTServer},
	{"getMQTTState","",cli_GetMQTTState},
	{"getWifiState","",cli_GetWifiState},
	{"publishMQTTContent","<topic><content>",cli_PublishMQTT},
	{"test","",cli_Test},
	{"setMQTTConfigUser","<clientid><username><password>",cli_SetMQTTConfigUser},
	{"setWifiMode","<mode>",cli_SetWifiMode},
};

static const int cli_CommandListNum = sizeof(cli_Commandlist)/sizeof(cli_Command);

char cli_buffer[30] = {0}; 
uint8_t cli_bufferIndex = 0;

void cli_Test(void *cmd, char *cmdLine)
{
	Serial_SendString(hlpuart1,"OK\r\n");
}

void cli_SetWifiMode(void *cmd, char *cmdLine)
{
	int mode;
	char feedback[30];
	
	uint8_t params = sscanf(cmdLine,"%d",&mode);
	
	cli_Command *cli_cmdTmp = (cli_Command*)cmd;
	if(params < 1){
		sprintf(feedback,"%s\r\n",cli_cmdTmp->params);
		Serial_SendString(hlpuart1,feedback);
		return;
	}
	if(mode > 3){
		sprintf(feedback,"mode:[0,3]\r\n");
		Serial_SendString(hlpuart1,feedback);
		return;
	}
	
	WIFI_SetWifiMode(mode);
}

void cli_ConnectWifi(void *cmd, char *cmdLine)
{
	char ssid[30];
	char pwd[30];
	char feedback[30];
	
	uint8_t params = sscanf(cmdLine,"%s %s",ssid,pwd);
	
	cli_Command *cli_cmdTmp = (cli_Command*)cmd;

	if(params < 2){
		sprintf(feedback,"%s\r\n",cli_cmdTmp->params);
		Serial_SendString(hlpuart1,feedback);
		return;
	}

	WIFI_ConnectWifi(ssid,pwd);
}

void cli_GetWifiState(void *cmd, char *cmdLine)
{
	/*
	Serial_SendString(hlpuart1,"WIFI_GetWifiState()\r\n");
	flag = 1;
	*/
	WIFI_GetWifiState();
}

void cli_SetMQTTConfigUser(void *cmd, char *cmdLine)
{
	char clientid[30];
	char username[30];
	char password[30];
	char feedback[30];
	
	uint8_t params = sscanf(cmdLine,"%s %s %s",clientid,username,password);
	
	cli_Command *cli_cmdTmp = (cli_Command*)cmd;
	
	if(params < 3){
		sprintf(feedback,"%s\r\n",cli_cmdTmp->params);
		Serial_SendString(hlpuart1,feedback);
		return;
	}
	
	WIFI_MQTT_ConfigUser(clientid,username,password);
}
void cli_ConnectMQTTServer(void *cmd, char *cmdLine)
{
	char host[30];
	int port;
	char feedback[30];
	
	uint8_t params = sscanf(cmdLine,"%s %d",host,&port);
	
	cli_Command *cli_cmdTmp = (cli_Command*)cmd;
	
	if(params < 2){
		sprintf(feedback,"%s\r\n",cli_cmdTmp->params);
		Serial_SendString(hlpuart1,feedback);
		return;
	}
	
	WIFI_MQTT_Connect(host,port);
}
void cli_GetMQTTState(void *cmd, char *cmdLine)
{
	WIFI_MQTT_GetState();
}
void cli_DisconnectMQTTServer(void *cmd, char *cmdLine)
{
	WIFI_MQTT_Disconnect();
}
void cli_PublishMQTT(void *cmd, char *cmdLine)
{
	char topic[20];
	char content[20];
	char feedback[30];
	
	uint8_t params = sscanf(cmdLine,"%s %s",topic,content);
	
	cli_Command *cli_cmdTmp = (cli_Command*)cmd;
	if(params < 2){
		sprintf(feedback,"%s\r\n",cli_cmdTmp->params);
		Serial_SendString(hlpuart1,feedback);
		return;
	}
	WIFI_MQTT_PublishStr(topic,content);
}

static int cli_CommandComp(const void *c1,const void *c2)
{
    const cli_Command *cmd1 = c1,*cmd2 = c2;
    return strncasecmp(cmd1->name, cmd2->name, strlen(cmd2->name));
}

static cli_Command *cli_CommandGet(char *buffer)
{
  cli_Command command_tmp = {buffer}; //令name为整个指令
  return bsearch(&command_tmp,cli_Commandlist,cli_CommandListNum,sizeof(cli_Commandlist[0]),cli_CommandComp);
}

static void cli_Prompt()
{
    memset(cli_buffer,0,sizeof(cli_buffer));
    cli_bufferIndex = 0;       
}

void cli_Check()
{
    cli_Command *cli_cmd;
    while(Serial_ReadAvailable(hlpuart1))
    {
        uint8_t data = Serial_ReadChar(hlpuart1);
        cli_buffer[cli_bufferIndex++] = data;

        if(cli_bufferIndex && (data == '\r'||data == '\n'))
        {
            cli_buffer[cli_bufferIndex-1] = '\0';	
			
            cli_cmd = cli_CommandGet(cli_buffer);
            
            if(cli_cmd){
                Serial_SendString(hlpuart1,"Get Command:");
                Serial_SendString(hlpuart1,cli_buffer);
                Serial_SendString(hlpuart1,"\r\n");
                cli_cmd->cmdFunc(cli_cmd,cli_buffer + strlen(cli_cmd->name));
            }
            else{
                Serial_SendString(hlpuart1,"Not Find Command\r\n");
				
			}
            cli_Prompt();
        }
        
        
  }

}
