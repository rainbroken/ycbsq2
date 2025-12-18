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

/** @addtogroup USART_AutoBaudRate
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void USARTx_Config(uint32_t Baud);
static void SysTickConfig(void);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Initialize LED */
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);
    HK_EVAL_LEDInit(LED3);
    HK_EVAL_LEDInit(LED4);

    /* SysTick configuration */
    SysTickConfig();

    /* Configure USARTx and USARTy */
    USARTx_Config(115200);

    /* Configure the AutoBaudRate method StartBit */
    USART_AutoBaudRateConfig(USARTx, USART_AutoBaudRate_StartBit);

    /* Enable AutoBaudRate feature */
    USART_AutoBaudRateCmd(USARTx, ENABLE);

    /* Wait until Receive enable acknowledge flag is set */
    while (USART_GetFlagStatus(USARTx, USART_FLAG_REACK) == RESET)
    {

    }

    /* Wait until Transmit enable acknowledge flag is set */
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TEACK) == RESET)
    {

    }

    /* Loop until the end of Autobaudrate phase */
    while (USART_GetFlagStatus(USARTx, USART_FLAG_ABRF) == RESET)
    {

    }

    /* If AutoBaudBate error occurred ABRE = 1 */
    if (USART_GetFlagStatus(USARTx, USART_FLAG_ABRE) != RESET)
    {
        /* Turn on LED3 */
        HK_EVAL_LEDOn(LED3);
    }
    else
    {
        /* Turn on LED2 */
        HK_EVAL_LEDOn(LED2);

        /* Wait until RXNE flag is set */
        while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET)
        {

        }

        /* Wait until TXE flag is set */
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
        {

        }

        /* Send received data one byte */
        printf("%x\n", USART_ReceiveData(USARTx));

        debug("Automatic baud rate detection successful!");

        /* clear the TE bit (if a transmission is on going or a data is in the TDR, it will be sent before
        efectivelly disabling the transmission) */
        //        USART_DirectionModeCmd(USARTx, USART_Mode_Tx, DISABLE);
    }

    while (1)
    {

    }
}

/**
  * @brief  Configure the USART Device
  * @param  Baud: The USARTx BaudRate
  * @retval None
  */
void USARTx_Config(uint32_t Baud)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable GPIO clock and Enable USART Clock,USARTx,USARTy */
    USARTx_TXIO_CLK_CMD(USARTx_TXIO_CLK, ENABLE);
    USARTx_RXIO_CLK_CMD(USARTx_RXIO_CLK, ENABLE);
    USARTx_CLK_CMD(USARTx_CLK, ENABLE);


    /* GPIO Configure RX TX */
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_UP;

    GPIO_InitStructure.GPIO_Pin     = USARTx_TX_PIN;
    GPIO_Init(USARTx_TXIO_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin     = USARTx_RX_PIN;
    GPIO_Init(USARTx_RXIO_PORT, &GPIO_InitStructure);


    /* Connect PXx to USART1 Tx Rx */
    GPIO_PinAFConfig(USARTx_TXIO_PORT, USARTx_AF_TX_PIN, USARTx_AF_SELECT);
    GPIO_PinAFConfig(USARTx_RXIO_PORT, USARTx_AF_RX_PIN, USARTx_AF_SELECT);

    /* USARTx configured */
    USART_InitStructure.USART_BaudRate = Baud;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;    /* Hardware flow control disabled (RTS and CTS signals) */
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                    /* Receive and transmit enabled */

    /* When using Parity the word length must be configured to 9 bits */
    USART_InitStructure.USART_Parity = USART_Parity_No;                                /* No parity */
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                             /* One Stop Bit */
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                        /*Word Length = 8 Bits */

    USART_Init(USARTx, &USART_InitStructure);

    /* NVIC configuration */

    /* Enable the USARTx Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable the USARTx Receive interrupt: this interrupt is generated when the
    USARTx receive data register is not empty */
    //USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);

    /* Enable USART */
    USART_Cmd(USARTx, ENABLE);
}

/**
  * @brief  Configure a SysTick Base time to 1 ms.
  * @param  None
  * @retval None
  */
static void SysTickConfig(void)
{
    /* Set SysTick Timer for 10ms interrupts  */
    if (SysTick_Config(SystemCoreClock / 1000))
    {
        /* Capture error */
        while (1)
        {

        }
    }

    /* Configure the SysTick handler priority */
    NVIC_SetPriority(SysTick_IRQn, 0x0);
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


