/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2023-10-08
1. 首次发布

******************************例程详细描述*****************************
功能描述:
1. 在输出比较定时模式下配置TIM3以及每个通道的相应中断请求，以便生成4个不同的时基；
2. 系统时钟为56MHz，TIM3CLK = 56MHz，TIM3计数器时钟频率为7MHz；
3. CC1 update rate = 170.89Hz，toggling frequency = 85.44Hz,
CC2 update rate = 256.31Hz，toggling frequency = 128.15Hz，
CC3 update rate = 512.63Hz，toggling frequency = 256.31Hz，
CC4 update rate = 1025.34Hz，toggling frequency = 512.67Hz，
时钟配置:
1. 本例程采用HSI56MHz作为系统时钟，用户如果需要更改系统时钟配置，
需要配置修改SYSCLK_SOURCE宏定义的。
2. 关于系统时钟如何配置，请参考对应用户手册或者RCC库函数及RCC相关例程。

适用芯片:
HK32F04AxxA

涉及外设:
TIM3
LED1
LED2
LED3
LED4

涉及管脚:
PC10 - LED1
PC11 - LED2
PC12 - LED3
PD2 - LED4

注意事项:
1. 推荐使用MDK5.00及其以上版本编译本工程（MDK - ARM）
或者IAR8.22及其以上版本编译本工程(EWARM);
2. 使用之前检测电源VCC、GND等是否正常。

如何使用:
1. 直接编译程序下载到评估版，重启评估版;

***********************************************************************
