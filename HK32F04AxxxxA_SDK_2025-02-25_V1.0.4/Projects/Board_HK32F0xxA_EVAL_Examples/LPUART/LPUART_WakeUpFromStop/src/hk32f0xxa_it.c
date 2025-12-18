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

/** @addtogroup LPUART_WakeUpFromStop
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint8_t Counter = 0;
__IO uint8_t InterruptCounter = 0x00;

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
    if (Counter == 20)
    {
        /* Toggle LED's */
        HK_EVAL_LEDToggle(LED1);
        HK_EVAL_LEDToggle(LED2);
        HK_EVAL_LEDToggle(LED3);
        HK_EVAL_LEDToggle(LED4);

        /* Reset Counter */
        Counter = 0;
    }
    else
    {
        /* increment Counter */
        Counter++;
    }
}


/******************************************************************************/
/*                 HK32F0xxA Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/******************************************************************************/

/**
  * @brief  This function handles LPUART interrupt request.
  * @param  None
  * @retval None
  */
void LPUARTx_IRQHandler(void)
{
    if (LPUART_GetITStatus(LPUART1, LPUART_IT_WU) == SET)
    {
        /* Clear The LPUART WU flag */
        LPUART_ClearITPendingBit(LPUART1, LPUART_IT_WU);
        InterruptCounter = 0x01;
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

