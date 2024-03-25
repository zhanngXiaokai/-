#ifndef __LOGIN_HPP__
#define __LOGIN_HPP__
#include "lcd.hpp"
#include <string>
#include <bmp.hpp>
using namespace std;
class login
{
    string username = "123";
    string password = "123";
    LcdSingle &_lcd; // 显示是需要lcd屏幕
public:
    login();
    string GetusernameAndpassword();
    
    // 调用这个函数就可以在指定的位置显示一个指定的文字
    // buf:你要显示的这个文字的字模信息
    //(x0,y0):文字的起始位置
    //(w,h):文字的大小
    void lcd_draw_word(char *buf, int x0, int y0, int w, int h, int color);
    // 可以在指定的位置显示一个指定的数字
    void lcd_draw_num(int num, int x0, int y0, int color);
    char get_num(int &x,int &y);
    // int show_num_mode(int &x,int &y);
   
};

#endif