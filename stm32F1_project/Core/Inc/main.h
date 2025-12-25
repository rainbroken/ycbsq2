/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TOUCH_Pin GPIO_PIN_0
#define TOUCH_GPIO_Port GPIOA
#define CAT1_TX_Pin GPIO_PIN_2
#define CAT1_TX_GPIO_Port GPIOA
#define CAT1_RX_Pin GPIO_PIN_3
#define CAT1_RX_GPIO_Port GPIOA
#define BAT_DET_Pin GPIO_PIN_4
#define BAT_DET_GPIO_Port GPIOA
#define RGB_Pin GPIO_PIN_0
#define RGB_GPIO_Port GPIOB
#define AMP_SHUT_Pin GPIO_PIN_1
#define AMP_SHUT_GPIO_Port GPIOB
#define VBUS_DET_Pin GPIO_PIN_2
#define VBUS_DET_GPIO_Port GPIOB
#define GPS_TX_Pin GPIO_PIN_10
#define GPS_TX_GPIO_Port GPIOB
#define GPS_RX_Pin GPIO_PIN_11
#define GPS_RX_GPIO_Port GPIOB
#define CHG_EN_Pin GPIO_PIN_12
#define CHG_EN_GPIO_Port GPIOB
#define CHG_DET_Pin GPIO_PIN_13
#define CHG_DET_GPIO_Port GPIOB
#define CHG_STB_Pin GPIO_PIN_14
#define CHG_STB_GPIO_Port GPIOB
#define V_5V_EN_Pin GPIO_PIN_15
#define V_5V_EN_GPIO_Port GPIOB
#define CAT1_RST_Pin GPIO_PIN_8
#define CAT1_RST_GPIO_Port GPIOA
#define CAT1_EN_Pin GPIO_PIN_11
#define CAT1_EN_GPIO_Port GPIOA
#define CAT1_PWRK_Pin GPIO_PIN_12
#define CAT1_PWRK_GPIO_Port GPIOA
#define CAN_EN_Pin GPIO_PIN_5
#define CAN_EN_GPIO_Port GPIOB
#define TTS_BUSY_Pin GPIO_PIN_6
#define TTS_BUSY_GPIO_Port GPIOB
#define TTS_DAT_Pin GPIO_PIN_7
#define TTS_DAT_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
extern void SystemClock_Config(void);
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
