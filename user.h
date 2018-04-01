#ifndef _USER_H_
#define _USER_H_

#include "./list.h"
#include "./public.h"
#include "./interfaceUI.h"

void register_user(userNode *pHuser);
userNode *login_user(userNode *pHuser) ;
int userFunc(userNode *pHuser,userNode *pUser);

#endif