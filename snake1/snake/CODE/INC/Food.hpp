#ifndef __FOOD_HPP__
#define __FOOD_HPP__
#include "Sharp.hpp"
#include "lcd.hpp"

class Food :public Sharp{
    int _w=20,_h=20;
    LcdSingle & _lcd;//显示是需要lcd屏幕
    public:
    Food(int x,int y,unsigned int color);
    void Clean();
    ~Food();
    void Display();
};




#endif