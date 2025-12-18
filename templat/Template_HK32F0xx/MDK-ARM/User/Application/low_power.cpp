#include "low_power.hpp"
#include "variables.hpp"

#include "main.h"
#include "adc.h"
#include "can.h"
#include "dma.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"



/**
 * @brief    MCU进入低功耗模式，并且关闭外围电路
 * @param    无
 * @param    无
 * @retval
 */
void EnterStop2Mode_New(void)
{
    //关闭CAN芯片供电
    periph_control.Open_5V(false);
    periph_control.OpenCanPort(false);
//    //关闭RGB
//    periph_control.OpenRGB(false);
    //关闭GPS
    periph_control.OpenGps(false);

    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU); //清除唤醒标志
    __HAL_RCC_PWR_CLK_ENABLE();      //使能电源管理时钟

    SysTick->CTRL = 0x00;   //关闭定时器
    SysTick->VAL  = 0x00;   //清空val,清空定时器

    //关闭TIM定时器
    __HAL_TIM_CLEAR_IT(&CHARGE_TIM_PORT,TIM_IT_UPDATE);
    HAL_TIM_Base_Stop_IT(&CHARGE_TIM_PORT);

    //关闭ADC
    HAL_ADCEx_InjectedStop(&BAT_ADC_PORT);
    HAL_ADC_Stop(&BAT_ADC_PORT);
    HAL_ADC_DeInit(&BAT_ADC_PORT);
    //关闭CAN
    HAL_CAN_Stop(&CAN_PORT);       //这里一定得记得关，否则唤醒后CAN邮箱会占满
    HAL_CAN_MspDeInit(&CAN_PORT);
    bspCanFilter_DeConfig();
    //关闭串口
    HAL_UART_MspDeInit(&CAT1_USART_PORT);
    HAL_UART_MspDeInit(&GPS_USART_PORT);
    //关闭RGB输出引脚
    HAL_TIM_PWM_MspDeInit(&RGB_TIM_PORT);

    //关闭时钟
    __HAL_RCC_GPIOC_CLK_DISABLE();
    __HAL_RCC_GPIOA_CLK_DISABLE();
    __HAL_RCC_GPIOB_CLK_DISABLE();

    //进入睡眠
//    HAL_PWREx_EnterSTOP2Mode(PWR_STOPENTRY_WFI);//进入STOP2
    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
}

/**
 * @brief    MCU唤醒睡眠后启动外围电路
 * @param    无
 * @param    无
 * @retval
 */
void SystemReInit(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_DMA_Init();
    /* CAN初始化 */
    HAL_CAN_MspInit(&CAN_PORT);
    MX_CAN_Init();
    bspCanFilter_Config();

    MX_ADC1_Init();
    //串口初始化
    HAL_UART_MspInit(&CAT1_USART_PORT);
    HAL_UART_MspInit(&GPS_USART_PORT);
    MX_USART2_UART_Init();
    MX_USART3_UART_Init();
    //RGB PWM定时器初始化
    MX_TIM3_Init();
    HAL_TIM_PWM_MspInit(&RGB_TIM_PORT);
    //RTC初始化
    MX_RTC_Init();
    //重新开启定时器
    MX_TIM4_Init();
    __HAL_TIM_CLEAR_IT(&CHARGE_TIM_PORT,TIM_IT_UPDATE);
    HAL_TIM_Base_Start_IT(&CHARGE_TIM_PORT);
    //开启外设
    periph_control.PeriphInit();
    printf("Reinit success\r\n");

}
