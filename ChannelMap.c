#include"ChannelMap.h"
#include<stdlib.h>
#include <string.h>

//初始化
struct ChannelMap* channelMapInit(int size)
{
    struct ChannelMap* map = (struct ChannelMap*)malloc(sizeof(struct ChannelMap));
    map->size = size;
    map->list = (struct channel**)malloc(size * sizeof(struct channel));
    return map;
}

//清空map
void channelMapClear(struct ChannelMap* map)
{
    if(map != NULL)
    {
        for(int i = 0;i < map->size;i++)
        {
            if(map->list[i] != NULL)
            {
                free(map->list[i]);
            }
        }
        free(map->list);
        map->list = NULL;
    }
    map->size = 0;
}

//数组扩容
bool  makeMapRoom(struct ChannelMap* map, int newSize, int unitSize)
{
    if(map->size < newSize)
    {
        int cursize = map->size;
        while(cursize < newSize)
        {
            cursize *= 2;
        }
        struct channel** temp = realloc(map->list,cursize * unitSize);
        if(temp == NULL)
        {
            return false;
        }
        map->list = temp;
        memset(&map->list[map->size],0,(cursize - map->size) * unitSize);
        map->size = cursize;
    }
    return true;
}