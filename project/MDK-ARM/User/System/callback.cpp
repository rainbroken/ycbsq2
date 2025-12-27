/*
 * @Author: RainBroken
 * @Date: 2025-12-24 18:17:17
 * @LastEditors: RainBroken
 * @LastEditTime: 2025-12-25 10:08:43
 * @FilePath: \project\MDK-ARM\User\System\callback.cpp
 * @Description: 中断回调函数
 *               中断触发函数一定要 extern "C"，否则有些会调用异常s
 *
 * Copyright (c) 2025 by RainBroken, All Rights Reserved.
 */

#include "callback.hpp"
#include "variables.hpp"
#include "main.h"
#include "bsp_usart.hpp"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @description: TIM6定时中断，触发频率 1000hz (1ms)
 * @return {*}
 */
void TIM6_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
    {
        //系统走时++
        system_ms++;
        // 清除中断标志
        TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
    }
}

/**
 * @description: 串口1中断服务函数 (debug)
 * @return {*}
 */
void USART1_IRQHandler(void)
{
    uint8_t rx_data;
   //检查串口ORE
   if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)
   {
        volatile uint16_t tmp;
        // 清除 ORE：先读 SR，再读 DR（标准清除流程）
       tmp = USART1->ISR;
       tmp = USART1->RDR;
       (void)tmp;                                  // 防止编译器优化
       USART_ClearFlag(USART1, USART_FLAG_ORE);    //清除溢出中断
   }

    // 先检查是否有接收数据（RXNE）
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        rx_data = USART_ReceiveData(USART1);
//        Uart1_Send(rx_data);
        Uart2_Send(rx_data);
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}


/**
 * @description: 串口2中断服务函数 (AT模块)
 * @return {*}
 */
void USART2_IRQHandler(void)
{
    volatile uint8_t rx_data;
    //检查串口ORE
    if (USART_GetFlagStatus(USART2, USART_FLAG_ORE) != RESET)
    {
        // 清除 ORE：先读 SR，再读 DR（标准清除流程）
       volatile uint16_t tmp;
       tmp = USART2->ISR;
       tmp = USART2->RDR;
       (void)tmp;                                  // 防止编译器优化
       USART_ClearFlag(USART2, USART_FLAG_ORE);    //清除溢出中断
    }

    // 先检查是否有接收数据（RXNE）
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        rx_data = USARTx_ReceiveData(USART2);
//#if A7680_RX_INT_PRINT
        Uart1_Send(rx_data);
//#endif
        a7680c_uart_msg.rxbuff[a7680c_uart_msg.rxcount++] = rx_data;
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    }
}

// 4.1 DMA传输完成中断处理
void DMA1_Channel5_IRQHandler(void) {
    if (DMA_GetITStatus(DMA1_IT_TC5)) {
        DMA_ClearITPendingBit(DMA1_IT_TC5);  // 清除中断标志

        // 计算接收数据长度（总长度 - 剩余未传输长度）
        rx_len = BUFFER_SIZE - DMA_GetCurrDataCounter(DMA1_Channel5);

        // 处理接收到的数据（例如回传）
        Uart1_print(rx_buffer);  // 通过DMA或轮询发送
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);

        // 重新启动DMA接收下一帧
        DMA_Cmd(DMA1_Channel5, DISABLE);
        DMA_SetCurrDataCounter(DMA1_Channel5, BUFFER_SIZE);
        DMA_Cmd(DMA1_Channel5, ENABLE);
    }
}

/**
  * @brief  Can接收中断服务函数
  * @retval None
  */
void CAN_IRQHandler(void)
{
    if (CAN_MessagePending(CAN_FIFO0) != 0)
    {

    }

    if (CAN_MessagePending(CAN_FIFO1) != 0)
    {

    }
}



#ifdef __cplusplus
}
#endif



#if 0

uint8_t power_capcity_Ah[2] = {0};
uint8_t power_capcity_V[2] = {0};
uint8_t queue_len = 0xff;
//can接收回调函数
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxHeaderTypeDef RxHeader = {0};
    can_frame_t frame;
    uint8_t buf[8] ={0};

    HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0,&RxHeader,buf);
    switch(bms.poll_step)
    {
    case CHM:
        if(RxHeader.ExtId == 0x182756F4)
        {
            bms.poll_step = CRM_00;
            bms.ison = true;
        }
        break;
    case CRM_00:
        if(RxHeader.ExtId == 0x1CEC56F4)
        {
            //有问题，pollstep变成2
            if(buf[0] ==0x10 && buf[6] == 0x02)
            {
                //获取返回字节数
                bms.pack_char_len = buf[1];
                bms.pack_len = buf[3];
                // printf("pack_len =%d\r\n",pack_len);
                bms.poll_step = BRM_TPCM_CTS;
            }
        }
        break;

    case BRM_TPCM_CTS:
        if(RxHeader.ExtId == 0x1CEB56F4)
        {
            //赋值msg
            frame.id = RxHeader.ExtId;
            frame.dlc = RxHeader.DLC;
            memset(frame.data,0,8);            //清空
            memcpy(frame.data,buf,8);          //重写
            //将接收到的数据存进队列
            bms.queue_.push(&frame);
            queue_len = bms.queue_.getLen();
            //这里需要得到BRM阶段的电池额定容量
            if(queue_len >= bms.pack_len)    //辨识信息  3.15修改，应该是==才对，但是实际接收可能会超出
            {
                //检测每一帧报文首字符是否为0x01,这一阶段包含电池容量
                can_frame_t frame_;
                for(uint8_t i=0; i<queue_len; i++)
                {
                    bms.queue_.pop(&frame_);
                    if(frame_.data[0] == 0x01)
                    {
                        power_capcity_Ah[0] = frame_.data[5];
                        power_capcity_Ah[1] = frame_.data[6];
                        power_capcity_V[0] = frame_.data[7];
                    }
                    if(frame_.data[0] == 0x02)
                    {
                        power_capcity_V[1] = frame_.data[1];
                    }
                }
                //整合电池容量数据
                bms.bms_data.Capcity_Ah_ = bytesToHalfWord(power_capcity_Ah[1],power_capcity_Ah[0]) *0.1;
                bms.bms_data.Capcity_V_  = bytesToHalfWord(power_capcity_V[1],power_capcity_V[0]) *0.1;
                bms.poll_step = BRM_TPCM_EM;
                bms.queue_.clear();
            }
        }
        break;

    case BRM_TPCM_EM:
        if(RxHeader.ExtId == 0x1CEC56F4)
        {
            if(buf[0] ==0x10 && buf[6] == 0x06)
            {
                bms.poll_step = BCP_TPCM_CTS;
            }
        }
        break;

    case BCP_TPCM_CTS:
        if(RxHeader.ExtId == 0x1CEB56F4)
        {
            //赋值msg
            frame.id = RxHeader.ExtId;
            frame.dlc = RxHeader.DLC;
            memset(frame.data,0,8);                       //清空
            memcpy(frame.data,buf,RxHeader.DLC);          //重写

            //将接收到的数据存进队列
            bms.queue_.push(&frame);
            if(bms.queue_.getLen() == 2 && bms.queue_.buffer[0].data[0] ==0x01 && bms.queue_.buffer[1].data[0] ==0x02)      //电压、温度
            {
                uint8_t bms_data_[16] = {0};
                can_frame_t frame_;
                bms.queue_.pop(&frame_);
                memcpy(bms_data_, frame_.data, 8);
                bms.queue_.pop(&frame_);
                memcpy(bms_data_+8, frame_.data, 8);
//                printf("bms data\r\n %X %X %X %X %X %X %X %X\r\n %X %X %X %X %X %X %X %X\r\n",\
//                    bms_data_[0],bms_data_[1],bms_data_[2],bms_data_[3],bms_data_[4],bms_data_[5],bms_data_[6],bms_data_[7],bms_data_[8],
//                    bms_data_[9],bms_data_[10],bms_data_[11],bms_data_[12],bms_data_[13],bms_data_[14],bms_data_[15]);
                bms.bms_data.Volt_ = bytesToHalfWord(bms_data_[14],bms_data_[13]) *0.1;
                bms.bms_data.Elect_= bytesToHalfWord(bms_data_[4],bms_data_[3])*0.1 -400;
                bms.bms_data.Ep_   = bytesToHalfWord(bms_data_[6],bms_data_[5])*0.1;
                bms.bms_data.Soc_  = bytesToHalfWord(bms_data_[12],bms_data_[11])*0.1;
                bms.poll_step = BCP_TPCM_EM;
                bms.queue_.clear();
            }
        }
        break;
    case BCP_TPCM_EM:
        break;
    case CTS:
        break;
    case CML:
        if(RxHeader.ExtId == 0x100956F4)
        {
            bms.poll_step = CRO_AA;
        }
        break;
    case CRO_AA:
        if(RxHeader.ExtId == 0x1CEC56F4)
        {
            if(buf[0] == 0x10 && buf[6] == 0x11)
            {
                bms.pack_char_len = buf[1];
                bms.pack_len = buf[3];
                bms.poll_step = BCS_TPCM_CTS;
            }
        }
        bms.poll_step = CRM_00;
        break;
    case BCS_TPCM_CTS:
        if(RxHeader.ExtId == 0x1CEB56F4)
        {
            //赋值msg
            frame.id = RxHeader.ExtId;
            frame.dlc = RxHeader.DLC;
            memset(frame.data,0,8);                       //清空
            memcpy(frame.data,buf,RxHeader.DLC);          //重写

            //将接收到的数据存进队列
            bms.queue_.push(&frame);
            if(bms.queue_.getLen() == 2 && bms.queue_.buffer[0].data[0] ==0x01 && bms.queue_.buffer[1].data[0] ==0x02)
            {
                bms.poll_step = BCS_TPCM_EM;
                bms.queue_.clear();
            }
        }
        break;
    case BCS_TPCM_EM:
        break;
    case CCS:
        if(RxHeader.ExtId == 0x1CEC56F4)
        {
            if(buf[0] == 0x10 && buf[6] == 0x15)
            {
                bms.pack_char_len = buf[1];
                bms.pack_len = buf[3];
                bms.poll_step = BMV_TPCM_CTS;
            }
        }
        break;
    case BMV_TPCM_CTS:
        if(RxHeader.ExtId == 0x1CEB56F4)
        {
            //赋值msg
            frame.id = RxHeader.ExtId;
            frame.dlc = RxHeader.DLC;
            memset(frame.data,0,8);                       //清空
            memcpy(frame.data,buf,RxHeader.DLC);          //重写

            //将接收到的数据存进队列
            bms.queue_.push(&frame);
            if(bms.queue_.getLen() == 2 && bms.queue_.buffer[0].data[0] ==0x01 && bms.queue_.buffer[1].data[0] ==0x02)
            {
                bms.poll_step = BMV_TPCM_EM;
                bms.queue_.clear();
            }
        }
        break;
    case BMV_TPCM_EM:
        if(RxHeader.ExtId == 0x1CEC56F4)
        {
            if(buf[0] == 0x10 && buf[6] == 0x16)
            {
                bms.pack_char_len = buf[1];
                bms.pack_len = buf[3];
                bms.poll_step = BMT_TPCM_CTS;
            }
        }
        break;
    case BMT_TPCM_CTS:
        if(RxHeader.ExtId == 0x1CEB56F4)
        {
            //赋值msg
            frame.id = RxHeader.ExtId;
            frame.dlc = RxHeader.DLC;
            memset(frame.data,0,8);                       //清空
            memcpy(frame.data,buf,RxHeader.DLC);          //重写

            //将接收到的数据存进队列
            bms.queue_.push(&frame);
            if(bms.queue_.getLen() == 2 && bms.queue_.buffer[0].data[0] ==0x01 && bms.queue_.buffer[1].data[0] ==0x02)
            {
                bms.poll_step = BMT_TPCM_EM;
                bms.queue_.clear();
            }
        }
        break;
    case BMT_TPCM_EM:
        if(RxHeader.ExtId == 0x101956F4)
        {
            bms.poll_step = CST;
        }
        break;
    case CST:
        if(RxHeader.ExtId == 0x181C56F4)
        {
            bms.poll_step = CSD;
        }
        break;

    default:
        break;
    }
    HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);//重新使能接收
}

void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc)
{
    flag_heartbeat = true;
    bspRtcSetAlarm(0x01,0x00,0x00); //1h后进入中断
}
#endif
