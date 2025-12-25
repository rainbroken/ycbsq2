/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f0xxa_aes.c
* @brief:     This file provides firmware functions to manage the following
*             functionalities of the AES peripheral:
*             + Configuration
*             + Read/Write operations
*             + DMA transfers management
*             + Interrupts and flags management
* @author:    AE Team
* @version:   V1.0.0/2023-10-08
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32f0xxa_aes.h"
#include "hk32f0xxa_rcc.h"

/** @addtogroup HK32F0xxA_StdPeriph_Driver
  * @{
  */

/** @defgroup AES AES
  * @brief AES driver modules
  * @{
    @verbatim
 ===============================================================================
                        ##### AES Peripheral features #####
 ===============================================================================
....[..]
   (#) The Advanced Encryption Standard hardware accelerator (AES) can be used
       to both encipher and decipher data using AES algorithm.
   (#) The AES supports 4 operation modes:
       (++) Encryption: It consumes 214 clock cycle when processing one 128-bit block
       (++) Decryption: It consumes 214 clock cycle when processing one 128-bit block
       (++) Key derivation for decryption: It consumes 80 clock cycle when processing one 128-bit block
       (++) Key Derivation and decryption: It consumes 288 clock cycle when processing one 128-bit blobk
   (#) Moreover 1 chaining modes are supported:
       (++) Electronic codebook (ECB): Each plain text is encrypted/decrypted separately
  (#) The AES peripheral supports write/read error handling with interrupt capability.
  (#) Automatic data flow control with support of direct memory access (DMA) using
      2 channels, one for incoming data, and one for outcoming data.

                      ##### How to use this driver #####
 ===============================================================================
    [..]
        (#) AES AHB clock must be enabled to get write access to AES registers
            using RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_AES, ENABLE).
        (#) Initialize the key using AES_KeyInit().
        (#) Configure the AES operation mode using AES_Init().
        (#) If required, enable interrupt source using AES_ITConfig() and
            enable the AES interrupt vector using NVIC_Init().
        (#) If required, when using the DMA mode.
            (##) Configure the DMA using DMA_Init().
            (##) Enable DMA requests using AES_DMAConfig().
        (#) Enable the AES peripheral using AES_Cmd().
    @endverbatim
  *
  ******************************************************************************
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup AES_Private_Defines AES_Private_Defines
  * @{
  */

#define IS_BIT_CLR(REG,BIT)       (((REG) & (BIT)) == RESET)
#define AES_TIMEOUT_VALUE         ((uint32_t) 0x00010000)
#define CR_CLEAR_MASK             ((uint32_t)0xFFFFFF81)
#define CR_All_CLEAR_MASK         ((uint32_t)0x00001FFF)
#define CR2_KEYSIZE_CLEAR_MASK    ((uint32_t)0xFFFFFFFC)

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/** @defgroup AES_Private_Variables AES_Private_Variables
  * @{
  */

AES_PAR sAesPar = { 0 };

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup AES_Private_Functions AES_Private_Functions
  * @{
  */

/** @defgroup AES_Group1 Initialization and configuration
 *  @brief   Initialization and configuration.
 *
@verbatim
 ===============================================================================
                ##### Initialization and configuration #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes AES peripheral registers to their default reset values.
  * @retval None
  */
void AES_DeInit(void)
{
    /* Enable AES reset state */
    RCC_AHB2PeriphResetCmd(RCC_AHB2Periph_AES, ENABLE);
    /* Release AES from reset state */
    RCC_AHB2PeriphResetCmd(RCC_AHB2Periph_AES, DISABLE);
}

/**
  * @brief  Initializes the AES peripheral according to the specified parameters
  *         in the AES_InitStruct:
  *         - AES_Operation: specifies the operation mode (encryption, decryption...).
  * @note   If AES is already enabled, use AES_Cmd(DISABLE) before setting the new
  *         configuration (When AES is enabled, setting configuration is forbidden).
  * @param  AES_InitStruct: pointer to an AES_InitTypeDef structure that contains
  *         the configuration information for AES peripheral.
  * @retval None
  */
void AES_Init(AES_InitTypeDef* AES_InitStruct)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_AES_MODE(AES_InitStruct->AES_Operation));

    /* Get AES CR register value */
    tmpreg = AES->CR;

    /* Clear DATATYPE[1:0], MODE[1:0] and CHMOD[1:0] bits */
    tmpreg &= (uint32_t)CR_CLEAR_MASK;
    /* Init DATATYPE[1:0], MODE[1:0] and CHMOD[1:0] bits */
    tmpreg |= AES_InitStruct->AES_Operation;

    AES->CR = (uint32_t) tmpreg;

    /* Init KEY_SIZE[1:0] bits */
    tmpreg = AES->CR2;

    tmpreg &= ~AES_CR2_KEY_SIZE_Mask;

    tmpreg |= AES_InitStruct->AES_KeySize;

    AES->CR2 = (uint32_t) tmpreg;
}

/**
  * @brief  Set aes key size.
  * @param  Keysize: The size of key.
  *         This parameter can be any combinations of the following values:
  *            @arg AES_KEYSIZE_128B: The key size is 128 bit.
  *            @arg AES_KEYSIZE_192B: The key size is 192 bit.
  *            @arg AES_KEYSIZE_256B: The key size is 256 bit.
  * @retval None
  */
void AES_SetKeySize(uint32_t Keysize)
{
    /* set aes key size  */
    AES->CR2 |= Keysize;
}

/**
  * @brief  Initializes the AES Keys according to the specified parameters in the AES_KeyInitStruct.
  * @param  AES_KeyInitStruct: pointer to an AES_KeyInitTypeDef structure that
  *         contains the configuration information for the specified AES Keysize.
  *         Key: the configuration information for the specified AES Keys.
  * @note   This function must be called while the AES is disabled.
  * @note   In encryption, key derivation and key derivation + decryption modes,
  *         the second parameter  must contain the encryption key.
  *         In decryption mode, the second parameter  must contain the decryption key.
  * @retval None
  */
void AES_KeyInit(AES_KeyInitTypeDef* AES_KeyInitStruct)
{
    /* Key Initialisation */
    AES->KEYR7 = AES_KeyInitStruct->AES_Key7;
    AES->KEYR6 = AES_KeyInitStruct->AES_Key6;
    AES->KEYR5 = AES_KeyInitStruct->AES_Key5;
    AES->KEYR4 = AES_KeyInitStruct->AES_Key4;
    AES->KEYR3 = AES_KeyInitStruct->AES_Key3;
    AES->KEYR2 = AES_KeyInitStruct->AES_Key2;
    AES->KEYR1 = AES_KeyInitStruct->AES_Key1;
    AES->KEYR0 = AES_KeyInitStruct->AES_Key0;
}

/**
  * @brief  Enable or disable the AES peripheral.
  * @param  NewState: new state of the AES peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @note   The key must be written while AES is disabled.
  * @retval None
  */
void AES_Cmd(FunctionalState NewState)
{
    /* Check the parameter */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the AES peripheral */
        AES->CR |= (uint32_t) AES_CR_EN;   /**< AES Enable */
    }
    else
    {
        /* Disable the AES peripheral */
        AES->CR &= (uint32_t)(~AES_CR_EN);  /**< AES Disable */
    }
}

/**
  * @brief  Enable or disable the random clock.
  * @param  NewState: new state of the random clock.
  *         This random clock can be: ENABLE or DISABLE.
  * @note   The key must be written while AES is disabled.
  * @retval None
  */
void AES_ClkRandom(FunctionalState NewState)
{
    /* Check the parameter */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable randomize the AES clock */
        AES->CR2 |= (uint32_t) AES_CR2_RANDOM;
    }
    else
    {
        /* Disable randomize the AES clock  */
        AES->CR2 &= (uint32_t)(~AES_CR2_RANDOM);
    }
}

/**
  * @brief  Initializes the AES peripheral according to the specified parameters
  *         in the AES_InitStruct:
  *         - AES_Operation: specifies the operation mode (encryption, decryption...).
  * @note   If AES is already enabled, use AES_Cmd(DISABLE) before setting the new
  *         configuration (When AES is enabled, setting configuration is forbidden).
  * @param  AES_InitStruct: pointer to an AES_InitTypeDef structure that contains
  *         the configuration information for AES peripheral.
  * @retval None
  */
void AES_SetChainOptionMode(AES_InitTypeDef* AES_InitStruct)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_AES_MODE(AES_InitStruct->AES_Operation));

    /* Get AES CR register value */
    tmpreg = AES->CR;

    /* Clear DATATYPE[1:0], MODE[1:0] and CHMOD[1:0] bits */
    tmpreg &= (uint32_t)CR_CLEAR_MASK;
    /* Init DATATYPE[1:0], MODE[1:0] and CHMOD[1:0] bits */
    tmpreg |= AES_InitStruct->AES_Operation;

    AES->CR = (uint32_t) tmpreg;
}

/**
  * @}
  */

/** @defgroup AES_Group2 Structures initialization functions
 *  @brief   Structures initialization.
 *
@verbatim
 ===============================================================================
              ##### Structures initialization functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Fills each AES_InitStruct member with its default value.
  * @param  AES_InitStruct: pointer to an AES_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void AES_StructInit(AES_InitTypeDef* AES_InitStruct)
{
    AES_InitStruct->AES_Operation = AES_Operation_Encryp;
}

/**
  * @}
  */

/** @defgroup AES_Group3 AES Read and Write
 *  @brief   AES Read and Write.
 *
@verbatim
 ===============================================================================
                  ##### AES Read and Write functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Write data in DINR register to be processed by AES peripheral.
  * @note   To process 128-bit data (4 * 32-bit), this function must be called
  *         four times to write the 128-bit data in the 32-bit register DINR.
  * @note   When an unexpected write to DOUTR register is detected, WRERR flag is
  *         set.
  * @param  Data: The data to be processed.
  * @retval None
  */
void AES_WriteSubData(uint32_t Data)
{
    /* Write Data */
    AES->DINR = Data;
}

/**
  * @brief  Returns the data in DOUTR register processed by AES peripheral.
  * @note   This function must be called four times to get the 128-bit data.
  * @note   When an unexpected read of DINR register is detected, RDERR flag is
  *         set.
  * @retval The processed data.
  */
uint32_t AES_ReadSubData(void)
{
    /* Read Data */
    return AES->DOUTR;
}

/**
  * @brief  Read the Key value.
  * @param  AES_KeyStruct: pointer to an AES_KeyInitTypeDef structure which
  *         will contain the key.
  * @note   When the key derivation mode is selected, AES must be disabled
  *         (AES_Cmd(DISABLE)) before reading the decryption key.
  *         Reading the key while the AES is enabled will return unpredictable
  *         value.
  * @retval None
  */
void AES_ReadKey(AES_KeyInitTypeDef* AES_KeyStruct)
{
    AES_KeyStruct->AES_Key0 = AES->KEYR0;
    AES_KeyStruct->AES_Key1 = AES->KEYR1;
    AES_KeyStruct->AES_Key2 = AES->KEYR2;
    AES_KeyStruct->AES_Key3 = AES->KEYR3;
    AES_KeyStruct->AES_Key4 = AES->KEYR4;
    AES_KeyStruct->AES_Key5 = AES->KEYR5;
    AES_KeyStruct->AES_Key6 = AES->KEYR6;
    AES_KeyStruct->AES_Key7 = AES->KEYR7;
}

/**
  * @}
  */

/** @defgroup AES_Group4 DMA transfers management functions
 *  @brief   DMA transfers management function.
 *
@verbatim
 ===============================================================================
               ##### DMA transfers management functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Configures the AES DMA interface.
  * @param  AES_DMATransfer: Specifies the AES DMA transfer.
  *         This parameter can be one of the following values:
  *            @arg AES_DMATransfer_In: When selected, DMA manages the data input phase.
  *            @arg AES_DMATransfer_Out: When selected, DMA manages the data output phase.
  *            @arg AES_DMATransfer_InOut: When selected, DMA manages both the data input/output phases.
  * @param  NewState Indicates the new state of the AES DMA interface.
  *         This parameter can be: ENABLE or DISABLE.
  * @note   The DMA has no action in key derivation mode.
  * @retval None
  */
void AES_DMAConfig(uint32_t AES_DMATransfer, FunctionalState NewState)
{
    /* Check the parameter */
    assert_param(IS_AES_DMA_TRANSFER(AES_DMATransfer));

    if (NewState != DISABLE)
    {
        /* Enable the DMA transfer */
        AES->CR |= (uint32_t) AES_DMATransfer;
    }
    else
    {
        /* Disable the DMA transfer */
        AES->CR &= (uint32_t)(~AES_DMATransfer);
    }
}

/**
  * @}
  */

/** @defgroup AES_Group5 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions.
 *
@verbatim

 ===============================================================================
           ##### Interrupts and flags management functions #####
 ===============================================================================
@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified AES interrupt.
  * @param  AES_IT: Specifies the AES interrupt source to enable/disable.
  *         This parameter can be any combinations of the following values:
  *            @arg AES_IT_CC: Computation Complete Interrupt. If enabled, once CCF
  *                 flag is set an interrupt is generated.
  *            @arg AES_IT_ERR: Error Interrupt. If enabled, once a read error
  *                 flags (RDERR) or write error flag (WRERR) is set,
  *                 an interrupt is generated.
  * @param  NewState: The new state of the AES interrupt source.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void AES_ITConfig(uint32_t AES_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_AES_IT(AES_IT));

    if (NewState != DISABLE)
    {
        AES->CR |= (uint32_t) AES_IT;    /**< AES_IT Enable */
    }
    else
    {
        AES->CR &= (uint32_t)(~AES_IT);  /**< AES_IT Disable */
    }
}

/**
  * @brief  Checks whether the specified AES flag is set or not.
  * @param  AES_FLAG specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg AES_FLAG_CCF: Computation Complete Flag is set by hardware when
  *                 he computation phase is completed.
  *            @arg AES_FLAG_RDERR: Read Error Flag is set when an unexpected read
  *                 operation of DOUTR register is detected.
  *            @arg AES_FLAG_WRERR: Write Error Flag  is set when an unexpected write
  *                 operation in DINR is detected.
  * @retval FlagStatus (SET or RESET)
  */
FlagStatus AES_GetFlagStatus(uint32_t AES_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check parameters */
    assert_param(IS_AES_FLAG(AES_FLAG));

    if ((AES->SR & AES_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    /* Return the AES_FLAG status */
    return  bitstatus;
}

/**
  * @brief  Clears the AES flags.
  * @param  AES_FLAG: specifies the flag to clear.
  *         This parameter can be:
  *            @arg AES_FLAG_CCF: Computation Complete Flag is cleared by setting CCFC
  *                 bit in CR register.
  *            @arg AES_FLAG_RDERR: Read Error is cleared by setting ERRC bit in
  *                 CR register.
  *            @arg AES_FLAG_WRERR: Write Error is cleared by setting ERRC bit in
  *                 CR register.
  * @retval None
  */
void AES_ClearFlag(uint32_t AES_FLAG)
{
    /* Check the parameters */
    assert_param(IS_AES_FLAG(AES_FLAG));

    /* Check if AES_FLAG is AES_FLAG_CCF */
    if (AES_FLAG == AES_FLAG_CCF)
    {
        /* Clear CCF flag by setting CCFC bit */
        AES->CR |= (uint32_t) AES_CR_CCFC;
    }
    /* AES_FLAG is AES_FLAG_RDERR or AES_FLAG_WRERR */
    else
    {
        /* Clear RDERR and WRERR flags by setting ERRC bit */
        AES->CR |= (uint32_t) AES_CR_ERRC;
    }
}

/**
  * @brief  Checks whether the specified AES interrupt has occurred or not.
  * @param  AES_IT: Specifies the AES interrupt pending bit to check.
  *         This parameter can be:
  *            @arg AES_IT_CC: Computation Complete Interrupt.
  *            @arg AES_IT_ERR: Error Interrupt.
  * @retval ITStatus The new state of AES_IT (SET or RESET).
  */
ITStatus AES_GetITStatus(uint32_t AES_IT)
{
    ITStatus itstatus = RESET;
    uint32_t cciebitstatus = RESET, ccfbitstatus = RESET;

    /* Check parameters */
    assert_param(IS_AES_GET_IT(AES_IT));

    cciebitstatus = AES->CR & AES_CR_CCFIE;
    ccfbitstatus =  AES->SR & AES_SR_CCF;

    /* Check if AES_IT is AES_IT_CC */
    if (AES_IT == AES_IT_CC)
    {
        /* Check the status of the specified AES interrupt */
        if (((cciebitstatus) != (uint32_t)RESET) && ((ccfbitstatus) != (uint32_t)RESET))
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
    else /* AES_IT is AES_IT_ERR */
    {
        /* Check the status of the specified AES interrupt */
        if ((AES->CR & AES_CR_ERRIE) != RESET)
        {
            /* Check if WRERR or RDERR flags are set */
            if ((AES->SR & (uint32_t)(AES_SR_WRERR | AES_SR_RDERR)) != (uint16_t)RESET)
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

    /* Return the AES_IT status */
    return itstatus;
}

/**
  * @brief  Clears the AES's interrupt pending bits.
  * @param  AES_IT: specifies the interrupt pending bit to clear.
  *         This parameter can be any combinations of the following values:
  *            @arg AES_IT_CC: Computation Complete Interrupt.
  *            @arg AES_IT_ERR: Error Interrupt.
  * @retval None
  */
void AES_ClearITPendingBit(uint32_t AES_IT)
{
    /* Check the parameters */
    assert_param(IS_AES_IT(AES_IT));

    /* Clear the interrupt pending bit */
    AES->CR |= (uint32_t) (AES_IT >> (uint32_t) 0x00000002);
}

/**
  * @}
  */

/** @defgroup AES_Group6 Pending and Resume config functions
 *  @brief   Pending and Resume config functions.
 *
@verbatim

 ===============================================================================
           ##### Pending and Resume config functions #####
 ===============================================================================
@endverbatim
  * @{
  */

/**
  * @brief  Pending configuration in interrupt mode , The aes operation will be suspended
  *         when a higher priority interrupt occurs in aes operations.
  * @retval None
  */
void AES_SetPendingConfigIT(void)
{
    uint32_t PendingTimeout = 0;

    /*1. Read the AES_cr AES_cr2 AES_sr registers and press the stack */
    sAesPar.u32Aes_cr = AES->CR;
    sAesPar.u32Aes_cr2 = AES->CR2;
    sAesPar.u32Aes_sr = AES->SR;

    /*2. If dma is used to clear AES.dmainen*/
    if (READ_BIT(AES->CR, AES_CR_DMAINEN))
    {
        CLEAR_BIT(AES->CR, AES_CR_DMAINEN);
    }

    /*3. wait AES_SR.CCF to be Set*/
    do
    {
        PendingTimeout++;
    } while ((PendingTimeout != AES_TIMEOUT_VALUE) && (IS_BIT_CLR(AES->SR, AES_SR_CCF)));/* Wait for DRDY flag to be set */

    /*4. If dma is used, the operation of dma read dout will still be done by removing the AES
    dmaout.dmaouten clear hardware. if no dma is used, read the 4-times_doutr register and press the result stack*/
    if (READ_BIT(AES->CR, AES_CR_DMAOUTEN))
    {
        CLEAR_BIT(AES->CR, AES_CR_DMAOUTEN);
    }
    else
    {
        sAesPar.u32Aes_Doutr3 = AES->DOUTR;
        sAesPar.u32Aes_Doutr2 = AES->DOUTR;
        sAesPar.u32Aes_Doutr1 = AES->DOUTR;
        sAesPar.u32Aes_Doutr0 = AES->DOUTR;
    }

    /*5. set bit cr register to clear ccf flag*/
    SET_BIT(AES->CR, AES_CR_CCFC);

    /*6. set bit cr register to clear ccf flag*/
    CLEAR_BIT(AES->CR, AES_CR_EN);

    /*7. Read the AES_dinr for 4 consecutive times and press the stack*/
    sAesPar.u32Aes_Dinr3 = AES->DINR ;
    sAesPar.u32Aes_Dinr2 = AES->DINR ;
    sAesPar.u32Aes_Dinr1 = AES->DINR ;
    sAesPar.u32Aes_Dinr0 = AES->DINR ;

    /*8. Read the SM4_keyrx registers and press the stack*/
    sAesPar.u32Aes_keyr7 =  AES->KEYR7;
    sAesPar.u32Aes_keyr6 =  AES->KEYR6;
    sAesPar.u32Aes_keyr5 =  AES->KEYR5;
    sAesPar.u32Aes_keyr4 =  AES->KEYR4;
    sAesPar.u32Aes_keyr3 =  AES->KEYR3;
    sAesPar.u32Aes_keyr2 =  AES->KEYR2;
    sAesPar.u32Aes_keyr1 =  AES->KEYR1;
    sAesPar.u32Aes_keyr0 =  AES->KEYR0;
}

/**
  * @brief  Resume , The aes operation will be Resumed when a higher priority interrupt over in aes operations.  .
  * @retval None
  */
void AES_SetResumeConfigIT(void)
{
    /*1. Set AES_CR.en to 0 and turn off AES*/
    CLEAR_BIT(AES->CR, AES_CR_EN);

    /*2. Resume AES_KEYRx config*/
    AES->KEYR7 = sAesPar.u32Aes_keyr7 ;
    AES->KEYR6 = sAesPar.u32Aes_keyr6 ;
    AES->KEYR5 = sAesPar.u32Aes_keyr5 ;
    AES->KEYR4 = sAesPar.u32Aes_keyr4 ;
    AES->KEYR3 = sAesPar.u32Aes_keyr3 ;
    AES->KEYR2 = sAesPar.u32Aes_keyr2 ;
    AES->KEYR1 = sAesPar.u32Aes_keyr1 ;
    AES->KEYR0 = sAesPar.u32Aes_keyr0 ;

    /*3. Resume AES_DOUTR*/
    AES->DOUTR = sAesPar.u32Aes_Doutr3 ;
    AES->DOUTR = sAesPar.u32Aes_Doutr2 ;
    AES->DOUTR = sAesPar.u32Aes_Doutr1 ;
    AES->DOUTR = sAesPar.u32Aes_Doutr0 ;

    /*4. Resume AES_DINR*/
    AES->DINR = sAesPar.u32Aes_Dinr3 ;
    AES->DINR = sAesPar.u32Aes_Dinr2 ;
    AES->DINR = sAesPar.u32Aes_Dinr1 ;
    AES->DINR = sAesPar.u32Aes_Dinr0 ;

    /*5. Resume AES_CR,AES_CR2 config*/
    AES->CR = sAesPar.u32Aes_cr;
    AES->CR2 = sAesPar.u32Aes_cr2;

    /*6. set SM4_CR2.CCF_SET and SM4_CR2.INT_RESUME*/
    SET_BIT(AES->CR2, AES_CR2_CCF_SET);
    SET_BIT(AES->CR2, AES_CR2_INT_RESUM);
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

