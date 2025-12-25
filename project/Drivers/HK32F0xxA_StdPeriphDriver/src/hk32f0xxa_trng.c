/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f0xxa_trng.c
* @brief:     True RNG module driver
* @author:    AE Team
* @version:   V1.0.0/2023-10-10
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32f0xxa_trng.h"
#include "hk32f0xxa_rcc.h"

/** @addtogroup HK32F0xxA_StdPeriph_Driver
  * @{
  */

/** @defgroup RNG RNG
  * @brief RNG driver modules
  * @{
  */

/** @defgroup RNG_Private_Defines RNG_Private_Defines
  * @{
  */

#define RNG_TIMEOUT_VALUE             ((uint32_t)0x00010000)
#define RNG_CR_CLEAR_MASK             ((uint32_t)0x0000000C)
/**
  * @}
  */


/** @defgroup RNG_Private_Functions RNG_Private_Functions
  * @{
  */

/**
  * @brief  Initializes the RNG peripheral and creates the associated handle.
  * @param  RNG_InitStruct pointer to a RNG_InitTypeDef structure that contains
  *         the configuration information for RNG.
  * @retval None
  */
void RNG_Init(RNG_InitTypeDef *RNG_InitStruct)
{
    uint32_t tmpreg = 0;
    /* Get RNG CR register value */
    tmpreg = RNG->CR;
    /* Clear OP_CYCLE[15:9] bits and work mode MODE[0] */
    tmpreg &= (uint32_t)RNG_CR_CLEAR_MASK;
    /* Set RNG accumulation clock period and work mode */
    tmpreg |= ((RNG_InitStruct->Option_Cycle << 1) | RNG_InitStruct->Mode);
    RNG->CR = (uint32_t)tmpreg;
}

/**
  * @brief  Deinitializes RNG peripheral registers to their default reset values.
  * @retval None
  */
void RNG_DeInit(void)
{
    /* Enable RNG reset state */
    RCC_AHB2PeriphResetCmd(RCC_AHB2Periph_TRNG, ENABLE);
    /* Release RNG from reset state */
    RCC_AHB2PeriphResetCmd(RCC_AHB2Periph_TRNG, DISABLE);
}

/**
  * @brief  Enable or disable the RNG peripheral.
  * @param  NewState: new state of the RNG peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RNG_Cmd(FunctionalState NewState)
{
    /* Check the parameter */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the RNG Peripheral */
        RNG->CR |= (uint32_t)RNG_CR_RNGEN;
    }
    else
    {
        /* Disable the RNG peripheral */
        RNG->CR &= (uint32_t)(~RNG_CR_RNGEN);  /**< RNG Disable */
    }
}

/*
@verbatim
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Get the 32 bit Random number
      (+) Get the 32 bit Random number with interrupt enabled
      (+) Handle RNG interrupt request

@endverbatim
  * @{
  */

/**
  * @brief  Generates a 32-bit random number.
  * @note   Each time the random number data is read the RNG_FLAG_DRDY flag
  *         is automatically cleared.
  * @param  random32bit pointer to generated random number variable if successful.
  * @retval FlagStatus (SET or SUCCESS)
  */
ErrorStatus RNG_GetRandomNumber(uint32_t *random32bit)
{
    uint32_t RandomNumber = 0;
    __IO uint32_t counter ;
    FlagStatus  ccstatus = RESET;
    ErrorStatus status = SUCCESS;
    /* Wait for DRDY flag to be set */
    counter = 0;

    do
    {
        ccstatus = RNG_GetFlagStatus(RNG_FLAG_DRDY);
        counter++;
    } while ((counter != RNG_TIMEOUT_VALUE) && (ccstatus == RESET));

    if (ccstatus == RESET)
    {
        status = ERROR;
    }
    else
    {
        /* Get a 32bit Random number */
        RandomNumber = RNG->DR;
        *random32bit = RandomNumber;
    }

    return status;
}


/**
  * @brief  Returns a 32-bit random number with interrupt enabled
  * @retval 32-bit random number
  */
uint32_t RNG_GetRandomNumberIT(void)
{
    uint32_t random32bit = 0U;
    /* Get a 32bit Random number */
    random32bit = RNG->DR;
    /* Return the 32 bit random number */
    return random32bit;
}


/**
  * @brief  Enables or disables the specified RNG interrupt.
  * @param  NewState: The new state of the RNG interrupt source.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RNG_ITConfig(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RNG->CR |= (uint32_t) RNG_IT_IE;    /**< RNG_IT Enable */
    }
    else
    {
        RNG->CR &= (uint32_t)(~RNG_IT_IE);  /**< RNG_IT Disable */
    }
}

/**
  * @brief  Checks whether the specified RNG flag is set or not.
  * @param  RNG_FLAG specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg RNG_FLAG_DRDY: Data ready
  *            @arg RNG_FLAG_SECS: Seed error current status
  * @retval FlagStatus (SET or RESET)
  */
FlagStatus RNG_GetFlagStatus(uint32_t RNG_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check parameters */
    assert_param(IS_RNG_FLAG(RNG_FLAG));

    if ((RNG->SR & RNG_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    /* Return the RNG_FLAG status */
    return  bitstatus;
}


/**
  * @brief  Checks whether the specified RNG interrupt has occurred or not.
  * @param  RNG_IT: Specifies the RNG interrupt pending bit to check.
  *         This parameter can be:
  *            @arg RNG_IT_DRDY: Data ready interrupt
  *            @arg RNG_IT_SEI: Seed error interrupt
  * @retval ITStatus The new state of RNG_IT (SET or RESET).
  */
ITStatus RNG_GetITStatus(uint32_t RNG_IT)
{
    ITStatus itstatus = RESET;
    uint32_t cciebitstatus = RESET;
    /* Check parameters */
    assert_param(IS_RNG_GET_IT(RNG_IT));
    cciebitstatus = RNG->CR & RNG_CR_IE;

    if (cciebitstatus != (uint16_t)RESET)
    {
        /* Check the status of the specified RNG interrupt */
        if ((RNG->SR & RNG_IT) != RESET)
        {
            /* Check if WRERR or RDERR flags are set */
            if ((RNG->SR & (uint32_t)(RNG_IT_DRDY | RNG_IT_SEI)) != (uint16_t)RESET)
            {
                /* Interrupt occurred */
                itstatus = SET;
            }
            else
            {
                /* Interrupt didn't occur */
                itstatus = RESET;
            }
        }
        else
        {
            /* Interrupt didn't occur */
            itstatus = (ITStatus) RESET;
        }
    }

    /* Return the RNG_IT status */
    return itstatus;
}

/**
  * @brief  Clears the RNG's interrupt pending bits.
  * @param  RNG_IT: specifies the interrupt pending bit to clear.
  *         This parameter can be any combinations of the following values:
  *            @arg RNG_IT_SEI: Seed error interrupt
  * @retval None
  */
void RNG_ClearITPendingBit(uint32_t RNG_IT)
{
    /* Check the parameters */
    assert_param(IS_RNG_IT(RNG_IT));
    /* Clear the interrupt pending bit */
    RNG->SR &= (uint32_t) (~RNG_IT);
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
