#include "Dispatcher.h"
#include<sys/epoll.h>
#include<stdlib.h>
#include<errno.h>
#include<stdio.h>
#include<unistd.h>

#define MAX 520

struct EpollData
{
    int epfd;
    struct epoll_event* evs;    
};

// 六个函数的声明     static的作用是使这些函数的作用域局限于源文件内部，函数不能被其他文件通过外部链接来调用，若其他文件要使用，要加extren关键字
// init
static void *EpollInit();
// 添加
static int EpollAdd(struct channel *chnl, struct EventLoop *evloop);
// 删除
static int EpollRemove(struct channel *chnl, struct EventLoop *evloop);
// 修改
static int EpollModify(struct channel *chnl, struct EventLoop *evloop);
// 事件监测
static int EpollDispatch(struct EventLoop *evloop, int timeout); // 单位：s
// 清除数据
static int EpollClear(struct EventLoop *evloop);

//添加  删除  修改  代码复用函数
static int EpollCtl(struct channel *chnl, struct EventLoop *evloop,int op);

// 将函数保存到结构体中，方便调用（extern）
struct Dispatcher EpollDispatcher = {
    EpollInit,
    EpollAdd,
    EpollRemove,
    EpollModify,
    EpollDispatch,
    EpollClear};

// init
static void* EpollInit()
{   
    struct EpollData* data = (struct EpollData*)malloc(sizeof(struct EpollData));
    //创建监听红黑树
    data->epfd = epoll_create(1);

    //printf("epfd = %d\n",data->epfd);

    if(data->epfd == -1)
    {
        perror("epoll_creata error");
        exit(1);
    }
    //为传出数组申请内存
    data->evs = (struct epoll_event*)calloc(MAX,sizeof(struct epoll_event));
    return data;
}

//添加  删除  修改  代码复用函数
static int EpollCtl(struct channel *chnl, struct EventLoop *evloop,int op)
{
    //接收红黑树
    struct EpollData* data = (struct EpollData*)evloop->dispatcherData;

    //printf("epfd = %d\n",data->epfd);

    //节点操作
    struct epoll_event ev;
    ev.data.fd = chnl->fd;
    int events = 0;
    if(chnl->events & readEvents)
    {
        events |= EPOLLIN;
    }
    if(chnl->events & writeEvents)
    {
        events |= EPOLLOUT;
    }
    ev.events = events;

    //printf("%d\n",ev.data.fd);

    int ret = epoll_ctl(data->epfd,op,chnl->fd,&ev);
    return ret;
}

// 添加
static int EpollAdd(struct channel *chnl, struct EventLoop *evloop)
{
    int ret = EpollCtl(chnl,evloop,EPOLL_CTL_ADD);
    if(ret == -1)
    {
        perror("epoll add error\n");
        exit(1);
    }
    return ret;
}

// 删除
static int EpollRemove(struct channel *chnl, struct EventLoop *evloop)
{
    int ret = EpollCtl(chnl,evloop,EPOLL_CTL_DEL);
    if(ret == -1)
    {
        perror("epoll del error\n");
        exit(1);
    }
    //通过channel释放资源
    chnl->destroy_cb(chnl->arg);
    return ret;
}

// 修改
static int EpollModify(struct channel *chnl, struct EventLoop *evloop)
{
    int ret = EpollCtl(chnl,evloop,EPOLL_CTL_MOD);
    if(ret == -1)
    {
        perror("epoll mod error\n");
        exit(1);
    }
    return ret;
}

// 事件监测
static int EpollDispatch(struct EventLoop *evloop, int timeout) //  单位：s
{
    //接收红黑树
    struct EpollData* data = (struct EpollData*)evloop->dispatcherData;
    //循环监听
    int num = epoll_wait(data->epfd,data->evs,MAX,timeout * 1000);
    for(int i = 0;i < num;i++)
    {
        int events = data->evs[i].events;
        int fd = data->evs[i].data.fd;
        if(events & EPOLLERR || events & EPOLLHUP)
        {
            //对端关闭了连接
            //EpollRemove();
            continue;
        }
        if(events & EPOLLIN)
        {
            eventActivate(evloop,fd,readEvents);
        }
        if(events & EPOLLOUT)
        {
            eventActivate(evloop,fd,writeEvents);
        }
    }
    return 0;
}

// 清除数据
static int EpollClear(struct EventLoop *evloop)
{
    //接收红黑树
    struct EpollData* data = (struct EpollData*)evloop->dispatcherData;

    free(data->evs);
    close(data->epfd);
    free(data);
    return 0;
}
