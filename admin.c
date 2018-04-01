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
    char ch = myGetc();
    lotNode *pHlot = lotInfoReadFromFile(FILENAME);//读取所需文件信息，保证操作的为最新数据
    switch(ch)
    {   
        case '1':   //彩票发布
        {
            if(add_lottery(pHlot))
                printf("彩票发布成功,请点击查询查看\n");
            else
                printf("发布失败,请重新发布\n");
            lotInfoWriteToFile(pHlot,FILENAME);
            break;
        }
        case '2':   //根据lotID删除彩票
        {
            if(del_lotNode(pHlot))
                printf("删除成功\n");
            else
                printf("删除失败,请重新操作\n");
            lotInfoWriteToFile(pHlot,FILENAME);
            break;
        }
        case '3':   //查询彩票信息－－＞ＩＤ查询/全部显示
        {
            search_lotID(pHlot);
            anyKey();
            break;
        }
        case '4':   //根据lotID排序
        {
            if(sort_lotID(pHlot))
                printf("排序成功\n");
            else
                printf("排序失败\n");
            lotInfoWriteToFile(pHlot,FILENAME);
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
            lotInfoWriteToFile(pHlot,FILENAME);
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









