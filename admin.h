#ifndef _ADMIN_H_
#define _ADMIN_H_

#include "./list.h"
#include "./public.h"
#include "./interfaceUI.h"

void register_admin(adminNode *pHadmin);
adminNode *login_admin(adminNode *pHadmin);
int adminFunc(adminNode *pHadmin,adminNode *pAdmin);

#endif
