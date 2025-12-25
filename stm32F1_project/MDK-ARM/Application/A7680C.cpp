/**
 * @Author: rainbroken
 * @Date: 2025-12-09 21:56:08
 * @LastEditors: rainbroken 
 * @LastEditTime: 2025-12-10 19:13:00
 * @FilePath: \hk32_project\MDK-ARM\Application\A7680C.cpp
 * @Description: 
 * @
 * @Copyright (c) 2025 by ${rainbroken}, All Rights Reserved. 
 */
#include "A7680C.hpp"
#include "bsp_usart.hpp"
//#include "string_algorithm.hpp"
//#include <stdlib.h>
#include <cstring>
#include <cstdio>
#include "variables.hpp"
#include "handler.hpp"

//at_fsm_t fsm_cmd_buffer[] =
//{
//    {STATE_IDLE,    "AT\r",             "OK",200,2,0},
//    {STATE_IDLE,    "AT+CSQ\r",         "OK",200,2,0},
//    {STATE_IDLE,    "AT+CREG?\r",       "OK",200,2,0},
//    {STATE_IDLE,    "AT+CGATT?\r",      "OK",200,2,0},
//    //MQTT连接
//    {STATE_IDLE,    "AT+CMQTTSTART\r",  "OK",200,2,0},
//    {STATE_IDLE,    "AT+CMQTTCONNECT=0"}
//    
//    
//};


A7680C::A7680C()
{
//    fsm_.current_state = STATE_IDLE;
//    fsm_.retry_count   = 5;             //5次最大尝试机会
}


void A7680C::SetCmdAck(const char *cmd,const char *ack, uint32_t timeout, uint8_t max_try, AtParseHandler handler)
{
    at_fsm_t fsm;
    fsm.current_state = STATE_SEND_CMD;
    fsm.cmd = cmd;
    fsm.ack = ack;
    fsm.timeout = timeout;
    fsm.max_try = max_try;
    fsm.retry_count = 0;
    fsm.parse_handler = handler;
    fsm.parse_suc = false;
    queue_.push(&fsm);
}


/**
 * @brief    向A7680C发送一个命令
 * @param    str   ：要发送数据的首地址
 * @retval   无
 */
void A7680C::SendCmd(void)
{
    memset(a7680c_uart_msg.rxbuff,0,sizeof(a7680c_uart_msg.rxbuff));
//    queue_.front(&fsm_);
    queue_.pop(&fsm_);
    while(*fsm_.cmd !='\0')
	{
		Uart2_Send(*fsm_.cmd++);
	}
}


/**
 * @brief    向A7680C发送一个命令
 * @param    str   ：要发送数据的首地址
 * @retval   无
 */
void A7680C::GetIMEI(uint32_t timeout, uint8_t max_try)
{
    SetCmdAck("AT\r",            "OK",   timeout, max_try, nullptr);
    SetCmdAck("AT+CICCID=?\r",   "OK",   timeout, max_try, hGet_IMEA);
}

void A7680C::ConnectMqtt(uint32_t timeout, uint8_t max_try)
{
    SetCmdAck("AT\r",               "OK",   timeout, max_try,nullptr);
    SetCmdAck("AT+CMQTTSTART\r",    "OK",   timeout, max_try,nullptr);
    SetCmdAck("AT+CMQTTACCQ=0\r",   "OK",   timeout, max_try,nullptr);
    sprintf((char*)a7680c_uart_msg.txbuff, "AT+CMQTTCONNECT=0,\"tcp://%s:%d\",60,1,%s,%s",
        mqttHostUrl,port,username,passwd);
    SetCmdAck(a7680c_uart_msg.txbuff,   "OK",   timeout, max_try,nullptr);
}

void A7680C::PublishOrder(uint32_t timeout, uint8_t max_try)
{
    
}


at_fsm_t* A7680C::GetFsmHandle_()
{
    return &fsm_;
}

at_state_e A7680C::GetFsmState_()
{
    return fsm_.current_state;
}

//void A7680C::SetFsmState(at_state_e state)
//{
//    fsm_.current_state = state;
//}


/**
 * @brief    检查串口缓存数组是否接收应答
 * @param    
 * @retval   bool 
 */
bool A7680C::CheckFsmAck()
{
    if(strstr(a7680c_uart_msg.rxbuff, fsm_.ack) == nullptr)
        return false;
    else
        return true;
}

