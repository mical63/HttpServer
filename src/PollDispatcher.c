#include "Dispatcher.h"
#include "channel.h"
#include <poll.h>
#include<stdlib.h>
#include<stdio.h>

#define MAX 1024

struct PollData
{
    int maxfd;
    struct pollfd fds[MAX];
};

// 六个函数的声明     static的作用是使这些函数的作用域局限于源文件内部，函数不能被其他文件通过外部链接来调用，若其他文件要使用，要加extren关键字
// init
static void *pollInit();
// 添加
static int pollAdd(struct channel *chnl, struct EventLoop *evloop);
// 删除
static int pollRemove(struct channel *chnl, struct EventLoop *evloop);
// 修改
static int pollModify(struct channel *chnl, struct EventLoop *evloop);
// 事件监测
static int pollDispatch(struct EventLoop *evloop, int timeout); // 单位：s
// 清除数据
static int pollClear(struct EventLoop *evloop);

// 将函数保存到结构体中，方便调用（extern）
struct Dispatcher PollDispatcher = {
    pollInit,
    pollAdd,
    pollRemove,
    pollModify,
    pollDispatch,
    pollClear};

// init
static void *pollInit()
{
    struct PollData *data = (struct PollData *)malloc(sizeof(struct PollData));
    data->maxfd = 0;
    for (int i = 0; i < MAX; i++)
    {
        data->fds[i].fd = -1;
        data->fds[i].events = 0;
        data->fds[i].revents = 0;
    }
    return data;
}

// 添加
static int pollAdd(struct channel *chnl, struct EventLoop *evloop)
{
    struct PollData *data = (struct PollData *)evloop->dispatcherData;
    int i = 0;
    for (; i < MAX; i++)
    {
        if (data->fds[i].fd == -1)
        {
            data->fds[i].fd = chnl->fd;
            if (chnl->events & readEvents)
            {
                data->fds[i].events |= POLLIN;
            }
            if (chnl->events & writeEvents)
            {
                data->fds[i].events |= POLLOUT;
            }
            data->maxfd = i > data->maxfd ? i : data->maxfd;
            break;
        }
    }
    if (i >= MAX)
    {
        return -1;
    }
    return 0;
}

// 删除
static int pollRemove(struct channel *chnl, struct EventLoop *evloop)
{
    struct PollData *data = (struct PollData *)evloop->dispatcherData;
    int i = 0;
    for (; i < MAX; i++)
    {
        if (data->fds[i].fd == chnl->fd)
        {
            data->fds[i].fd = -1;
            data->fds[i].events = 0;
            data->fds[i].revents = 0;
            break;
        }
    }
    // 通过channel释放资源
    chnl->destroy_cb(chnl->arg);
    if (i >= MAX)
    {
        return -1;
    }
    return 0;
}

// 修改
static int pollModify(struct channel *chnl, struct EventLoop *evloop)
{
    struct PollData *data = (struct PollData *)evloop->dispatcherData;
    int events = 0;
    if (chnl->events & readEvents)
    {
        events |= POLLIN;
    }
    if (chnl->events & writeEvents)
    {
        events |= POLLOUT;
    }
    int i = 0;
    for (; i < MAX; i++)
    {
        if (data->fds[i].fd == chnl->fd)
        {
            data->fds[i].events = events;
            break;
        }
    }
    if (i >= MAX)
    {
        return -1;
    }
    return 0;
}

// 事件监测
static int pollDispatch(struct EventLoop *evloop, int timeout) //  单位：s
{
    struct PollData *data = (struct PollData *)evloop->dispatcherData;

    int num = poll(data->fds, data->maxfd + 1, timeout * 1000);
    if (num == -1)
    {
        perror("poll error\n");
        exit(1);
    }
    for (int i = 0; i <= data->maxfd; i++)
    {
        if (data->fds[i].fd == -1)
        {
            continue;
        }
        if (data->fds[i].revents & POLLIN)
        {
            eventActivate(evloop, data->fds[i].fd, readEvents);
        }
        if (data->fds[i].revents & POLLOUT)
        {
            eventActivate(evloop, data->fds[i].fd, writeEvents);
        }
    }
    return 0;
}

// 清除数据
static int pollClear(struct EventLoop *evloop)
{
    struct PollData *data = (struct PollData *)evloop->dispatcherData;
    free(data);
    return 0;
}
