/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-10-08
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup HK32F0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup DBUMCU
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
EXTI_InitTypeDef   EXTI_InitStructure;
GPIO_InitTypeDef   GPIO_InitStructure;
NVIC_InitTypeDef   NVIC_InitStructure;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* DEBUG Periph clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_DBGMCU, ENABLE);

    /* PWR Periph clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    /* Initialize LEDs mounted on EVAL board */
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);

    /* Configure PA0 in interrupt mode */
    HK_EVAL_PBInit(BUTTON_SEL, BUTTON_MODE_EXTI);
    /*Enable debugging in stop mode*/
    DBGMCU_Config(DBGMCU_STOP, ENABLE);
    /*Enter stop mode*/
    PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_SLEEPEntry_WFI);

    /* Infinite loop */
    while (1)
    {
        HK_EVAL_LEDToggle(LED1);
    }
}




#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif

/**
  * @}
  */

/**
  * @}
  */


