#include "taskmy.h"

static TaskHandle_t AppTaskCreate_Handle = NULL;

static TaskHandle_t LED_Task_Handle = NULL;
static TaskHandle_t UI_Task_Handle = NULL;
static TaskHandle_t ECG_Task_Handle = NULL;
static TaskHandle_t CLI_Task_Handle = NULL;
static TaskHandle_t MQTT_Task_Handle = NULL;

void AppTaskCreateStart(void)
{
  BaseType_t xReturn = pdPASS;
  
	xReturn = xTaskCreate((TaskFunction_t)AppTaskCreate,
                        (const char*)"AppTaskCreate",
                        (uint32_t)512,
                        (void*)NULL,
                        (UBaseType_t)1,
                        (TaskHandle_t*)&AppTaskCreate_Handle);
	
	if(pdPASS == xReturn){
		Serial_SendString(hlpuart1,"RTOS Start Success\r\n");
		vTaskStartScheduler();
	}else {
		Serial_SendString(hlpuart1,"RTOS Start Fail\r\n");
	}

}
static void AppTaskCreate(void)
{
	BaseType_t xReturn = pdPASS;
  
  taskENTER_CRITICAL();
	
	xReturn = xTaskCreate((TaskFunction_t)LED_Task,
                        (const char*)"LED_Task",
                        (uint32_t)1024,
                        (void*)NULL,
                        (UBaseType_t)4,
                        (TaskHandle_t*)&LED_Task_Handle);
										
	if(xReturn == pdPASS)
		Serial_SendString(hlpuart1,"LED_Task Create Success\r\n");
	else
		Serial_SendString(hlpuart1,"LED_Task Create Fail\r\n");
  
	
	xReturn = xTaskCreate((TaskFunction_t)UI_Task,
                        (const char*)"UI_Task",
                        (uint32_t)512,
                        (void*)NULL,
                        (UBaseType_t)2,
                        (TaskHandle_t*)&UI_Task_Handle);
  
  if(xReturn == pdPASS)
		Serial_SendString(hlpuart1,"OLED_Task Create Success\r\n");
	else
		Serial_SendString(hlpuart1,"OLED_Task Create Fail\r\n");
  
  
  xReturn = xTaskCreate((TaskFunction_t)ECG_Task,
                        (const char*)"ECG_Task",
                        (uint32_t)1024,
                        (void*)NULL,
                        (UBaseType_t)2,
                        (TaskHandle_t)&ECG_Task_Handle);

  if(xReturn == pdPASS)
		Serial_SendString(hlpuart1,"ECG_Task Create Success\r\n");
	else
		Serial_SendString(hlpuart1,"ECG_Task Create Fail\r\n");
  
  xReturn = xTaskCreate((TaskFunction_t)MQTT_Task,
                        (const char*)"MQTT_Task",
                        (uint32_t)512,
                        (void*)NULL,
                        (UBaseType_t)2,
                        (TaskHandle_t)&MQTT_Task_Handle);

  if(xReturn == pdPASS)
		Serial_SendString(hlpuart1,"MQTT_Task Create Success\r\n");
	else
		Serial_SendString(hlpuart1,"MQTT_Task Create Fail\r\n");
  
  xReturn = xTaskCreate((TaskFunction_t)CLI_Task,
                        (const char*)"CLI_Task",
                        (uint32_t)512,
                        (void*)NULL,
                        (UBaseType_t)2,
                        (TaskHandle_t)&CLI_Task_Handle);

  if(xReturn == pdPASS)
		Serial_SendString(hlpuart1,"CLI_Task Create Success\r\n");
	else
		Serial_SendString(hlpuart1,"CLI_Task Create Fail\r\n");
                        
  
  vTaskDelete(AppTaskCreate_Handle);
	taskEXIT_CRITICAL();
}

static void LED_Task(void)
{
	while(1)
  {
		//Serial_SendString(hlpuart1,"LED ON\r\n");
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
		vTaskDelay(1000);
    
		//Serial_SendString(hlpuart1,"LED OFF\r\n");
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
		vTaskDelay(1000);
	}

}

static void ECG_Task(void)
{
  while(1){
    ECG_GetValue();
    Serial_SendNum(hlpuart1,data[0]);
    vTaskDelay(5);  //采样频率约为200Hz
    
  }
}

static void UI_Task(void)
{ 
  UI_Init();
  //vTaskDelay(1000);
  //UI_SwitchMenu(1);
  //vTaskDelay(1000);
  //UI_EnterMenu();
  //vTaskDelay(1000);
  //UI_ExitMenu();
  char data[30];
  while(1){
    OLED_Clear();
    
    sprintf(data,"heartRate:%d",heartRate);
    OLED_DrawString(0,0,data,ASC2_1206);
    
    sprintf(data,"SDNN:%.2f ms",SDNN);
    OLED_DrawString(0,12,data,ASC2_1206);
    
    sprintf(data,"rMSSD:%.2f ms",rMSSD);
    OLED_DrawString(0,24,data,ASC2_1206);
    
    sprintf(data,"pNN50:%.2f",pNN50);
    OLED_DrawString(0,36,data,ASC2_1206);
    OLED_Refresh();
    vTaskDelay(3000);
  }
}

static void CLI_Task(void)
{
   while(1){
      cli_Check();
   }
}

static void MQTT_Task(void)
{
  WIFI_Init();
  WIFI_MQTT_Subscribe("ECG-data");
  //WIFI_MQTT_PublishNum("ECG",50);
  
  while(1){
    //WIFI_MQTT_PublishStr("ECG","start");
    /*
    for(int i = 0;i < 3000;i++){
      WIFI_MQTT_PublishNum("ECG",ecgdata[i]);
    }
    */
    mqttindex = 0;
    mqttcompleteflag = 0;
   //WIFI_MQTT_PublishStr("ECG","end");
  }
}

void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                    signed char *pcTaskName )
{
  char data[20];
  sprintf(data,"%s overflow",pcTaskName);
  Serial_SendString(hlpuart1,data);
}
