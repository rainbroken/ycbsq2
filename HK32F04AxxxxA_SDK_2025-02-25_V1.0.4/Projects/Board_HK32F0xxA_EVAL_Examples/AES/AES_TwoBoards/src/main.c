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

/** @addtogroup AES_TwoBoards
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
AES_InitTypeDef AES_InitStructure;
AES_KeyInitTypeDef  AES_KeyInitStructure;
USART_InitTypeDef USART_InitStructure;

#ifdef AES_BoardA
/* Board A encrypts plaintext data */
uint8_t BoardA_TxBuffer[AES_TEXT_SIZE] =
{
    0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
    0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a
};

/* The ciphertext array stored on board A after encryption is also the array that board A sends to board B */
uint8_t BoardA_CipherText[AES_TEXT_SIZE];

/*  After board A is correctly encrypted, the standard ciphertext must be correct */
uint8_t BoardA_ExpectedCipherText[16] = {0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60,
                                         0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97
                                        };
/* The key used for encryption and decryption of board A and board B */
uint8_t BoardAB_EncryptionKey[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
                                     0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
                                    };

/* Cache of data received by board A */
uint8_t BoardA_RxBuffer[AES_TEXT_SIZE];
uint8_t RxIndex = 0;
uint8_t RxDone = 0;

#else
/* Board A encrypts plaintext data */
uint8_t BoardA_TxBuffer[AES_TEXT_SIZE] =
{
    0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
    0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a
};


/*  After board A is correctly encrypted, the standard ciphertext must be correct  */
uint8_t BoardA_ExpectedCipherText[16] = {0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60,
                                         0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97
                                        };
/* The key used for encryption and decryption of board A and board B */
uint8_t BoardAB_EncryptionKey[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
                                     0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
                                    };

/* Cache of data received by board B */
uint8_t BoardB_RxBuffer[AES_TEXT_SIZE];
uint8_t RxIndex = 0;
uint8_t RxDone = 0;

/* After board B receives the ciphertext and performs the decryption algorithm,
    the plaintext array stored on board B is also the array that Board B sends to board A */
uint8_t BoardB_ComputedPlainText[AES_TEXT_SIZE];
#endif

/* Private function prototypes -----------------------------------------------*/
static ErrorStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
#ifdef AES_BoardA
    static void Display_PlainData(uint32_t datalength);
    static void Display_EncryptedData(uint8_t mode, uint16_t keysize, uint32_t datalength);
#else
    static void Display_DecryptedData(uint8_t mode, uint16_t keysize, uint32_t datalength);
#endif
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
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

    /* Initialize USART2 */

    /* Enable GPIO clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    /* Enable USART clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    /* Connect PXx to USARTx_Tx */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_3);

    /* Connect PXx to USARTx_Rx */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_3);

    /* Configure USART Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure USART Rx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* USART configuration */
    USART_Init(USART2, &USART_InitStructure);

    /* Enable USART */
    USART_Cmd(USART2, ENABLE);
    USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);

    /* Enable and set USART2 Interrupt to the lowest priority */
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0x03;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#ifdef AES_BoardA

    /* Initialize AES */
    printf("AES Two Boards Example\r\n");
    AES_DeInit();
    RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_AES, ENABLE);
    printf("board A: This is board A\r\n");

    /* Display Plain Data*/
    Display_PlainData(AES_TEXT_SIZE);

    /* Encrypt the plaintext message*/
    AES_ECB_Encrypt(BoardAB_EncryptionKey, 128, BoardA_TxBuffer, AES_TEXT_SIZE, BoardA_CipherText);

    /* Read the CipherText and check content correctness */
    if (Buffercmp(BoardA_ExpectedCipherText, BoardA_CipherText, AES_TEXT_SIZE) == SUCCESS)
    {
        printf("board A: AES ECB 128Keysize Encrypted ok\r\n");

        /* Display encrypted Data*/
        Display_EncryptedData(ECB, 128, AES_TEXT_SIZE);
        printf("board A: Send CipherText to Board B ...\r\n");

        /* send encrypted Data to board B*/
        for (uint32_t i = 0; i < AES_TEXT_SIZE; i++)
        {
            USART_SendData(USART2, (unsigned char) BoardA_CipherText[i]);

            while (USART_GetFlagStatus(USART2, USART_FLAG_TC) != SET)
            {
            }
        }

        printf("board A: Send CipherText to Board B Finished ...\r\n");
    }
    else
    {
        printf("board A: AES ECB 128Keysize Encrypted Fail\r\n");
    }

    /* Infinite loop */
    while (1)
    {
        if (RxDone)
        {
            RxDone = 0;

            /* Perform data check on the received data */
            if (Buffercmp(BoardA_TxBuffer, BoardA_RxBuffer, AES_TEXT_SIZE) == SUCCESS)
            {
                printf("board A: Received vaild\r\n");

                /* Display Plain Data*/
                Display_PlainData(AES_TEXT_SIZE);
            }
            else
            {
                printf("board A: Received invaild\r\n");
            }
        }
    }

#else
    printf("AES Two Boards Example\r\n");
    /* Initialize AES */
    AES_DeInit();
    RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_AES, ENABLE);
    printf("board B: This is board B\r\n");

    /* Infinite loop */
    while (1)
    {
        if (RxDone)
        {
            RxDone = 0;

            /* Perform data check on the received data */
            if (Buffercmp(BoardA_ExpectedCipherText, BoardB_RxBuffer, AES_TEXT_SIZE) == SUCCESS)
            {
                printf("board B: Received vaild\r\n");
            }
            else
            {
                printf("board B: Received invaild\r\n");
            }

            /*=====================================================
                Decryption in ECB mode
            ======================================================*/
            /****************************************/
            /*                           AES 128   **/
            /****************************************/
            /* Decrypt the plaintext message  */
            AES_ECB_Decrypt( BoardAB_EncryptionKey, 128, BoardB_RxBuffer, AES_TEXT_SIZE, BoardB_ComputedPlainText);

            /* Read the CipherText and check content correctness */
            if (Buffercmp(BoardA_TxBuffer, BoardB_ComputedPlainText, AES_TEXT_SIZE) == SUCCESS)
            {
                printf("board B: AES ECB 128Keysize Decrypted ok\r\n");
                /* Display decrypted data*/
                Display_DecryptedData(ECB, 128, AES_TEXT_SIZE);
                printf("board B: Send BoardB_ComputedPlainText to Board A ...\r\n");

                /* send encrypted Data to board A*/
                for (uint32_t i = 0; i < AES_TEXT_SIZE; i++)
                {
                    USART_SendData(USART2, (unsigned char) BoardB_ComputedPlainText[i]);

                    while (USART_GetFlagStatus(USART2, USART_FLAG_TC) != SET)
                    {
                    }
                }

                printf("board B: Send BoardB_ComputedPlainText to Board A Finished ...\r\n");
            }
            else
            {
                printf("AES ECB 128Keysize Decrypted  Fail\r\n");
            }
        }
    }

#endif
}

/**
  * @brief  Compares two 8-bit buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval - SUCCESS: pBuffer1 identical to pBuffer2
  *         - ERROR: pBuffer1 differs from pBuffer2
  */
ErrorStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer1 != *pBuffer2)
        {
            return ERROR;
        }

        pBuffer1++;
        pBuffer2++;
    }

    return SUCCESS;
}

#ifdef AES_BoardA

/**
  * @brief  Display Plain Data
  * @param  datalength: length of the data to display
  * @retval None
  */
static void Display_PlainData(uint32_t datalength)
{
    uint32_t BufferCounter = 0;
    uint32_t count = 0;
    printf(" ===========================================\n\r");
    printf(" Plain Data :\n\r");
    printf(" -------------------------------------------\n\r");

    for (BufferCounter = 0; BufferCounter < datalength; BufferCounter++)
    {
        printf("[0x%02X]", BoardA_TxBuffer[BufferCounter]);
        count++;

        if (count == 16)
        {
            count = 0;
            printf("  Block %d \n\r", BufferCounter / 16);
        }
    }

    printf(" -------------------------------------------\n\r");
}

/**
  * @brief  Display Encrypted Data
  * @param  mode: chaining mode
  * @param  keysize: AES key size used
  * @param  datalength: length of the data to display
  * @retval None
  */
static void Display_EncryptedData(uint8_t mode, uint16_t keysize, uint32_t datalength)
{
    uint32_t BufferCounter = 0;
    uint32_t count = 0;
    printf("\n\r =======================================\n\r");
    printf(" Encrypted Data with AES %d  Mode  ", keysize );

    if (mode == ECB)
    {
        printf("ECB\n\r");
    }
    else
    {
    }

    printf(" -------------------------------------------\n\r");

    for (BufferCounter = 0; BufferCounter < datalength; BufferCounter++)
    {
        printf("[0x%02X]", BoardA_CipherText[BufferCounter]);
        count++;

        if (count == 16)
        {
            count = 0;
            printf(" Block %d \n\r", BufferCounter / 16);
        }
    }

    printf(" -------------------------------------------\n\r");
    printf(" ===========================================\n\r");
}

/**
  * @brief  Encrypt using AES in ECB Mode
  * @param  Key: Key used for AES algorithm.
    * @param  Keysize: length of the Key, must be a 128, 192 or 256.
  * @param  Input: pointer to the Input buffer.
  * @param  Ilength: length of the Input buffer, must be a multiple of 16 bytes.
  * @param  Output: pointer to the returned buffer.
  * @retval An ErrorStatus enumeration value:
  *         - SUCCESS: Operation done
  *         - ERROR: Operation failed
  */
ErrorStatus AES_ECB_Encrypt(uint8_t* Key, uint16_t Keysize, uint8_t* Input, uint32_t Ilength, uint8_t* Output)
{
    AES_InitTypeDef AES_InitStructure;
    AES_KeyInitTypeDef  AES_KeyInitStructure = {0};
    ErrorStatus status = SUCCESS;
    uint32_t keyaddr    = (uint32_t)Key;
    uint32_t inputaddr  = (uint32_t)Input;
    uint32_t outputaddr = (uint32_t)Output;
    __IO uint32_t counter = 0;
    uint32_t ccstatus = 0;
    uint32_t i = 0;

    /* AES Key config */
    switch (Keysize)
    {
        case 128:
            AES_InitStructure.AES_KeySize = AES_KEYSIZE_128B;
            AES_KeyInitStructure.AES_Key3 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key2 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key1 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key0 = __REV(*(uint32_t*)(keyaddr));
            break;

        case 192:
            AES_InitStructure.AES_KeySize = AES_KEYSIZE_192B;
            AES_KeyInitStructure.AES_Key5 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key4 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key3 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key2 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key1 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key0 = __REV(*(uint32_t*)(keyaddr));
            break;

        case 256:
            AES_InitStructure.AES_KeySize = AES_KEYSIZE_256B;
            AES_KeyInitStructure.AES_Key7 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key6 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key5 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key4 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key3 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key2 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key1 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key0 = __REV(*(uint32_t*)(keyaddr));
            break;

        default:
            break;
    }

    /* AES Key initialisation */
    AES_KeyInit(&AES_KeyInitStructure);
    /* AES configuration */
    AES_InitStructure.AES_Operation = AES_Operation_Encryp;
    AES_Init(&AES_InitStructure);
    /* Enable AES */
    AES_Cmd(ENABLE);

    for (i = 0; ((i < Ilength) && (status != ERROR)); i += 16)
    {
        /* Write the Input block in the IN FIFO */
        AES_WriteSubData(__REV(*(uint32_t*)(inputaddr)));
        inputaddr += 4;
        AES_WriteSubData(__REV(*(uint32_t*)(inputaddr)));
        inputaddr += 4;
        AES_WriteSubData(__REV(*(uint32_t*)(inputaddr)));
        inputaddr += 4;
        AES_WriteSubData(__REV(*(uint32_t*)(inputaddr)));
        inputaddr += 4;
        /* Wait for CCF flag to be set (Wait until the complete message has been processed) */
        counter = 0;

        do
        {
            ccstatus = AES_GetFlagStatus(AES_FLAG_CCF);
            counter++;
        } while ((counter != AES_CC_TIMEOUT) && (ccstatus == RESET));

        if (ccstatus == RESET)
        {
            status = ERROR;
        }
        else
        {
            /* Clear CCF flag */
            AES_ClearFlag(AES_FLAG_CCF);

            /* Read cipher text */
            *(uint32_t*)(outputaddr) = __REV(AES_ReadSubData());
            outputaddr += 4;
            *(uint32_t*)(outputaddr) = __REV(AES_ReadSubData());
            outputaddr += 4;
            *(uint32_t*)(outputaddr) = __REV(AES_ReadSubData());
            outputaddr += 4;
            *(uint32_t*)(outputaddr) = __REV(AES_ReadSubData());
            outputaddr += 4;
        }
    }

    /* Disable AES before starting new processing */
    AES_Cmd(DISABLE);
    return status;
}

#else

/**
  * @brief  Display Decrypted Data
  * @param  mode: chaining mode
  * @param  keysize: AES key size used
  * @param  datalength: length of the data to display
  * @retval None
  */
static void Display_DecryptedData(uint8_t mode, uint16_t keysize, uint32_t datalength)
{
    uint32_t BufferCounter = 0;
    uint32_t count = 0;
    printf("\n\r =======================================\n\r");
    printf(" Decrypted Data with AES %d  Mode  ", keysize );

    if (mode == ECB)
    {
        printf("ECB\n\r");
    }
    else
    {
    }

    printf(" -------------------------------------------\n\r");

    for (BufferCounter = 0; BufferCounter < datalength; BufferCounter++)
    {
        printf("[0x%02X]", BoardB_ComputedPlainText[BufferCounter]);
        count++;

        if (count == 16)
        {
            count = 0;
            printf(" Block %d \n\r", BufferCounter / 16);
        }
    }

    printf(" -------------------------------------------\n\r");
    printf(" ===========================================\n\r");
}

/**
  * @brief  Decrypt using AES in ECB Mode
  * @param  Key: Key used for AES algorithm.
  * @param  Keysize: length of the Key, must be a 128, 192 or 256.
  * @param  Input: pointer to the Input buffer.
  * @param  Ilength: length of the Input buffer, must be a multiple of 16 bytes.
  * @param  Output: pointer to the returned buffer.
  * @retval An ErrorStatus enumeration value:
  *         - SUCCESS: Operation done
  *         - ERROR: Operation failed
  */
ErrorStatus AES_ECB_Decrypt(uint8_t* Key, uint16_t Keysize, uint8_t* Input, uint32_t Ilength, uint8_t* Output)
{
    AES_InitTypeDef AES_InitStructure;
    AES_KeyInitTypeDef  AES_KeyInitStructure = {0};
    ErrorStatus status = SUCCESS;
    uint32_t keyaddr    = (uint32_t)Key;
    uint32_t inputaddr  = (uint32_t)Input;
    uint32_t outputaddr = (uint32_t)Output;
    __IO uint32_t counter = 0;
    uint32_t ccstatus = 0;
    uint32_t i = 0;

    /* AES Key config */
    switch (Keysize)
    {
        case 128:
            AES_InitStructure.AES_KeySize = AES_KEYSIZE_128B;
            AES_KeyInitStructure.AES_Key3 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key2 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key1 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key0 = __REV(*(uint32_t*)(keyaddr));
            break;

        case 192:
            AES_InitStructure.AES_KeySize = AES_KEYSIZE_192B;
            AES_KeyInitStructure.AES_Key5 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key4 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key3 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key2 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key1 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key0 = __REV(*(uint32_t*)(keyaddr));
            break;

        case 256:
            AES_InitStructure.AES_KeySize = AES_KEYSIZE_256B;
            AES_KeyInitStructure.AES_Key7 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key6 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key5 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key4 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key3 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key2 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key1 = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4U;
            AES_KeyInitStructure.AES_Key0 = __REV(*(uint32_t*)(keyaddr));
            break;

        default:
            break;
    }

    /* AES configuration */
    AES_InitStructure.AES_Operation = AES_Operation_KeyDerivAndDecryp;
    AES_Init(&AES_InitStructure);
    /* AES Key initialisation */
    AES_KeyInit(&AES_KeyInitStructure);
    /* Enable AES */
    AES_Cmd(ENABLE);

    for (i = 0; ((i < Ilength) && (status != ERROR)); i += 16)
    {
        AES_KeyInit(&AES_KeyInitStructure);
        AES_WriteSubData(__REV(*(uint32_t*)(inputaddr)));
        inputaddr += 4;
        AES_WriteSubData(__REV(*(uint32_t*)(inputaddr)));
        inputaddr += 4;
        AES_WriteSubData(__REV(*(uint32_t*)(inputaddr)));
        inputaddr += 4;
        AES_WriteSubData(__REV(*(uint32_t*)(inputaddr)));
        inputaddr += 4;
        /* Wait for CCF flag to be set */
        counter = 0;

        do
        {
            ccstatus = AES_GetFlagStatus(AES_FLAG_CCF);
            counter++;
        } while ((counter != AES_CC_TIMEOUT) && (ccstatus == RESET));

        if (ccstatus == RESET)
        {
            status = ERROR;
        }
        else
        {
            /* Clear CCF flag */
            AES_ClearFlag(AES_FLAG_CCF);

            /* Read cipher text */
            *(uint32_t*)(outputaddr) = __REV(AES_ReadSubData());
            outputaddr += 4;
            *(uint32_t*)(outputaddr) = __REV(AES_ReadSubData());
            outputaddr += 4;
            *(uint32_t*)(outputaddr) = __REV(AES_ReadSubData());
            outputaddr += 4;
            *(uint32_t*)(outputaddr) = __REV(AES_ReadSubData());
            outputaddr += 4;
        }
    }

    /* Disable AES before starting new processing */
    AES_Cmd(DISABLE);
    return status;
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

