#pragma once
#include "hk32f04axxA.h"
#include "main.h"

#include "adc.hpp"
#include "can.hpp"
#include "tim.hpp"
#include "usart.hpp"
#include "iic.hpp"
#include "gpio.hpp"
#include "dma.hpp"
//#include "usart.h"
//#include "rtc.h"

#include <cstdint>
#include <cstdio>
#include <cstring>

/*  Algorithm  */
#include "algorithm.hpp"

/*  Application  */
#include "batVolt.hpp"
#include "periph_control.hpp"
#include "low_power.hpp"

/*  Bsp  */
#include "bsp_adc.hpp"
#include "bsp_can.hpp"
#include "bsp_usart.hpp"
#include "bsp_rtc.hpp"

/*  class  */
#include "A7680C.hpp"
#include "bms.hpp"
#include "rgb.hpp"

/*  system  */
#include "MillisTaskManager.h"
#include "System.hpp"
#include "state_machine.hpp"

/*  Task  */
#include "AllTasks.hpp"
#include "main_task.hpp"

#define BAT_ADC_PORT            hadc1

#define CAN_PORT                hcan
#define RGB_TIM_PORT            htim3
#define RGB_TIM_CHANNEL         TIM_CHANNEL_4
#define CHARGE_TIM_PORT         htim4

#define DEBUG_USART_PORT        huart1
#define CAT1_USART_PORT         huart2
#define GPS_USART_PORT          huart3

extern uart_message a7680c_uart_msg;
extern volatile uint32_t system_ms;
extern MillisTaskManager mtmMain;
extern systemStateMachine stateMachine;

//extern parse_t  parse_data_t;
extern A7680C a7680c;
extern Bms bms;
extern Periph_Control periph_control;

extern bool flag_heartbeat;




