#include "algorithm.hpp"
#include "stdint.h"

/**
 * @description: 将高八位和低八位数据进行拼接
 * @param {uint8_t} High
 * @param {uint8_t} Low
 * @return {*}
 */
uint16_t bytesToHalfWord(uint8_t High, uint8_t Low)
{
    uint16_t temp;
    temp = (uint16_t)((High<<8)|Low);
    return temp;
}

//template<typename T>
//T abs_my(T original)
//{
//    if(original >=0)
//        original = original;
//    else
//        original = -original;
//    return original;
//}
