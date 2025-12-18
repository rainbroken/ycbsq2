#pragma once
#include "hk32f04axxA.h"
#include "system_hk32f0xxa.h"

#define F_CPU SystemCoreClock
#define CYCLES_PER_MICROSECOND (F_CPU / 1000000U)


uint32_t millis(void);
uint32_t micros(void);
