/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f0xxa_dma.h
* @brief:     This file contains all the functions prototypes for the DMA firmware
*             library.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F0XXA_DMA_H
#define __HK32F0XXA_DMA_H

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

/** @addtogroup DMA
  * @{
  */
/* Exported types ------------------------------------------------------------*/

/** @defgroup DMA_Exported_Types DMA_Exported_Types
  * @{
  */

/**
  * @brief  DMA Init structures definition
  */
typedef struct
{
    uint32_t DMA_PeripheralBaseAddr; /*!< Specifies the peripheral base address for DMAy Channelx.              */

    uint32_t DMA_MemoryBaseAddr;     /*!< Specifies the memory base address for DMAy Channelx.                  */

    uint32_t DMA_DIR;                /*!< Specifies if the peripheral is the source or destination.
                                        This parameter can be a value of @ref DMA_Data_Transfer_Direction     */

    uint32_t DMA_BufferSize;         /*!< Specifies the buffer size, in data unit, of the specified Channel.
                                        The data unit is equal to the configuration set in DMA_PeripheralDataSize
                                        or DMA_MemoryDataSize members depending in the transfer direction     */

    uint32_t DMA_PeripheralInc;      /*!< Specifies whether the Peripheral address register is incremented or not.
                                        This parameter can be a value of @ref DMA_Peripheral_Incremented_Mode */

    uint32_t DMA_MemoryInc;          /*!< Specifies whether the memory address register is incremented or not.
                                        This parameter can be a value of @ref DMA_Memory_Incremented_Mode     */

    uint32_t DMA_PeripheralDataSize; /*!< Specifies the Peripheral data width.
                                        This parameter can be a value of @ref DMA_Peripheral_Data_Size        */

    uint32_t DMA_MemoryDataSize;     /*!< Specifies the Memory data width.
                                        This parameter can be a value of @ref DMA_Memory_Data_Size            */

    uint32_t DMA_Mode;               /*!< Specifies the operation mode of the DMAy Channelx.
                                        This parameter can be a value of @ref DMA_Circular_Normal_Mode
                                        @note: The circular buffer mode cannot be used if the memory-to-memory
                                              data transfer is configured on the selected Channel */

    uint32_t DMA_Priority;           /*!< Specifies the software priority for the DMAy Channelx.
                                        This parameter can be a value of @ref DMA_Priority_Level              */

    uint32_t DMA_M2M;                /*!< Specifies if the DMAy Channelx will be used in memory-to-memory transfer.
                                        This parameter can be a value of @ref DMA_Memory_To_Memory            */
} DMA_InitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup DMA_Exported_Constants DMA_Exported_Constants
  * @{
  */

/** @defgroup DMA_Channel_Check DMA_Channel_Check
  * @{
  */
#define IS_DMA_ALL_PERIPH(PERIPH) (((PERIPH) == DMA1_Channel1) || \
                                   ((PERIPH) == DMA1_Channel2) || \
                                   ((PERIPH) == DMA1_Channel3) || \
                                   ((PERIPH) == DMA1_Channel4) || \
                                   ((PERIPH) == DMA1_Channel5)  )

/**
  * @}
  */

/** @defgroup DMA_Data_Transfer_Direction DMA_Data_Transfer_Direction
  * @{
  */

#define DMA_DIR_PeripheralSRC              ((uint32_t)0x00000000)
#define DMA_DIR_PeripheralDST              DMA_CCR_DIR

#define IS_DMA_DIR(DIR) (((DIR) == DMA_DIR_PeripheralSRC) || \
                         ((DIR) == DMA_DIR_PeripheralDST))

/**
  * @}
  */

/** @defgroup DMA_Peripheral_Incremented_Mode DMA_Peripheral_Incremented_Mode
  * @{
  */

#define DMA_PeripheralInc_Disable          ((uint32_t)0x00000000)
#define DMA_PeripheralInc_Enable           DMA_CCR_PINC

#define IS_DMA_PERIPHERAL_INC_STATE(STATE) (((STATE) == DMA_PeripheralInc_Disable) || \
                                            ((STATE) == DMA_PeripheralInc_Enable))
/**
  * @}
  */

/** @defgroup DMA_Memory_Incremented_Mode DMA_Memory_Incremented_Mode
  * @{
  */

#define DMA_MemoryInc_Disable              ((uint32_t)0x00000000)
#define DMA_MemoryInc_Enable               DMA_CCR_MINC

#define IS_DMA_MEMORY_INC_STATE(STATE) (((STATE) == DMA_MemoryInc_Disable) || \
                                        ((STATE) == DMA_MemoryInc_Enable))
/**
  * @}
  */

/** @defgroup DMA_Peripheral_Data_Size DMA_Peripheral_Data_Size
  * @{
  */

#define DMA_PeripheralDataSize_Byte        ((uint32_t)0x00000000)
#define DMA_PeripheralDataSize_HalfWord    DMA_CCR_PSIZE_0
#define DMA_PeripheralDataSize_Word        DMA_CCR_PSIZE_1

#define IS_DMA_PERIPHERAL_DATA_SIZE(SIZE) (((SIZE) == DMA_PeripheralDataSize_Byte) || \
                                           ((SIZE) == DMA_PeripheralDataSize_HalfWord) || \
                                           ((SIZE) == DMA_PeripheralDataSize_Word))

/**
  * @}
  */

/** @defgroup DMA_Memory_Data_Size DMA_Memory_Data_Size
  * @{
  */

#define DMA_MemoryDataSize_Byte            ((uint32_t)0x00000000)
#define DMA_MemoryDataSize_HalfWord        DMA_CCR_MSIZE_0
#define DMA_MemoryDataSize_Word            DMA_CCR_MSIZE_1

#define IS_DMA_MEMORY_DATA_SIZE(SIZE) (((SIZE) == DMA_MemoryDataSize_Byte) || \
                                       ((SIZE) == DMA_MemoryDataSize_HalfWord) || \
                                       ((SIZE) == DMA_MemoryDataSize_Word))

/**
  * @}
  */

/** @defgroup DMA_Circular_Normal_Mode DMA_Circular_Normal_Mode
  * @{
  */

#define DMA_Mode_Normal                    ((uint32_t)0x00000000)
#define DMA_Mode_Circular                  DMA_CCR_CIRC

#define IS_DMA_MODE(MODE) (((MODE) == DMA_Mode_Normal) || ((MODE) == DMA_Mode_Circular))

/**
  * @}
  */

/** @defgroup DMA_Priority_Level DMA_Priority_Level
  * @{
  */

#define DMA_Priority_VeryHigh              DMA_CCR_PL
#define DMA_Priority_High                  DMA_CCR_PL_1
#define DMA_Priority_Medium                DMA_CCR_PL_0
#define DMA_Priority_Low                   ((uint32_t)0x00000000)

#define IS_DMA_PRIORITY(PRIORITY) (((PRIORITY) == DMA_Priority_VeryHigh) || \
                                   ((PRIORITY) == DMA_Priority_High) || \
                                   ((PRIORITY) == DMA_Priority_Medium) || \
                                   ((PRIORITY) == DMA_Priority_Low))

/**
  * @}
  */

/** @defgroup DMA_Memory_To_Memory DMA_Memory_To_Memory
  * @{
  */

#define DMA_M2M_Disable                    ((uint32_t)0x00000000)
#define DMA_M2M_Enable                     DMA_CCR_MEM2MEM

#define IS_DMA_M2M_STATE(STATE) (((STATE) == DMA_M2M_Disable) || ((STATE) == DMA_M2M_Enable))

/**
  * @}
  */


/** @defgroup DMA_Interrupts_Definition DMA_Interrupts_Definition
  * @{
  */

#define DMA_IT_TC                          DMA_CCR_TCIE
#define DMA_IT_HT                          DMA_CCR_HTIE
#define DMA_IT_TE                          DMA_CCR_TEIE

#define IS_DMA_CONFIG_IT(IT) ((((IT) & 0xFFFFFFF1) == 0x00) && ((IT) != 0x00))

#define DMA1_IT_GL1                        DMA_ISR_GIF1
#define DMA1_IT_TC1                        DMA_ISR_TCIF1
#define DMA1_IT_HT1                        DMA_ISR_HTIF1
#define DMA1_IT_TE1                        DMA_ISR_TEIF1
#define DMA1_IT_GL2                        DMA_ISR_GIF2
#define DMA1_IT_TC2                        DMA_ISR_TCIF2
#define DMA1_IT_HT2                        DMA_ISR_HTIF2
#define DMA1_IT_TE2                        DMA_ISR_TEIF2
#define DMA1_IT_GL3                        DMA_ISR_GIF3
#define DMA1_IT_TC3                        DMA_ISR_TCIF3
#define DMA1_IT_HT3                        DMA_ISR_HTIF3
#define DMA1_IT_TE3                        DMA_ISR_TEIF3
#define DMA1_IT_GL4                        DMA_ISR_GIF4
#define DMA1_IT_TC4                        DMA_ISR_TCIF4
#define DMA1_IT_HT4                        DMA_ISR_HTIF4
#define DMA1_IT_TE4                        DMA_ISR_TEIF4
#define DMA1_IT_GL5                        DMA_ISR_GIF5
#define DMA1_IT_TC5                        DMA_ISR_TCIF5
#define DMA1_IT_HT5                        DMA_ISR_HTIF5
#define DMA1_IT_TE5                        DMA_ISR_TEIF5
#define DMA1_IT_GL6                        DMA_ISR_GIF6
#define DMA1_IT_TC6                        DMA_ISR_TCIF6
#define DMA1_IT_HT6                        DMA_ISR_HTIF6
#define DMA1_IT_TE6                        DMA_ISR_TEIF6
#define DMA1_IT_GL7                        DMA_ISR_GIF7
#define DMA1_IT_TC7                        DMA_ISR_TCIF7
#define DMA1_IT_HT7                        DMA_ISR_HTIF7
#define DMA1_IT_TE7                        DMA_ISR_TEIF7


#define IS_DMA_CLEAR_IT(IT) (((((IT) & 0xF0000000) == 0x00) || (((IT) & 0xEFF00000) == 0x00)) && ((IT) != 0x00))

#define IS_DMA_GET_IT(IT) (((IT) == DMA1_IT_GL1) || ((IT) == DMA1_IT_TC1) || \
                           ((IT) == DMA1_IT_HT1) || ((IT) == DMA1_IT_TE1) || \
                           ((IT) == DMA1_IT_GL2) || ((IT) == DMA1_IT_TC2) || \
                           ((IT) == DMA1_IT_HT2) || ((IT) == DMA1_IT_TE2) || \
                           ((IT) == DMA1_IT_GL3) || ((IT) == DMA1_IT_TC3) || \
                           ((IT) == DMA1_IT_HT3) || ((IT) == DMA1_IT_TE3) || \
                           ((IT) == DMA1_IT_GL4) || ((IT) == DMA1_IT_TC4) || \
                           ((IT) == DMA1_IT_HT4) || ((IT) == DMA1_IT_TE4) || \
                                                     ((IT) == DMA1_IT_GL5) || ((IT) == DMA1_IT_TC5) || \
                           ((IT) == DMA1_IT_HT5) || ((IT) == DMA1_IT_TE5) || \
                                                     ((IT) == DMA1_IT_GL6) || ((IT) == DMA1_IT_TC6) || \
                           ((IT) == DMA1_IT_HT6) || ((IT) == DMA1_IT_TE6) || \
                           ((IT) == DMA1_IT_GL7) || ((IT) == DMA1_IT_TC7) || \
                           ((IT) == DMA1_IT_HT7) || ((IT) == DMA1_IT_TE7))

/**
  * @}
  */

/** @defgroup DMA_Flags_Definition DMA_Flags_Definition
  * @{
  */
#define DMA1_FLAG_GL1                      DMA_ISR_GIF1
#define DMA1_FLAG_TC1                      DMA_ISR_TCIF1
#define DMA1_FLAG_HT1                      DMA_ISR_HTIF1
#define DMA1_FLAG_TE1                      DMA_ISR_TEIF1
#define DMA1_FLAG_GL2                      DMA_ISR_GIF2
#define DMA1_FLAG_TC2                      DMA_ISR_TCIF2
#define DMA1_FLAG_HT2                      DMA_ISR_HTIF2
#define DMA1_FLAG_TE2                      DMA_ISR_TEIF2
#define DMA1_FLAG_GL3                      DMA_ISR_GIF3
#define DMA1_FLAG_TC3                      DMA_ISR_TCIF3
#define DMA1_FLAG_HT3                      DMA_ISR_HTIF3
#define DMA1_FLAG_TE3                      DMA_ISR_TEIF3
#define DMA1_FLAG_GL4                      DMA_ISR_GIF4
#define DMA1_FLAG_TC4                      DMA_ISR_TCIF4
#define DMA1_FLAG_HT4                      DMA_ISR_HTIF4
#define DMA1_FLAG_TE4                      DMA_ISR_TEIF4
#define DMA1_FLAG_GL5                      DMA_ISR_GIF5
#define DMA1_FLAG_TC5                      DMA_ISR_TCIF5
#define DMA1_FLAG_HT5                      DMA_ISR_HTIF5
#define DMA1_FLAG_TE5                      DMA_ISR_TEIF5
#define DMA1_FLAG_GL6                      DMA_ISR_GIF6
#define DMA1_FLAG_TC6                      DMA_ISR_TCIF6
#define DMA1_FLAG_HT6                      DMA_ISR_HTIF6
#define DMA1_FLAG_TE6                      DMA_ISR_TEIF6
#define DMA1_FLAG_GL7                      DMA_ISR_GIF7
#define DMA1_FLAG_TC7                      DMA_ISR_TCIF7
#define DMA1_FLAG_HT7                      DMA_ISR_HTIF7
#define DMA1_FLAG_TE7                      DMA_ISR_TEIF7


#define IS_DMA_CLEAR_FLAG(FLAG) (((((FLAG) & 0xF0000000) == 0x00) || (((FLAG) & 0xEFF00000) == 0x00)) && ((FLAG) != 0x00))

#define IS_DMA_GET_FLAG(FLAG) (((FLAG) == DMA1_FLAG_GL1) || ((FLAG) == DMA1_FLAG_TC1) || \
                               ((FLAG) == DMA1_FLAG_HT1) || ((FLAG) == DMA1_FLAG_TE1) || \
                               ((FLAG) == DMA1_FLAG_GL2) || ((FLAG) == DMA1_FLAG_TC2) || \
                               ((FLAG) == DMA1_FLAG_HT2) || ((FLAG) == DMA1_FLAG_TE2) || \
                               ((FLAG) == DMA1_FLAG_GL3) || ((FLAG) == DMA1_FLAG_TC3) || \
                               ((FLAG) == DMA1_FLAG_HT3) || ((FLAG) == DMA1_FLAG_TE3) || \
                               ((FLAG) == DMA1_FLAG_GL4) || ((FLAG) == DMA1_FLAG_TC4) || \
                               ((FLAG) == DMA1_FLAG_HT4) || ((FLAG) == DMA1_FLAG_TE4) || \
                                                             ((FLAG) == DMA1_FLAG_GL4) || ((FLAG) == DMA1_FLAG_TC5) || \
                               ((FLAG) == DMA1_FLAG_HT4) || ((FLAG) == DMA1_FLAG_TE5) || \
                                                             ((FLAG) == DMA1_FLAG_GL4) || ((FLAG) == DMA1_FLAG_TC6) || \
                               ((FLAG) == DMA1_FLAG_HT4) || ((FLAG) == DMA1_FLAG_TE6) || \
                               ((FLAG) == DMA1_FLAG_GL5) || ((FLAG) == DMA1_FLAG_TC7) || \
                               ((FLAG) == DMA1_FLAG_HT5) || ((FLAG) == DMA1_FLAG_TE7))
/**
  * @}
  */

/** @defgroup DMA_Buffer_Size DMA_Buffer_Size
  * @{
  */

#define IS_DMA_BUFFER_SIZE(SIZE) (((SIZE) >= 0x1) && ((SIZE) < 0x10000))

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

/* Function used to set the DMA configuration to the default reset state ******/
void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx);

/* Initialization and Configuration functions *********************************/
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct);
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct);
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState);

/* Data Counter functions******************************************************/
void DMA_SetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx, uint16_t DataNumber);
uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx);

/* Interrupts and flags management functions **********************************/
void DMA_ITConfig(DMA_Channel_TypeDef* DMAy_Channelx, uint32_t DMA_IT, FunctionalState NewState);
FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG);
void DMA_ClearFlag(uint32_t DMAy_FLAG);
ITStatus DMA_GetITStatus(uint32_t DMAy_IT);
void DMA_ClearITPendingBit(uint32_t DMAy_IT);

#ifdef __cplusplus
}
#endif

#endif /*__HK32F0XXA_DMA_H */


