/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f0xxa_emacc.h
* @brief:     Head file of emacc module
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F0XXA_EMACC_H
#define __HK32F0XXA_EMACC_H

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


/** @addtogroup EMACC
  * @{
  */


/** @defgroup EMACC_Exported_Types EMACC_Exported_Types
  * @{
  */

/**
  * @brief Handle of a PI component
  */
typedef struct
{
    uint32_t  wKpiGain;              /**< gain used by PI component */
    uint32_t  wUpperIntegralLimit;  /**< Upper limit used to saturate the integral
                                       term given by integral of process variable error */
    uint32_t  wLowerIntegralLimit;  /**< Lower limit used to saturate the integral
                                       term given by Ki / Ki divisor * integral of
                                       process variable error */
    int16_t   hUpperOutputLimit;    /**< Upper limit used to saturate the PI output */
    int16_t   hLowerOutputLimit;    /**< Lower limit used to saturate the PI output */
    uint16_t  hKpDivisorPOW2;       /**< Kp gain divisor expressed as power of 2.
                                       E.g. if gain divisor is 512 the value
                                       must be 9 as 2^9 = 512 */
    uint16_t  hKiDivisorPOW2;       /**< Ki gain divisor expressed as power of 2.
                                       E.g. if gain divisor is 512 the value
                                       must be 9 as 2^9 = 512 */
} EMACC_PI_InitTypeDef;

/**
  * @brief Two components stator current type definition
  */
typedef struct
{
    int16_t qI_Component1;
    int16_t qI_Component2;
} Curr_Components;

/**
  * @brief  Two components stator voltage type definition
  */
typedef struct
{
    int16_t qV_Component1;
    int16_t qV_Component2;
} Volt_Components;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup EMACC_Exported_Constants EMACC_Exported_Constants
  * @{
  */

/** @defgroup EMACC_Circle limit_Selection
  * @{
  */

#define CIRCLELIM_MAXMODULE       (0x7FFF)      //  Circle limitation maximum allowed module
#define CIRCLELIM_TABLE_INDEX     (0x3F)        //  Circle limitation table indexing strart
#define EMACC_CLEAR_STATUS_MASK   (0x1F)        // clear all emacc status flag


#define PID_RAM_BASE              ((uint32_t *) 0x40028100)
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/* EMACC Configuration function ************************************************/
void EMACC_DeInit(void);
void EMACC_Init(EMACC_PI_InitTypeDef* EMACC_ID_InitStruct, EMACC_PI_InitTypeDef* EMACC_IQ_InitStruct);

void EMACC_Cmd(FunctionalState NewState);

/* emacc calculate functions ***********************************/

Volt_Components EMACC_Cal(int16_t hElAngle, Curr_Components Iab, Curr_Components Iqdref);

#ifdef __cplusplus
}
#endif

#endif /*__HK32F0XXA_EMACC_H */



