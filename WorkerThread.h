#pragma once
#include<pthread.h>
#include"EventLoop.h"

//定义子线程结构体
struct WorkerThread
{
    //线程id
    pthread_t tid;
    //线程名
    char tname[32];
    //互斥锁                  锁反应堆
    pthread_mutex_t mutex;
    //条件变量                反应堆不为空
    pthread_cond_t cond;
    //反应堆
    struct EventLoop* evloop;
};

// 初始化
int workerThreadInit(struct WorkerThread* thread, int index); 
// 启动线程
void workerThreadRun(struct WorkerThread* thread);