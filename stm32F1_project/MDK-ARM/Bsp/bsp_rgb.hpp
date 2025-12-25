#pragma once

#include "variables.hpp"


void ws2812_show(void);
void ws2812_set_solor(uint8_t R, uint8_t G, uint8_t B);
void ws2812_hsv_to_rgb(int h,int s,int v,float *R,float *G,float *B);
