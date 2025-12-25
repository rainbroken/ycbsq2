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

/* Exported define -----------------------------------------------------------*/
//chang it ,USARTx switch to USART1/USART2
#if 0

#define USARTx_CKIO_PORT                 GPIOA
#define USARTx_CK_PIN                    GPIO_Pin_4
#define USARTx_AF_CK_PIN                 GPIO_PinSource4
#define USARTx_CKIO_CLK_CMD              RCC_AHBPeriphClockCmd   /* CK IO clock Enable */
#define USARTx_CKIO_CLK                  RCC_AHBPeriph_GPIOA

#define USARTx_TXIO_PORT                 GPIOA
#define USARTx_TX_PIN                    GPIO_Pin_9
#define USARTx_AF_TX_PIN                 GPIO_PinSource9
#define USARTx_TXIO_CLK_CMD              RCC_AHBPeriphClockCmd   /* TX IO clock Enable */
#define USARTx_TXIO_CLK                  RCC_AHBPeriph_GPIOA

#define USARTx_RXIO_PORT                 GPIOA
#define USARTx_RX_PIN                    GPIO_Pin_10
#define USARTx_AF_RX_PIN                 GPIO_PinSource10
#define USARTx_RXIO_CLK_CMD              RCC_AHBPeriphClockCmd   /* RX IO clock Enable */
#define USARTx_RXIO_CLK                  RCC_AHBPeriph_GPIOA

#define USARTx_AF_SELECT                 GPIO_AF_1               /* AFIO SELECT Reference datasheet 6.8 table*/

#define USARTx                           EVAL_COM1
#define USARTx_IRQn                      USART1_IRQn
#define USARTx_IRQHandler                USART1_IRQHandler       /* USART1 interrupt handle */
#define USARTx_CLK_CMD                   RCC_APB2PeriphClockCmd  /* USART1 clock Enable */
#define USARTx_CLK                       RCC_APB2Periph_USART1

#define USARTx_TX_DMA_CHANNEL            DMA1_Channel2
#define USARTx_RX_DMA_CHANNEL            DMA1_Channel3

#define USARTx_TXRX_DMA_IRQ              DMA1_Channel2_3_IRQn
#define USARTx_DMATXRX_IRQHandle         DMA1_Channel2_3_IRQHandler

#define USARTx_TX_DMA_FLAG_TC            DMA1_FLAG_TC2
#define USARTx_TX_DMA_FLAG_GL            DMA1_FLAG_GL2
#define USARTx_RX_DMA_FLAG_TC            DMA1_FLAG_TC3
#define USARTx_RX_DMA_FLAG_GL            DMA1_FLAG_GL3

#else

#define USARTx_CKIO_PORT                 GPIOA
#define USARTx_CK_PIN                    GPIO_Pin_4
#define USARTx_AF_CK_PIN                 GPIO_PinSource4
#define USARTx_CKIO_CLK_CMD              RCC_AHBPeriphClockCmd   /* CK IO clock Enable */
#define USARTx_CKIO_CLK                  RCC_AHBPeriph_GPIOA

#define USARTx_TXIO_PORT                 GPIOA
#define USARTx_TX_PIN                    GPIO_Pin_2
#define USARTx_AF_TX_PIN                 GPIO_PinSource2
#define USARTx_TXIO_CLK_CMD              RCC_AHBPeriphClockCmd   /* TX IO clock Enable */
#define USARTx_TXIO_CLK                  RCC_AHBPeriph_GPIOA

#define USARTx_RXIO_PORT                 GPIOA
#define USARTx_RX_PIN                    GPIO_Pin_3
#define USARTx_AF_RX_PIN                 GPIO_PinSource3
#define USARTx_RXIO_CLK_CMD              RCC_AHBPeriphClockCmd   /* RX IO clock Enable */
#define USARTx_RXIO_CLK                  RCC_AHBPeriph_GPIOA

#define USARTx_AF_SELECT                 GPIO_AF_3               /* AFIO SELECT */

#define USARTx                           USART2
#define USARTx_IRQn                      USART2_IRQn
#define USARTx_IRQHandler                USART2_IRQHandler       /* USART2 interrupt handle */
#define USARTx_CLK_CMD                   RCC_APB1PeriphClockCmd  /* USART2 clock Enable */
#define USARTx_CLK                       RCC_APB1Periph_USART2

/* To use USART2 DMA,remapping needs to be enabled,Call the following function
SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_USART2_DMA_RMP,ENABLE); */
#define USARTx_TX_DMA_CHANNEL            DMA1_Channel6
#define USARTx_RX_DMA_CHANNEL            DMA1_Channel7

#define USARTx_TXRX_DMA_IRQ              DMA1_Channel4_7_IRQn
#define USARTx_DMATXRX_IRQHandle         DMA1_Channel4_7_IRQHandler

#define USARTx_TX_DMA_FLAG_TC            DMA1_FLAG_TC6
#define USARTx_TX_DMA_FLAG_GL            DMA1_FLAG_GL6
#define USARTx_RX_DMA_FLAG_TC            DMA1_FLAG_TC7
#define USARTx_RX_DMA_FLAG_GL            DMA1_FLAG_GL7

#endif

#define USARTx_TDR_ADDRESS               ((uint32_t)&USARTx->TDR)
#define USARTx_RDR_ADDRESS               ((uint32_t)&USARTx->RDR)

//USARTy USART2
#define USARTy_CKIO_PORT                 GPIOA
#define USARTy_CK_PIN                    GPIO_Pin_4
#define USARTy_AF_CK_PIN                 GPIO_PinSource4
#define USARTy_CKIO_CLK_CMD              RCC_AHBPeriphClockCmd   /* CK IO clock Enable */
#define USARTy_CKIO_CLK                  RCC_AHBPeriph_GPIOA

#define USARTy_TXIO_PORT                 GPIOA
#define USARTy_TX_PIN                    GPIO_Pin_2
#define USARTy_AF_TX_PIN                 GPIO_PinSource2
#define USARTy_TXIO_CLK_CMD              RCC_AHBPeriphClockCmd   /* TX IO clock Enable */
#define USARTy_TXIO_CLK                  RCC_AHBPeriph_GPIOA

#define USARTy_RXIO_PORT                 GPIOA
#define USARTy_RX_PIN                    GPIO_Pin_3
#define USARTy_AF_RX_PIN                 GPIO_PinSource3
#define USARTy_RXIO_CLK_CMD              RCC_AHBPeriphClockCmd   /* RX IO clock Enable */
#define USARTy_RXIO_CLK                  RCC_AHBPeriph_GPIOA

#define USARTy_AF_SELECT                 GPIO_AF_3               /* AFIO SELECT */

#define USARTy                           USART2
#define USARTy_IRQn                      USART2_IRQn
#define USARTy_IRQHandler                USART2_IRQHandler       /* USART2 interrupt handle */
#define USARTy_CLK_CMD                   RCC_APB1PeriphClockCmd  /* USART2 clock Enable */
#define USARTy_CLK                       RCC_APB1Periph_USART2

/* To use USART2 DMA,remapping needs to be enabled,Call the following function
   SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_USART2_DMA_RMP,ENABLE); */
#define USARTy_TX_DMA_CHANNEL            DMA1_Channel6
#define USARTy_RX_DMA_CHANNEL            DMA1_Channel7

#define USARTy_TXRX_DMA_IRQ              DMA1_Channel4_7_IRQn
#define USARTy_DMATXRX_IRQHandle         DMA1_Channel4_7_IRQHandler

#define USARTy_TX_DMA_FLAG_TC            DMA1_FLAG_TC6
#define USARTy_TX_DMA_FLAG_GL            DMA1_FLAG_GL6
#define USARTy_RX_DMA_FLAG_TC            DMA1_FLAG_TC7
#define USARTy_RX_DMA_FLAG_GL            DMA1_FLAG_GL7

/******************************************************************************/

//SPI1
#define SPIy                     SPI1
#define SPIy_GPIO                GPIOA
#define SPIy_CLK                 RCC_APB2Periph_SPI1
#define SPIy_CLK_CMD             RCC_APB2PeriphClockCmd

#define SPIy_CK_IO_PORT          GPIOA
#define SPIy_SCKPin              GPIO_Pin_5
#define SPIy_AF_CK_PIN           GPIO_PinSource5

#define SPIy_MISO_IO_PORT        GPIOA
#define SPIy_MISOPin             GPIO_Pin_6
#define SPIy_AF_MISO_PIN         GPIO_PinSource6

#define SPIy_MOSI_IO_PORT        GPIOA
#define SPIy_MOSIPin             GPIO_Pin_7
#define SPIy_AF_MOSI_PIN         GPIO_PinSource7

#define SPIy_AF_SELECT           GPIO_AF_0

//SPI IO CLOCK
#define SPIy_IOCLK_CMD           RCC_AHBPeriphClockCmd
#define SPIy_IOCLK               RCC_AHBPeriph_GPIOA

/******************************************************************************/
//I2Cx
#define I2C_COMx                          I2C1

#define I2C_COMx_SCL_PIN                  GPIO_Pin_6                  /* PB.06 */
#define I2C_COMx_SCL_IO_PORT              GPIOB                       /* GPIOB */
#define I2C_COMx_SCL_SOURCE               GPIO_PinSource6
#define I2C_COMx_SCL_AF                   GPIO_AF_1
#define I2C_COMx_SCLIO_CLKCMD             RCC_AHBPeriphClockCmd
#define I2C_COMx_SCL_IO_CLK               RCC_AHBPeriph_GPIOB

#define I2C_COMx_SDA_PIN                  GPIO_Pin_7                  /* PB.07 */
#define I2C_COMx_SDA_IO_PORT              GPIOB                       /* GPIOB */
#define I2C_COMx_SDA_SOURCE               GPIO_PinSource7
#define I2C_COMx_SDA_AF                   GPIO_AF_1
#define I2C_COMx_SDAIO_CLKCMD             RCC_AHBPeriphClockCmd
#define I2C_COMx_SDA_IO_CLK               RCC_AHBPeriph_GPIOB

//I2C CLOCK
#define I2C_COMx_CLK_CMD                  RCC_APB1PeriphClockCmd
#define I2C_COMx_CLK                      RCC_APB1Periph_I2C1
//I2C STOP MODE clock
#define I2C_COMx_STOPCLK                  RCC_I2C1CLK_HSI

/* I2C DMA Config need to remap config,Call the following function
   SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_I2C1_DMA_RMP,ENABLE); */
#define I2C_COMx_DMATX_Channel         DMA1_Channel6
#define I2C_COMx_DMATX_IRQ             DMA1_Channel4_7_IRQn
#define I2C_COMx_DMATX_IRQHandle       DMA1_Channel4_7_IRQHandler

#define I2C_COMx_DMARX_Channel         DMA1_Channel7
#define I2C_COMx_DMARX_IRQ             DMA1_Channel4_7_IRQn
#define I2C_COMx_DMARX_IRQHandle       DMA1_Channel4_7_IRQHandler

#define I2C_COMx_TX_DMA_FLAG_TC        DMA1_FLAG_TC6
#define I2C_COMx_TX_DMA_FLAG_GL        DMA1_FLAG_GL6
#define I2C_COMx_RX_DMA_FLAG_TC        DMA1_FLAG_TC7
#define I2C_COMx_RX_DMA_FLAG_GL        DMA1_FLAG_GL7


//slect open or close debug info
#define DEBUG_ON 1

//define to slect master or remove to slect slave
#define I2C_MASTER

/* Configure the OA1 address of the slave device
   NOTE: The real address in 7-bit address mode is SLAVEADDRESS<<1*/
#define SLAVEADDRESS                      ((uint8_t)0x33)

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* print with file name and number of lines you can close it by change DEBUG_ON is 0*/
#define debug(fmt,arg...)                if(DEBUG_ON)\
                                         printf("[%s:%d]\t"fmt"\r\n",__FILE__,__LINE__, ##arg)
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif  /* End of __cplusplus */

#endif /*__MAIN_H */

