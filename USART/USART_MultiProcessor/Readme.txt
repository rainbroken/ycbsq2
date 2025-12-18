/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2023-10-23
1.首次发布

******************************例程详细描述*****************************
功能描述:
本示例介绍了如何在多处理器模式下使用USART。
USARTx和USARTy是USART1和USART2

首先，USARTx和USARTy地址被设置为0x1和0x2, 使能USARTy的静默与活动切换模式。
USARTx将字符0x33循环地发送给USARTy。然后USARTy接收到0x33
并切换LED1、LED2、LED3以及LED4引脚
同时，当BUTTON_DOWN按下时，将产生中断
在EXTI4_15_IRQHandler程序中，USARTy发送一个不是USARTy的地址0x3，使USARTy进入静默模式
在此模式下USARTy无法收到数据（也就无LED切换），直到BUTTON_UP按下发送USARTy地址唤醒之
在这个BUTTON_UP的按键中断程序中，USARTx发送地址标记（0x102）的字符给USARTy
唤醒USARTy，该串口又可以接收到0x33数据，LED重新启动切换。

时钟配置:
本例程采用HSI56MHz作为系统时钟，用户如果需要更改系统时钟配置，
需要配置修改SYSCLK_SOURCE宏定义的。
关于系统时钟如何配置，请参考对应用户手册或者RCC库函数及RCC相关例程。

适用芯片:
HK32F04AxxA

涉及外设:
USART1
USART2
串口1和串口2配置如下：
- BaudRate = 115200 baud
- Word Length = 8 Bits
- One Stop Bit
- No parity
- Hardware flow control disabled (RTS and CTS signals)
- Receive and transmit enabled

涉及管脚:
USART1 TX - PA9
USART1 RX - PA10

USART2 TX - PA2
USART2 RX - PA3

LED1 - PC10
LED2 - PC11
LED3 - PC12
LED4 - PD2

UP_BUTTON   - PC6
DOWN_BUTTON - PC7

注意事项:
1. 推荐使用MDK5.00及其以上版本编译本工程（MDK - ARM）
或者IAR8.22及其以上版本编译本工程(EWARM);
2. 使用之前检测电源VCC、GND等是否正常。
如何使用:
1. 直接编译程序下载到评估板，重启评估板;
***********************************************************************
