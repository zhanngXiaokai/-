//这是一个图形基类
#ifndef __SHARP_HPP__
#define __SHARP_HPP__


//抽象类 不能实例化
class Sharp
{
	unsigned int _color;
	int _x,_y;
public:
	Sharp(int x,int y,int color);
	virtual void Display() = 0;//显示的纯虚函数
	virtual void Clean() = 0;//清除
	void Set_x_y(int x,int y);
	int Get_x() const;
	int Get_y() const;
	unsigned int Get_color() const;
	
};








#endif


