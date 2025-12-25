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

/** @addtogroup USART_MultiProcessor
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
  * @brief  This function handles External interrupt Line 4-15 request.
  * @param  None
  * @retval None
  */
void EXTI4_15_IRQHandler(void)
{
    /* wakeup line */
    if (EXTI_GetITStatus(UP_BUTTON_EXTI_LINE) != RESET)
    {
        /* Send the address mark (0x102) to wakeup USARTy USARTy ADDR is 0x02,
        MSB = 1 to be recognized as an address, otherwise it is data */
        USART_SendData(USARTx, 0x102);

        /* Wait while USARTx TXE = 0 */
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
        {
        }

        debug("USARTx Send the address mark to wakeup USARTy!");

        /* Clear the IT Bit */
        EXTI_ClearITPendingBit(UP_BUTTON_EXTI_LINE);
    }

    /* mute line */
    if (EXTI_GetITStatus(DOWN_BUTTON_EXTI_LINE) != RESET)
    {
        /* Flush DR register and clear the USARTy RXNE flag */
        USART_ReceiveData(USARTy);

        /* Send the other address mark to make USARTy(0x02) enter mute mode*/
        USART_SendData(USARTx, 0x103);

        /* Wait while USARTx TXE = 0 */
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
        {
        }

        debug("USARTy enter Mute mode!");

        /* Clear Key Button EXTI Line Pending Bit */
        EXTI_ClearITPendingBit(DOWN_BUTTON_EXTI_LINE);
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

