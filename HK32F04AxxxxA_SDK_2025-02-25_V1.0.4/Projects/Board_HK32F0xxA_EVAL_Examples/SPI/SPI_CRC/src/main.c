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

/** @addtogroup SPI_CRC
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BufferSize  32

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
SPI_InitTypeDef  SPI_InitStructure;
uint16_t SPI1_Buffer_Tx[BufferSize] = {0x0102, 0x0304, 0x0506, 0x0708, 0x090A, 0x0B0C,
                                       0x0D0E, 0x0F10, 0x1112, 0x1314, 0x1516, 0x1718,
                                       0x191A, 0x1B1C, 0x1D1E, 0x1F20, 0x2122, 0x2324,
                                       0x2526, 0x2728, 0x292A, 0x2B2C, 0x2D2E, 0x2F30,
                                       0x3132, 0x3334, 0x3536, 0x3738, 0x393A, 0x3B3C,
                                       0x3D3E, 0x3F40
                                      };
uint16_t SPI2_Buffer_Tx[BufferSize] = {0x5152, 0x5354, 0x5556, 0x5758, 0x595A, 0x5B5C,
                                       0x5D5E, 0x5F60, 0x6162, 0x6364, 0x6566, 0x6768,
                                       0x696A, 0x6B6C, 0x6D6E, 0x6F70, 0x7172, 0x7374,
                                       0x7576, 0x7778, 0x797A, 0x7B7C, 0x7D7E, 0x7F80,
                                       0x8182, 0x8384, 0x8586, 0x8788, 0x898A, 0x8B8C,
                                       0x8D8E, 0x8F90
                                      };
uint16_t SPI1_Buffer_Rx[BufferSize], SPI2_Buffer_Rx[BufferSize];
uint32_t TxIdx = 0, RxIdx = 0;
__IO uint16_t CRC1Value = 0, CRC2Value = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void TimeOut_UserCallback(void);
static TestStatus Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength);
static void SPI_Config(void);

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


    /* SPIx configuration ------------------------------------------------------*/
    SPI_Config();

    /* Transfer procedure */
    while (TxIdx < BufferSize - 1)
    {
        /* Wait for SPIx Tx buffer empty */
        while (SPI_I2SGetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET)
        {

        }

        /* Send SPIxx data */
        SPI_I2SSendData16(SPIxx, SPI2_Buffer_Tx[TxIdx]);

        /* Send SPIx data */
        SPI_I2SSendData16(SPIx, SPI1_Buffer_Tx[TxIdx++]);

        /* Wait for SPIxx data reception */
        while (SPI_I2SGetFlagStatus(SPIxx, SPI_I2S_FLAG_RXNE) == RESET)
        {

        }

        /* Read SPIxx received data */
        SPI2_Buffer_Rx[RxIdx] = SPI_I2SReceiveData16(SPIxx);

        /* Wait for SPIx data reception */
        while (SPI_I2SGetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET)
        {

        }

        /* Read SPIx received data */
        SPI1_Buffer_Rx[RxIdx++] = SPI_I2SReceiveData16(SPIx);
    }

    /* Wait for SPIx Tx buffer empty */
    while (SPI_I2SGetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET)
    {

    }

    /* Wait for SPIxx Tx buffer empty */
    while (SPI_I2SGetFlagStatus(SPIxx, SPI_I2S_FLAG_TXE) == RESET)
    {

    }

    /* Send last SPI2_Buffer_Tx data */
    SPI_I2SSendData16(SPIxx, SPI2_Buffer_Tx[TxIdx]);
    /* Enable SPIxx CRC transmission */
    SPI_TransmitCRC(SPIxx);
    /* Send last SPI1_Buffer_Tx data */
    SPI_I2SSendData16(SPIx, SPI1_Buffer_Tx[TxIdx]);
    /* Enable SPIx CRC transmission */
    SPI_TransmitCRC(SPIx);

    /* Wait for SPIx last data reception */
    while (SPI_I2SGetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET)
    {

    }

    /* Read SPIx last received data */
    SPI1_Buffer_Rx[RxIdx] = SPI_I2SReceiveData16(SPIx);

    /* Wait for SPIxx last data reception */
    while (SPI_I2SGetFlagStatus(SPIxx, SPI_I2S_FLAG_RXNE) == RESET)
    {

    }

    /* Read SPIxx last received data */
    SPI2_Buffer_Rx[RxIdx] = SPI_I2SReceiveData16(SPIxx);

    /* Wait for SPIx data reception: CRC transmitted by SPIxx */
    while (SPI_I2SGetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET)
    {

    }

    /* Wait for SPIxx data reception: CRC transmitted by SPIx */
    while (SPI_I2SGetFlagStatus(SPIxx, SPI_I2S_FLAG_RXNE) == RESET)
    {

    }

    /* Check the received data with the send ones */
    TransferStatus1 = Buffercmp(SPI2_Buffer_Rx, SPI1_Buffer_Tx, BufferSize);
    TransferStatus2 = Buffercmp(SPI1_Buffer_Rx, SPI2_Buffer_Tx, BufferSize);
    /* TransferStatus1, TransferStatus2 = PASSED, if the data transmitted and received
       are correct */
    /* TransferStatus1, TransferStatus2 = FAILED, if the data transmitted and received
       are different */

    /* Test on the SPIx CRC Error flag */
    if ((SPI_I2SGetFlagStatus(SPIx, SPI_FLAG_CRCERR)) == SET)
    {
        TransferStatus2 = FAILED;
    }

    /* Test on the SPIxx CRC Error flag */
    if ((SPI_I2SGetFlagStatus(SPIxx, SPI_FLAG_CRCERR)) == SET)
    {
        TransferStatus1 = FAILED;
    }

    /* Did an error occur before generating CRC  */
    if ((TransferStatus1 == FAILED) || (TransferStatus2 == FAILED))
    {
        TimeOut_UserCallback();
    }

    /* Read SPIx received CRC value */
    CRC1Value = SPI_I2SReceiveData16(SPIx);
    /* Read SPIxx received CRC value */
    CRC2Value = SPI_I2SReceiveData16(SPIxx);

    while (1)
    {

    }
}

/**
  * @brief  Basic management of the timeout situation.
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
    SPI_InitTypeDef  SPI_InitStructure;

    /* Enable the SPI periph */
    RCC_APB2PeriphClockCmd(SPIx_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(SPIxx_CLK, ENABLE);

    /* Enable SCK, MOSI, MISO and NSS GPIO clocks */
    RCC_AHBPeriphClockCmd(SPIx_SCK_GPIO_CLK | SPIx_MISO_GPIO_CLK | SPIx_MOSI_GPIO_CLK, ENABLE);
    RCC_AHBPeriphClockCmd(SPIxx_SCK_GPIO_CLK | SPIxx_MISO_GPIO_CLK | SPIxx_MOSI_GPIO_CLK, ENABLE);

    /* spi1 AF */
    GPIO_PinAFConfig(SPIx_SCK_GPIO_PORT, SPIx_SCK_SOURCE, SPIx_SCK_AF);
    GPIO_PinAFConfig(SPIx_MOSI_GPIO_PORT, SPIx_MOSI_SOURCE, SPIx_MOSI_AF);
    GPIO_PinAFConfig(SPIx_MISO_GPIO_PORT, SPIx_MISO_SOURCE, SPIx_MISO_AF);

    /* spi2 AF */
    GPIO_PinAFConfig(SPIxx_SCK_GPIO_PORT, SPIxx_SCK_SOURCE, SPIxx_SCK_AF);
    GPIO_PinAFConfig(SPIxx_MOSI_GPIO_PORT, SPIxx_MOSI_SOURCE, SPIxx_MOSI_AF);
    GPIO_PinAFConfig(SPIxx_MISO_GPIO_PORT, SPIxx_MISO_SOURCE, SPIxx_MISO_AF);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;

    /* SPI SCK pin configuration */
    GPIO_InitStructure.GPIO_Pin = SPIx_SCK_PIN;
    GPIO_Init(SPIx_SCK_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SPIxx_SCK_PIN;
    GPIO_Init(SPIxx_SCK_GPIO_PORT, &GPIO_InitStructure);

    /* SPI  MOSI pin configuration */
    GPIO_InitStructure.GPIO_Pin =  SPIx_MOSI_PIN;
    GPIO_Init(SPIx_MOSI_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin =  SPIxx_MOSI_PIN;
    GPIO_Init(SPIxx_MOSI_GPIO_PORT, &GPIO_InitStructure);

    /* SPI MISO pin configuration */
    GPIO_InitStructure.GPIO_Pin = SPIx_MISO_PIN;
    GPIO_Init(SPIx_MISO_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SPIxx_MISO_PIN;
    GPIO_Init(SPIxx_MISO_GPIO_PORT, &GPIO_InitStructure);

    /* SPIx configuration -------------------------------------------------------*/
    SPI_I2SDeInit(SPIx);
    SPI_I2SDeInit(SPIxx);
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPIx, &SPI_InitStructure);

    /* SPIxx configuration ------------------------------------------------------*/
    SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
    SPI_Init(SPIxx, &SPI_InitStructure);

    /* Initialize the FIFO threshold */
    SPI_RxFIFOThresholdConfig(SPIx, SPI_RxFIFOThreshold_HF);
    SPI_RxFIFOThresholdConfig(SPIxx, SPI_RxFIFOThreshold_HF);

    /* Enable SPI CRC calculation */
    SPI_CalculateCRC(SPIx, ENABLE);
    SPI_CalculateCRC(SPIxx, ENABLE);

    /* Enable the SPI peripheral */
    SPI_Cmd(SPIx, ENABLE);
    SPI_Cmd(SPIxx, ENABLE);
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



