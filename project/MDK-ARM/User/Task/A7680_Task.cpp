#include "AllTasks.hpp"
#include "A7680C.hpp"
#include "variables.hpp"

//最大尝试次数
//#define     MAX_RETRY   5 

#ifdef __cplusplus
extern "C" {
#endif

void at_fsm_run(A7680C *a7680_) 
{
    if(a7680_ == nullptr)
    {
        log_error("at_fsm_run ptr error");
        return;
    }
    
    //获取句柄
    at_fsm_t *fsm =  a7680_->GetFsmHandle_();
    log_info("current_state = %d",fsm->current_state);
    
    switch(fsm->current_state) 
    {
//句柄出队
    case STATE_IDLE:
        //检测发送队列是否存留消息
        if(a7680_->GetQueueLen() != 0)
        {
            a7680_->queue_.front(fsm);
            fsm->current_state = STATE_SEND_CMD;
        }
        break;
            
    case STATE_SEND_CMD:
        a7680_->SendCmd();
        fsm->current_state = STATE_WAIT_ACK;
        break;
        
    case STATE_WAIT_ACK:
        //若已经收到回复,则重置状态
        if (a7680_->CheckFsmAck() == true)   
        {
            fsm->current_state = STATE_PARSE;
            fsm->retry_count = 0;
        } 
        //没收到回复，继续等 &检测超时
        else
        {
            fsm->retry_count++ ;
            //未超过尝试次数，准备重新发送
            if(fsm->retry_count < fsm->max_try)
            {
                fsm->current_state = STATE_SEND_CMD;
            }
            //超过尝试次数，进入超时处理
            else 
            {
                fsm->current_state = STATE_TIMEOUT;
            }
        }
        break;
//数据解析
    case STATE_PARSE:
        //需要解析数据
        if(fsm->parse_handler != nullptr)
        {
            //解析完毕
            if(fsm->parse_handler())
            {
                fsm->parse_suc = true;
                fsm->current_state = STATE_SUCCESS;
            }
            else
                fsm->current_state = STATE_ERR;
        }
        //不需要解析数据
        else
        {
            fsm->parse_suc = true;
            fsm->current_state = STATE_SUCCESS;
        }
        break;
        
    case STATE_SUCCESS:
        break;
        
    case STATE_TIMEOUT:
        break;
    
    case STATE_ERR:
        break;
    
    default:
        break;
    }
}


/**
  * @brief  时间差判定
  * @param  nowTick:当前时间
  * @param  prevTick:上一个时间
  * @retval 时间差
  */

void A7680Task(void)
{
    at_fsm_run(&a7680c);
}

#ifdef __cplusplus
}
#endif

