#pragma once 

#include <cstdint>


class Periph_Control
{
public:
    Periph_Control();
    void PeriphInit(void);

    bool DetectBsqOnCar(uint8_t max_try = 10);   //检测是否插上车
    bool DetectCHG(void);
    bool DetectPPR(void);

    void OpenGps(bool state);
//    void OpenAdcBat(bool state);
    void OpenBatCharge(bool state);
    void OpenCanPort(bool state);
//    void OpenRGB(bool state);
    void Open_5V(bool state);

private:
    bool gps_state_;
    bool adc_bat_state_;
    bool bat_charge_state_;
    bool can_port_state_;
    bool charge_state_;         //电池充电状态(true:充电中, false:充电完成)
    bool rgb_state_;            //RGB灯状态(true:打开, false:关闭)
    bool en_5v_state_;          //5V电源状态(true:打开, false:关闭)

};

