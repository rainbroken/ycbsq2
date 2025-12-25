/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-10-15
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup HK32F0xxA_StdPeriph_Examples
  * @{
  */

/** @addtogroup WWDG_Reset
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define BufLen(a)   (sizeof(a) / sizeof(*(a)))

/* Private variables ---------------------------------------------------------*/
__IO uint32_t TimingDelay;

/* Private function prototypes -----------------------------------------------*/
static void DEBUG_USARTx_Config(uint32_t Baud);
static void SysTickConfig(void);

void WWDG_Config(void);
void Delay_ms(__IO uint32_t nTime);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* LED Init */
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);

    /* Tamper Button EXTI Init */
    HK_EVAL_PBInit(BUTTON_TAMPER, BUTTON_MODE_EXTI);

    /* USARTx Configured for printf */
    DEBUG_USARTx_Config(115200);

    /* Check if the system has resumed from WWDG reset */
    if (RCC_GetFlagStatus(RCC_FLAG_WWDGRST) != RESET)
    {
        /* WWDGRST flag set */

        /* Turn on LED1 */
        HK_EVAL_LEDOn(LED1);

        /* Clear reset flags */
        RCC_ClearFlag();
        debug("WWDGRST flag set!");
    }
    else
    {
        /* WWDGRST flag is not set */

        /* Turn off LED1 */
        HK_EVAL_LEDOff(LED1);
        debug("WWDGRST flag is not set!");
    }

    /* Setup SysTick Timer for 1 msec interrupts  */
    SysTickConfig();

    /* Configure WWDG */
    WWDG_Config();

    while (1)
    {
        /* Toggle LED2 */
        HK_EVAL_LEDToggle(LED2);

        /* Insert 33 ms delay */
        Delay_ms(33);

        /* Update WWDG counter */
        WWDG_SetCounter(127);
    }
}
/**
  * @brief  Configure the WWDG Device
  * @param  None
  * @retval None
  */
void WWDG_Config(void)
{
    /* Enable WWDG clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);

    /* WWDG clock counter = (PCLK1 (48MHz)/4096)/8 = 1464Hz (~683 us)  */
    WWDG_SetPrescaler(WWDG_Prescaler_8);

    /* Set Window value to 80; WWDG counter should be refreshed only when the counter
    is below 80 (and greater than 64) otherwise a reset will be generated */
    WWDG_SetWindowValue(80);

    /* Enable WWDG and set counter value to 127, WWDG timeout = ~683 us * 64 = 43.7 ms
     In this case the refresh window is: ~683 * (127-80)= 32.1ms < refresh window < ~683 * 64 = 43.7ms
     */
    WWDG_Enable(127);

}

/**
  * @brief  Configure the USARTx Device for printf
  * @param  Baud: The USARTx BaudRate
  * @retval None
  */
static void DEBUG_USARTx_Config(uint32_t Baud)
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
    USART_InitStructure.USART_BaudRate = Baud;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    HK_EVAL_COMInit(COM1, &USART_InitStructure);
}

/**
  * @brief  Configure a SysTick Base time to 10 ms.
  * @param  None
  * @retval None
  */
static void SysTickConfig(void)
{
    /* Set SysTick Timer for 1ms interrupts  */
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

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 1 ms.
  * @retval None
  */
void Delay_ms(__IO uint32_t nTime)
{
    TimingDelay = nTime;

    while (TimingDelay != 0)
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


