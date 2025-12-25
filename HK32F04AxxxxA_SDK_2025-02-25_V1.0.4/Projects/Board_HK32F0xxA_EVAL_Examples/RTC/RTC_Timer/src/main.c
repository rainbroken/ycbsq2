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
#include "hk32f0xxa_eval.h"

/** @addtogroup HK32F0xxA_StdPeriph_Examples
  * @{
  */

/** @addtogroup RTC_Timer_Example
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint8_t ALARM_Occured = 0;
__IO uint32_t RTCAlarmCount = 0;

/* Private function prototypes -----------------------------------------------*/
static void RTC_Config(void);
static void RTC_AlarmConfig(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_hk32f0xxa.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_hk32f0xxa.c file
       */
    NVIC_InitTypeDef  NVIC_InitStructure;
    EXTI_InitTypeDef  EXTI_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    uint32_t ProcessBak = 0xff;

    /* USARTx configured as follow:
          - BaudRate = 115200 baud
          - Word Length = 8 Bits
          - One Stop Bit
          - No parity
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

    /* Output a message on Hyperterminal using printf function */
    printf("\n\r  *********************** RTC Hardware Timer Example ***********************\n\r");
    printf("\n\r  **    Press SEL button to start the RTC                                 **\n\r");
    printf("\n\r  **    Press Tamper button to stop the RTC                               **\n\r");
    printf("\n\r  **************************************************************************\n\r");

    /* RTC configuration  */
    RTC_Config();

    /* Configure the external interrupt "KEY", "SEL" buttons */
    HK_EVAL_PBInit(BUTTON_TAMPER, BUTTON_MODE_EXTI);
    HK_EVAL_PBInit(BUTTON_SEL, BUTTON_MODE_EXTI);

    /* Configure RTC AlarmA register to generate 8 interrupts per 1 Second */
    RTC_AlarmConfig();

    /* Configure LEDs */
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);

    /* Turn LED2 ON */
    HK_EVAL_LEDOn(LED2);

    /* RTC Alarm A Interrupt Configuration */

    /* EXTI configuration *********************************************************/
    EXTI_ClearITPendingBit(EXTI_Line17);
    EXTI_InitStructure.EXTI_Line = EXTI_Line17;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Enable the RTC Alarm Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Infinite loop */
    while (1)
    {
        uint32_t tmp = 0;

        /* ALARM Interrupt */
        if (ALARM_Occured)
        {
            if (RTCAlarmCount != 480)
            {
                /* Increament the counter of Alarma interrupts */
                RTCAlarmCount++;

                /* Define the rate of Progress bar */
                tmp = (RTCAlarmCount * 100) / 480;

                if (ProcessBak != tmp)
                {
                    printf("\r\n%3d%%", tmp);
                    ProcessBak = tmp;
                }
            }
            else
            {
                /* Disable the RTC Clock */
                RCC_RTCCLKCmd(DISABLE);

                /* Turn LED1 OFF */
                HK_EVAL_LEDOff(LED1);
            }

            /* Reinitialize the ALARM variable */
            ALARM_Occured = 0;
        }
    }
}

/**
  * @brief  Configures the RTC peripheral and select the clock source.
  * @param  None
  * @retval None
  */
static void RTC_Config(void)
{
    RTC_InitTypeDef  RTC_InitStructure;
    RTC_TimeTypeDef  RTC_TimeStruct;

    /* Enable the PWR clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    /* Allow access to RTC */
    PWR_BackupAccessCmd(ENABLE);

    /* Reset RTC Domain */
    RCC_BackupResetCmd(ENABLE);
    RCC_BackupResetCmd(DISABLE);

    /* Enable the LSE OSC */
    RCC_LSEConfig(RCC_LSE_ON);

    /* Wait till LSE is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
    {
        ;
    }

    /* Select the RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

    /* Configure the RTC data register and RTC prescaler */

    /* ck_spre(1Hz) = RTCCLK(LSI) /(AsynchPrediv + 1)*(SynchPrediv + 1)*/
    RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
    RTC_InitStructure.RTC_SynchPrediv  = 0xFF;
    RTC_InitStructure.RTC_HourFormat   = RTC_HourFormat_24;
    RTC_Init(&RTC_InitStructure);

    /* Set the time to 00h 00mn 00s AM */
    RTC_TimeStruct.RTC_H12     = RTC_H12_AM;
    RTC_TimeStruct.RTC_Hours   = 0x00;
    RTC_TimeStruct.RTC_Minutes = 0x00;
    RTC_TimeStruct.RTC_Seconds = 0x00;
    RTC_SetTime(RTC_Format_BCD, &RTC_TimeStruct);
}

/**
  * @brief  Configures the RTC Alarm.
  * @retval None
  */
static void RTC_AlarmConfig(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    RTC_AlarmTypeDef RTC_AlarmStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RTC_AlarmStructInit(&RTC_AlarmStructure);

    /* EXTI configuration */
    EXTI_ClearITPendingBit(EXTI_Line17);
    EXTI_InitStructure.EXTI_Line = EXTI_Line17;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Enable the RTC Alarm Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Set the alarmA Masks */
    RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_All;
    RTC_SetAlarm(RTC_Format_BCD, RTC_Alarm_A, &RTC_AlarmStructure);

    /* Set AlarmA subseconds and enable SubSec Alarm : generate 8 interripts per Second */
    RTC_AlarmSubSecondConfig(RTC_Alarm_A, 0xFF, RTC_AlarmSubSecondMask_SS14_5);

    /* Enable AlarmA interrupt */
    RTC_ITConfig(RTC_IT_ALRA, ENABLE);
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
        ;
    }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

