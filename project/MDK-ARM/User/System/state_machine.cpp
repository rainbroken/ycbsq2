#include "state_machine.hpp"
#include "variables.hpp"

void systemStateMachine::running()
{
    switch(systemState_)
    {
// 1.系统唤醒，回复外围电路
    case sms_WAKEUP:
        SystemReInit();
        systemState_ = sms_DETECT_CAR;  //状态机切换模式:检测BMS握手
        break;

// 2.检测与BMS握手
    case sms_DETECT_CAR:
        //握手成功，进入bms读取
        if(periph_control.DetectBsqOnCar(10))
            systemState_ = sms_BMS;
        //握手失败，检测OTA更新
        else
            systemState_ = sms_DETECT_OTA;
        break;

// 3.握手成功，进行bms读取任务，同时阻塞所有进程 <待优化>
    case sms_BMS:
        if(bms.read_suc == false)
        {
            mtmMain.SetState(BmsTask,true);
        }
        //读取成功，准备联网上报
        else
        {
            mtmMain.SetState(BmsTask, false);   //挂起bms任务
            systemState_ = sms_CONNECT_MQTT;
        }
        break;

// 4.联网，准备上报
    case sms_CONNECT_MQTT:
        a7680c.ConnectMqtt();
        //等待联网成功
        if((a7680c.GetFsmState_() == STATE_SUCCESS) &&(a7680c.queue_.getLen() == 0))
        {
            systemState_ = sms_PUBLISH_ORDER;
        }
        break;

// 5.发布指令码
    case sms_PUBLISH_ORDER:
//        a7680c.
        break;

    case sms_GET_ORDER_CODE:
        break;

    case sms_PUBLISH_PAYLOAD:
        break;

    case sms_PUBLISH_HEARTBEAR:
        break;

    case sms_DETECT_OTA:
        break;

    case sms_OTA_UPDATE:
        break;

    case sms_SLEEP:
        break;

    case sms_ERROR:
        break;

    default:
        break;
    }
}




