/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2023-10-31
1.首次发布

******************************例程详细描述*****************************
功能描述:
此示例显示如何使用I2C设备的“从STOP唤醒”功能

此示例需要两块板，主机板与从机板，
主机板与从机板的程序通过是否在在main.h中添加I2C_MASTER宏定义决定！

主机板配置在主模式下运行
从机板配置为从模式，它有一个从机地址。
从机的I2C配置为进入STOP模式的从设备，在激活从停止唤醒功能之后。

主机板用于发送对应从机地址的数据将从机板从STOP唤醒。通过按下
主机板的SEL按钮来发送数据，如果从属设备识别出自己的地址，则从STOP唤醒。
从机唤醒后点亮LED1与LED2，并将接收到的数据准备发送回主机板，主机板读取该数据进行检查。
流程中的调试信息可通过串口1在PC端串口助手查看
此过程无限重复。

注：在进入STOP之前：
1.I2C时钟源必须设置为HSI
2.必须使能时钟延长（NOSTRETCH = 0）才能确保从停机模式唤醒功能正常工作。
3.数字滤波器与从停机模式唤醒功能不兼容，需关掉滤波功能, 将I2C_DigitalFilter = 0

时钟配置:
本例程采用HSI56MHz作为系统时钟，用户如果需要更改系统时钟配置，
需要配置修改SYSCLK_SOURCE宏定义的。
关于系统时钟如何配置，请参考对应用户手册或者RCC库函数及RCC相关例程。

适用芯片:
HK32F04AxxA

涉及外设:
I2C

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

BUTTON_SEL - PA0

LED1 - PC10
LED2 - PC11

注意事项:
1. 推荐使用MDK5.00及其以上版本编译本工程（MDK - ARM）
或者IAR8.22及其以上版本编译本工程(EWARM);
2. 使用之前检测电源VCC、GND等是否正常。
如何使用:
1. 在main.h中宏定义I2C_MASTER后直接编译程序下载到评估板A，重启评估板;
2. 取消宏定义I2C_MASTER后编译程序下载到评估板B，重启评估板;
***********************************************************************
