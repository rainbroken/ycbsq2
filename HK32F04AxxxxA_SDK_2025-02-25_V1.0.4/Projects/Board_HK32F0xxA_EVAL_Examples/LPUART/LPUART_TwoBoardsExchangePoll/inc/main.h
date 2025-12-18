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

/* Uncomment this line to Use BoardB */
//#define LPUART_BoardB

/******************************************************************************/
//chang it ,LPUART1  PB6/PB7

#define LPUARTx_TXIO_PORT                 GPIOB
#define LPUARTx_TX_PIN                    GPIO_Pin_6
#define LPUARTx_AF_TX_PIN                 GPIO_PinSource6
#define LPUARTx_TXIO_CLK_CMD              RCC_AHBPeriphClockCmd   /* TX IO clock Enable */
#define LPUARTx_TXIO_CLK                  RCC_AHBPeriph_GPIOB

#define LPUARTx_RXIO_PORT                 GPIOB
#define LPUARTx_RX_PIN                    GPIO_Pin_7
#define LPUARTx_AF_RX_PIN                 GPIO_PinSource7
#define LPUARTx_RXIO_CLK_CMD              RCC_AHBPeriphClockCmd   /* RX IO clock Enable */
#define LPUARTx_RXIO_CLK                  RCC_AHBPeriph_GPIOB

#define LPUARTx_AF_SELECT                 GPIO_AF_3               /* AFIO SELECT Reference datasheet 6.8 table*/

#define LPUARTx                           EVAL_COM1
#define LPUARTx_IRQn                      LPUART1_IRQn
#define LPUARTx_IRQHandler                LPUART1_IRQHandler       /* LPUART1 interrupt handle */
#define LPUARTx_CLK_CMD                   RCC_APB1PeriphClockCmd  /* LPUART1 clock Enable */
#define LPUARTx_CLK                       RCC_APB1Periph_LPUART1

#define LPUARTx_TX_DMA_CHANNEL            DMA1_Channel6
#define LPUARTx_RX_DMA_CHANNEL            DMA1_Channel7

#define LPUARTx_TXRX_DMA_IRQ              DMA1_Channel4_7_IRQn
#define LPUARTx_DMATXRX_IRQHandle         DMA1_Channel4_7_IRQHandler

#define LPUARTx_TX_DMA_FLAG_TC            DMA1_FLAG_TC6
#define LPUARTx_TX_DMA_FLAG_GL            DMA1_FLAG_GL6
#define LPUARTx_RX_DMA_FLAG_TC            DMA1_FLAG_TC7
#define LPUARTx_RX_DMA_FLAG_GL            DMA1_FLAG_GL7

#define LPUARTx_TDR_ADDRESS               ((uint32_t)&LPUART1->TDR)
#define LPUARTx_RDR_ADDRESS               ((uint32_t)&LPUART1->RDR)

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


/* USER_TIMEOUT value for waiting loops. This timeout is just guarantee that the
   application will not remain stuck if the LPUART communication is corrupted.
   You may modify this timeout value depending on CPU frequency and application
   conditions (interrupts routines, number of data to transfer, baudrate, CPU
   frequency...). */
#define USER_TIMEOUT                    ((uint32_t)0x64) /* Waiting 1s */

/* Joystick Commands */
#define CMD_RIGHT                        0x55
#define CMD_LEFT                         0xAA
#define CMD_UP                           0x33
#define CMD_DOWN                         0xCC
#define CMD_SEL                          0xFF

#define CMD_ACK                          0x66

/* Define numbers of bytes to transmit from TxBuffer */
#define CMD_RIGHT_SIZE                   0x01
#define CMD_LEFT_SIZE                    0x05
#define CMD_UP_SIZE                      0x14
#define CMD_DOWN_SIZE                    0x1E
#define CMD_SEL_SIZE                     TXBUFFERSIZE

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Delay(__IO uint32_t nCount);
#ifdef __cplusplus
}
#endif  /* End of __cplusplus */

#endif /*__MAIN_H */

