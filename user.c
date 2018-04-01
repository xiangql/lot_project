#include "./user.h"

void register_user(userNode *pHuser)
{
     if(add_user(pHuser))
            printf("注册成功,请登录系统!\n");
        else
            printf("注册失败，请重新注册!\n");
    return;
}

userNode *login_user(userNode *pHuser)      //成功返回当前用户节点否则返回空
{
    userNode *pUser = user_login(pHuser);
    if(NULL != pUser){
        printf("%s ,welcome login system!\n",pUser->data.name);
        return pUser;
    }
    else
    {
           printf("登录失败，请重新登录!\n");
           return NULL;
    }
     return NULL;
}

int userFunc(userNode *pHuser,userNode *pUser)
{
    system("clear");
    printf("\t\t用户: %s \n\n",pUser->data.name);
    userUI();
    char ch = myGetc(); 
    lotNode *pHlot = lotInfoReadFromFile(FILENAME);
    reloadNode(pUser);
    switch(ch)
    {
        case '1':   //查询个人信息
        {
            show_userInfo(pUser);
            break;
        }
        case '2':   //显示购彩记录
        {
            show_lotInfo(pUser->data.pFrist);
            break;
        }
        case '3':   //查看彩票
        {
            show_lotInfo(pHlot);
            break;
        }
        case '4':   //购买彩票
        {
            buy_lottory(pUser);
            userInfoWriteToFile(pHuser);
            break;
        }
          case '5':   //账户充值
        {
            Rechage(&pUser->data);
            userInfoWriteToFile(pHuser);
            break;
        }
        case '6':   //清空开奖彩票
        {
            clear_past_lotNode(pUser->data.pFrist);
            break;
        }
        case '8':   //修改用户信息
        {
            correct_userInfo(pHuser,pUser);
            userInfoWriteToFile(pHuser);
            break;
        }
        case '7':   //注销用户
        {
            del_user(pHuser,pUser);
            userInfoWriteToFile(pHuser);
            anyKey();
            return 0;
        }
        case '0':   //退出　销毁链表
        {
            destory_lotInfo(pHlot);
            destory_userInfo(pHuser);
            return 0;
        }
    }
    anyKey();
    return 1;
}

