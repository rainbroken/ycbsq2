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

/** @addtogroup CAN_Networking_Example
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
CanRxMsg RxMessage = {0};
__IO uint8_t KeyPressed = 0;

extern uint8_t KeyNumber;

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
  * @brief  This function handles CAN request.
  * @retval None
  */
void CAN_IRQHandler(void)
{
    if (CAN_GetITStatus(CAN_IT_FMP0) != RESET)
    {
        /* Clears the CAN1 interrupt pending bit */
        CAN_ClearITPendingBit(CAN_IT_FF0);
        CAN_Receive(CAN_FIFO0, &RxMessage);

        if ((RxMessage.StdId == 0x321) && (RxMessage.IDE == CAN_ID_STD) && (RxMessage.DLC == 1))
        {
            LED_Display(RxMessage.Data[0]);
            KeyNumber = RxMessage.Data[0];
        }
    }
}

/**
  * @brief  This function handles EXTI 6 request.
  * @param  None
  * @retval None
  */
void EXTI4_15_IRQHandler(void)
{
    /* Set KeyPressed flag */
    KeyPressed = 1;

    /* Clear the EXTI line 6 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line13);
}

/**
  * @brief  This function handles EXTI 10 to 15 request.
  * @param  None
  * @retval None
  */
void EXTI0_1_IRQHandler(void)
{
}


/**
  * @}
  */

/**
  * @}
  */

