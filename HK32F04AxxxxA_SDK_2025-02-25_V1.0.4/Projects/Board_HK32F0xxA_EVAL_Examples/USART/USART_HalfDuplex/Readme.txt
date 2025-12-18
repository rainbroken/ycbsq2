/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2023-10-23
1.首次发布

******************************例程详细描述*****************************
功能描述:
此示例提供了 USARTx 和 USARTy 之间的基本通信
使用标志的半双工模式。USARTx 和 USARTy 就是是 USART1 和 USART2，
它具体取决于所使用的评估板和芯片资源。

首先，USARTx 使用 TXE 标志将数据从 TxBuffer1 缓冲区发送到 USARTy。
USARTy 使用 RXNE 标志接收的数据存储在 RxBuffer2 中，然后与
发送的和此比较的结果匹配则亮LED1

然后，USARTy 使用 TXE 标志将数据从 TxBuffer2 缓冲区发送到 USARTx。
USARTx 使用 RXNE 标志接收的数据存储在 RxBuffer1 中，然后与
发送的和此比较的结果匹配则亮LED2

匹配结果也将通过串口1进行输出。可在PC端串口助手查看

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
- BaudRate = 230400 baud
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

注意事项:
1. 推荐使用MDK5.00及其以上版本编译本工程（MDK - ARM）
或者IAR8.22及其以上版本编译本工程(EWARM);
2. 使用之前检测电源VCC、GND等是否正常。
如何使用:
1. 直接编译程序下载到评估板，重启评估板;
***********************************************************************
