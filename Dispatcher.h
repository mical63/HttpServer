#pragma once
#include"channel.h"     //封装了文件描述符 事件 回调函数
#include"EventLoop.h"

struct EventLoop;

//结构体，存放六个函数指针
struct Dispatcher
{
    //init
    void* (*init)();
    //添加
    int (*add)(struct channel* chnl,struct EventLoop* evloop);
    //删除
    int (*remove)(struct channel* chnl,struct EventLoop* evloop);
    //修改
    int (*modify)(struct channel* chnl,struct EventLoop* evloop);
    //事件监测
    int (*dispatch)(struct EventLoop* evloop,int timeout);     //单位：s
    //清除数据
    int (*clear)(struct EventLoop* evloop);
};