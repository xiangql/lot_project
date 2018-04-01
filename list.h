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
#define FILENAME "./lotInfo.dat"

typedef struct adminInfo{   //管理员信息结构
    int adminID;
    int adminPwd;
    char name[SIZE];
}adminInfo;
typedef struct adminNode{   //管理员信息节点
    struct adminInfo data;  //数据域

    struct adminNode *pNext;//指针域
}adminNode;

typedef struct lotInfo{     //彩票信息结构
    int lotID;      //全局唯一
    char lotname[SIZE];
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
    float balance;
    char filename[SIZE];
    lotNode *pFrist;       //购买彩票信息
}userInfo;
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

/***********************************************
 *管理员函数声明
 ************************************************/
int check_adminID(adminNode *pHadmin,int adminID);
void init_adminInfo(adminNode *pHadmin,adminInfo *pAdmin);
int add_admin(adminNode *pHadmin);
adminNode *admin_login(adminNode *pHadmin);
int check_lotID(lotNode *pHlot,int lotID);
void init_lotInfo(lotNode *pHlot,lotInfo *temp);
int add_lottery(lotNode *pHlot);
int del_lotNode(lotNode *pHlot);
void print_lotInfo(lotInfo temp);
int search_lotID(lotNode *pHlot);
void swapNode(lotInfo *temp,lotInfo *loop);
int sort_lotID(lotNode *pHlot);
int num_range(lotNode *pHlot);
int get_WinID(lotNode *pHlot,int money);
void update(int lotID,int money,userNode *pHuser);
void show_Win_lotInfo(lotNode *pHlot);
void clear_past_lotNode(lotNode *pHlot);
void del_admin(adminNode *pHadmin,adminNode *pAdmin);


/**********************************************
 *用户函数声明 
 *********************************************/
int check_userID(userNode *pHuser,char *userID);
void init_userInfo(userNode *pHuser,userInfo *temp);
int add_user(userNode *pHuser);
userNode *user_login(userNode *pHuser);
userNode *reloadNode(userNode *pUser);
void show_userInfo(userNode *temp);
int buy_lottory(userNode *pUser,lotNode *pFrist);
void show_buy_lotInfo(lotNode *pHlot);
void show_lotInfo_user(lotNode *pFrist);
int Rechage(userInfo *temp);
int correct_userInfo(userNode *pHuser,userNode *pUser);
int del_user(userNode *phUser,userNode *pUser);

/**********************************************
 * 节点创建　文件读取　链表销毁函数声明
 *********************************************/
adminNode *make_adminNode();
lotNode *make_lotNode();
userNode *make_userNode();
lotNode *lotInfoReadFromFile(char *filename);
void lotInfoWriteToFile(lotNode *pHlot,char *filename);
adminNode *adminInfoReadFromFile();
void adminInfoWriteToFile(adminNode *pHadmin);
userNode *userInfoReadFromFile();
void userInfoWriteToFile(userNode *pHuser);
void destory_adminInfo(adminNode *pHadmin);
void destory_lotInfo(lotNode *pHlot);
void destory_userInfo(userNode *pHuser);
#endif
