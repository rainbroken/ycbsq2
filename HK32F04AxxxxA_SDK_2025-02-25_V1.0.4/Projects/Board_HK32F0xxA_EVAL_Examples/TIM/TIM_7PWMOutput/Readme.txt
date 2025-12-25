/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2023-10-08
1. 首次发布

******************************例程详细描述*****************************
功能描述:
1. TIM1产生7路PWM输出信号，具有4个不同的占空比
2. TIM1的PWM输出频率为17.57KHz；
3. channel 1和channel 1N的占空比为50 % ，
channel 2和channel 2N的占空比为37.5 % ，
channel 3和channel 3N的占空比为25 % ，
channel 4的占空比为12.5 % ；
时钟配置:
1. 本例程采用HSI56MHz作为系统时钟，用户如果需要更改系统时钟配置，
需要配置修改SYSCLK_SOURCE宏定义的。
2. 关于系统时钟如何配置，请参考对应用户手册或者RCC库函数及RCC相关例程。

适用芯片:
HK32F04AxxA

涉及外设:
TIM1

涉及管脚:
PA8 - TIM1 Channel 1
PA9 - TIM1 Channel 2
PA10 - TIM1 Channel 3
PA11 - TIM1 Channel 4
PA7 - TIM1 Channel 1N
PB0 - TIM1 Channel 2N
PB1 - TIM1 Channel 3N

注意事项:
1. 推荐使用MDK5.00及其以上版本编译本工程（MDK - ARM）
或者IAR8.22及其以上版本编译本工程(EWARM);
2. 使用之前检测电源VCC、GND等是否正常。

如何使用:
1. 直接编译程序下载到评估版，重启评估版;

***********************************************************************
