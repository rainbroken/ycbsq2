#pragma once
#include <cstdint>

typedef enum
{
    sms_WAKEUP = 0x00,
    sms_DETECT_CAR,
    sms_BMS,
    sms_CONNECT_MQTT,
    sms_PUBLISH_ORDER,
    sms_GET_ORDER_CODE,
    sms_PUBLISH_PAYLOAD,
    sms_PUBLISH_HEARTBEAR,
    sms_DETECT_OTA,
    sms_OTA_UPDATE,
    sms_SLEEP,
    sms_ERROR
}systemState;

class systemStateMachine
{
public:    
    systemStateMachine() :systemState_(sms_WAKEUP)    {}
        
    void running(); 
    void setState(systemState state);
    systemState getState(void);
    void setErrcode(uint8_t err);
    uint16_t praseErrcode();
private:   
    systemState systemState_;
    uint16_t errcode_ = 0x07FF;
};

