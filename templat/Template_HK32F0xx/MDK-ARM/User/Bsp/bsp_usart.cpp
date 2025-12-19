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
uint8_t USARTx_ReceiveData(USART_TypeDef *huartx)
{
    return (uint8_t) (huartx->RDR &0xFF);
}


/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
    uint32_t Timeout = 0;
    FlagStatus Status;

    USART_SendData(EVAL_COM1, (uint8_t) ch);

    do
    {
        Status = USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TXE);
        Timeout++;
    } while ((Status == RESET) && (Timeout != 0xFFFF));

    return (ch);
}