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

/** @addtogroup USART_TwoBoardsExchangeIT
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint8_t Counter = 0x00;
extern __IO uint32_t TimeOut;

extern uint8_t TxBuffer[];
extern uint8_t RxBuffer[];
extern uint8_t CmdBuffer[];
extern uint8_t AckBuffer[];
extern __IO uint8_t RxIndex;
extern __IO uint8_t TxIndex;

extern __IO uint8_t UsartTransactionType;
extern __IO uint8_t UsartMode;

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
    /* Decrement the timeout value */
    if (TimeOut != 0x0)
    {
        TimeOut--;
    }

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
    /* USART in mode Transmitter -------------------------------------------------*/
    if (USART_GetITStatus(USARTx, USART_IT_TXE) == SET)
    {
        /* When Joystick Pressed send the command then send the data */
        if (UsartMode == USART_MODE_TRANSMITTER)
        {
            /* Send the command */
            if (UsartTransactionType == USART_TRANSACTIONTYPE_CMD)
            {
                USART_SendData(USARTx, CmdBuffer[TxIndex++]);

                if (TxIndex == 0x02)
                {
                    /* Disable the USARTx transmit data register empty interrupt */
                    USART_ITConfig(USARTx, USART_IT_TXE, DISABLE);
                }
            }

            /* Send the data */
            else
            {
                USART_SendData(USARTx, TxBuffer[TxIndex++]);

                if (TxIndex == CmdBuffer[0x01])
                {
                    /* Disable the USARTx transmit data register empty interrupt */
                    USART_ITConfig(USARTx, USART_IT_TXE, DISABLE);
                }
            }
        }
        /*If Data Received send the ACK*/
        else
        {
            USART_SendData(USARTx, AckBuffer[TxIndex++]);

            if (TxIndex == 0x02)
            {
                /* Disable the USARTx transmit data register empty interrupt */
                USART_ITConfig(USARTx, USART_IT_TXE, DISABLE);
            }
        }
    }

    /* USART in mode Receiver --------------------------------------------------*/
    if (USART_GetITStatus(USARTx, USART_IT_RXNE) == SET)
    {
        if (UsartMode == USART_MODE_TRANSMITTER)
        {
            AckBuffer[RxIndex++] = USART_ReceiveData(USARTx);
        }
        else
        {
            /* Receive the command */
            if (UsartTransactionType == USART_TRANSACTIONTYPE_CMD)
            {
                CmdBuffer[RxIndex++] = USART_ReceiveData(USARTx);
            }

            /* Receive the USART data */
            else
            {
                RxBuffer[RxIndex++] = USART_ReceiveData(USARTx);
            }


        }


    }

}

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

