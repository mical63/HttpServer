#pragma once
#include"EventLoop.h"
#include"channel.h"
#include"Buffer.h"
#include"HttpRequest.h"
#include"HttpResponse.h"
#include<stdlib.h>

//#define MSG_SEND_AUTO

struct TcpConnection
{
    //名字
    char name[32];
    //两个缓冲
    struct Buffer* readBuf;
    struct Buffer* writeBuf;
    //反应堆（子线程提供）
    struct EventLoop* evloop;
    //channel
    struct channel* chnl;
    //http
    struct HttpRequest* request;
    struct HttpResponse* response;
};

// 初始化
struct TcpConnection* tcpConnectionInit(int fd, struct EventLoop* evloop);

//释放资源
int tcpConnectionDestroy(void* arg);