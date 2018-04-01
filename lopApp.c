#include "./lotApp.h"
/**************************************************
*根据输入的标示符来确定操作者的身份
*admin --> 1   user--> 2   failure--> 0
***************************************************/
int getLogo(void)
{
    char checkPwd[SIZE] = "";
    printf("提示信息身份标识:\n用户标识为:user\n管理员标识为:admin\n");
    printf("请先输入身份标识：");
    myGets(checkPwd,SIZE);
    if(!strcmp(checkPwd,"admin"))   //管理员端口
        return 1;
    else if(!strcmp(checkPwd,"user"))  //用户端口
        return 2;
    else
        return 0;
}
/*************************************************
*根据用户操作选择和调用获得身份标识函数来确定函数调用
*管理员注册:1   用户注册:2 　管理员登录:3 　用户登录:4
*失败重新载入:5  退出:0
*************************************************/
int choice_func()
{
    system("clear");
    loginUI();
    switch(myGetc())
    {
        case '1':
        { 
            int code = getLogo();
            if(1 == code)       //管理员注册端口
                return 1;
            else if(2 == code)  //用户注册端口
                return 2;
            else                //输入标示符不符合要求
                return 5;
        }
        case '2':
        {
            int code = getLogo();
            if(1 == code)       //管理员登录端口
                return 3;
            else if(2 == code)  //用户登录端口
                return 4;
            else                //输入标示符出错
                return 5;
        }
        case '0':
        {
            return 0;
        }
    }
    return 5;
}

/****************************************************
*根据不同用户操作实现不同用户的注册及登录
*登录成功会载入不同用户相应操作模块
*****************************************************/
int main_func()
{
    adminNode *pHadmin = adminInfoReadFromFile();
    userNode *pHuser = userInfoReadFromFile();
   
    switch(choice_func())
    {
        case 1://管理员注册端口
        {
            register_admin(pHadmin);
            break;
        }
        case 2://用户注册端口
        { 
            register_user(pHuser);
            break;
        }
        case 3://管理员登录端口
        {
            adminNode *pAdmin = login_admin(pHadmin);
            if(NULL != pAdmin)
            {
                while(adminFunc(pHadmin,pAdmin));
            }
            break;
        }
        case 4://用户登录端口
        {
            userNode *pUser = login_user(pHuser);
            if(NULL != pUser)
            {
                while(userFunc(pHuser,pUser));
            }
            break;
        }
        case 5://输入标示符出错
        {
             printf("您输入的标示符错误，注意标示符为全小写\n");
             break;
        }
        case 0:
        {
            return 0;
        }
    }
    anyKey();
    return 1;
}

int main(int argc ,char *argv[])
{
    initUI();
    anyKey();
    while(main_func());
    return 0; 
}


