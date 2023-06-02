#include "taskmy.h"

static TaskHandle_t AppTaskCreate_Handle = NULL;

static TaskHandle_t LED_Task_Handle = NULL;
static TaskHandle_t UI_Task_Handle = NULL;
static TaskHandle_t ECG_Task_Handle = NULL;


void AppTaskCreateStart(void)
{
  BaseType_t xReturn = pdPASS;
  
	xReturn = xTaskCreate((TaskFunction_t)AppTaskCreate,
                        (const char*)"AppTaskCreate",
                        (uint32_t)1024,
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
  
	/*
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
  */
  /**
  xReturn = xTaskCreate((TaskFunction_t)ECG_Task,
                        (const char*)"ECG_Task",
                        (uint32_t)1024,
                        (void*)NULL,
                        (UBaseType_t)4,
                        (TaskHandle_t)&ECG_Task_Handle);

  if(xReturn == pdPASS)
		Serial_SendString(hlpuart1,"ECG_Task Create Success\r\n");
	else
		Serial_SendString(hlpuart1,"ECG_Task Create Fail\r\n");*/
  /*
  xReturn = xTaskCreate((TaskFunction_t)CLI_Task,
                        (const char*)"CLI_Task",
                        (uint32_t)256,
                        (void*)NULL,
                        (UBaseType_t)2,
                        (TaskHandle_t)&CLI_Task_Handle);

  if(xReturn == pdPASS)
		Serial_SendString(hlpuart1,"CLI_Task Create Success\r\n");
	else
		Serial_SendString(hlpuart1,"CLI_Task Create Fail\r\n");
                        
  vTaskDelete(AppTaskCreate_Handle);
	*/
	taskEXIT_CRITICAL();
}

static void LED_Task(void)
{
	while(1)
  {
		Serial_SendString(hlpuart1,"LED ON\r\n");
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
		vTaskDelay(1000);
    
		Serial_SendString(hlpuart1,"LED OFF\r\n");
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
		vTaskDelay(1000);
	}

}

static void ECG_Task(void)
{
  //WIFI_Init();
  //WIFI_MQTT_PublishNum("ECG",50);
  while(1){
    ECG_GetValue();
    Serial_SendNum(hlpuart1,data[0]);
    //WIFI_MQTT_PublishNum("ECG",data[0]);
    //OLED_DrawNumber(0,0,data[0],ASC2_1206);
    vTaskDelay(5);  //采样频率约为500Hz
    
  }
}

static void UI_Task(void)
{ 
  UI_Init();
  vTaskDelay(1000);
  UI_SwitchMenu(1);
  vTaskDelay(1000);
  UI_EnterMenu();
  vTaskDelay(1000);
  UI_ExitMenu();
  
  while(1){
   
  }
}


void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                    signed char *pcTaskName )
{
  char data[20];
  sprintf(data,"%s overflow",pcTaskName);
  Serial_SendString(hlpuart1,data);
}