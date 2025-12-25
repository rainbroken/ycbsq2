#include "bms.hpp"
#include "bsp_can.hpp"

//握手阶段
uint8_t data_CHM[3] = {0x01,0x01,0x00}; //CHM   0x1826F456
uint8_t data_CRM_00[8] = {0x00,0xB8,0x22,0x00,0x00,0x00,0x00,0x00}; //CRM 0x1801F456
uint8_t data_BRM_TPCM_CTS[8] = {0x11,0x07,0x01,0xFF,0xFF,0x00,0x02,0x00};   //需要改包长,
uint8_t data_BRM_TPCM_EM[8] = {0x13,0x31,0x00,0x07,0xFF,0x00,0x02,0x00};    //需要改字符长
uint8_t data_CRM_AA[8] = {0xAA,0xB8,0x22,0x00,0x00,0x00,0x00,0x00};
//配置阶段
uint8_t data_BCP_TPCM_CTS[8] = {0x11,0x02,0x01,0xFF,0xFF,0x00,0x06,0x00};
uint8_t data_BCP_TPCM_EM[8] = {0x13,0x0D,0x00,0x02,0xFF,0x00,0x06,0x00};

uint8_t data_CTS[7] = {0x06,0x50,0x16,0x04,0x11,0x15,0x20};
uint8_t data_CML[8] = {0xC6,0x11,0xD0,0x07,0xC4,0x09,0xD8,0x0E};
uint8_t data_CRO_AA[1] = {0xAA};

uint8_t data_BCS_TPCM_CTS[8] = {0x11,0x02,0x01,0xFF,0xFF,0x00,0x11,0x00};
uint8_t data_BCS_TPCM_EM[8]  = {0x13,0x09,0x00,0x02,0xFF,0x00,0x11,0x00};

uint8_t data_CCS[7] = {0x83,0x0E,0xA0,0x0F,0x00,0x00,0xFD};

uint8_t data_BMV_TPCM_CTS[8] = {0x11,0x02,0x01,0xFF,0xFF,0x00,0x15,0x00};
uint8_t data_BMV_TPCM_EM[8]  = {0x13,0x09,0x00,0x02,0xFF,0x00,0x15,0x00};

uint8_t data_BMT_TPCM_CTS[8] = {0x11,0x02,0x01,0xFF,0xFF,0x00,0x16,0x00};
uint8_t data_BMT_TPCM_EM[8]  = {0x13,0x09,0x00,0x02,0xFF,0x00,0x16,0x00};

uint8_t data_CST[4] = {0x10,0x00,0xF4,0xF0};
uint8_t data_CSD[8] = {0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00};


Bms::Bms()
{
    queue_.clear();

    bms_data.Capcity_Ah_ =0.0;
    bms_data.Capcity_V_  =0.0;
    bms_data.Ep_         =0.0;
    bms_data.Soc_        =0.0;
    bms_data.Volt_       =0.0;
    bms_data.Elect_      =0.0;

    bms_msg[CHM].msg_id_ = 0x1826F456;
    bms_msg[CRM_00].msg_id_ = 0x1801F456;

    bms_msg[BRM_TPCM_CTS].msg_id_ = 0x1CECF456;
    bms_msg[BRM_TPCM_EM].msg_id_ = 0x1CECF456;

    bms_msg[CRM_AA].msg_id_ = 0x1801F456;

    bms_msg[BCP_TPCM_CTS].msg_id_ = 0x1CECF456;
    bms_msg[BCP_TPCM_EM].msg_id_ = 0x1CECF456;

    bms_msg[CTS].msg_id_ = 0x1CECF456;
    bms_msg[CML].msg_id_ = 0x1808F456;
    bms_msg[CRO_AA].msg_id_ = 0x100AF456;

    bms_msg[BCS_TPCM_CTS].msg_id_ = 0x1CECF456;
    bms_msg[BCS_TPCM_EM].msg_id_ = 0x1CECF456;

    bms_msg[CCS].msg_id_ = 0x1812F456;

    bms_msg[BMV_TPCM_CTS].msg_id_ = 0x1CECF456;
    bms_msg[BMV_TPCM_EM].msg_id_ = 0x1CECF456;

    bms_msg[BMT_TPCM_CTS].msg_id_ = 0x1CECF456;
    bms_msg[BMT_TPCM_EM].msg_id_ = 0x1CECF456;

    bms_msg[CST].msg_id_ = 0x101AF456;
    bms_msg[CSD].msg_id_ = 0x181DF456;
}

void Bms::Send(uint32_t id, uint8_t *data, uint8_t dlc)
{
    bspCanSend(id,data,dlc);
}

uint8_t Bms::askCar(void)
{
//    tryTime = 20;
//    poll_step = CRM_00; //这里已经前面做了握手检测

//    while(tryTime)
//    {
//        tryTime--;
//        printf("step =%d\r\n",poll_step);
//        printf("pack size =%d, char len =%d\r\n",pack_len,pack_char_len);
//        printf("bms.QueueGetLenght() =%d \r\n",bms.QueueGetLenght());
        switch(poll_step)
        {
        case CHM:
            // printf("---------0-----------");
            Send(0x1826F456,data_CHM,3);        break;
        case CRM_00:
            // printf("---------1-----------");
            Send(0x1801F456,data_CRM_00,8);     break;
        case BRM_TPCM_CTS:
            // printf("---------2-----------");
            data_BRM_TPCM_CTS[1] = pack_len;    //获取bms信息
            // printf("data_CRM_TPCM_CTS =  %x %x  %x %x  %x %x  %x %x",data_CRM_TPCM_CTS[0],data_CRM_TPCM_CTS[1],data_CRM_TPCM_CTS[2],data_CRM_TPCM_CTS[3],data_CRM_TPCM_CTS[4],data_CRM_TPCM_CTS[5],data_CRM_TPCM_CTS[6],data_CRM_TPCM_CTS[7]);
            Send(0x1CECF456,data_BRM_TPCM_CTS,8); break;
        case BRM_TPCM_EM:
            // printf("---------3-----------");
            data_BRM_TPCM_EM[1] = pack_char_len;
            data_BRM_TPCM_EM[3] = pack_len;
//            printf("send = %x %x %x %x %x %x %x %x\r\n",data_CRM_TPCM_EM[0],data_CRM_TPCM_EM[1],data_CRM_TPCM_EM[2],data_CRM_TPCM_EM[3],data_CRM_TPCM_EM[4],data_CRM_TPCM_EM[5],data_CRM_TPCM_EM[6],data_CRM_TPCM_EM[7]);
            Send(0x1CECF456,data_BRM_TPCM_EM,8);    //查询电压、温度信息
//            poll_step = CRM_AA;
            delay_ms(260);
            Send(0x1801F456,data_CRM_AA,8);
            break;
        case BCP_TPCM_CTS:
            //结束接收报文
            // printf("---------4-----------");
//            printf("send %X %X %X %X %X %X %X %X\r\n",data_BCP_TPCM_CTS[0],data_BCP_TPCM_CTS[1],data_BCP_TPCM_CTS[2],data_BCP_TPCM_CTS[3],data_BCP_TPCM_CTS[4],data_BCP_TPCM_CTS[5],data_BCP_TPCM_CTS[6],data_BCP_TPCM_CTS[7]);
            Send(0x1CECF456,data_BCP_TPCM_CTS,8);
            break;
        case BCP_TPCM_EM:
            // printf("---------5-----------");
//            printf("send %X %X %X %X %X %X %X %X\r\n",data_BCP_TPCM_EM[0],data_BCP_TPCM_EM[1],data_BCP_TPCM_EM[2],data_BCP_TPCM_EM[3],data_BCP_TPCM_EM[4],data_BCP_TPCM_EM[5],data_BCP_TPCM_EM[6],data_BCP_TPCM_EM[7]);
            Send(0x1CECF456,data_BCP_TPCM_EM,8);
            poll_step = CTS;
            bms.queue_.clear();
            break;

        case CTS:
            Send(0x1807F456,data_CTS,7);
            poll_step = CML;
            break;
        case CML:
            Send(0x1808F456,data_CML,8);
            bms.queue_.clear();
            break;
        case CRO_AA:
            Send(0x100AF456,data_CRO_AA,1);
            poll_step = CRM_00;
            return 0;
//            break;
/**************************目前发送CRO_AA 后，BMS就会停止发送报文，问题解决(9.13)*****************************/
        case BCS_TPCM_CTS:
            data_BCS_TPCM_CTS[1] = pack_len;
            Send(0x1CECF456,data_BCS_TPCM_CTS,8);
            break;
        case BCS_TPCM_EM:
            data_BCS_TPCM_EM[1] = pack_char_len;
            data_BCS_TPCM_EM[3] = pack_len;
            Send(0x1CECF456,data_BCS_TPCM_EM,8);
            poll_step = CCS;
            break;
        case CCS:
            Send(0x1812F456,data_CCS,7);
            break;
        case BMV_TPCM_CTS:
            data_BCS_TPCM_CTS[1] = pack_len;
            Send(0x1CECF456,data_BMV_TPCM_CTS,8);
            break;
        case BMV_TPCM_EM:
            data_BMV_TPCM_EM[1] = pack_char_len;
            data_BMV_TPCM_EM[3] = pack_len;
            Send(0x1CECF456,data_BMV_TPCM_EM,8);
            break;
        case BMT_TPCM_CTS:
            data_BMT_TPCM_CTS[1] = pack_len;
            Send(0x1CECF456,data_BMT_TPCM_CTS,8);
            break;
        case BMT_TPCM_EM:
            data_BMT_TPCM_EM[1] = pack_char_len;
            data_BMT_TPCM_EM[3] = pack_len;
            Send(0x1CECF456,data_BMT_TPCM_EM,8);
            break;
        case CST:
            Send(0x101AF456,data_CST,4);
            break;
        case CSD:
            Send(0x181DF456,data_CSD,8);
            poll_step = CHM;
            return 0;
        default:
            break;
        }
    return 1;

}
