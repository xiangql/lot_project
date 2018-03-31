#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#include<stdio.h>
#include "./list.h"

char *myGets(char *src, int size);

int initTime(Times *times);
void setTime(Times *times);
void putTime(Times times);

int putInt();
int setID();
int setAccount();
int setPwd();
int setNum();
char * setName(char *str);
int setMoney();
char myGetc();
void anyKey();
void printState(bool a,int b);
//增加的函数声明
adminNode *make_adminNode();
lotNode *make_lotNode();




#endif
