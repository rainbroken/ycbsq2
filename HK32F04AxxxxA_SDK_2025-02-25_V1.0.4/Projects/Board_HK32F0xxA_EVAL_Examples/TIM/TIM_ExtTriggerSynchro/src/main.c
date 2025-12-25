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

/** @addtogroup TIM_ExtTriggerSynchro
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void TIM_Config(void);

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

    /* TIM1 Configuration */
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
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_ICInitTypeDef  TIM_ICInitStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    /* GPIOA Clocks enable */
    RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE);

    /*GPIOA Configuration:  PA8(TIM1 CH1) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
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

    /* GPIOB Configuration: PA6(TIM3 CH1) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_1);

    /*GPIOA Configuration:  PA9(TIM1 CH2) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9 ;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ; //default no trigger
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_2);


    /* Timers synchronisation in cascade mode with an external trigger -----
      1/TIM1 is configured as Master Timer:
       - Toggle Mode is used
       - The TIM1 Enable event is used as Trigger Output

      2/TIM1 is configured as Slave Timer for an external Trigger connected
       to TIM1 TI2 pin (TIM1 CH2 configured as input pin):
       - The TIM1 TI2FP2 is used as Trigger Input
       - Rising edge is used to start and stop the TIM1: Gated Mode.

      3/TIM2 is slave for TIM1 and Master for TIM3,
       - Toggle Mode is used
       - The ITR0(TIM1) is used as input trigger
       - Gated mode is used, so start and stop of slave counter
         are controlled by the Master trigger output signal(TIM1 enable event).
       - The TIM2 enable event is used as Trigger Output.

      4/TIM3 is slave for TIM2,
       - Toggle Mode is used
       - The ITR1(TIM2) is used as input trigger
       - Gated mode is used, so start and stop of slave counter
         are controlled by the Master trigger output signal(TIM2 enable event).

        The TIMxCLK is fixed to 56 MHZ, the Prescaler is equal to 3 so the TIMx clock
        counter is equal to 14 MHz.
        The Three Timers are running at:
        TIMx frequency = TIMx clock counter/ 2*(TIMx_Period + 1) = 94.5 KHz.

      The starts and stops of the TIM1 counters are controlled by the
      external trigger.
      The TIM2 starts and stops are controlled by the TIM1, and the TIM3
      starts and stops are controlled by the TIM2.
    -------------------------------------------------------------------- */

    /* TIM clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    /* Time base configuration */
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = 73;
    TIM_TimeBaseStructure.TIM_Prescaler = 3;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    TIM_TimeBaseStructure.TIM_Period = 73;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_TimeBaseStructure.TIM_Period = 73;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    /* Master Configuration in Toggle Mode */
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 64;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM1, &TIM_OCInitStructure);

    /* TIM1 Input Capture Configuration */
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0;

    TIM_ICInit(TIM1, &TIM_ICInitStructure);

    /* TIM1 Input trigger configuration: External Trigger connected to TI2 */
    TIM_SelectInputTrigger(TIM1, TIM_TS_TI2FP2);
    TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Gated);

    /* Select the Master Slave Mode */
    TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable);

    /* Master Mode selection: TIM1 */
    TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Enable);

    /* Slaves Configuration: Toggle Mode */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;

    TIM_OC1Init(TIM2, &TIM_OCInitStructure);

    TIM_OC1Init(TIM3, &TIM_OCInitStructure);

    /* Slave Mode selection: TIM2 */
    TIM_SelectInputTrigger(TIM2, TIM_TS_ITR0);
    TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Gated);

    /* Select the Master Slave Mode */
    TIM_SelectMasterSlaveMode(TIM2, TIM_MasterSlaveMode_Enable);

    /* Master Mode selection: TIM2 */
    TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Enable);

    /* Slave Mode selection: TIM3 */
    TIM_SelectInputTrigger(TIM3, TIM_TS_ITR1);
    TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Gated);

    /* TIM1 Main Output Enable */
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    /* TIM enable counter */
    TIM_Cmd(TIM1, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
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



