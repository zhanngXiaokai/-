//蛇的身体类  继承自Sharp类

#ifndef __BODY_HPP__
#define __BODY_HPP__

#include "Sharp.hpp"
#include "lcd.hpp"

class Body : public Sharp
{
	int _w,_h;
	LcdSingle & _lcd;//显示是需要lcd屏幕
public:
	Body(int x,int y,unsigned int color);
	virtual void Display();
	virtual void Clean();
};







#endif
