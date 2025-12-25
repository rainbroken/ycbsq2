#include "periph_control.hpp"
#include "main.h"
#include "bsp_can.hpp"
#include <stdio.h>

Periph_Control::Periph_Control()
{
    gps_state_ = false;
    adc_bat_state_ = false;
    bat_charge_state_ = false;
    can_port_state_ = false;
}

void Periph_Control::OpenGps(bool state)
{
    gps_state_ = state;
    if (state)
        HAL_GPIO_WritePin(CAT1_EN_GPIO_Port, CAT1_EN_Pin, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(CAT1_EN_GPIO_Port, CAT1_EN_Pin, GPIO_PIN_RESET);
}

//void Periph_Control::OpenAdcBat(bool state)
//{
//    adc_bat_state_ = state;
//    if (state)
//        HAL_GPIO_WritePin(ADC_EN_BAT_GPIO_Port, ADC_EN_BAT_Pin, GPIO_PIN_SET);
//    else
//        HAL_GPIO_WritePin(ADC_EN_BAT_GPIO_Port, ADC_EN_BAT_Pin, GPIO_PIN_RESET);
//}

//低电平开启充电
void Periph_Control::OpenBatCharge(bool state)
{
    bat_charge_state_ = state;
   if (state)
       HAL_GPIO_WritePin(CHG_EN_GPIO_Port, CHG_EN_Pin, GPIO_PIN_RESET);
   else
       HAL_GPIO_WritePin(CHG_EN_GPIO_Port, CHG_EN_Pin, GPIO_PIN_SET);
}

void Periph_Control::OpenCanPort(bool state)
{
    can_port_state_ = state;
    Open_5V(state);
    HAL_Delay(1);

    if (state)
    {
        HAL_GPIO_WritePin(V_5V_EN_GPIO_Port, V_5V_EN_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(V_5V_EN_GPIO_Port, V_5V_EN_Pin, GPIO_PIN_RESET);
    }
}


//void Periph_Control::OpenRGB(bool state)
//{
//    rgb_state_ = state;
//    if (state)
//        HAL_GPIO_WritePin(RGB_EN_GPIO_Port, RGB_EN_Pin, GPIO_PIN_SET);
//    else
//        HAL_GPIO_WritePin(RGB_EN_GPIO_Port, RGB_EN_Pin, GPIO_PIN_RESET);
//}

void Periph_Control::Open_5V(bool state)
{
    en_5v_state_ = state;
    if (state)
        HAL_GPIO_WritePin(V_5V_EN_GPIO_Port, V_5V_EN_Pin, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(V_5V_EN_GPIO_Port, V_5V_EN_Pin, GPIO_PIN_RESET);
}



void Periph_Control::PeriphInit(void)
{
    //打开模块的rgb灯
//    OpenRGB(false);
//    HAL_Delay(10);
//    OpenAdcBat(true);   //开启采集电池ADC通道
//    HAL_Delay(100);
    OpenBatCharge(true);
    HAL_Delay(100);
    OpenGps(false);
    HAL_Delay(100);    //延时等待上电稳定
    OpenCanPort(true);
    HAL_Delay(100);
}

bool Periph_Control::DetectBsqOnCar(uint8_t max_try)
{
//    shake_wait_flag = false;
    bms.ison = false;
    uint8_t data_chm[3] = {0x01,0x01,0x00};
    bms.poll_step = 0;

    //发送握手报文，直到应答或者超时
    while(max_try-- && bms.ison==false)
    {
//        printf("try shake hand\r\n");
        bms.Send(0x1826F456,data_chm,3);
        HAL_Delay(250);
    }
    if(bms.ison==true)
    {
        printf("shake hand success\r\n");
        bms.ison = false;
        return true;
    }
    else
    {
        printf("shake hand failed!!!\r\n");
        return false;
    }
}

/**
 * @description: 读取避锁器是否充满电
 * @return {*}  0: 充满电  1: 未充满电
 */
bool Periph_Control::DetectCHG(void)
{
    return (bool)HAL_GPIO_ReadPin(CHG_DET_GPIO_Port,CHG_DET_Pin);
}

/**
 * @description: 读取避锁器是否在充电
 * @return {*}  0: 正在充电  1: 未充电
 */
bool Periph_Control::DetectPPR(void)
{
    return (bool)HAL_GPIO_ReadPin(CHG_STB_GPIO_Port,CHG_STB_Pin);
}



