#include"Dispatcher.h"
#include"channel.h"
#include<sys/select.h>
#include<stdlib.h>
#include<stdio.h>

#define MAX 1024

struct SelectData
{
    fd_set rdSet;
    fd_set wrSet;
};

// 六个函数的声明     static的作用是使这些函数的作用域局限于源文件内部，函数不能被其他文件通过外部链接来调用，若其他文件要使用，要加extren关键字
// init
static void *SelectInit();
// 添加
static int SelectAdd(struct channel *chnl, struct EventLoop *evloop);
// 删除
static int SelectRemove(struct channel *chnl, struct EventLoop *evloop);
// 修改
static int SelectModify(struct channel *chnl, struct EventLoop *evloop);
// 事件监测
static int SelectDispatch(struct EventLoop *evloop, int timeout); // 单位：s
// 清除数据
static int SelectClear(struct EventLoop *evloop);

static void setFdSet(struct channel* chnl, struct SelectData* data);
static void clearFdSet(struct channel* chnl, struct SelectData* data);


// 将函数保存到结构体中，方便调用（extern）
struct Dispatcher SelectDispatcher = {
    SelectInit,
    SelectAdd,
    SelectRemove,
    SelectModify,
    SelectDispatch,
    SelectClear};

// init
static void* SelectInit()
{   
    struct SelectData* data = (struct SelectData*)malloc(sizeof(struct SelectData));
    FD_ZERO(&data->rdSet);
    FD_ZERO(&data->wrSet);
    return data;
}

static void setFdSet(struct channel* chnl, struct SelectData* data)
{
    if(chnl->events & readEvents)
    {
        FD_SET(chnl->fd,&data->rdSet);
    }
    if(chnl->events & writeEvents)
    {
        FD_SET(chnl->fd,&data->wrSet);
    }
}

static void clearFdSet(struct channel* chnl, struct SelectData* data)
{
    if(chnl->events & readEvents)
    {
        FD_CLR(chnl->fd,&data->rdSet);
    }
    if(chnl->events & writeEvents)
    {
        FD_CLR(chnl->fd,&data->wrSet);
    }
}

// 添加
static int SelectAdd(struct channel *chnl, struct EventLoop *evloop)
{
    struct SelectData* data = (struct SelectData*)evloop->dispatcherData;
    if(chnl->fd >= MAX)
    {
        return -1;
    }
    setFdSet(chnl,data);
    return 0;
}

// 删除
static int SelectRemove(struct channel *chnl, struct EventLoop *evloop)
{
    struct SelectData* data = (struct SelectData*)evloop->dispatcherData;
    if(chnl->fd >= MAX)
    {
        return -1;
    }
    clearFdSet(chnl,data);
    //通过channel释放资源
    chnl->destroy_cb(chnl->arg);
    return 0;
}

// 修改
static int SelectModify(struct channel *chnl, struct EventLoop *evloop)
{
    struct SelectData* data = (struct SelectData*)evloop->dispatcherData;
    if(chnl->fd >= MAX)
    {
        return -1;
    }
    //清除原事件，无论读写
    FD_CLR(chnl->fd,&data->rdSet);
    FD_CLR(chnl->fd,&data->wrSet);
    //添加新事件
    setFdSet(chnl,data);
    return 0;
}

// 事件监测
static int SelectDispatch(struct EventLoop *evloop, int timeout) //  单位：s
{
    struct SelectData* data = (struct SelectData*)evloop->dispatcherData;
    struct timeval time;
    time.tv_sec = timeout;
    time.tv_usec = 0;
    fd_set rdtmp = data->rdSet;
    fd_set wrtmp = data->wrSet;
    int num = select(1024,&rdtmp,&wrtmp,NULL,&time);
    if(num == -1)
    {
        perror("select error\n");
        exit(1);
    }
    int i = 3;
    for(;i < MAX;i++)
    {
        if(FD_ISSET(i,&rdtmp))
        {
            eventActivate(evloop,i,readEvents);
        }
        if(FD_ISSET(i,&wrtmp))
        {
            eventActivate(evloop,i,writeEvents);
        }
    }
    return 0;
}

// 清除数据
static int SelectClear(struct EventLoop *evloop)
{
    struct SelectData* data = (struct SelectData*)evloop->dispatcherData;
    free(data);
    return 0;
}
