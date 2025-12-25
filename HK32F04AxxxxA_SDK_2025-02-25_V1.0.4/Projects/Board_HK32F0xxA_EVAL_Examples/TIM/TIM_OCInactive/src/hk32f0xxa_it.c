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

/** @addtogroup TIM_OCInactive
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
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
  * @brief  This function handles TIM2 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
    {
        /* Clear TIM2 Capture Compare1 interrupt pending bit*/
        TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);

        /* PA.00 turnoff after 1000 ms */
        GPIO_ResetBits(GPIOA, GPIO_Pin_0);
    }
    else if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)
    {
        /* Clear TIM2 Capture Compare2 interrupt pending bit*/
        TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);

        /* PA.01 turnoff after 500 ms */
        GPIO_ResetBits(GPIOA, GPIO_Pin_1);
    }
    else if (TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET)
    {
        /* Clear TIM2 Capture Compare3 interrupt pending bit*/
        TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);

        /* PA.02 turnoff after 250 ms */
        GPIO_ResetBits(GPIOA, GPIO_Pin_2);
    }
    else
    {
        /* Clear TIM2 Capture Compare4 interrupt pending bit*/
        TIM_ClearITPendingBit(TIM2, TIM_IT_CC4);

        /* PA.03 turnoff after 125 ms */
        GPIO_ResetBits(GPIOA, GPIO_Pin_3);
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


