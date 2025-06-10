#define _GNU_SOURCE  // 必须在包含头文件之前定义，必须在所有头文件之前写这个宏
#include "HttpRequest.h"
#include <stdio.h>
#include "Buffer.h"
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <dirent.h>
#include <fcntl.h>
#include<unistd.h>
#include"Log.h"

#define Headersize 12

// 初始化
struct HttpRequest *httpRequestInit()
{
    struct HttpRequest *req = (struct HttpRequest *)malloc(sizeof(struct HttpRequest));
    httpRequestReset(req);
    req->reqHeaders = (struct RequestHeader *)malloc(sizeof(struct RequestHeader) * Headersize);
    return req;
}

// 重置
void httpRequestReset(struct HttpRequest *req)
{
    req->method = NULL;
    req->url = NULL;
    req->version = NULL;
    req->reqHeadersNum = 0;
    req->curState = ParseReqLine;
}

void httpRequestResetEx(struct HttpRequest *req)
{
    free(req->method);
    free(req->url);
    free(req->version);
    if (req->reqHeaders != NULL)
    {
        for (int i = 0; i < req->reqHeadersNum; i++)
        {
            free(req->reqHeaders[i].key);
            free(req->reqHeaders[i].value);
        }
        free(req->reqHeaders);
    }
    httpRequestReset(req);
}

void httpRequestDestroy(struct HttpRequest *req)
{
    if (req != NULL)
    {
        httpRequestResetEx(req);
        free(req);
    }
}

// 获取处理状态
enum RequestState httpRequestState(struct HttpRequest *req)
{
    return req->curState;
}

// 添加请求头
void httpRequestAddHeader(struct HttpRequest *req, const char *key, const char *value)
{
    req->reqHeaders[req->reqHeadersNum].key = (char*)key;
    req->reqHeaders[req->reqHeadersNum].value = (char*)value;
    req->reqHeadersNum++;
}

// 根据key得到请求头的value
char *httpRequestGetHeader(struct HttpRequest *req, const char *key)
{
    if (req->reqHeaders != NULL)
    {
        for (int i = 0; i < req->reqHeadersNum; i++)
        {
            if (strncasecmp(req->reqHeaders[i].key, key, strlen(key)) == 0)
            {
                return req->reqHeaders->value;
            }
        }
    }
    return NULL;
}

char *splitRequestLine(const char *start, const char *end, const char *sub, char **ptr)
{
    char *space = (char*)end;
    if (sub != NULL)
    {
        space = memmem(start, end - start, sub, strlen(sub));
        assert(space != NULL);
    }
    int len = space - start;
    char *temp = (char *)malloc(len + 1);
    strncpy(temp, start, len);
    temp[len] = '\0';
    *ptr = temp;
    return space + 1;
}

// 解析请求行
bool parseHttpRequestLine(struct HttpRequest *request, struct Buffer *readBuf)
{
    char *start = readBuf->data + readBuf->readPos;
    char *end = bufferFindCRLF(readBuf);
    int linesize = end - start;

    if (linesize > 0)
    {
        start = splitRequestLine(start, end, " ", &request->method);
        start = splitRequestLine(start, end, " ", &request->url);
        splitRequestLine(start, end, NULL, &request->version);

        // 更新
        readBuf->readPos += linesize;
        readBuf->readPos += 2;

        request->curState = ParseReqHeaders;
        return true;
    }
    return false;
}

// 解析请求头中的一行
bool parseHttpRequestHeader(struct HttpRequest *req, struct Buffer *readBuf)
{
    char *end = bufferFindCRLF(readBuf);
    if (end != NULL)
    {
        char *start = readBuf->data + readBuf->readPos;
        int linesize = end - start;
        // 找": "
        char *middle = memmem(start, linesize, ": ", 2);
        if (middle != NULL)
        {
            char *key = (char *)malloc(middle - start + 1);
            strncpy(key, start, middle - start);
            key[middle - start] = '\0';

            char *value = (char *)malloc(end - middle - 2 + 1);
            strncpy(value, middle + 2, end - middle - 1);
            value[end - middle - 2] = '\0';

            httpRequestAddHeader(req, key, value);

            readBuf->readPos += linesize;
            readBuf->readPos += 2;
        }
        else // 读到空行
        {
            readBuf->readPos += 2;

            req->curState = ParseReqDone;
        }
        return true;
    }
    return false;
}

// 解析完整的请求
bool parseHttpRequest(struct HttpRequest *req, struct Buffer *readbuf, struct HttpResponse *response, struct Buffer *sendbuf, int sockfd)
{
    bool flag = true;
    while (req->curState != ParseReqDone)
    {
        switch (req->curState)
        {
        case ParseReqLine:
            flag = parseHttpRequestLine(req, readbuf);
            break;
        case ParseReqHeaders:
            flag = parseHttpRequestHeader(req, readbuf);
            break;
        case ParseReqBody:
            break;
        default:
            break;
        }
        if (flag == false)
        {
            return false;
        }
        if (req->curState == ParseReqDone)
        {
            // 1. 根据解析出的原始数据, 对客户端的请求做出处理
            processHttpRequest(req, response);
            // 2. 组织响应数据并发送给客户端
            httpResponsePrepareMsg(response, sendbuf, sockfd);
        }
    }
    req->curState = ParseReqLine;
    return flag;
}

// 处理http请求协议
bool processHttpRequest(struct HttpRequest *req, struct HttpResponse *response)
{
    // get
    if (strcasecmp(req->method, "get") != 0)
    {
        return false;
    }
    decodeMsg(req->url, req->url);
    // 获取文件路径
    char *file = NULL;
    if (strcmp(req->url, "/") == 0)
    {
        file = "./";
    }
    else
    {
        file = req->url + 1;
    }
    // 文件状态
    struct stat st;
    int ret = stat(file, &st);
    // 不存在
    if (ret == -1)
    {
        // 发送404
        // 状态码
        response->statuscode = NotFound;
        strcpy(response->statusMsg, "Not Found");
        strcpy(response->filename, "404.html");
        // 响应头
        httpResponseAddHeader(response, "Content-type", getFileType(".html"));
        // 回应内容
        response->sendDataFunc = sendFile;
    }
    strcpy(response->filename, file);
    response->statuscode = OK;
    strcpy(response->statusMsg, "OK");
    // 目录
    if (S_ISDIR(st.st_mode))
    {
        httpResponseAddHeader(response, "Content-type", getFileType(".html"));
        response->sendDataFunc = sendDir;
    }
    // 文件
    else
    {
        char tmp[16] = {0};
        sprintf(tmp, "%ld", st.st_size);
        httpResponseAddHeader(response, "Content-type", getFileType(file));
        httpResponseAddHeader(response, "Content-length", tmp);
        response->sendDataFunc = sendFile;
    }
    return false;
}

// 发送文件
void sendFile(const char *filename, struct Buffer *sendbuf, int sockfd)
{
    Debug("要发文件了。。。");
    // 打开文件
    printf("filename: %s\n", filename);
    int fd = open(filename, O_RDONLY);
    // assert(fd > 0);
    if (fd < 0)
    {
        perror("open error\n");
        exit(1);
    }
    // 发送文件
    char buf[1024] = {0};
#if 1
    while (1)
    {
        int ret = read(fd, buf, sizeof(buf));
        if (ret > 0)
        {
            // send(cfd,buf,ret,0);
            bufferAppendData(sendbuf, buf, ret);
#ifndef MSG_SEND_AUTO
            // 发送数据
            bufferSendData(sendbuf, sockfd);
#endif
            //usleep(10); // 防止服务器发的太快，客户端解析不过来
        }
        else if (ret == 0)
        {
            break;
        }
        else
        {
            close(fd);
            perror("read error");
        }
    }
    close(fd);
#else
    off_t offset;
    int size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    while (offset < size)
    {
        int ret = sendfile(cfd, fd, &offset, size - offset);
        if (ret == -1)
        {
            perror("send file error\n");
        }
    }
    close(fd);
#endif
}

// 发送目录
void sendDir(const char *dirname, struct Buffer *sendbuf, int sockfd)
{
    Debug("要发目录了。。。");
    // 遍历目录
    struct dirent **namelist; // 指向的是一个指针数组 struct dirent* tmp[]
    int num = scandir(dirname, &namelist, NULL, alphasort);
    char buf[4096] = {0};
    sprintf(buf, "<html><head><title>%s</title></head><body><table>", dirname);
    for (int i = 0; i < num; i++)
    {
        // char cwd[1024] = {0};
        // 获取文件名
        char *name = namelist[i]->d_name;
        //跳过隐藏文件
        if(strcmp(name,".") == 0)
        {
            continue;
        }
        if(strcmp(name,"..") == 0)
        {
            continue;
        }
        // 判断文件类型
        struct stat st;
        char subPath[1024] = {0};
        // if (strcmp(dirname, "./") == 0)
        // {
        //     sprintf(subPath, "%s%s", dirname, name);
        // }
        // else
        // {
        //     sprintf(subPath, "%s%s", dirname, name);
        // }
        //sprintf(subPath, "%s/%s", dirname, name);
        sprintf(subPath, "%s%s", dirname, name);
        printf("subPath: %s,dirname: %s, name: %s\n", subPath, dirname, name);
        stat(subPath, &st);
        if (S_ISDIR(st.st_mode)) // 目录
        {
            // sprintf(buf + strlen(buf),"<tr><td><a href=\"%s\">%s/</a></td><td>%ld</td></tr>",subPath,name,st.st_size);
            sprintf(buf + strlen(buf), "<tr><td><a href=\"%s/\">%s</a></td><td>%ld</td></tr>", name, name, st.st_size);
        }
        if (S_ISREG(st.st_mode)) // 文件
        {
            sprintf(buf + strlen(buf), "<tr><td><a href=\"%s\">%s</a></td><td>%ld</td></tr>", name, name, st.st_size);
        }
        // send(cfd,buf,strlen(buf),0);
        bufferAppendString(sendbuf, buf);
#ifndef MSG_SEND_AUTO
        // 发送数据
        bufferSendData(sendbuf, sockfd);
#endif
        memset(buf, 0, sizeof(buf));
        free(namelist[i]);
    }
    sprintf(buf + strlen(buf), "</table></body></html>");
    //send(cfd,buf,strlen(buf),0);
    bufferAppendString(sendbuf, buf);
#ifndef MSG_SEND_AUTO
    // 发送数据
    bufferSendData(sendbuf, sockfd);
#endif
    free(namelist);
    return;
}

// 将字符转换为整形数
int hexToDec(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;

    return 0;
}

// 解码
// to 存储解码之后的数据, 传出参数, from被解码的数据, 传入参数
void decodeMsg(char *to, char *from)
{
    for (; *from != '\0'; ++to, ++from)
    {
        // isxdigit -> 判断字符是不是16进制格式, 取值在 0-f
        // Linux%E5%86%85%E6%A0%B8.jpg
        if (from[0] == '%' && isxdigit(from[1]) && isxdigit(from[2]))
        {
            // 将16进制的数 -> 十进制 将这个数值赋值给了字符 int -> char
            // B2 == 178
            // 将3个字符, 变成了一个字符, 这个字符就是原始数据
            *to = hexToDec(from[1]) * 16 + hexToDec(from[2]);

            // 跳过 from[1] 和 from[2] 因此在当前循环中已经处理过了
            from += 2;
        }
        else
        {
            // 字符拷贝, 赋值
            *to = *from;
        }
    }
    *to = '\0';
}

const char *getFileType(const char *name)
{
    // a.jpg a.mp4 a.html
    // 自右向左查找‘.’字符, 如不存在返回NULL
    const char *dot = strrchr(name, '.');
    if (dot == NULL)
        return "text/plain; charset=utf-8"; // 纯文本
    if (strcmp(dot, ".html") == 0 || strcmp(dot, ".htm") == 0)
        return "text/html; charset=utf-8";
    if (strcmp(dot, ".jpg") == 0 || strcmp(dot, ".jpeg") == 0)
        return "image/jpeg";
    if (strcmp(dot, ".gif") == 0)
        return "image/gif";
    if (strcmp(dot, ".png") == 0)
        return "image/png";
    if (strcmp(dot, ".css") == 0)
        return "text/css";
    if (strcmp(dot, ".au") == 0)
        return "audio/basic";
    if (strcmp(dot, ".wav") == 0)
        return "audio/wav";
    if (strcmp(dot, ".avi") == 0)
        return "video/x-msvideo";
    if (strcmp(dot, ".mov") == 0 || strcmp(dot, ".qt") == 0)
        return "video/quicktime";
    if (strcmp(dot, ".mpeg") == 0 || strcmp(dot, ".mpe") == 0)
        return "video/mpeg";
    if (strcmp(dot, ".vrml") == 0 || strcmp(dot, ".wrl") == 0)
        return "model/vrml";
    if (strcmp(dot, ".midi") == 0 || strcmp(dot, ".mid") == 0)
        return "audio/midi";
    if (strcmp(dot, ".mp3") == 0)
        return "audio/mpeg";
    if (strcmp(dot, ".ogg") == 0)
        return "application/ogg";
    if (strcmp(dot, ".pac") == 0)
        return "application/x-ns-proxy-autoconfig";

    return "text/plain; charset=utf-8";
}
