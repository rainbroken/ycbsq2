#pragma once 

#include "variables.hpp"

uint16_t bytesToHalfWord(uint8_t High, uint8_t Low);
//double abs_my(double original);

template<typename T>
T abs_my(T original)
{
    if(original >=0)
        original = original;
    else
        original = -original;
    return original;
}
