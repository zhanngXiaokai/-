#include "Head.hpp"
#include <math.h>

Head::Head(int x,int y,unsigned int color):Sharp(x,y,color),_r(10),_lcd(LcdSingle::GetLcd())
{
	
}
//头部的清除没有什么功能
void Head::Clean()
{
	
}
void Head::Display()
{
	int x0 = Get_x() + 10;
	
	int y0 = Get_y() + 10;//圆心
		
	for(int y = y0 - 10;y <  y0 + 10;y++)
	{
		for(int x = x0 - 10;x < x0 + 10;x++)
		{
			if(pow(x - x0,2) + pow(y - y0,2) <= pow(this ->_r,2))			
			{
				this ->_lcd.Display(x,y,Get_color());
			}
		}
	}
	
	
}
