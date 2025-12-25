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

/** @addtogroup SPI_InternalExchangeDMA
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BufferSize  32

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t SPI_MASTER_Buffer_Tx[BufferSize] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                                            0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C,
                                            0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12,
                                            0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
                                            0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E,
                                            0x1F, 0x20
                                           };
uint8_t SPI_SLAVE_Buffer_Rx[BufferSize];
__IO uint8_t TxIdx = 0;
volatile TestStatus TransferStatus = FAILED;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void TimeOut_UserCallback(void);
static TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
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
    while (TxIdx < BufferSize)
    {
        /* Wait for SPI_MASTER Tx buffer empty */
        while (SPI_I2SGetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET)
        {
        }

        /* Send SPI_MASTER data */
        SPI_SendData8(SPIx, SPI_MASTER_Buffer_Tx[TxIdx++]);
    }

    /* Wait for DMA1 channel4 transfer complete */
    while (!DMA_GetFlagStatus(SPIxx_Rx_DMA_FLAG))
    {
    }

    /* Check the correctness of written data */
    TransferStatus = Buffercmp(SPI_SLAVE_Buffer_Rx, SPI_MASTER_Buffer_Tx, BufferSize);
    /* TransferStatus = PASSED, if the transmitted and received data
    are equal */
    /* TransferStatus = FAILED, if the transmitted and received data
    are different */

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
    DMA_InitTypeDef DMA_InitStructure;

    /* Enable the SPI periph */
    RCC_APB2PeriphClockCmd(SPIx_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(SPIxx_CLK, ENABLE);

    /* Enable the DMA periph */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

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

    /* SPI_SLAVE_Rx_DMA_Channel configuration ---------------------------------------------*/
    DMA_DeInit(SPIxx_Rx_DMA_Channel);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SPIxx_DR_Base;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SPI_SLAVE_Buffer_Rx;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = BufferSize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(SPIxx_Rx_DMA_Channel, &DMA_InitStructure);

    /* SPIx configuration -------------------------------------------------------*/
    SPI_I2SDeInit(SPIx);
    SPI_I2SDeInit(SPIxx);
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
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
    SPI_RxFIFOThresholdConfig(SPIx, SPI_RxFIFOThreshold_QF);
    SPI_RxFIFOThresholdConfig(SPIxx, SPI_RxFIFOThreshold_QF);

    /* Enable SPI_SLAVE Rx request */
    SPI_I2SDMACmd(SPIxx, SPI_I2S_DMAReq_Rx, ENABLE);

    /* Enable the SPI peripheral */
    SPI_Cmd(SPIx, ENABLE);
    SPI_Cmd(SPIxx, ENABLE);

    /* Enable DMA1 Channel4 */
    DMA_Cmd(SPIxx_Rx_DMA_Channel, ENABLE);
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
  */
static TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
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



