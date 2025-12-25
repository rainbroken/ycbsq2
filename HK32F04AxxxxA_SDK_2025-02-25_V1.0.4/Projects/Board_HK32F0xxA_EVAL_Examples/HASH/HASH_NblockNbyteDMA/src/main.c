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

/** @addtogroup HASH_NblockNbyteDMA
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define HASH_INPUTSEIZE             strlen((char const*)aInput)
#define HASH_TIMEOUT                0x1000U
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

uint8_t ubButtonPress = 0;
USART_InitTypeDef USART_InitStructure;

/* Store data for the user to select HASH with different sizes */
#if 1
    __ALIGN_BEGIN const uint8_t aInput[] __ALIGN_END = "The HK32F0xxA series is the result of a perfect symbiosis of the real-time control capabilities of an MCU and the signal processing performance of a DSP, and thus complements the HK32 portfolio with a new class of devices, digital signal controllers (DSC).";//256 byte
    /* The correct HASH information */
    //b127d3fc623120701ca45e242c405f2aba8226ed79bbec5f47a04f98b5662a33
#elif 0
    __ALIGN_BEGIN const uint8_t aInput[] __ALIGN_END = "The HK32F0xxA series is the result of a perfect symbiosis of the xxx";
    /* The correct HASH information */
    //44037560135cc2dff201a9ae401141c15e91cea505d857826d1ed5a5806e879f
#elif 0
    __ALIGN_BEGIN const uint8_t aInput[] __ALIGN_END = "The HK32F0xxA series is the result of a perfect symbiosis of the xxxx";
    /* The correct HASH information */
    //490ca8c20856aefdfb548290e0284b402cda8a39edbc36008de400cad0de917f
#else
    __ALIGN_BEGIN const uint8_t aInput[] __ALIGN_END = "abcd";//4
    /* The correct HASH information */
    //88d4266fd4e6338d13b845fcf289579d209c897823b9217da3e161936f031589
#endif
/* Private function prototypes -----------------------------------------------*/
HASH_MsgDigest MsgDigest;
/* Private functions ---------------------------------------------------------*/
static void Display_MainMessage(void);
static void Display_SHA256Digest(void);
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
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

    /* Configure HASH */
    HASH_Config();

    /* Wait for User push-button press to trigger random numbers generation */
    WaitForUserButtonPress();

    /* HASH DMA */
    HASH_Function_Handle();

    /* Infinite loop */
    while (1)
    {
    }
}

/**
  * @brief  Display the Display message.
  * @param  None
  * @retval None
  */
static void Display_MainMessage(void)
{
    uint32_t buffercounter = 0;
    printf("\n\r ======================================\n\r");
    printf(" ====  HASH Using DMA Example  ====\n\r");
    printf(" ======================================\n\r");
    printf(" ---------------------------------------\n\r");
    printf(" Text to be Hashed (%d bytes,%d bits):\n\r", HASH_INPUTSEIZE, HASH_INPUTSEIZE * 8);
    printf(" ---------------------------------------\n\r");

    for (buffercounter = 0; buffercounter < HASH_INPUTSEIZE; buffercounter++)
    {
        printf("%c", aInput[buffercounter]);

        if (((buffercounter % 31) == 0) && (buffercounter != 0))
        {
            printf("\n\r");
        }
    }
}

/**
  * @brief  Display the SHA256 digest.
  * @param  None
  * @retval None
  */
static void Display_SHA256Digest(void)
{
    printf("\n\r ---------------------------------------\n\r");
    printf(" SHA256 Message Digest (256 bits):\n\r");
    printf(" ---------------------------------------\n\r");
    printf(" H0 = [0x%08x]  \n\r", MsgDigest.Data[0]);
    printf(" H1 = [0x%08x]  \n\r", MsgDigest.Data[1]);
    printf(" H2 = [0x%08x]  \n\r", MsgDigest.Data[2]);
    printf(" H3 = [0x%08x]  \n\r", MsgDigest.Data[3]);
    printf(" H4 = [0x%08x]  \n\r", MsgDigest.Data[4]);
    printf(" H5 = [0x%08x]  \n\r", MsgDigest.Data[5]);
    printf(" H6 = [0x%08x]  \n\r", MsgDigest.Data[6]);
    printf(" H7 = [0x%08x]  \n\r", MsgDigest.Data[7]);
}

/**
  * @brief  Config HASH Clock and Init.
  * @retval None
  */
void HASH_Config(void)
{
    HASH_InitTypeDef HASH_InitStruct;
    DMA_InitTypeDef DMA_InitStruct;

    /* Enable the RCC clock */
    RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_HASH, ENABLE);

    /* Enable the DMA1 clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    HASH_DeInit();
    HASH_InitStruct.HASH_AlgoMode = HASH_AlgoMode_HASH ;
    HASH_InitStruct.HASH_AlgoSelection = HASH_AlgoSelection_SHA256;
    HASH_InitStruct.HASH_DataType = HASH_DataType_8b;
    HASH_Init(&HASH_InitStruct);

    DMA_Cmd(DMA1_Channel6, DISABLE);
    DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)aInput;
    DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t) & (HASH->DIN) ;
    DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;

    /* the cnt register of dma is 16 bits, that is, the maximum cannot exceed 65535 */
    DMA_InitStruct.DMA_BufferSize =  HASH_INPUTSEIZE / 4;
    DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
    DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
    DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel6, &DMA_InitStruct);
}

/**
  * @brief  This function configures HASH Handle.
  * @note   This function is show to:
  *         Display the SHA256 digest.
  * @retval None
  */
void HASH_Function_Handle(void)
{
    __IO uint16_t nbvalidbitsdata = 0;

    /* Display the original message */
    Display_MainMessage();

    HASH_DMACmd(ENABLE);
    DMA_Cmd(DMA1_Channel6, ENABLE);

    /* Wait until DMA Transfer completed */
    while (DMA_GetFlagStatus(DMA1_FLAG_TC6) == RESET)
    {
    }

    /* Wait until the Busy flag is RESET */
    while (HASH_GetFlagStatus(HASH_FLAG_BUSY) != RESET)
    {
    }

    /* Wait until the Busy flag is RESET */
    while (HASH_GetFlagStatus(HASH_FLAG_DINIS) == RESET)
    {
    }

    /* Wait until the Busy flag is RESET */
    while (HASH_GetFlagStatus(HASH_FLAG_DCIS) == RESET)
    {
    }

    /* Get the SHA256 Digest */
    HASH_GetDigest(&MsgDigest);

    /* Display the SHA256 digest */
    Display_SHA256Digest();

    /* Turn LED2 on */
    HK_EVAL_LEDOn(LED2);
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

