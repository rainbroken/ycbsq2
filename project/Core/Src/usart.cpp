#include "usart.hpp"

void USART1_UART_Init(uint32_t baudrate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    /* Enable GPIO clock */
    RCC_AHBPeriphClockCmd(USART1_TXIO_CLK | USART1_RXIO_CLK, ENABLE);
    /* Enable USART clock */
    RCC_APB2PeriphClockCmd(USART1_CLK, ENABLE);
    
    /* USARTx configured as follow:
    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - Stop Bit = 1 Stop Bit
    - Parity = No Parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    
    /* Connect PXx to USARTx_Tx */
    GPIO_PinAFConfig(USART1_TXIO_PORT, USART1_AF_TX_SOURCE, USART1_TX_AF);

    /* Connect PXx to USARTx_Rx */
    GPIO_PinAFConfig(USART1_RXIO_PORT, USART1_AF_RX_SOURCE, USART1_RX_AF);

     /* Configure USART Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(USART1_TXIO_PORT, &GPIO_InitStructure);
    
    /* Configure USART Rx as alternate function push-spull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(USART1_RXIO_PORT, &GPIO_InitStructure);
    
    /* USART configuration */
    USART_Init(USART1_COM, &USART_InitStructure);
    // 使能接收中断（当 RXNE 标志置位时触发中断）
    USART_ITConfig(USART1_COM, USART_IT_RXNE, ENABLE);
    
    /* Enable the USART Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable USART */
    USART_Cmd(USART1_COM, ENABLE);
    

}

void USART2_UART_Init(uint32_t baudrate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    
    /* Enable GPIO clock */
    RCC_AHBPeriphClockCmd(USART2_TXIO_CLK | USART2_RXIO_CLK, ENABLE);
    /* Enable USART clock */
    RCC_APB2PeriphClockCmd(USART2_CLK, ENABLE);
    
    /* USARTx configured as follow:
    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - Stop Bit = 1 Stop Bit
    - Parity = No Parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    
    /* Connect PXx to USARTx_Tx */
    GPIO_PinAFConfig(USART2_TXIO_PORT, USART2_AF_TX_SOURCE, USART2_TX_AF);

    /* Connect PXx to USARTx_Rx */
    GPIO_PinAFConfig(USART2_RXIO_PORT, USART2_AF_RX_SOURCE, USART2_RX_AF);

     /* Configure USART Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = USART2_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(USART1_TXIO_PORT, &GPIO_InitStructure);
    
    /* Configure USART Rx as alternate function push-spull */
    GPIO_InitStructure.GPIO_Pin = USART2_RX_PIN;
    GPIO_Init(USART1_RXIO_PORT, &GPIO_InitStructure);
    
    /* USART configuration */
    USART_Init(USART2_COM, &USART_InitStructure);

    /* Enable USART */
    USART_Cmd(USART2_COM, ENABLE);
    
}
