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



/* Private macro -------------------------------------------------------------*/
#include "variables.hpp"
#include "callback.hpp"
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

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
//    system_ms++;
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
//void CAN_IRQHandler(void)
//{
//    if (CAN_MessagePending(CAN_FIFO0) != 0)
//    {

//    }

//    if (CAN_MessagePending(CAN_FIFO1) != 0)
//    {

//    }
//}

/**
  * @brief  This function handles EXTI 6 request.
  * @param  None
  * @retval None
  */
void EXTI4_15_IRQHandler(void)
{
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
    /* Clear the EXTI line 13 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line0);
}




/**
  * @}
  */

#ifdef __cplusplus
}
#endif
