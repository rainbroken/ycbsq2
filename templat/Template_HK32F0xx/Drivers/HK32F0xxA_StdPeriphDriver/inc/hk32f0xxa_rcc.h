/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f0xxa_rcc.h
* @brief:     This file contains all the functions prototypes for the RCC
*             firmware library.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F0XXA_RCC_H
#define __HK32F0XXA_RCC_H

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

/** @addtogroup RCC
  * @{
  */

/** @defgroup RCC_Exported_Types RCC_Exported_Types
  * @{
  */
typedef struct
{
    uint32_t SYSCLK_Frequency;
    uint32_t HCLK_Frequency;
    uint32_t PCLK_Frequency;
    uint32_t I2C1CLK_Frequency;
    uint32_t I2C2CLK_Frequency;
    uint32_t USART1CLK_Frequency;
    uint32_t USART2CLK_Frequency;
    uint32_t LPUART1CLK_Frequency;
    uint32_t LPTIM1CLK_Frequency;
    uint32_t RTCCLK_Frequency;
    uint32_t FLASHCLK_Frequency;
} RCC_ClocksTypeDef;
/**
  * @}
  */
/* Exported constants --------------------------------------------------------*/

/** @defgroup RCC_Exported_Constants RCC_Exported_Constants
  * @{
  */

/** @defgroup RCC_HSE_configuration RCC_HSE_configuration
  * @{
  */

#define RCC_HSE_OFF                      ((uint8_t)0x00)
#define RCC_HSE_ON                       ((uint8_t)0x01)
#define RCC_HSE_Bypass                   ((uint8_t)0x05)
#define IS_RCC_HSE(HSE) (((HSE) == RCC_HSE_OFF) || ((HSE) == RCC_HSE_ON) || \
                         ((HSE) == RCC_HSE_Bypass))

/**
  * @}
  */

/** @defgroup RCC_PLL_Clock_Source RCC_PLL_Clock_Source
  * @{
  */

#define RCC_PLLSource_HSI_Div2           ((uint8_t)0x00)
#define RCC_PLLSource_HSE                ((uint8_t)0x10)
#define RCC_PLLSource_HSI                ((uint8_t)0x11)

#define IS_RCC_PLL_SOURCE(SOURCE) (((SOURCE) == RCC_PLLSource_HSI_Div2) || \
                                   ((SOURCE) == RCC_PLLSource_HSI)      || \
                                   ((SOURCE) == RCC_PLLSource_HSE))

/**
  * @}
  */

/** @defgroup RCC_PLL_Multiplication_Factor RCC_PLL_Multiplication_Factor
  * @{
  */

#define RCC_PLLMul_2                    ((uint32_t)0x00 << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_3                    ((uint32_t)0x01 << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_4                    ((uint32_t)0x02 << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_5                    ((uint32_t)0x03 << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_6                    ((uint32_t)0x04 << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_7                    ((uint32_t)0x05 << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_8                    ((uint32_t)0x06 << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_9                    ((uint32_t)0x07 << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_10                   ((uint32_t)0x08 << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_11                   ((uint32_t)0x09 << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_12                   ((uint32_t)0x0A << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_13                   ((uint32_t)0x0B << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_14                   ((uint32_t)0x0C << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_15                   ((uint32_t)0x0D << RCC_CFGR_PLLMUL_Pos)
#define RCC_PLLMul_16                   ((uint32_t)0x0E << RCC_CFGR_PLLMUL_Pos)

#define IS_RCC_PLL_MUL(MUL) (((MUL) == RCC_PLLMul_2) || ((MUL) == RCC_PLLMul_3)   || \
                             ((MUL) == RCC_PLLMul_4) || ((MUL) == RCC_PLLMul_5)   || \
                             ((MUL) == RCC_PLLMul_6) || ((MUL) == RCC_PLLMul_7)   || \
                             ((MUL) == RCC_PLLMul_8) || ((MUL) == RCC_PLLMul_9)   || \
                             ((MUL) == RCC_PLLMul_10) || ((MUL) == RCC_PLLMul_11) || \
                             ((MUL) == RCC_PLLMul_12) || ((MUL) == RCC_PLLMul_13) || \
                             ((MUL) == RCC_PLLMul_14) || ((MUL) == RCC_PLLMul_15) || \
                             ((MUL) == RCC_PLLMul_16))
/**
  * @}
  */

/** @defgroup RCC_PREDIV1_division_factor RCC_PREDIV1_division_factor
  * @{
  */
#define  RCC_PREDIV1_Div1               ((uint32_t)0x00 << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV1_Div2               ((uint32_t)0x01 << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV1_Div3               ((uint32_t)0x02 << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV1_Div4               ((uint32_t)0x03 << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV1_Div5               ((uint32_t)0x04 << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV1_Div6               ((uint32_t)0x05 << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV1_Div7               ((uint32_t)0x06 << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV1_Div8               ((uint32_t)0x07 << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV1_Div9               ((uint32_t)0x08 << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV1_Div10              ((uint32_t)0x09 << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV1_Div11              ((uint32_t)0x0A << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV1_Div12              ((uint32_t)0x0B << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV1_Div13              ((uint32_t)0x0C << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV1_Div14              ((uint32_t)0x0D << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV1_Div15              ((uint32_t)0x0E << RCC_CFGR2_PREDIV_Pos)
#define  RCC_PREDIV1_Div16              ((uint32_t)0x0F << RCC_CFGR2_PREDIV_Pos)

#define IS_RCC_PREDIV1(PREDIV1) (((PREDIV1) == RCC_PREDIV1_Div1) || ((PREDIV1) == RCC_PREDIV1_Div2) || \
                                 ((PREDIV1) == RCC_PREDIV1_Div3) || ((PREDIV1) == RCC_PREDIV1_Div4) || \
                                 ((PREDIV1) == RCC_PREDIV1_Div5) || ((PREDIV1) == RCC_PREDIV1_Div6) || \
                                 ((PREDIV1) == RCC_PREDIV1_Div7) || ((PREDIV1) == RCC_PREDIV1_Div8) || \
                                 ((PREDIV1) == RCC_PREDIV1_Div9) || ((PREDIV1) == RCC_PREDIV1_Div10) || \
                                 ((PREDIV1) == RCC_PREDIV1_Div11) || ((PREDIV1) == RCC_PREDIV1_Div12) || \
                                 ((PREDIV1) == RCC_PREDIV1_Div13) || ((PREDIV1) == RCC_PREDIV1_Div14) || \
                                 ((PREDIV1) == RCC_PREDIV1_Div15) || ((PREDIV1) == RCC_PREDIV1_Div16))
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Source RCC_System_Clock_Source
  * @{
  */

#define RCC_SYSCLKSource_HSI             0x00
#define RCC_SYSCLKSource_HSE             0x01
#define RCC_SYSCLKSource_PLLCLK          0x02
#define IS_RCC_SYSCLK_SOURCE(SOURCE) (((SOURCE) == RCC_SYSCLKSource_HSI)   || \
                                      ((SOURCE) == RCC_SYSCLKSource_HSE)   || \
                                      ((SOURCE) == RCC_SYSCLKSource_PLLCLK))

#define RCC_SYSCLKSource_LSE             0x10
#define RCC_SYSCLKSource_LSI             0x11
#define RCC_SYSCLKSource_HSI56           0x12
#define RCC_SYSCLKSource_HSI14           0x13
#define RCC_SYSCLKSource_EXTCLK          0x14
#define IS_RCC_SYSCLK_SOURCE1(SOURCE) (((SOURCE) == RCC_SYSCLKSource_LSE)   || \
                                      ((SOURCE) == RCC_SYSCLKSource_LSI)   || \
                                      ((SOURCE) == RCC_SYSCLKSource_HSI56)   || \
                                      ((SOURCE) == RCC_SYSCLKSource_HSI14)   || \
                                      ((SOURCE) == RCC_SYSCLKSource_EXTCLK))

/**
  * @}
  */

/** @defgroup RCC_AHB_Clock_Source RCC_AHB_Clock_Source
  * @{
  */

#define RCC_SYSCLK_Div1                  ((uint32_t)0x00 << RCC_CFGR_HPRE_Pos)
#define RCC_SYSCLK_Div2                  ((uint32_t)0x08 << RCC_CFGR_HPRE_Pos)
#define RCC_SYSCLK_Div4                  ((uint32_t)0x09 << RCC_CFGR_HPRE_Pos)
#define RCC_SYSCLK_Div8                  ((uint32_t)0x0A << RCC_CFGR_HPRE_Pos)
#define RCC_SYSCLK_Div16                 ((uint32_t)0x0B << RCC_CFGR_HPRE_Pos)
#define RCC_SYSCLK_Div64                 ((uint32_t)0x0C << RCC_CFGR_HPRE_Pos)
#define RCC_SYSCLK_Div128                ((uint32_t)0x0D << RCC_CFGR_HPRE_Pos)
#define RCC_SYSCLK_Div256                ((uint32_t)0x0E << RCC_CFGR_HPRE_Pos)
#define RCC_SYSCLK_Div512                ((uint32_t)0x0F << RCC_CFGR_HPRE_Pos)
#define IS_RCC_HCLK(HCLK) (((HCLK) == RCC_SYSCLK_Div1) || ((HCLK) == RCC_SYSCLK_Div2) || \
                           ((HCLK) == RCC_SYSCLK_Div4) || ((HCLK) == RCC_SYSCLK_Div8) || \
                           ((HCLK) == RCC_SYSCLK_Div16) || ((HCLK) == RCC_SYSCLK_Div64) || \
                           ((HCLK) == RCC_SYSCLK_Div128) || ((HCLK) == RCC_SYSCLK_Div256) || \
                           ((HCLK) == RCC_SYSCLK_Div512))
/**
  * @}
  */

/** @defgroup RCC_APB_Clock_Source RCC_APB_Clock_Source
  * @{
  */

#define RCC_HCLK_Div1                    ((uint32_t)0x00)
#define RCC_HCLK_Div2                    ((uint32_t)0x04)
#define RCC_HCLK_Div4                    ((uint32_t)0x05)
#define RCC_HCLK_Div8                    ((uint32_t)0x06)
#define RCC_HCLK_Div16                   ((uint32_t)0x07)
#define IS_RCC_PCLK(PCLK) (((PCLK) == RCC_HCLK_Div1) || ((PCLK) == RCC_HCLK_Div2) || \
                           ((PCLK) == RCC_HCLK_Div4) || ((PCLK) == RCC_HCLK_Div8) || \
                           ((PCLK) == RCC_HCLK_Div16))
/**
  * @}
  */


/** @defgroup RCC_I2C_clock_source RCC_I2C_clock_source
  * @{
  */

#define RCC_I2C1CLK_HSI                    ((uint8_t)0x00)
#define RCC_I2C1CLK_SYSCLK                 ((uint8_t)0x01)
#define RCC_I2C1CLK_PCLK                   ((uint8_t)0x11)

#define IS_RCC_I2C1CLK(I2C1CLK) (((I2C1CLK) == RCC_I2C1CLK_HSI)    ||  \
                                 ((I2C1CLK) == RCC_I2C1CLK_SYSCLK) || \
                                 ((I2C1CLK) == RCC_I2C1CLK_PCLK))

#define RCC_I2C2CLK_PCLK                   ((uint32_t)0x00000000)
#define RCC_I2C2CLK_HSI                    ((uint32_t)0x04000000)
#define RCC_I2C2CLK_SYSCLK                 ((uint32_t)0x08000000)

#define IS_RCC_I2C2CLK(I2C2CLK) (((I2C2CLK) == RCC_I2C2CLK_PCLK)    ||  \
                               ((I2C2CLK) == RCC_I2C2CLK_HSI) || \
                               ((I2C2CLK) == RCC_I2C2CLK_SYSCLK))

/**
  * @}
  */

/** @defgroup RCC_USART_clock_source RCC_USART_clock_source
  * @{
  */

#define RCC_USART1CLK_PCLK                  ((uint32_t)0x00)
#define RCC_USART1CLK_SYSCLK                ((uint32_t)0x01)
#define RCC_USART1CLK_LSE                   ((uint32_t)0x02)
#define RCC_USART1CLK_HSI                   ((uint32_t)0x03)

#define RCC_USART2CLK_PCLK                  ((uint32_t)0x00)
#define RCC_USART2CLK_SYSCLK                ((uint32_t)0x01)
#define RCC_USART2CLK_LSE                   ((uint32_t)0x02)
#define RCC_USART2CLK_HSI                   ((uint32_t)0x03)

#define IS_RCC_USARTCLK(USARTCLK) (((USARTCLK) == RCC_USART1CLK_PCLK)   || \
                                   ((USARTCLK) == RCC_USART1CLK_SYSCLK) || \
                                   ((USARTCLK) == RCC_USART1CLK_LSE)    || \
                                   ((USARTCLK) == RCC_USART1CLK_HSI)    || \
                                   ((USARTCLK) == RCC_USART2CLK_PCLK)   || \
                                   ((USARTCLK) == RCC_USART2CLK_SYSCLK) || \
                                   ((USARTCLK) == RCC_USART2CLK_LSE)    || \
                                   ((USARTCLK) == RCC_USART2CLK_HSI))


#define RCC_LPUART1CLK_PCLK                  ((uint32_t)0x00)
#define RCC_LPUART1CLK_SYSCLK                ((uint32_t)0x01)
#define RCC_LPUART1CLK_LSE                   ((uint32_t)0x02)
#define RCC_LPUART1CLK_HSI                   ((uint32_t)0x03)

#define IS_RCC_LPUARTCLK(LPUSRTCLK) (((LPUSRTCLK) == RCC_LPUART1CLK_PCLK)   || \
                                   ((LPUSRTCLK) == RCC_LPUART1CLK_SYSCLK) || \
                                   ((LPUSRTCLK) == RCC_LPUART1CLK_LSE)    || \
                                   ((LPUSRTCLK) == RCC_LPUART1CLK_HSI))


#define RCC_LPTIMCLK_PCLK                  ((uint32_t)0x00)
#define RCC_LPTIMCLK_SYSCLK                 ((uint32_t)0x01)
#define RCC_LPTIMCLK_LSE                    ((uint32_t)0x02)
#define RCC_LPTIMCLK_HSI                   ((uint32_t)0x03)

#define IS_RCC_LPTIMCLK(LPTIMCLK) (((LPTIMCLK) == RCC_LPTIMCLK_PCLK)   || \
                                   ((LPTIMCLK) == RCC_LPTIMCLK_SYSCLK) || \
                                   ((LPTIMCLK) == RCC_LPTIMCLK_LSE)    || \
                                   ((LPTIMCLK) == RCC_LPTIMCLK_HSI))

/** @defgroup RCC_Interrupt_Source RCC_Interrupt_Source
  * @{
  */

#define RCC_IT_LSIRDY                    ((uint32_t)0x01)
#define RCC_IT_LSERDY                    ((uint32_t)0x02)
#define RCC_IT_HSIRDY                    ((uint32_t)0x04)
#define RCC_IT_HSERDY                    ((uint32_t)0x08)
#define RCC_IT_PLLRDY                    ((uint32_t)0x10)
#define RCC_IT_HSI14RDY                  ((uint32_t)0x20)
#define RCC_IT_CSSHSE                    ((uint32_t)0x80)
#define RCC_IT_LSEFAIL                   ((uint32_t)0x80)
#define RCC_IT_CSSLSE                    ((uint32_t)0x40000000)
#define IS_RCC_IT(IT) ((((IT) & (uint32_t)0x80) == 0x00) && ((IT) != 0x00))

#define IS_RCC_GET_IT(IT) (((IT) == RCC_IT_LSIRDY) || ((IT) == RCC_IT_LSERDY) || \
                           ((IT) == RCC_IT_HSIRDY) || ((IT) == RCC_IT_HSERDY) || \
                           ((IT) == RCC_IT_PLLRDY) || ((IT) == RCC_IT_HSI14RDY) || \
                           ((IT) == RCC_IT_LSEFAIL) ||  ((IT) == RCC_IT_CSSHSE) ||  ((IT) == RCC_IT_CSSLSE))

#define IS_RCC_CLEAR_IT(IT) ((IT) != 0x00)

/**
  * @}
  */

/** @defgroup RCC_LSE_Configuration RCC_LSE_Configuration
  * @{
  */

#define RCC_LSE_OFF                      ((uint32_t)0x00000000)
#define RCC_LSE_ON                       RCC_BDCR_LSEON
#define RCC_LSE_Bypass                   ((uint32_t)(RCC_BDCR_LSEON | RCC_BDCR_LSEBYP))
#define IS_RCC_LSE(LSE) (((LSE) == RCC_LSE_OFF) || ((LSE) == RCC_LSE_ON) || \
                         ((LSE) == RCC_LSE_Bypass))
/**
  * @}
  */

/** @defgroup RCC_RTC_Clock_Source RCC_RTC_Clock_Source
  * @{
  */

#define RCC_RTCCLKSource_LSE             RCC_BDCR_RTCSEL_0
#define RCC_RTCCLKSource_LSI             RCC_BDCR_RTCSEL_1
#define RCC_RTCCLKSource_HSE_Div32       RCC_BDCR_RTCSEL

#define IS_RCC_RTCCLK_SOURCE(SOURCE) (((SOURCE) == RCC_RTCCLKSource_LSE) || \
                                      ((SOURCE) == RCC_RTCCLKSource_LSI) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div32))
/**
  * @}
  */

/** @defgroup RCC_LSE_Drive_Configuration RCC_LSE_Drive_Configuration
  * @{
  */

#define RCC_LSEDrive_Low                 ((uint32_t)0x00000000)
#define RCC_LSEDrive_MediumLow           RCC_BDCR_LSEDRV_0
#define RCC_LSEDrive_MediumHigh          RCC_BDCR_LSEDRV_1
#define RCC_LSEDrive_High                RCC_BDCR_LSEDRV
#define IS_RCC_LSE_DRIVE(DRIVE) (((DRIVE) == RCC_LSEDrive_Low) || ((DRIVE) == RCC_LSEDrive_MediumLow) || \
                                 ((DRIVE) == RCC_LSEDrive_MediumHigh) || ((DRIVE) == RCC_LSEDrive_High))
/**
  * @}
  */

/** @defgroup RCC_AHB_Peripherals RCC_AHB_Peripherals
  * @{
  */

#define RCC_AHBPeriph_GPIOA               RCC_AHBENR_IOPAEN
#define RCC_AHBPeriph_GPIOB               RCC_AHBENR_IOPBEN
#define RCC_AHBPeriph_GPIOC               RCC_AHBENR_IOPCEN
#define RCC_AHBPeriph_GPIOD               RCC_AHBENR_IOPDEN
#define RCC_AHBPeriph_GPIOF               RCC_AHBENR_IOPFEN
#define RCC_AHBPeriph_DIVSQ               RCC_AHBENR_DVSQEN
#define RCC_AHBPeriph_CRC                 RCC_AHBENR_CRCEN
#define RCC_AHBPeriph_FLITF               RCC_AHBENR_FLITFEN
#define RCC_AHBPeriph_SRAM                RCC_AHBENR_SRAMEN
#define RCC_AHBPeriph_DMA1                RCC_AHBENR_DMAEN


#define IS_RCC_AHB_PERIPH(PERIPH) ((((PERIPH) & 0xFFA1FEAA) == 0x00) && ((PERIPH) != 0x00))
#define IS_RCC_AHB_RST_PERIPH(PERIPH) ((((PERIPH) & 0xFFA1FEAA) == 0x00) && ((PERIPH) != 0x00))

/**
  * @}
  */

/** @defgroup RCC_APB2_Peripherals RCC_APB2_Peripherals
  * @{
  */

#define RCC_APB2Periph_SYSCFG            RCC_APB2ENR_SYSCFGEN
#define RCC_APB2Periph_ADC              RCC_APB2ENR_ADCEN
#define RCC_APB2Periph_TIM1              RCC_APB2ENR_TIM1EN
#define RCC_APB2Periph_SPI1              RCC_APB2ENR_SPI1EN
#define RCC_APB2Periph_USART1            RCC_APB2ENR_USART1EN
#define RCC_APB2Periph_TIM15             RCC_APB2ENR_TIM15EN
#define RCC_APB2Periph_TIM16             RCC_APB2ENR_TIM16EN
#define RCC_APB2Periph_TIM17             RCC_APB2ENR_TIM17EN
#define RCC_APB2Periph_DBGMCU            RCC_APB2ENR_DBGMCUEN

#define IS_RCC_APB2_PERIPH(PERIPH) ((((PERIPH) & 0xFFB8A5FE) == 0x00) && ((PERIPH) != 0x00))

/**
  * @}
  */

/** @defgroup RCC_AHB2_Peripherals RCC_AHB2_Peripherals
  * @{
  */

#define RCC_AHB2Periph_EMACC            RCC_AHBENR2_EAACCEN
#define RCC_AHB2Periph_TRNG             RCC_AHBENR2_TRNGEN
#define RCC_AHB2Periph_HASH             RCC_AHBENR2_HASHEN
#define RCC_AHB2Periph_AES              RCC_AHBENR2_AESEN
#define RCC_AHB2Periph_DVSQ             RCC_AHBENR2_DVSQEN


#define IS_RCC_AHB2_PERIPH(PERIPH) ((((PERIPH) & 0xFFFFFDF0) == 0x00) && ((PERIPH) != 0x00))

/**
  * @}
  */

/** @defgroup RCC_APB1_Peripherals RCC_APB1_Peripherals
  * @{
  */

#define RCC_APB1Periph_TIM2              RCC_APB1ENR_TIM2EN
#define RCC_APB1Periph_TIM3              RCC_APB1ENR_TIM3EN
#define RCC_APB1Periph_TIM6              RCC_APB1ENR_TIM6EN
#define RCC_APB1Periph_TIM14             RCC_APB1ENR_TIM14EN
#define RCC_APB1Periph_WWDG              RCC_APB1ENR_WWDGEN
#define RCC_APB1Periph_SPI2              RCC_APB1ENR_SPI2EN
#define RCC_APB1Periph_USART2            RCC_APB1ENR_USART2EN
#define RCC_APB1Periph_I2C1              RCC_APB1ENR_I2C1EN
#define RCC_APB1Periph_I2C2              RCC_APB1ENR_I2C2EN
#define RCC_APB1Periph_CAN               RCC_APB1ENR_CANEN
#define RCC_APB1Periph_LPUART1           RCC_APB1ENR_LPUARTEN
#define RCC_APB1Periph_PWR               RCC_APB1ENR_PWREN
#define RCC_APB1Periph_LPTIM1            RCC_APB1ENR_LPTIMEN

#define IS_RCC_APB1_PERIPH(PERIPH) ((((PERIPH) & 0x6C9DB6EC) == 0x00) && ((PERIPH) != 0x00))
/**
  * @}
  */

/** @defgroup RCC_MCO_Clock_Source RCC_MCO_Clock_Source
  * @{
  */

#define RCC_MCOSource_NoClock            ((uint8_t)0x00)
#define RCC_MCOSource_HSI14              ((uint8_t)0x01)
#define RCC_MCOSource_LSI                ((uint8_t)0x02)
#define RCC_MCOSource_LSE                ((uint8_t)0x03)
#define RCC_MCOSource_SYSCLK             ((uint8_t)0x04)
#define RCC_MCOSource_HSI                ((uint8_t)0x05)
#define RCC_MCOSource_HSE                ((uint8_t)0x06)
#define RCC_MCOSource_PLLCLK_Div2        ((uint8_t)0x07)


#define IS_RCC_MCO_SOURCE(SOURCE) (((SOURCE) == RCC_MCOSource_NoClock) || ((SOURCE) == RCC_MCOSource_HSI14)      || \
                                   ((SOURCE) == RCC_MCOSource_SYSCLK)  || ((SOURCE) == RCC_MCOSource_HSI)        || \
                                   ((SOURCE) == RCC_MCOSource_HSE)     || ((SOURCE) == RCC_MCOSource_PLLCLK_Div2)|| \
                                   ((SOURCE) == RCC_MCOSource_LSI)     || ((SOURCE) == RCC_MCOSource_LSE))
/**
  * @}
  */

/** @defgroup RCC_MCOPrescaler RCC_MCOPrescaler
  * @{
  */

#define RCC_MCOPrescaler_1            ((uint32_t)0x00 << RCC_CFGR_MCOPRE_Pos)
#define RCC_MCOPrescaler_2            ((uint32_t)0x01 << RCC_CFGR_MCOPRE_Pos)
#define RCC_MCOPrescaler_4            ((uint32_t)0x02 << RCC_CFGR_MCOPRE_Pos)
#define RCC_MCOPrescaler_8            ((uint32_t)0x03 << RCC_CFGR_MCOPRE_Pos)
#define RCC_MCOPrescaler_16           ((uint32_t)0x04 << RCC_CFGR_MCOPRE_Pos)
#define RCC_MCOPrescaler_32           ((uint32_t)0x05 << RCC_CFGR_MCOPRE_Pos)
#define RCC_MCOPrescaler_64           ((uint32_t)0x06 << RCC_CFGR_MCOPRE_Pos)
#define RCC_MCOPrescaler_128          ((uint32_t)0x07 << RCC_CFGR_MCOPRE_Pos)

#define IS_RCC_MCO_PRESCALER(PRESCALER) (((PRESCALER) == RCC_MCOPrescaler_1)  || \
                                         ((PRESCALER) == RCC_MCOPrescaler_2)  || \
                                         ((PRESCALER) == RCC_MCOPrescaler_4)  || \
                                         ((PRESCALER) == RCC_MCOPrescaler_8)  || \
                                         ((PRESCALER) == RCC_MCOPrescaler_16) || \
                                         ((PRESCALER) == RCC_MCOPrescaler_32) || \
                                         ((PRESCALER) == RCC_MCOPrescaler_64) || \
                                         ((PRESCALER) == RCC_MCOPrescaler_128))

/**
  * @}
  */

/** @defgroup RCC_Flag RCC_Flag
  * @{
  */
#define RCC_FLAG_HSIRDY                  ((uint8_t)0x01)
#define RCC_FLAG_HSERDY                  ((uint8_t)0x11)
#define RCC_FLAG_PLLRDY                  ((uint8_t)0x19)
#define RCC_FLAG_LSERDY                  ((uint8_t)0x21)
#define RCC_FLAG_LSIRDY                  ((uint8_t)0x41)
#define RCC_FLAG_V15PWRRSTF              ((uint8_t)0x57)
#define RCC_FLAG_OBLRST                  ((uint8_t)0x59)
#define RCC_FLAG_PINRST                  ((uint8_t)0x5A)
#define RCC_FLAG_PORRST                  ((uint8_t)0x5B)
#define RCC_FLAG_SFTRST                  ((uint8_t)0x5C)
#define RCC_FLAG_IWDGRST                 ((uint8_t)0x5D)
#define RCC_FLAG_WWDGRST                 ((uint8_t)0x5E)
#define RCC_FLAG_LPWRRST                 ((uint8_t)0x5F)
#define RCC_FLAG_HSI14RDY                ((uint8_t)0x61)

#define IS_RCC_FLAG(FLAG) (((FLAG) == RCC_FLAG_HSIRDY)  || ((FLAG) == RCC_FLAG_HSERDY)  || \
                           ((FLAG) == RCC_FLAG_PLLRDY)  || ((FLAG) == RCC_FLAG_LSERDY)  || \
                           ((FLAG) == RCC_FLAG_LSIRDY)  || ((FLAG) == RCC_FLAG_OBLRST)  || \
                           ((FLAG) == RCC_FLAG_PINRST)  || ((FLAG) == RCC_FLAG_PORRST)  || \
                           ((FLAG) == RCC_FLAG_SFTRST)  || ((FLAG) == RCC_FLAG_IWDGRST) || \
                           ((FLAG) == RCC_FLAG_WWDGRST) || ((FLAG) == RCC_FLAG_LPWRRST) || \
                           ((FLAG) == RCC_FLAG_HSI14RDY)|| \
                           ((FLAG) == RCC_FLAG_V15PWRRSTF))

#define IS_RCC_HSI_CALIBRATION_VALUE(VALUE) ((VALUE) <= 0x1F)
#define IS_RCC_HSI14_CALIBRATION_VALUE(VALUE) ((VALUE) <= 0x1F)

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

/* Function used to set the RCC clock configuration to the default reset state */
void RCC_DeInit(void);

/* Internal/external clocks, PLL, CSS and MCO configuration functions *********/
void RCC_HSEConfig(uint8_t RCC_HSE);
ErrorStatus RCC_WaitForHSEStartUp(void);
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue);
void RCC_HSICmd(FunctionalState NewState);
void RCC_AdjustHSI14CalibrationValue(uint8_t HSI14CalibrationValue);
void RCC_HSI14Cmd(FunctionalState NewState);
void RCC_LSEConfig(uint32_t RCC_LSE);
void RCC_LSEDriveConfig(uint32_t RCC_LSEDrive);
void RCC_LSICmd(FunctionalState NewState);
void RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul);
void RCC_PLLCmd(FunctionalState NewState);
void RCC_HSI56Cmd(FunctionalState NewState);
void RCC_PREDIV1Config(uint32_t RCC_PREDIV1_Div);
void RCC_ClockSecuritySystemCmd(FunctionalState NewState);
void RCC_MCOConfig(uint8_t RCC_MCOSource, uint32_t RCC_MCOPrescaler);

/* System, AHB and APB busses clocks configuration functions ******************/
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource);
uint8_t RCC_GetSYSCLKSource(void);
void RCC_HCLKConfig(uint32_t RCC_SYSCLK);
void RCC_PCLKConfig(uint32_t RCC_HCLK);

void RCC_I2CCLKConfig(uint32_t RCC_I2CCLK);
void RCC_I2C2CLKConfig(uint32_t RCC_I2CCLK);
void RCC_USART1CLKConfig(uint32_t RCC_USART2CLK);
void RCC_USART2CLKConfig(uint32_t RCC_USART1CLK);
void RCC_LPTIMCLKConfig(uint32_t RCC_LPTIMCLK);
void RCC_LPUARTCLKConfig(uint32_t RCC_LPUARTCLK);

void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);

/* Peripheral clocks configuration functions **********************************/
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource);
void RCC_RTCCLKCmd(FunctionalState NewState);
void RCC_BackupResetCmd(FunctionalState NewState);

void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_AHB2PeriphClockCmd(uint32_t RCC_AHB2Periph, FunctionalState NewState);
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);

void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_AHB2PeriphResetCmd(uint32_t RCC_AHB2Periph, FunctionalState NewState);
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);

/* Interrupts and flags management functions **********************************/
void RCC_ITConfig(uint32_t RCC_IT, FunctionalState NewState);
FlagStatus RCC_GetFlagStatus(uint32_t RCC_FLAG);
void RCC_ClearFlag(void);
ITStatus RCC_GetITStatus(uint32_t RCC_IT);
void RCC_ClearITPendingBit(uint32_t RCC_IT);

#ifdef __cplusplus
}
#endif

#endif /*__HK32F0XXA_RCC_H */


