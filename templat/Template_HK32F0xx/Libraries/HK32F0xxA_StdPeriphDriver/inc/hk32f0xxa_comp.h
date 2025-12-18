/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f0xxa_comp.h
* @brief:     API file of analog comparator module
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F0XXA_COMP_H
#define __HK32F0XXA_COMP_H

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


/** @addtogroup COMP COMP
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  COMP Init structure definition
  */

typedef struct
{

    uint32_t COMP_InvertingInput;     /*!< Selects the inverting input of the comparator.
                                          This parameter can be a value of @ref COMP_InvertingInput */

    uint32_t COMP_Output;             /*!< Selects the output redirection of the comparator.
                                          This parameter can be a value of @ref COMP_Output */

    uint32_t COMP_OutputPol;           /*!< Selects the output polarity of the comparator.
                                          This parameter can be a value of @ref COMP_OutputPolarity */

    uint32_t COMP_Hysteresis;         /*!< Selects the hysteresis voltage of the comparator.
                                          This parameter can be a value of @ref COMP_Hysteresis */

    uint32_t COMP_Mode;               /*!< Selects the operating mode of the comparator
                                         and allows to adjust the speed/consumption.
                                          This parameter can be a value of @ref COMP_Mode */

} COMP_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup COMP_Exported_Constants COMP_Exported_Constants
  * @{
  */

/** @defgroup COMP_Selection COMP_Selection
  * @{
  */

#define COMP_Selection_COMP1                    ((uint32_t)0x00000000) /*!< COMP1 Selection */
#define COMP_Selection_COMP2                    ((uint32_t)0x00000010) /*!< COMP2 Selection */
#define COMP_Selection_COMP3                    ((uint32_t)0x00000001) /*!< COMP2 Selection */

#define IS_COMP_ALL_PERIPH(PERIPH) (((PERIPH) == COMP_Selection_COMP1) || \
                                    ((PERIPH) == COMP_Selection_COMP2) || \
                                    ((PERIPH) == COMP_Selection_COMP3))

/**
  * @}
  */

/** @defgroup COMP_InvertingInput COMP_InvertingInput
  * @{
  */

#define COMP_InvertingInput_1_4VREFINT          ((uint32_t)0x00000000)  /*!< 1/4 VREFINT connected to comparator inverting input */
#define COMP_InvertingInput_1_2VREFINT          ((uint32_t)0x00000010)  /*!< 1/2 VREFINT connected to comparator inverting input */
#define COMP_InvertingInput_3_4VREFINT          ((uint32_t)0x00000020)  /*!< 3/4 VREFINT connected to comparator inverting input */
#define COMP_InvertingInput_VREFINT             ((uint32_t)0x00000030)  /*!< VREFINT connected to comparator inverting input */
#define COMP_InvertingInput_PA4                 ((uint32_t)0x00000040)  /*!<  PA4 connected to comparator inverting input */
#define COMP_InvertingInput_PA5                 ((uint32_t)0x00000050)  /*!<  PA5 connected to comparator inverting input*/
#define COMP_InvertingInput_PB1                 ((uint32_t)0x00000060)  /*!<  PB1 connected to comparator inverting input */

#define IS_COMP_INVERTING_INPUT(INPUT) (((INPUT) == COMP_InvertingInput_1_4VREFINT) || \
                                        ((INPUT) == COMP_InvertingInput_1_2VREFINT) || \
                                        ((INPUT) == COMP_InvertingInput_3_4VREFINT) || \
                                        ((INPUT) == COMP_InvertingInput_VREFINT)    || \
                                        ((INPUT) == COMP_InvertingInput_PA4)       || \
                                        ((INPUT) == COMP_InvertingInput_PA5)       || \
                                        ((INPUT) == COMP_InvertingInput_PB1))
/**
  * @}
  */

/** @defgroup COMP_Output COMP_Output
  * @{
  */

#define COMP_Output_None                  ((uint32_t)0x00000000)   /*!< COMP output isn't connected to other peripherals */
#define COMP_Output_TIM1BKIN              ((uint32_t)0x00000100)   /*!< COMP output connected to TIM1 Break Input (BKIN) */
#define COMP_Output_TIM1IC1               ((uint32_t)0x00000200)   /*!< COMP output connected to TIM1 Input Capture 1 */
#define COMP_Output_TIM1OCREFCLR          ((uint32_t)0x00000300)   /*!< COMP output connected to TIM1 OCREF Clear */
#define COMP_Output_TIM2IC4               ((uint32_t)0x00000400)   /*!< COMP output connected to TIM2 Input Capture 4 */
#define COMP_Output_TIM2OCREFCLR          ((uint32_t)0x00000500)   /*!< COMP output connected to TIM2 OCREF Clear */
#define COMP_Output_TIM3IC1               ((uint32_t)0x00000600)   /*!< COMP output connected to TIM3 Input Capture 1 */
#define COMP_Output_TIM3OCREFCLR          ((uint32_t)0x00000700)   /*!< COMP output connected to TIM3 OCREF Clear */


#define IS_COMP_OUTPUT(OUTPUT) (((OUTPUT) == COMP_Output_None)         || \
                                ((OUTPUT) == COMP_Output_TIM1BKIN)     || \
                                ((OUTPUT) == COMP_Output_TIM1IC1)      || \
                                ((OUTPUT) == COMP_Output_TIM1OCREFCLR) || \
                                ((OUTPUT) == COMP_Output_TIM2IC4)      || \
                                ((OUTPUT) == COMP_Output_TIM2OCREFCLR) || \
                                ((OUTPUT) == COMP_Output_TIM3IC1)      || \
                                ((OUTPUT) == COMP_Output_TIM3OCREFCLR))
/**
  * @}
  */

/** @defgroup COMP_OutputPolarity COMP_OutputPolarity
  * @{
  */
#define COMP_OutputPol_NonInverted          ((uint32_t)0x00000000)  /*!< COMP output on GPIO isn't inverted */
#define COMP_OutputPol_Inverted             ((uint32_t)0x00000800)       /*!< COMP output on GPIO is inverted */

#define IS_COMP_OUTPUT_POL(POL) (((POL) == COMP_OutputPol_NonInverted)  || \
                                 ((POL) == COMP_OutputPol_Inverted))

/**
  * @}
  */

/** @defgroup COMP_Hysteresis COMP_Hysteresis
  * @{
  */
/* Please refer to the electrical characteristics in the device datasheet for
   the hysteresis level */
#define COMP_Hysteresis_No                         ((uint32_t)0x00000000) /*!< No hysteresis */
#define COMP_Hysteresis_Low                        ((uint32_t)0x00001000) /*!< Hysteresis level low */
#define COMP_Hysteresis_Medium                     ((uint32_t)0x00002000) /*!< Hysteresis level medium */
#define COMP_Hysteresis_High                       ((uint32_t)0x00003000) /*!< Hysteresis level high */

#define IS_COMP_HYSTERESIS(HYSTERESIS)    (((HYSTERESIS) == COMP_Hysteresis_No) || \
                                           ((HYSTERESIS) == COMP_Hysteresis_Low) || \
                                           ((HYSTERESIS) == COMP_Hysteresis_Medium) || \
                                           ((HYSTERESIS) == COMP_Hysteresis_High))
/**
  * @}
  */

/** @defgroup COMP_Mode COMP_Mode
  * @{
  */
/* Please refer to the electrical characteristics in the device datasheet for
   the power consumption values */
#define COMP_Mode_HighSpeed                     ((uint32_t)0x00000000)  /*!< High Speed */
#define COMP_Mode_MediumSpeed                   ((uint32_t)0x00000004)  /*!< Medium Speed */
#define COMP_Mode_LowPower                      ((uint32_t)0x00000008)  /*!< Low power mode */
#define COMP_Mode_UltraLowPower                 ((uint32_t)0x0000000c)  /*!< Ultra-low power mode */

#define IS_COMP_MODE(MODE)    (((MODE) == COMP_Mode_UltraLowPower) || \
                               ((MODE) == COMP_Mode_LowPower)      || \
                               ((MODE) == COMP_Mode_MediumSpeed)   || \
                               ((MODE) == COMP_Mode_HighSpeed))
/**
  * @}
  */

/** @defgroup COMP_OutputLevel COMP_OutputLevel
  * @{
  */
/* When output polarity is not inverted, comparator output is high when
   the non-inverting input is at a higher voltage than the inverting input */
#define COMP_OutputLevel_High                   ((uint32_t)0x00004000)
/* When output polarity is not inverted, comparator output is low when
   the non-inverting input is at a lower voltage than the inverting input*/
#define COMP_OutputLevel_Low                    ((uint32_t)0x00000000)

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
/* Exported functions ------------------------------------------------------- */

/*  Function used to set the COMP configuration to the default reset state ****/
void COMP_DeInit(void);

/* Initialization and Configuration functions *********************************/
void COMP_Init(uint32_t COMP_Selection, COMP_InitTypeDef* COMP_InitStruct);
void COMP_StructInit(COMP_InitTypeDef* COMP_InitStruct);
void COMP_Cmd(uint32_t COMP_Selection, FunctionalState NewState);
void COMP_SwitchCmd(FunctionalState NewState);
uint32_t COMP_GetOutputLevel(uint32_t COMP_Selection);

/* Window mode control function ***********************************************/
void COMP_WindowCmd(uint32_t COMP_Selection, FunctionalState NewState);

/* COMP configuration locking function ****************************************/
void COMP_LockConfig(uint32_t COMP_Selection);

#ifdef __cplusplus
}
#endif

#endif /*__HK32F0XXA_COMP_H */





