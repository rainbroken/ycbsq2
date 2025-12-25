#pragma once
#include <cstdint>
#include "ring_queue.hpp"

//BMS通信id
#define    RECV_ID   0x1CECF456

#define    CHM_ID    0x1826F456
#define    BHM_ID    0x182756F4
#define    CRM_00_ID 0x1801F456
#define    BRM_ID    0x180256F4
#define    BCP_ID    0x180656F4
#define    CTS_ID    0x1807F456
#define    CML_ID    0x1808F456
#define    BRO_ID    0x100956F4
#define    CRO_ID    0x100AF456
#define    BCL_ID    0x181056F4
#define    BCS_ID    0x181156F4
#define    CCS_ID    0x1812F456
#define    BSM_ID    0x181356F4
#define    BMV_ID    0x181556F4
#define    BMT_ID    0x181656F4
#define    BSP_ID    0x181756F4
#define    BST_ID    0x101956F4
#define    CST_ID    0x101AF456
#define    BSD_ID    0x181C56F4

//接收阶段
enum BMS_STEP
{
    CHM = 0x00,
    CRM_00,
    
    BRM_TPCM_CTS,
    BRM_TPCM_EM,
    
    CRM_AA,
    
    BCP_TPCM_CTS,
    BCP_TPCM_EM,
    
    CTS,
    CML,
    CRO_AA,
    
    BCS_TPCM_CTS,
    BCS_TPCM_EM,
    
    CCS,
    
    BMV_TPCM_CTS,
    BMV_TPCM_EM,
    
    BMT_TPCM_CTS,
    BMT_TPCM_EM,
    
    CST,
    
    CSD
};

typedef struct
{
    uint32_t id;
    uint8_t data[8];
    uint8_t dlc;
}can_frame_t;

typedef struct{
    uint32_t msg_id_;
    uint8_t* message_;
}bms_msg_handle_t_;


typedef struct
{
    double Capcity_Ah_ ;
    double Capcity_V_ ;
    double Ep_ ;
    double Soc_ ;
    double Volt_ ;
    double Elect_ ;
}bms_data_t;


class Bms
{
public:
    Bms();

    uint8_t askCar(void);
    void Send(uint32_t id, uint8_t *data, uint8_t dlc);
        
    bms_data_t bms_data;
    bms_msg_handle_t_ bms_msg[19];

    RingQueue<can_frame_t> queue_;

    //改变检测插上状态逻辑，通过握手解决
    bool ison = false;
    uint8_t pack_len = 0;       //获取辨识报文包长度
    uint8_t pack_char_len = 0;  //获取辨识报文包字符长度
    uint8_t poll_step = CRM_00;      //轮询步数
    uint8_t tryTime = 20;       //Bms查询最大次数
    
    bool read_suc = false;

};

