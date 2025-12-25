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

/** @addtogroup IWDG_Reset
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define BufLen(a)   (sizeof(a) / sizeof(*(a)))

/* Private variables ---------------------------------------------------------*/
__IO uint32_t TimingDelay;
__IO uint32_t LsiFreq = 40000;

/* Private function prototypes -----------------------------------------------*/
void DEBUG_USARTx_Config(uint32_t Baud);
void IWDG_Config(void);

static void SysTickConfig(void);
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

    /* Check if the system has resumed from IWDG reset */
    if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
    {
        /* IWDGRST flag set */

        /* Turn on LED1 */
        HK_EVAL_LEDOn(LED1);

        /* Clear reset flags */
        RCC_ClearFlag();
        debug("IWDGRST flag set!");
    }
    else
    {
        /* IWDGRST flag is not set */

        /* Turn off LED1 */
        HK_EVAL_LEDOff(LED1);
        debug("IWDGRST flag is not set!");
    }

    /* Setup SysTick Timer for 1 msec interrupts  */
    SysTickConfig();

    /* IWDG configuration to 250ms*/
    IWDG_Config();

    while (1)
    {
        /* Toggle LED2 */
        HK_EVAL_LEDToggle(LED2);

        /* Insert 220 ms delay */
        Delay_ms(220);

        /* Reload IWDG counter */
        IWDG_ReloadCounter();
        //printf("Reload IWDG counter!");
    }
}
/**
  * @brief  Configure the IWDG Device
  * @param  None
  * @retval None
  */
void IWDG_Config(void)
{

    /* Enable write access to IWDG_PR and IWDG_RLR registers */
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

    /* IWDG counter clock: LSI/32 = 40000/16 = 1250HZ */
    IWDG_SetPrescaler(IWDG_Prescaler_32);

    /* Set counter reload value to obtain 250ms IWDG TimeOut.
     Counter Reload Value = 250ms/IWDG counter clock period
                          = 250ms / (LSI/32)
                          = 0.25s / (LsiFreq/32)
                          = LsiFreq/(32 * 4)
                          = LsiFreq/128
    */
    IWDG_SetReload(LsiFreq / 128);

    /* Reload IWDG counter */
    IWDG_ReloadCounter();

    /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
    IWDG_Enable();
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


