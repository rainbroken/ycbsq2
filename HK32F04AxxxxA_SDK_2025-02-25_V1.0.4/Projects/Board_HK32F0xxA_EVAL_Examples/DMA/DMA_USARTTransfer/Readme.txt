/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2023-10-19
1.首次发布

******************************例程详细描述*****************************
功能描述:
这个例子使用DMA2提供了USART1和USART2之间的基本通信能力。

首先，DMA将数据从TxBuffer2缓冲区传输到USART2传输数据寄存器，
然后将此数据发送到USART1。
传输USART1接收到的数据并存储在RxBuffer1中，然后与发送的数据和结果
进行比较这个比较的数据存储在“TransferStatus1”变量中。

同时，DMA将数据从TxBuffer1缓冲区传输到USART1 Transmit数据寄存器，
然后将该数据发送到USART2。
USART2接收到的数据为通过DMA传输并存储在RxBuffer2中，
然后与发送的和进行比较比较的结果存储在“TransferStatus2”变量中。

时钟配置:
本例程采用HSI56MHz作为系统时钟，用户如果需要更改系统时钟配置，
需要配置修改SYSCLK_SOURCE宏定义的。
关于系统时钟如何配置，请参考对应用户手册或者RCC库函数及RCC相关例程。

适用芯片:
HK32F04AxxA

涉及外设:
USART1和USART2
USART1和USART2配置如下:
—波特率 = 9600
- 字长 = USART_WordLength_7b
—停止位 = USART_StopBits_1
—奇偶校验 = USART_Parity_No
- 硬件流控制被禁用(RTS和CTS信号)
—使能接收和发送
涉及管脚:
USART1 TX - PA9
USART1 RX - PA10

USART2 TX - PA2
USART2 RX - PA3

注意事项:
1. 推荐使用MDK5.00及其以上版本编译本工程（MDK - ARM）
或者IAR8.22及其以上版本编译本工程(EWARM);
2. 使用之前检测电源VCC、GND等是否正常。

如何使用:
1. 直接编译程序下载到评估版，重启评估版;
***********************************************************************
