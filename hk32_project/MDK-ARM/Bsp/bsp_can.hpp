#pragma once 

#include "variables.hpp"


uint8_t bspCanFilter_Config(void);
void bspCanFilter_DeConfig(void);
void bspCanSend(uint32_t id, uint8_t *data, uint8_t dlc);

