#include "rgb.hpp"
#include "bsp_rgb.hpp"
#include "variables.hpp"






void showHsv(int h, int s,int v)
{
    float r,g,b;
    ws2812_hsv_to_rgb(h,s,v,&r,&g,&b);
    ws2812_set_solor((int)r,(int)g,(int)b);
    ws2812_show();
}

void showRgb(int r, int g,int b)
{
    ws2812_set_solor((uint8_t)r,(uint8_t)g,(uint8_t)b);
    ws2812_show();
}


void showColor(Color color, uint8_t brightness)
{
    switch(color)
    {
    case RED:
        showRgb(brightness,0,0);    break;
    case GREEN:
        showRgb(0,brightness,0);    break;
    case BLUE:
        showRgb(0,0,brightness);    break;
    case WHITE:
        showRgb(brightness,brightness,brightness);  break;
    case YELLOW:
        showRgb(brightness,brightness,0);  break;
    case PINK:
        showRgb(brightness,0,brightness);  break;
    default:
        break;
    }
}


void shutRgb(void)
{
    showRgb(0,0,0);
}


void breathRgb(Color color, uint16_t ms_step)
{
    for(uint8_t i=0;i<200;i+=20)
    {
        showColor(color,i);
        delay_ms(ms_step);
    }
    for(uint8_t i=200;i>0;i-=20)
    {
        showColor(color,i);
        delay_ms(ms_step);
    }
    shutRgb();
}

void shineRgb(Color color, uint16_t ms_step, uint8_t times)
{
    for(uint8_t i=0;i<times;i++)
    {
        showColor(color,200);
        delay_ms(ms_step);
        showRgb(0,0,0);
        delay_ms(ms_step);
    }
}

