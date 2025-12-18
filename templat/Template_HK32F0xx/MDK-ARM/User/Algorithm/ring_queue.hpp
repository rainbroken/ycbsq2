#pragma once
#include <cstdint>
#include <cstring>

template<typename T, uint8_t Capacity = 30>
class RingQueue
{
public:
    RingQueue() : in_(0), out_(0), length_(0) {}
    ~RingQueue() {  clear();    }
    
    bool isFull(void)
    {
        if (length_==Capacity) return true;
        else            return false;
    }        
    
    bool isEmpty(void)
    {
        if (length_==0) return true;
        else            return false;
    }
    
    bool push (const T* data)
    {
        if(!data)       return false;
        if(isFull())    return false;
//        buffer[in_] = *data;
        //入队
        memcpy(&buffer[in_], data, sizeof(T));
        in_ = (++in_)%Capacity;
        length_++;
        return true;
    }
    
    bool pop (T* data)
    {
        if(!data)       return false;
        if(isEmpty())   return false;
//        *data = buffer[out_];
        //出队
        memcpy(data, &buffer[out_], sizeof(T));
        out_ = (++out_)%Capacity;
        length_--;
        return true;
    }
    
    void front(T* data)
    {
        if(!data)       return;
        if(isEmpty())   return;
        *data = buffer[out_];
    }
    
    void back(T* data)
    {
        if(!data)       return;
        if(isEmpty())   return;
        *data = buffer[in_];
    }
    
    void clear(void)
    {
        in_     = 0;
        out_    = 0;
        length_ = 0;
    }
    
    uint8_t getLen(void)
    {
        return length_;
    }
    
    T buffer[Capacity];
    
private:
    uint8_t in_;
    uint8_t out_;
    uint8_t length_;
};
