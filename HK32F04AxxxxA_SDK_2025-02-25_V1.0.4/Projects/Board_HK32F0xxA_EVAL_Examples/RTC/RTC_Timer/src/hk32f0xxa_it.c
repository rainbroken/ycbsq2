/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f0xxa_it.c
* @brief:     Interrupt Service Routines
* @author:    AE Team
* @version:   V1.0.0/2023-10-10
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32f0xxa_it.h"

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
extern __IO uint8_t ALARM_Occured;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @retval None
  */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles SVCall exception.
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 HK32F0xxA Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_hk32f0xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles External line 0 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_1_IRQHandler(void)
{
    if (EXTI_GetITStatus(SEL_BUTTON_EXTI_LINE) != RESET)
    {
        /* Enable the RTC Clock */
        RCC_RTCCLKCmd(ENABLE);

        /* Turn LED1 ON */
        HK_EVAL_LEDOn(LED1);

        /* Wait for RTC APB registers synchronisation */
        RTC_WaitForSynchro();

        /* Enable the alarmA */
        RTC_AlarmCmd(RTC_Alarm_A, ENABLE);

        /* Clear the SEL Button EXTI line pending bit */
        EXTI_ClearITPendingBit(SEL_BUTTON_EXTI_LINE);
    }
}

/**
  * @brief  This function handles External lines 9 to 5 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI4_15_IRQHandler(void)
{
    if (EXTI_GetITStatus(TAMPER_BUTTON_EXTI_LINE) != RESET)
    {
        /* Disable the RTC Clock */
        RCC_RTCCLKCmd(DISABLE);

        /* Wait for RTC APB registers synchronisation */
        RTC_WaitForSynchro();

        /* Clear the Key Button EXTI line pending bit */
        EXTI_ClearITPendingBit(TAMPER_BUTTON_EXTI_LINE);
    }
}

/**
  * @brief  This function handles RTC interrupt request.
  * @param  None
  * @retval None
  */
void RTC_IRQHandler(void)
{
    /* Check on the AlarmA flag and on the number of interrupts per Second (60*8) */
    if (RTC_GetITStatus(RTC_IT_ALRA) != RESET)
    {
        /* ALARM is enabled */
        ALARM_Occured = 1;
        RTC_ClearITPendingBit(RTC_IT_ALRA);
        EXTI_ClearITPendingBit(EXTI_Line17);
        HK_EVAL_LEDToggle(LED2);
    }
}


/**
  * @}
  */

/**
  * @}
  */

