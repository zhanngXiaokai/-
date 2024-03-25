#include "Body.hpp"

Body::Body(int x,int y,unsigned int color):Sharp(x,y,color),_w(20),_h(20),
												_lcd(LcdSingle::GetLcd())
{
	
}

//清除身体这一节
void Body::Clean()
{
	for(int y = Get_y();y < Get_y() + 20;y++)
	{
		for(int x = Get_x();x < Get_x() + 20;x++)		
		{
			this ->_lcd.Display(x,y,0xffffff);
		}
	}
}


void Body::Display()
{
	for(int y = Get_y();y < Get_y() + 20;y++)
	{
		for(int x = Get_x();x < Get_x() + 20;x++)		
		{
			this ->_lcd.Display(x,y,Get_color());
		}
	}
}


