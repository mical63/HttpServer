#pragma once
#include"Buffer.h"
#include<stdio.h>
#include<string.h>
#include<strings.h>
#include<stdlib.h>

//状态码
enum ResponseStatusCode
{
    Unkown,
    OK = 200,
    MovedPermanently = 301,
    MovedTemporarily = 302,
    BadRequest = 400,
    NotFound = 404
};

//消息头结构体
struct ResponseHeader
{
    char key[32];
    char value[128];
};

//定义一个函数指针 文件 or 目录
typedef void (*responseBody)(const char* filename,struct Buffer* sendbuf,int sockfd);

//回应消息 结构体
struct HttpResponse
{
    //状态码
    enum ResponseStatusCode statuscode;
    //状态描述
    char statusMsg[128];
    //文件名
    char filename[128];
    //消息头 结构体数组
    struct ResponseHeader* headers;
    //数组有效个数
    int headerNum;
    //函数指针
    responseBody sendDataFunc;
};


// 初始化
struct HttpResponse* httpResponseInit();
// 销毁
void httpResponseDestroy(struct HttpResponse* response);
// 添加响应头
void httpResponseAddHeader(struct HttpResponse* response, const char* key, const char* value);
// 组织http响应数据
void httpResponsePrepareMsg(struct HttpResponse* response, struct Buffer* sendBuf, int sockfd);