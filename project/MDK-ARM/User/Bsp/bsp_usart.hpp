#pragma once
#include "main.h"
//#include "usart.h"
#include "config.hpp"

#ifdef __cplusplus
extern "C" {
#endif


#define log_print(format, ...) uart1_log_format(format "\r\n", ##__VA_ARGS__)

#ifdef LOG_DEBUG
#define log_debug(format, ...) uart1_log_format("[debug %d][%s]:" format "\r\n", log_cnt++, __func__, ##__VA_ARGS__)
#else
#define log_debug(format, ...)
#endif

#ifdef LOG_INFO
#define log_info(format, ...)  uart1_log_format("[info %d][%s]:" format "\r\n", log_cnt++, __func__, ##__VA_ARGS__)
// 计数 文件名 行号 函数 日志追踪
//#define log_info(format, ...) uart1_log_format("[info %d][%s:%d %s]:" format "\r\n", log_cnt++, __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else
#define log_info(format, ...)
#endif

#ifdef LOG_WARN
#define log_warn(format, ...)  uart1_log_format("[warn %d][%s]:" format "\r\n", log_cnt++, __func__, ##__VA_ARGS__)
#else
#define log_warn(format, ...)
#endif

#ifdef LOG_ERROR
#define log_error(format, ...) uart1_log_format("[eror %d][%s]:" format "\r\n", log_cnt++, __func__, ##__VA_ARGS__)
#else
#define log_error(format, ...)
#endif

extern volatile uint32_t log_cnt;

const uint16_t  kAirSendSize           = 500;
const uint16_t  kAirRecvSize           = 1200;
typedef struct
{
    char        txbuff[kAirSendSize];  //发送数据缓存
	char        rxbuff[kAirRecvSize];  //接收数据缓存
	uint16_t    rxcount;        //接收的数量
    bool        rx_flag;        //接收完毕标志
}uart_message;


void Uart1_Send(uint8_t data);
void Uart2_Send(uint8_t data);

void Uart1_print(uint8_t* str);
void Uart2_print(uint8_t* str);
void uart1_log_format(char* format, ...);

uint8_t USARTx_ReceiveData(USART_TypeDef *huartx);




#ifdef __cplusplus
}
#endif
