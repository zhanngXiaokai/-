#include "Sharp.hpp"



Sharp::Sharp(int x,int y,int color):_x(x),_y(y),_color(color)
{
	
}

void Sharp::Set_x_y(int x,int y)
{
	this ->_x = x;
	this ->_y = y;
}
int Sharp::Get_x() const
{
	return this ->_x;
}
int Sharp::Get_y() const
{
	return this ->_y;
}
unsigned int Sharp::Get_color() const
{
	return this ->_color;
}
