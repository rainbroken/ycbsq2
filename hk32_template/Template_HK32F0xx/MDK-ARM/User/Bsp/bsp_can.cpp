#include "bsp_can.hpp"
//#include "bsp.hpp"


//void bspCanFilter_DeConfig(void)
//{
//    HAL_CAN_DeactivateNotification(&CAN_PORT, CAN_IT_RX_FIFO0_MSG_PENDING);
//    HAL_CAN_Stop(&CAN_PORT);
//}

void bspCanSend(uint32_t id, uint8_t *data, uint8_t dlc)
{
    CanTxMsg TxMessage;
    
    TxMessage.StdId = 0x00;
    TxMessage.ExtId = id;
    TxMessage.IDE = CAN_ID_EXT;
    TxMessage.RTR = CAN_RTR_DATA;
    TxMessage.DLC = dlc;
    
    for(uint8_t i=0; i<dlc; i++)
    {
        TxMessage.Data[i] = data[i];
    }
    
    CAN_Transmit(&TxMessage);
}

