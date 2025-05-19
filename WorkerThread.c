#include"WorkerThread.h"
#include<stdio.h>

// 初始化
int workerThreadInit(struct WorkerThread* thread, int index)
{
    thread->tid = 0;

    sprintf(thread->tname,"SunThread--%d",index);

    pthread_mutex_init(&thread->mutex,NULL);

    pthread_cond_init(&thread->cond,NULL);

    thread->evloop = NULL;

    return 0;
}

// 子线程的回调函数
void* subThreadRunning(void* arg)
{
    //接收数据
    struct WorkerThread* thread = (struct WorkerThread*)arg;
     //创建反应堆
    pthread_mutex_lock(&thread->mutex);
    thread->evloop = eventLoopInitEx(thread->tname);
    pthread_mutex_unlock(&thread->mutex);
    //唤醒主线程
    pthread_cond_signal(&thread->cond);
    //启动反应堆
    eventLoopRun(thread->evloop);
    return NULL;
}


// 启动线程   主线程调用
void workerThreadRun(struct WorkerThread* thread)
{
    //创建子线程
    pthread_create(&thread->tid,NULL,subThreadRunning,thread);
    //阻塞主线程  防止evloop没创建出来，这个函数就返回
    pthread_mutex_lock(&thread->mutex);
    while(thread->evloop == NULL)
    {
        pthread_cond_wait(&thread->cond,&thread->mutex);
    }
    pthread_mutex_unlock(&thread->mutex);
}