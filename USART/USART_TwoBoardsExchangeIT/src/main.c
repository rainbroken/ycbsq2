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

/** @addtogroup USART_TwoBoardsExchangeIT
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
DMA_InitTypeDef  DMA_InitStructure;
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define TXBUFFERSIZE    (BufLen(TxBuffer) - 1)
#define RXBUFFERSIZE    TXBUFFERSIZE

/* Private macro -------------------------------------------------------------*/
#define BufLen(a)   (sizeof(a) / sizeof(*(a)))

/* Private variables ---------------------------------------------------------*/
uint8_t TxBuffer[] = "USART Interrupt Example: Communication between two USART using Interrupt";
uint8_t RxBuffer [RXBUFFERSIZE];

uint8_t CmdBuffer [0x02] = {0x00, 0x00}; /* {Command, Number of byte to receive or to transmit} */
uint8_t AckBuffer [0x02] = {0x00, 0x00}; /* {Command, ACK} */

__IO uint32_t TimeOut = 0x0;
__IO JOYState_TypeDef PressedButton = JOY_NONE;

__IO uint8_t UsartTransactionType = USART_TRANSACTIONTYPE_CMD;
__IO uint8_t UsartMode = USART_MODE_TRANSMITTER;
__IO uint8_t RxIndex = 0x00;
__IO uint8_t TxIndex = 0x00;

/* Private function prototypes -----------------------------------------------*/
void USARTx_Config(uint32_t Baud);
static void DEBUG_USART_Config(uint32_t Baud);
static void SysTickConfig(void);
static void TimeOut_UserCallback(void);
static JOYState_TypeDef Read_Joystick(void);
static void Fill_Buffer(uint8_t* pBuffer, uint16_t BufferLength);
static uint8_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* LED Init */
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);
    HK_EVAL_LEDInit(LED3);
    HK_EVAL_LEDInit(LED4);

    /* Initialize push-buttons mounted on EVAL board */
    HK_EVAL_PBInit(BUTTON_RIGHT, BUTTON_MODE_GPIO);
    HK_EVAL_PBInit(BUTTON_LEFT, BUTTON_MODE_GPIO);
    HK_EVAL_PBInit(BUTTON_UP, BUTTON_MODE_GPIO);
    HK_EVAL_PBInit(BUTTON_DOWN, BUTTON_MODE_GPIO);
    HK_EVAL_PBInit(BUTTON_SEL, BUTTON_MODE_GPIO);

    /* SysTick configuration */
    SysTickConfig();

    /* USART configuration for printf */
    DEBUG_USART_Config(115200);

    /* USART configuration */
    USARTx_Config(115200);

    debug("system is running!\n");

    while (1)
    {
        TxIndex = 0x00;
        RxIndex = 0x00;

        UsartTransactionType = USART_TRANSACTIONTYPE_CMD;
        UsartMode = USART_MODE_RECEIVER;

        /* Clear Buffers */
        Fill_Buffer(CmdBuffer, 0x02);
        Fill_Buffer(AckBuffer, 0x02);
        Fill_Buffer(RxBuffer, TXBUFFERSIZE);

        /* Get key value */
        PressedButton = Read_Joystick();

        /* Waiting Joystick pressed in case to transmit data or received Transaction command */
        while ((PressedButton == JOY_NONE) && (CmdBuffer[0x00] == 0x00))
        {
            PressedButton = Read_Joystick();
        }

        /* USART in Mode Transmitter ---------------------------------------------*/
        if ((PressedButton != JOY_NONE) && (CmdBuffer[0x00] == 0x00))
        {
            UsartMode = USART_MODE_TRANSMITTER;
            printf("system in Mode Transmitter!\n");

            switch (PressedButton)
            {
                /* JOY_RIGHT button pressed */
                case JOY_RIGHT:
                    printf("JOY_RIGHT Pressed!\n");
                    CmdBuffer[0x00] = CMD_RIGHT;
                    CmdBuffer[0x01] = CMD_RIGHT_SIZE;
                    break;

                /* JOY_LEFT button pressed */
                case JOY_LEFT:
                    printf("JOY_LEFT Pressed!\n");
                    CmdBuffer[0x00] = CMD_LEFT;
                    CmdBuffer[0x01]  = CMD_LEFT_SIZE;
                    break;

                /* JOY_UP button pressed */
                case JOY_UP:
                    printf("JOY_UP Pressed!\n");
                    CmdBuffer[0x00] = CMD_UP;
                    CmdBuffer[0x01] = CMD_UP_SIZE;
                    break;

                /* JOY_DOWN button pressed */
                case JOY_DOWN:
                    printf("JOY_DOWN Pressed!\n");
                    CmdBuffer[0x00] = CMD_DOWN;
                    CmdBuffer[0x01] = CMD_DOWN_SIZE;
                    break;

                /* JOY_SEL button pressed */
                case JOY_SEL:
                    printf("JOY_SEL Pressed!\n");
                    CmdBuffer[0x00] = CMD_SEL;
                    CmdBuffer[0x01] = CMD_SEL_SIZE;
                    break;

                default:
                    break;
            }

            /* send cmd to slave*/
            /* Enable the USARTx transmit data register empty interrupt */
            USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);

            /* Wait until USART sends the command or time out */
            TimeOut = USER_TIMEOUT;

            while ((TxIndex < 0x02) && (TimeOut != 0x00))
            {

            }

            if (TimeOut == 0)
            {
                TimeOut_UserCallback();
            }

            /* The software must wait until TC=1. The TC flag remains cleared during all data
               transfers and it is set by hardware at the last frame?s end of transmission*/
            TimeOut = USER_TIMEOUT;

            while ((USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET) && (TimeOut != 0x00))
            {

            }

            if (TimeOut == 0)
            {
                TimeOut_UserCallback();
            }

            printf("key CmdBuffer send success!\n");

            /* Wait until USART receives the Ack command  or time out*/
            TimeOut = USER_TIMEOUT;

            while ((RxIndex < 0x02) && (TimeOut != 0x00))
            {

            }

            if (TimeOut == 0)
            {
                TimeOut_UserCallback();
            }

            printf("Ack Buffer recv success!\n");
            /* USART sends the data */
            UsartTransactionType = USART_TRANSACTIONTYPE_DATA;
            TxIndex = 0x00;
            RxIndex = 0x00;

            /* Enable the USARTx transmit data register empty interrupt */
            USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);

            /* Wait until end of data transfer */
            TimeOut = USER_TIMEOUT;

            while ((TxIndex < CmdBuffer[0x01]) && (TimeOut != 0x00))
            {

            }

            if (TimeOut == 0)
            {
                TimeOut_UserCallback();
            }

            /* The software must wait until TC=1. The TC flag remains cleared during all data
               transfers and it is set by hardware at the last frame?s end of transmission*/
            TimeOut = USER_TIMEOUT;

            while ((USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET) && (TimeOut != 0x00))
            {

            }

            if (TimeOut == 0)
            {
                TimeOut_UserCallback();
            }

            printf("key DataBuffer send success!\n");

            CmdBuffer[0x00] = 0x00;
        }

        /* USART in Mode Receiver-------------------------------------------------*/
        if (CmdBuffer[0x00] != 0x00)
        {
            /* Wait until USART receives the command  or time out */
            TimeOut = USER_TIMEOUT;

            while ((RxIndex < 0x02) && (TimeOut != 0x00))
            {

            }

            if (TimeOut == 0)
            {
                TimeOut_UserCallback();
            }

            UsartMode = USART_MODE_RECEIVER;
            printf("system in Mode Receiver!\n");

            /* Enable the USARTx transmit data register empty interrupt */
            USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);

            /* Wait until USART sends the ACK command or time out*/
            TimeOut = USER_TIMEOUT;

            while ((TxIndex < 0x02) && (TimeOut != 0x00))
            {

            }

            if (TimeOut == 0)
            {
                TimeOut_UserCallback();
            }

            /* The software must wait until TC=1. The TC flag remains cleared during all data
             transfers and it is set by hardware at the last frame?s end of transmission*/
            TimeOut = USER_TIMEOUT;

            while ((USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET) && (TimeOut != 0x00))
            {

            }

            if (TimeOut == 0)
            {
                TimeOut_UserCallback();
            }

            printf("Ack Buffer send success!\n");

            /* USART receives the data */
            UsartTransactionType = USART_TRANSACTIONTYPE_DATA;
            TxIndex = 0x00;
            RxIndex = 0x00;

            /* Wait until end of data transfer or time out */
            TimeOut = USER_TIMEOUT;

            while ((RxIndex < CmdBuffer[0x01]) && (TimeOut != 0x00))
            {

            }

            if (TimeOut == 0)
            {
                TimeOut_UserCallback();
            }

            printf("Data Buffer recv success!\n");

            switch (CmdBuffer[0x01])
            {
                /* CMD_RIGHT command received */
                case CMD_RIGHT_SIZE:
                    if (Buffercmp(TxBuffer, RxBuffer, CMD_RIGHT_SIZE) != FAILED)
                    {
                        printf("JOY_RIGHT Received data correctly!\n");

                        /* Turn ON LED2 and LED3 */
                        HK_EVAL_LEDOn(LED2);
                        HK_EVAL_LEDOn(LED3);

                        /* Turn OFF LED4 */
                        HK_EVAL_LEDOff(LED4);
                    }

                    break;

                /* CMD_LEFT command received */
                case CMD_LEFT_SIZE:
                    if (Buffercmp(TxBuffer, RxBuffer, CMD_LEFT_SIZE) != FAILED)
                    {
                        printf("JOY_LEFT Received data correctly!\n");

                        /* Turn ON LED4 */
                        HK_EVAL_LEDOn(LED4);

                        /* Turn OFF LED2 and LED3 */
                        HK_EVAL_LEDOff(LED2);
                        HK_EVAL_LEDOff(LED3);
                    }

                    break;

                /* CMD_UP command received */
                case CMD_UP_SIZE:
                    if (Buffercmp(TxBuffer, RxBuffer, CMD_UP_SIZE) != FAILED)
                    {
                        printf("JOY_UP Received data correctly!\n");

                        /* Turn ON LED2 */
                        HK_EVAL_LEDOn(LED2);

                        /* Turn OFF LED3 and LED4 */
                        HK_EVAL_LEDOff(LED3);
                        HK_EVAL_LEDOff(LED4);
                    }

                    break;

                /* CMD_DOWN command received */
                case CMD_DOWN_SIZE:
                    if (Buffercmp(TxBuffer, RxBuffer, CMD_DOWN_SIZE) != FAILED)
                    {
                        printf("JOY_DOWN Received data correctly!\n");

                        /* Turn ON LED3 */
                        HK_EVAL_LEDOn(LED3);

                        /* Turn OFF LED2 and LED4 */
                        HK_EVAL_LEDOff(LED2);
                        HK_EVAL_LEDOff(LED4);
                    }

                    break;

                /* CMD_SEL command received */
                case CMD_SEL_SIZE:
                    if (Buffercmp(TxBuffer, RxBuffer, CMD_SEL_SIZE) != FAILED)
                    {
                        printf("JOY_SEL Received data correctly!\n");

                        /* Turn ON all LED2, LED3 and LED4 */
                        HK_EVAL_LEDOn(LED2);
                        HK_EVAL_LEDOn(LED3);
                        HK_EVAL_LEDOn(LED4);
                    }

                    break;

                default:
                    break;
            }

            CmdBuffer[0x00] = 0x00;
        }
    }
}

/**
  * @brief  Configure a SysTick Base time to 10 ms.
  * @param  None
  * @retval None
  */
static void SysTickConfig(void)
{
    /* Set SysTick Timer for 10ms interrupts  */
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
  * @brief  Reads key from evaluationboard.
  * @param  None
  * @retval Return JOY_RIGHT, JOY_LEFT, JOY_SEL, JOY_UP, JOY_DOWN or JOY_NONE
  */
static JOYState_TypeDef Read_Joystick(void)
{
    /* "JOY_RIGHT" key is pressed */
    if (HK_EVAL_PBGetState(BUTTON_RIGHT))
    {
        while (HK_EVAL_PBGetState(BUTTON_RIGHT) == RESET)
        {

        }

        return JOY_RIGHT;
    }

    /* "JOY_LEFT" key is pressed */
    if (HK_EVAL_PBGetState(BUTTON_LEFT))
    {
        while (HK_EVAL_PBGetState(BUTTON_LEFT) == RESET)
        {

        }

        return JOY_LEFT;
    }

    /* "JOY_UP" key is pressed */
    if (HK_EVAL_PBGetState(BUTTON_UP))
    {
        while (HK_EVAL_PBGetState(BUTTON_UP) == RESET)
        {

        }

        return JOY_UP;
    }

    /* "JOY_DOWN" key is pressed */
    if (HK_EVAL_PBGetState(BUTTON_DOWN))
    {
        while (HK_EVAL_PBGetState(BUTTON_DOWN) == RESET)
        {

        }

        return JOY_DOWN;
    }

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

/**
  * @brief  Configure the USART1 Device for printf
  * @param  None
  * @retval None
  */
static void DEBUG_USART_Config(uint32_t Baud)
{
    USART_InitTypeDef USART_InitStructure;

    /* USARTx configured as follow:
    - BaudRate = baud
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
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval None.
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
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
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

/**
  * @brief  Fills buffer.
  * @param  pBuffer: pointer on the Buffer to fill
  * @param  BufferLength: size of the buffer to fill
  * @retval None
  */
static void Fill_Buffer(uint8_t* pBuffer, uint16_t BufferLength)
{
    uint16_t index = 0;

    /* Put in global buffer same values */
    for (index = 0; index < BufferLength; index++)
    {
        pBuffer[index] = 0x00;
    }
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


