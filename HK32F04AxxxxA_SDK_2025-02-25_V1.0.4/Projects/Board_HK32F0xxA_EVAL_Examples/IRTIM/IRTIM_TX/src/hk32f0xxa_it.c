/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f0xxa_it.c
* @brief:     Interrupt Service Routines
* @author:    AE Team
* @version:   V1.0.0/2023-10-08
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32f0xxa_it.h"

/** @addtogroup HK32F0xxA_StdPeriph_Examples
  * @{
  */

/** @addtogroup IRTIM_TX
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern volatile unsigned char g_IRSendFlag;
extern volatile unsigned int g_IRTIM_count;

extern volatile unsigned char g_ButtonFlag;

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
  * @param  None
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
  * @brief  This function handles EXTI interrupt request.
  * @param  None
  * @retval None
  */
void EXTI4_15_IRQHandler(void)
{
    if (EXTI_GetITStatus(KEY_BUTTON_EXTI_LINE) != RESET)
    {
        EXTI_ClearITPendingBit(KEY_BUTTON_EXTI_LINE);

        g_ButtonFlag = 1;
    }
}

/**
  * @brief  This function handles TIM16 interrupt request.
  * @param  None
  * @retval None
  */
void TIM16_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM16, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM16, TIM_IT_Update);

        g_IRTIM_count++;

        if (g_IRSendFlag == 1)
        {
            TIM16->CCR1 = ENVELOPE_TIM_PERIOD;
        }
        else
        {
            TIM16->CCR1 = (uint16_t)(0);
        }
    }
}

/**
  * @brief  This function handles PPP interrupt request.
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */


