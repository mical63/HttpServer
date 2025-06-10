#define _GNU_SOURCE
#include"Buffer.h"
#include<stdio.h>
#include<sys/uio.h>
#include <string.h>
#include<strings.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<errno.h>

// 初始化
struct Buffer* bufferInit(int size)
{
    struct Buffer* buf = (struct Buffer*)malloc(sizeof(struct Buffer));
    buf->capacity = size;
    buf->readPos = buf->writePos = 0;
    buf->data = (char*)malloc(size);
    memset(buf->data,0,size);

    return buf;
}

//释放
void bufferDestroy(struct Buffer* buf)
{
    if(buf != NULL)
    {
        if(buf->data != NULL)
        {
            free(buf->data);
        }
        free(buf);
    }
}


// 扩容
void bufferExtendRoom(struct Buffer* buf, int size)
{
    //剩余可写容量足够，无需扩容  可写 > size
    if(bufferWriteableSize(buf) >= size)
    {
        return;
    }
    //容量合并后足够，无需扩容  可写 + 已读 > size
    else if(buf->readPos + bufferWriteableSize(buf) >= size)
    {
        //获取可读，即移动缓冲区的大小
        int readable = bufferReadableSize(buf);
        //移动内存
        memcpy(buf->data,buf->data + buf->readPos,readable);
        //更新位置
        buf->readPos = 0;
        buf->writePos = readable;
    }
    //都不行，需要扩容
    else
    {
        //扩容
        void* temp = realloc(buf->data,buf->capacity + size);
        memset(temp + buf->capacity,0,size);
        //更新位置
        buf->data = temp;
        buf->capacity += size;
    }
}

// 得到剩余的可写的内存容量
int bufferWriteableSize(struct Buffer* buf)
{
    return buf->capacity - buf->writePos;
}

// 得到剩余的可读的内存容量
int bufferReadableSize(struct Buffer* buf)
{
    return buf->writePos - buf->readPos;
}

// 写内存 
//1. 直接写 
int bufferAppendData(struct Buffer* buf, const char* data, int size)
{
    if(buf == NULL || data == NULL || size <= 0)
    {
        return -1;
    }
    //调用扩容函数（不一定扩）
    bufferExtendRoom(buf,size);
    //写入数据
    memcpy(buf->data + buf->writePos,data,size);
    //更新位置
    buf->writePos += size;

    return 0;
}
int bufferAppendString(struct Buffer* buf, const char* data)  //我们自己算size
{
    int size = strlen(data);  //strlen 找的是字符串结尾处的'\0',但是有些字符串的中间位置就有'\0',这是这个函数的弊端
    int ret = bufferAppendData(buf,data,size);
    return ret;
}

//2. 接收套接字数据
int bufferSocketRead(struct Buffer* buf, int fd)
{
    //使用readv   这个函数可以把数据读到多个缓冲区，第一个缓冲区满了，就读第二个
    struct iovec iov[2];
    //初始化数组
    int writeable = bufferWriteableSize(buf);
    iov[0].iov_base = buf->data + buf->writePos;
    iov[0].iov_len = writeable;
    char* temp = (char*)malloc(40960);
    iov[1].iov_base = temp;
    iov[1].iov_len = 40960;
    //调用readv
    int ret = readv(fd,iov,2);  //返回读到的字节数
    if(ret == -1)
    {
        perror("readv");
        return -1;
    }
    else if(ret <= writeable)
    {
        buf->writePos += ret;
    }
    else
    {   
        buf->writePos = buf->capacity;
        bufferAppendData(buf,temp,ret - writeable);
    }   
    free(temp);
    return ret;
}


char* bufferFindCRLF(struct Buffer* buf)
{
    // strstr --> 大字符串中匹配子字符串(遇到\0结束) char *strstr(const char *haystack, const char *needle);
    // memmem --> 大数据块中匹配子数据块(需要指定数据块大小)
    // void *memmem(const void *haystack, size_t haystacklen,
    //      const void* needle, size_t needlelen);
    char*ptr = memmem(buf->data + buf->readPos,bufferReadableSize(buf),"\r\n",2);
    return ptr;
}

//发送数据
int bufferSendData(struct Buffer* sendbuf, int socket)
{
    //检测有无可发数据
    int readable = bufferReadableSize(sendbuf);
    //发送数据
    if(readable > 0)
    {
        int count = send(socket,sendbuf->data + sendbuf->readPos,readable,MSG_NOSIGNAL);
        if(count > 0)
        {
            sendbuf->readPos += count;
            usleep(1);
        }
        else if(count == -1)
        {
            if(errno == EAGAIN)
            {
                return 0;
            }
            perror("send");
            return -1;
        }
        return count;
    }
    return 0;
}
