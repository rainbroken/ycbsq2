#pragma once
#include "stm32f1xx.h"
#include "system_stm32f1xx.h"

#define F_CPU SystemCoreClock
#define CYCLES_PER_MICROSECOND (F_CPU / 1000000U)


uint32_t millis(void);
uint32_t micros(void);
