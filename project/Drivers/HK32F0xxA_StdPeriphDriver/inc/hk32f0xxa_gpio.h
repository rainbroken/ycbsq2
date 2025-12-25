/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f0xxa_gpio.h
* @brief:     GPIO initialization and configuration
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F0XXA_GPIO_H
#define __HK32F0XXA_GPIO_H

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

#define IS_GPIO_ALL_PERIPH(PERIPH) (((PERIPH) == GPIOA) || \
                                    ((PERIPH) == GPIOB) || \
                                    ((PERIPH) == GPIOC) || \
                                    ((PERIPH) == GPIOD) || \
                                    ((PERIPH) == GPIOF))

#define IS_GPIO_LIST_PERIPH(PERIPH) (((PERIPH) == GPIOA) || \
                                     ((PERIPH) == GPIOB))

#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_Mode_IN)|| ((MODE) == GPIO_Mode_OUT) || \
                            ((MODE) == GPIO_Mode_AF)|| ((MODE) == GPIO_Mode_AN))


#define IS_GPIO_OTYPE(OTYPE) (((OTYPE) == GPIO_OType_PP) || ((OTYPE) == GPIO_OType_OD))

#define IS_GPIO_SPEED(SPEED) (((SPEED) == GPIO_Speed_Level_1) || ((SPEED) == GPIO_Speed_Level_2) || \
                              ((SPEED) == GPIO_Speed_Level_3) || ((SPEED) == GPIO_Speed_UltraHigh))

#define IS_GPIO_PUPD(PUPD) (((PUPD) == GPIO_PuPd_NOPULL) || ((PUPD) == GPIO_PuPd_UP) || \
                            ((PUPD) == GPIO_PuPd_DOWN))

#define IS_GPIO_BIT_ACTION(ACTION) (((ACTION) == Bit_RESET) || ((ACTION) == Bit_SET))

#define IS_GPIO_PIN(PIN) ((PIN) != (uint16_t)0x00)

#define IS_GET_GPIO_PIN(PIN) (((PIN) == GPIO_Pin_0) || \
                              ((PIN) == GPIO_Pin_1) || \
                              ((PIN) == GPIO_Pin_2) || \
                              ((PIN) == GPIO_Pin_3) || \
                              ((PIN) == GPIO_Pin_4) || \
                              ((PIN) == GPIO_Pin_5) || \
                              ((PIN) == GPIO_Pin_6) || \
                              ((PIN) == GPIO_Pin_7) || \
                              ((PIN) == GPIO_Pin_8) || \
                              ((PIN) == GPIO_Pin_9) || \
                              ((PIN) == GPIO_Pin_10) || \
                              ((PIN) == GPIO_Pin_11) || \
                              ((PIN) == GPIO_Pin_12) || \
                              ((PIN) == GPIO_Pin_13) || \
                              ((PIN) == GPIO_Pin_14) || \
                              ((PIN) == GPIO_Pin_15))

#define IS_GPIO_PIN_SOURCE(PINSOURCE) (((PINSOURCE) == GPIO_PinSource0) || \
                                       ((PINSOURCE) == GPIO_PinSource1) || \
                                       ((PINSOURCE) == GPIO_PinSource2) || \
                                       ((PINSOURCE) == GPIO_PinSource3) || \
                                       ((PINSOURCE) == GPIO_PinSource4) || \
                                       ((PINSOURCE) == GPIO_PinSource5) || \
                                       ((PINSOURCE) == GPIO_PinSource6) || \
                                       ((PINSOURCE) == GPIO_PinSource7) || \
                                       ((PINSOURCE) == GPIO_PinSource8) || \
                                       ((PINSOURCE) == GPIO_PinSource9) || \
                                       ((PINSOURCE) == GPIO_PinSource10) || \
                                       ((PINSOURCE) == GPIO_PinSource11) || \
                                       ((PINSOURCE) == GPIO_PinSource12) || \
                                       ((PINSOURCE) == GPIO_PinSource13) || \
                                       ((PINSOURCE) == GPIO_PinSource14) || \
                                       ((PINSOURCE) == GPIO_PinSource15))

#define IS_GPIO_AF(AF)   (((AF) == GPIO_AF_0)  || ((AF) == GPIO_AF_1)  || \
                                                    ((AF) == GPIO_AF_2)  || ((AF) == GPIO_AF_3)  || \
                                                    ((AF) == GPIO_AF_4)  || ((AF) == GPIO_AF_5)  || \
                                                    ((AF) == GPIO_AF_6)  || ((AF) == GPIO_AF_7)  || \
                                                    ((AF) == GPIO_AF_8)  || ((AF) == GPIO_AF_9)  || \
                                                    ((AF) == GPIO_AF_10) || ((AF) == GPIO_AF_11) || \
                                                    ((AF) == GPIO_AF_12) || ((AF) == GPIO_AF_13) || \
                                                    ((AF) == GPIO_AF_14) || ((AF) == GPIO_AF_15))




/** @addtogroup GPIO
  * @{
  */
/* Exported types ------------------------------------------------------------*/

/** @defgroup GPIO_Exported_Types GPIO_Exported_Types
  * @{
  */

/**
  * @brief  Configuration_Mode_enumeration
  */
typedef enum
{
    GPIO_Mode_IN   = 0x00, /*!< GPIO Input Mode              */
    GPIO_Mode_OUT  = 0x01, /*!< GPIO Output Mode             */
    GPIO_Mode_AF   = 0x02, /*!< GPIO Alternate function Mode */
    GPIO_Mode_AN   = 0x03  /*!< GPIO Analog In/Out Mode      */
} GPIOMode_TypeDef;

/**
  * @brief  Configuration Schmit
  */

typedef enum
{
    GPIO_Schmit_Disable = 0x1,
    GPIO_Schmit_Enable = 0x0,
} GPIOSchmit_TypeDef;


/**
  * @brief  Output_type_enumeration
  */

typedef enum
{
    GPIO_OType_PP = 0x00,
    GPIO_OType_OD = 0x01
} GPIOOType_TypeDef;

/**
  * @brief  Output_Maximum_frequency_enumeration
  */
typedef enum
{
    GPIO_Speed_Level_1  = 0x00,  /*!< I/O output speed: Low 2 MHz */
    GPIO_Speed_Level_2  = 0x01,  /*!< I/O output speed: Medium 10 MHz */
    GPIO_Speed_Level_3  = 0x03,  /*!< I/O output speed: High 50 MHz */
    GPIO_Speed_Level_4  = 0x04  /*!< I/O output speed: Ultra High */
} GPIOSpeed_TypeDef;

/**
  * @brief  Configuration_Pull-Up_Pull-Down_enumeration
  */
typedef enum
{
    GPIO_PuPd_NOPULL = 0x00,
    GPIO_PuPd_UP     = 0x01,
    GPIO_PuPd_DOWN   = 0x02
} GPIOPuPd_TypeDef;
/**
  * @brief  Bit_SET_and_Bit_RESET_enumeration
  */
typedef enum
{
    Bit_RESET = 0,
    Bit_SET
} BitAction;

/**
  * @brief  GPIO Init structure definition
  */

typedef struct
{
    uint32_t GPIO_Pin;              /*!< Specifies the GPIO pins to be configured.
                                       This parameter can be any value of @ref GPIO_Pins_Define */

    GPIOMode_TypeDef GPIO_Mode;     /*!< Specifies the operating mode for the selected pins.
                                       This parameter can be a value of @ref GPIOMode_TypeDef   */

    GPIOSpeed_TypeDef GPIO_Speed;   /*!< Specifies the speed for the selected pins.
                                       This parameter can be a value of @ref GPIOSpeed_TypeDef  */

    GPIOOType_TypeDef GPIO_OType;   /*!< Specifies the operating output type for the selected pins.
                                       This parameter can be a value of @ref GPIOOType_TypeDef  */

    GPIOPuPd_TypeDef GPIO_PuPd;     /*!< Specifies the operating Pull-up/Pull down for the selected pins.
                                       This parameter can be a value of @ref GPIOPuPd_TypeDef   */
    GPIOSchmit_TypeDef GPIO_Schmit;

} GPIO_InitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup GPIO_Exported_Constants GPIO_Exported_Constants
  * @{
  */

/** @defgroup GPIO_Pins_Define GPIO_Pins_Define
  * @{
  */
#define GPIO_Pin_0                 ((uint16_t)0x0001)  /*!< Pin 0 selected    */
#define GPIO_Pin_1                 ((uint16_t)0x0002)  /*!< Pin 1 selected    */
#define GPIO_Pin_2                 ((uint16_t)0x0004)  /*!< Pin 2 selected    */
#define GPIO_Pin_3                 ((uint16_t)0x0008)  /*!< Pin 3 selected    */
#define GPIO_Pin_4                 ((uint16_t)0x0010)  /*!< Pin 4 selected    */
#define GPIO_Pin_5                 ((uint16_t)0x0020)  /*!< Pin 5 selected    */
#define GPIO_Pin_6                 ((uint16_t)0x0040)  /*!< Pin 6 selected    */
#define GPIO_Pin_7                 ((uint16_t)0x0080)  /*!< Pin 7 selected    */
#define GPIO_Pin_8                 ((uint16_t)0x0100)  /*!< Pin 8 selected    */
#define GPIO_Pin_9                 ((uint16_t)0x0200)  /*!< Pin 9 selected    */
#define GPIO_Pin_10                ((uint16_t)0x0400)  /*!< Pin 10 selected   */
#define GPIO_Pin_11                ((uint16_t)0x0800)  /*!< Pin 11 selected   */
#define GPIO_Pin_12                ((uint16_t)0x1000)  /*!< Pin 12 selected   */
#define GPIO_Pin_13                ((uint16_t)0x2000)  /*!< Pin 13 selected   */
#define GPIO_Pin_14                ((uint16_t)0x4000)  /*!< Pin 14 selected   */
#define GPIO_Pin_15                ((uint16_t)0x8000)  /*!< Pin 15 selected   */
#define GPIO_Pin_All               ((uint16_t)0xFFFF)  /*!< All pins selected */

/**
  * @}
  */

/** @defgroup GPIO_Pin_Sources GPIO_Pin_Sources
  * @{
  */
#define GPIO_PinSource0            ((uint8_t)0x00)
#define GPIO_PinSource1            ((uint8_t)0x01)
#define GPIO_PinSource2            ((uint8_t)0x02)
#define GPIO_PinSource3            ((uint8_t)0x03)
#define GPIO_PinSource4            ((uint8_t)0x04)
#define GPIO_PinSource5            ((uint8_t)0x05)
#define GPIO_PinSource6            ((uint8_t)0x06)
#define GPIO_PinSource7            ((uint8_t)0x07)
#define GPIO_PinSource8            ((uint8_t)0x08)
#define GPIO_PinSource9            ((uint8_t)0x09)
#define GPIO_PinSource10           ((uint8_t)0x0A)
#define GPIO_PinSource11           ((uint8_t)0x0B)
#define GPIO_PinSource12           ((uint8_t)0x0C)
#define GPIO_PinSource13           ((uint8_t)0x0D)
#define GPIO_PinSource14           ((uint8_t)0x0E)
#define GPIO_PinSource15           ((uint8_t)0x0F)


/**
  * @}
  */

/** @defgroup GPIO_Alternate_Function_Selection_Define GPIO_Alternate_Function_Selection_Define
  * @{
  */

/**
  * @brief  AF 0 selection
  */
#define GPIO_AF_0            ((uint8_t)0x00) /* WKUP, EVENTOUT, TIM15, SPI1, TIM17,
                                                MCO, SWDAT, SWCLK, TIM14, BOOT,
                                                USART1, CEC, IR_OUT, SPI2, TS, TIM3,
                                                USART4, CAN, TIM3, USART2, USART3, 
                                                CRS, TIM16, TIM1 */
/**
  * @brief  AF 1 selection
  */
#define GPIO_AF_1            ((uint8_t)0x01) /* USART2, CEC, TIM3, USART1, IR,
                                                EVENTOUT, I2C1, I2C2, TIM15, SPI2,
                                                USART3, TS, SPI1 */
/**
  * @brief  AF 2 selection
  */
#define GPIO_AF_2            ((uint8_t)0x02) /* TIM2, TIM1, EVENTOUT, TIM16, TIM17,
                                                USB */
/**
  * @brief  AF 3 selection
  */
#define GPIO_AF_3            ((uint8_t)0x03) /* TS, I2C1, TIM15, EVENTOUT */

/**
  * @brief  AF 4 selection
  */
#define GPIO_AF_4            ((uint8_t)0x04) /* TIM14, USART4, USART3, CRS, CAN,
                                                I2C1 */

/**
  * @brief  AF 5 selection
  */
#define GPIO_AF_5            ((uint8_t)0x05) /* TIM16, TIM17, TIM15, SPI2, I2C2, 
                                                MCO, I2C1, USB */

/**
  * @brief  AF 6 selection
  */
#define GPIO_AF_6            ((uint8_t)0x06) /* EVENTOUT */

/**
  * @brief  AF 7 selection
  */
#define GPIO_AF_7            ((uint8_t)0x07) /* COMP1, COMP2 and COMP3 OUT */

/**
  * @brief  AF 8 selection
  */
#define GPIO_AF_8            ((uint8_t)0x08) /* SPI2_NSS/I2S2_WS, SPI2_SCK/I2S2_CK, SPI2_MISO/I2S2_MCK and SPI2_MOSI/I2S2_SD */

/**
  * @brief  AF 9 selection
  */
#define GPIO_AF_9            ((uint8_t)0x09) /* CLU0_0 */

/**
  * @brief  AF 10 selection
  */
#define GPIO_AF_10           ((uint8_t)0x0a) /* CLU1_0 */

/**
  * @brief  AF 11 selection
  */
#define GPIO_AF_11           ((uint8_t)0x0b) /* CLU2_0 */

/**
  * @brief  AF 12 selection
  */
#define GPIO_AF_12           ((uint8_t)0x0c) /* CLU3_0 */

/**
  * @brief  AF 13 selection
  */
#define GPIO_AF_13           ((uint8_t)0x0d) /* */

/**
  * @brief  AF 14 selection
  */
#define GPIO_AF_14           ((uint8_t)0x0e) /* CAN_RX, CAN_TX */

/**
  * @brief  AF 15 selection
  */
#define GPIO_AF_15           ((uint8_t)0x0f) /* RCC_MCO, I2C1_SMBA, I2C2_SMBA */



/**
  * @}
  */


/** @defgroup GPIO_Speed_Legacy GPIO_Speed_Legacy
  * @{
  */

#define GPIO_Speed_2MHz       GPIO_Speed_Level_1   /*!< I/O output speed: Low 2 MHz  */
#define GPIO_Speed_10MHz      GPIO_Speed_Level_2   /*!< I/O output speed: Medium 10 MHz */
#define GPIO_Speed_50MHz      GPIO_Speed_Level_3   /*!< I/O output speed: High 50 MHz */
#define GPIO_Speed_UltraHigh  GPIO_Speed_Level_4   /*!< I/O output speed: Ultra High */

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
/* Function used to set the GPIO configuration to the default reset state *****/
void GPIO_DeInit(GPIO_TypeDef* GPIOx);

/* Initialization and Configuration functions *********************************/
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/* GPIO Read and Write functions **********************************************/
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal);

/* GPIO Alternate functions configuration functions ***************************/
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF);

#ifdef __cplusplus
}
#endif

#endif /*__HK32F0XXA_GPIO_H */

