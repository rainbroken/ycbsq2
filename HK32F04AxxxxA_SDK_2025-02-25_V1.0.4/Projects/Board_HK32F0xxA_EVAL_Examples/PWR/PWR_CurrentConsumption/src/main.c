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

/** @addtogroup HK32F0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup PWR_CurrentConsumption
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#if !defined (SLEEP_MODE) && !defined (STOP_MODE) && !defined (STANDBY_MODE)\
    && !defined (STANDBY_RTC_MODE)
    /* Uncomment the corresponding line to select the HK32F0xxA Low Power mode */
    #define SLEEP_MODE
    //#define STOP_MODE
    //#define STANDBY_MODE
    //#define STANDBY_RTC_MODE
#endif

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t i = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void SleepMode_Measure(void);
void StopMode_Measure(void);
void StandbyMode_Measure(void);
void StandbyRTCMode_Measure(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Configure Tamper Button */
    HK_EVAL_PBInit(BUTTON_TAMPER, BUTTON_MODE_GPIO);

    /* Loop while Tamper button is maintained pressed */
    while (HK_EVAL_PBGetState(BUTTON_TAMPER) == RESET)
    {
    }

    /* Enable PWR APB1 Clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    /* Allow access to Backup */
    PWR_BackupAccessCmd(ENABLE);

    /* Reset RTC Domain */
    RCC_BackupResetCmd(ENABLE);
    RCC_BackupResetCmd(DISABLE);

    /* Loop while Tamper button is maintained pressed */
    while (HK_EVAL_PBGetState(BUTTON_TAMPER) != RESET)
    {
    }

    /* Loop while Tamper button is maintained pressed */
    while (HK_EVAL_PBGetState(BUTTON_TAMPER) == RESET)
    {
    }

#if defined (SLEEP_MODE)

    /* Sleep Mode Entry
        - System Running at PLL (48MHz)
        - Flash 3 wait state
        - Prefetch and Cache enabled
        - Code running from Internal FLASH
        - All peripherals disabled.
        - Wakeup using EXTI Line (Joystick SEL Button PA.00)
     */
    SleepMode_Measure();
#elif defined (STOP_MODE)

    /* STOP Mode Entry
        - RTC Clocked by LSI
        - Regulator in LP mode
        - HSI, HSE OFF and LSI OFF if not used as RTC Clock source
        - No IWDG
        - FLASH in deep power down mode
        - Automatic Wakeup using RTC clocked by LSI
     */
    StopMode_Measure();
#elif defined (STANDBY_MODE)

    /* STANDBY Mode Entry
        - RTC OFF
        - IWDG and LSI OFF
        - Wakeup using WakeUp Pin 2(PC.13)
     */
    StandbyMode_Measure();
#elif defined (STANDBY_RTC_MODE)

    /* STANDBY Mode with RTC on LSI Entry
        - RTC Clocked by LSI
        - IWDG OFF and LSI OFF if not used as RTC Clock source
        - Automatic Wakeup using RTC clocked by LSI
     */
    StandbyRTCMode_Measure();
#else

    /* Initialize LED3 on EVAL board */
    HK_EVAL_LEDInit(LED3);

    /* Infinite loop */
    while (1)
    {
        /* Toggle The LED3 */
        HK_EVAL_LEDToggle(LED3);

        /* Inserted Delay */
        for (i = 0; i < 0x7FFF; i++)
        {
        }
    }

#endif
}

/**
  * @brief  Config SleepMode
  * @param  None
  * @retval None
  */
void SleepMode_Measure(void)
{
    __IO uint32_t index = 0;
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Configure all GPIO as analog to reduce current consumption on non used IOs */

    /* Enable GPIOs clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC |
                          RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOF, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* Disable GPIOs clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC |
                          RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOF, DISABLE);

    /* Configure Joystick SEL Button */
    HK_EVAL_PBInit(BUTTON_SEL, BUTTON_MODE_EXTI);

    /* Request to enter SLEEP mode */
    __WFI();

    /* Initialize LED4 on EVAL board */
    HK_EVAL_LEDInit(LED4);

    /* Infinite loop */
    while (1)
    {
        /* Toggle The LED4 */
        HK_EVAL_LEDToggle(LED4);

        /* Inserted Delay */
        for (index = 0; index < 0x7FFFF; index++)
        {
        }
    }
}

/**
  * @brief  This function configures the system to enter Stop mode with RTC
  *         clocked by LSI for current consumption measurement purpose.
  *         STOP Mode with RTC clocked by LSI
  *         =====================================
  *         - RTC Clocked by LSI
  *         - Regulator in LP mode
  *         - HSI, HSE OFF and LSI OFF if not used as RTC Clock source
  *         - No IWDG
  *         - FLASH in deep power down mode
  *         - Automatic Wakeup using RTC clocked by LSI (~5s)
  * @param  None
  * @retval None
  */
void StopMode_Measure(void)
{
    __IO uint32_t index = 0;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;
    EXTI_InitTypeDef  EXTI_InitStructure;
    RTC_InitTypeDef   RTC_InitStructure;
    RTC_TimeTypeDef   RTC_TimeStructure;
    RTC_AlarmTypeDef  RTC_AlarmStructure;

    /* Allow access to RTC */
    PWR_BackupAccessCmd(ENABLE);

    /* The RTC Clock may varies due to LSI frequency dispersion. */

    /* Enable the LSI OSC */
    RCC_LSICmd(ENABLE);

    /* Wait till LSI is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
    {
    }

    /* Select the RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

    /* Enable the RTC Clock */
    RCC_RTCCLKCmd(ENABLE);

    /* Wait for RTC APB registers synchronisation */
    RTC_WaitForSynchro();

    /* Configure all GPIO as analog to reduce current consumption on non used IOs */

    /* Enable GPIOs clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC |
                          RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOF, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* Disable GPIOs clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC |
                          RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOF, DISABLE);
    RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
    RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
    RTC_InitStructure.RTC_SynchPrediv = 0x0138;

    if (RTC_Init(&RTC_InitStructure) == ERROR)
    {
        while (1)
        {
        }
    }

    /* EXTI configuration */
    EXTI_ClearITPendingBit(EXTI_Line17);
    EXTI_InitStructure.EXTI_Line = EXTI_Line17;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    /* NVIC configuration */
    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    /* Set the alarm X+5s */
    RTC_AlarmStructure.RTC_AlarmTime.RTC_H12     = RTC_H12_AM;
    RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours   = 0x01;
    RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = 0x00;
    RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = 0x05;
    RTC_AlarmStructure.RTC_AlarmDateWeekDay = 0x31;
    RTC_AlarmStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
    RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay;
    RTC_SetAlarm(RTC_Format_BCD, RTC_Alarm_A, &RTC_AlarmStructure);
    /* Enable the alarm */
    RTC_AlarmCmd(RTC_Alarm_A, ENABLE);
    /* Enable the RTC Alarm A interrupt */
    RTC_ITConfig(RTC_IT_ALRA, ENABLE);
    /* Set the time to 01h 00mn 00s AM */
    RTC_TimeStructure.RTC_H12     = RTC_H12_AM;
    RTC_TimeStructure.RTC_Hours   = 0x01;
    RTC_TimeStructure.RTC_Minutes = 0x00;
    RTC_TimeStructure.RTC_Seconds = 0x00;
    RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);
    /* Clear the Alarm A Pending Bit */
    RTC_ClearITPendingBit(RTC_IT_ALRA);
    /* Enter Stop Mode */
    PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
    /* Initialize LED4 on EVAL board */
    HK_EVAL_LEDInit(LED4);

    /* Infinite loop */
    while (1)
    {
        /* Toggle The LED4 */
        HK_EVAL_LEDToggle(LED4);

        /* Inserted Delay */
        for (index = 0; index < 0x5FFFF; index++)
        {
        }
    }
}

/**
  * @brief  This function configures the system to enter Standby mode for
  *         current consumption measurement purpose.
  *         STANDBY Mode
  *         ============
  *         - RTC OFF
  *         - IWDG and LSI OFF
  *         - Wakeup using WakeUp Pin2 (PC.13)
  * @param  None
  * @retval None
  */
void StandbyMode_Measure(void)
{
    /* Disable wake-up source(Wake up pin) to guarantee free access to WUT level-OR input */
    PWR_WakeUpPinCmd(PWR_WakeUpPin_1, DISABLE);

    /* Clear Standby flag */
    PWR_ClearFlag(PWR_FLAG_SB);

    /* Clear Power Wake-up (CWUF) flag */
    PWR_ClearFlag(PWR_FLAG_WU);

    /* Enable WKUP pin 1 */
    PWR_WakeUpPinCmd(PWR_WakeUpPin_1, ENABLE);

    /* Request to enter STANDBY mode (Wake Up flag is cleared in PWR_EnterSTANDBYMode function) */
    PWR_EnterSTANDBYMode(PWR_STANDBYEntry_WFI);

    /* Infinite loop */
    while (1)
    {
    }
}

/**
  * @brief  This function configures the system to enter Standby mode with RTC
  *         clocked by LSI for current consumption measurement purpose.
  *         STANDBY Mode with RTC clocked by LSI
  *         ========================================
  *         - RTC Clocked by LSI
  *         - IWDG OFF
  *         - Automatic Wakeup using RTC
  * @param  None
  * @retval None
  */
void StandbyRTCMode_Measure(void)
{
    RTC_InitTypeDef   RTC_InitStructure;
    RTC_AlarmTypeDef  RTC_AlarmStructure;
    RTC_TimeTypeDef   RTC_TimeStructure;

    /* Allow access to RTC */
    PWR_BackupAccessCmd(ENABLE);

    /* The RTC Clock may varies due to LSI frequency dispersion. */

    /* Enable the LSI OSC */
    RCC_LSICmd(ENABLE);

    /* Wait till LSI is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
    {
    }

    /* Select the RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

    /* Enable the RTC Clock */
    RCC_RTCCLKCmd(ENABLE);

    /* Wait for RTC APB registers synchronisation */
    RTC_WaitForSynchro();
    RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
    RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
    RTC_InitStructure.RTC_SynchPrediv = 0x0138;
    RTC_Init(&RTC_InitStructure);

    /* Set the alarm X+5s */
    RTC_AlarmStructure.RTC_AlarmTime.RTC_H12     = RTC_H12_AM;
    RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours   = 0x01;
    RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = 0x00;
    RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = 0x08;
    RTC_AlarmStructure.RTC_AlarmDateWeekDay = 0x31;
    RTC_AlarmStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
    RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay;
    RTC_SetAlarm(RTC_Format_BCD, RTC_Alarm_A, &RTC_AlarmStructure);

    /* Enable the alarm */
    RTC_AlarmCmd(RTC_Alarm_A, ENABLE);

    /* Set the time to 01h 00mn 00s AM */
    RTC_TimeStructure.RTC_H12     = RTC_H12_AM;
    RTC_TimeStructure.RTC_Hours   = 0x01;
    RTC_TimeStructure.RTC_Minutes = 0x00;
    RTC_TimeStructure.RTC_Seconds = 0x00;
    RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);

    /* Disable RTC Alarm A Interrupt */
    RTC_ITConfig(RTC_IT_ALRA, DISABLE);

    /* Clear Power Wake-up (CWUF) flag */
    PWR_ClearFlag(PWR_FLAG_WU);

    /* Enable RTC Alarm A Interrupt */
    RTC_ITConfig(RTC_IT_ALRA, ENABLE);
    RTC_ClearFlag(RTC_FLAG_ALRAF);

    /* Request to enter STANDBY mode (Wake Up flag is cleared in PWR_EnterSTANDBYMode function) */
    PWR_EnterSTANDBYMode(PWR_STANDBYEntry_WFI);

    /* Infinite loop */
    while (1)
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
