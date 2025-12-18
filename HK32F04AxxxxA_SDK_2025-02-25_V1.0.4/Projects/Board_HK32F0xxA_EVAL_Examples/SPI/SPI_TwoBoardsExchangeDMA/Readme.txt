/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2023-10-08
1. 首次发布

******************************例程详细描述*****************************
功能描述:
1. 此示例提供了一个小型应用程序，其中按钮用于使用DMA并通过使用SPI固件库来触发SPI通信；
2. 此应用需要使用两块HK32应用板（A和B板），A板作为master，B板作为slave，连线方式如下：
*------------------------------------------------------------------------------*
|                BOARD A                                BOARD B                |
|         ____________________                   ____________________          |
|        |                    |                 |                    |         |
|        |                    |                 |                    |         |
|        |     __________ ____ | _______SCK_______ | ____ __________     |         |
|        |    | SPI Master | ____ | _______MOSI______ | ____ | SPI Slave |    |         |
|        |    |  Device  | ____ | _______MISO______ | ____ |  Device  |    |         |
|        |    | __________ | ____ | _______NSS_______ | ____ | __________ |    |         |
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
*------------------------------------------------------------------------------ *
3. 主机模式和从机模式下，SPI配置为全双工DMA模式，硬件NSS；
4. 主设备使用TIM2_CH2 DMA请求（DMA1_Channel3）向从设备发送特定命令
（该命令包含事务代码（CMD_RIGHT、CMD_LEFT、CMD_UP、CMD_DOWN或CMD_SEL），
并使用SPI_Rx DMA请求（DMA 1_Channel2）从设备接收ACK命令；
5. 从设备使用SPI_Rx DMA请求（DMA1_Channel2）接收命令，
并使用SPI_Tx DMA请求发送ACK命令（DMA1_Channel3）；
6. 主设备使用TIM2_CH2 DMA请求（DMA1_Channel3）将定义的NumberOfByte
从TxBuffer发送到从设备，并使用SPI_Rx DMA请求（DMA 1_Channel2）
将NumberOf字节从从设备接收到Rxbuffer；
7. 从设备使用SPI_Tx DMA请求（DMA1_Channel3）将定义的NumberOfByte从
Txbuffer发送到主设备，并使用SPI_Rx DMA请求从主设备接收NumberOf字节
（DMA1_Channel2）到Rxbuffer；
8. Master将接收到的NumberOfByte数据与TxBuffer中定义的数据进行比较，
并检查ACK命令，接收到的数据正确性通过LD点亮发出信号，如下所示：
- 操纵手柄JOY_RIGHT和数据正确接收 => LD2和LD3 ON和LD4 OFF
- 操纵手柄JOY_LEFT和正确接收到的数据 => LD4打开，LD2和LD3关闭
- 操纵手柄JOY_UP和正确接收到的数据 => LD2打开，LD3和LD4关闭
- 操纵手柄JOY_DOWN和正确接收到的数据 => LD3打开，LD2和LD4关闭
- 操纵手柄JOY_SEL和数据正确接收 => LD2、LD3和LD4指示灯亮起
9. 从设备将接收到的NumberOfByte数据与TxBuffer中定义的数据进行比较，
并检查接收到的命令。接收到的数据正确性通过LED点亮发出信号，如下所示：
-接收到命令CMD_RIGHT和正确接收到数据 => LD2和LD3 ON和LD4 OFF
- 接收到命令CMD_LEFT和正确接收到数据 => LD2打开，LD3和LD4关闭
-接收到命令CMD_UP和正确接收到的数据 => LD2打开，LD3和LD4关闭
-接收到命令CMD_DOWN和正确接收到的数据 => LD3打开，LD2和LD4关闭
-接收到命令CMD_SEL和正确接收到数据 => LD2、LD3和LD4指示灯亮起
10. SysTick被配置为每10ms产生一次中断。SysTick ISR内部的专用
计数器用于每隔100ms切换LD1，指示固件正在运行；

时钟配置:
1. 本例程采用HSI56MHz作为系统时钟，用户如果需要更改系统时钟配置，
需要配置修改SYSCLK_SOURCE宏定义的。
2. 关于系统时钟如何配置，请参考对应用户手册或者RCC库函数及RCC相关例程。

适用芯片:
HK32F04AxxA

涉及外设:
SPI
GPIO
TIM2
SysTick

涉及管脚:
SPI_SCK - PA5
SPI_MISO - PB4
SPI_MOSI - PA7
SPI_CS - PA15
PC10 - LED1
PC11 - LED2
PC12 - LED3
PD2 - LED4
PC8 - BUTTON_UP
PC9 - BUTTON_DOWN
PC10 - BUTTON_LEFT
PC11 - BUTTON_RIGHT
PA0 - BUTTON_SEL

注意事项:
1. 推荐使用MDK5.00及其以上版本编译本工程（MDK - ARM）
或者IAR8.22及其以上版本编译本工程(EWARM);
2. 使用之前检测电源VCC、GND等是否正常。

如何使用:
1. 直接编译程序下载到评估版，重启评估版;

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
