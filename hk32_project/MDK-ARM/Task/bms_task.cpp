#include "AllTasks.hpp"
#include "bms.hpp"
#include "variables.hpp"

void BmsTask()
{
    uint8_t try_max = 5;//最多尝试5次bms通信
    while(try_max--)
    {
        while(bms.tryTime)
        {
            bms.tryTime --;
            //如果返回0，则bms查询成功，应当挂起任务
            if(bms.askCar() == 0)
            {
                bms.tryTime = 20;
                bms.read_suc = true;
                return;
            }
            HAL_Delay(280);
        }
    }
    bms.read_suc = false;
    
}