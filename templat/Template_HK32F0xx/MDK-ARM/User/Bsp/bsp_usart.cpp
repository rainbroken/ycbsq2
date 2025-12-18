#include "bsp_usart.hpp"
#include "variables.hpp"

void bspUartInit(void)
{
    __HAL_UART_ENABLE_IT(&CAT1_USART_PORT,UART_IT_RXNE);
}

/**
 * @description: 串口1发送单字节数据
 * @param {uint8_t} data 待发送数据
 * @return {*}
 */
void Uart1_Send(uint8_t data)
{
#ifdef STM32F1xx
    while((USART1->SR & 0x80) == RESET);
    USART1->DR = data;
#elif STM32F4xx || STM32L4xx
    while((USART1->TSR & 0x80) == RESET);
    USART1->TDR = data;
#endif
}


/**
 * @description: 串口2发送单字节数据
 * @param {uint8_t} data 待发送数据
 * @return {*}
 */
void Uart2_Send(uint8_t data)
{
#ifdef STM32F1xx
    while((USART2->SR & 0x80) == RESET);
    USART2->DR = data;
#elif STM32F4xx || STM32L4xx
    while((USART2->TSR & 0x80) == RESET);
    USART2->TDR = data;
#endif
}

/**
 * @description: 串口3发送单字节数据
 * @param {uint8_t} data 待发送数据
 * @return {*}
 */
void Uart3_Send(uint8_t data)
{

#ifdef STM32F1xx
    while((USART3->SR & 0x80) == RESET);
    USART3->DR = data;
#elif STM32F4xx || STM32L4xx
    while((USART3->TSR & 0x80) == RESET);
    USART3->TDR = data;
#endif
}

/**
 * @description: 接收串口单字节数据
 * @param {UART_HandleTypeDef} *huartx  串口句柄
 * @return {*}                          串口接收到的数据
 */
inline uint8_t USART_ReceiveData(UART_HandleTypeDef *huartx)
{
#ifdef STM32F1xx
    return (uint8_t)(huartx->Instance->DR & 0xFF);
#elif STM32F4xx || STM32L4xx
    return (uint8_t)(huartx->Instance->RDR & 0xFF);
#endif
}