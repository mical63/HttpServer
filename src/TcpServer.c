#include"TcpServer.h"
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include"Log.h"

//初始化listener
struct listener* listenerInit(unsigned short port)
{
    struct listener* listener = (struct listener*)malloc(sizeof(struct listener));
    //初始化lfd
    int lfd = socket(AF_INET,SOCK_STREAM,0);

    //printf("lfd = %d\n",lfd);

    if(lfd == -1)
    {
        perror("socket");
        exit(1);
    }
    //设置端口服用
    int opt = 1;
    int ret = setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    if(ret == -1)
    {
        perror("setsockopt");
        exit(1);
    }
    //绑定地址结构
    struct sockaddr_in ser_addr;
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(port);
    ser_addr.sin_addr.s_addr = INADDR_ANY;
    ret = bind(lfd,(struct sockaddr*)&ser_addr,sizeof(ser_addr));
    if(ret == -1)
    {
        perror("bind");
        exit(1);
    }
    //设置监听上限
    ret = listen(lfd,128);
    if(ret == -1)
    {
        perror("ret");
        exit(1);
    }

    listener->lfd = lfd;
    listener->port = port;
    return listener;
}

// 初始化
struct TcpServer* tcpServerInit(unsigned short port, int threadNum)
{
    struct TcpServer* tcp = (struct TcpServer*)malloc(sizeof(struct TcpServer));
    tcp->mainloop = eventLoopInit();
    tcp->threadNUm = threadNum;
    tcp->pool = threadPoolInit(tcp->mainloop,threadNum);
    tcp->listener = listenerInit(port);

    return tcp;
}

int acceptConnection(void* arg)
{
    //接收数据
    struct TcpServer* server = (struct TcpServer*)arg;
    //建立连接
    int cfd = accept(server->listener->lfd,NULL,NULL);
    if(cfd == -1)
    {
        perror("accept");
        exit(1);
    }
    // 从线程池中取出一个子线程的反应堆实例, 去处理这个cfd
    struct EventLoop* evloop = takeWorkerEventLoop(server->pool);
    // 将cfd放到 TcpConnection中处理
    tcpConnectionInit(cfd, evloop);
    return 0;
}

// 启动服务器
void tcpServerRun(struct TcpServer* server)
{
    //启动线程池
    threadPoolRun(server->pool);
    //添加lfd
    printf("11111\n");
    struct channel* chnl = channelInit(server->listener->lfd,readEvents,acceptConnection,NULL,NULL,server);
    eventLoopAddTask(server->mainloop,chnl,ADD);
    //启动反应堆模型
    eventLoopRun(server->mainloop);
}