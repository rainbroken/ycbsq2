#pragma once
#include "variables.hpp"

void bspAdcInit(void);
uint16_t bspAdcGetValue(uint32_t channel);
uint16_t bspAdcVal(uint32_t channel);
uint16_t bspAdcAvgVal(uint32_t channel, uint8_t cnt);
uint16_t ADC_ReadChannel(uint32_t channel);
