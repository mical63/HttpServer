#include"ThreadPool.h"
#include<assert.h>

// 初始化线程池
struct ThreadPool* threadPoolInit(struct EventLoop* mainevLoop, int count)
{
    struct ThreadPool* threadpool = (struct ThreadPool*)malloc(sizeof(struct ThreadPool));

    threadpool->isStart = false;

    threadpool->threadNum = count;

    threadpool->index = 0;

    threadpool->workerthreads = (struct WorkerThread*)malloc(count * sizeof(struct WorkerThread));

    threadpool->mainevloop = mainevLoop;

    return threadpool;
}

// 启动线程池
void threadPoolRun(struct ThreadPool* pool)
{
    assert(pool && !pool->isStart);
    if(pthread_self() != pool->mainevloop->tid)  //只能主线程启动
    {
        exit(1);
    }
    pool->isStart = true;
    if(pool->threadNum)
    {
        for(int i = 0;i < pool->threadNum;i++)
        {
            workerThreadInit(&pool->workerthreads[i],i);
            workerThreadRun(&pool->workerthreads[i]);
        }
    }
}

// 取出线程池中的某个子线程的反应堆实例
struct EventLoop* takeWorkerEventLoop(struct ThreadPool* pool)
{
    assert(pool->isStart);
    if(pthread_self() != pool->mainevloop->tid)  //只能主线程调用
    {
        exit(1);
    }
    //取出某一个线程的反应堆实例
    struct EventLoop* evloop = pool->mainevloop;
    if(pool->threadNum > 0)
    {
        evloop = pool->workerthreads[pool->index].evloop;
        pool->index = ++pool->index % pool->threadNum;
    }
    return evloop;
}