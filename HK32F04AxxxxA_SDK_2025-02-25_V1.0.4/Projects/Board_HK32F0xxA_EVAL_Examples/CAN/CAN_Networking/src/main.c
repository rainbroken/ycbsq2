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
#include "hk32f0xxa_eval.h"

/** @addtogroup HK32F0xxA_StdPeriph_Examples
  * @{
  */

/** @addtogroup CAN_Networking_Example
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
CanTxMsg TxMessage = {0};
uint8_t KeyNumber = 0x0;
extern __IO uint8_t MsgReceived;
extern __IO uint8_t KeyPressed;

/* Private function prototypes -----------------------------------------------*/
static void CAN_Config(void);


void Delay(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
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

    /* Configures LED 1..4 */
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);
    HK_EVAL_LEDInit(LED3);
    HK_EVAL_LEDInit(LED4);

    /* Configure Push button key */
    HK_EVAL_PBInit(BUTTON_TAMPER, BUTTON_MODE_EXTI);

    /* LED1 ON */
    HK_EVAL_LEDOn(LED1);

    /* CAN configuration */
    CAN_Config();
    KeyPressed = 0;
    KeyNumber = 0;

    /* Infinite loop */
    while (1)
    {
        if (KeyPressed)
        {
            if (KeyNumber == 0x4)
            {
                KeyNumber = 0x00;
            }

            LED_Display(++KeyNumber);
            TxMessage.Data[0] = KeyNumber;
            CAN_Transmit(&TxMessage);
            //Delay();
            KeyPressed = 0;
        }
    }
}

/**
  * @brief  Configures the CAN.
  * @param  None
  * @retval None
  */
static void CAN_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;
    CAN_InitTypeDef        CAN_InitStructure;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;

    /* CAN GPIOs configuration **************************************************/

    /* Enable GPIO clock */
    RCC_AHBPeriphClockCmd(CAN_GPIO_CLK, ENABLE);

    /* Connect CAN pins to AF7 */
    GPIO_PinAFConfig(CAN_GPIO_PORT, CAN_RX_SOURCE, CAN_AF_PORT);
    GPIO_PinAFConfig(CAN_GPIO_PORT, CAN_TX_SOURCE, CAN_AF_PORT);

    /* Configure CAN pin: RX */
    GPIO_InitStructure.GPIO_Pin = CAN_RX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(CAN_GPIO_PORT, &GPIO_InitStructure);

    /* Configure CAN pin: TX */
    GPIO_InitStructure.GPIO_Pin = CAN_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(CAN_GPIO_PORT, &GPIO_InitStructure);

    /* NVIC configuration *******************************************************/
    NVIC_InitStructure.NVIC_IRQChannel = CAN_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0x0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* CAN configuration ********************************************************/

    /* Enable CAN clock */
    RCC_APB1PeriphClockCmd(CAN_CLK, ENABLE);

    /* CAN register init */
    CAN_DeInit();
    CAN_StructInit(&CAN_InitStructure);

    /* CAN cell init */
    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = DISABLE;
    CAN_InitStructure.CAN_AWUM = DISABLE;
    CAN_InitStructure.CAN_NART = DISABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = DISABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;

    /* CAN Baudrate = 1MBps (sysclk: HSI56M, CAN clocked at 56/2 MHz) */
    CAN_InitStructure.CAN_BS1 = CAN_BS1_9tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_4tq;
    CAN_InitStructure.CAN_Prescaler = 2;
    CAN_Init(&CAN_InitStructure);

    /* CAN filter init "FIFO0" */
    CAN_FilterInitStructure.CAN_FilterNumber = 0;
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);

    /* Transmit Structure preparation */
    TxMessage.StdId = 0x321;
    TxMessage.ExtId = 0x01;
    TxMessage.RTR = CAN_RTR_DATA;
    TxMessage.IDE = CAN_ID_STD;
    TxMessage.DLC = 1;

    /* Enable FIFO 0 message pending Interrupt */
    CAN_ITConfig(CAN_IT_FMP0, ENABLE);
}

/**
  * @brief  Turn ON/OFF the dedicated led
  * @param  Ledstatus: Led number from 1 to 4.
  * @retval None
  */
void LED_Display(uint8_t Ledstatus)
{
    /* Turn off all leds */
    HK_EVAL_LEDOff(LED1);
    HK_EVAL_LEDOff(LED2);
    HK_EVAL_LEDOff(LED3);
    HK_EVAL_LEDOff(LED4);

    switch (Ledstatus)
    {
        case (1):
            HK_EVAL_LEDOn(LED2);
            break;

        case (2):
            HK_EVAL_LEDOn(LED3);
            break;

        case (3):
            HK_EVAL_LEDOn(LED4);
            break;

        case (4):
            HK_EVAL_LEDOn(LED1);
            break;

        default:
            break;
    }
}

/**
  * @brief  Delay
  * @param  None
  * @retval None
  */
void Delay(void)
{
    uint32_t Time = 0x0000;

    for (Time = 0; Time < 0xFFFFF; Time++)
    {
        ;
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
        ;
    }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

