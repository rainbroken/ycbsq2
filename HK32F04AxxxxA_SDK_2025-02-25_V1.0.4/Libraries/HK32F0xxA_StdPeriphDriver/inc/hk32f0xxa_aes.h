/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f0xxa_aes.h
* @brief:     This file contains all the functions prototypes for the AES firmware
*             library.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F0XXA_AES_H
#define __HK32F0XXA_AES_H

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
#elif defined(HK32ASPin010xx)
#include "hk32aspinx.h"
#elif defined(HK32ASAFE010xx)
#include "hk32asafex.h"
#else
#error "Please select first the target HK32F0xxA device used in your application (in hk32f0xxa.h file)"
#endif

/** @addtogroup AES
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup AES_Exported_Types AES_Exported_Types
  * @{
  */

/**
  * @brief  AES init structure definition
  */

typedef struct
{
    uint32_t u32Aes_cr ;
    uint32_t u32Aes_cr2 ;
    uint32_t u32Aes_sr ;

    uint32_t u32Aes_keyr0 ;
    uint32_t u32Aes_keyr1 ;
    uint32_t u32Aes_keyr2 ;
    uint32_t u32Aes_keyr3 ;
    uint32_t u32Aes_keyr4 ;
    uint32_t u32Aes_keyr5 ;
    uint32_t u32Aes_keyr6 ;
    uint32_t u32Aes_keyr7 ;

    uint32_t u32Aes_ivr0 ;
    uint32_t u32Aes_ivr1 ;
    uint32_t u32Aes_ivr2 ;
    uint32_t u32Aes_ivr3 ;

    uint32_t u32Aes_Doutr0 ;
    uint32_t u32Aes_Doutr1 ;
    uint32_t u32Aes_Doutr2 ;
    uint32_t u32Aes_Doutr3 ;

    uint32_t u32Aes_Dinr0 ;
    uint32_t u32Aes_Dinr1 ;
    uint32_t u32Aes_Dinr2 ;
    uint32_t u32Aes_Dinr3 ;
} AES_PAR;

/**
  * @brief   AES Init structure definition
  */
typedef struct
{
    uint32_t AES_Operation; /*!< Specifies the AES mode of operation.
                               This parameter can be a value of @ref AES_possible_Operation_modes */

    uint32_t AES_KeySize;   /*!< Used only in AES mode only : 128, 192 or 256 bit
                                key length. This parameter can be a value of
                                @ref AES_keysize */
} AES_InitTypeDef;

/**
  * @brief   AES Key(s) structure definition
  */
typedef struct
{
    uint32_t AES_Key0;  /*!< Key[31:0]   */
    uint32_t AES_Key1;  /*!< Key[63:32]  */
    uint32_t AES_Key2;  /*!< Key[95:64]  */
    uint32_t AES_Key3;  /*!< Key[127:96] */
    uint32_t AES_Key4;  /*!< Key[159:128]   */
    uint32_t AES_Key5;  /*!< Key[191:160]  */
    uint32_t AES_Key6;  /*!< Key[223:192]  */
    uint32_t AES_Key7;  /*!< Key[255:254] */
} AES_KeyInitTypeDef;


/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup AES_Exported_Constants AES_Exported_Constants
  * @{
  */

/** @defgroup AES_possible_Operation_modes AES_possible_Operation_modes
  * @{
  */

#define AES_Operation_Encryp               ((uint32_t)0x00000000) /*!< AES in Encryption mode */
#define AES_Operation_KeyDeriv             AES_CR_MODE_0          /*!< AES in Key Derivation mode */
#define AES_Operation_Decryp               AES_CR_MODE_1          /*!< AES in Decryption mode */
#define AES_Operation_KeyDerivAndDecryp    AES_CR_MODE            /*!< AES in Key Derivation and Decryption mode */

#define IS_AES_MODE(OPERATION) (((OPERATION) == AES_Operation_Encryp)    || \
                                ((OPERATION) == AES_Operation_KeyDeriv)  || \
                                ((OPERATION) == AES_Operation_Decryp)    || \
                                ((OPERATION) == AES_Operation_KeyDerivAndDecryp))
/**
  * @}
  */


/** @defgroup AES_keysize AES_keysize
  * @{
  */

#define AES_KEYSIZE_128B                   ((uint32_t)0x00000000U)
#define AES_KEYSIZE_192B                   ((uint32_t)0x00000001U)
#define AES_KEYSIZE_256B                   ((uint32_t)0x00000002U)

#define IS_AES_KEYSIZE(KEYSIZE) (((KEYSIZE) == AES_KEYSIZE_128B)    || \
                                 ((KEYSIZE) == AES_KEYSIZE_192B)    || \
                                 ((KEYSIZE) == AES_KEYSIZE_256B) )

/**
  * @}
  */


/** @defgroup AES_Flags AES_Flags
  * @{
  */

#define AES_FLAG_CCF                       AES_SR_CCF    /*!< Computation Complete Flag */
#define AES_FLAG_RDERR                     AES_SR_RDERR  /*!< Read Error Flag           */
#define AES_FLAG_WRERR                     AES_SR_WRERR  /*!< Write Error Flag          */

#define IS_AES_FLAG(FLAG) (((FLAG) == AES_FLAG_CCF)    || \
                           ((FLAG) == AES_FLAG_RDERR)  || \
                           ((FLAG) == AES_FLAG_WRERR))

/**
  * @}
  */

/** @defgroup AES_Interrupts AES_Interrupts
  * @{
  */

#define AES_IT_CC                          AES_CR_CCFIE  /*!< Computation Complete interrupt */
#define AES_IT_ERR                         AES_CR_ERRIE /*!< Error interrupt                */

#define IS_AES_IT(IT) ((((IT) & (uint32_t)0xFFFFF9FF) == 0x00) && ((IT) != 0x00))
#define IS_AES_GET_IT(IT) (((IT) == AES_IT_CC) || ((IT) == AES_IT_ERR))

/**
  * @}
  */

/** @defgroup AES_DMA_Transfer_modes AES_DMA_Transfer_modes
  * @{
  */

#define AES_DMATransfer_In                 AES_CR_DMAINEN                     /*!< DMA requests enabled for input transfer phase */
#define AES_DMATransfer_Out                AES_CR_DMAOUTEN                    /*!< DMA requests enabled for input transfer phase */
#define AES_DMATransfer_InOut              (AES_CR_DMAINEN | AES_CR_DMAOUTEN) /*!< DMA requests enabled for both input and output phases */

#define IS_AES_DMA_TRANSFER(TRANSFER)   (((TRANSFER) == AES_DMATransfer_In)  || \
                                         ((TRANSFER) == AES_DMATransfer_Out) || \
                                         ((TRANSFER) == AES_DMATransfer_InOut))

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/** @defgroup AES_Exported_Functions AES_Exported_Functions
  * @{
  */

/**
 * @brief   Initialization and configuration functions
 */
void AES_DeInit(void);
void AES_Init(AES_InitTypeDef* AES_InitStruct);
void AES_SetKeySize(uint32_t Keysize);
void AES_KeyInit(AES_KeyInitTypeDef* AES_KeyInitStruct);
void AES_Cmd(FunctionalState NewState);
void AES_ClkRandom(FunctionalState NewState);
void AES_SetChainOptionMode(AES_InitTypeDef* AES_InitStruct);

/**
 * @brief   Structures initialization functions
 */
void AES_StructInit(AES_InitTypeDef* AES_InitStruct);

/**
 * @brief   AES Read and Write functions
 */
void AES_WriteSubData(uint32_t Data);
uint32_t AES_ReadSubData(void);
void AES_ReadKey(AES_KeyInitTypeDef* AES_KeyStruct);

/**
 * @brief   DMA transfers management function
 */
void AES_DMAConfig(uint32_t AES_DMATransfer, FunctionalState NewState);

/**
 * @brief   Interrupts and flags management functions
 */
void AES_ITConfig(uint32_t AES_IT, FunctionalState NewState);
FlagStatus AES_GetFlagStatus(uint32_t AES_FLAG);
void AES_ClearFlag(uint32_t AES_FLAG);
ITStatus AES_GetITStatus(uint32_t AES_IT);
void AES_ClearITPendingBit(uint32_t AES_IT);

/**
 * @brief   Pending and Resume config functions
 */
void AES_SetPendingConfigIT(void);
void AES_SetResumeConfigIT(void);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__HK32F0XXA_AES_H */
