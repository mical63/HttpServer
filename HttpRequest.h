#pragma once
#include<stdbool.h>
#include"HttpResponse.h"
#include<ctype.h>

//请求头
struct RequestHeader
{
    char* key;
    char* value;
};

//状态
enum RequestState
{
    ParseReqLine,
    ParseReqHeaders,
    ParseReqBody,
    ParseReqDone
};

//请求 结构体
struct HttpRequest
{
    //方法
    char* method;
    //资源
    char* url;
    //协议
    char* version;
    //请求头 结构体数组
    struct RequestHeader* reqHeaders;
    //数组有效个数
    int reqHeadersNum;
    //当前状态
    enum RequestState curState;
};

//初始化
struct HttpRequest* httpRequestInit();
//重置
void httpRequestReset(struct HttpRequest* req);
void httpRequestResetEx(struct HttpRequest* req);
void httpRequestDestroy(struct HttpRequest* req);
// 获取处理状态
enum RequestState httpRequestState(struct HttpRequest* req);
// 添加请求头
void httpRequestAddHeader(struct HttpRequest* req, const char* key, const char* value);
// 根据key得到请求头的value
char* httpRequestGetHeader(struct HttpRequest* req, const char* key);
// 解析请求头
bool parseHttpRequestHeader(struct HttpRequest* req, struct Buffer* readBuf);
//解析完整的请求
bool parseHttpRequest(struct HttpRequest *req, struct Buffer *readbuf,struct HttpResponse* response,struct Buffer* sendbuf,int sockfd);
// 处理http请求协议
bool processHttpRequest(struct HttpRequest* req, struct HttpResponse* response);


//发送文件
void sendFile(const char* filename,struct Buffer* sendbuf,int sockfd);
//发送目录
void sendDir(const char* dirname,struct Buffer* sendbuf,int sockfd);

// 将字符转换为整形数
int hexToDec(char c);
// 解码
// to 存储解码之后的数据, 传出参数, from被解码的数据, 传入参数
void decodeMsg(char* to, char* from);
//获取文件类型
const char* getFileType(const char* name);