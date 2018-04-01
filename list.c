#include "./list.h"

/***********************管理员端口函数********************
*初始化管理员注册信息并保证ID全局唯一
*将管理员注册节点连接上链表并写入文件
*******************************************************/
int check_adminID(adminNode *pHadmin,int adminID)
{
    adminNode *temp = pHadmin->pNext;
    while(NULL != temp)
    {
        if(temp->data.adminID == adminID)
            return 0;
        temp = temp->pNext;
        if(NULL == temp)
            return 1;
    }
    return 1;
}
void init_adminInfo(adminNode *pHadmin,adminInfo *pAdmin)
{
    printf("============完善以下信息============\n");
    pAdmin->adminID = set_adminID();
    if(!check_adminID(pHadmin,pAdmin->adminID))
    {
        printf("ID 已被占用,请重新录入\n");
        init_adminInfo(pHadmin,pAdmin);
        return;
    }
    pAdmin->adminPwd = set_adminPwd();
    set_name(pAdmin->name);
}
int add_admin(adminNode *pHadmin)
{
    if(NULL == pHadmin){
        printf("%s the link is empty!\n",__func__);
        return -1;
    }
    adminNode *newNode = make_adminNode();
    init_adminInfo(pHadmin,&newNode->data);
    newNode->pNext = pHadmin->pNext;
    pHadmin->pNext = newNode;
    if(pHadmin == NULL)
        printf("dafsdfa");
    adminInfoWriteToFile(pHadmin);
    newNode = NULL;
    return 1;
}
/*******************************************************
*根据输入的ID and pwd 寻找链表的匹配节点
*找匹配节点则返回，未找到则返回空
********************************************************/
adminNode *admin_login(adminNode *pHadmin)
{
    if(NULL == pHadmin){
        printf("%s the link is empty!\n",__func__);
        return NULL;
    }
    int adminID = set_adminID();
    int adminPwd = set_adminPwd();
    adminNode *temp = pHadmin->pNext;
    while(NULL != temp)
    {
        if(adminID == temp->data.adminID && adminPwd == temp->data.adminPwd)
            break;
        temp = temp->pNext;
    }
    return temp;
}
/******************************************************************
*初始化彩票信息并保证ＩＤ全局唯一
*将彩票节点连接上链表，并写入文件
*******************************************************************/
int check_lotID(lotNode *pHlot,int lotID)
{
    lotNode *temp = pHlot->pNext;
    while(NULL != temp){
        if(lotID == temp->data.lotID)
            return 0;  //ID重复 返回 0
        temp = temp->pNext;
    }
    if(NULL == temp)
        return 1;    //此ID唯一 返回 1
    return 1;
}

void init_lotInfo(lotNode *pHlot,lotInfo *temp)
{
    printf("\n=============彩票信息添加===============\n");
    temp->lotID = set_lotID();
    if(!check_lotID(pHlot,temp->lotID)){
        printf("此ID已占用，请重新录入\n");
        init_lotInfo(pHlot,temp);
        return;
    }
    printf("名字：");
    myGets(temp->lotname,SIZE);
    printf("类型：");
    myGets(temp->type,SIZE);
    printf("单价：");
    scanf("%f",&temp->price);
    getchar();
    //购买数量初始化为零
    temp->counted = 0;
    temp->state[0] = true;      //初始化状态为未开奖
    temp->state[1] = 0;         //中奖金额初始化为零
    printf("发布时间：\n");
    myGets(temp->star,SIZE);
    printf("开奖时间：\n");
    myGets(temp->last,SIZE);
    return;
}

int add_lottery(lotNode *pHlot)
{
    if(NULL == pHlot){
        printf("\n\t%s:the link is empty!\n",__func__);
        return -1;
    }

    lotNode *newNode = make_lotNode();
    init_lotInfo(pHlot,&newNode->data);

    newNode->pNext = pHlot->pNext;
    pHlot->pNext = newNode;
    newNode = NULL; 
    return 1;
}
/*************************************************************
*根据彩票ID删除相应的彩票节点
**************************************************************/
int del_lotNode(lotNode *pHlot)
{
    if(NULL == pHlot || NULL == pHlot->pNext){
        printf("无彩票信息，请先添加\n");
        return -1;
    }
    int lotID = set_lotID();
    lotNode *pPre = pHlot;
    lotNode *pCur = pHlot->pNext;

    while(NULL != pCur)
    {
        if(lotID == pCur->data.lotID)
        {
            pPre->pNext = pCur->pNext;
            free(pCur);
            pCur = NULL;

            return 1;
        }
        pCur = pCur->pNext;
        pPre = pPre->pNext;
    }
    if(NULL == pCur){
        printf("无此相关信息\n");
        return 0; //未找到匹配项
    }
    return 1;
}
/***************************************************
*打印彩票节点数据域信息
*根据ID找到彩票链表中的节点，并打印
**************************************************/
void print_lotInfo(lotInfo temp)
{
    printf("%d\t%s\t%.2f\t %d\t",
            temp.lotID,
            temp.type,
            temp.price,
            temp.counted);
    printState(temp.state[0],temp.state[1]);
    printf("\t%s\t%s\n",temp.star,temp.last);
    return;
}

int search_lotID(lotNode *pHlot)
{
    if(NULL == pHlot || NULL == pHlot->pNext){
        printf("无彩票信息，请先添加\n");
        return 0;
    }
    int lotID = set_lotID();
    lotNode *temp = pHlot->pNext;
    while(NULL != temp){
        if(lotID == temp->data.lotID){
            printf("编号\t类型\t单价\t数量\t状态\t发布时间\t开奖时间\n");
            print_lotInfo(temp->data);
            return 1;
        }
        temp = temp->pNext;
    }
    if(NULL == temp){
        return 0;   //没有相关信息
    }
    anyKey();
    return 1;
}
/****************************************************
*根据ID对彩票链表进行排序
****************************************************/
void swapNode(lotInfo *temp,lotInfo *loop)
{
    lotInfo p = *temp;
    *temp = *loop;
    *loop = p;
}

int sort_lotID(lotNode *pHlot)
{
    if(NULL == pHlot || NULL == pHlot->pNext){
        printf("%s the link is empty!\n",__func__);
        return -1;
    }
    lotNode *temp = pHlot->pNext;
    if(NULL == temp->pNext)
        return 1;
    while(NULL != temp->pNext){
        lotNode * loop = temp->pNext;
        while(NULL != loop){
            if(temp->data.lotID > loop->data.lotID){  //从小到大排序
                //第一个节点存储最小值，如果不是比后面节点的值小，则交换结构体成员的值
                swapNode(&temp->data,&loop->data);
            }
            loop = loop->pNext;
        }
        temp = temp->pNext;
    }
    return 1;
}
/**********************************************************
*随机选取未开奖彩票ID进行开奖并显示
*更改彩票的状态以及更改购买者的余额和被购彩票的状态
**********************************************************/
int num_range(lotNode *pHlot)
{
    int num = 0;
    lotNode *temp = pHlot->pNext;
    while(NULL != temp){
        if(temp->data.state[0])
            num+=1;
        temp = temp->pNext;
    }
    if(num == 0){
        printf("无未开奖彩票\n");
    }
    return num;
}
int get_WinID(lotNode *pHlot,int money)
{
    if(NULL == pHlot || NULL == pHlot->pNext){
        printf("%s the link empty!\n",__func__);
        return 0;
    }
    srand(time(0));
    int size = (int)(rand()%num_range(pHlot))+1;
    lotNode *p = pHlot->pNext;
    while(NULL != p){
        if(p->data.state[0] == true)
            size-=1;
        if(size == 0)
            break;
        p = p->pNext;
    }
    p->data.state[0] = false;
    p->data.state[1] = money;
    print_lotInfo(p->data);
    int lotID = p->data.lotID;
    p = NULL;
    lotInfoWriteToFile(pHlot,FILENAME);
    return lotID;
}

void update(int lotID,int money,userNode *pHuser)
{
    if(NULL == pHuser){
        printf("%s the link is empty!",__func__);
        return;
    }
    userNode *temp = pHuser->pNext;
    while(NULL != temp)
    {
        lotNode *pHbuy = temp->data.pFrist;
        lotNode *loop = pHbuy->pNext;
        while(NULL != loop)
        {
            if(loop->data.lotID == lotID)
            {
                temp->data.balance += (loop->data.counted*money);
            }
            loop = loop->pNext;
        }
        lotInfoWriteToFile(temp->data.pFrist,temp->data.filename);
        temp = temp->pNext;
    }
    userInfoWriteToFile(pHuser);
    return;
}
void show_Win_lotInfo(lotNode *pHlot)
{
    int money = set_money();
    int lotID = get_WinID(pHlot,money);
    userNode *pHuser = userInfoReadFromFile();
    update(lotID,money,pHuser);
    return;
}

/************************************************************
*清空彩票文件中已开奖彩票的信息
***************************************************************/
void clear_past_lotNode(lotNode *pHlot)
{
    if(NULL == pHlot || NULL == pHlot->pNext){
        printf("the link is empty!\n");
        return;
    }
    lotNode *pPre = pHlot;
    lotNode *pCur = pHlot->pNext;
    while(NULL != pCur)
    {
        if(pCur->data.state[0] == false){
            pPre->pNext = pCur->pNext;
            free(pCur);
            pCur = NULL;
        }
        pCur = pPre->pNext; 
        pPre = pPre->pNext;
    }
    return;
}

/**************************************************************
*注销当前用户，且更新文件信息
****************************************************************/
void del_admin(adminNode *pHadmin,adminNode *pAdmin)
{
    adminNode *pPre = pHadmin;
    adminNode *pCur = pHadmin->pNext;
    while(NULL != pCur)
    {
        if(pCur->data.adminID == pAdmin->data.adminID)
        {
            pPre->pNext = pCur->pNext;
            free(pCur);
            pCur = NULL;
        }
        pCur = pPre->pNext;
        pPre = pPre->pNext;
    } 
    adminInfoWriteToFile(pHadmin);
    return;
}

/**********************************************************
*用户端口函数
*用户的添加并且保证ID全局唯一
*将改动信息写入文件
************************************************************/
int check_userID(userNode *pHuser,char *userID)
{
    userNode *temp = pHuser->pNext;
    while(NULL != temp){
        if(!strcmp(userID,temp->data.userID))
            return 0;  //账户重名 返回 0
        temp = temp->pNext;
    }
    if(NULL == temp)
        return 1;    //此账户唯一 返回 1
    return 1;
}
void init_userInfo(userNode *pHuser,userInfo *temp)
{
    printf("\n============完善用户信息===============\n");
    //需要检查账户的唯一性
    printf("注意ID确认后无法更改,请认真填写\n");
    set_userID(temp->userID);
    if(!check_userID(pHuser,temp->userID)){
        printf("次账户已存在，请重新录入\n");
        sleep(1);
        init_userInfo(pHuser,temp);
        return;
    }
    //strcpy(temp->userID,userID);
    set_name(temp->name);
    set_userPwd(temp->userPwd);
    printf("初始余额为零，请注意充值\n");
    temp->balance = 0;  //初始化账户余额为0
    set_filename(temp->filename,temp->userID);
    temp->pFrist = make_lotNode();
    return;
}
int add_user(userNode *pHuser)
{
    if(NULL == pHuser){
        printf("\n\t%s:the link is empty!\n",__func__);
        return 0;
    }
    userNode *newNode = make_userNode();
    init_userInfo(pHuser,&newNode->data);

    newNode->pNext = pHuser->pNext;
    pHuser->pNext = newNode;
    newNode = NULL;
    userInfoWriteToFile(pHuser);
    return 1;
}

/*********************************************************
*检测用户登录　成功返回当前用户节点　失败返回空
*********************************************************/
userNode *user_login(userNode *pHuser)
{
    if(NULL == pHuser){
        printf("%s the link is empty!\n",__func__);
        return NULL;
    }
    userNode *temp = pHuser->pNext;
    char userID[SIZE] = "";
    set_userID(userID);
    char userPwd[SIZE] = "";
    set_userPwd(userPwd);
    while(NULL != temp)
    {
        if(!strcmp(userID,temp->data.userID) && !strcmp(userPwd,temp->data.userPwd))
            break;
        temp = temp->pNext;
    }
    return temp;
}
/************************************************
*用户重定位
*************************************************/
userNode *reloadNode(userNode *pUser)
{
    userNode *pHuser = userInfoReadFromFile();
    userNode *temp = pHuser->pNext;
    while(NULL != temp){
        if(!strcmp(pUser->data.userID,temp->data.userID))
            pUser->data.balance = temp->data.balance;
            temp = temp->pNext;
    }
    return pUser;
}
/************************************************
*打印用户相关信息
*************************************************/
void show_userInfo(userNode *temp)
{
    printf("账 户：%s\n",temp->data.userID);
    printf("用户名：%s\n",temp->data.name);
    printf("余 额：%.2f\n",temp->data.balance);
    return;
}
/**************************************************
 * 用户端口显示彩票信息,将开奖彩票进行隐藏显示
 *************************************************/

void show_lotInfo_user(lotNode *pFrist)
{
    printf("编号\t类型\t单价\t数量\t状态\t发布时间\t开奖时间\n");
    lotNode *temp = pFrist->pNext;
    while(NULL != temp){
        if(temp->data.state[0] == true)
            print_lotInfo(temp->data);
        temp = temp->pNext;
    }
    return;
}

/**************************************************
*购买彩票并改变用户余额
*改变彩票的被够数量
****************************************************/

int buy_lottory(userNode *pUser,lotNode *pFrist)
{
    lotNode *pHlot = lotInfoReadFromFile(FILENAME);
    lotNode *temp = pHlot->pNext;
    int lotID = set_lotID();
    int counted = set_counted();
    while(NULL != temp)
    {
        if(lotID == temp->data.lotID)
        {
            if(temp->data.price*counted > pUser->data.balance){
                printf("余额不足,请先充值\n");
                return 0;
            }
            if(temp->data.state[0] == false)
            {
                printf("此ID彩票已开奖,请重新购买\n");
                return 0;
            }
            lotNode *newNode = make_lotNode();
            newNode->data = temp->data;
            newNode->data.counted = counted;
            temp->data.counted += counted;
            pUser->data.balance -= temp->data.price*counted;
            
            newNode->pNext = pFrist->pNext;
            pFrist->pNext = newNode;
            newNode = NULL;
            lotInfoWriteToFile(pHlot,FILENAME);
            return 1;
        }
        temp = temp->pNext;
    }
    if(temp == NULL)
        printf("此ID彩票不存在,请确认ID正确\n");
    return 0;
}
/****************************************************
*根据头指针显示购买彩票信息
*****************************************************/
void show_buy_lotInfo(lotNode *pHlot)
{
    if(NULL == pHlot || NULL == pHlot->pNext){
        printf("the link is empty!\n");
        return;
    }
    lotNode *temp = pHlot->pNext;
    printf("编号\t类型\t单价\t数量\t状态\t发布时间\t开奖时间\n");
    while(NULL != temp){
        print_lotInfo(temp->data);
        temp = temp->pNext;
    }
    return;
}
/***************************************************
*对当前用户进行充值
****************************************************/
int Rechage(userInfo *temp)
{
    temp->balance += (float)set_money();
    return 1;
}

/***************************************************
*修改用户信息
***************************************************/
int correct_userInfo(userNode *pHuser,userNode *pUser)
{   
    char userPwd[SIZE] = "";
    set_userPwd(userPwd);
    if(!strcmp(userPwd,pUser->data.userPwd)){
    //    init_userInfo(pHuser,&pUser->data);调用会使余额归零
    //    set_userID(pUser->userID); 更改会造成文件名与用户ID不匹配
        set_name(pUser->name);
        set_userPwd(pUser->userPwd);
    }
    else
        printf("请确认密码正确才允许修改数据\n");
    return 1;
}
/****************************************************
*注销用户
*****************************************************/
int del_user(userNode *phUser,userNode *pUser)
{
    userNode *pPre = phUser;
    userNode *pCur = phUser->pNext;
    while(NULL != pCur){
        if(strcmp(pCur->data.userID,pUser->data.userID)){
            //销毁用户彩票链表
            pPre->pNext = pCur->pNext;
            destory_lotInfo(pUser->data.pFrist);
           lotInfoWriteToFile(pUser->data.pFrist,pUser->data.filename);
            return 1;
        }
        pPre = pPre->pNext;
        pCur = pCur->pNext;
    }
    return 0;
}

/***********************************************************
*创建相关数据节点
*读取相关文件信息到链表
*将链表信息写入文件
*注销链表结构
************************************************************/
adminNode *make_adminNode()
{
    adminNode *newNode = (adminNode*)malloc(ADMIN_NODE_LEN);
    if(NULL == newNode)
        newNode = (adminNode*)malloc(ADMIN_NODE_LEN);
    newNode->pNext = NULL;
    return newNode;
}

lotNode *make_lotNode()
{
    lotNode *newNode = (lotNode*)malloc(LOT_NODE_LEN);
    if(NULL == newNode)
        newNode = (lotNode*)malloc(LOT_NODE_LEN);
    newNode->pNext = NULL;
    return newNode;
}

userNode *make_userNode()
{
    userNode * newNode = (userNode*)malloc(USER_NODE_LEN);
    if(NULL == newNode)
        newNode = (userNode*)malloc(USER_NODE_LEN);
    newNode->pNext = NULL;
    return newNode;
}

lotNode *lotInfoReadFromFile(char *filename)
{
    FILE *fpr = fopen(filename,"a+");
    if(NULL == fpr){
        perror("open error");
        return NULL;
    }
    lotNode *pHlot = make_lotNode();
    lotNode *newNode = make_lotNode();
    while(fread(&newNode->data,LOT_INFO_LEN,1,fpr)>0)
    {
        newNode->pNext = pHlot->pNext;
        pHlot->pNext = newNode;
        newNode = make_lotNode();
    }
    free(newNode);
    newNode = NULL;
    fclose(fpr);
    return pHlot;
}

void lotInfoWriteToFile(lotNode *pHlot,char *filename)
{
    if(NULL == pHlot){
        printf("%s the link is empty!\n",__func__);
        return;
    }
    FILE *fpw = fopen(filename,"w");
    if(NULL == fpw){
        perror("open error");
        return;
    }
    int ret = 0;
    lotNode *temp = pHlot->pNext;
    while(NULL != temp){
        ret = fwrite(&temp->data,LOT_INFO_LEN,1,fpw);
        if(ret < 0)
            break;
        temp = temp->pNext;
    }
    fclose(fpw);
    return;
}

adminNode *adminInfoReadFromFile()
{
    FILE *fpr = fopen("./adminInfo.dat","r");
    if(NULL == fpr){
        perror("open error");
        return NULL;
    }
    adminNode *pHadmin = make_adminNode();
    adminNode *newNode = make_adminNode();
    while(fread(&newNode->data,ADMIN_INFO_LEN,1,fpr) > 0)
    {
        newNode->pNext = pHadmin->pNext;
        pHadmin->pNext = newNode;
        newNode = make_adminNode();
    }
    free(newNode);
    newNode = NULL;
    fclose(fpr);
    return pHadmin;
}

void adminInfoWriteToFile(adminNode *pHadmin)
{
    if(NULL == pHadmin){
        printf("%s the link is empty!\n",__func__);
        return;
    }
    FILE *fpw = fopen("./adminInfo.dat","w");
    if(NULL == fpw){
        perror("open error");
        return;
    }
    int ret = 0;
    adminNode *temp = pHadmin->pNext;
    while(NULL != temp)
    {
        ret = fwrite(&temp->data,ADMIN_INFO_LEN,1,fpw);
        if(ret < 0)
            break;
        temp = temp->pNext;
    }
    fclose(fpw);
    return;
}

userNode *userInfoReadFromFile()
{
    FILE *fpr = fopen("./userInfo.dat","r");
    if(NULL == fpr){
        perror("open error");
        return NULL;
    }
    userNode *pHuser = make_userNode();
    userNode *newNode = make_userNode();
    while(fread(&newNode->data,USER_INFO_LEN,1,fpr) > 0)
    {
        newNode->pNext = pHuser->pNext;
        pHuser->pNext = newNode;
        newNode = make_userNode();
    }
    free(newNode);
    newNode = NULL;
    fclose(fpr);
    return pHuser;
}

void userInfoWriteToFile(userNode *pHuser)
{
    if(NULL == pHuser){
        printf("the link is empty!");
        return;
    }
    FILE *fpw = fopen("./userInfo.dat","w");
    if(NULL == fpw){
        perror("open error");
        return;
    }
    int ret = 0;
    userNode *temp = pHuser->pNext;
    while(NULL != temp)
    {
        ret = fwrite(&temp->data,USER_INFO_LEN,1,fpw);
        if(ret < 0)
            break;
        temp = temp->pNext;
    }
    fclose(fpw);
    return;
}

void destory_adminInfo(adminNode *pHadmin)
{
    if(NULL == pHadmin)
    {
        printf("the link is empty!\n");
        return;
    }
    adminNode *temp = NULL;
    while(NULL != pHadmin){
        temp = pHadmin;
        pHadmin = pHadmin->pNext;
        free(temp);
    }
    temp = NULL;
    return;
}
void destory_lotInfo(lotNode *pHlot)
{
    if(NULL != pHlot){
        printf("the link is empty!\n");
        return;
    }
    lotNode *temp = NULL;
    while(NULL != temp)
    {
        temp = pHlot;
        pHlot = pHlot->pNext;
        free(temp);
    }
    temp = NULL;
    return;
}
void destory_userInfo(userNode *pHuser)
{   
    if(NULL == pHuser)
    {
        printf("the link is empty!\n");
        return;
    }
    userNode *temp = NULL;
    while(NULL != pHuser){
        temp = pHuser;
        pHuser = pHuser->pNext;
        destory_lotInfo(temp->data.pFrist);
        free(temp);
    }
    temp = NULL;
    return;
}