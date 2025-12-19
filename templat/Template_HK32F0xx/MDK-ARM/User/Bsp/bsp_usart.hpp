#pragma once 
#include "main.h"
//#include "usart.h"

#ifdef __cplusplus
extern "C" {
#endif
    

const uint16_t  kAirSendSize           = 500;
const uint16_t  kAirRecvSize           = 1200;
typedef struct
{
    char        txbuff[kAirSendSize];  //发送数据缓存
	char        rxbuff[kAirRecvSize];  //接收数据缓存
	uint16_t    rxcount;        //接收的数量
    bool        rx_flag;        //接收完毕标志
}uart_message;

void bspUartInit(void);
void Uart1_Send(uint8_t data);
void Uart2_Send(uint8_t data);
void Uart3_Send(uint8_t data);
uint8_t USARTx_ReceiveData(USART_TypeDef *huartx);

    
    
    
#ifdef __cplusplus
}
#endif