#include "./public.h"
char *myGets(char *src, int size)
{
    char *dest = src;
    for(; dest<src+size-1; )
    {
        *dest = getchar();
        if(*src == '\n')
            continue;
        if(*dest == '\n')
            break;
        dest++;
    }
    if(*dest != '\n')
        while(getchar() != '\n');
    *dest = '\0';
    return src;
}
char myGetc()   //只获取一个字符
{
    char ch= getchar();
    while(getchar()!='\n')
    ;
    return ch;
}
void anyKey()   //在清屏前暂停显示
{
    printf("\n按任意键继续..\n");
    while(getchar() != '\n');
}

void printState(bool a,int b)   //彩票的几种状态的打印方式
{
    if(a == false){
        if(0 == b)
            printf("false");
        else
            printf("$:%d",b);
    }
    else
        printf("true ");
    return;
}
int set_adminID()
{
    printf("管理员ID:");
    int adminID = 0;
    scanf("%d",&adminID);
    return adminID;
}
int set_adminPwd()
{
    printf("密码:");
    int adminPwd = 0;
    scanf("%d",&adminPwd);
    return adminPwd;
}
int set_lotID()
{
    printf("彩票ID:");
    int lotID = 0;
    scanf("%d",&lotID);
    return lotID;
}
void set_name(char *name)
{
    printf("用户名:");
    myGets(name,SIZE);
    return;
}
void set_userID(char *userID)
{
    printf("ID:");
    myGets(userID,SIZE);
    return;
}
void set_userPwd(char *userPwd)
{
    printf("密码:");
    myGets(userPwd,SIZE);
    return;
}
char *set_filename(char *filename,char *userID)
{
    strcat(filename,"./user/");
    strcat(filename,userID);
    strcat(filename,".dat");
    return filename;
}
int set_money()
{
    int money = 0;
    printf("输入金额:");
    scanf("%d",&money);
    return money;
}

int set_counted()
{
    printf("输入购买数量:");
    int counted = 0;
    scanf("%d",&counted);
    return counted;
}







