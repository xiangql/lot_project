#ifndef _LIST_H_
#define _LIST_H_

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include "./public.h"

#define bool int
#define true 1
#define false 0
#define SIZE 32

typedef struct adminInfo{   //管理员信息结构
    int adminID;
    int adminPwd;
    char name[SIZE];
}adminInfo;
typedef struct adminNode{   //管理员信息节点
    struct adminInfo data;  //数据域

    struct adminInfo *pNext;//指针域
}

typedef struct lotInfo{     //彩票信息结构
    int lotID;      //全局唯一
    char name[SIZE];
    char type[SIZE];
    float price;
    int counted;
    bool state[2];//是否开奖　及中奖金额
    char star[SIZE];
    char last[SIZE];
}lotInfo;

typedef struct lotNode{     //彩票信息节点
    struct lotInfo data;

    struct lotNode *pNext;
}lotNode;

typedef struct userInfo{    //用户信息结构
    char userID[SIZE];
    char name[SIZE];
    char userPwd[SIZE];
    float blance;
    char filename[SIZE];
    adminNode *pHbuy;       //购买彩票信息
}
typedef struct userNode{    //用户信息节点
    struct userInfo data;

    struct userNode *pNext;
}userNode;

#define ADMIN_INFO_LEN sizeof(adminInfo)
#define ADMIN_NODE_LEN sizeof(adminNode)
#define LOT_INFO_LEN sizeof(lotInfo)
#define LOT_NODE_LEN sizeof(lotNode)
#define USER_INFO_LEN sizeof(userInfo)
#define USER_NODE_LEN sizeof(userNode)





#endif
