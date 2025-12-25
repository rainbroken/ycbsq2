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

/** @addtogroup IRTIM_TX
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

volatile unsigned char g_IRSendFlag = 0;  /* send flag, 1 is carrier, 0 is envelope */
volatile unsigned int g_IRTIM_count;

volatile unsigned char g_ButtonFlag;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void IRTIM_config(void);
static void Write_IRdata(unsigned char pCustomCode, unsigned char pKeyCode);

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

    /* Initialize button */
    HK_EVAL_PBInit(BUTTON_KEY, BUTTON_MODE_EXTI);

    /* Initialize IRTIM */
    IRTIM_config();

    while (1)
    {
        if (g_ButtonFlag == 1)
        {
            g_ButtonFlag = 0;

            Write_IRdata(0x55, 0x12);
        }
    }

}

/**
  * @brief  IR output GPIO(PB9) configurate.
  * @param  None
  * @retval None
  */
static void IROUT_GPIOConfig(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init( GPIOB, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_0);

    /* Enhance driving ability */
    SYSCFG_I2CFastModePlusConfig(SYSCFG_I2CFastModePlus_PB9, ENABLE);
}

/**
  * @brief  IRTIM carrier configurate to 38KHz, Abide by NEC agreement.
  * @param  None
  * @retval None
  */
static void IRTIMCarrier_Config(void)
{
    /* Duty cycle is set to 50%, frequency is 38KHz*/
    uint32_t IRTimerPeriod = (SystemCoreClock / 38000);
    uint16_t IRTimerPulse = IRTimerPeriod / 2;

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    TIM_TimeBaseStructure.TIM_Period = IRTimerPeriod - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM17, &TIM_TimeBaseStructure);

    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = IRTimerPulse;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM17, &TIM_OCInitStructure);

    TIM_CtrlPWMOutputs(TIM17, ENABLE);
    TIM_CCPreloadControl(TIM17, DISABLE);

    /* TIM17 counter enable */
    TIM_Cmd(TIM17, ENABLE);
}


/**
  * @brief  IRTIM envelope interrupt configurate.
  * @param  None
  * @retval None
  */
static void IRTIMEnvelope_NVIC_config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = TIM16_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  IRTIM envelope config, Abide by NEC agreement.
  * @param  None
  * @retval None
  */
static void IRTIMEnvelope_config(void)
{
    uint32_t IRTimerPrescaler = SystemCoreClock / 1000000;

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    /*The envelope period is 27us*/
    TIM_TimeBaseStructure.TIM_Period = ENVELOPE_TIM_PERIOD;
    TIM_TimeBaseStructure.TIM_Prescaler = IRTimerPrescaler - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM16, &TIM_TimeBaseStructure);

    /* PWM1 Mode configuration: Channel1 */
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM16, &TIM_OCInitStructure);

    TIM_CtrlPWMOutputs(TIM16, ENABLE);
    TIM_CCPreloadControl(TIM16, DISABLE);

    TIM_ClearFlag(TIM16, TIM_FLAG_Update);

    TIM_ITConfig(TIM16, TIM_IT_Update, ENABLE);

    /* TIM16 counter enable */
    TIM_Cmd(TIM16, ENABLE);
}

/**
  * @brief  Configures the IRTIM Peripheral.
  * @param  None
  * @retval None
  */
static void IRTIM_config(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    IROUT_GPIOConfig();
    IRTIMCarrier_Config();
    IRTIMEnvelope_NVIC_config();
    IRTIMEnvelope_config();

}

/**
  * @brief  Send IR data, Abide by NEC agreement.
  * @param  x_irdata: Data that needs to be sent, LSB first.
  * @retval None
  */
static void Send_IRdata(unsigned char x_irdata)
{
    unsigned char i;
    unsigned char irdata;
    unsigned int EndCount;

    irdata = x_irdata;

    for (i = 0; i < 8; i++)
    {
        /* Send 0.56ms carrier */
        EndCount = IRT_560US_TIMER;
        g_IRTIM_count = 0;
        g_IRSendFlag = 1;   /* Start Sending carrier*/

        while (g_IRTIM_count < EndCount)
        {

        }

        if (irdata & 0x01)
        {
            /*1.68ms is 1*/
            EndCount = IRT_1680US_TIMER;
        }
        else
        {
            /*0.56ms is 0*/
            EndCount = IRT_560US_TIMER;
        }

        g_IRTIM_count = 0;
        g_IRSendFlag = 0;  /* Start Sending envelope*/

        while (g_IRTIM_count < EndCount)
        {

        }

        irdata = irdata >> 1;
    }
}

/**
  * @brief  Write IR data, Abide by NEC agreement.
  * @param  pCustomCode: Custom data code.
  * @param  pKeyCode: Key data code.
  * @retval None
  */
static void Write_IRdata(unsigned char CustomCode, unsigned char KeyCode)
{
    unsigned int EndCount;

    /* 1. Send 9ms leader code(high level) */
    EndCount = IRT_LEADER_CODE_TIMER;
    g_IRTIM_count = 0;
    g_IRSendFlag = 1;  /* Start Sending carrier*/

    while (g_IRTIM_count < EndCount)
    {

    }

    /* 2. Send the end code of the 4.5ms leader code(low level)*/
    EndCount = IRT_LEADER_CODE_END_TIMER;
    g_IRTIM_count = 0;
    g_IRSendFlag = 0;  /* Start Sending envelope*/

    while (g_IRTIM_count < EndCount)
    {

    }

    /* 3. Send 16 bit address, LSB first */
    Send_IRdata(CustomCode);
    Send_IRdata(~CustomCode);

    /* 4. Send 16 bit data, LSB first */
    Send_IRdata(KeyCode);
    Send_IRdata(~KeyCode);

    /* 5. Send Stop bit */
    EndCount = IRT_560US_TIMER;
    g_IRTIM_count = 0;
    g_IRSendFlag = 1;   /* Start Sending carrier*/

    while (g_IRTIM_count < EndCount)
    {

    }

    /* 6. End of code */
    EndCount = IRT_END_CODE_TIMER;
    g_IRTIM_count = 0;
    g_IRSendFlag = 0;  /* Start Sending envelope*/

    while (g_IRTIM_count < EndCount)
    {

    }

    EndCount = IRT_560US_TIMER;
    g_IRTIM_count = 0;
    g_IRSendFlag = 1;  /* Start Sending carrier*/

    while (g_IRTIM_count < EndCount)
    {

    }

    g_IRSendFlag = 0;
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



