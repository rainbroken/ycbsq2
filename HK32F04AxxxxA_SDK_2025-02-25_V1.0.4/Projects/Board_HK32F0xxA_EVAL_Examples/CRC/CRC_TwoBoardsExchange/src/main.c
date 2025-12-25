/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-10-15
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup HK32F0xxA_StdPeriph_Examples
  * @{
  */

/** @addtogroup CRC_TwoBoardsExchange
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define BufLen(a)   (sizeof(a) / sizeof(*(a)))

/* Private variables ---------------------------------------------------------*/
const uint8_t CRC32Buffer[] =
{
    0x12, 0x34, 0x56, 0x78, 0x00, 0x00, 0x10, 0x21
};

uint8_t Txbuffer[BufLen(CRC32Buffer) + 4];
uint8_t Rxbuffer[BufLen(Txbuffer)];

__IO JOYState_TypeDef PressedButton  = JOY_NONE;
__IO uint8_t RxIndex = 0x00;
uint32_t RxCRCValue;

uint32_t ExpectedCRC = 0x7A426B65; /* The expected CRC value of CRCBuffer using the
                               polynomial X32 + X26 + X23 + X22 + X16 + X12 + X11 +
                                              X10 +X8 + X7 + X5 + X4 + X2+ X + 1 */

/* Private function prototypes -----------------------------------------------*/
void USARTx_Config(uint32_t Baud);
void CRC_Config(void);
static void SysTickConfig(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    volatile uint32_t ComputedCRC;

    uint8_t length = 0;
    uint32_t index = 0;

    /* LED Init */
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);
    HK_EVAL_LEDInit(LED3);

    /* USART configuration */
    USARTx_Config(115200);

    /* SysTick configuration */
    SysTickConfig();

    /* Configure the F04A CRC peripheral to use the fixed polynomial X32 + X26 + X23 + X22 +
                          X16 + X12 + X11 + X10 +X8 + X7 + X5 + X4 + X2+ X +1 (0x4C11DB7)*/
    CRC_Config();

    /* clear crc DR */
    CRC_ResetDR();

#ifdef MODE_TRANSMITTER

    HK_EVAL_PBInit(BUTTON_SEL, BUTTON_MODE_EXTI);

    while (1)
    {
        /*Wait "JOY_SEL" to start data transfer */
        if ((PressedButton != JOY_NONE))
        {
            length = BufLen(CRC32Buffer);

            /* Compute the CRC value of the 32bit buffer: CRC32Buffer */
            for (index = 0; index < length; index++)
            {
                /* Write in 8bitdata way to register one by one then compute CRC32*/
                ComputedCRC = CRC_CalcCRC8bits(CRC32Buffer[index]);
            }


            /* Load data and crc32 to Txbuffer */
            for (index = 0; index < length; index++)
            {
                Txbuffer[index] = CRC32Buffer[index];
            }

            Txbuffer[index++] = (uint8_t)(ComputedCRC >> 24);
            Txbuffer[index++] = (uint8_t)(ComputedCRC >> 16);
            Txbuffer[index++] = (uint8_t)(ComputedCRC >> 8);
            Txbuffer[index++] = (uint8_t)(ComputedCRC);

            /* transmit data to slave */
            for (index = 0; index < BufLen(Txbuffer); index++)
            {
                USART_SendData(USARTx, Txbuffer[index]);

                while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
                {

                }
            }

            PressedButton = JOY_NONE;

            /* clear crc DR */
            CRC_ResetDR();
        }

    }


#else

    while (1)
    {
        if (RxIndex == (BufLen(CRC32Buffer) + 4))
        {
            length = BufLen(Rxbuffer);

            /* Compute the CRC value of the 8bit buffer: Rxbuffer */
            for (index = 0; index < (length - 4); index++)
            {
                /* Write in 8bitdata way to register one by one then compute CRC32*/
                ComputedCRC = CRC_CalcCRC8bits(Rxbuffer[index]);
            }

            /* Get RxCRC32Value */
            RxCRCValue = (Rxbuffer[index] << 24) | (Rxbuffer[index + 1] << 16) | (Rxbuffer[index + 2] << 8) | (Rxbuffer[index + 3]);

            /* Check if the computed CRC matches the recv one */
            if (ComputedCRC != RxCRCValue)
            {
                /* LED3 On */
                HK_EVAL_LEDOn(LED3);

                /* LED2 Off */
                HK_EVAL_LEDOff(LED2);
                debug("RxCRC32 Verify error!");
            }
            else
            {
                /* LED3 Off */
                HK_EVAL_LEDOff(LED3);

                /* Toggle LED2 */
                HK_EVAL_LEDToggle(LED2);
                debug("RxCRC32 Verify correct!");
            }

            RxIndex = 0;
            /* clear crc DR */
            CRC_ResetDR();
        }

    }

#endif

}


/**
  * @brief  Configure CRC peripheral to use 32-bit polynomials
  * @param  poly: the CRC polynomial
  * @retval None
  */
void CRC_Config(void)
{
    /* Enable CRC AHB clock interface */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);

    /* DeInit CRC peripheral */
    CRC_DeInit();

    /* Init the INIT register */
    CRC_SetInitRegister(0);
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


/**
  * @brief  Configure the USART Device
  * @param  Baud: The USARTx BaudRate
  * @retval None
  */
void USARTx_Config(uint32_t Baud)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable GPIO clock and Enable USART Clock,USARTx,USARTy */
    USARTx_TXIO_CLK_CMD(USARTx_TXIO_CLK, ENABLE);
    USARTx_RXIO_CLK_CMD(USARTx_RXIO_CLK, ENABLE);
    USARTx_CLK_CMD(USARTx_CLK, ENABLE);


    /* GPIO Configure RX TX */
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_UP;

    GPIO_InitStructure.GPIO_Pin     = USARTx_TX_PIN;
    GPIO_Init(USARTx_TXIO_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin     = USARTx_RX_PIN;
    GPIO_Init(USARTx_RXIO_PORT, &GPIO_InitStructure);


    /* Connect PXx to USART1 Tx Rx */
    GPIO_PinAFConfig(USARTx_TXIO_PORT, USARTx_AF_TX_PIN, USARTx_AF_SELECT);
    GPIO_PinAFConfig(USARTx_RXIO_PORT, USARTx_AF_RX_PIN, USARTx_AF_SELECT);

    /* USARTx configured */
    USART_InitStructure.USART_BaudRate = Baud;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;    /* Hardware flow control disabled (RTS and CTS signals) */
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                    /* Receive and transmit enabled */

    /* When using Parity the word length must be configured to 9 bits */
    USART_InitStructure.USART_Parity = USART_Parity_No;                                /* No parity */
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                             /* One Stop Bit */
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                        /*Word Length = 8 Bits */

    USART_Init(USARTx, &USART_InitStructure);

    /* NVIC configuration */

    /* Enable the USARTx Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable the USARTx Receive interrupt: this interrupt is generated when the
    USARTx receive data register is not empty */
    USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);

    /* Enable USART */
    USART_Cmd(USARTx, ENABLE);
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


