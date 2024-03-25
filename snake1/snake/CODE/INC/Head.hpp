//蛇头的类  继承自Sharp
#ifndef __HEAD_HPP__
#define __HEAD_HPP__

#include "Sharp.hpp"
#include "lcd.hpp"


//如果你的游戏里面只有一条蛇 这条蛇就是单例
class Head : public Sharp
{
	int _r;//蛇头是一个圆  有半径   圆心可以在基类里面的左上角坐标搞定
	LcdSingle & _lcd;//显示是需要lcd屏幕
public:
	Head(int x,int y,unsigned int color);
	virtual void Display();
	virtual void Clean();
};




#endif

