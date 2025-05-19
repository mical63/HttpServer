#include "TcpConnection.h"
#include"Log.h"

int processRead(void *arg)
{
    // 接收数据
    struct TcpConnection *conn = (struct TcpConnection *)arg;
    // 读数据
    int ret = bufferSocketRead(conn->readBuf, conn->chnl->fd);
    
    Debug("接收到的http请求数据: %s", conn->readBuf->data + conn->readBuf->readPos);

    if (ret > 0)
    {
#ifdef MSG_SEND_AUTO
        // 检测读写事件
        writeEventEnable(conn->chnl, true);
        eventLoopAddTask(conn->evloop, conn->chnl, MODIFY);
#endif
        // 解析HTTP协议
        bool flag = parseHttpRequest(conn->request, conn->readBuf, conn->response, conn->writeBuf, conn->chnl->fd);
        if (flag == false)
        {
            // 解析失败
            char *tmp = "HTTP/1.1 400 Bad Request\r\n\r\n";
            bufferAppendString(conn->writeBuf, tmp);
        }
    }
    else
    {
#ifdef MSG_SEND_AUTO
    // 断开连接
    eventLoopAddTask(conn->evloop, conn->chnl, DELETE);
#endif
#ifndef MSG_SEND_AUTO
    // 断开连接
    eventLoopAddTask(conn->evloop, conn->chnl, DELETE);
#endif
    }
    return 0;
}

int processWrite(void *arg)
{
    // 接收数据
    struct TcpConnection *conn = (struct TcpConnection *)arg;
    // 发送数据
    int count = bufferSendData(conn->writeBuf, conn->chnl->fd);
    if (count > 0)
    {
        if (bufferReadableSize(conn->writeBuf) == 0)
        {
            // 检测写事件
            writeEventEnable(conn->chnl, false);
            eventLoopAddTask(conn->evloop, conn->chnl, MODIFY);
            // 可断开连接
            eventLoopAddTask(conn->evloop, conn->chnl, DELETE);
        }
    }
}

// 初始化
struct TcpConnection *tcpConnectionInit(int fd, struct EventLoop *evloop)
{
    struct TcpConnection *conn = (struct TcpConnection *)malloc(sizeof(struct TcpConnection));
    sprintf(conn->name, "Connection-%d", fd);
    conn->readBuf = bufferInit(10240);
    conn->writeBuf = bufferInit(10240);
    conn->evloop = evloop;
    conn->chnl = channelInit(fd, readEvents, processRead, processWrite, tcpConnectionDestroy, conn);
    eventLoopAddTask(conn->evloop, conn->chnl, ADD);

    conn->request = httpRequestInit();
    conn->response = httpResponseInit();

    Debug("和客户端建立连接, threadName: %s, threadID:%ld, connName: %s",evloop->tname, evloop->tid, conn->name);

    return conn;
}

// 释放资源
int tcpConnectionDestroy(void* arg)
{
    // 接收数据
    struct TcpConnection *conn = (struct TcpConnection *)arg;
    if (conn != NULL)
    {
        if (conn->readBuf && bufferReadableSize(conn->readBuf) == 0 && conn->writeBuf && bufferWriteableSize(conn->writeBuf) == 0)
        {
            destroyChannel(conn->evloop, conn->chnl);
            bufferDestroy(conn->readBuf);
            bufferDestroy(conn->writeBuf);
            httpRequestDestroy(conn->request);
            httpResponseDestroy(conn->response);
            free(conn);
        }
    }
    Debug("连接断开, 释放资源, gameover, connName: %s", conn->name);
    return 0;
}