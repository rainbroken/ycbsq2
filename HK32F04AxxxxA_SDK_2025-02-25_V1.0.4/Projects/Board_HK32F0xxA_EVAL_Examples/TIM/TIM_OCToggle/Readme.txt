/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2023-10-08
1. 首次发布

******************************例程详细描述*****************************
功能描述:
1. 配置TIM3外围设备以生成具有四个不同频率的四个不同信号；
2. TIM3CLK = 56MHz；
3. CC1 update rate = TIM3 counter clock / CCR1_Val = 1367.1 Hz
因此TIM3 channel 1 产生1个周期型号的频率为683.5Hz；
3. CC2 update rate = TIM3 counter clock / CCR2_Val = 2734.3 Hz
因此TIM3 channel 2 产生1个周期型号的频率为1367.1Hz；
3. CC3 update rate = TIM3 counter clock / CCR3_Val = 5468.6 Hz
因此TIM3 channel 1 产生1个周期型号的频率为2734.3Hz；
3. CC4 update rate = TIM3 counter clock / CCR4_Val = 10937.2 Hz
因此TIM3 channel 1 产生1个周期型号的频率为5468.6Hz。
时钟配置:
1. 本例程采用HSI56MHz作为系统时钟，用户如果需要更改系统时钟配置，
需要配置修改SYSCLK_SOURCE宏定义的。
2. 关于系统时钟如何配置，请参考对应用户手册或者RCC库函数及RCC相关例程。

适用芯片:
HK32F04AxxA

涉及外设:
TIM3

涉及管脚:
PA6 - TIM3 Channel 1
PA7 - TIM3 Channel 2
PB0 - TIM3 Channel 3
PB1 - TIM3 Channel 4

注意事项:
1. 推荐使用MDK5.00及其以上版本编译本工程（MDK - ARM）
或者IAR8.22及其以上版本编译本工程(EWARM);
2. 使用之前检测电源VCC、GND等是否正常。

如何使用:
1. 直接编译程序下载到评估版，重启评估版;

***********************************************************************
