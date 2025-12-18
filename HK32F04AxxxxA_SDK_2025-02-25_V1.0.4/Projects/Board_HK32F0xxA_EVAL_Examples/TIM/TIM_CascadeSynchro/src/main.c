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

/** @addtogroup TIM_Cascade_Synchro
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;

/* Private function prototypes -----------------------------------------------*/
void GPIO_Configuration(void);
static void TIM_Config(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_hk32f0xxa.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_hk32f0xxa.c file
       */

    /* GPIO Configuration */
    GPIO_Configuration();

    /* TIM Configuration */
    TIM_Config();

    /* Infinite loop */
    while (1)
    {

    }
}

/**
  * @brief  TIM configuration
  * @param  None
  * @retval None
  */
static void TIM_Config(void)
{
    /* Timers synchronisation in cascade mode ----------------------------
       1/TIM1 is configured as Master Timer:
       - PWM Mode is used
       - The TIM1 Update event is used as Trigger Output

       2/TIM2 is slave for TIM1 and Master for TIM3,
       - PWM Mode is used
       - The ITR0(TIM1) is used as input trigger
       - Gated mode is used, so start and stop of slave counter
        are controlled by the Master trigger output signal(TIM1 update event).
        - The TIM2 Update event is used as Trigger Output.

        3/TIM3 is slave for TIM2,
       - PWM Mode is used
       - The ITR1(TIM2) is used as input trigger
       - Gated mode is used, so start and stop of slave counter
        are controlled by the Master trigger output signal(TIM2 update event).

       * The TIMxCLK is fixed to 56 MHz, the TIM1 counter clock is 56 MHz.

         The Master Timer TIM1 is running at TIM1 frequency :
         TIM1 frequency = (TIM1 counter clock)/ (TIM1 period + 1) = 218.750 KHz
         and the duty cycle = TIM1_CCR1/(TIM1_ARR + 1) = 25%.

         The TIM2 is running:
         - At (TIM1 frequency)/ (TIM2 period + 1) = 54.688 KHz and a duty cycle
           equal to TIM2_CCR1/(TIM2_ARR + 1) = 25%

          The TIM3 is running:
        - At (TIM2 frequency)/ (TIM3 period + 1) = 13.672 KHz and a duty cycle
          equal to TIM3_CCR1/(TIM3_ARR + 1) = 25%
    -------------------------------------------------------------------- */

    /* TIM clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    /* Time base configuration */
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = 255;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    TIM_TimeBaseStructure.TIM_Period = 3;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_TimeBaseStructure.TIM_Period = 3;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    /* Master Configuration in PWM1 Mode */
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 64;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM1, &TIM_OCInitStructure);

    /* Select the Master Slave Mode */
    TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable);

    /* Master Mode selection */
    TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Update);

    /* Slaves Configuration: PWM1 Mode */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 1;

    TIM_OC1Init(TIM2, &TIM_OCInitStructure);

    TIM_OC1Init(TIM3, &TIM_OCInitStructure);

    /* Slave Mode selection: TIM2 */
    TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Gated);
    TIM_SelectInputTrigger(TIM2, TIM_TS_ITR0);

    /* Select the Master Slave Mode */
    TIM_SelectMasterSlaveMode(TIM2, TIM_MasterSlaveMode_Enable);

    /* Master Mode selection: TIM2 */
    TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);

    /* Slave Mode selection: TIM3 */
    TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Gated);
    TIM_SelectInputTrigger(TIM3, TIM_TS_ITR1);

    /* TIM enable counter */
    TIM_Cmd(TIM1, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
    TIM_Cmd(TIM3, ENABLE);

    /* TIM1 Main Output Enable */
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

/**
  * @brief  Configure the GPIOD Pins.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* GPIOA Clocks enable */
    RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE);

    /*GPIOA Configuration:  PA8(TIM1 CH1) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2);

    /* GPIOA Configuration: PA5(TIM2 CH1) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_2);

    /* GPIOA Configuration: PA6(TIM3 CH1) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_1);
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



