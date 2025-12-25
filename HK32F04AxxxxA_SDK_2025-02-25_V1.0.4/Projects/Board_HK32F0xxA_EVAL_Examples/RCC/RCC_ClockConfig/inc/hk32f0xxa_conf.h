/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f0xxa_conf.h
* @brief:     conf program body
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F0XXA_CONF_H
#define __HK32F0XXA_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/*system clock source*/
#define SYSCLK_SRC_PLL          0x1
#define SYSCLK_SRC_HSI8M        0x2
#define SYSCLK_SRC_HSI14M       0x3
#define SYSCLK_SRC_HSI56M       0x4
#define SYSCLK_SRC_HSE          0x5
#define SYSCLK_SRC_HSE_BYPASS   0x6
#define SYSCLK_SRC_EXTCLK_IO    0x7
#define SYSCLK_SRC_LSI          0x8
#define SYSCLK_SRC_LSE          0x9
/* select sysclk source here */
#define SYSCLK_SOURCE    SYSCLK_SRC_HSE

// #define VECT_TAB_SRAM
#define VECT_TAB_OFFSET  0x0 /*!< Vector Table base offset field. This value must be a multiple of 0x200. */

#if(SYSCLK_SOURCE==SYSCLK_SRC_PLL)
//#define SYSCLK_HSE8M_PLL_FREQ_24MHz       24000000     //RCC_CFGR4.PPSS = 0(选择HSE) PREDIV = 1  PLLSRC = 1  PLLMUL = 3  8M/1 * 3 = 24M
//#define SYSCLK_HSE8M_PLL_FREQ_48MHz       48000000     //RCC_CFGR4.PPSS = 0(选择HSE) PREDIV = 1  PLLSRC = 1  PLLMUL = 6  8M/1 * 6 = 48M
//#define SYSCLK_HSE8M_PLL_FREQ_72MHz       72000000     //RCC_CFGR4.PPSS = 0(选择HSE) PREDIV = 1  PLLSRC = 1  PLLMUL = 9  8M/1 * 9 = 72M
#define SYSCLK_HSE8M_PLL_FREQ_96MHz         96000000     //RCC_CFGR4.PPSS = 0(选择HSE) PREDIV = 1  PLLSRC = 1  PLLMUL = 12 8M/1 * 3 = 96M

//#define SYSCLK_HSI_PLL_FREQ_48MHz         48000000     //HSI=8M RCC_CFGR4.PPSS = 0(选择HSE) PREDIV = 1  PLLSRC = 0（HSI/2） PLLMUL = 12 4M/1 * 12 = 48M
//#define SYSCLK_HSI_PLL_FREQ_64MHz         64000000     //HSI=8M RCC_CFGR4.PPSS = 1(选择HSI) PREDIV = 1  PLLSRC = 1          PLLMUL = 8  8M/1 * 8 = 64M
//#define SYSCLK_HSI_PLL_FREQ_72MHz         72000000     //HSI=8M RCC_CFGR4.PPSS = 1(选择HSI) PREDIV = 1  PLLSRC = 1          PLLMUL = 9  8M/1 * 9 = 72M
//#define SYSCLK_HSI_PLL_FREQ_96MHz         96000000     //HSI=8M RCC_CFGR4.PPSS = 1(选择HSI) PREDIV = 1  PLLSRC = 1          PLLMUL = 12 8M/1 * 8 = 96M

#elif(SYSCLK_SOURCE == SYSCLK_SRC_HSE | SYSCLK_SOURCE == SYSCLK_SRC_HSE_BYPASS)
#define SYSCLK_FREQ_HSE                    HSE_VALUE
#elif(SYSCLK_SOURCE == SYSCLK_SRC_HSI8M)
#define SYSCLK_FREQ_HSI_8M                 8000000
#elif(SYSCLK_SOURCE == SYSCLK_SRC_HSI14M)
#define SYSCLK_FREQ_HSI_14M                14000000
#elif(SYSCLK_SOURCE == SYSCLK_SRC_HSI56M)
#define SYSCLK_FREQ_HSI_56M                56000000
#elif(SYSCLK_SOURCE == SYSCLK_SRC_EXTCLK_IO)
#define SYSCLK_FREQ_EXTCLK                 8000000
#elif(SYSCLK_SOURCE == SYSCLK_SRC_LSI)
#define SYSCLK_FREQ_LSI             LSI_VALUE
#elif(SYSCLK_SOURCE == SYSCLK_SRC_LSE)
#define SYSCLK_FREQ_LSE             LSE_VALUE
#else
#error "Please select the target valid clock source used in your application (in hk32f0xxa_conf.h file)
#endif

/*
* @brief In the following line adjust the value of External High Speed oscillator (HSE)
  used in your application

  Tip: To avoid modifying this file each time you need to use different HSE, you
       can define the HSE value in your toolchain compiler preprocessor.
 */
#if !defined  (HSE_VALUE)
#define HSE_VALUE    ((uint32_t)8000000) /*!< Value of the External oscillator in Hz*/
#endif /* HSE_VALUE */

/**
 * @brief In the following line adjust the External High Speed oscillator (HSE) Startup
   Timeout value
   */
#if !defined  (HSE_STARTUP_TIMEOUT)
#define HSE_STARTUP_TIMEOUT   ((uint16_t)0xFFFF) /*!< Time out for HSE start up */
#endif /* HSE_STARTUP_TIMEOUT */

/**
 * @brief In the following line adjust the Internal High Speed oscillator (HSI) Startup
   Timeout value
   */
#if !defined  (HSI_STARTUP_TIMEOUT)
#define HSI_STARTUP_TIMEOUT   ((uint16_t)0xFFFF) /*!< Time out for HSI start up */
#endif /* HSI_STARTUP_TIMEOUT */

#if !defined  (HSI_VALUE)
#define HSI_VALUE  ((uint32_t)8000000) /*!< Value of the Internal High Speed oscillator in Hz.
                                             The real value may vary depending on the variations
                                             in voltage and temperature.  */
#endif /* HSI_VALUE */

#if !defined  (HSI14_VALUE)
#define HSI14_VALUE ((uint32_t)14000000) /*!< Value of the Internal High Speed oscillator for ADC in Hz.
                                             The real value may vary depending on the variations
                                             in voltage and temperature.  */
#endif /* HSI14_VALUE */

#if !defined  (HSI56_VALUE)
#define HSI56_VALUE ((uint32_t)56000000) /*!< Value of the Internal High Speed oscillator for USB in Hz.
                                             The real value may vary depending on the variations
                                             in voltage and temperature.  */
#endif /* HSI72_VALUE */

#if !defined  (LSI_VALUE)
#define LSI_VALUE  ((uint32_t)39550)    /*!< Value of the Internal Low Speed oscillator in Hz
                                             The real value may vary depending on the variations
                                             in voltage and temperature.  */
#endif /* LSI_VALUE */

#if !defined  (LSE_VALUE)
#define LSE_VALUE  ((uint32_t)32768)    /*!< Value of the External Low Speed oscillator in Hz */
#endif /* LSE_VALUE */

#if !defined  (EXTCLK_VALUE)
#define EXTCLK_VALUE    ((uint32_t)8000000) /*!< Value of the Internal oscillator in Hz*/
#endif /* LSE_VALUE */

/* Includes ------------------------------------------------------------------*/
/**
  * @brief Include module's header file
  */

/* Exported macro ------------------------------------------------------------*/
#if defined(HK32F030xxA)
#include "hk32f0xxa_adc.h"
#include "hk32f0xxa_dma.h"
#include "hk32f0xxa_dbgmcu.h"
#include "hk32f0xxa_crc.h"
#include "hk32f0xxa_exti.h"
#include "hk32f0xxa_flash.h"
#include "hk32f0xxa_gpio.h"
#include "hk32f0xxa_syscfg.h"
#include "hk32f0xxa_i2c.h"
#include "hk32f0xxa_iwdg.h"
#include "hk32f0xxa_pwr.h"
#include "hk32f0xxa_rcc.h"
#include "hk32f0xxa_rtc.h"
#include "hk32f0xxa_spi.h"
#include "hk32f0xxa_tim.h"
#include "hk32f0xxa_divsqrt.h"
#include "hk32f0xxa_usart.h"
#include "hk32f0xxa_wwdg.h"
#include "hk32f0xxa_misc.h"
//#include "hk32f0xxa_aes.h"
//#include "hk32f0xxa_hash.h"
//#include "hk32f0xxa_trng.h"
//#include "hk32f0xxa_emacc.h"
//#include "hk32f0xxa_can.h"
//#include "hk32f0xxa_clu.h"
#include "hk32f0xxa_lpuart.h"
//#include "hk32f0xxa_comp.h"
#elif defined(HK32F031xxA)
#include "hk32f0xxa_adc.h"
#include "hk32f0xxa_dma.h"
#include "hk32f0xxa_dbgmcu.h"
#include "hk32f0xxa_crc.h"
#include "hk32f0xxa_exti.h"
#include "hk32f0xxa_flash.h"
#include "hk32f0xxa_gpio.h"
#include "hk32f0xxa_syscfg.h"
#include "hk32f0xxa_i2c.h"
#include "hk32f0xxa_iwdg.h"
#include "hk32f0xxa_pwr.h"
#include "hk32f0xxa_rcc.h"
#include "hk32f0xxa_rtc.h"
#include "hk32f0xxa_spi.h"
#include "hk32f0xxa_tim.h"
#include "hk32f0xxa_divsqrt.h"
#include "hk32f0xxa_usart.h"
#include "hk32f0xxa_wwdg.h"
#include "hk32f0xxa_misc.h"
//#include "hk32f0xxa_aes.h"
//#include "hk32f0xxa_hash.h"
//#include "hk32f0xxa_trng.h"
//#include "hk32f0xxa_emacc.h"
//#include "hk32f0xxa_can.h"
//#include "hk32f0xxa_clu.h"
#include "hk32f0xxa_lpuart.h"
//#include "hk32f0xxa_comp.h"
#elif defined(HK32F072x)
#include "hk32f0xxa_adc.h"
#include "hk32f0xxa_dma.h"
#include "hk32f0xxa_dbgmcu.h"
#include "hk32f0xxa_crc.h"
#include "hk32f0xxa_exti.h"
#include "hk32f0xxa_flash.h"
#include "hk32f0xxa_gpio.h"
#include "hk32f0xxa_syscfg.h"
#include "hk32f0xxa_i2c.h"
#include "hk32f0xxa_iwdg.h"
#include "hk32f0xxa_pwr.h"
#include "hk32f0xxa_rcc.h"
#include "hk32f0xxa_rtc.h"
#include "hk32f0xxa_spi.h"
#include "hk32f0xxa_tim.h"
#include "hk32f0xxa_divsqrt.h"
#include "hk32f0xxa_usart.h"
#include "hk32f0xxa_wwdg.h"
#include "hk32f0xxa_misc.h"
//#include "hk32f0xxa_aes.h"
//#include "hk32f0xxa_hash.h"
//#include "hk32f0xxa_trng.h"
//#include "hk32f0xxa_emacc.h"
#include "hk32f0xxa_can.h"
//#include "hk32f0xxa_clu.h"
#include "hk32f0xxa_lpuart.h"
#include "hk32f0xxa_comp.h"
#elif defined(HK32F04AxxA)
#include "hk32f0xxa_adc.h"
#include "hk32f0xxa_dma.h"
#include "hk32f0xxa_dbgmcu.h"
#include "hk32f0xxa_crc.h"
#include "hk32f0xxa_exti.h"
#include "hk32f0xxa_flash.h"
#include "hk32f0xxa_gpio.h"
#include "hk32f0xxa_syscfg.h"
#include "hk32f0xxa_i2c.h"
#include "hk32f0xxa_iwdg.h"
#include "hk32f0xxa_pwr.h"
#include "hk32f0xxa_rcc.h"
#include "hk32f0xxa_rtc.h"
#include "hk32f0xxa_spi.h"
#include "hk32f0xxa_tim.h"
#include "hk32f0xxa_divsqrt.h"
#include "hk32f0xxa_usart.h"
#include "hk32f0xxa_wwdg.h"
#include "hk32f0xxa_misc.h"
#include "hk32f0xxa_aes.h"
#include "hk32f0xxa_hash.h"
#include "hk32f0xxa_trng.h"
#include "hk32f0xxa_emacc.h"
#include "hk32f0xxa_can.h"
#include "hk32f0xxa_clu.h"
#include "hk32f0xxa_lpuart.h"
#include "hk32f0xxa_comp.h"
#elif defined(HK32ASPIN010xx)
#include "hk32f0xxa_adc.h"
#include "hk32f0xxa_dma.h"
#include "hk32f0xxa_dbgmcu.h"
#include "hk32f0xxa_crc.h"
#include "hk32f0xxa_exti.h"
#include "hk32f0xxa_flash.h"
#include "hk32f0xxa_gpio.h"
#include "hk32f0xxa_syscfg.h"
#include "hk32f0xxa_i2c.h"
#include "hk32f0xxa_iwdg.h"
#include "hk32f0xxa_pwr.h"
#include "hk32f0xxa_rcc.h"
#include "hk32f0xxa_rtc.h"
#include "hk32f0xxa_spi.h"
#include "hk32f0xxa_tim.h"
#include "hk32f0xxa_divsqrt.h"
#include "hk32f0xxa_usart.h"
#include "hk32f0xxa_wwdg.h"
#include "hk32f0xxa_misc.h"
//#include "hk32f0xxa_aes.h"
//#include "hk32f0xxa_hash.h"
//#include "hk32f0xxa_trng.h"
#include "hk32f0xxa_emacc.h"
#include "hk32f0xxa_can.h"
#include "hk32f0xxa_clu.h"
#include "hk32f0xxa_lpuart.h"
#include "hk32f0xxa_comp.h"
#elif defined(HK32ASAFE010xx)
#include "hk32f0xxa_adc.h"
#include "hk32f0xxa_dma.h"
#include "hk32f0xxa_dbgmcu.h"
#include "hk32f0xxa_crc.h"
#include "hk32f0xxa_exti.h"
#include "hk32f0xxa_flash.h"
#include "hk32f0xxa_gpio.h"
#include "hk32f0xxa_syscfg.h"
#include "hk32f0xxa_i2c.h"
#include "hk32f0xxa_iwdg.h"
#include "hk32f0xxa_pwr.h"
#include "hk32f0xxa_rcc.h"
#include "hk32f0xxa_rtc.h"
#include "hk32f0xxa_spi.h"
#include "hk32f0xxa_tim.h"
#include "hk32f0xxa_divsqrt.h"
#include "hk32f0xxa_usart.h"
#include "hk32f0xxa_wwdg.h"
#include "hk32f0xxa_misc.h"
#include "hk32f0xxa_aes.h"
#include "hk32f0xxa_hash.h"
#include "hk32f0xxa_trng.h"
//#include "hk32f0xxa_emacc.h"
#include "hk32f0xxa_can.h"
//#include "hk32f0xxa_clu.h"
#include "hk32f0xxa_lpuart.h"
//#include "hk32f0xxa_comp.h"
#else
#error "Please select first the target HK32F0xxA device used in your application (in hk32f0xxa.h file)"
#endif



#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports
  *         the name of the source file and the source line number of the call
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
#define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void assert_failed(uint8_t* file, uint32_t line);
#else
#define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#ifdef __cplusplus
}
#endif  /* End of __cplusplus */

#endif /*__HK32F0XXA_CONF_H */
