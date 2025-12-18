/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-10-08
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup HK32F0xxA_StdPeriph_Examples
  * @{
  */

/** @addtogroup USART_HalfDuplex
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TxBufferSize1   (BufLen(TxBuffer1) - 1)
#define TxBufferSize2   (BufLen(TxBuffer2) - 1)
/* Private macro -------------------------------------------------------------*/
#define BufLen(a)   (sizeof(a) / sizeof(*(a)))

/* Private variables ---------------------------------------------------------*/
uint8_t TxBuffer1[] = "USART Half Duplex: USARTx -> USARTy using HalfDuplex mode";
uint8_t TxBuffer2[] = "USART Half Duplex: USARTy -> USARTx using HalfDuplex mode";

uint8_t RxBuffer1[TxBufferSize2];
uint8_t RxBuffer2[TxBufferSize1];
uint32_t NbrOfDataToSend1 = TxBufferSize2;
uint32_t NbrOfDataToSend2 = TxBufferSize1;
uint8_t TxCounter1 = 0, RxCounter1 = 0;
uint8_t TxCounter2 = 0, RxCounter2 = 0;
uint8_t TransferStatus1 = 0;
uint8_t TransferStatus2 = 0;

/* Private function prototypes -----------------------------------------------*/
void USARTxy_Config(uint32_t Baud);
uint8_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* init LED */
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);

    /* Configure USARTx and USARTy */
    USARTxy_Config(230400);

    /* Enable USARTx Half Duplex Mode */
    USART_HalfDuplexCmd(USARTx, ENABLE);

    /* Enable USARTy Half Duplex Mode */
    USART_HalfDuplexCmd(USARTy, ENABLE);

    while (NbrOfDataToSend2--)
    {
        /* Wait until end of transmit */
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
        {
        }

        /* Write one byte in the USARTx Transmit Data Register */
        USART_SendData(USARTx, TxBuffer1[TxCounter1++]);

        /* Wait the byte is entirely received by USARTy */
        while (USART_GetFlagStatus(USARTy, USART_FLAG_RXNE) == RESET)
        {
        }

        /* Store the received byte in the RxBuffer2 */
        RxBuffer2[RxCounter2++] = USART_ReceiveData(USARTy);
    }

    /* Clear the USARTx Data Register */
    USART_ReceiveData(USARTx);

    while (NbrOfDataToSend1--)
    {
        /* Wait until end of transmit */
        while (USART_GetFlagStatus(USARTy, USART_FLAG_TXE) == RESET)
        {
        }

        /* Write one byte in the USARTy Transmit Data Register */
        USART_SendData(USARTy, TxBuffer2[TxCounter2++]);

        /* Wait the byte is entirely received by USARTx */
        while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET)
        {
        }

        /* Store the received byte in the RxBuffer1 */
        RxBuffer1[RxCounter1++] = USART_ReceiveData(USARTx);
    }

    /* Check the received data with the send ones */
    TransferStatus1 = Buffercmp(TxBuffer1, RxBuffer2, TxBufferSize1);

    if (TransferStatus1)
    {
        printf("\nUSARTx -> USARTy Verification passed!\n");
        HK_EVAL_LEDOn(LED1);
    }
    else
    {
        printf("\nUSARTx -> USARTy Verification failed!\n");
        HK_EVAL_LEDOff(LED1);
    }

    TransferStatus2 = Buffercmp(TxBuffer2, RxBuffer1, TxBufferSize2);

    if (TransferStatus2)
    {
        printf("USARTy -> USARTx Verification passed!\n");
        HK_EVAL_LEDOn(LED2);
    }
    else
    {
        printf("USARTy -> USARTx Verification failed!\n");
        HK_EVAL_LEDOff(LED2);
    }

    while (1)
    {

    }
}

/**
  * @brief  Configure the USART Device
  * @param  Baud: The USARTx and USARTx BaudRate
  * @retval None
  */
void USARTxy_Config(uint32_t Baud)
{
    USART_InitTypeDef usart_struct;
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* Enable GPIO clock and USART clock,USARTx and USARTy */
    USARTx_TXIO_CLK_CMD(USARTx_TXIO_CLK, ENABLE);
    USARTx_RXIO_CLK_CMD(USARTx_RXIO_CLK, ENABLE);
    USARTx_CLK_CMD(USARTx_CLK, ENABLE);
    USARTy_TXIO_CLK_CMD(USARTy_TXIO_CLK, ENABLE);
    USARTy_RXIO_CLK_CMD(USARTy_RXIO_CLK, ENABLE);
    USARTy_CLK_CMD(USARTy_CLK, ENABLE);

    /* Configure USART Tx Rx GPIO */
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_UP;

    GPIO_InitStructure.GPIO_Pin     = USARTx_TX_PIN;
    GPIO_Init(USARTx_TXIO_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin     = USARTx_RX_PIN;
    GPIO_Init(USARTx_RXIO_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin     = USARTy_TX_PIN;
    GPIO_Init(USARTy_TXIO_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin     = USARTy_RX_PIN;
    GPIO_Init(USARTy_RXIO_PORT, &GPIO_InitStructure);


    /* Connect PXx to USARTx */
    GPIO_PinAFConfig(USARTx_TXIO_PORT, USARTx_AF_TX_PIN, USARTx_AF_SELECT);
    GPIO_PinAFConfig(USARTx_RXIO_PORT, USARTx_AF_RX_PIN, USARTx_AF_SELECT);

    /* Connect PXx to USARTy */
    GPIO_PinAFConfig(USARTy_TXIO_PORT, USARTy_AF_TX_PIN, USARTy_AF_SELECT);
    GPIO_PinAFConfig(USARTy_RXIO_PORT, USARTy_AF_RX_PIN, USARTy_AF_SELECT);

    /* USART configured */
    usart_struct.USART_BaudRate = Baud;
    usart_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;    /* Hardware flow control disabled (RTS and CTS signals) */
    usart_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                    /* Receive and transmit enabled */
    usart_struct.USART_Parity = USART_Parity_No;                                /* Parity = No Parity */
    usart_struct.USART_StopBits = USART_StopBits_1;                             /* Stop Bit = 1 Stop Bit */
    usart_struct.USART_WordLength = USART_WordLength_8b;                        /* Word Length = 8 Bits */

    USART_Init(USARTx, &usart_struct);
    USART_Init(USARTy, &usart_struct);

    /* Enable USART */
    USART_Cmd(USARTx, ENABLE);
    USART_Cmd(USARTy, ENABLE);
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
  */
uint8_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer1 != *pBuffer2)
        {
            return 0;
        }

        pBuffer1++;
        pBuffer2++;
    }

    return 1;
}
#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif

/**
  * @}
  */

/**
  * @}
  */


