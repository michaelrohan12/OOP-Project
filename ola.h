#ifndef OLA_H_INCLUDED
#define OLA_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdio>
#include <sys/stat.h>
#include <windows.h>
#include <cstring>
#include <algorithm>
#include <list>
#include <conio.h>
#include <regex>
#include <semaphore.h>

using namespace std;

#define MAX 100000
#define SUCCESS                     1
#define FAILURE                    -1
#define FILE_OPEN_ERROR             1001
#define MEMORY_ALLOCATION_ERROR     1002
#define FILE_DELETE_ERROR           1003
#define COUNT_EXCEED_ERROR          1004
#define FILE_EMPTY_ERROR            1006
#define RESULT_NOT_FOUND            1005


void replace(string& str) {
    for(int i=0;i<str.length();i++){
        if(str[i] == '_')
            str[i] = ' ';
    }
}

char str[] = "0123456789";
char temp[7];
int flag1 = 1;
int flag2 = 1;
int flagl = 1;
int flags = 1;
int choice1 = 1;
int choice2 = 1;
int choice3 = 1;
int choice4 = 1;
int choice5 = 1;
int choice6 = 1;
int status = 0;
int running = 1;
int ans = 0;
int index1,index2;
string vehicle_type;
int temp1;
char temp2[50],temp5[50],temp6[50];
double temp3,temp4;
string coupon_temp;
int dis;
int code;


#endif