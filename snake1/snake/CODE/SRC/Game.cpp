#include "Game.hpp"

#include <unistd.h>

using namespace std;
Gameclass::Gameclass() : _lcd(LcdSingle::GetLcd())
{
	// 构造四节
	_snake.push_front(new Head(200, 100, 0xff0000)); // 蛇头
	_snake.push_back(new Body(180, 100, 0xff));		 // 蛇身体
	_snake.push_back(new Body(160, 100, 0xff));		 // 蛇身体
	_snake.push_back(new Body(140, 100, 0xff));		 // 蛇身体
	init_food();
	this->_lcd.Display_color(0xffffff); // 将屏幕刷白
}

void Gameclass::init_food()
{
	for (int i = 0; i < 4; i++)
	{
		int x = rand() % 780;
		int y = rand() % 460;
	A:
		for (auto it : _snake) //
		{

			if (it->Get_x() >= x - 20 && it->Get_x() <= x + 20 &&
				it->Get_y() <= y - 20 && it->Get_y() >= y + 20) // 在蛇身上
			{
				int x = rand() % 780;
				int y = rand() % 460;
				goto A;
			}
		}
		_food.push_back(new Food(x, y, 0xff0000)); // 四个food
	}
}

void Gameclass::Display()
{
	for (auto it : _snake)
	{
		it->Display();
	}
	for (auto it : _food)
	{
		it->Display();
	}
}

void Gameclass::CleanWeiba()
{
	auto it = this->_snake.back();
	it->Clean();
}

void Gameclass::Move_right(void)
{

	// Jum();

	// if (Snake_Myself() || Snake_qiangbi())
	// {

	// 	//exit(0);
	// }

	CleanWeiba();
	int x = 0, y = 0, x0 = 0, y0 = 0; // x0,y0 是上一节的老坐标
	for (auto it : _snake)
	{

		x0 = x; // 保存没有走之前的坐标
		y0 = y;
		x = it->Get_x();
		y = it->Get_y();
		if (it == *this->_snake.begin())
		{
			it->Set_x_y(x + 20, y);
		}
		else
		{
			it->Set_x_y(x0, y0); // 跟随前面一节
		}
		if (show_fenshu() < 10)
		{
			usleep(30000);
		}
		else if (show_fenshu() < 20)
		{
			usleep(20000);
		}
		else
			usleep(15000);
	}
	if (eat_Food())
	{
		auto it1 = _snake.rbegin();
		int last_x = (*it1)->Get_x();
		int last_y = (*it1)->Get_y();
		_snake.push_back(new Body(last_x - 20, last_y, 0xff));
	}
	Display();
}

void Gameclass::Move_left(void)
{ // 向左
	//  Jum();

	// if (Snake_Myself() || Snake_qiangbi())
	// {
	// 	exit(0);
	// }
	CleanWeiba();
	int x = 0, y = 0, x0 = 0, y0 = 0; // x0,y0 是上一节的老坐标
	for (auto it : _snake)
	{
		x0 = x; // 保存没有走之前的坐标
		y0 = y;
		x = it->Get_x();
		y = it->Get_y();
		if (it == *this->_snake.begin())
		{
			it->Set_x_y(x - 20, y);
		}
		else
		{
			it->Set_x_y(x0, y0); // 跟随前面一节
		}

		if (show_fenshu() < 10)
		{
			usleep(30000);
		}
		else if (show_fenshu() < 20)
		{
			usleep(20000);
		}
		else
			usleep(15000);
	}
	if (eat_Food())
	{
		auto it1 = _snake.rbegin();
		int last_x = (*it1)->Get_x();
		int last_y = (*it1)->Get_y();
		_snake.push_back(new Body(last_x + 20, last_y, 0xff));
	}
	Display();
}
void Gameclass::Move_up(void)
{ // 向上
	//  Jum();
	// if (Snake_Myself() || Snake_qiangbi())
	// {
	// 	exit(0);
	// }
	CleanWeiba();
	int x = 0, y = 0, x0 = 0, y0 = 0; // x0,y0 是上一节的老坐标
	for (auto it : _snake)
	{
		x0 = x; // 保存没有走之前的坐标
		y0 = y;
		x = it->Get_x();
		y = it->Get_y();
		if (it == *this->_snake.begin())
		{
			it->Set_x_y(x, y - 20);
		}
		else
		{
			it->Set_x_y(x0, y0); // 跟随前面一节
		}

		if (show_fenshu() < 10)
		{
			usleep(30000);
		}
		else if (show_fenshu() < 20)
		{
			usleep(20000);
		}
		else
			usleep(15000);
		usleep(30000);
	}
	if (eat_Food())
	{
		auto it1 = _snake.rbegin();
		int last_x = (*it1)->Get_x();
		int last_y = (*it1)->Get_y();
		_snake.push_back(new Body(last_x, last_y + 20, 0xff));
	}
	Display();
}
void Gameclass::Move_down(void)
{ // 向下
	//  Jum();
	// if (Snake_Myself() || Snake_qiangbi())
	// {
	// 	exit(0);
	// }
	CleanWeiba();
	int x = 0, y = 0, x0 = 0, y0 = 0; // x0,y0 是上一节的老坐标
	for (auto it : _snake)
	{
		x0 = x; // 保存没有走之前的坐标
		y0 = y;
		x = it->Get_x();
		y = it->Get_y();
		if (it == *this->_snake.begin())
		{
			it->Set_x_y(x, y + 20);
		}
		else
		{
			it->Set_x_y(x0, y0); // 跟随前面一节
		}

		if (show_fenshu() < 10)
		{
			usleep(30000);
		}
		else if (show_fenshu() < 20)
		{
			usleep(20000);
		}
		else
			usleep(15000);
	}
	if (eat_Food())
	{
		auto it1 = _snake.rbegin();
		int last_x = (*it1)->Get_x();
		int last_y = (*it1)->Get_y();
		_snake.push_back(new Body(last_x, last_y - 20, 0xff));
	}
	Display();
}

bool Gameclass::Snake_Myself()
{

	auto it = _snake.begin(); // 头
	for (auto it1 : _snake)
	{
		if (it1 == *it)
		{
			continue;
		}
		std::cout << it1->Get_x() << " " << it1->Get_y() << std::endl;
		if ((*it)->Get_x() == it1->Get_x() && (*it)->Get_y() == it1->Get_y())
		{
			return true;
		}
	}

	return false;
}

bool Gameclass::Snake_qiangbi() // 是否碰到障碍
{
	auto it = _snake.begin();
	if ((*it)->Get_x() + 20 > 800 || (*it)->Get_x() - 20 < 0 ||
		(*it)->Get_y() + 20 > 480 || (*it)->Get_y() - 20 < 0)
		return true;
	return false;
}

void Gameclass::Jum()
{ // 200 *240 跳 600 *240  ，400*120 跳 400*360

	for (auto it : _snake)
	{
		if (it->Get_x() == 200 && it->Get_y() == 240)
		{
			it->Set_x_y(600, 240);
		}
		else if (it->Get_x() == 600 && it->Get_y() == 240)
		{
			it->Set_x_y(200, 240);
		}
		else if (it->Get_x() == 400 && it->Get_y() == 120)
		{
			it->Set_x_y(400, 360);
		}
		else if (it->Get_x() == 400 && it->Get_y() == 360)
		{
			it->Set_x_y(400, 120);
		}
	}
}

bool Gameclass::eat_Food()
{
	auto head = _snake.begin();
	int x = (*head)->Get_x();
	int y = (*head)->Get_y();
	for (auto it : _food)
	{
		if (it->Get_x() >= x - 20 && it->Get_x() <= x + 20 &&
			it->Get_y() >= y - 20 && it->Get_y() <= y + 20)
		{
			it->Clean();
			it->Set_x_y(rand() % 780, rand() % 460);
			// auto it1= _snake.rbegin();
			// int last_x = (*it1)->Get_x();
			// int last_y = (*it1)->Get_y();
			// _snake.push_back(new Body(last_x,,0xff));
			return true;
		}
	}
	return false;
}

int Gameclass::show_fenshu()
{
	for(int y=10;y<50;y++)
	{
		for(int x=10;x<100;x++)
		{
			this->_lcd.Display(x,y,0xffffff);
		}
	}
	return (_snake.size()-4)*2;
}


int Gameclass::end_index(int &x, int &y)
{
	std ::BmpPictureClass bp;
	bp.BmpInit("./end.bmp");
	bp.Display(0, 0);
	while (1)
	{
		if(x>150&&x<300&&y>200&&y<400){
			//重新开始
			return 1;

		}else if(x>500&&y>200&&y<400){
			//退出到登录界面
			return 2;
		}
	}
}

void Gameclass::clear_snake()
{
	_snake.clear();
}
