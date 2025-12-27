#pragma once
#include "hk32f04axxA.h"
#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif
    
#if UART1_DMA_RX
    void USART1_UART_Init_DMA(uint32_t baudrate);
#endif
void USART1_UART_Init(uint32_t baudrate);
void USART2_UART_Init(uint32_t baudrate);


#ifdef __cplusplus
}
#endif

