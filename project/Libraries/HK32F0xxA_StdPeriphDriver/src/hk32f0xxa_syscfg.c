/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f0xxa_syscfg.c
* @brief:     This file provides firmware functions to syscfg
* @author:    AE Team
* @version:   V1.0.0/2023-10-08
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32f0xxa_syscfg.h"

/** @addtogroup HK32F0xxA_StdPeriph_Driver
  * @{
  */

/** @defgroup SYSCFG SYSCFG
  * @brief SYSCFG driver modules
  * @{
  */

/**
 ===============================================================================
                     ##### How to use this driver #####
 ===============================================================================
    [..]
               The SYSCFG registers can be accessed only when the SYSCFG
               interface APB clock is enabled.
               To enable SYSCFG APB clock use:
               RCC_APBPeriphClockCmd(RCC_APBPeriph_SYSCFG, ENABLE).

  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup SYSCFG_Private_Functions SYSCFG_Private_Functions
  * @{
  */

/** @defgroup SYSCFG_Group1 SYSCFG Initialization and Configuration functions
 *  @brief   SYSCFG Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
        ##### SYSCFG Initialization and Configuration functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the SYSCFG registers to their default reset values.
  * @retval None
  * @note   MEM_MODE bits are not affected by APB reset.
  * @note   MEM_MODE bits took the value from the user option bytes.
  * @note   CFGR2 register is not affected by APB reset.
  * @note   CLABBB configuration bits are locked when set.
  * @note   To unlock the configuration, perform a system reset.
  */
void SYSCFG_DeInit(void)
{
    /* Set SYSCFG_CFGR1 register to reset value without affecting MEM_MODE bits */
    SYSCFG->CFGR1 &= SYSCFG_CFGR1_MEM_MODE;
    /* Set EXTICRx registers to reset value */
    SYSCFG->EXTICR1 = 0;
    SYSCFG->EXTICR2 = 0;
    SYSCFG->EXTICR3 = 0;
    SYSCFG->EXTICR4 = 0;
    /* Set CFGR2 register to reset value: clear SRAM parity error flag */
    SYSCFG->CFGR2 |= (uint32_t) SYSCFG_CFGR2_SRAM_PEF;
}

/**
  * @brief  Configures the memory mapping at address 0x00000000.
  * @param  SYSCFG_MemoryRemap: selects the memory remapping.
  *         This parameter can be one of the following values:
  *            @arg SYSCFG_MemoryRemap_Flash: Main Flash memory mapped at 0x00000000
  *            @arg SYSCFG_MemoryRemap_SystemMemory: System Flash memory mapped at 0x00000000
  *            @arg SYSCFG_MemoryRemap_SRAM: Embedded SRAM mapped at 0x00000000
  * @retval None
  */
void SYSCFG_MemoryRemapConfig(uint32_t SYSCFG_MemoryRemap)
{
    uint32_t tmpctrl = 0;
    /* Check the parameter */
    assert_param(IS_SYSCFG_MEMORY_REMAP(SYSCFG_MemoryRemap));
    /* Get CFGR1 register value */
    tmpctrl = SYSCFG->CFGR1;
    /* Clear MEM_MODE bits */
    tmpctrl &= (uint32_t) (~SYSCFG_CFGR1_MEM_MODE);
    /* Set the new MEM_MODE bits value */
    tmpctrl |= (uint32_t) SYSCFG_MemoryRemap;
    /* Set CFGR1 register with the new memory remap configuration */
    SYSCFG->CFGR1 = tmpctrl;
}

/**
  * @brief  Configures the reference voltage selection.
  * @param  SYSCFG_VREF_SEL: This parameter can be :
  *            @arg SYSCFG_Vref_Sel_VDDH: The reference voltage is VDDH
  *            @arg SYSCFG_Vref_Sel_VREF12: SYSCFG_Vref_Sel_VREF12
  * @retval None
  */
void SYSCFG_VrefConfig(uint32_t SYSCFG_VREF_SEL)
{
    uint32_t tmpctrl = 0;
    /* Check the parameter */
    assert_param(IS_SYSCFG_Vref_Sel(SYSCFG_VREF_SEL));
    /* Get CFGR2 register value */
    tmpctrl = SYSCFG->CFGR2;
    /* Clear SYSCFG_VREF_SEL bit */
    tmpctrl &= (uint32_t) (~SYSCFG_CFGR2_VREF_SEL);
    /* Set the new SYSCFG_VREF_SEL bit value */
    tmpctrl |= (uint32_t) SYSCFG_VREF_SEL;
    /* Set CFGR2 register with the SYSCFG_VREF_SEL configuration */
    SYSCFG->CFGR2 = tmpctrl;
}

/**
  * @brief  Enables or disables the VREF_BUF.
  * @param  SYSCFG_Vref_Buf: This parameter can be :
  *            @arg SYSCFG_Vref_Buf_EN: The VREF_BUF_EN si set.
  *            @arg SYSCFG_Vref_Buf_DISABLE: The VREF_BUF_EN si reset.
  * @retval None
  */
void SYSCFG_VrefBufCMD(uint32_t SYSCFG_Vref_Buf)
{
    uint32_t tmpctrl = 0;
    /* Check the parameters */
    assert_param(IS_SYSCFG_Vref_Buf(SYSCFG_Vref_Buf));
    /* Get CFGR2 register value */
    tmpctrl = SYSCFG->CFGR2;
    /* Clear SYSCFG_CFGR2_VREF_BUF_EN bit */
    tmpctrl &= (uint32_t) (~SYSCFG_CFGR2_VREF_BUF_EN);
    /* Set the new SYSCFG_CFGR2_VREF_BUF_EN bit value */
    tmpctrl |= (uint32_t) SYSCFG_Vref_Buf;
    /* Set CFGR2 register with the SYSCFG_CFGR2_VREF_BUF configuration */
    SYSCFG->CFGR2 = tmpctrl;
}

/**
  * @brief  Configures the reference voltage selection.
  * @param  CRV_VO_DIV: This parameter can be :
  *            @arg SYSCFG_CRV_VO_0: forbid
  *            @arg SYSCFG_CRV_VO_1: 1/32 VREFP
  *            @arg SYSCFG_CRV_VO_2: 1/32 VREFP
  *            @arg SYSCFG_CRV_VO_3: 1/32 VREFP
  *                 ...
  *                 ...
  *            @arg SYSCFG_CRV_VO_31: 31/32 VREFP
  * @retval None
  */
void SYSCFG_RefVolConfig(uint32_t CRV_VO_DIV)
{
    uint32_t tmpctrl = 0;
    /* Check the parameter */
    assert_param(IS_SYSCFG_CRV_VO(CRV_VO_DIV));
    /* Get CFGR2 register value */
    tmpctrl = SYSCFG->CFGR2;
    /* Clear SYSCFG_VREF_SEL bit */
    tmpctrl &= (uint32_t) (~SYSCFG_CFGR2_CRV_VO_Mask);
    /* Set the new SYSCFG_VREF_SEL bit value */
    tmpctrl |= (uint32_t) CRV_VO_DIV;
    /* Set CFGR2 register with the SYSCFG_VREF_SEL configuration */
    SYSCFG->CFGR2 = tmpctrl;
}

/**
  * @brief  Configures the TIM3_CH4 remapping.
  * @param  SYSCFG_TIM3_CH4_REMAP: This parameter can be :
  *            @arg SYSCFG_TIM3_CH4_Remap_0: GPIO serves as CH4 input source for TIM3
  *            @arg SYSCFG_TIM3_CH4_Remap_1: LSI serves as CH4 input source for TIM3
  *            @arg SYSCFG_TIM3_CH4_Remap_2: The division HSI clock serves as the CH4 input source for TIM3
  *            @arg SYSCFG_TIM3_CH4_Remap_3: LSE serves as CH4 input source for TIM3
  *            @arg SYSCFG_TIM3_CH4_Remap_4: reserved
  *            @arg SYSCFG_TIM3_CH4_Remap_5: reserved (GPIO serves as CH4 input source for TIM3)
  *            @arg SYSCFG_TIM3_CH4_Remap_6: reserved (GPIO serves as CH4 input source for TIM3)
  *            @arg SYSCFG_TIM3_CH4_Remap_7: reserved (GPIO serves as CH4 input source for TIM3)
  * @retval None
  */
void SYSCFG_Tim3Ch4RemapConfig(uint32_t SYSCFG_TIM3_CH4_REMAP)
{
    uint32_t tmpctrl = 0;
    /* Check the parameter */
    assert_param(IS_SYSCFG_TIM3_CH4_Remap(SYSCFG_TIM3_CH4_REMAP));
    /* Get CFGR2 register value */
    tmpctrl = SYSCFG->CFGR2;
    /* Clear TIM3_CH4_REMAP bit */
    tmpctrl &= (uint32_t) (~SYSCFG_CFGR2_TIM3_CH4_REMAP_Mask);
    /* Set the new TIM3_CH4_REMAP bit value */
    tmpctrl |= (uint32_t) SYSCFG_TIM3_CH4_REMAP;
    /* Set CFGR2 register with the TIM3_CH4_REMAP configuration */
    SYSCFG->CFGR2 = tmpctrl;
}

/**
  * @brief  Configures the ADC_BUF voltage selection..
  * @param  SYSCFG_V_ADC_BUF: This parameter can be :
  *            @arg SYSCFG_V_ADC_BUF_SELECT_0: ADC BUF Voltage VREF12
  *            @arg SYSCFG_V_ADC_BUF_SELECT_1: reserved
  *            @arg SYSCFG_V_ADC_BUF_SELECT_2: reserved
  *            @arg SYSCFG_V_ADC_BUF_SELECT_3: reserved
  * @retval None
  */
void SYSCFG_AdcBufConfig(uint32_t SYSCFG_V_ADC_BUF)
{
    uint32_t tmpctrl = 0;
    /* Check the parameter */
    assert_param(IS_SYSCFG_V_ADC_BUF_SELECT(SYSCFG_V_ADC_BUF));
    /* Get CFGR2 register value */
    tmpctrl = SYSCFG->CFGR2;
    /* Clear SYSCFG_V_ADC_BUF bit */
    tmpctrl &= (uint32_t) (~SYSCFG_CFGR2_V_ADC_BUF_SELECT_Mask);
    /* Set the new SYSCFG_V_ADC_BUF value */
    tmpctrl |= (uint32_t) SYSCFG_V_ADC_BUF;
    /* Set CFGR2 register with the SYSCFG_V_ADC_BUF configuration */
    SYSCFG->CFGR2 = tmpctrl;
}

/**
  * @brief  Configures the ADC18 channel sampling voltage selection.
  * @param  SYSCFG_V_ADC_IN_18: This parameter can be :
  *            @arg SYSCFG_V_ADC_IN_18_SELECT_0: ADC18 channel sampling voltage is selected as ADC_DIV_O (VBAT partial voltage).
  *            @arg SYSCFG_V_ADC_IN_18_SELECT_1: reserved
  *            @arg SYSCFG_V_ADC_IN_18_SELECT_2: reserved
  *            @arg SYSCFG_V_ADC_IN_18_SELECT_3: reserved
  *            @arg SYSCFG_V_ADC_IN_18_SELECT_4: The sampling voltage of ADC18 channel is selected as internal voltage divider CRV.
  *            @arg SYSCFG_V_ADC_IN_18_SELECT_5: reserved
  *            @arg SYSCFG_V_ADC_IN_18_SELECT_6: forbid
  *            @arg SYSCFG_V_ADC_IN_18_SELECT_7: forbid
  * @retval None
  */
void SYSCFG_AdcIn18VolConfig(uint32_t SYSCFG_V_ADC_IN_18)
{
    uint32_t tmpctrl = 0;
    /* Check the parameter */
    assert_param(IS_SYSCFG_V_ADC_IN_18_SELECT(SYSCFG_V_ADC_IN_18));
    /* Get CFGR2 register value */
    tmpctrl = SYSCFG->CFGR2;
    /* Clear SYSCFG_V_ADC_IN_18_SELECT bit */
    tmpctrl &= (uint32_t) (~SYSCFG_CFGR2_V_ADC_IN_18_SELECT_Mask);
    /* Set the new SYSCFG_V_ADC_IN_18_SELECT value */
    tmpctrl |= (uint32_t) SYSCFG_V_ADC_IN_18;
    /* Set CFGR2 register with the SYSCFG_V_ADC_IN_18_SELECT configuration */
    SYSCFG->CFGR2 = tmpctrl;
}

/**
  * @brief  Configure the DMA channels remapping.
  * @param  SYSCFG_DMARemap: selects the DMA channels remap.
  *         This parameter can be one of the following values:
  *            @arg SYSCFG_DMARemap_I2C1: Remap I2C1 DMA Rx requests from channel3 to channel7 \n
  *                 Remap I2C1_Tx DMA requests from channel2 to channel6
  *            @arg SYSCFG_DMARemap_USART2: Remap USART2_Rx DMA requests from channel5 to channel7  \n
  *                 Remap USART2_Tx DMA requests from channel4 to channel6
  *            @arg SYSCFG_DMARemap_TIM17: Remap TIM17 DMA requests from channel1 to channel2
  *            @arg SYSCFG_DMARemap_TIM16: Remap TIM16 DMA requests from channel3 to channel4
  *            @arg SYSCFG_DMARemap_USART1_Rx: Remap USART1 Rx DMA requests from channel3 to channel5
  *            @arg SYSCFG_DMARemap_USART1_Tx: Remap USART1 Tx DMA requests from channel2 to channel4
  *            @arg SYSCFG_DMARemap_ADC: Remap ADC DMA requests from channel1 to channel2
  * @param  NewState: new state of the DMA channel remapping.
  *         This parameter can be: ENABLE or DISABLE.
  * @note   When enabled, DMA channel of the selected peripheral is remapped
  * @note   When disabled, Default DMA channel is mapped to the selected peripheral
  * @note   By default TIM17 DMA requests is mapped to channel 1,
  *         use SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_TIM17, Enable) to remap
  *         TIM17 DMA requests to channel 2 and use
  *         SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_TIM17, Disable) to map
  *         TIM17 DMA requests to channel 1 (default mapping)
  * @retval None
  */
void SYSCFG_DMAChannelRemapConfig(uint32_t SYSCFG_DMARemap, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_SYSCFG_DMA_REMAP(SYSCFG_DMARemap));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Remap the DMA channel */
        SYSCFG->CFGR1 |= (uint32_t)SYSCFG_DMARemap;
    }
    else
    {
        /* use the default DMA channel mapping */
        SYSCFG->CFGR1 &= (uint32_t)(~SYSCFG_DMARemap);
    }
}

/**
  * @brief  Configure the I2C fast mode plus driving capability.
  * @param  SYSCFG_I2CFastModePlus: selects the pin.
  *         This parameter can be one of the following values:
  *            @arg SYSCFG_I2CFastModePlus_PB6: Configure fast mode plus driving capability for PB6
  *            @arg SYSCFG_I2CFastModePlus_PB7: Configure fast mode plus driving capability for PB7
  *            @arg SYSCFG_I2CFastModePlus_PB8: Configure fast mode plus driving capability for PB8
  *            @arg SYSCFG_I2CFastModePlus_PB9: Configure fast mode plus driving capability for PB9
  *            @arg SYSCFG_I2CFastModePlus_PA9: Configure fast mode plus driving capability for PA9 
  *            @arg SYSCFG_I2CFastModePlus_PA10: Configure fast mode plus driving capability for PA10 
  *            @arg SYSCFG_I2CFastModePlus_I2C1: Configure fast mode plus driving capability for PB10, PB11, PF6 and PF7
  *            @arg SYSCFG_I2CFastModePlus_I2C2: Configure fast mode plus driving capability for I2C2 pins,
  * @param  NewState: new state of the DMA channel remapping.
  *         This parameter can be:  ENABLE or DISABLE.
  * @note   ENABLE: Enable fast mode plus driving capability for selected I2C pin
  * @note   DISABLE: Disable fast mode plus driving capability for selected I2C pin
  * @note   For I2C1, fast mode plus driving capability can be enabled on all selected
  *         I2C1 pins using SYSCFG_I2CFastModePlus_I2C1 parameter or independently
  *         on each one of the following pins PB6, PB7, PB8 and PB9.
  * @note   For remaining I2C1 pins (PA14, PA15...) fast mode plus driving capability
  *         can be enabled only by using SYSCFG_I2CFastModePlus_I2C1 parameter.
  * @note   For all I2C2 pins fast mode plus driving capability can be enabled
  *         only by using SYSCFG_I2CFastModePlus_I2C2 parameter.
  * @retval None
  */
void SYSCFG_I2CFastModePlusConfig(uint32_t SYSCFG_I2CFastModePlus, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable fast mode plus driving capability for selected pin */
        SYSCFG->CFGR1 |= (uint32_t)SYSCFG_I2CFastModePlus;
    }
    else
    {
        /* Disable fast mode plus driving capability for selected pin */
        SYSCFG->CFGR1 &= (uint32_t)(~SYSCFG_I2CFastModePlus);
    }
}


/**
  * @brief  Selects the GPIO pin used as EXTI Line.
  * @param  EXTI_PortSourceGPIOx: selects the GPIO port to be used as source
  *         for EXTI lines where x can be (A, B, C, D, E or F).
  * @param  EXTI_PinSourcex: specifies the EXTI line to be configured.
  * @retval None
  */
void SYSCFG_EXTILineConfig(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex)
{
    uint32_t tmp = 0x00;
    /* Check the parameters */
    assert_param(IS_EXTI_PORT_SOURCE(EXTI_PortSourceGPIOx));
    assert_param(IS_EXTI_PIN_SOURCE(EXTI_PinSourcex));
    tmp = ((uint32_t)0x0F) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03));

    switch (EXTI_PinSourcex >> 0x02)
    {
        case (uint8_t)0x00:
            SYSCFG->EXTICR1 &= ~tmp;
            SYSCFG->EXTICR1 |= (((uint32_t)EXTI_PortSourceGPIOx) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03)));
            break;

        case (uint8_t)0x01:
            SYSCFG->EXTICR2 &= ~tmp;
            SYSCFG->EXTICR2 |= (((uint32_t)EXTI_PortSourceGPIOx) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03)));
            break;

        case (uint8_t)0x02:
            SYSCFG->EXTICR3 &= ~tmp;
            SYSCFG->EXTICR3 |= (((uint32_t)EXTI_PortSourceGPIOx) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03)));
            break;

        case (uint8_t)0x03:
            SYSCFG->EXTICR4 &= ~tmp;
            SYSCFG->EXTICR4 |= (((uint32_t)EXTI_PortSourceGPIOx) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03)));
            break;

        default:
            break;
    }
}

/**
  * @brief  Connect the selected parameter to the break input of TIM1.
  * @note   The selected configuration is locked and can be unlocked by system reset
  * @param  SYSCFG_Break: selects the configuration to be connected to break
  *         input of TIM1
  *         This parameter can be any combination of the following values:
  *            @arg SYSCFG_Break_PVD: Connects the PVD event to the Break Input of TIM1,
  *            @arg SYSCFG_Break_SRAMParity: Connects the SRAM_PARITY error signal to the Break Input of TIM1 .
  *            @arg SYSCFG_Break_Lockup: Connects Lockup output of CortexM0 to the break input of TIM1.
  * @retval None
  */
void SYSCFG_BreakConfig(uint32_t SYSCFG_Break)
{
    /* Check the parameter */
    assert_param(IS_SYSCFG_LOCK_CONFIG(SYSCFG_Break));
    SYSCFG->CFGR2 |= (uint32_t) SYSCFG_Break;
}

/**
  * @brief  Checks whether the specified SYSCFG flag is set or not.
  * @param  SYSCFG_Flag: specifies the SYSCFG flag to check.
  *         This parameter can be one of the following values:
  *            @arg SYSCFG_FLAG_PEF: SRAM parity error flag.
  * @retval The new state of SYSCFG_Flag (SET or RESET).
  */
FlagStatus SYSCFG_GetFlagStatus(uint32_t SYSCFG_Flag)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameter */
    assert_param(IS_SYSCFG_FLAG(SYSCFG_Flag));

    /* Check the status of the specified SPI flag */
    if ((SYSCFG->CFGR2 & SYSCFG_CFGR2_SRAM_PEF) != (uint32_t)RESET)
    {
        /* SYSCFG_Flag is set */
        bitstatus = SET;
    }
    else
    {
        /* SYSCFG_Flag is reset */
        bitstatus = RESET;
    }

    /* Return the SYSCFG_Flag status */
    return  bitstatus;
}

/**
  * @brief  Clear the selected SYSCFG flag.
  * @param  SYSCFG_Flag: selects the flag to be cleared.
  *         This parameter can be any combination of the following values:
  *            @arg SYSCFG_FLAG_PEF: SRAM parity error flag.
  * @retval None
  */
void SYSCFG_ClearFlag(uint32_t SYSCFG_Flag)
{
    /* Check the parameter */
    assert_param(IS_SYSCFG_FLAG(SYSCFG_Flag));
    SYSCFG->CFGR2 |= (uint32_t) SYSCFG_Flag;
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

/**
  * @}
  */
