#include "serial.h"

Serial serial2 = 
{
	.rx_head = 0,
	.rx_tail = 0,
	.tx_head = 0,
	.tx_tail = 0,	
	.dataRxBuffer = 0,
};

Serial seriallp1 = 
{
	.rx_head = 0,
	.rx_tail = 0,
	.tx_head = 0,
	.tx_tail = 0,
	.dataRxBuffer = 0,
};

/*
*Function:Serial_SendChar
*Biref:���͵����ַ�
*Params:
*@huart ���ھ��
*@data �����ַ�
*/
void Serial_SendChar(UART_HandleTypeDef huart,uint8_t data)
{
    HAL_UART_Transmit(&huart,&data,1,30);
}
/*
*Function:Serial_SendString
*Brief:�����ַ���
*Params:
*@huart ���ھ��
*@str �ַ���
*/
void Serial_SendString(UART_HandleTypeDef huart,const char* str)
{
    while(*str)
      Serial_SendChar(huart,*(str++));
}

void Serial_SendNum(UART_HandleTypeDef huart,uint16_t num)
{
  char data[10];
  sprintf(data,"%d\r\n",num);
  Serial_SendString(huart,data);
}
/*
*Function:Serial_ReadAvailable
*Brief:�ж��Ƿ����ַ�
*Params:
*@huart ���ھ��
*Return:
*@0 ���ַ��ɶ�ȡ
*@1 ���ַ��ɶ�ȡ
*/
uint8_t Serial_ReadAvailable(UART_HandleTypeDef huart)
{
	if(huart.Instance == LPUART1){
		if(seriallp1.rx_tail!=seriallp1.rx_head)
			return 1;
		return 0;
	}
	
	if(huart.Instance == USART2){
		if(serial2.rx_tail!=serial2.rx_head)
			return 1;
		return 0;
	}
	return 0;
}
/*
*Function:Serial_ReadChar
*Brief:��ȡһ���ַ�
*Params:
*@huart ���ھ��
*Return:
*data �ַ�
*/
uint8_t Serial_ReadChar(UART_HandleTypeDef huart)
{
    if(huart.Instance == LPUART1){
		uint8_t data = seriallp1.rxDataBuffer[seriallp1.rx_tail++];
		if(seriallp1.rx_tail >= SERIAL_RXSIZE)
			seriallp1.rx_tail = 0;
		return data;
	}
	
	if(huart.Instance == USART2){
		uint8_t data = serial2.rxDataBuffer[serial2.rx_tail++];
		if(serial2.rx_tail >= SERIAL_RXSIZE)
			serial2.rx_tail = 0;
		return data;
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART2){
        serial2.rxDataBuffer[serial2.rx_head++] = serial2.dataRxBuffer;
        if(serial2.rx_head >= SERIAL_RXSIZE)
             serial2.rx_head = 0;
		while(HAL_UART_Receive_IT(&huart2, (uint8_t *)&serial2.dataRxBuffer, 1)!=HAL_OK);
    } 
    if(huart->Instance == LPUART1){
        seriallp1.rxDataBuffer[seriallp1.rx_head++] = seriallp1.dataRxBuffer;
        if(seriallp1.rx_head >= SERIAL_RXSIZE)
             seriallp1.rx_head = 0;
		while(HAL_UART_Receive_IT(&hlpuart1, (uint8_t *)&seriallp1.dataRxBuffer, 1)!=HAL_OK);
		
    } 
}
