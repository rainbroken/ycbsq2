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

//#ifdef USE_HK32F0xxA_EVAL
//#include "hk32f0xxa_eval.h"
//#include "hk32f0xxa_eval_i2c_ee.h"
//#include "hk32f0xxa_eval_i2c_tsensor.h"
//#include "hk32f0xxa_eval_spi_sd.h"
//#endif /* USE_HK32F0xxA_EVAL */


/* Exported types ------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define TOUCH_Pin GPIO_Pin_0
#define TOUCH_GPIO_Port GPIOA
#define CAT1_TX_Pin GPIO_Pin_2
#define CAT1_TX_GPIO_Port GPIOA
#define CAT1_RX_Pin GPIO_Pin_3
#define CAT1_RX_GPIO_Port GPIOA
#define BAT_DET_Pin GPIO_Pin_4
#define BAT_DET_GPIO_Port GPIOA
#define RGB_Pin GPIO_Pin_0
#define RGB_GPIO_Port GPIOB
#define AMP_SHUT_Pin GPIO_Pin_1
#define AMP_SHUT_GPIO_Port GPIOB
#define VBUS_DET_Pin GPIO_Pin_2
#define VBUS_DET_GPIO_Port GPIOB
#define GPS_TX_Pin GPIO_Pin_10
#define GPS_TX_GPIO_Port GPIOB
#define GPS_RX_Pin GPIO_Pin_11
#define GPS_RX_GPIO_Port GPIOB
#define CHG_EN_Pin GPIO_Pin_12
#define CHG_EN_GPIO_Port GPIOB
#define CHG_DET_Pin GPIO_Pin_13
#define CHG_DET_GPIO_Port GPIOB
#define CHG_STB_Pin GPIO_Pin_14
#define CHG_STB_GPIO_Port GPIOB
#define V_5V_EN_Pin GPIO_Pin_15
#define V_5V_EN_GPIO_Port GPIOB
#define CAT1_RST_Pin GPIO_Pin_8
#define CAT1_RST_GPIO_Port GPIOA
#define CAT1_EN_Pin GPIO_Pin_11
#define CAT1_EN_GPIO_Port GPIOA
#define CAT1_PWRK_Pin GPIO_Pin_12
#define CAT1_PWRK_GPIO_Port GPIOA
#define CAN_EN_Pin GPIO_Pin_5
#define CAN_EN_GPIO_Port GPIOB
#define TTS_BUSY_Pin GPIO_Pin_6
#define TTS_BUSY_GPIO_Port GPIOB
#define TTS_DAT_Pin GPIO_Pin_7
#define TTS_DAT_GPIO_Port GPIOB


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
#define CAN_GPIO_PORT              GPIOB
#define CAN_GPIO_CLK               RCC_AHBPeriph_GPIOB
#define CAN_AF_PORT                GPIO_AF_14
#define CAN_RX_SOURCE              GPIO_PinSource8
#define CAN_TX_SOURCE              GPIO_PinSource9

// USART
/*  USART1  */
#define USART1_COM                       USART1
#define USART1_CLK                       RCC_APB2Periph_USART1
#define USART1_CLK_CMD                   RCC_APB1PeriphClockCmd  /* USART2 clock Enable */

#define USART1_TXIO_PORT                 GPIOA
#define USART1_TX_PIN                    GPIO_Pin_9
#define USART1_AF_TX_SOURCE              GPIO_PinSource9
#define USART1_TXIO_CLK_CMD              RCC_AHBPeriphClockCmd   /* TX IO clock Enable */
#define USART1_TXIO_CLK                  RCC_AHBPeriph_GPIOA
#define USART1_TX_AF                     GPIO_AF_1
             
#define USART1_RXIO_PORT                 GPIOA
#define USART1_RX_PIN                    GPIO_Pin_10
#define USART1_AF_RX_SOURCE              GPIO_PinSource10
#define USART1_RXIO_CLK_CMD              RCC_AHBPeriphClockCmd   /* RX IO clock Enable */
#define USART1_RXIO_CLK                  RCC_AHBPeriph_GPIOA
#define USART1_RX_AF                     GPIO_AF_1
             
#define USART1_AF_SELECT                 GPIO_AF_1               /* AFIO SELECT Reference datasheet 6.8 table*/
             

/*  USART2  */
#define USART2_COM                       USART2
#define USART2_CLK                       RCC_APB1Periph_USART2
#define USART2_CLK_CMD                   RCC_APB1PeriphClockCmd  /* USART2 clock Enable */

#define USART2_TXIO_PORT                 GPIOA
#define USART2_TX_PIN                    GPIO_Pin_2
#define USART2_AF_TX_SOURCE              GPIO_PinSource2
#define USART2_TXIO_CLK_CMD              RCC_AHBPeriphClockCmd   /* TX IO clock Enable */
#define USART2_TXIO_CLK                  RCC_AHBPeriph_GPIOA
#define USART2_TX_AF                     GPIO_AF_3
             
#define USART2_RXIO_PORT                 GPIOA
#define USART2_RX_PIN                    GPIO_Pin_3
#define USART2_AF_RX_SOURCE              GPIO_PinSource3
#define USART2_RXIO_CLK_CMD              RCC_AHBPeriphClockCmd   /* RX IO clock Enable */
#define USART2_RXIO_CLK                  RCC_AHBPeriph_GPIOA
#define USART2_RX_AF                     GPIO_AF_3
             
#define USART2_AF_SELECT                 GPIO_AF_3               /* AFIO SELECT */

//I2Cx
#define I2C2_COMx                          I2C2
#define I2C2_COMx_CLK                      RCC_APB1Periph_I2C2
#define I2C2_RCC_CLK_HSI                   RCC_I2C2CLK_HSI
           
#define I2C2_COMx_SCL_PIN                  GPIO_Pin_10                  /* PB.06 */
#define I2C2_COMx_SCL_IO_PORT              GPIOB                       /* GPIOB */
#define I2C2_COMx_SCL_SOURCE               GPIO_PinSource10
#define I2C2_COMx_SCL_AF                   GPIO_AF_10
#define I2C2_COMx_SCLIO_CLKCMD             RCC_APB1PeriphClockCmd
#define I2C2_COMx_SCL_IO_CLK               RCC_AHBPeriph_GPIOB
           
#define I2C2_COMx_SDA_PIN                  GPIO_Pin_11                  /* PB.07 */
#define I2C2_COMx_SDA_IO_PORT              GPIOB                       /* GPIOB */
#define I2C2_COMx_SDA_SOURCE               GPIO_PinSource11
#define I2C2_COMx_SDA_AF                   GPIO_AF_11
#define I2C2_COMx_SDAIO_CLKCMD             RCC_APB1PeriphClockCmd
#define I2C2_COMx_SDA_IO_CLK               RCC_AHBPeriph_GPIOB

//I2C CLOCK
#define I2C2_COMx_CLK_CMD                  RCC_APB1PeriphClockCmd

//TIM3
#define TIM3_CLK                            RCC_APB1Periph_TIM3


/*  USART2  */



/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#ifdef __cplusplus
}
#endif  /* End of __cplusplus */

#endif /*__MAIN_H */

