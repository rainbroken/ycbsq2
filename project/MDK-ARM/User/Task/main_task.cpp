#include "main_task.hpp"


void fun1(void)
{
    log_info("hello");
}
void fun2(void)
{
    log_info("----------");
}


void main_setup(void)
{

    uint8_t data[8] = {0x01,0x02,0x03,0x04,0x05 ,0x06,0x07,0x08};
// systick 配置1ms中断
    SystemInit();
    SysTick_Config(SystemCoreClock/ 1000);
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
/*  外设配置  */
//    vGPIO_Init();
//    ADC1_Init();
//    DMA_Config();
    CAN1_Init();
//    TIM3_Init();      //RGB灯定时器
    TIM6_Init();        //系统走时定时器

    USART1_UART_Init(115200);
//    USART2_UART_Init(115200);
//    IIC2_Init();

    for(;;)
    {
       bspCanSend(0x1826F456,data,8);
    }


}

void main_task(void)
{
    for(;;) mtmMain.Running(millis());

}



#if 0
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
#endif
