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

/** @addtogroup RTC_TimerStamp_Example
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint8_t Button_State;
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

#if 0
/**
  * @brief  This function handles External line 0 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_1_IRQHandler(void)
{
    /* Clear the TimeStamp registers */
    if (EXTI_GetITStatus(SEL_BUTTON_EXTI_LINE) != RESET)
    {
        Button_State = SEL_ON;

        /* Clear the Wakeup Button EXTI line pending bit */
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
    /* TimeStamp Event detected */
    if (EXTI_GetITStatus(TAMPER_BUTTON_EXTI_LINE) != RESET)
    {
        Button_State = TAMPER_ON;

        /* Clear the TAMPER Button EXTI line pending bit */
        EXTI_ClearITPendingBit(TAMPER_BUTTON_EXTI_LINE);

        /* Clear TSF&TSOVF flag */
        //RTC_ClearITPendingBit((RTC_IT_TS | RTC_IT_TSOV));
    }
}
#endif
/**
  * @brief  This function handles RTC interrupt request.
  * @param  None
  * @retval None
  */
void RTC_IRQHandler(void)
{
    if (RTC_GetFlagStatus(RTC_FLAG_TSF) != RESET)
    {
        Button_State = TAMPER_ON;

        /* Clear the TAMPER Button EXTI line pending bit */
        EXTI_ClearITPendingBit(TAMPER_BUTTON_EXTI_LINE);

        /* Clear TSF&TSOVF flag */
#if 0
        RTC_ClearFlag((RTC_FLAG_TSF | RTC_FLAG_TSOVF));
        RTC_ClearFlag(RTC_FLAG_TSF);
#endif
    }

    /* Clear the EXTIL line 19 */
    EXTI_ClearITPendingBit(EXTI_Line19);
}


/**
  * @}
  */

/**
  * @}
  */

