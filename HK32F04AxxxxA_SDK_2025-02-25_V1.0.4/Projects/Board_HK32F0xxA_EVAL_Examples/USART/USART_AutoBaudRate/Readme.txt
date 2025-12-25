/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2023-10-23
1.首次发布

******************************例程详细描述*****************************
功能描述:
本例介绍了如何使用USART自动波特率功能。

首先，配置USART1
使用StartBit测量方法自动检测波特率（任何字符
以1开始的比特应当被发送到USART以检测波特率）。
配置后，USART等待，直到PC端通过串口助手发送数据到评估板
随即启动波特率阶段的自动检测。通过ABRF标志，监控此阶段的结束

自动检测的结果由EVAL板指示灯指示。在自动波特率阶段如果发生错误
ABRE标志被置1，LED3被打开，
如果该阶段成功完成，LED2亮起，
并将接收到的数据传回到PC端
您可以通过更改PC端侧串口助手的波特率来重复此过程以测试设备的波特率自适应。
LED1与LED4闪烁用来指示程序正在运行

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

LED1 - PC10
LED2 - PC11
LED3 - PC12
LED4 - PD2

注意事项:
1. 推荐使用MDK5.00及其以上版本编译本工程（MDK - ARM）
或者IAR8.22及其以上版本编译本工程(EWARM);
2. 使用之前检测电源VCC、GND等是否正常。
如何使用:
1. 直接编译程序下载到评估板，重启评估板;
***********************************************************************
