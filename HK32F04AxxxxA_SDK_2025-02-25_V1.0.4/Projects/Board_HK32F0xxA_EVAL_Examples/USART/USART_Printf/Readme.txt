/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2023-10-23
1.首次发布

******************************例程详细描述*****************************
功能描述:
此示例显示如何将C库printf函数重定向到USART1。
此实现基于USART1使用printf即可在PC端串口助手上输出消息
在PUTCHAR_PROTOTYPE函数中重定向输出位置，该函数在hk32f0xxa_eval.c中

时钟配置:
本例程采用HSI56MHz作为系统时钟，用户如果需要更改系统时钟配置，
需要配置修改SYSCLK_SOURCE宏定义的。
关于系统时钟如何配置，请参考对应用户手册或者RCC库函数及RCC相关例程。

适用芯片:
HK32F04AxxA

涉及外设:
USART1
串口1配置如下：
- BaudRate = 115200 baud
- Word Length = 8 Bits
- One Stop Bit
- No parity
- Hardware flow control disabled (RTS and CTS signals)
- Receive and transmit enabled

涉及管脚:
USART1 TX - PA9
USART1 RX - PA10

注意事项:
1. 推荐使用MDK5.00及其以上版本编译本工程（MDK - ARM）
或者IAR8.22及其以上版本编译本工程(EWARM);
2. 使用之前检测电源VCC、GND等是否正常。
如何使用:
1. 直接编译程序下载到评估板，重启评估板;
***********************************************************************
