#include "bsp_can.hpp"

uint8_t bspCanFilter_Config(void)
{
    CAN_FilterTypeDef Can_Filter;

    // 配置过滤器
    Can_Filter.FilterActivation     = CAN_FILTER_ENABLE;      // 激活过滤器
    Can_Filter.FilterBank           = 0;                      // 过滤器0
    Can_Filter.FilterMode           = CAN_FILTERMODE_IDMASK;  // ID掩码模式
    Can_Filter.FilterScale          = CAN_FILTERSCALE_32BIT;  // 32位过滤器
    Can_Filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;       // 挂在过滤器FIFO0
    Can_Filter.FilterIdHigh         = 0x0000;                 // 过滤器需要过滤高ID
    Can_Filter.FilterIdLow          = 0x0000;                 // 过滤器需要过滤低ID
    Can_Filter.FilterMaskIdHigh     = 0x0000;                 // 过滤器掩码 '0'位不限制
    Can_Filter.FilterMaskIdLow      = 0x0000;                 // 过滤器掩码 '0'位不限制
    Can_Filter.SlaveStartFilterBank = 14;                     

    if(HAL_CAN_ConfigFilter(&CAN_PORT, &Can_Filter) != HAL_OK)  return 1;
    if(HAL_CAN_ActivateNotification(&CAN_PORT, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) return 2;
    if(HAL_CAN_Start(&CAN_PORT) != HAL_OK) return 3;
    return 0;
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

