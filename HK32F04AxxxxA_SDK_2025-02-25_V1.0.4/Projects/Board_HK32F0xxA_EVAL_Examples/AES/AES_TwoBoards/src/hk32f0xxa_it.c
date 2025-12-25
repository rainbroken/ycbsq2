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

/** @addtogroup DMA_FLASHRAMTransfer
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
  * @brief  This function handles usart2 Handler.
  * @param  None
  * @retval None
  */

#ifdef AES_BoardA
    /* Data received by board A */
    extern  uint8_t BoardA_RxBuffer[AES_TEXT_SIZE];
#else
    /* Data received by board B */
    extern  uint8_t BoardB_RxBuffer[AES_TEXT_SIZE];
#endif

extern  uint8_t RxIndex  ;
extern  uint8_t RxDone  ;

/**
  * @brief  This function handles USART2 Handler.
  * @retval None
  */
void USART2_IRQHandler(void)
{
    static uint8_t Rxindextemp = 0;

    if (USART_GetFlagStatus(USART2, USART_FLAG_ORE))
    {
        USART_ClearFlag(USART2, USART_FLAG_ORE);
    }

    if (USART_GetITStatus(USART2, USART_IT_RXNE))
    {
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
#ifdef AES_BoardA
        BoardA_RxBuffer[RxIndex++] = USART_ReceiveData(USART2);
#else
        BoardB_RxBuffer[RxIndex++] = USART_ReceiveData(USART2);
#endif

        if (RxIndex == AES_TEXT_SIZE)
        {
            Rxindextemp = 1;
        }
        else
        {
            Rxindextemp = 0;
        }

        RxIndex %= AES_TEXT_SIZE;
    }

    if (USART_GetITStatus(USART2, USART_IT_IDLE))
    {
        USART_ClearITPendingBit(USART2, USART_IT_IDLE);

        if (Rxindextemp)
        {
            RxDone = 1;
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

