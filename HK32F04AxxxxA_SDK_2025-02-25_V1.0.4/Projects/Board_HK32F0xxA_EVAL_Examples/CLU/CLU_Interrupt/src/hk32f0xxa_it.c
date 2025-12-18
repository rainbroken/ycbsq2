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

extern void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);


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
  * @brief  This function handles CLU0 Handler.
  *         @Note   CLU0 is combined with the TIMER14 to NVIC.
  * @param  None
  * @retval None
  */
void TIM14_IRQHandler(void)
{
    if (EXTI2_GetITStatus(EXTI2_Line0) != RESET)
    {
        EXTI2_ClearITPendingBit(EXTI2_Line0);
        GPIO_TogglePin(GPIOB, GPIO_Pin_2);
    }
}


/**
  * @brief  This function handles CLU1 Handler.
  *         @Note   CLU1 is combined with the TIMER16 to NVIC.
  * @param  None
  * @retval None
  */
void TIM16_IRQHandler(void)
{
    if (EXTI2_GetITStatus(EXTI2_Line1) != RESET)
    {
        EXTI2_ClearITPendingBit(EXTI2_Line1);
        GPIO_TogglePin(GPIOB, GPIO_Pin_2);
    }
}

/**
  * @brief  This function handles CLU2 Handler.
  *         @Note   CLU2 is combined with the SPI1 to NVIC.
  * @param  None
  * @retval None
  */
void SPI1_IRQHandler(void)
{
    if (EXTI2_GetITStatus(EXTI2_Line2) != RESET)
    {
        GPIO_TogglePin(GPIOB, GPIO_Pin_2);
        EXTI2_ClearITPendingBit(EXTI2_Line2);
    }
}

/**
  * @brief  This function handles CLU3 Handler.
  *         @Note   CLU3 is combined with the SPI2 to NVIC.
  * @param  None
  * @retval None
  */
void SPI2_IRQHandler(void)
{
    if (EXTI2_GetITStatus(EXTI2_Line3) != RESET)
    {
        GPIO_TogglePin(GPIOB, GPIO_Pin_2);
        EXTI2_ClearITPendingBit(EXTI2_Line3);
    }
}

/**
  * @}
  */

/**
  * @}
  */

