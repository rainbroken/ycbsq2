/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f0xxa_divsqrt.h
* @brief:     Head file of divsqrt module
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F0XXA_DIVSQRT_H
#define __HK32F0XXA_DIVSQRT_H

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

/** @addtogroup DIVSQRT
  * @{
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup DIVSQRT_Exported_Constants DIVSQRT_Exported_Constants
  * @{
  */

/** @defgroup DIVSQRT_Busy_Wait DIVSQRT_Busy_Wait
  * @{
  */
#define DVSQ_BUSY_WAIT_EN                           1                                     /* 为1的话在读取DVSQ运算结果寄存器前都会判断并等待DVSQ空闲 */
/**
  * @}
  */



/** @defgroup DIVSQRT_Access_Pointer DIVSQRT_Access_Pointer
  * @{
  */
#define DVSQ                                        DIVSQRT
/**
  * @}
  */


/** @defgroup DIVSQRT_Periph_Rcc DIVSQRT_Periph_Rcc
  * @{
  */
#define RCC_AHBPeriph_DVSQ                          ((uint32_t)0x00000001)
#define RCC_AHBPeriph_DVSQ_CLK_Enable()             RCC->AHBENR2 |= RCC_AHBPeriph_DVSQ     /* Enable DVSQ RCC */
#define RCC_AHBPeriph_DVSQ_CLK_Disable()            RCC->AHBENR2 &= ~RCC_AHBPeriph_DVSQ    /* Disable DVSQ RCC */
/**
  * @}
  */


/** @defgroup DIVSQRT_Status DIVSQRT_Status
  * @{
  */
#define DVSQ_IDLE_NO_OPERATION                      ((uint32_t)0x00000000)                /* DVSQ is idle and has not undergone square root or division operations */
#define DVSQ_IDLE_SQRT                              ((uint32_t)0x20000000)                /* DVSQ is idle and the last operation completed was a square root operation */
#define DVSQ_IDLE_DIV                               ((uint32_t)0x40000000)                /* DVSQ is idle and the previous operation completed is a division operation */
#define DVSQ_BUSY_SQRT                              ((uint32_t)0xA0000000)                /* DVSQ is busy and performing square root operation */
#define DVSQ_BUSY_DIV                               ((uint32_t)0xC0000000)                /* DVSQ is busy and performing division operation */

#define DVSQ_IsBusy()                               ((DVSQ->CSR & DIVSQRT_CSR_BUSY)? 1:0) /* 返回'1'表示忙;  返回'0'表示空闲 */
/**
  * @}
  */


/** @defgroup DIVSQRT_Div_Fast_En DIVSQRT_Div_Fast_En
  * @{
  */
#define DVSQ_EnableDivFastStart()                   DVSQ->CSR &= ~DIVSQRT_CSR_DFS         /* Enable Fast division operation */
#define DVSQ_DisableDivFastStart()                  DVSQ->CSR |= DIVSQRT_CSR_DFS          /* Disable Fast division operation */
/**
  * @}
  */


/** @defgroup DIVSQRT_Div_Signed DIVSQRT_Div_Signed
  * @{
  */
#define DVSQ_ConfigDivUnsigned()                    DVSQ->CSR |= DIVSQRT_CSR_UNSIGN_DIV   /* config DVSQ for unsigned division operation */
#define DVSQ_ConfigDivSigned()                      DVSQ->CSR &= ~DIVSQRT_CSR_UNSIGN_DIV  /* config DVSQ for signed division operation */
/**
  * @}
  */


/** @defgroup DIVSQRT_Div_precision DIVSQRT_Div_precision
  * @{
  */
#define DVSQ_ConfigSqrtPresHigh()                   DVSQ->CSR |= DIVSQRT_CSR_HPRESQRT    /* config DVSQ for high precision square root operation */
#define DVSQ_ConfigSqrtPresNormal()                 DVSQ->CSR &= ~DIVSQRT_CSR_HPRESQRT    /* config DVSQfor normal precision square root operation */
/**
  * @}
  */



/** @defgroup DIVSQRT_Ctrl DIVSQRT_Ctrl
  * @{
  */
/* If DVSQ->CSR.DVSQ_CSR_DFS = 1, must set DVSQ->CSR.DIVSQRT_CSR_DIV_SRT by software to start div operation;
   else the division operation is started by hardware when DVSQ_DIVISOR is written */
#define DVSQ_StartDivCalc()                         DVSQ->CSR |= DIVSQRT_CSR_DIV_SRT      /* start division operation */


/* DVSQ wait for idle */
#if (DVSQ_BUSY_WAIT_EN == 1)
#define DVSQ_Wait()                                 while(DVSQ_IsBusy())
#else
#define DVSQ_Wait()
#endif
/**
  * @}
  */

/**
  * @}
  */
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
void DVSQ_Init(void);
uint32_t DVSQ_Sqrt(uint32_t u32Radicand);
uint16_t DVSQ_SqrtH(uint32_t u32Radicand, uint16_t *fraction);
int32_t DVSQ_Divsion(int32_t i32Dividend, int32_t i32Divisor, int32_t *i32pRemainder);
uint32_t DVSQ_UDivsion(uint32_t u32Dividend, uint32_t u32Divisor, uint32_t *u32pRemainder);

#ifdef __cplusplus
}
#endif

#endif /*__HK32F0XXA_DIVSQRT_H */

