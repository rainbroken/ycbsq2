#pragma once

/*串口1 debug 功能 */
#define UART1_RE_PRINTF   1
//使能串口dma接收（未实现）
#define UART1_DMA_RX      0

#define LOG_INFO    1
#define LOG_DEBUG   1
#define LOG_WARN    1
#define LOG_ERROR   1

/* A7680C 串口配置 */
#define A7680_RXNE_INT_ENABLE  1
#define A7680_IDLE_INT_ENABLE  0
//串口接收中断打印(测试阶段开启，正式阶段关闭)
#define A7680_RX_INT_PRINT     1

