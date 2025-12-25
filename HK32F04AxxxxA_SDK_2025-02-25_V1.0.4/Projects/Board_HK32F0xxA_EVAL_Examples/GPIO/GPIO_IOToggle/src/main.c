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

/** @addtogroup HK32F0xxA_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef        GPIO_InitStructure;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* GPIOC Periph clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

    /* Configure PC10 and PC11 in output pushpull mode */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Schmit = GPIO_Schmit_Disable;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    while (1)
    {
        GPIO_SetBits(GPIOC, GPIO_Pin_10 | GPIO_Pin_11);
        GPIO_ResetBits(GPIOC, GPIO_Pin_10 | GPIO_Pin_11);
        GPIO_SetBits(GPIOC, GPIO_Pin_10 | GPIO_Pin_11);
        GPIO_ResetBits(GPIOC, GPIO_Pin_10 | GPIO_Pin_11);
        GPIO_SetBits(GPIOC, GPIO_Pin_10 | GPIO_Pin_11);
        GPIO_ResetBits(GPIOC, GPIO_Pin_10 | GPIO_Pin_11);
        GPIO_SetBits(GPIOC, GPIO_Pin_10 | GPIO_Pin_11);
        GPIO_ResetBits(GPIOC, GPIO_Pin_10 | GPIO_Pin_11);
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




