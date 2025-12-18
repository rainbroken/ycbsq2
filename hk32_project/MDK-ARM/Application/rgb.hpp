
#pragma once 
#include <cstdint>

#define MAX_RGB_TASKS  2

enum Color
{
    RED,
    GREEN,
    BLUE,
    WHITE,
    YELLOW,
    PINK,
};

typedef struct {
    uint8_t Run;        // 运行标志
    uint8_t Timer;      // 计时器
    uint8_t ItvTime;    // 间隔时间（单位：ms）
    void (*TaskFunc)(Color, uint16_t, uint8_t); // 任务函数指针
}RGB_Task_t;



void showHsv(int h, int s,int v);
void showRgb(int r, int g,int b);

void showColor(Color color, uint8_t brightness);
void shutRgb(void);   

void breathRgb(Color color, uint16_t ms_step);
void shineRgb(Color color, uint16_t ms_step, uint8_t times);
