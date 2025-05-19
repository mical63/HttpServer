#include"EventLoop.h"
#include<assert.h>
#include<stdio.h>
#include<unistd.h>
#include"Log.h"

//主线程 
struct EventLoop* eventLoopInit()
{
    return eventLoopInitEx(NULL);
}

//sv[0] 写数据
void taskWakeup(struct EventLoop* evLoop)
{
    write(evLoop->sv[0],"Wake up now!",strlen("Wake up now!"));
}

//sv[1]  读数据
int readLocalMessage(void* arg)
{
    struct EventLoop* evloop = (struct EventLoop*)arg;
    char buf[128];
    read(evloop->sv[1],buf,sizeof(buf));
    return 0;
}

//子线程
struct EventLoop* eventLoopInitEx(const char* threadName)
{
    struct EventLoop* evloop = (struct EventLoop*)malloc(sizeof(struct EventLoop));
    evloop->isQuit = false;
    evloop->dispatcher = &EpollDispatcher;
    //evloop->dispatcher = &PollDispatcher;
    //evloop->dispatcher = &SelectDispatcher;
    evloop->dispatcherData = evloop->dispatcher->init();
    evloop->head = evloop->tail = NULL;
    evloop->channelMap = channelMapInit(128);
    evloop->tid = pthread_self();
    strcpy(evloop->tname,threadName == NULL ? "Main" : threadName);
    pthread_mutex_init(&evloop->mutex,NULL);
    //初始化sv
    int ret = socketpair(AF_LOCAL,SOCK_STREAM,0,evloop->sv);
    if(ret == -1)
    {
        perror("socketpair error");
        exit(1);
    }
    //制定规则：sv[0] 发送数据  sv[1] 读数据   
    struct channel* chnl = channelInit(evloop->sv[1],readEvents,readLocalMessage,NULL,NULL,evloop);

    //printf("%d  %d\n",evloop->sv[0],evloop->sv[1]);
    //将sv[1]添加到队列
    eventLoopAddTask(evloop,chnl,ADD);
    return evloop;
}

// 启动反应堆模型
int eventLoopRun(struct EventLoop* evloop)
{
    assert(evloop != NULL);
    if(evloop->tid != pthread_self())
    {
        return -1;
    }
    //启动
    Debug("服务器启动了。。。");
    while(!evloop->isQuit)
    {
        evloop->dispatcher->dispatch(evloop,2);
        eventLoopProcessTask(evloop);
    }
    return 0;
}

// 处理被激活的文件fd
int eventActivate(struct EventLoop* evloop, int fd, int event)
{
    if(evloop == NULL || fd < 0)
    {
        return -1;
    }
    struct channel* chnl = evloop->channelMap->list[fd];
    assert(chnl->fd == fd);
    if(event & readEvents && chnl->read_cb)
    {
        chnl->read_cb(chnl->arg);
    }
    if(event & writeEvents && chnl->write_cb)
    {
        chnl->write_cb(chnl->arg);
    }
    return 0;
}

//向任务队列中添加任务
int eventLoopAddTask(struct EventLoop* evloop,struct channel* chnl,int type)
{
    //初始化一个任务队列节点
    struct ChannelElement* cement = (struct ChannelElement*)malloc(sizeof(struct ChannelElement));
    cement->chnl = chnl;
    cement->type = type;
    cement->next = NULL;

    //加锁
    pthread_mutex_lock(&evloop->mutex);
    
    //添加节点
    if(evloop->head == NULL)
    {
        evloop->head = evloop->tail = cement;
    }
    else
    {
        evloop->tail->next = cement;
        evloop->tail = cement;
    }

    //解锁
    pthread_mutex_unlock(&evloop->mutex);

    //处理节点      只能子线程处理节点
    if(pthread_self() == evloop->tid)     //子线程(基于子线程的角度分析)
    {
        eventLoopProcessTask(evloop);
    }
    else                                //主进程     添加节点后要唤醒子线程
    {
        taskWakeup(evloop);
    }
}

//处理任务
int eventLoopProcessTask(struct EventLoop* evloop)
{
    //加锁
    pthread_mutex_lock(&evloop->mutex);

    while(evloop->head != NULL)
    {
        struct channel* chnl = evloop->head->chnl;
        if(evloop->head->type == ADD)
        {
            eventLoopAdd(evloop,chnl);
        }
        if(evloop->head->type == DELETE)
        {
            eventLoopRemove(evloop,chnl);
        }
        if(evloop->head->type == MODIFY)
        {
            eventLoopModify(evloop,chnl);
        }
        struct ChannelElement* tmp = evloop->head;
        evloop->head = evloop->head->next;
        free(tmp);
    }
    evloop->head = evloop->tail = NULL;

    //解锁
    pthread_mutex_unlock(&evloop->mutex);
    return 0;
}

// 处理dispatcher中的节点
int eventLoopAdd(struct EventLoop* evloop, struct channel* chnl)
{
    int fd = chnl->fd;
    struct ChannelMap* map = evloop->channelMap;
    if(fd >= map->size)
    {
        if(!makeMapRoom(map,fd,sizeof(struct channel)))
        {
            return -1;
        }
    }
    int ret = -1;
    if(map->list[fd] == NULL)
    {
        map->list[fd] = chnl;
        ret = evloop->dispatcher->add(chnl,evloop);
    }
    return ret;
}

int eventLoopRemove(struct EventLoop* evloop, struct channel* chnl)
{
    int fd = chnl->fd;
    struct ChannelMap* map = evloop->channelMap;
    if(fd >= map->size)
    {
        return -1;
    }
    int ret = -1;
    if(map->list[fd] != NULL)
    {
        ret = evloop->dispatcher->remove(chnl,evloop);
    }
    return ret;
}

int eventLoopModify(struct EventLoop* evloop, struct channel* chnl)
{
    int fd = chnl->fd;
    struct ChannelMap* map = evloop->channelMap;
    if(fd >= map->size || map->list[fd] == NULL)
    {
        return -1;
    }
    int ret = -1;
    if(map->list[fd] != NULL)
    {
        map->list[fd]->events = chnl->events;
        ret = evloop->dispatcher->modify(chnl,evloop);
    }
    return ret;
}

// 释放channel
int destroyChannel(struct EventLoop* evloop, struct channel* chnl)
{
    evloop->channelMap->list[chnl->fd] = NULL;
    close(chnl->fd);
    free(chnl);
    return 0;
}