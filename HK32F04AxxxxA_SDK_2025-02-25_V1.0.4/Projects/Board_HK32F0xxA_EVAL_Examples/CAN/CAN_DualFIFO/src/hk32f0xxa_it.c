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

/** @addtogroup CAN_DualFIFO_Example
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MESSAGE1   "FIFO0 : Msg received"
#define MESSAGE2   "FIFO1 : Msg received"

#define T_MESSAGE1   "MSG0 : transmited"
#define T_MESSAGE2   "MSG1 : transmited"


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
CanRxMsg RxMessage, RxMessage1;
extern uint8_t KeyNumber;
extern CanTxMsg TxMessage, TxMessage1;

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
    if (CAN_MessagePending(CAN_FIFO0) != 0)
    {
        CAN_Receive(CAN_FIFO0, &RxMessage);
        LED_Display(RxMessage.Data[0]);
        KeyNumber = RxMessage.Data[0];
        printf("\r\n %s \r\n", MESSAGE1);
    }

    if (CAN_MessagePending(CAN_FIFO1) != 0)
    {
        CAN_Receive(CAN_FIFO1, &RxMessage1);
        LED_Display(RxMessage1.Data[0]);
        KeyNumber = RxMessage1.Data[0];
        printf("\r\n %s \r\n", MESSAGE2);
    }
}

/**
  * @brief  This function handles EXTI 6 request.
  * @param  None
  * @retval None
  */
void EXTI4_15_IRQHandler(void)
{
    if (KeyNumber < 0x2)
    {
        KeyNumber = 0x05;
    }

    LED_Display(--KeyNumber);
    TxMessage.Data[0] = KeyNumber;
    CAN_Transmit(&TxMessage);
    printf("\r\n %s \r\n", T_MESSAGE1);
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
    if (KeyNumber == 0x4)
    {
        KeyNumber = 0x00;
    }

    LED_Display(++KeyNumber);
    TxMessage1.Data[0] = KeyNumber;
    CAN_Transmit(&TxMessage1);
    printf("\r\n %s \r\n", T_MESSAGE2);

    /* Clear the EXTI line 13 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line0);
}


/**
  * @}
  */

/**
  * @}
  */

