#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#define bool int
#define true 1
#define false 0
#include<stdio.h>
#include "./list.h"

char *myGets(char *src, int size);
char myGetc();
void anyKey();
void printState(bool a,int b);


int set_adminID();
int set_adminPwd();
int set_lotID();
void set_name(char *name);
void set_userID(char *adminID);
void set_userPwd(char *adminPwd);
char *set_filename(char *filename,char *userID);
int set_money();
int set_counted();
#endif
