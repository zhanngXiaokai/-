// 游戏类
#ifndef __GAME_HPP__
#define __GAME_HPP__
#include <iostream>
#include <list>
#include <vector>
#include "Sharp.hpp"
#include "Body.hpp"
#include "Head.hpp"
#include "Food.hpp"
#include <vector>
#include"bmp.hpp"
using std::list;
using std::vector;
class Gameclass
{
	list<Sharp *> _snake;
	vector<Food *> _food;
	LcdSingle & _lcd;
public:
	Gameclass();			//初始化蛇
						
	void Display();			//画节点	// 刷新这个蛇身
	void CleanWeiba();		//清除尾部
	bool Snake_Myself();	//是否碰到自己
	bool Snake_qiangbi();	//是否碰到障碍
	void Jum();				//跳跃		200 *240 跳 600 *240  ，400*120 跳 400*360 
	void Move_right(void);	//向右
	void Move_left(void);	//向左
	void Move_up(void);		//向上
	void Move_down(void);	//向下
	bool eat_Food(void);
	void init_food();
	int show_fenshu();
	int end_index(int &x,int &y);
	void clear_snake();
};

#endif
