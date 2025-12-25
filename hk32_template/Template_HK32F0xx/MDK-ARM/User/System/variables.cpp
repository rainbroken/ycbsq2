#include "variables.hpp"
//uart_message air780_uart_msg = {0};


uart_message a7680c_uart_msg = {0};
//parse_t  parse_data_t;

A7680C a7680c;
Bms bms;
Periph_Control periph_control;

volatile uint32_t system_ms = 0;
MillisTaskManager mtmMain;
systemStateMachine stateMachine;

TaskFlag taskFlag;

bool flag_heartbeat = false;
