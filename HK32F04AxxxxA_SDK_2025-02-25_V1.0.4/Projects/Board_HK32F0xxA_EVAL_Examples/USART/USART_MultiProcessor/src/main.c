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

/** @addtogroup USART_MultiProcessor
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void USARTxy_Config(uint32_t Baud);
void Delay(__IO uint32_t nCount);

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

    /* Initialize Wakeup and Key Buttons EXTI line */
    HK_EVAL_PBInit(BUTTON_UP, BUTTON_MODE_EXTI);
    HK_EVAL_PBInit(BUTTON_DOWN, BUTTON_MODE_EXTI);

    /* Configure USARTx and USARTy */
    USARTxy_Config(115200);

    /* Config These bit field can only be written when the USART is disabled (UE=0). */
    USART_Cmd(USARTy, DISABLE);

    /* Set the USARTx Address */
    USART_SetAddress(USARTx, 0x1);

    /* Set the USARTy Address */
    USART_SetAddress(USARTy, 0x2);

    /* NOTE USART in Multiprocessor Communication,LINEN bit in USART_CR2 register,
    The HDSEL, IREN, and SCEN bits in the USART_CR3 register need to be zero */

    /* Select the USARTY WakeUp Method */
    USART_MuteModeWakeUpConfig(USARTy, USART_WakeUp_AddressMark);

    /* Enable the USARTy mute mode switch */
    USART_MuteModeCmd(USARTy, ENABLE);

    /* Enable USARTy */
    USART_Cmd(USARTy, ENABLE);

    debug("system is running!");

    while (1)
    {
        /* Send one byte from USARTX to USARTy */
        USART_SendData(USARTx, 0x33);

        /* Wait while USART1 TC = 0 */
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
        {
        }

        if (USART_GetFlagStatus(USARTy, USART_FLAG_RXNE) != RESET)
        {
            /* control LED */
            if (USART_ReceiveData(USARTy) == 0x33)
            {
                HK_EVAL_LEDToggle(LED1);
                Delay(0x5FFFF);
                HK_EVAL_LEDToggle(LED2);
                Delay(0x5FFFF);
                HK_EVAL_LEDToggle(LED3);
                Delay(0x5FFFF);
                HK_EVAL_LEDToggle(LED4);
                Delay(0x5FFFF);
                printf("USARTy has Received 0X33 data!\n");
            }
        }
    }
}

/**
  * @brief  Configure the USART Device USARTx and USARTy
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
    GPIO_Init( USARTx_TXIO_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin     = USARTx_RX_PIN;
    GPIO_Init( USARTx_RXIO_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin     = USARTy_TX_PIN;
    GPIO_Init( USARTy_TXIO_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin     = USARTy_RX_PIN;
    GPIO_Init( USARTy_RXIO_PORT, &GPIO_InitStructure);


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
    usart_struct.USART_WordLength = USART_WordLength_9b;                        /* Word Length = 9 Bits */

    USART_Init(USARTx, &usart_struct);
    USART_Init(USARTy, &usart_struct);

    /* Enable USART */
    USART_Cmd(USARTx, ENABLE);
    USART_Cmd(USARTy, ENABLE);
}


/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
void Delay(__IO uint32_t nCount)
{
    /* Decrement nCount value,a Simple Counting Delay */
    for (; nCount != 0; nCount--)
    {

    }
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


