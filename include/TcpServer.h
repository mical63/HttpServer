#pragma once
#include"EventLoop.h"
#include"ThreadPool.h"
#include"TcpConnection.h"

//定义lfd结构体
struct listener
{
    int lfd;
    unsigned short port;
};

//初始化listener
struct listener* listenerInit(unsigned short port);

//定义结构体
struct TcpServer
{   
    //主反应堆
    struct EventLoop* mainloop;
    //线程池线程数量
    int threadNUm;
    //线程池
    struct ThreadPool* pool;
    //listener
    struct listener* listener;
};

// 初始化
struct TcpServer* tcpServerInit(unsigned short port, int threadNum);

// 启动服务器
void tcpServerRun(struct TcpServer* server);