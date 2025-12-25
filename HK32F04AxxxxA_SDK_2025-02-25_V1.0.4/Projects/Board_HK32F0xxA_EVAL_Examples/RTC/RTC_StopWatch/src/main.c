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

/** @addtogroup RTC_Tamper_Example
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
#define MESSAGE1   "\n\r  *********************** RTC StopWatch Example ***********************\n\r"
#define MESSAGE2   "\n\r  **   Press LEFT button to start the stopwatch                      **\n\r"
#define MESSAGE3   "\n\r  **   Press RIGHT button to log the stopwatch                       **\n\r"
#define MESSAGE4   "\n\r  **   Press and hold TAMPER to stop the stopwatch                   **\n\r"
/* Private macro -------------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define RTC_BKP_DR_NUMBER              5  /* RTC Backup Data Register Number */

/* Uncomment the corresponding line to select the RTC Clock source */
#define RTC_CLOCK_SOURCE_LSE   /* LSE used as RTC source clock */
/* #define RTC_CLOCK_SOURCE_LSI */ /* LSI used as RTC source clock. The RTC Clock
                                      may varies due to LSI frequency dispersion. */


/* Private macro -------------------------------------------------------------*/
#define WATCH_DOG_LOG_CNT               ((uint32_t)2)
/* Private variables ---------------------------------------------------------*/
__IO uint32_t SecondFraction = 0;
uint32_t BackupIndex = 0;
__IO uint32_t SubSecFrac = 0;
__IO uint8_t StartEvent = 0;
__IO uint8_t Button_State = 0;
__IO uint8_t Button_RTC = 0;
uint8_t i = 0;
extern __IO uint32_t CurrentTimeSec;
/* Define the backup register */
uint32_t BKPDataReg[5] = { RTC_BKP_DR0, RTC_BKP_DR1, RTC_BKP_DR2, RTC_BKP_DR3, RTC_BKP_DR4
                         };
__IO uint32_t CurrentTimeSec = 0;
/* Private function prototypes -----------------------------------------------*/
static void RTC_Config(void);
static void RTC_TamperConfig(void);

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
    RTC_TimeTypeDef  RTC_TimeStruct;
    RTC_TimeTypeDef  RTC_TimeStructureInit;
    RTC_TimeTypeDef  RTC_StampTimeStruct;
    USART_InitTypeDef USART_InitStructure;
    static uint32_t SubSecondBak = 0;

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
    printf("%s", MESSAGE1);
    printf("%s", MESSAGE2);
    printf("%s", MESSAGE3);
    printf("%s", MESSAGE4);

    /* Configure the external interrupt "RIGHT" and "LEFT" buttons */
    HK_EVAL_PBInit(BUTTON_RIGHT, BUTTON_MODE_EXTI);
    HK_EVAL_PBInit(BUTTON_LEFT, BUTTON_MODE_EXTI);

    /* Configure the RTC peripheral by selecting the clock source */
    RTC_Config();

    /* Configure the RTC tamper register : To Clear all the Backup data register */
    RTC_TamperConfig();

    /* Initialize time Stucture */
    RTC_TimeStructInit(&RTC_TimeStruct);

    /* Infinite loop */
    while (1)
    {
        /* Check on the event 'start' */
        if (StartEvent != 0x0)
        {
            /* Get the RTC sub second fraction */
            SecondFraction = (((256 - (uint32_t)RTC_GetSubSecond()) * 1000) / 256);

            if (SubSecondBak != SecondFraction)
            {
                /* Get the Curent time */
                RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);

                /* Refresh : Display the curent time and the sub second on the LCD  */
                //RTC_Time_Display(37, Black , RTC_Get_Time(SecondFraction , &RTC_TimeStruct));
                printf("\r\n %2d:%2d:%2d:%3d", RTC_TimeStruct.RTC_Hours, RTC_TimeStruct.RTC_Minutes,
                       RTC_TimeStruct.RTC_Seconds, SecondFraction);
                SubSecondBak = SecondFraction;
            }
        }
        else
        {
            /* Re-initialize the Display time on the LCD */
            //RTC_Time_InitDisplay();
        }

        /* Left button is pressed */
        if (Button_State == LEFT_ON)
        {
            /* Enable Tamper interrupt */
            RTC_ITConfig(RTC_IT_TAMP, ENABLE);
            /* Enabale the tamper 1 */
            RTC_TamperCmd(RTC_Tamper_1, ENABLE);
            /* Get the current time */
            RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructureInit);
            CurrentTimeSec = (RTC_TimeStructureInit.RTC_Hours * 3600) + (RTC_TimeStructureInit.RTC_Minutes * 60) +
                             RTC_TimeStructureInit.RTC_Seconds;
            /* start count */
            StartEvent = 0x1;
            /* Reinitialize Button_State variable */
            Button_State = 0;
        }
        /* Right button is pressed */
        else if (Button_State == RIGHT_ON)
        {
            if (BackupIndex < WATCH_DOG_LOG_CNT)
            {
                SubSecFrac = 0;

                /* Get the Current sub second and time */
                SubSecFrac = (((256 - (uint32_t)RTC_GetSubSecond()) * 1000) / 256);
                RTC_GetTime(RTC_Format_BIN, &RTC_StampTimeStruct);

                /* Display result on the LCD */
                //RTC_Time_Display( LINE(3 + BackupIndex), Colorx, RTC_Get_Time(SubSecFrac , &RTC_StampTimeStruct) );
                printf("\r\n %2d:%2d:%2d:%3d", RTC_TimeStruct.RTC_Hours, RTC_TimeStruct.RTC_Minutes,
                       RTC_TimeStruct.RTC_Seconds, SecondFraction);
                //if (BackupIndex < 2)
                {
                    /* Save time register  to Backup register ( the first 5 register is reserved for time) */
                    RTC_WriteBackupRegister(BKPDataReg[BackupIndex], (uint32_t)RTC->TR);

                    /* Save sub second time stamp register ( the latest 6 register is reserved for time) */
                    RTC_WriteBackupRegister(BKPDataReg[BackupIndex + 2], SubSecFrac);
                }
            }
            else
            {
                /* the backup register is full with 2trials */
                printf("%s", MESSAGE4);
            }

            BackupIndex++;
            /* Reinitialize Button_State variable */
            Button_State = 0;
        }
        /* TAMPER button is pressed */
        else if (Button_RTC == RTC_TAMP)
        {
            /* reset Counter */
            BackupIndex = 0 ;
            /* Enetr to idle */
            StartEvent = 0x0;
            /* Enable Tamper interrupt */
            RTC_ITConfig(RTC_IT_TAMP, DISABLE);
            /* Enabale the tamper 1 */
            RTC_TamperCmd(RTC_Tamper_1, DISABLE);
            /* Reinitialize Button_RTC variable */
            Button_RTC = 0;
        }
    }
}

/**
  * @brief  RTC Tamper Configuration..
  * @retval None
  */
static void RTC_TamperConfig(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* EXTI configuration *********************************************************/
    EXTI_ClearITPendingBit(EXTI_Line19);
    EXTI_InitStructure.EXTI_Line = EXTI_Line19;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Enable RTC_IRQn */
    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* determines the number of active pulse for the specific level */
    RTC_TamperFilterConfig(RTC_TamperFilter_2Sample);

    /* Determines the frequency at which each of the tamper inputs are sampled */
    RTC_TamperSamplingFreqConfig(RTC_TamperSamplingFreq_RTCCLK_Div32768);
    RTC_TamperPullUpCmd(DISABLE);

    /* Select the tamper 1 with High level */
    RTC_TamperTriggerConfig(RTC_Tamper_1, RTC_TamperTrigger_LowLevel );

    /* Clear tamper 1 flag */
    RTC_ClearFlag(RTC_FLAG_TAMP1F);
}

/**
  * @brief  Configure the RTC peripheral by selecting the clock source.
  * @retval None
  */
static void RTC_Config(void)
{
    RTC_InitTypeDef RTC_InitStructure;
    RTC_TimeTypeDef  RTC_TimeStruct;

    /* Enable the PWR clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    /* Allow access to RTC */
    PWR_BackupAccessCmd(ENABLE);

    /* Enable the LSE OSC */
    RCC_LSEConfig(RCC_LSE_ON);

    /* Wait till LSE is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
    {
        ;
    }

    /* Select the RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
    RTC_DeInit();

    /* Configure the RTC data register and RTC prescaler */
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

    /* Enable the RTC Clock */
    RCC_RTCCLKCmd(ENABLE);

    /* Wait for RTC APB registers synchronisation */
    RTC_WaitForSynchro();
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

