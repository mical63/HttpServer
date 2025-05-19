#pragma once


//定义缓冲区结构体
struct Buffer
{
    //指向缓冲区地址的指针
    char* data;
    //缓冲区的容量
    int capacity;
    //读位置
    int readPos;
    //写位置
    int writePos;
};

// 初始化
struct Buffer* bufferInit(int size);

//释放
void bufferDestroy(struct Buffer* buf);

// 扩容
void bufferExtendRoom(struct Buffer* buf, int size);

// 得到剩余的可写的内存容量
int bufferWriteableSize(struct Buffer* buf);

// 得到剩余的可读的内存容量
int bufferReadableSize(struct Buffer* buf);

// 写内存 
//1. 直接写 
int bufferAppendData(struct Buffer* buf, const char* data, int size);
int bufferAppendString(struct Buffer* buf, const char* data);

//2. 接收套接字数据
int bufferSocketRead(struct Buffer* buf, int fd);

// 根据\r\n取出一行, 找到其在数据块中的位置, 返回该位置
char* bufferFindCRLF(struct Buffer* buf);

//发送数据
int bufferSendData(struct Buffer* sendbuf, int socket);



