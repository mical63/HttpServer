#pragma once
#include"EventLoop.h"
#include"WorkerThread.h"
#include<stdbool.h>
#include<stdlib.h>

//定义线程池结构体
struct ThreadPool
{
    //是否开启
    bool isStart;
    //线程数量
    int threadNum;
    //子线程数组
    struct WorkerThread* workerthreads;
    //即将调用的线程的下标
    int index;
    //主反应堆
    struct EventLoop* mainevloop;
};

// 初始化线程池
struct ThreadPool* threadPoolInit(struct EventLoop* mainevLoop, int count);

// 启动线程池
void threadPoolRun(struct ThreadPool* pool);

// 取出线程池中的某个子线程的反应堆实例
struct EventLoop* takeWorkerEventLoop(struct ThreadPool* pool);
