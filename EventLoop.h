#pragma once
#include"Dispatcher.h"
#include"channel.h"
#include"ChannelMap.h"
#include<pthread.h>
#include<stdbool.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>

extern struct Dispatcher EpollDispatcher;
extern struct Dispatcher PollDispatcher;
extern struct Dispatcher SelectDispatcher;

//枚举处理方式
enum Elemtype {ADD,DELETE,MODIFY};

//定义任务队列的节点结构体
struct ChannelElement
{
    int type;     //处理方式
    struct channel* chnl;
    struct ChannelElement* next;
};

struct Dispatcher;   //如果两个结构体互相包含。可以提前做一个声明，就不报错了

struct EventLoop
{
    //判断Eventloop是否运行
    bool isQuit;
    //结构体指针，指向EpollDispatcher  PollDispatcher  SelectDispatcher，可自行选择epoll poll select
    struct Dispatcher* dispatcher;
    //存放数据的数据块      例如 epoll 的红黑树  也可自行选择
    void* dispatcherData;
    //任务队列 头指针 尾指针
    struct ChannelElement* head;
    struct ChannelElement* tail;
    // map
    struct ChannelMap* channelMap;
    //线程id name
    pthread_t tid;
    char tname[32];
    //互斥锁      锁任务队列
    pthread_mutex_t mutex;
    //存储用于本进程内线程通信的fd，以便主线程唤醒子线程
    int sv[2];
};

//初始化
struct EventLoop* eventLoopInit();
struct EventLoop* eventLoopInitEx(const char* threadName);

// 启动反应堆模型
int eventLoopRun(struct EventLoop* evLoop);

// 处理别激活的文件fd
int eventActivate(struct EventLoop* evLoop, int fd, int event);

//向任务队列中添加任务
int eventLoopAddTask(struct EventLoop* evloop,struct channel* chnl,int type);

//处理任务
int eventLoopProcessTask(struct EventLoop* evloop);

// 处理dispatcher中的节点
int eventLoopAdd(struct EventLoop* evloop, struct channel* chnl);
int eventLoopRemove(struct EventLoop* evloop, struct channel* chnl);
int eventLoopModify(struct EventLoop* evloop, struct channel* chnl);

// 释放channel
int destroyChannel(struct EventLoop* evloop, struct channel* chnl);
