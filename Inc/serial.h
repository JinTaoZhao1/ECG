#ifndef __SERIAL_H__
#define __SERIAL_H__

#include "usart.h"

#include "stdint.h"
#include "stdio.h"

#define SERIAL_RXSIZE 200
#define SERIAL_TXSIZE 100

typedef struct{	
	uint8_t rxDataBuffer[SERIAL_RXSIZE];
	uint8_t rx_tail,rx_head;
    
	uint8_t txDataBuffer[SERIAL_TXSIZE];
	uint8_t tx_tail,tx_head;
	
	uint8_t dataRxBuffer;
} Serial;  

extern Serial serial2;
extern Serial seriallp1;

void Serial_SendChar(UART_HandleTypeDef huart,uint8_t data);
void Serial_SendString(UART_HandleTypeDef huart,const char* str);
void Serial_SendNum(UART_HandleTypeDef huart,uint16_t num);
uint8_t Serial_ReadAvailable(UART_HandleTypeDef huart);
uint8_t Serial_ReadChar(UART_HandleTypeDef huart);

#endif
