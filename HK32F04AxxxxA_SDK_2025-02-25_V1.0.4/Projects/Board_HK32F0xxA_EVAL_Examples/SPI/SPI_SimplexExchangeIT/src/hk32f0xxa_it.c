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

/** @addtogroup SPI_SimplexExchangeIT
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint8_t TxIdx, RxIdx;
extern uint8_t SPI_MASTER_Buffer_Tx[BufferSize], SPI_SLAVE_Buffer_Rx[BufferSize];

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
  * @param  None
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
  * @brief  This function handles SPI2 global interrupt request.
  * @param  None
  * @retval None
  */
void SPIxx_IRQHandler(void)
{
    if (SPI_I2SGetITStatus(SPIxx, SPI_I2S_IT_TXE) != RESET)
    {
        /* Send SPI_MASTER data */
        SPI_SendData8(SPIxx, SPI_MASTER_Buffer_Tx[TxIdx++]);

        /* Disable SPI_MASTER TXE interrupt */
        if (TxIdx >= BufferSize)
        {
            SPI_I2SITConfig(SPIxx, SPI_I2S_IT_TXE, DISABLE);
        }
    }
}

/**
  * @brief  This function handles SPI1 global interrupt request.
  * @param  None
  * @retval None
  */
void SPIx_IRQHandler(void)
{
    if (SPI_I2SGetITStatus(SPIx, SPI_I2S_IT_RXNE) != RESET)
    {
        /* Store SPI_SLAVE received data */
        SPI_SLAVE_Buffer_Rx[RxIdx++] = SPI_ReceiveData8(SPIx);
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


