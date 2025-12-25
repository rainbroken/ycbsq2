#pragma once
#include <cstdint>

typedef struct
{
    bool flagA7680;
    bool flagBms;
    bool flagRgb;
    bool flagCharge;
}TaskFlag;  

void A7680Task(void);
void BmsTask(void);
void RgbTask(void);
void ChargeTask(void);
void stateMachineTask(void);

