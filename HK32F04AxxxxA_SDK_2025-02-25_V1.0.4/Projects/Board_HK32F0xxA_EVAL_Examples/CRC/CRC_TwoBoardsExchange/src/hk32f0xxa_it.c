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

/** @addtogroup CRC_TwoBoardsExchange
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint8_t Rxbuffer[];
extern __IO uint8_t RxIndex;
extern __IO JOYState_TypeDef PressedButton;
__IO uint8_t Counter = 0x00;

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
    if (Counter < 10)
    {
        Counter++;
    }
    else
    {
        Counter = 0x00;
        HK_EVAL_LEDToggle(LED1);
    }
}

/******************************************************************************/
/*            HK32F0xx Peripherals Interrupt Handlers                        */
/******************************************************************************/
/**
  * @brief  This function handles USART interrupt request.
  * @retval None
  */
void USARTx_IRQHandler(void)
{
    /*  */
    if (USART_GetITStatus(USARTx, USART_IT_TXE) == SET)
    {

    }

#ifdef MODE_TRANSMITTER

#else

    /*  */
    if (USART_GetITStatus(USARTx, USART_IT_RXNE) == SET)
    {
        /* Receive the USART data */
        Rxbuffer[RxIndex++] = USART_ReceiveData(USARTx);
    }

#endif

}

#ifdef MODE_TRANSMITTER
/**
  * @brief  This function handles External lines 0 to 1 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_1_IRQHandler(void)
{
    /* To detect user action on JOY_SEL button */
    if (EXTI_GetITStatus(SEL_BUTTON_EXTI_LINE) != RESET)
    {
        PressedButton = JOY_SEL;

        /* Clear the SEL Button EXTI line pending bit */
        EXTI_ClearITPendingBit(SEL_BUTTON_EXTI_LINE);
    }
}
#endif /* MODE_TRANSMITTER */

/******************************************************************************/
/*                 HK32F0xxA Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_hk32f0xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
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

