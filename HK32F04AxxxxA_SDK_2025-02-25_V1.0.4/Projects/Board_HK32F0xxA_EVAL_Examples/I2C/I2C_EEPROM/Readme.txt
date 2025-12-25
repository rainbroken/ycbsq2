/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2023-11-03
1.首次发布

******************************例程详细描述*****************************
功能描述:
此固件提供了如何使用I2C固件库的基本示例，以及
与I2C EEPROM设备通信的关联I2C EEPROM驱动器（此处示例为
HK24C02 EEPROM在hk32f0xxa_eval_i2c_ee.h中可查看）

使用的外设是I2C1，但可以通过修改宏定义的值进行配置
在hk32f0xxa_eval.h文件中。

与HK24C02的最大通信速度为400kHz。
通过设置sEE_I2C_TIMING宏定义的值以及I2C模式来配置通信速度
在hk32f0xxa_eval_i2c_ee.h文件中定义。
还需要指明EEPROM的I2C从机地址，该地址根据硬件的连接修改sEE_HW_ADDRESS宏定义，本例程为0XA8
在hk32f0xxa_eval_i2c_ee.h文件中定义。

程序验证流程：
首先，将WriteBuf1 的内容被写入到EE_ADDR1
读取写入的数据。然后将WriteBuf1和读取的缓冲数据进行比较。
然后，执行第二次写入操作，这一次WriteBuf2的数据被
写入到EE_ADDR2。在完成第二写入操作之后，
读取EE_ADDR2的数据。比较WriteBuf2和读取的缓冲数据的内容。
数据比对正确时会点亮LED1与LED2并有相应串口输出，
程序运行流程中的信息将通过串口1打印，请在PC端串口助手查看。

时钟配置:
本例程采用HSI56MHz作为系统时钟，用户如果需要更改系统时钟配置，
需要配置修改SYSCLK_SOURCE宏定义的。
关于系统时钟如何配置，请参考对应用户手册或者RCC库函数及RCC相关例程。

适用芯片:
HK32F04AxxA

涉及外设:
I2C1

USART1:
- BaudRate = 115200 baud
- Word Length = 8 Bits
- One Stop Bit
- No parity
- Hardware flow control disabled (RTS and CTS signals)
- Receive and transmit enabled

涉及管脚:
USART1 TX - PA9
USART1 RX - PA10

I2C SCL - PB6
I2C SDA - PB7

LED1 - PC10
LED2 - PC11

注意事项:
1. 推荐使用MDK5.00及其以上版本编译本工程（MDK - ARM）
或者IAR8.22及其以上版本编译本工程(EWARM);
2. 使用之前检测电源VCC、GND等是否正常。
如何使用:
1. 直接编译程序下载到评估板，重启评估板;
***********************************************************************
