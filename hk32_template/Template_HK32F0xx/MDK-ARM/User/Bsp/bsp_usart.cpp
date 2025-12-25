#include "bsp_usart.hpp"
#include "variables.hpp"
#include <cstdarg>

#if 0
void bspUartInit(void)
{
    __HAL_UART_ENABLE_IT(&CAT1_USART_PORT,UART_IT_RXNE);
}
#endif

/**
 * @description: 串口1发送单字节数据
 * @param {uint8_t} data 待发送数据
 * @return {*}
 */
void Uart1_Send(uint8_t data)
{
    while((USART1->ISR & 0x80) == RESET);
    USART1->TDR = data;
}


/**
 * @description: 串口2发送单字节数据
 * @param {uint8_t} data 待发送数据
 * @return {*}
 */
void Uart2_Send(uint8_t data)
{
    while((USART1->ISR & 0x80) == RESET);
    USART2->TDR = data;
}

void Uart1_print(uint8_t* str)
{
    while(*str != '\0')
        Uart1_Send(*str++);
}

void Uart2_print(uint8_t* str)
{
    while(*str != '\0')
        Uart2_Send(*str++);
}

void uart_print(char* format, ...)
{
    uint8_t str[64];
      va_list aptr;
      va_start(aptr, format);
      vsprintf((char *)str, format, aptr);
      va_end(aptr);
    Uart1_print(str);
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

    USART_SendData(USART1, (uint8_t) ch);

    do
    {
        Status = USART_GetFlagStatus(USART1, USART_FLAG_TXE);
        Timeout++;
    } while ((Status == RESET) && (Timeout != 0xFFFF));

    return (ch);
}