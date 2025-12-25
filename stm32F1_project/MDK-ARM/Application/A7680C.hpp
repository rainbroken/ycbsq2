#pragma once 
#include <cstdint>
#include <ctime>
#include "ring_queue.hpp"

#define QUEUE_SIZE 30

#define username       "admin"
#define passwd 	 	   "yh12345"
#define mqttHostUrl    "113.45.141.242"
#define port 		   1883  

typedef bool (*AtParseHandler)(void);

typedef enum 
{
    STATE_IDLE,
    STATE_SEND_CMD,
    STATE_WAIT_ACK,
    STATE_PARSE,
    STATE_SUCCESS,
    STATE_TIMEOUT,
    STATE_ERR,
} at_state_e;

typedef struct 
{
    at_state_e current_state;
    const char *cmd;
    const char *ack;
    uint32_t timeout;
    uint8_t max_try;
    uint8_t retry_count;
    AtParseHandler parse_handler;
    bool parse_suc;
}at_fsm_t;


class A7680C
{
public:
    A7680C();

    typedef struct
    {
        char topic[120];
        char id[80];
        char IMEI[30];
        char* cmd;
        time_t timestamp;
        char msgid[50];
        char* model;
        char vers[30];
        char bootloader_vers[30];
        char sn[20];
        char latitude[20];       //获取到的纬度
        char longitude[20];      //获取到的经度
        char position_way[5];       //定位方式
    }parse_t;
    
    parse_t  parse_data_t;
    RingQueue<at_fsm_t> queue_; //AT任务状态句柄队列

//    void Reset(uint16_t delay_ms);

    void SetCmdAck(const char *cmd,const char *ack, uint32_t timeout, uint8_t max_try, AtParseHandler handler);
    void SendCmd(void);
 
// 获取IMEI
    void GetIMEI(uint32_t timeout=20, uint8_t max_try=3);
//    uint8_t NetInit(uint32_t timeout, uint8_t max_try);
    void ConnectMqtt(uint32_t timeout=20, uint8_t max_try=3);
    void PublishOrder(uint32_t timeout=20, uint8_t max_try=3);

    at_fsm_t*  GetFsmHandle_();
    at_state_e GetFsmState_();
//    void SetFsmState(at_state_e state);
    
    bool CheckFsmAck();         //比对at_fsm_t.expected_ack 和 回复缓冲区 是否相等
/********************   待实现    ***********************/
    void SubscribeTopics(void);
    uint8_t GetTimeStamp(time_t *timeStamp_);
    uint8_t GetLocateLBS(char *lat_,  char *lon_);
    uint8_t GetLocateGPS(char *lat_,  char *lon_);



private:
    at_fsm_t fsm_;              //AT任务状态句柄
    


};    