/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f0xxa_comp.c
* @brief:     API file of analog comparator module
* @author:    AE Team
* @version:   V1.0.0/2023-10-10
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32f0xxa_comp.h"

/** @addtogroup HK32F0xxA_StdPeriph_Driver
  * @{
  */


/** @defgroup COMP COMP
  * @brief COMP driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* CSR register Mask */
#define COMP_CSR_CLEAR_MASK              ((uint32_t)0x00003FFE)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup COMP_Private_Functions COMP_Private_Functions
  * @{
  */

/** @defgroup  Initialization_And_Configuration Initialization_And_Configuration
 *  @brief   Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
               ##### Initialization and Configuration functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes COMP peripheral registers to their default reset values.
  * @note   Deinitialization can't be performed if the COMP configuration is locked.
  *         To unlock the configuration, perform a system reset.
  * @retval None
  */
void COMP_DeInit(void)
{
    COMP->CSR = ((uint32_t)0x00000000);    /*!< Set COMP_CSR register to reset value */
    COMP->CSR3 = ((uint32_t)0x00000000);    /*!< Set COMP_CSR3 register to reset value */
}

/**
  * @brief  Initializes the COMP peripheral according to the specified parameters
  *         in COMP_InitStruct
  * @note   If the selected comparator is locked, initialization can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @note   By default, PA1 is selected as COMP1 non inverting input.
  *         To use PA4 as COMP1 non inverting input call COMP_SwitchCmd() after COMP_Init()
  * @param  COMP_Selection: the selected comparator.
  *         This parameter can be one of the following values:
  *            @arg COMP_Selection_COMP1: COMP1 selected
  *            @arg COMP_Selection_COMP2: COMP2 selected
  * @param  COMP_InitStruct: pointer to an COMP_InitTypeDef structure that contains
  *         the configuration information for the specified COMP peripheral.
  * @retval None
  */
void COMP_Init(uint32_t COMP_Selection, COMP_InitTypeDef* COMP_InitStruct)
{
    uint32_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));
    assert_param(IS_COMP_INVERTING_INPUT(COMP_InitStruct->COMP_InvertingInput));
    assert_param(IS_COMP_OUTPUT(COMP_InitStruct->COMP_Output));
    assert_param(IS_COMP_OUTPUT_POL(COMP_InitStruct->COMP_OutputPol));
    assert_param(IS_COMP_HYSTERESIS(COMP_InitStruct->COMP_Hysteresis));
    assert_param(IS_COMP_MODE(COMP_InitStruct->COMP_Mode));

    if (COMP_Selection != COMP_Selection_COMP3)
    {
        /*!< Get the COMP_CSR register value */
        tmpreg = COMP->CSR;
        /*!< Clear the COMP1SW1, COMPx_IN_SEL, COMPx_OUT_TIM_SEL, COMPx_POL, COMPx_HYST and COMPx_PWR_MODE bits */
        tmpreg &= (uint32_t) ~(COMP_CSR_CLEAR_MASK << COMP_Selection);
    }
    else
    {
        tmpreg = COMP->CSR3;
        tmpreg &= (uint32_t) ~(COMP_CSR_CLEAR_MASK);
    }

    /*!< Configure COMP: inverting input, output redirection, hysteresis value and power mode */
    /*!< Set COMPxINSEL bits according to COMP_InitStruct->COMP_InvertingInput value */
    /*!< Set COMPxOUTSEL bits according to COMP_InitStruct->COMP_Output value */
    /*!< Set COMPxPOL bit according to COMP_InitStruct->COMP_OutputPol value */
    /*!< Set COMPxHYST bits according to COMP_InitStruct->COMP_Hysteresis value */
    /*!< Set COMPxMODE bits according to COMP_InitStruct->COMP_Mode value */
    tmpreg |= (uint32_t)((COMP_InitStruct->COMP_InvertingInput | COMP_InitStruct->COMP_Output |
                          COMP_InitStruct->COMP_OutputPol | COMP_InitStruct->COMP_Hysteresis |
                          COMP_InitStruct->COMP_Mode) << COMP_Selection);

    if (COMP_Selection != COMP_Selection_COMP3)
    {
        /*!< Write to COMP_CSR register */
        COMP->CSR = tmpreg;
    }
    else
    {
        COMP->CSR3 = tmpreg;
    }
}

/**
  * @brief  Fills each COMP_InitStruct member with its default value.
  * @param  COMP_InitStruct: pointer to an COMP_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void COMP_StructInit(COMP_InitTypeDef* COMP_InitStruct)
{
    COMP_InitStruct->COMP_InvertingInput = COMP_InvertingInput_1_4VREFINT;
    COMP_InitStruct->COMP_Output = COMP_Output_None;
    COMP_InitStruct->COMP_OutputPol = COMP_OutputPol_NonInverted;
    COMP_InitStruct->COMP_Hysteresis = COMP_Hysteresis_No;
    COMP_InitStruct->COMP_Mode = COMP_Mode_UltraLowPower;
}

/**
  * @brief  Enable or disable the COMP peripheral.
  * @note   If the selected comparator is locked, enable/disable can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @param  COMP_Selection: the selected comparator.
  *         This parameter can be one of the following values:
  *            @arg COMP_Selection_COMP1: COMP1 selected
  *            @arg COMP_Selection_COMP2: COMP2 selected
  * @param  NewState: new state of the COMP peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @note   When enabled, the comparator compares the non inverting input with
  *         the inverting input and the comparison result is available on comparator output.
  * @note   When disabled, the comparator doesn't perform comparison and the
  *         output level is low.
  * @retval None
  */
void COMP_Cmd(uint32_t COMP_Selection, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the selected COMP peripheral */
        if (COMP_Selection != COMP_Selection_COMP3)
        {
            COMP->CSR |= (uint32_t) (1 << COMP_Selection);
        }
        else
        {
            COMP->CSR3 |= COMP_CSR3_COMP3EN;
        }
    }
    else
    {
        /* Disable the selected COMP peripheral  */
        if (COMP_Selection != COMP_Selection_COMP3)
        {
            COMP->CSR &= (uint32_t)(~((uint32_t)1 << COMP_Selection));
        }
        else
        {
            COMP->CSR3 &= ~COMP_CSR3_COMP3EN;
        }
    }
}

/**
  * @brief  Close or Open the SW1 switch.
  * @note   This switch is solely intended to redirect signals onto high
  *         impedance input, such as COMP1 non-inverting input (highly resistive switch)
  * @param  NewState: New state of the analog switch.
  *         This parameter can be: ENABLE or DISABLE.
  * @note   When enabled, the SW1 is closed; PA1 is connected to PA4
  * @note   When disabled, the SW1 switch is open; PA1 is disconnected from PA4
  * @retval None
  */
void COMP_SwitchCmd(FunctionalState NewState)
{
    /* Check the parameter */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Close SW1 switch */
        COMP->CSR |= (uint32_t) (COMP_CSR_COMP1SW1);
    }
    else
    {
        /* Open SW1 switch */
        COMP->CSR &= (uint32_t)(~COMP_CSR_COMP1SW1);
    }
}

/**
  * @brief  Return the output level (high or low) of the selected comparator.
  * @note   The output level depends on the selected polarity.
  * @note   If the polarity is not inverted:
  *         - Comparator output is low when the non-inverting input is at a lower
  *         voltage than the inverting input
  *         - Comparator output is high when the non-inverting input is at a higher
  *         voltage than the inverting input
  * @note   If the polarity is inverted:
  *         - Comparator output is high when the non-inverting input is at a lower
  *         voltage than the inverting input
  *         - Comparator output is low when the non-inverting input is at a higher
  *         voltage than the inverting input
  * @param  COMP_Selection: the selected comparator.
  *         This parameter can be one of the following values:
  *            @arg COMP_Selection_COMP1: COMP1 selected
  *            @arg COMP_Selection_COMP2: COMP2 selected
  * @retval Returns the selected comparator output level: low or high.
  */
uint32_t COMP_GetOutputLevel(uint32_t COMP_Selection)
{
    uint32_t compout = 0x0;
    /* Check the parameters */
    assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));

    /* Check if selected comparator output is high */
    if (COMP_Selection != COMP_Selection_COMP3)
    {
        compout = COMP->CSR & (COMP_CSR_COMP1OUT << COMP_Selection);
    }
    else
    {
        compout = COMP->CSR3 & COMP_CSR3_COMP3OUT;
    }

    if (compout != COMP_OutputLevel_Low)
    {
        compout = COMP_OutputLevel_High;
    }

    /* Return the comparator output level */
    return (uint32_t)(compout);
}

/**
  * @}
  */

/** @defgroup  Window_Mode_Control Window_Mode_Control
 *  @brief   Window mode control function
 *
@verbatim
 ===============================================================================
                     ##### Window mode control function #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the window mode.
  * @note   In window mode, COMP1 and COMP2 non inverting inputs are connected
  *         together and only COMP1 non inverting input (PA1) can be used.
  * @param  COMP_Selection: selects the comparator to be locked
  *         This parameter can be a value of the following values:
  *            @arg COMP_Selection_COMP2: COMP1 configuration is locked.
  *            @arg COMP_Selection_COMP3: COMP3 configuration is locked.
  * @param  NewState: new state of the window mode.
  * @retval None
  */
void COMP_WindowCmd(uint32_t COMP_Selection, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));

    if (NewState != DISABLE)
    {
        /* Enable the window mode */
        if (COMP_Selection != COMP_Selection_COMP3)
        {
            COMP->CSR |= (uint32_t) COMP_CSR_COMP2WNDWEN;
        }
        else
        {
            COMP->CSR3 |= (uint32_t) COMP_CSR3_COMP3WNDWEN;
        }
    }
    else
    {
        /* Disable the window mode */
        if (COMP_Selection != COMP_Selection_COMP3)
        {
            COMP->CSR &= (uint32_t)(~COMP_CSR_COMP2WNDWEN);
        }
        else
        {
            COMP->CSR3 &= (uint32_t)(~COMP_CSR3_COMP3WNDWEN);
        }
    }
}

/**
  * @}
  */

/** @defgroup  COMP_Configuration_Locking COMP_Configuration_Locking
 *  @brief   COMP1 and COMP2 configuration locking function
 *           COMP1 and COMP2 configuration can be locked each separately.
 *           Unlocking is performed by system reset.
 *
@verbatim
 ===============================================================================
                     ##### Configuration Lock function #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Lock the selected comparator (COMP1/COMP2) configuration.
  * @note   Locking the configuration means that all control bits are read-only.
  *         To unlock the comparator configuration, perform a system reset.
  * @param  COMP_Selection: selects the comparator to be locked
  *         This parameter can be a value of the following values:
  *            @arg COMP_Selection_COMP1: COMP1 configuration is locked.
  *            @arg COMP_Selection_COMP2: COMP2 configuration is locked.
  * @retval None
  */
void COMP_LockConfig(uint32_t COMP_Selection)
{
    /* Check the parameter */
    assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));

    /* Set the lock bit corresponding to selected comparator */

    if (COMP_Selection != COMP_Selection_COMP3)
    {
        COMP->CSR |= (uint32_t) (COMP_CSR_COMP1LOCK << COMP_Selection);
    }
    else
    {
        COMP->CSR |= (uint32_t) (COMP_CSR3_COMP3LOCK);
    }
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
