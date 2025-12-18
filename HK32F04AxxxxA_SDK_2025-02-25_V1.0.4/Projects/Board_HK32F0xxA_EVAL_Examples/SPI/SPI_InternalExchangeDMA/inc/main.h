/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.h
* @brief:     Main program body
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

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

#ifdef USE_HK32F0xxA_EVAL
#include "hk32f0xxa_eval.h"
#include "hk32f0xxa_eval_i2c_ee.h"
#include "hk32f0xxa_eval_i2c_tsensor.h"
#include "hk32f0xxa_eval_spi_sd.h"
#endif /* USE_HK32F0xxA_EVAL */

/* Exported typedef ----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Exported define -----------------------------------------------------------*/

/* Communication boards SPIx Interface */
#define SPIx                             SPI1
#define SPIx_CLK                         RCC_APB2Periph_SPI1
#define SPIx_IRQn                        SPI1_IRQn
#define SPIx_IRQHandler                  SPI1_IRQHandler

#define SPIx_SCK_PIN                     GPIO_Pin_5
#define SPIx_SCK_GPIO_PORT               GPIOA
#define SPIx_SCK_GPIO_CLK                RCC_AHBPeriph_GPIOA
#define SPIx_SCK_SOURCE                  GPIO_PinSource5
#define SPIx_SCK_AF                      GPIO_AF_0

#define SPIx_MISO_PIN                    GPIO_Pin_4
#define SPIx_MISO_GPIO_PORT              GPIOB
#define SPIx_MISO_GPIO_CLK               RCC_AHBPeriph_GPIOB
#define SPIx_MISO_SOURCE                 GPIO_PinSource4
#define SPIx_MISO_AF                     GPIO_AF_0

#define SPIx_MOSI_PIN                    GPIO_Pin_7
#define SPIx_MOSI_GPIO_PORT              GPIOA
#define SPIx_MOSI_GPIO_CLK               RCC_AHBPeriph_GPIOA
#define SPIx_MOSI_SOURCE                 GPIO_PinSource7
#define SPIx_MOSI_AF                     GPIO_AF_0

#define SPIxx                            SPI2
#define SPIxx_CLK                        RCC_APB1Periph_SPI2
#define SPIxx_IRQn                       SPI2_IRQn
#define SPIxx_IRQHandler                 SPI2_IRQHandler

#define SPIxx_SCK_PIN                    GPIO_Pin_13
#define SPIxx_SCK_GPIO_PORT              GPIOB
#define SPIxx_SCK_GPIO_CLK               RCC_AHBPeriph_GPIOB
#define SPIxx_SCK_SOURCE                 GPIO_PinSource13
#define SPIxx_SCK_AF                     GPIO_AF_8

#define SPIxx_MISO_PIN                   GPIO_Pin_14
#define SPIxx_MISO_GPIO_PORT             GPIOB
#define SPIxx_MISO_GPIO_CLK              RCC_AHBPeriph_GPIOB
#define SPIxx_MISO_SOURCE                GPIO_PinSource14
#define SPIxx_MISO_AF                    GPIO_AF_8

#define SPIxx_MOSI_PIN                   GPIO_Pin_15
#define SPIxx_MOSI_GPIO_PORT             GPIOB
#define SPIxx_MOSI_GPIO_CLK              RCC_AHBPeriph_GPIOB
#define SPIxx_MOSI_SOURCE                GPIO_PinSource15
#define SPIxx_MOSI_AF                    GPIO_AF_8

#define SPIxx_Rx_DMA_Channel             DMA1_Channel4
#define SPIxx_DR_Base                    0x4000380C
#define SPIxx_Rx_DMA_FLAG                DMA1_FLAG_TC4

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif  /* End of __cplusplus */

#endif /*__MAIN_H */

