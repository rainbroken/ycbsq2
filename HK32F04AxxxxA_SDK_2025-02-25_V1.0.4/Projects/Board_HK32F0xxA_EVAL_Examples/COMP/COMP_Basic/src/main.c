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

/** @addtogroup COMP_PWMSignalControl
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void COMP_Config(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    HK_EVAL_LEDInit(LED1);

    /* COMP2 Configuration */
    COMP_Config();

    /* Infinite loop */
    while (1)
    {
    }
}



/**
  * @brief  Configures COMP2: PA3 as COMP2 non inverting input
  *         VREFINT as COMP2 inverting input
  *         and COMP2 output to TIM2 BKIN.
  * @param  None
  * @retval None
  */
static void COMP_Config(void)
{
    COMP_InitTypeDef        COMP_InitStructure;
    GPIO_InitTypeDef        GPIO_InitStructure;
    EXTI_InitTypeDef        EXTI_InitStructure;
    NVIC_InitTypeDef        NVIC_InitStructure;

    /* GPIOA Peripheral clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    /* Configure PA3 in analog mode: PA3 is connected to COMP2 non inverting input */
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_7);

    /* COMP Peripheral clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    /*Turn on the Vrefint switch and select Vrefint as 1.2V*/
    SYSCFG_VrefBufCMD(SYSCFG_Vref_Buf_EN);

    /* COMP2 config */
    COMP_StructInit(&COMP_InitStructure);
    COMP_InitStructure.COMP_InvertingInput = COMP_InvertingInput_PA5;
    COMP_InitStructure.COMP_Output = COMP_Output_None;
    COMP_InitStructure.COMP_Hysteresis = COMP_Hysteresis_No;
    COMP_InitStructure.COMP_Mode = COMP_Mode_UltraLowPower;
    COMP_InitStructure.COMP_OutputPol =  COMP_OutputPol_NonInverted;
    COMP_Init(COMP_Selection_COMP2, &COMP_InitStructure);

    /* Enable COMP2 */
    COMP_Cmd(COMP_Selection_COMP2, ENABLE);

    /* Configure EXTI Line 22 in interrupt mode */
    EXTI_InitStructure.EXTI_Line = EXTI_Line22;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Clear EXTI22 line */
    EXTI_ClearITPendingBit(EXTI_Line22);

    /* Configure COMP IRQ */
    NVIC_InitStructure.NVIC_IRQChannel = ADC_COMP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
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



