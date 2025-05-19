#pragma once
#include<stdbool.h>
#include"channel.h"

struct ChannelMap
{
    //struct channel* list[]
    struct channel** list;
    
    //数组元素个数
    int size;
};

//初始化
struct ChannelMap* channelMapInit(int size);

//清空map
void channelMapClear(struct ChannelMap* map);

//数组扩容
bool  makeMapRoom(struct ChannelMap* map, int newSize, int unitSize);