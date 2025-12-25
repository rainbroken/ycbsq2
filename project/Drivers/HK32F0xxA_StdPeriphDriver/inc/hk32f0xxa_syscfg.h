/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f0xxa_syscfg.h
* @brief:     Head file of syscfg module
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F0XXA_SYSCFG_H
#define __HK32F0XXA_SYSCFG_H

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

/** @addtogroup SYSCFG
  * @{
  */
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup SYSCFG_Exported_Constants SYSCFG_Exported_Constants
  * @{
  */

/** @defgroup SYSCFG_EXTI_Port_Sources SYSCFG_EXTI_Port_Sources
  * @{
  */
#define EXTI_PortSourceGPIOA       ((uint8_t)0x00)
#define EXTI_PortSourceGPIOB       ((uint8_t)0x01)
#define EXTI_PortSourceGPIOC       ((uint8_t)0x02)
#define EXTI_PortSourceGPIOD       ((uint8_t)0x03)
#define EXTI_PortSourceGPIOE       ((uint8_t)0x04)
#define EXTI_PortSourceGPIOF       ((uint8_t)0x05)

#define IS_EXTI_PORT_SOURCE(PORTSOURCE) (((PORTSOURCE) == EXTI_PortSourceGPIOA) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOB) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOC) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOD) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOE) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOF))
/**
  * @}
  */

/** @defgroup SYSCFG_EXTI_Pin_sources SYSCFG_EXTI_Pin_sources
  * @{
  */
#define EXTI_PinSource0            ((uint8_t)0x00)
#define EXTI_PinSource1            ((uint8_t)0x01)
#define EXTI_PinSource2            ((uint8_t)0x02)
#define EXTI_PinSource3            ((uint8_t)0x03)
#define EXTI_PinSource4            ((uint8_t)0x04)
#define EXTI_PinSource5            ((uint8_t)0x05)
#define EXTI_PinSource6            ((uint8_t)0x06)
#define EXTI_PinSource7            ((uint8_t)0x07)
#define EXTI_PinSource8            ((uint8_t)0x08)
#define EXTI_PinSource9            ((uint8_t)0x09)
#define EXTI_PinSource10           ((uint8_t)0x0A)
#define EXTI_PinSource11           ((uint8_t)0x0B)
#define EXTI_PinSource12           ((uint8_t)0x0C)
#define EXTI_PinSource13           ((uint8_t)0x0D)
#define EXTI_PinSource14           ((uint8_t)0x0E)
#define EXTI_PinSource15           ((uint8_t)0x0F)

#define IS_EXTI_PIN_SOURCE(PINSOURCE) (((PINSOURCE) == EXTI_PinSource0) || \
                                       ((PINSOURCE) == EXTI_PinSource1) || \
                                       ((PINSOURCE) == EXTI_PinSource2) || \
                                       ((PINSOURCE) == EXTI_PinSource3) || \
                                       ((PINSOURCE) == EXTI_PinSource4) || \
                                       ((PINSOURCE) == EXTI_PinSource5) || \
                                       ((PINSOURCE) == EXTI_PinSource6) || \
                                       ((PINSOURCE) == EXTI_PinSource7) || \
                                       ((PINSOURCE) == EXTI_PinSource8) || \
                                       ((PINSOURCE) == EXTI_PinSource9) || \
                                       ((PINSOURCE) == EXTI_PinSource10) || \
                                       ((PINSOURCE) == EXTI_PinSource11) || \
                                       ((PINSOURCE) == EXTI_PinSource12) || \
                                       ((PINSOURCE) == EXTI_PinSource13) || \
                                       ((PINSOURCE) == EXTI_PinSource14) || \
                                       ((PINSOURCE) == EXTI_PinSource15))
/**
  * @}
  */

/** @defgroup SYSCFG_Memory_Remap_Config SYSCFG_Memory_Remap_Config
  * @{
  */
#define SYSCFG_MemoryRemap_Flash                ((uint8_t)0x00)
#define SYSCFG_MemoryRemap_SystemMemory         ((uint8_t)0x01)
#define SYSCFG_MemoryRemap_SRAM                 ((uint8_t)0x03)


#define IS_SYSCFG_MEMORY_REMAP(REMAP) (((REMAP) == SYSCFG_MemoryRemap_Flash) || \
                                       ((REMAP) == SYSCFG_MemoryRemap_SystemMemory) || \
                                       ((REMAP) == SYSCFG_MemoryRemap_SRAM))

/**
  * @}
  */

/** @defgroup SYSCFG_DMA_Remap_Config SYSCFG_DMA_Remap_Config
  * @{
  */
#define SYSCFG_DMARemap_USART2              SYSCFG_CFGR1_USART2_DMA_RMP
#define SYSCFG_DMARemap_I2C1                SYSCFG_CFGR1_I2C_DMA_RMP
#define SYSCFG_DMARemap_TIM17               SYSCFG_CFGR1_TIM17_DMA_RMP    /* Remap TIM17 DMA requests from channel1 to channel2 */
#define SYSCFG_DMARemap_TIM16               SYSCFG_CFGR1_TIM16_DMA_RMP    /* Remap TIM16 DMA requests from channel3 to channel4 */
#define SYSCFG_DMARemap_USART1_Rx           SYSCFG_CFGR1_USART1_RX_DMA_RMP /* Remap USART1 Rx DMA requests from channel3 to channel5 */
#define SYSCFG_DMARemap_USART1_Tx           SYSCFG_CFGR1_USART1_TX_DMA_RMP /* Remap USART1 Tx DMA requests from channel2 to channel4 */
#define SYSCFG_DMARemap_ADC                SYSCFG_CFGR1_ADC_DMA_RMP      /* Remap ADC1 DMA requests from channel1 to channel2 */

#define IS_SYSCFG_DMA_REMAP(REMAP) (((REMAP) == SYSCFG_DMARemap_USART2) || \
                                    ((REMAP) == SYSCFG_DMARemap_I2C1) || \
                                    ((REMAP) == SYSCFG_DMARemap_TIM17) || \
                                    ((REMAP) == SYSCFG_DMARemap_TIM16) || \
                                    ((REMAP) == SYSCFG_DMARemap_USART1_Rx) || \
                                    ((REMAP) == SYSCFG_DMARemap_USART1_Tx) || \
                                    ((REMAP) == SYSCFG_DMARemap_ADC))

/**
  * @}
  */

/** @defgroup SYSCFG_I2C_FastModePlus_Config SYSCFG_I2C_FastModePlus_Config
  * @{
  */
#define SYSCFG_I2CFastModePlus_PB6       SYSCFG_CFGR1_I2C_PB6_FMP /* Enable Fast Mode Plus on PB6 */
#define SYSCFG_I2CFastModePlus_PB7       SYSCFG_CFGR1_I2C_PB7_FMP /* Enable Fast Mode Plus on PB7 */
#define SYSCFG_I2CFastModePlus_PB8       SYSCFG_CFGR1_I2C_PB8_FMP /* Enable Fast Mode Plus on PB8 */
#define SYSCFG_I2CFastModePlus_PB9       SYSCFG_CFGR1_I2C_PB9_FMP /* Enable Fast Mode Plus on PB9 */
#define SYSCFG_I2CFastModePlus_I2C1      SYSCFG_CFGR1_I2C1_FMP   /* Enable Fast Mode Plus on PB10, PB11, PF6 and PF7 */
#define SYSCFG_I2CFastModePlus_I2C2      SYSCFG_CFGR1_I2C2_FMP   /* Enable Fast Mode Plus on I2C2 pins */
#define SYSCFG_I2CFastModePlus_PA9       SYSCFG_CFGR1_I2C_PA9_FMP /* Enable Fast Mode Plus on PA9  */
#define SYSCFG_I2CFastModePlus_PA10      SYSCFG_CFGR1_I2C_PA10_FMP/* Enable Fast Mode Plus on PA10 */

#define IS_SYSCFG_I2C_FMP(PIN) (((PIN) == SYSCFG_I2CFastModePlus_PB6)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PB7)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PB8)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PB9)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_I2C1) || \
                                ((PIN) == SYSCFG_I2CFastModePlus_I2C2) || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PA9)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PA10))


/**
  * @}
  */

/** @defgroup SYSCFG_Lock_Config SYSCFG_Lock_Config
  * @{
  */
#define SYSCFG_Break_PVD                     SYSCFG_CFGR2_PVD_LOCK       /*!< Connects the PVD event to the Break Input of TIM1 */
#define SYSCFG_Break_SRAMParity              SYSCFG_CFGR2_SRAM_PARITY_LOCK  /*!< Connects the SRAM_PARITY error signal to the Break Input of TIM1 */
#define SYSCFG_Break_Lockup                  SYSCFG_CFGR2_LOCUP_LOCK       /*!< Connects Lockup output of CortexM0 to the break input of TIM1 */

#define IS_SYSCFG_LOCK_CONFIG(CONFIG) (((CONFIG) == SYSCFG_Break_PVD)        || \
                                       ((CONFIG) == SYSCFG_Break_SRAMParity) || \
                                       ((CONFIG) == SYSCFG_Break_Lockup))

/**
  * @}
  */

/** @defgroup SYSCFG_flags_definition SYSCFG_flags_definition
  * @{
  */

#define SYSCFG_FLAG_PEF               SYSCFG_CFGR2_SRAM_PEF

#define IS_SYSCFG_FLAG(FLAG) (((FLAG) == SYSCFG_FLAG_PEF))

/**
  * @}
  */

/** @defgroup SYSCFG_Vref_Sel_Config SYSCFG_Vref_Sel_Config
  * @{
  */

#define SYSCFG_Vref_Sel_VDDH                ((uint32_t)0x00000000)
#define SYSCFG_Vref_Sel_VREF12              ((uint32_t)0x40000000)

#define IS_SYSCFG_Vref_Sel(SEL) (((SEL) == SYSCFG_Vref_Sel_VDDH)||\
                                 ((SEL) == SYSCFG_Vref_Sel_VREF12))

/**
  * @}
  */

/** @defgroup SYSCFG_Vref_Buf_EN_Config SYSCFG_Vref_Buf_EN_Config
  * @{
  */

#define SYSCFG_Vref_Buf_EN               SYSCFG_CFGR2_VREF_BUF_EN
#define SYSCFG_Vref_Buf_DISABLE          ((uint32_t)0x00000000)

#define IS_SYSCFG_Vref_Buf(Buf) (((Buf) == SYSCFG_Vref_Buf_EN)||\
                                                                 ((Buf) == SYSCFG_Vref_Buf_DISABLE))

/**
  * @}
  */


/** @defgroup SYSCFG_RefVolCfg SYSCFG_RefVolCfg
  * @{
  */
#define SYSCFG_CRV_VO_0               ((uint32_t)0x00000000)
#define SYSCFG_CRV_VO_1               ((uint32_t)0x01000000)
#define SYSCFG_CRV_VO_2               ((uint32_t)0x02000000)
#define SYSCFG_CRV_VO_3               ((uint32_t)0x03000000)
#define SYSCFG_CRV_VO_4               ((uint32_t)0x04000000)
#define SYSCFG_CRV_VO_5               ((uint32_t)0x05000000)
#define SYSCFG_CRV_VO_6               ((uint32_t)0x06000000)
#define SYSCFG_CRV_VO_7               ((uint32_t)0x07000000)
#define SYSCFG_CRV_VO_8               ((uint32_t)0x08000000)
#define SYSCFG_CRV_VO_9               ((uint32_t)0x09000000)
#define SYSCFG_CRV_VO_10              ((uint32_t)0x0A000000)
#define SYSCFG_CRV_VO_11              ((uint32_t)0x0B000000)
#define SYSCFG_CRV_VO_12              ((uint32_t)0x0C000000)
#define SYSCFG_CRV_VO_13              ((uint32_t)0x0D000000)
#define SYSCFG_CRV_VO_14              ((uint32_t)0x0E000000)
#define SYSCFG_CRV_VO_15              ((uint32_t)0x0F000000)
#define SYSCFG_CRV_VO_16              ((uint32_t)0x10000000)
#define SYSCFG_CRV_VO_17              ((uint32_t)0x11000000)
#define SYSCFG_CRV_VO_18              ((uint32_t)0x12000000)
#define SYSCFG_CRV_VO_19              ((uint32_t)0x13000000)
#define SYSCFG_CRV_VO_20              ((uint32_t)0x14000000)
#define SYSCFG_CRV_VO_21              ((uint32_t)0x15000000)
#define SYSCFG_CRV_VO_22              ((uint32_t)0x16000000)
#define SYSCFG_CRV_VO_23              ((uint32_t)0x17000000)
#define SYSCFG_CRV_VO_24              ((uint32_t)0x18000000)
#define SYSCFG_CRV_VO_25              ((uint32_t)0x19000000)
#define SYSCFG_CRV_VO_26              ((uint32_t)0x1A000000)
#define SYSCFG_CRV_VO_27              ((uint32_t)0x1B000000)
#define SYSCFG_CRV_VO_28              ((uint32_t)0x1C000000)
#define SYSCFG_CRV_VO_29              ((uint32_t)0x1D000000)
#define SYSCFG_CRV_VO_30              ((uint32_t)0x1E000000)
#define SYSCFG_CRV_VO_31              ((uint32_t)0x1F000000)

#define IS_SYSCFG_CRV_VO(DIV) (((DIV) == SYSCFG_CRV_VO_0) || \
                               ((DIV) == SYSCFG_CRV_VO_1) || \
                                                             ((DIV) == SYSCFG_CRV_VO_2) || \
                                                             ((DIV) == SYSCFG_CRV_VO_3) || \
                                                             ((DIV) == SYSCFG_CRV_VO_4) || \
                                                             ((DIV) == SYSCFG_CRV_VO_5) || \
                                                             ((DIV) == SYSCFG_CRV_VO_6) || \
                                                             ((DIV) == SYSCFG_CRV_VO_7) || \
                                                             ((DIV) == SYSCFG_CRV_VO_8) || \
                                                             ((DIV) == SYSCFG_CRV_VO_9) || \
                                                             ((DIV) == SYSCFG_CRV_VO_10) || \
                                                             ((DIV) == SYSCFG_CRV_VO_11) || \
                                                             ((DIV) == SYSCFG_CRV_VO_12) || \
                                                             ((DIV) == SYSCFG_CRV_VO_13) || \
                                                             ((DIV) == SYSCFG_CRV_VO_14) || \
                                                             ((DIV) == SYSCFG_CRV_VO_15) || \
                                                             ((DIV) == SYSCFG_CRV_VO_16) || \
                                                             ((DIV) == SYSCFG_CRV_VO_17) || \
                                                             ((DIV) == SYSCFG_CRV_VO_18) || \
                                                             ((DIV) == SYSCFG_CRV_VO_19) || \
                                                             ((DIV) == SYSCFG_CRV_VO_20) || \
                                                             ((DIV) == SYSCFG_CRV_VO_21) || \
                                                             ((DIV) == SYSCFG_CRV_VO_22) || \
                                                             ((DIV) == SYSCFG_CRV_VO_23) || \
                                                             ((DIV) == SYSCFG_CRV_VO_24) || \
                                                             ((DIV) == SYSCFG_CRV_VO_25) || \
                                                             ((DIV) == SYSCFG_CRV_VO_26) || \
                                                             ((DIV) == SYSCFG_CRV_VO_27) || \
                                                             ((DIV) == SYSCFG_CRV_VO_28) || \
                                                             ((DIV) == SYSCFG_CRV_VO_29) || \
                                                             ((DIV) == SYSCFG_CRV_VO_30) || \
                               ((DIV) == SYSCFG_CRV_VO_31))

/**
  * @}
  */

/** @defgroup SYSCFG_TIM3_CH4_Remap_Config SYSCFG_TIM3_CH4_Remap_Config
  * @{
  */
#define SYSCFG_TIM3_CH4_Remap_0               ((uint32_t)0x00000000)
#define SYSCFG_TIM3_CH4_Remap_1               ((uint32_t)0x00200000)
#define SYSCFG_TIM3_CH4_Remap_2               ((uint32_t)0x00400000)
#define SYSCFG_TIM3_CH4_Remap_3               ((uint32_t)0x00600000)
#define SYSCFG_TIM3_CH4_Remap_4               ((uint32_t)0x00800000)
#define SYSCFG_TIM3_CH4_Remap_5               ((uint32_t)0x00A00000)
#define SYSCFG_TIM3_CH4_Remap_6               ((uint32_t)0x00C00000)
#define SYSCFG_TIM3_CH4_Remap_7               ((uint32_t)0x00E00000)

#define IS_SYSCFG_TIM3_CH4_Remap(REMAP) (((REMAP) == SYSCFG_TIM3_CH4_Remap_0) || \
                                                                                 ((REMAP) == SYSCFG_TIM3_CH4_Remap_1) || \
                                                                                 ((REMAP) == SYSCFG_TIM3_CH4_Remap_2) || \
                                                                                 ((REMAP) == SYSCFG_TIM3_CH4_Remap_3) || \
                                                                                 ((REMAP) == SYSCFG_TIM3_CH4_Remap_4) || \
                                                                                 ((REMAP) == SYSCFG_TIM3_CH4_Remap_5) || \
                                                                                 ((REMAP) == SYSCFG_TIM3_CH4_Remap_6) || \
                                                                                 ((REMAP) == SYSCFG_TIM3_CH4_Remap_7))

/**
  * @}
  */

/** @defgroup SYSCFG_AdcBufSel_Config SYSCFG_AdcBufSel_Config
  * @{
  */
#define SYSCFG_V_ADC_BUF_SELECT_0              ((uint32_t)0x00000000)
#define SYSCFG_V_ADC_BUF_SELECT_1              ((uint32_t)0x00080000)
#define SYSCFG_V_ADC_BUF_SELECT_2              ((uint32_t)0x00100000)
#define SYSCFG_V_ADC_BUF_SELECT_3              ((uint32_t)0x00180000)

#define IS_SYSCFG_V_ADC_BUF_SELECT(SELECT) (((SELECT) == SYSCFG_V_ADC_BUF_SELECT_0) || \
                                                                                      ((SELECT) == SYSCFG_V_ADC_BUF_SELECT_1) || \
                                                                                      ((SELECT) == SYSCFG_V_ADC_BUF_SELECT_2) || \
                                                                                      ((SELECT) == SYSCFG_V_ADC_BUF_SELECT_3))

/**
  * @}
  */

/** @defgroup SYSCFG_V_ADC_IN_18_SELECT_Config SYSCFG_V_ADC_IN_18_SELECT_Config
  * @{
  */
#define SYSCFG_V_ADC_IN_18_SELECT_0              ((uint32_t)0x00000000)
#define SYSCFG_V_ADC_IN_18_SELECT_1                ((uint32_t)0x00010000)
#define SYSCFG_V_ADC_IN_18_SELECT_2              ((uint32_t)0x00020000)
#define SYSCFG_V_ADC_IN_18_SELECT_3              ((uint32_t)0x00030000)
#define SYSCFG_V_ADC_IN_18_SELECT_4              ((uint32_t)0x00040000)
#define SYSCFG_V_ADC_IN_18_SELECT_5                ((uint32_t)0x00050000)
#define SYSCFG_V_ADC_IN_18_SELECT_6              ((uint32_t)0x00060000)
#define SYSCFG_V_ADC_IN_18_SELECT_7              ((uint32_t)0x00070000)

#define IS_SYSCFG_V_ADC_IN_18_SELECT(SELECT) (((SELECT) == SYSCFG_V_ADC_IN_18_SELECT_0) || \
                                                                                            ((SELECT) == SYSCFG_V_ADC_IN_18_SELECT_1) || \
                                                                                            ((SELECT) == SYSCFG_V_ADC_IN_18_SELECT_2) || \
                                                                                            ((SELECT) == SYSCFG_V_ADC_IN_18_SELECT_3) || \
                                                                                            ((SELECT) == SYSCFG_V_ADC_IN_18_SELECT_4) || \
                                                                                            ((SELECT) == SYSCFG_V_ADC_IN_18_SELECT_5) || \
                                                                                            ((SELECT) == SYSCFG_V_ADC_IN_18_SELECT_6) || \
                                                                                            ((SELECT) == SYSCFG_V_ADC_IN_18_SELECT_7))


/** @defgroup IRDA_ENV_SEL IRDA_ENV_SEL
  * @{
  */
#define SYSCFG_IRDA_ENV_SEL_TIM16     (SYSCFG_CFGR1_IR_MOD_0&SYSCFG_CFGR1_IR_MOD_1)    /* Timer16 is selected as IRDA Modulation envelope source */

#define IS_SYSCFG_IRDA_ENV(ENV) (((ENV) == SYSCFG_IRDA_ENV_SEL_TIM16))
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

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*  Function used to set the SYSCFG configuration to the default reset state **/
void SYSCFG_DeInit(void);

/* SYSCFG configuration functions *********************************************/
void SYSCFG_MemoryRemapConfig(uint32_t SYSCFG_MemoryRemap);
void SYSCFG_DMAChannelRemapConfig(uint32_t SYSCFG_DMARemap, FunctionalState NewState);
void SYSCFG_I2CFastModePlusConfig(uint32_t SYSCFG_I2CFastModePlus, FunctionalState NewState);
void SYSCFG_EXTILineConfig(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex);
uint32_t SYSCFG_GetPendingIT(uint32_t ITSourceLine);
void SYSCFG_BreakConfig(uint32_t SYSCFG_Break);
FlagStatus SYSCFG_GetFlagStatus(uint32_t SYSCFG_Flag);
void SYSCFG_ClearFlag(uint32_t SYSCFG_Flag);
void SYSCFG_VrefSel(uint32_t SYSCFG_VREF_SEL);
void SYSCFG_VrefConfig(uint32_t SYSCFG_VREF_SEL);
void SYSCFG_VrefBufCMD(uint32_t SYSCFG_Vref_Buf);
void SYSCFG_RefVolConfig(uint32_t CRV_VO_DIV);
void SYSCFG_Tim3Ch4RemapConfig(uint32_t SYSCFG_TIM3_CH4_REMAP);
void SYSCFG_AdcBufConfig(uint32_t SYSCFG_V_ADC_BUF);
void SYSCFG_AdcIn18VolConfig(uint32_t SYSCFG_V_ADC_IN_18);
#ifdef __cplusplus
}
#endif

#endif /*__HK32F0XXA_SYSCFG_H */


