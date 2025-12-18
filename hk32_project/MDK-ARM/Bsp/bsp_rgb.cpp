#include "bsp_rgb.hpp"



//主频8M
#define  bit1   6
#define  bit0   3
uint8_t ws2812_buffer[27];
//extern TIM_HandleTypeDef htim3;

void ws2812_show(void)
{
    HAL_TIM_PWM_Start_DMA(&RGB_TIM_PORT,RGB_TIM_CHANNEL,(uint32_t*)ws2812_buffer,sizeof(ws2812_buffer));
}

/**
 * @description: 设置RGB参数数组
 * @param {uint8_t} R   0-255
 * @param {uint8_t} G   0-255
 * @param {uint8_t} B   0-255
 * @return {*}
 */
void ws2812_set_solor(uint8_t R, uint8_t G, uint8_t B)
{
    uint8_t i;
    for(i=0; i<8; i++)
    {
        ws2812_buffer[i+2]     = (G &(0x80>>i)) ?bit1 :bit0;
        ws2812_buffer[i +8+2]  = (R &(0x80>>i)) ?bit1 :bit0;
        ws2812_buffer[i +16+2] = (B &(0x80>>i)) ?bit1 :bit0;
    }
}

/**
 * @description: 将hsv转换为rgb(不稳定，别用)
 * @param {int} h   范围0-100
 * @param {int} s   范围0-100
 * @param {int} v   范围0-360
 * @param {float} *R
 * @param {float} *G
 * @param {float} *B
 * @return {*}
 */
void ws2812_hsv_to_rgb(int h,int s,int v,float *R,float *G,float *B)
{
    float C = 0,X = 0,Y = 0,Z = 0;
    int i=0;
    float H=(float)(h),S=(float)(s)/100.0f,V=(float)(v)/100.0f;
    if(S == 0)
        *R = *G = *B = V;
    else
    {
        H = H/60;
        i = (int)H;
        C = H - i;
        X = V * (1 - S);
        Y = V * (1 - S*C);
        Z = V * (1 - S*(1-C));
        switch(i)
        {
            case 0 : *R = V; *G = Z; *B = X; break;
            case 1 : *R = Y; *G = V; *B = X; break;
            case 2 : *R = X; *G = V; *B = Z; break;
            case 3 : *R = X; *G = Y; *B = V; break;
            case 4 : *R = Z; *G = X; *B = V; break;
            case 5 : *R = V; *G = X; *B = Y; break;
        }
    }
    *R = *R *255;
    *G = *G *255;
    *B = *B *255;
}