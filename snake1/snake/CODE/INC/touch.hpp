#ifndef __TOUCH_HPP__
#define __TOUCH_HPP__

#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <linux/input.h>
#include <unistd.h>
#include <iostream>
#define right 1
#define left 2
#define down 3
#define up 4
using namespace std;
class Touch
{
    
     int touch_fd;
    static Touch _touch;
    
    Touch(const Touch &) = delete;
    Touch &operator=(const Touch &) = delete; // 禁止赋值
public:
 
    Touch();
 
    static Touch & GetTouch();
    void  slide_touch(int & touch_zhuangtai,int &r_x,int &r_y);//,int &r_x,int &r_y
    ~Touch();

};

#endif