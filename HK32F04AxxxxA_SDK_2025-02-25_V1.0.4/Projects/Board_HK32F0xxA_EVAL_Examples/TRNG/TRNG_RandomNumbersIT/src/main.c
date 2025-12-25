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

/** @addtogroup TRNG_RandomNumbersPoll
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define    NB_OF_GENERATED_RANDOM_NUMBERS      8       /* Nb of Random numbers generated after eash User button press */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Array used for storing generated Random 32bit Numbers */
uint32_t aRandom32bit[NB_OF_GENERATED_RANDOM_NUMBERS];
uint8_t ubButtonPress = 0;
USART_InitTypeDef USART_InitStructure;
uint8_t ubIsNbGenerated = 0;
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    uint8_t index = 0;

    /* Initialize LED2 */
    HK_EVAL_LEDInit(LED2);
    /*------------------------------- USART-------------------------------------*/

    /* USARTx configured as follow:
    - BaudRate = 115200
    - Word Length = USART_WordLength_8b
    - Stop Bit = USART_StopBits_1
    - Parity = USART_Parity_No
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    /* Initialize USART1 */
    HK_EVAL_COMInit(COM1, &USART_InitStructure);

    /* Initialize User push-button in EXTI mode */
    HK_EVAL_PBInit(BUTTON_KEY, BUTTON_MODE_EXTI);

    /* Configure RNG (RNG IP configuration : Clock enabling) */
    Configure_Config();

    /* Wait for User push-button press to trigger random numbers generation */
    WaitForUserButtonPress();

    /* Generate Random Numbers series */
    RandomNumbersGeneration_IT();

    /* Infinite loop */
    while (1)
    {
        if (ubIsNbGenerated == 1 && index < 8) /* Call function in charge of handling DR reading */
        {
            /* Disable RNG IT generation */
            RNG_ITConfig(DISABLE);

            /* Value of generated random number could be retrieved and stored in dedicated array */
            aRandom32bit[index] = RNG_GetRandomNumberIT();

            /* Display the Random number value on the  USART */
            printf("Random32bit:0x%08x    count:%d\r\n", aRandom32bit[index],  index + 1);

            /* Set Flag indicated random Number generation is completed */
            ubIsNbGenerated = 0;
            RNG_ITConfig(ENABLE);
            index++;
        }
        else if (ubIsNbGenerated == 2) /* Call Error function */
        {
            HK_EVAL_LEDToggle(LED2);
            Delay(0x6FFF);
        }
        else if (index == 8)
        {
            Delay(0x6FFF);

            /* Stop random numbers generation */
            RNG_Cmd(DISABLE);

            /* Disable RNG IT generation */
            RNG_ITConfig(DISABLE);

            /* Values of Generated Random numbers are now available in aRandom32bit array.
            LED2 is turned on */
            HK_EVAL_LEDOn(LED2);
            ubIsNbGenerated = 0;
            index = 0;
        }
    }
}

/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
void Delay(__IO uint32_t nCount)
{
    /* Decrement nCount value */
    while (nCount != 0)
    {
        nCount--;
    }
}

/**
  * @brief  Wait for User push-button press to start transfer.
  * @param  None
  * @retval None
  */
void WaitForUserButtonPress(void)
{
    while (ubButtonPress == 0)
    {
        HK_EVAL_LEDToggle(LED2);
        Delay(0x3FFF);
    }

    /* Turn LED2 off */
    HK_EVAL_LEDOff(LED2);
}

/**
  * @brief  This function configures RNG Instance.
  * @note   This function is used to :
  *         -1- Enable peripheral clock for RNG.
  *         -2- NVIC Configuration for RNG interrupts.
  * @param  None
  * @retval None
  */
void Configure_Config(void)
{
    /* Enable TRNG clock source */
    RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_TRNG, ENABLE);

    /* (2) NVIC Configuration for TRNG interrupts */

    /*  - Set priority for AES_TRNG_HASH_EAACC_IRQn */

    /*  - Enable AES_TRNG_HASH_EAACC_IRQn */
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = AES_TRNG_HASH_EAACC_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}

/**
  * @brief  This function performs several random numbers generation.
  * @note   Generated random numbers are stored in global variable array, so that
  *         generated values could be observed by user by watching variable content
  *         in specific debugger window
  * @param  None
  * @retval None
  */
void RandomNumbersGeneration_IT(void)
{
    // enable RNG interrupt
    RNG_ITConfig(ENABLE);

    /* Initialize random numbers generation */
    RNG_Cmd(ENABLE);
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

