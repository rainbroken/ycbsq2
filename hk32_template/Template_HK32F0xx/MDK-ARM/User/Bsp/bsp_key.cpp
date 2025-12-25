#include "bsp_key.hpp"

#if 0
#define KEY_Port	TOUCH_GPIO_Port
#define KEY_Pin	    TOUCH_Pin
#define KEY         GPIO_ReadInputDataBit(KEY_Port,KEY_Pin)


#if 1
void KeyModeInit(keyMode mode)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    HAL_GPIO_DeInit(TOUCH_GPIO_Port,TOUCH_Pin);
    if(mode == INPUTMODE)
    {
        HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);  //关中断
        GPIO_InitStruct.Pin = TOUCH_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(TOUCH_GPIO_Port, &GPIO_InitStruct);
    }
    else if(mode == EXTIMODE)
    {
        GPIO_InitStruct.Pin = TOUCH_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        HAL_GPIO_Init(TOUCH_GPIO_Port, &GPIO_InitStruct); /* EXTI interrupt init*/

        HAL_NVIC_SetPriority(EXTI9_5_IRQn, 4, 0);
        HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
    }
    delay_ms(3000);
}

/**
 * @brief    按键扫描
 * @param    Frequency          执行该函数的扫描频率
 * @param    filter_time        延迟滤波时间
 *
 * @retval   PRESS_LESS         无按下
 *           PRESS_ONCE         单机
 *           PRESS_TWICE        双击
 *           PRESS_LONGTIME     长按
 * @note
 *
 */
uint8_t Key_Scan(uint16_t Frequency, uint16_t filter_time)
{
    static uint16_t press_flag = 0; //按键按下标志位
    static uint16_t check_once = 0; //按键按下一次标志位
    static uint16_t long_press_record;//长按识别
    static uint16_t delay_time1;    //延时时间1
    static uint16_t delay_time2;    //延时时间2
    static uint16_t delay_time_double;      //两次按下

    //计算1000ms 需要次数
    float countTo1s = 1000.0f/ (float)Frequency;
    //float record_time = (((float)(1.0f/(float)Frequency))*1000.f);

    if(check_once)
    {
        press_flag = 0;
        long_press_record = 0;
        delay_time1 = 0;
        delay_time2 = 0;
        delay_time_double = 0;
    }
    if(check_once&&KEY==1)//如果按键松开回弹后，开启下次扫描
        check_once = 0;

    //检测到按键被按下一次
    if(check_once==0 && KEY==0)
    {
        press_flag = 1;
        if(++delay_time1 >filter_time)
        {
            delay_time1 = 0;
            long_press_record++;
        }
    }

    //检测到按下超过3000ms,视为长按
    if(long_press_record >= (uint16_t)(3000.0f /countTo1s))
    {
        check_once = 1;//按下标志位置1
        return PRESS_LONGTIME;
    }

    //按下一次后检测到松手
    if(press_flag && KEY==1)
    {
        if(++delay_time2 > filter_time)
        {
            delay_time2 = 0;
            delay_time_double ++;
        }
    }

    //(50-500ms)内再次被按下
    if(press_flag && (delay_time_double>(uint16_t)(50.0f/ countTo1s)) && (delay_time_double<(uint16_t)(500.0f/ countTo1s)))
    {
        if(KEY == 0)
        {
            check_once = 1; //按下标志位置1
            return PRESS_TWICE;
        }
    }
    else if(delay_time_double>(uint16_t)(500.0f/ countTo1s))
    {
        check_once = 1; //按下标志位置1
        return PRESS_ONCE;
    }

    return PRESS_LESS;
}

#endif
#endif
