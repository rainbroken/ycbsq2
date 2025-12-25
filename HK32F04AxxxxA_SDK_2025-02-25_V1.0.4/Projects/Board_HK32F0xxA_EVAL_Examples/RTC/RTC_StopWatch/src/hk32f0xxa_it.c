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
#include "main.h"

/** @addtogroup HK32F0xxA_StdPeriph_Examples
  * @{
  */

/** @addtogroup RTC_StopWatch_Example
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint8_t Button_State;
extern __IO uint8_t Button_RTC;
extern __IO uint8_t StartEvent;
extern uint32_t BackupIndex;
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
  * @brief  This function handles External lines 15 to 4 interrupt request.
  * @retval None
  */
void EXTI4_15_IRQHandler(void)
{
    if ((EXTI_GetITStatus(LEFT_BUTTON_EXTI_LINE) != RESET) && (StartEvent == 0x0))
    {
        Button_State = LEFT_ON;
    }
    else if ((EXTI_GetITStatus(RIGHT_BUTTON_EXTI_LINE) != RESET) && (StartEvent != 0x0) && (BackupIndex < 11))
    {
        Button_State = RIGHT_ON;
    }

    /* Clear the LEFT EXTI  pending bit */
    EXTI_ClearITPendingBit(LEFT_BUTTON_EXTI_LINE);

    /* Clear the RIGHT EXTI line */
    EXTI_ClearITPendingBit(RIGHT_BUTTON_EXTI_LINE);
}

/**
  * @brief  This function handles Tamper pin interrupt request.
  * @param  None
  * @retval None
  */
void RTC_IRQHandler(void)
{
    if (RTC_GetITStatus(RTC_IT_TAMP1) != RESET)
    {
        Button_RTC = RTC_TAMP;
    }

    /* Clear the EXTIL line 19 */
    EXTI_ClearITPendingBit(EXTI_Line19);

    /* Clear Tamper pin interrupt pending bit */
    RTC_ClearITPendingBit(RTC_IT_TAMP1);
}


/**
  * @}
  */

/**
  * @}
  */

