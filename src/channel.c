#include "channel.h"
#include<string.h>
#include<stdlib.h>

//初始化
struct channel* channelInit(int fd,int events,handleFunc read_cb,handleFunc write_cb,handleFunc destroy_cb,void* arg)
{
    struct channel* chnl = (struct channel*)malloc(sizeof(struct channel));
    chnl->fd = fd;
    chnl->events = events;
    chnl->read_cb = read_cb;    
    chnl->write_cb = write_cb;
    chnl->destroy_cb = destroy_cb;
    chnl->arg = arg;
}

// 修改fd的写事件(检测 or 不检测)
void writeEventEnable(struct channel* chnl,bool flag)
{
    if(flag == true)
    {
        chnl->events |= writeEvents;
    }
    else
    {
        chnl->events &= ~writeEvents;
    }
}

// 判断是否需要检测文件描述符的写事件
bool isWriteEventEnable(struct channel* chnl)
{
    return chnl->events & writeEvents;
}
