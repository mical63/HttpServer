#include"HttpResponse.h"
#include<stdlib.h>

#define _GNU_SOURCE  // 必须在包含头文件之前定义
#include <string.h>
#include"Log.h"

#define ResHeaderSize 16

// 初始化
struct HttpResponse* httpResponseInit()
{
    struct HttpResponse* response = (struct HttpResponse*)malloc(sizeof(struct HttpResponse));

    response->statuscode = Unkown;
    bzero(response->statusMsg,sizeof(response->statusMsg));

    bzero(response->filename,sizeof(response->filename));
    
    response->sendDataFunc = NULL;

    response->headerNum = 0;
    int size = sizeof(struct ResponseHeader) * ResHeaderSize;
    response->headers = (struct ResponseHeader*)malloc(size);
    bzero(response->headers,size);

    return response;
}

// 销毁
void httpResponseDestroy(struct HttpResponse* response)
{
    if(response != NULL)
    {
        free(response->headers);
        free(response);
    }
}

// 添加响应头
void httpResponseAddHeader(struct HttpResponse* response, const char* key, const char* value)
{
    if(response == NULL || key == NULL || value == NULL)
    {
        return;
    }
    strcpy(response->headers[response->headerNum].key,key);
    strcpy(response->headers[response->headerNum].value,value);
    response->headerNum++;
}

// 组织http响应数据
void httpResponsePrepareMsg(struct HttpResponse* response, struct Buffer* sendBuf, int sockfd)
{
    char tmp[1024] = {0};
    //状态码
    sprintf(tmp,"HTTP/1.1 %d %s\r\n",response->statuscode,response->statusMsg);
    bufferAppendString(sendBuf,tmp); 
    //响应头
    for(int i = 0;i < response->headerNum;i++)
    {
        sprintf(tmp,"%s: %s\r\n",response->headers[i].key,response->headers[i].value);
        bufferAppendString(sendBuf,tmp); 
        response->headerNum--;
    }
    //空行
    bufferAppendString(sendBuf,"\r\n"); 

    Debug("回应的HTTP消息: %s",sendBuf->data + sendBuf->readPos);

#ifndef MSG_SEND_AUTO
    //发送数据
    bufferSendData(sendBuf,sockfd);
#endif

    //回复的数据
    response->sendDataFunc(response->filename,sendBuf,sockfd);
}
