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

/** @addtogroup I2C_EEPROM
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define EE_ADDR1      0x00
#define EE_ADDR2      0x01

#define WRITEBUF_LEN1   5
#define WRITEBUF_LEN2   9
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t WriteBuf1[] = {0x05, 0x04, 0x03, 0x02, 0x01};
uint8_t WriteBuf2[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};

uint8_t ReadBuf[10] = {0};
volatile uint16_t NumDataRead = 0;

/* Private function prototypes -----------------------------------------------*/
static void DEBUG_USARTx_Config(uint32_t Baud);
static uint8_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    uint8_t count;

    /* LED Init */
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);

    /* USARTx Configured for printf */
    DEBUG_USARTx_Config(115200);

    /* Initialize the I2C EEPROM driver */
    sEE_Init();

    debug("I2C_EEPROM example is running!\n");

    /* First write in the memory followed by a read of the written data -------*/
    printf("First write eeprom... \n");
    sEE_WriteBuffer(WriteBuf1, EE_ADDR1, WRITEBUF_LEN1);
    printf("First write eeprom End!");

    printf("\nFirst read eeprom :\n");
    NumDataRead = WRITEBUF_LEN1;
    sEE_ReadBuffer(ReadBuf, EE_ADDR1, (uint16_t *)(&NumDataRead));

    for (count = 0; count < WRITEBUF_LEN1; count++)
    {
        printf("%02x ", ReadBuf[count]);
    }

    /* Check if the data written to the memory is read correctly */
    if (Buffercmp(ReadBuf, WriteBuf1, WRITEBUF_LEN1))
    {
        printf("\nFirst Data verification is PASSED!\n");
        HK_EVAL_LEDOn(LED1);
        HK_EVAL_LEDOn(LED2);
    }
    else
    {
        printf("\nFirst Data verification is FAILED!\n");
        HK_EVAL_LEDOff(LED1);
        HK_EVAL_LEDOff(LED2);
    }

    /* Second write in the memory followed by a read of the written data -------*/
    /* Write on I2C EEPROM from EE_ADDR2 */
    printf("Second write eeprom... \n");
    sEE_WriteBuffer(WriteBuf2, EE_ADDR2, WRITEBUF_LEN2);
    printf("Second write eeprom End!");

    printf("\nSecond read eeprom :\n");
    NumDataRead = WRITEBUF_LEN2;
    sEE_ReadBuffer(ReadBuf, EE_ADDR2, (uint16_t *)(&NumDataRead));

    for (count = 0; count < WRITEBUF_LEN2; count++)
    {
        printf("%02x ", ReadBuf[count]);
    }

    /* Check if the data written to the memory is read correctly */
    if (Buffercmp(ReadBuf, WriteBuf2, WRITEBUF_LEN2))
    {
        printf("\nSecond Data verification is PASSED!");
        HK_EVAL_LEDOn(LED1);
        HK_EVAL_LEDOn(LED2);
    }
    else
    {
        printf("\nSecond Data verification is FAILED!");
        HK_EVAL_LEDOff(LED1);
        HK_EVAL_LEDOff(LED2);
    }


    /* Free all used resources */
    sEE_DeInit();

    while (1)
    {
    }
}

/**
  * @brief  Configure the USARTx Device for printf
  * @param  Baud: The USARTx BaudRate
  * @retval None
  */
static void DEBUG_USARTx_Config(uint32_t Baud)
{
    USART_InitTypeDef USART_InitStructure;

    /* USARTx configured as follow:
    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - Stop Bit = 1 Stop Bit
    - Parity = No Parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = Baud;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    HK_EVAL_COMInit(COM1, &USART_InitStructure);
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval 1: pBuffer1 identical to pBuffer2
  *         0: pBuffer1 differs from pBuffer2
  */
static uint8_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer1 != *pBuffer2)
        {
            return 0;
        }

        pBuffer1++;
        pBuffer2++;
    }

    return 1;
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


