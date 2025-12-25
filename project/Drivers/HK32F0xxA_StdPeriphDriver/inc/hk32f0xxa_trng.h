/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f0xxa_trng.h
* @brief:     True RNG module driver
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F0XXA_TRNG_H
#define __HK32F0XXA_TRNG_H

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



/** @addtogroup RNG
  * @{
  */

/** @defgroup RNG_Exported_Constants RNG_Exported_Constants
  * @{
  */

/* Exported constants --------------------------------------------------------*/


/** @defgroup RNG_Exported_Constants_Group1 RNG Interrupt definition
  * @{
  */
#define RNG_IT_DRDY  RNG_SR_DRDY  /*!< Data Ready interrupt  */
#define RNG_IT_SEI   RNG_SR_SEIS  /*!< Seed error interrupt  */
/**
  * @}
  */

/** @defgroup RNG_Exported_Constants_Group2 RNG Flag definition
  * @{
  */
#define RNG_FLAG_DRDY   RNG_SR_DRDY  /*!< Data ready                 */
#define RNG_FLAG_SECS   RNG_SR_SECS  /*!< Seed error current status  */

#define RNG_IT_IE       RNG_CR_IE      /*!< RNG Interrupt enable */

#define RNG_MODE_OPEN_ANOLOG      RNG_CR_MODE // 
#define RNG_MODE_CLOSED_ANOLOG    RNG_CR_MODE_Pos
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */


typedef struct
{
    uint32_t Option_Cycle;  //RNG accumulation clock period
    uint32_t Mode;          // RNG work mode
} RNG_InitTypeDef;


/* Exported functions --------------------------------------------------------*/

void RNG_Init(RNG_InitTypeDef *RNG_InitStruct);
void RNG_DeInit(void);
void RNG_Cmd(FunctionalState NewState);
ErrorStatus RNG_GetRandomNumber(uint32_t *random32bit);
uint32_t RNG_GetRandomNumberIT(void);
void RNG_ITConfig( FunctionalState NewState);
FlagStatus RNG_GetFlagStatus(uint32_t RNG_FLAG);
void RNG_ClearFlag(uint32_t RNG_FLAG);
ITStatus RNG_GetITStatus(uint32_t RNG_IT);
void RNG_ClearITPendingBit(uint32_t RNG_IT);

void RNG_IRQHandler(void);

#define IS_RNG_GET_IT(IT) (((IT) == RNG_IT_DRDY) || RNG_IT_SEI)


#define IS_RNG_IT(IT) ((IT) == RNG_IT_SEI)

#define IS_RNG_FLAG(FLAG) (((FLAG) == RNG_FLAG_DRDY) || \
                           ((FLAG) == RNG_FLAG_SECS))


#ifdef __cplusplus
}
#endif

#endif /*__HK32F0XXA_TRNG_H */


