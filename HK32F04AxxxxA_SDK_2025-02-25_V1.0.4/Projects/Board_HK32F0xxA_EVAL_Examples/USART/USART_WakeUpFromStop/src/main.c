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

/** @addtogroup USART_WakeUpFromStop
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint8_t InterruptCounter;

/* Private function prototypes -----------------------------------------------*/
void USART_WakeStop_Config(uint32_t Baud);
static void SysTickConfig(void);
static void RestoreConfiguration(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    uint32_t i = 0xFFFF;

    /* Initialize LED */
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);
    HK_EVAL_LEDInit(LED3);
    HK_EVAL_LEDInit(LED4);


    /* Configure USARTx use wakeup STOP mode */
    USART_WakeStop_Config(9600);

    debug("Enter STOP mode!");

    /* Waiting for data transfer to complete */
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) != RESET)
    {
    }

    /* delay a time to usart idle */
    while (i--)
    {
        
    }

    /* Enable PWR APB clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    /* Enter USART in STOP mode with regulator in low power mode */
    PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);

    /* Waiting Wake Up interrupt */
    while (InterruptCounter == 0x00)
    {
        
    }

    /* Restore system clock */
    RestoreConfiguration();

    debug("MCU STOP mode wake up!");

    /* Configure and enable the systick timer to generate an interrupt each 1 ms */
    SysTickConfig();

    while (1)
    {

    }
}

/**
  * @brief  Configure the USART Device
  * @param  Baud: The USARTx BaudRate
  * @retval None
  */
void USART_WakeStop_Config(uint32_t Baud)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable GPIO clock and Enable USART Clock,USARTx,USARTy */
    USARTx_TXIO_CLK_CMD(USARTx_TXIO_CLK, ENABLE);
    USARTx_RXIO_CLK_CMD(USARTx_RXIO_CLK, ENABLE);
    USARTx_CLK_CMD(USARTx_CLK, ENABLE);

    /* Configure the HSI as USART clock Need to wake up stop mode must use HSI or LSE */
    USARTx_STOPCLK_COFIG(USARTx_STOPCLK);

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

    /* Configure the wake up Method = Start bit */
    USART_StopModeWakeUpSourceConfig(USARTx, USART_WakeUpSource_StartBit);

    /* Enable USART */
    USART_Cmd(USARTx, ENABLE);

    /* Before entering the USART in STOP mode the REACK flag must be checked to ensure the USART RX is ready */
    while (USART_GetFlagStatus(USARTx, USART_FLAG_REACK) == RESET)
    {

    }

    /* Enable USART STOP mode by setting the UESM bit in the CR1 register */
    USART_STOPModeCmd(USARTx, ENABLE);

    /* Enable the wake up from stop Interrupt WUF */
    USART_ITConfig(USARTx, USART_IT_WU, ENABLE);
}

/**
  * @brief  Restore peripheral config before entering STOP mode.
  * @param  None
  * @retval None
  */
void RestoreConfiguration(void)
{
    uint32_t ntick = 0xFFFF;
    __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */

    /* Enable HSI */
    RCC->CFGR4 |= ((uint32_t)RCC_CFGR4_HSI56ON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSIStatus = RCC->CFGR4 & RCC_CFGR4_HSI56RDY;
        StartUpCounter++;
    } while ((HSIStatus == 0) && (StartUpCounter != HSI_STARTUP_TIMEOUT));

    if ((RCC->CFGR4 & RCC_CFGR4_HSI56RDY) != RESET)
    {
        HSIStatus = (uint32_t)0x01;
    }
    else
    {
        HSIStatus = (uint32_t)0x00;
    }

    if (HSIStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Flash 1 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_Latency_2;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)0x0 << RCC_CFGR_HPRE_Pos;
        /* PCLK = HCLK/2 */
        RCC->CFGR |= (uint32_t)0x4 << RCC_CFGR_PPRE_Pos;
        /* Select HSI56 as system clock source */
        RCC->CFGR4 |= RCC_CFGR4_ESSS;
        RCC->CFGR4 &= ~(RCC_CFGR4_ESW);
        RCC->CFGR4 |= (uint32_t)0x2 << RCC_CFGR4_ESW_Pos;

        /* Wait till HSI is used as system clock source */
        while ((RCC->CFGR4 & (uint32_t)RCC_CFGR4_ESWS) != ((uint32_t)0x2 << RCC_CFGR4_ESWS_Pos))
        {
        }
    }
    else
    {
        /* If fails to start-up */
    }

    /* delay for clock stability */
    while (ntick --)
    {

    }
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


