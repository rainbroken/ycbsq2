#include "main_task.hpp"
//#include "stm32f1xx_hal_tim.h"

void main_setup(void)
{
    mtmMain.Register(A7680Task, 20,true);
    mtmMain.Register(RgbTask, 100,true);
    mtmMain.Register(BmsTask, 280,false);
    mtmMain.Register(stateMachineTask, 100,true);
    
    bspUartInit();
    bspAdcInit();
    bspCanFilter_Config();
    
    periph_control.PeriphInit();
    __HAL_TIM_CLEAR_IT(&htim4,TIM_IT_UPDATE);
    HAL_TIM_Base_Start_IT(&htim4);
    
    //RTC时钟每小时唤醒一次,这里为了方便测试，预留3s定时中断。
    //中断出发函数会设置1h中断
    bspRtcSetAlarm(0x00,0x00,0x03);
   
}

void main_task(void)
{
    for(;;) 
        mtmMain.Running(millis());
}
