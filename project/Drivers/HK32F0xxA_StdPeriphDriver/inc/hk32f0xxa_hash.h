/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f0xxa_hash.h
* @brief:     This file contains all the functions prototypes for the HASH
*             firmware library.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F0XXA_HASH_H
#define __HK32F0XXA_HASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#if defined(HK32F030xxA)
#include "hk32f030xxA.h"
#elif defined(HK32F031xxA)
#include "hk32f031xxA.h"
#elif defined(HK32F072x)
#include "hk32f072x.h"
#elif defined(HK32F04AxxA)
#include "hk32f04axxA.h"
#elif defined(HK32ASPIN010xx)
#include "hk32aspinx.h"
#elif defined(HK32ASAFE010xx)
#include "hk32asafex.h"
#else
#error "Please select first the target HK32F0xxA device used in your application (in hk32f0xxa.h file)"
#endif

/** @addtogroup HASH
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup HASH_Exported_Types HASH_Exported_Types
  * @{
  */

/**
  * @brief   HASH Init structure definition
  */
typedef struct
{
    uint32_t HASH_AlgoSelection; /*!<  SHA-256 This parameter
                                    can be a value of @ref HASH_Algo_Selection */
    uint32_t HASH_AlgoMode;      /*!< HASH . This parameter can be a value
                                    of @ref HASH_processor_Algorithm_Mode */
    uint32_t HASH_DataType;      /*!< 32-bit data, 16-bit data, 8-bit data or
                                    bit string. This parameter can be a value of
                                    @ref HASH_Data_Type */
} HASH_InitTypeDef;

/**
  * @brief  HASH message digest result structure definition
  */
typedef struct
{
    uint32_t Data[8];      /*!< Message digest result : 8x 32bit wors for SHA-256 */
} HASH_MsgDigest;

/**
  * @brief  HASH context swapping structure definition
  */
typedef struct
{
    uint32_t HASH_IMR;
    uint32_t HASH_STR;
    uint32_t HASH_CR;
    uint32_t HASH_CSR[38];
} HASH_Context;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup HASH_Exported_Constants HASH_Exported_Constants
  * @{
  */

/** @defgroup HASH_Algo_Selection HASH_Algo_Selection
  * @{
  */
#define HASH_AlgoSelection_SHA256    (HASH_CR_ALGO_0|HASH_CR_ALGO_1)      /*!< HASH function is SHA256 */

#define IS_HASH_ALGOSELECTION(ALGOSELECTION) ( (ALGOSELECTION) == HASH_AlgoSelection_SHA256 )
/**
  * @}
  */

/** @defgroup HASH_processor_Algorithm_Mode HASH_processor_Algorithm_Mode
  * @{
  */
#define HASH_AlgoMode_HASH         ((uint32_t)0x00000000) /*!< Algorithm is HASH */

#define IS_HASH_ALGOMODE(ALGOMODE) ((ALGOMODE) == HASH_AlgoMode_HASH)
/**
  * @}
  */

/** @defgroup HASH_Data_Type  HASH_Data_Type
  * @{
  */
#define HASH_DataType_32b          ((uint32_t)0x0000) /*!< 32-bit data. No swapping                     */
#define HASH_DataType_16b          HASH_CR_DATATYPE_0 /*!< 16-bit data. Each half word is swapped       */
#define HASH_DataType_8b           HASH_CR_DATATYPE_1 /*!< 8-bit data. All bytes are swapped            */
#define HASH_DataType_1b           HASH_CR_DATATYPE   /*!< 1-bit data. In the word all bits are swapped */

#define IS_HASH_DATATYPE(DATATYPE) (((DATATYPE) == HASH_DataType_32b)|| \
                                    ((DATATYPE) == HASH_DataType_16b)|| \
                                    ((DATATYPE) == HASH_DataType_8b) || \
                                    ((DATATYPE) == HASH_DataType_1b))
/**
  * @}
  */




/** @defgroup Number_of_valid_bits_in_last_word_of_the_message   Number_of_valid_bits_in_last_word_of_the_message
  * @{
  */

#define IS_HASH_VALIDBITSNUMBER(VALIDBITS) ((VALIDBITS) <= 0x1F)

/**
  * @}
  */

/** @defgroup HASH_interrupts_definition   HASH_interrupts_definition
  * @{
  */
#define HASH_IT_DINI               HASH_IMR_DINIE  /*!< A new block can be entered into the input buffer (DIN) */
#define HASH_IT_DCI                HASH_IMR_DCIE   /*!< Digest calculation complete                            */

#define IS_HASH_IT(IT) ((((IT) & (uint32_t)0xFFFFFFFC) == 0x00000000) && ((IT) != 0x00000000))
#define IS_HASH_GET_IT(IT) (((IT) == HASH_IT_DINI) || ((IT) == HASH_IT_DCI))

/**
  * @}
  */

/** @defgroup HASH_flags_definition   HASH_flags_definition
  * @{
  */
#define HASH_FLAG_DINIS            HASH_SR_DINIS  /*!< 16 locations are free in the DIN : A new block can be entered into the input buffer */
#define HASH_FLAG_DCIS             HASH_SR_DCIS   /*!< Digest calculation complete                                                         */
#define HASH_FLAG_DMAS             HASH_SR_DMAS   /*!< DMA interface is enabled (DMAE=1) or a transfer is ongoing                          */
#define HASH_FLAG_BUSY             HASH_SR_BUSY   /*!< The hash core is Busy : processing a block of data                                  */
#define HASH_FLAG_DINNE            HASH_CR_DINNE  /*!< DIN not empty : The input buffer contains at least one word of data                 */

#define IS_HASH_GET_FLAG(FLAG) (((FLAG) == HASH_FLAG_DINIS) || \
                                ((FLAG) == HASH_FLAG_DCIS)  || \
                                ((FLAG) == HASH_FLAG_DMAS)  || \
                                ((FLAG) == HASH_FLAG_BUSY)  || \
                                ((FLAG) == HASH_FLAG_DINNE))

#define IS_HASH_CLEAR_FLAG(FLAG)(((FLAG) == HASH_FLAG_DINIS) || \
                                 ((FLAG) == HASH_FLAG_DCIS))

/**
  * @}
  */

/**
  * @}
  */





/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup HASH_Exported_Functions HASH_Exported_Functions
  * @{
  */

/**
 * @brief   Function used to set the HASH configuration to the default reset state
 */

void HASH_DeInit(void);

/**
 * @brief   Initialization and Configuration functions
 */

void HASH_Init(HASH_InitTypeDef* HASH_InitStruct);
void HASH_StructInit(HASH_InitTypeDef* HASH_InitStruct);
void HASH_Reset(void);

/**
 * @brief   Message Digest generation functions
 */

void HASH_DataIn(uint32_t Data);
uint8_t HASH_GetInFIFOWordsNbr(void);
void HASH_SetLastWordValidBitsNbr(uint16_t ValidNumber);
void HASH_StartDigest(void);
void HASH_GetDigest(HASH_MsgDigest* HASH_MessageDigest);

/**
 * @brief   Context swapping functions
 */

void HASH_SaveContext(HASH_Context* HASH_ContextSave);
void HASH_RestoreContext(HASH_Context* HASH_ContextRestore);

/**
 * @brief   HASH's DMA interface Configuration function
 */

void HASH_DMACmd(FunctionalState NewState);

/**
 * @brief   Interrupts and flags management functions
 */

void HASH_ITConfig(uint32_t HASH_IT, FunctionalState NewState);
FlagStatus HASH_GetFlagStatus(uint32_t HASH_FLAG);
void HASH_ClearFlag(uint32_t HASH_FLAG);
ITStatus HASH_GetITStatus(uint32_t HASH_IT);
void HASH_ClearITPendingBit(uint32_t HASH_IT);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__HK32F0XXA_HASH_H */



