#include <Food.hpp>
#include <lcd.hpp>
Food::Food(int x, int y, unsigned int color):Sharp(x, y, color),_lcd(LcdSingle::GetLcd())
{

}

void Food::Display()
{
    for (int y = Get_y(); y < Get_y() + _h; y++)
    {
        for (int x = Get_x(); x < Get_x() + _w; x++)
        {
            this->_lcd.Display(x, y, Get_color());
        }
    }
}
void Food::Clean()
{
    for (int y = Get_y(); y < Get_y() + _h; y++)
    {
        for (int x = Get_x(); x < Get_x() + _w; x++)
        {
            this->_lcd.Display(x, y, 0xffffff);
        }
    }
}
Food::~Food()
{
}

