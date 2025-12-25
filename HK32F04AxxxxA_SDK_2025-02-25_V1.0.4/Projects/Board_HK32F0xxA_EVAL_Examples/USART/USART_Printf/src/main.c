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

/** @addtogroup USART_Printf
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint8_t NbrOfDataToTransfer;
extern uint8_t NbrOfDataToRead;
extern __IO uint8_t TxCount;
extern __IO uint16_t RxCount;

/* Private function prototypes -----------------------------------------------*/
static void USARTx_Config(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /*
    Note: In order to adapt to the output redirection of printf for different compilers,
    this macro needs to define PUTCHAR_PROTOTYPE, defined in hk32f0xxa_ def.h,
    then Change the position of printf output in the PUTCHAR_PROTOTYPE function
    to the USART1 TDR
    */

    /* USART configuration */
    USARTx_Config();

    /* Output a message on Hyperterminal using printf function */
    printf("\n\rUSART Printf Example: retarget the C library printf function to the USART\n\r");

    /* Output a message on Hyperterminal using printf function with with file name and number of lines */
    debug("USART Printf Example:printf with file name and number of lines");

    /* Loop until the end of transmission */

    /* The software must wait until TC=1. The TC flag remains cleared during all data
     transfers and it is set by hardware at the last frame?s end of transmission*/
    while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) == RESET)
    {
        
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
static void USARTx_Config(void)
{
    USART_InitTypeDef USART_InitStructure;

    /* USARTx configured as follow:
    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - Stop Bit = 1 Stop Bit
    - Parity = No Parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    HK_EVAL_COMInit(COM1, &USART_InitStructure);
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


