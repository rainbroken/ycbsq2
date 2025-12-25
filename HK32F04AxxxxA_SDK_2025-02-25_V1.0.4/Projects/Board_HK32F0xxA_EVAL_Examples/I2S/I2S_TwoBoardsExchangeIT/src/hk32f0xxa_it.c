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

/** @addtogroup I2S_TwoBoardsExchangeIT
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern const uint16_t I2S_Buffer_Tx[32];
extern __IO uint16_t TxIdx, RxIdx;
extern uint16_t I2S_Buffer_Rx[32];

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
  * @brief  This function handles SPI1 global interrupt request
  * @param  None
  * @retval : None
  */
void SPI1_IRQHandler(void)
{
    uint32_t tmpreg = 0x00;
    tmpreg = SPI1->SR;
#if defined (I2S_SLAVE_RECEIVER)

    if ((tmpreg & 0x01) == 0x01)
    {
        I2S_Buffer_Rx[RxIdx++] = SPI_I2SReceiveData16(SPI1);

        /* Disable the Interrupt when transfer is complete */
        if (RxIdx == 32)
        {
            /* Disable the I2S1 RXNE Interrupt */
            SPI_I2SITConfig(SPI1, SPI_I2S_IT_RXNE, DISABLE);
        }
    }

#elif defined (I2S_MASTER_TRANSMITTER)

    if ((tmpreg & 0x02) == 0x02)
    {
        SPI_I2SSendData16(SPI1, I2S_Buffer_Tx[TxIdx++]);

        if (TxIdx == 32)
        {
            /* Disable the I2S1 TXE Interrupt */
            SPI_I2SITConfig(SPI1, SPI_I2S_IT_TXE, DISABLE);
        }
    }

#endif
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


