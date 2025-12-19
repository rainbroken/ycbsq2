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


/* Exported types ------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
// ADC
#define ADC_BAT                     ADC
#define ADC_CLK                     RCC_APB2Periph_ADC
#define ADC_GPIO_CLK                RCC_AHBPeriph_GPIOA
#define ADC_GPIO_PORT               GPIOA

// CAN
#define CANx                       CAN
#define CAN_CLK                    RCC_APB1Periph_CAN
#define CAN_RX_PIN                 GPIO_Pin_8
#define CAN_TX_PIN                 GPIO_Pin_9
#define CAN_GPIO_PORT              GPIOA
#define CAN_GPIO_CLK               RCC_AHBPeriph_GPIOB
#define CAN_AF_PORT                GPIO_AF_14
#define CAN_RX_SOURCE              GPIO_PinSource8
#define CAN_TX_SOURCE              GPIO_PinSource9

// USART
/*  USART1  */
#define USART1_TXIO_PORT                 GPIOA
#define USART1_TX_PIN                    GPIO_Pin_9
#define USART1_AF_TX_PIN                 GPIO_PinSource9
#define USART1_TXIO_CLK_CMD              RCC_AHBPeriphClockCmd   /* TX IO clock Enable */
#define USART1_TXIO_CLK                  RCC_AHBPeriph_GPIOA
             
#define USART1_RXIO_PORT                 GPIOA
#define USART1_RX_PIN                    GPIO_Pin_10
#define USART1_AF_RX_PIN                 GPIO_PinSource10
#define USART1_RXIO_CLK_CMD              RCC_AHBPeriphClockCmd   /* RX IO clock Enable */
#define USART1_RXIO_CLK                  RCC_AHBPeriph_GPIOA
             
#define USART1_AF_SELECT                 GPIO_AF_1               /* AFIO SELECT Reference datasheet 6.8 table*/
             
#define USART1_CLK_CMD                   RCC_APB1PeriphClockCmd  /* USART2 clock Enable */
#define USART1_CLK                       RCC_APB1Periph_USART1

/*  USART2  */
#define USART2_TXIO_PORT                 GPIOA
#define USART2_TX_PIN                    GPIO_Pin_2
#define USART2_AF_TX_PIN                 GPIO_PinSource2
#define USART2_TXIO_CLK_CMD              RCC_AHBPeriphClockCmd   /* TX IO clock Enable */
#define USART2_TXIO_CLK                  RCC_AHBPeriph_GPIOA
             
#define USART2_RXIO_PORT                 GPIOA
#define USART2_RX_PIN                    GPIO_Pin_3
#define USART2_AF_RX_PIN                 GPIO_PinSource3
#define USART2_RXIO_CLK_CMD              RCC_AHBPeriphClockCmd   /* RX IO clock Enable */
#define USART2_RXIO_CLK                  RCC_AHBPeriph_GPIOA
             
#define USART2_AF_SELECT                 GPIO_AF_3               /* AFIO SELECT */
             
#define USART2_CLK_CMD                   RCC_APB1PeriphClockCmd  /* USART2 clock Enable */
#define USART2_CLK                       RCC_APB1Periph_USART2

//I2Cx
#define I2C_COMx                          I2C1
#define I2C_COMx_CLK                      RCC_APB1Periph_I2C1

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
//#define I2C_COMx_CLK                      RCC_APB1Periph_I2C1


/*  USART2  */



/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#ifdef __cplusplus
}
#endif  /* End of __cplusplus */

#endif /*__MAIN_H */

