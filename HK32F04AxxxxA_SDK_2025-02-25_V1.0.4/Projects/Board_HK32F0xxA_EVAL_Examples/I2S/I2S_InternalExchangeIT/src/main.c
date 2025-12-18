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

/** @addtogroup I2S_InternalExchangeIT
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
const uint16_t I2S_Buffer_Tx[32] = {0x0102, 0x0304, 0x0506, 0x0708, 0x090A, 0x0B0C,
                                    0x0D0E, 0x0F10, 0x1112, 0x1314, 0x1516, 0x1718,
                                    0x191A, 0x1B1C, 0x1D1E, 0x1F20, 0x2122, 0x2324,
                                    0x2526, 0x2728, 0x292A, 0x2B2C, 0x2D2E, 0x2F30,
                                    0x3132, 0x3334, 0x3536, 0x3738, 0x393A, 0x3B3C,
                                    0x3D3E, 0x3F40
                                   };
__IO uint16_t TxIdx = 0, RxIdx = 0;
uint16_t I2S_Buffer_Rx[32] = {0};
TestStatus TransferStatus = FAILED;

/* Private function prototypes -----------------------------------------------*/
static TestStatus Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength);
static void I2S_Config(void);

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

    /* I2S peripheral Configuration */
    I2S_Config();

    /* Enable the Tamper button */
    HK_EVAL_PBInit(BUTTON_SEL, BUTTON_MODE_GPIO);

    /* Initialize the LEDs */
    HK_EVAL_LEDInit(LED3);
    HK_EVAL_LEDInit(LED1);

    while (HK_EVAL_PBGetState(BUTTON_SEL) != RESET)
    {

    }

    /* Enable the I2S1 TX Interrupt */
    SPI_I2SITConfig(SPI1, SPI_I2S_IT_TXE, ENABLE);

    /* Enable the I2S */
    I2S_Cmd(SPI1, ENABLE);

    while (RxIdx < 32)
    {

    }

    /* Check if the data transmitted from Master Board and received by
    Slave Board are the same */
    TransferStatus = Buffercmp(I2S_Buffer_Rx, (uint16_t*)I2S_Buffer_Tx, 32);

    if (TransferStatus == PASSED) /* successful transfer */
    {
        /* Green Led On */
        HK_EVAL_LEDOn(LED1);
        HK_EVAL_LEDOff(LED3);
    }
    else /* unsuccessful transfer */
    {
        /* Red Led On */
        HK_EVAL_LEDOn(LED3);
        HK_EVAL_LEDOff(LED1);
    }


    /* Infinite loop */
    while (1)
    {

    }
}

/**
  * @brief  Configures I2S peripheral.
  * @param  None
  * @retval None
  */
static void I2S_Config(void)
{
    I2S_InitTypeDef I2S_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable SPI1 and SPI2 APB clocks */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

    /* Enable GPIOA, GPIOB clocks */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB, ENABLE);

    /* I2S1 Pins configuration */

    /* Configure pins as AF */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Connect pin to Periph */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_0);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_0);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_0);

    /* I2S2 Pins configuration */

    /* Configure pins as AF */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* Connect pin to Periph */
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_8);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_8);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_8);

    /* I2S1 peripheral configuration */
    I2S_InitStructure.I2S_Standard = I2S_Standard_Phillips;
    I2S_InitStructure.I2S_DataFormat = I2S_DataFormat_16b;
    I2S_InitStructure.I2S_MCLKOutput = I2S_MCLKOutput_Disable;
    I2S_InitStructure.I2S_AudioFreq = I2S_AudioFreq_16k;
    I2S_InitStructure.I2S_CPOL = I2S_CPOL_Low;

    /* I2S Master Transmitter configuration */
    I2S_InitStructure.I2S_Mode = I2S_Mode_MasterTx;
    I2S_Init(SPI1, &I2S_InitStructure);

    /* I2S2 peripheral configuration */
    I2S_InitStructure.I2S_Mode = I2S_Mode_SlaveRx;
    I2S_Init(SPI2, &I2S_InitStructure);

    /* SPI1 IRQ Channel configuration */
    NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* SPI2 IRQ Channel configuration */
    NVIC_InitStructure.NVIC_IRQChannel = SPI2_IRQn;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable the I2S2 RxNE interrupt */
    SPI_I2SITConfig(SPI2, SPI_I2S_IT_RXNE, ENABLE);

    /* Enable the I2S2 */
    I2S_Cmd(SPI2, ENABLE);
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
  */
static TestStatus Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer1 != *pBuffer2)
        {
            return FAILED;
        }

        pBuffer1++;
        pBuffer2++;
    }

    return PASSED;
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



