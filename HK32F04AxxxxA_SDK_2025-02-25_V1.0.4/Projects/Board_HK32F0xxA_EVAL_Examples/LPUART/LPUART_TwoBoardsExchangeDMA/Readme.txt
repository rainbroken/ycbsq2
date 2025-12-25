/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2023-10-23
1.首次发布

******************************例程详细描述*****************************
功能描述:
此示例提供了一个使用Joystick按钮控制两块板间DMA LPUART通信的小型应用程序

-硬件说明
要使用此示例，您需要将其加载到两个HK32板上（我们称之为
板A和板B）然后通过USART线和GND连接这两个板。
*------------------------------------------------------------------------------*
|                BOARD A                                BOARD B                |
|         ____________________                   ____________________          |
|        |                    |                 |                    |         |
|        |                    |                 |                    |         |
|        |     __________     |                 |     __________     |         |
|        |    |   USART  | ____ | TX_____________RX | ____ |   USART  |    |         |
|        |    |  Device1 | ____ | RX_____________TX | ____ |  Device2 |    |         |
|        |    | __________ |    |                 |    | __________ |    |         |
|        |                    |                 |                    |         |
|        |  O LD1             |                 |  O LD1             |         |
|        |  O LD2    Joystick |                 |  O LD2    Joystick |         |
|        |  O LD3        _    |                 |  O LD3        _    |         |
|        |  O LD4       | _ |   |                 |  O LD4       | _ |   |         |
|        |                    |                 |                    |         |
|        |             GND O-- | ---------------- - | --O GND             |         |
|        | ____________________ |                 | ____________________ |         |
|                                                                              |
|                                                                              |
*------------------------------------------------------------------------------*
-引脚之间的连接应使用公共接地。

-软件说明
在板A上，在按钮区处按下：
-LPUART Board A向LPUART Board B发送特定命令（命令
包含事务代码（CMD_RIGHT、CMD_LEFT、CMD_UP、CMD_DOWN或CMD_SEL）
接着是要发送的数据的数量（CMD_RIGHT_SIZE、CMD_LEFT_SIZE、
CMD_UP_SIZE、CMD_DOWN_SIZE或CMD_SEL_SIZE）
-LPUART板B接收命令并向USART板A发送CMD_ACK命令
-LPUART板A接收CMD_ACK命令后，按xx_SIZE发送指定字节数数据
从TxBuffer到USART Board B。
-LPUART Board B将接收到的字节数与定义的字节数进行比较

接收到的数据正确性通过LED点亮发出信号，如下所示：
-Joystick RIGHT且正确接收到数据 => LD2、LD3 ON和LD4 OFF
- Joystick LEFT且正确接收到数据  => LD4 ON、LD2和LD3 OFF
- Joystick UP且正确接收到数据    => LD2 ON，LD3和LD4 OFF
- Joystick DOWN且正确接收到数据  => LD3 ON，LD2和LD4 OFF
- Joystick SEL且正确接收到数据   => LD2、LD3和LD4 ON
并通过串口1打印调试信息可在PC端串口助手查看

上述步骤也可以由Board B方发起Board A接收。

在两个板（板A或板B）中，使用USART收发并通过DMA管理数据传输
SysTick被配置为每10ms产生一次中断。专用计数器，
SysTick 中断函数内用于每100ms切换LED1，指示固件正在运行。

定义的通信超时确保应用程序不会保留
如果USART通信损坏，则进入TimeOut_UserCallback函数陷入死循环卡住。
您可以通过main.h文件中的USER_TIMEOUT定义来调整此超时，默认100，一次10ms也就是1S的超时
取决于CPU频率和应用条件（中断例程，要传输的数据数量、波特率、CPU频率…）。
这些操作可以无限重复。

时钟配置:
本例程采用HSI56MHz作为系统时钟，用户如果需要更改系统时钟配置，
需要配置修改SYSCLK_SOURCE宏定义的。
关于系统时钟如何配置，请参考对应用户手册或者RCC库函数及RCC相关例程。

适用芯片:
HK32F04AxxA

涉及外设:
USART1
LPUART

涉及管脚:
USART1 TX - PA9
USART1 RX - PA10

LPUART TX - PB6
LPUART RX - PB7

LED1 - PC10
LED2 - PC11
LED3 - PC12
LED4 - PD2

BUTTON_RIGHT - PC8
BUTTON_LEFT  - PC9
BUTTON_UP    - PC6
BUTTON_DOWN  - PC7
BUTTON_SEL   - PA0

注意事项:
1. 推荐使用MDK5.00及其以上版本编译本工程（MDK - ARM）
或者IAR8.22及其以上版本编译本工程(EWARM);
2. 使用之前检测电源VCC、GND等是否正常。
如何使用:
1. 直接编译程序下载到评估版，重启评估版;
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
