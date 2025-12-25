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
#include "hk32f0xxa_eval_spi_flash.h"
#endif /* USE_HK32F0xxA_EVAL */

/* Exported typedef ----------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#define ENVELOPE_TIM_PERIOD             (27-1)
#define IRT_LEADER_CODE_TIMER           (9000/(ENVELOPE_TIM_PERIOD+1))   // 9ms / 27us
#define IRT_LEADER_CODE_END_TIMER       (4500/(ENVELOPE_TIM_PERIOD+1))   // 4.5ms / 27us
#define IRT_END_CODE_TIMER              (2100/(ENVELOPE_TIM_PERIOD+1))   // 2.1ms / 27us
#define IRT_560US_TIMER                 (560/(ENVELOPE_TIM_PERIOD+1))    // 0.56ms / 27us
#define IRT_1680US_TIMER                (1680/(ENVELOPE_TIM_PERIOD+1))   // 1.68ms / 27us

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif  /* End of __cplusplus */

#endif /*__MAIN_H */

