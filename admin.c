#include "./admin.h"

/************************************************************
*管理员的注册，同时返回注册的结果
*管理员的登录，成功返回当前用户节点，失败返回空
************************************************************/

void register_admin(adminNode *pHadmin)     //显示注册结果
{
    if(add_admin(pHadmin))
        printf("注册成功,请登录系统!\n");
    else
        printf("注册失败，请重新注册!\n");
    return;
}

adminNode *login_admin(adminNode *pHadmin)      //成功返回当前用户节点否则返回空
{
    adminNode *pAdmin = admin_login(pHadmin);
    if(NULL != pAdmin){
        printf("%s ,welcome login system!\n",pAdmin->data.name);
        return pAdmin;
    }
    else
    {
           printf("登录失败，请重新登录!\n");
           return NULL;
    }
     return NULL;
}

/*****************************************************************
*管理员登录成功载入此操作界面
*实现管理员的所有功能模块
******************************************************************/
int adminFunc(adminNode *pHadmin,adminNode *pAdmin)
{
    system("clear");
    printf("\t\t管理员: %s \n\n",pAdmin->data.name);
    adminUI();
    switch(myGetc())
    {   
        lotNode *pHlot = lotInfoReadFromFile(FILENAME);
        //读取所需文件信息，保证操作的为最新数据
        case '1':   //彩票发布
        {
            add_lottery(pHlot);
            break;
        }
        case '2':   //根据lotID删除彩票
        {
            del_lotNode(pHlot);
            break;
        }
        case '3':   //查询彩票信息－－＞ＩＤ查询/全部显示
        {
            search_lotID(pHlot);
            break;
        }
        case '4':   //根据lotID排序
        {
            sort_lotID(pHlot);
            break;
        }
        case '5':   //彩票开奖
        {
            show_Win_lotInfo(pHlot);
            break;
        }
        case '6':   //清空开奖彩票
        {
            clear_past_lotNode(pHlot);
            break;
        }
        case '7':   //注销用户
        {
            del_admin(pHadmin,pAdmin);
            anyKey();
            return 0;
        }
        case '0':   //退出　销毁链表
        {
            destory_adminInfo(pHadmin);
            destory_lotInfo(pHlot);
            return 0;
        }
    }
    anyKey();
    return 1;
}









