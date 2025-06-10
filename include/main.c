#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include"TcpServer.h"

int main(int argc, char* argv[]) 
{
#if 0 
    if(argc < 3)
    {
        printf("a.out workdir port\n");
        return -1;
    }
    //port
    unsigned short port = atoi(argv[2]);
    //dir
    chdir(argv[1]);
#else
    unsigned short port = 8080;
    chdir("/home/mical/lib-web");
#endif
    //启动
    struct TcpServer* server = tcpServerInit(port,4);
    tcpServerRun(server);
    return 0;
}

