/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f0xxa_emacc.c
* @brief:     This file provides firmware functions to emacc
* @author:    AE Team
* @version:   V1.0.0/2023-10-08
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32f0xxa_emacc.h"
#include "hk32f0xxa_rcc.h"

static uint16_t MMItable[65] =
{
    32767, 32390, 32146, 31907, 31673, 31444, 31220, 31001, 30787, 30577, 30371,
    30169, 29971, 29777, 29587, 29400, 29217, 29037, 28861, 28687, 28517,
    28350, 28185, 28024, 27865, 27709, 27555, 27404, 27256, 27110, 26966,
    26824, 26685, 26548, 26413, 26280, 26149, 26019, 25892, 25767, 25643,
    25521, 25401, 25283, 25166, 25051, 24937, 24825, 24715, 24606, 24498,
    24392, 24287, 24183, 24081, 23980, 23880, 23782, 23684, 23588, 23493,
    23400, 23307, 23215, 23125
};

/** @addtogroup HK32F0xxA_StdPeriph_Driver
  * @{
  */

/** @defgroup EMACC EMACC
  * @brief EMACC driver modules
  * @{
  */


/** @defgroup EMACC_Private_Functions EMACC_Private_Functions
  * @{
  */

/**
  * @brief  De-initializes the EMACC peripheral registers to their default reset values
  * @retval None
  */
void EMACC_DeInit(void)
{
    /* Enable EMACC reset state */
    RCC_AHB2PeriphResetCmd(RCC_AHB2Periph_EMACC, ENABLE);
    /* Release EMACC from reset state */
    RCC_AHB2PeriphResetCmd(RCC_AHB2Periph_EMACC, DISABLE);
}

/**
  * @brief  Initializes the EMAC C peripheral according to the specified parameters
  *         in the EMACC_PI_InitTypeDef structure.
  * @param  EMACC_ID_InitStruct: pointer to a EMACC_PI_InitTypeDef structure that contains
  *         the configuration information for ID of the EMACC peripheral.
  * @param  EMACC_IQ_InitStruct : pointer to a EMACC_PI_InitTypeDef structure that contains
  *         the configuration information for IQ of  the EMACC peripheral.
  * @retval None
  */
void EMACC_Init(EMACC_PI_InitTypeDef* EMACC_ID_InitStruct, EMACC_PI_InitTypeDef* EMACC_IQ_InitStruct)
{
    uint32_t* Pdata = PID_RAM_BASE;
    //init PI Id
    EMACC->G1_KPKI = EMACC_ID_InitStruct->wKpiGain;
    EMACC->G1_INT_UPPERLMT = EMACC_ID_InitStruct->wUpperIntegralLimit;
    EMACC->G1_INT_LOWERLMT = EMACC_ID_InitStruct->wLowerIntegralLimit;
    EMACC->G1_OUT_LMT = (uint16_t)(EMACC_ID_InitStruct->hLowerOutputLimit) | ((uint16_t)(EMACC_ID_InitStruct->hUpperOutputLimit) << 16);
    EMACC->G1_DIVPOW2 = (uint16_t)(EMACC_ID_InitStruct->hKiDivisorPOW2) | ((uint16_t)(EMACC_ID_InitStruct->hKpDivisorPOW2) << 16);
    //init PI Iq
    EMACC->G2_KPKI = EMACC_IQ_InitStruct->wKpiGain;
    EMACC->G2_INT_UPPERLMT = EMACC_IQ_InitStruct->wUpperIntegralLimit;
    EMACC->G2_INT_LOWERLMT = EMACC_IQ_InitStruct->wLowerIntegralLimit;
    EMACC->G2_OUT_LMT = (uint16_t)(EMACC_IQ_InitStruct->hLowerOutputLimit) | ((uint16_t)(EMACC_IQ_InitStruct->hUpperOutputLimit) << 16);
    EMACC->G2_DIVPOW2 = (uint16_t)(EMACC_IQ_InitStruct->hKiDivisorPOW2) | ((uint16_t)(EMACC_IQ_InitStruct->hKpDivisorPOW2) << 16);
    //RAM WR ENABLE
    EMACC->CR |= EMACC_CR_RAMWREN | EMACC_CR_RAMRDEN;

    //init MMITABLE
    for (int16_t i = 0; i < 65 ; )
    {
        *Pdata = MMItable[i] | (uint32_t)(MMItable[i + 1] << 16);
        Pdata++;
        i = i + 2;
    }

    // init the Circle limitation
    EMACC->CIRCLE_LMT_VAL1 = (CIRCLELIM_TABLE_INDEX << 16) | CIRCLELIM_MAXMODULE;
    //RAM WR DISABLE
    EMACC->CR &= ~(EMACC_CR_RAMWREN | EMACC_CR_RAMRDEN);
}

/**
  * @brief  Enable or disable the EMACC peripheral.
  * @param  NewState: new state of the EMACC peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void EMACC_Cmd(FunctionalState NewState)
{
    /* Check the parameter */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the EMACC Peripheral */
        EMACC->CR |= (uint32_t) (EMACC_CR_EMEN | EMACC_CR_PIDEN | EMACC_CR_PARKEN | EMACC_CR_CLARKEEN | EMACC_CR_CORDICEN | EMACC_CR_RPARKEN);
    }
    else
    {
        /* Disable the EMACC peripheral */
        EMACC->CR &= (uint32_t)(~(EMACC_CR_EMEN | EMACC_CR_PIDEN | EMACC_CR_PARKEN | EMACC_CR_CLARKEEN | EMACC_CR_CORDICEN | EMACC_CR_RPARKEN));
    }
}

/**
  * @brief  Caculation
  * @param  hElAngle: Electric Angle
  * @param  Iab: the current of A & B axis
  * @param  Iqdref: the reference current of D & Q axis
  * @retval the Voltage of alpha and beta axis
  */
Volt_Components EMACC_Cal(int16_t hElAngle, Curr_Components Iab, Curr_Components Iqdref)
{
    __IO uint32_t CaleStatus = 0;
    Volt_Components Valphabeta;
    //input ref
    EMACC->G1_IDQ_REF = Iqdref.qI_Component2 << 16 | Iqdref.qI_Component1;
    EMACC->G2_IDQ_REF = Iqdref.qI_Component2 << 16 | Iqdref.qI_Component1;
    //input hElAngle
    EMACC->ANG_LDR = hElAngle;
    //input Iab
    EMACC->CLARKE_LDR = (uint16_t)(Iab.qI_Component2) | ((uint16_t)(Iab.qI_Component1) << 16) ;

    //wait result
    do
    {
        CaleStatus = EMACC->SR & EMACC_SR_RPARK_CF;
    } while (CaleStatus == 0);

    Valphabeta.qV_Component1 = (EMACC->RevPARK_OUT >> 16) & 0xFFFF;
    Valphabeta.qV_Component2 = EMACC->RevPARK_OUT & 0xFFFF;
    //clear status
    EMACC->CLRSR |= EMACC_CLEAR_STATUS_MASK;
    return Valphabeta;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

