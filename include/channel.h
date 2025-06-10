#pragma once
#include<stdbool.h>

//定义回调函数指针类型
typedef int(*handleFunc)(void* arg);

//枚举 事件类型
enum FDEvent
{
    readEvents = 0x02,
    writeEvents = 0x04
};

//channel结构体
struct channel
{
    //文件描述符
    int fd;
    //事件
    int events;
    //回调函数
    handleFunc read_cb;
    handleFunc write_cb;
    handleFunc destroy_cb;
    //回调函数的参数
    void* arg;
};

//初始化一个channel对象
struct channel* channelInit(int fd,int events,handleFunc read_cb,handleFunc write_cb,handleFunc destroy_cb,void* arg);

// 修改fd的写事件(检测 or 不检测)
void writeEventEnable(struct channel* chnl,bool flag);

// 判断是否需要检测文件描述符的写事件
bool isWriteEventEnable(struct channel* chnl);