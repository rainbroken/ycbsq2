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
#include "hk32f0xxa_conf.h"
#include "main.h"
#include "hk32f0xxa_eval.h"


/** @addtogroup HK32F0xxA_StdPeriph_Examples
  * @{
  */

/** @addtogroup CLU_BASIC_Example
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint32_t Reply = 0xFFFF;

/* Private function prototypes -----------------------------------------------*/
static void GPIO_Config(void);
static void USART_Config(void);

static void Delay_us(__IO uint32_t TCounter);
static void AsureConn(void);
static void SelFunID(uint32_t  FunIDCnt);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
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
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    uint32_t FunIDCnt = 4;
    USART_Config();
    GPIO_Config();
    CLU->CLU0MX |= (uint32_t)0x1F << 16;
    CLU->CLU1MX |= (uint32_t)0x1F << 16;
    CLU->CLU2MX |= (uint32_t)0x1F << 16;
    CLU->CLU3MX |= (uint32_t)0x1F << 16;
    printf("\r\n +-------- Test CLU Synchronous Output Function --------+\r\n");
    printf("\r\n  Please select CLU (CLU0 / CLU1 / CLU2 / CLU3) to test? (Please enter the following numbers)");
    printf("\r\n  <1>:CLU0    <2>:CLU1    <3>:CLU2    <4>:CLU3");
    SelFunID(FunIDCnt);

    if (Reply == 1)
    {
        printf("\r\n Your choose is \" <1>:CLU0 \" \r\n");
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        /* For CLU0 , MXA=PA0, Ignore MXB,MXC and MXD, Function=A */
        CLU0_MultiplexerInputConfig(CLU0_MXA_PA0, 0, 0, 0);
        CLU_SetOutputFunction(CLU0, (uint32_t)CLU_FUNCTION_A_INPUT_TRUE);
        CLU_OutputSelection(CLU0, CLUxCF_OUTSEL__LUT);
        CLU_EnablePinOutput(CLU0, CLUxCF_OEN__ENABLE);
        CLU_Cmd(CLU0, ENABLE);

        /* Multiplex the PC10 pin as CLU0 output */
        GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_9);
        EXTI2_ClearITPendingBit(EXTI_Line0);
        EXTI_InitStructure.EXTI_Line = EXTI2_Line0;

        /* Enable the CLU0 gloabal Interrupt */
        NVIC_InitStructure.NVIC_IRQChannel = TIM14_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
        printf("\r\n Please connect the pins as follows:");
        printf("\r\n< Test_Pin  |  MX_Pin >");
        printf("\r\n[PB0/key ----->  PA0  ]");
        printf("\r\n[ Probe1  <-----  PC10 ]");
        printf("\r\n[ Probe2  <-----  PB2  ]");
        printf("\r\n <3>Already connected    <4>Not connected successfully   (Please enter the number between '<' and '>' ) ");
        AsureConn();
        printf("\r\n Please view the oscilloscope waveform ! \r\n");
    }
    else if (Reply == 2)
    {
        printf("\r\n Your choose is \" <1>:CLU1 \" \r\n");
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        /* For CLU1 , MXA=PA4, Ignore MXB,MXC and MXD, Function=A */
        CLU1_MultiplexerInputConfig(CLU1_MXA_PA4, 0, 0, 0);
        CLU_SetOutputFunction(CLU1, (uint32_t)CLU_FUNCTION_A_INPUT_TRUE);
        CLU_OutputSelection(CLU1, CLUxCF_OUTSEL__LUT);
        CLU_EnablePinOutput(CLU1, CLUxCF_OEN__ENABLE);
        CLU_Cmd(CLU1, ENABLE);

        /* Multiplex the PC10 pin as CLU0 output */
        GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_10);
        EXTI2_ClearITPendingBit(EXTI_Line1);
        EXTI_InitStructure.EXTI_Line = EXTI2_Line1;

        /* Enable the CLU1 gloabal Interrupt */
        NVIC_InitStructure.NVIC_IRQChannel = TIM16_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
        printf("\r\n Please connect the pins as follows:");
        printf("\r\n< Test_Pin  |  MX_Pin >");
        printf("\r\n[PB0/key ----->  PA4  ]");
        printf("\r\n[ Probe1  <-----  PC10 ]");
        printf("\r\n[ Probe2  <-----  PB2  ]");
        printf("\r\n <3>Already connected    <4>Not connected successfully   (Please enter the number between '<' and '>' ) ");
        AsureConn();
        printf("\r\n Please view the oscilloscope waveform ! \r\n");
    }
    else if (Reply == 3)
    {
        printf("\r\n Your choose is \" <1>:CLU2 \" \r\n");
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        /* For CLU2 , MXA=PA6, Ignore MXB,MXC and MXD, Function=A */
        CLU2_MultiplexerInputConfig(CLU2_MXA_PA6, 0, 0, 0);
        CLU_SetOutputFunction(CLU2, (uint32_t)CLU_FUNCTION_A_INPUT_TRUE);
        CLU_OutputSelection(CLU2, CLUxCF_OUTSEL__LUT);
        CLU_EnablePinOutput(CLU2, CLUxCF_OEN__ENABLE);
        CLU_Cmd(CLU2, ENABLE);

        /* Multiplex the PC10 pin as CLU0 output */
        GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_11);
        EXTI2_ClearITPendingBit(EXTI2_Line2);
        EXTI_InitStructure.EXTI_Line = EXTI2_Line2;

        /* Enable the CLU2 gloabal Interrupt */
        NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
        printf("\r\n Please connect the pins as follows:");
        printf("\r\n< Test_Pin  |  MX_Pin >");
        printf("\r\n[PB0/key ----->  PA6  ]");
        printf("\r\n[ Probe1  <-----  PC10 ]");
        printf("\r\n[ Probe2  <-----  PB2  ]");
        printf("\r\n <3>Already connected    <4>Not connected successfully   (Please enter the number between '<' and '>' ) ");
        AsureConn();
        printf("\r\n Please view the oscilloscope waveform ! \r\n");
    }
    else if (Reply == 4)
    {
        printf("\r\n Your choose is \" <1>:CLU3 \" \r\n");
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        /* For CLU3 , MXA=PA12, Ignore MXB,MXC and MXD, Function=A */
        CLU3_MultiplexerInputConfig(CLU3_MXA_PA12, 0, 0, 0);
        CLU_SetOutputFunction(CLU3, (uint32_t)CLU_FUNCTION_A_INPUT_TRUE);
        CLU_OutputSelection(CLU3, CLUxCF_OUTSEL__LUT);
        CLU_EnablePinOutput(CLU3, CLUxCF_OEN__ENABLE);
        CLU_Cmd(CLU3, ENABLE);

        /* Multiplex the PC10 pin as CLU0 output */
        GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_12);
        EXTI2_ClearITPendingBit(EXTI2_Line3);
        EXTI_InitStructure.EXTI_Line = EXTI2_Line3;

        /* Enable the CLU3 gloabal Interrupt */
        NVIC_InitStructure.NVIC_IRQChannel = SPI2_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
        printf("\r\n Please connect the pins as follows:");
        printf("\r\n< Test_Pin  |  MX_Pin >");
        printf("\r\n[ PB0     ----->  PA12 ]");
        printf("\r\n[ Probe1  <-----  PC10 ]");
        printf("\r\n[ Probe2  <-----  PB2  ]");
        printf("\r\n <3>Already connected    <4>Not connected successfully   (Please enter the number between '<' and '>' ) ");
        AsureConn();
        printf("\r\n Please view the oscilloscope waveform ! \r\n");
    }
    else
    {
        printf("\r\n #### Your choose is error , please restart ! ####\r\n");
    }

    printf("\r\n Please select the test point of CLU synchronous output ?  (Please enter the following numbers)");
    printf("\r\n <1> Test CLU Falling Edge Interrupt ");
    printf("\r\n <2> Test CLU Rising Edge Interrupt ");
    printf("\r\n <3> Test CLU Falling& Rising Edge Interrupt ");
    FunIDCnt = 3;
    SelFunID(FunIDCnt);

    //RCC_MCO();

    if (Reply == 1)
    {
        printf("\r\n Your choose is \" <1> Test CLU Falling Edge Interrupt \" \r\n");
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;
        EXTI2_Init(&EXTI_InitStructure);
    }
    else if (Reply == 2)
    {
        printf("\r\n Your choose is \" <2> Test CLU Rising Edge Interrupt \" \r\n");
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;
        EXTI2_Init(&EXTI_InitStructure);
    }
    else if (Reply == 3)
    {
        printf("\r\n Your choose is \" <3> Test CLU Falling& Rising Edge Interrupt \" \r\n");
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;
        EXTI2_Init(&EXTI_InitStructure);
    }
    else
    {
        printf("\r\n #### Your choose is error , please restart ! ####\r\n");
    }

    while (1)
    {
        if (Reply <= FunIDCnt)
        {
            GPIO_SetBits(GPIOB, GPIO_Pin_0);
            Delay_us(3);
            GPIO_ResetBits(GPIOB, GPIO_Pin_0);
            Delay_us(5);
        }
    }
}

/**
  * @brief  Configure GPIO peripheral, used to CLU output/input.
  * @param  None
  * @retval None
  */
static void GPIO_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* Enable GPIO Clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

    /* Configure PB0/PB1/PB2/PB8 of GPIO to output pwm signal, used connected MXA/MXB/MXC/MXD of CLU */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_8);

    /* Configure PC10 as CLU output */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/**
  * @brief  Configure USART peripheral, used to print.
  * @param  None
  * @retval None
  */
static void USART_Config(void)
{
    USART_InitTypeDef USART_InitStructure;
    //ErrorStatus ErrLog;

    /* USARTx configured as follow:
          - BaudRate = 115200 baud
          - Word Length = 8 Bits
          - One Stop Bit
          - No parity
          - Hardware flow control disabled (RTS and CTS signals)
          - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = 115200;
    //USART_InitStructure.USART_BaudRate = 1200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    HK_EVAL_COMInit(COM1, &USART_InitStructure);
}

/**
  * @brief  Delay Us
  * @param  TCounter : Delay counter
  * @retval None
  */
static void Delay_us(__IO uint32_t TCounter)
{
    while (TCounter--)
    {
        /* 8M */
        //for(uint32_t i=0; i<5; i++);

        /* 56M */
        for (uint32_t i = 0; i < 35; i++)
        {
            ;
        }
    }
}

/**
  * @brief  SelFunID
  * @param  FunIDCnt : ID counter
  * @retval None
  */
static void SelFunID(uint32_t  FunIDCnt)
{
    Reply = 0xFFFF;

    while (Reply > FunIDCnt)
    {
        //scanf("%d",&Reply);
        while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
        {
            ;
        }

        //USART_ClearFlag(USART1,USART_FLAG_RXNE);
        Reply = (uint32_t)USART_ReceiveData(USART1);
        Reply -= '0';

        /* Checks */
        if (Reply > FunIDCnt)
        {
            printf("\n\rPlease enter valid number between 0 and %d", FunIDCnt);
        }
    }
}

/**
  * @brief  AsureConn
  * @param  None
  * @retval None
  */
static void AsureConn(void)
{
    uint32_t ExptID = 3;
    Reply = 0xFFFF;

    while (Reply != ExptID)
    {
        //scanf("%d",&Reply);
        while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
        {
            ;
        }

        //USART_ClearFlag(USART1,USART_FLAG_RXNE);
        Reply = (uint32_t)USART_ReceiveData(USART1);
        Reply -= '0';

        if (Reply != ExptID)
        {
            printf("\r\n#### Please reconnect and enter the number ! #### \r\n");
        }
    }
}

/**
  * @brief  Toggle GPIO pin
  * @param  GPIOx: can be GPIOA, GPIOB, GPIOC,GPIOD, GPIOF
  * @param  GPIO_Pin: GPIO_Pin_0 to GPIO_Pin_15
  * @retval None
  */
void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_PIN(GPIO_Pin));
    GPIOx->ODR ^= GPIO_Pin;
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
        ;
    }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

