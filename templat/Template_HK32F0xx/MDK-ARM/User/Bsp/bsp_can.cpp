#include "bsp_can.hpp"
//#include "bsp.hpp"

/**
  * @brief  Configures the CAN.
  * @param  None
  * @retval None
  */
uint8_t bspCanFilter_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;
    CAN_InitTypeDef        CAN_InitStructure;
    //CAN_FilterInitTypeDef  CAN_FilterInitStructure;

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
    CAN_InitStructure.CAN_RFLM = ENABLE;
    CAN_InitStructure.CAN_TXFP = ENABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;

    /* CAN Baudrate = 1MBps (sysclk: HSI56M, CAN clocked at 56/2 MHz) */
    CAN_InitStructure.CAN_BS1 = CAN_BS1_9tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_4tq;
    CAN_InitStructure.CAN_Prescaler = 2;
    CAN_Init(&CAN_InitStructure);

    /* CAN filter init "FIFO0" */
    CAN_FilterInitStructure.CAN_FilterNumber = 0;
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x6420;
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);

    /* Transmit Structure preparation */
    TxMessage.StdId = 0x321;
    TxMessage.ExtId = 0x00;
    TxMessage.RTR = CAN_RTR_DATA;
    TxMessage.IDE = CAN_ID_STD;
    TxMessage.DLC = 1;

    /* Enable FIFO 0 full  Interrupt */
    CAN_ITConfig(CAN_IT_FF0, ENABLE);

    /* Enable FIFO 1 full  Interrupt */
    CAN_ITConfig(CAN_IT_FF1, ENABLE);
}

void bspCanFilter_DeConfig(void)
{
    HAL_CAN_DeactivateNotification(&CAN_PORT, CAN_IT_RX_FIFO0_MSG_PENDING);
    HAL_CAN_Stop(&CAN_PORT);
}

void bspCanSend(uint32_t id, uint8_t *data, uint8_t dlc)
{
    //邮箱
    uint32_t mbox;

    CAN_TxHeaderTypeDef TxHeader;
    TxHeader.StdId  = 0;           //标准帧id
    TxHeader.ExtId  = id;           //扩展帧id
    TxHeader.IDE    = CAN_ID_EXT;   //使用扩展帧id
    TxHeader.RTR    = CAN_RTR_DATA; //发送报文：数据帧
    TxHeader.DLC    = dlc;          //数据帧长度
    TxHeader.TransmitGlobalTime = DISABLE;//时间戳：不使能

//    printf("txmail box =%d\r\n",HAL_CAN_GetTxMailboxesFreeLevel(&kCanHandle));
    if(HAL_CAN_GetTxMailboxesFreeLevel(&CAN_PORT) == 0)
    {
        HAL_Delay(300);
        HAL_CAN_MspInit(&CAN_PORT);
        MX_CAN_Init();
        bspCanFilter_DeConfig();
        HAL_Delay(100);
        bspCanFilter_Config();
    }
    HAL_CAN_AddTxMessage(&CAN_PORT,&TxHeader,data,&mbox);
}

