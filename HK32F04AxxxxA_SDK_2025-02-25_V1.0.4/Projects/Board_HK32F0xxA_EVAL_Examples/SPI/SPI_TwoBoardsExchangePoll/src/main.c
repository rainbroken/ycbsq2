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

/** @addtogroup SPI_TwoBoardsExchangePoll
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t TxBuffer[] = "SPI Interrupt Example: Communication between two SPI using Interrupts";
uint8_t RxBuffer [RXBUFFERSIZE];

__IO JOYState_TypeDef PressedButton  = JOY_NONE;
__IO uint32_t TimeOut = 0x0;
__IO uint8_t Counter = 0x00;

/* Private function prototypes -----------------------------------------------*/
#ifdef SPI_MASTER
    static void SPI_SendData(SPI_TypeDef* SPINum, uint8_t *Data, uint32_t cnt);
#else
    static void SPI_ReceiveData(SPI_TypeDef* SPINum, uint8_t *Data, uint32_t cnt);
#endif
static void SPI_Config(void);
static void SysTickConfig(void);
static void TimeOut_UserCallback(void);
#ifndef SPI_MASTER
    static TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength, uint8_t DataMask);
#endif
static void Fill_Buffer(uint8_t *pBuffer, uint16_t BufferLength);
#ifdef SPI_MASTER
    static JOYState_TypeDef Read_Joystick(void);
#endif

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

    /* SPI configuration ------------------------------------------------------*/
    SPI_Config();

    /* SysTick configuration ---------------------------------------------------*/
    SysTickConfig();

    /* Initialize push-buttons */
    HK_EVAL_PBInit(BUTTON_SEL, BUTTON_MODE_GPIO);

    /* Clear the RxBuffer */
    Fill_Buffer(RxBuffer, TXBUFFERSIZE);

    /* Master board configuration ------------------------------------------------*/
#ifdef SPI_MASTER
    PressedButton = Read_Joystick();

    while (PressedButton == JOY_NONE)
    {
        PressedButton = Read_Joystick();
    }

    if (PressedButton != JOY_NONE)
    {
        SPI_SendData(SPIx, TxBuffer, RXBUFFERSIZE);
    }

    /* Slave board configuration ------------------------------------------------*/
#else
    SPI_ReceiveData(SPIx, RxBuffer, RXBUFFERSIZE);

    if (Buffercmp(TxBuffer, RxBuffer, RXBUFFERSIZE, SPI_DATAMASK) != PASSED)
    {
        TimeOut_UserCallback();
    }

#endif

    while (1)
    {

    }
}

#ifdef SPI_MASTER
/**
  * @brief  SPI send data function.
  * @param  SPINum: spi number.
  * @param  Data: Send data.
  * @param  cnt: The length of data sent.
  * @retval None
  */
static void SPI_SendData(SPI_TypeDef* SPINum, uint8_t *Data, uint32_t cnt)
{
    uint32_t i = 0;

    for (i = 0; i < cnt; i++)
    {
        /* Wait until end of data transfer or time out*/
        TimeOut = USER_TIMEOUT;

        while ((SPI_I2SGetFlagStatus(SPINum, SPI_I2S_FLAG_TXE) == RESET) && (TimeOut != 0x00))
        {
        }

        if (TimeOut == 0)
        {
            TimeOut_UserCallback();
        }

        SPI_SendData8(SPINum, Data[i]);
    }
}

#else
/**
  * @brief  SPI receive data function.
  * @param  SPINum: spi number.
  * @param  Data: Receive data.
  * @param  cnt: The length of data received.
  * @retval None
  */
static void SPI_ReceiveData(SPI_TypeDef* SPINum, uint8_t *Data, uint32_t cnt)
{
    uint32_t i = 0;

    for (i = 0; i < cnt; i++)
    {
        /* Wait until end of data transfer or time out*/
        TimeOut = USER_TIMEOUT;

        while (SPI_I2SGetFlagStatus(SPINum, SPI_I2S_FLAG_RXNE) == RESET)
        {
        }

        Data[i] = SPI_ReceiveData8(SPINum);
    }
}
#endif

/**
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval None
  */
static void TimeOut_UserCallback(void)
{
    /* User can add his own implementation to manage TimeOut Communication failure */

    /* Block communication and all processes */
    while (1)
    {
    }
}

/**
  * @brief  Configures the SPI Peripheral.
  * @param  None
  * @retval None
  */
static void SPI_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;

    /* Enable the SPI periph */
    RCC_APB2PeriphClockCmd(SPIx_CLK, ENABLE);

    /* Enable SCK, MOSI, MISO and NSS GPIO clocks */
    RCC_AHBPeriphClockCmd(SPIx_SCK_GPIO_CLK | SPIx_MISO_GPIO_CLK | SPIx_MOSI_GPIO_CLK, ENABLE);

    GPIO_PinAFConfig(SPIx_SCK_GPIO_PORT, SPIx_SCK_SOURCE, SPIx_SCK_AF);
    GPIO_PinAFConfig(SPIx_MOSI_GPIO_PORT, SPIx_MOSI_SOURCE, SPIx_MOSI_AF);
    GPIO_PinAFConfig(SPIx_MISO_GPIO_PORT, SPIx_MISO_SOURCE, SPIx_MISO_AF);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;

    /* SPI SCK pin configuration */
    GPIO_InitStructure.GPIO_Pin = SPIx_SCK_PIN;
    GPIO_Init(SPIx_SCK_GPIO_PORT, &GPIO_InitStructure);

    /* SPI  MOSI pin configuration */
    GPIO_InitStructure.GPIO_Pin =  SPIx_MOSI_PIN;
    GPIO_Init(SPIx_MOSI_GPIO_PORT, &GPIO_InitStructure);

    /* SPI MISO pin configuration */
    GPIO_InitStructure.GPIO_Pin = SPIx_MISO_PIN;
    GPIO_Init(SPIx_MISO_GPIO_PORT, &GPIO_InitStructure);

    /* SPI configuration -------------------------------------------------------*/
    SPI_I2SDeInit(SPIx);
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
#ifdef SPI_MASTER
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
#else
    SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
#endif
    SPI_InitStructure.SPI_DataSize = SPI_DATASIZE;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;

    SPI_Init(SPIx, &SPI_InitStructure);

    /* Configure the SPI interrupt priority */
    NVIC_InitStructure.NVIC_IRQChannel = SPIx_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Initialize the FIFO threshold */
    SPI_RxFIFOThresholdConfig(SPIx, SPI_RxFIFOThreshold_QF);

    /* Enable the SPI peripheral */
    SPI_Cmd(SPIx, ENABLE);
}

/**
  * @brief  Configure a SysTick Base time to 10 ms.
  * @param  None
  * @retval None
  */
static void SysTickConfig(void)
{
    /* Setup SysTick Timer for 10ms interrupts  */
    if (SysTick_Config(SystemCoreClock / 100))
    {
        /* Capture error */
        while (1)
        {
        }
    }

    /* Configure the SysTick handler priority */
    NVIC_SetPriority(SysTick_IRQn, 0x0);
}

#ifndef SPI_MASTER
/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
  */
static TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength, uint8_t DataMask)
{
    while (BufferLength--)
    {
        if (((*pBuffer1) & DataMask) != *pBuffer2)
        {
            return FAILED;
        }

        pBuffer1++;
        pBuffer2++;
    }

    return PASSED;
}
#endif

/**
  * @brief  Fills buffer.
  * @param  pBuffer: pointer on the Buffer to fill
  * @param  BufferLength: size of the buffer to fill
  * @retval None
  */
static void Fill_Buffer(uint8_t *pBuffer, uint16_t BufferLength)
{
    uint16_t index = 0;

    /* Put in global buffer same values */
    for (index = 0; index < BufferLength; index++ )
    {
        pBuffer[index] = 0x00;
    }
}

#ifdef SPI_MASTER
/**
  * @brief  Reads key from evaluationboard.
  * @param  None
  * @retval None
  */
static JOYState_TypeDef Read_Joystick(void)
{
    /* "JOY_SEL" key is pressed */
    if (HK_EVAL_PBGetState(BUTTON_SEL))
    {
        while (HK_EVAL_PBGetState(BUTTON_SEL) == RESET)
        {
        }

        return JOY_SEL;
    }
    /* No key is pressed */
    else
    {
        return JOY_NONE;
    }
}
#endif

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



