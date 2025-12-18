#include "bsp_rtc.hpp"
#include "rtc.h"

void bspRtcSetAlarm(uint8_t hour, uint8_t min, uint8_t second)
{
    RTC_AlarmTypeDef aTime;
 
    //…Ë÷√ƒ÷÷”
    aTime.Alarm = 0;
    aTime.AlarmTime.Hours = 0x01;
    aTime.AlarmTime.Minutes = 0x0;
    aTime.AlarmTime.Seconds = 0x0;
    HAL_RTC_SetAlarm_IT(&hrtc,&aTime,RTC_FORMAT_BCD);
}
