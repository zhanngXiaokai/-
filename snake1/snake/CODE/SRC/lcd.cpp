#include "lcd.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <iostream>

//工程里面用的都是这个实例
LcdSingle LcdSingle::_lcd;


//lcd的构造
LcdSingle::LcdSingle()
{
    this ->_fd = :: open("/dev/fb0",O_RDWR);
    if(-1 == this ->_fd)
    {

        throw std :: runtime_error("open fb0 error");
    }
    this ->_plcd = (unsigned int *) :: mmap(NULL,
                                        800 * 480 *4,
                                        PROT_READ | PROT_WRITE,
                                        MAP_SHARED,
                                        _fd,
                                        0);
    if(MAP_FAILED == this ->_plcd)
    {
        throw std :: runtime_error("mmap fb0 error");
    }
                                        
}
//获取lcd单例
LcdSingle & LcdSingle::GetLcd()
{
    return _lcd;
}

//显示
void LcdSingle::Display(int x,int y,unsigned int color)
{
    if(x >= 0 && x < 800 && y >= 0 && y <480)
        *(this ->_plcd + x + y * 800) = color;
}

//将屏幕刷新一个颜色
void LcdSingle::Display_color(unsigned int color)
{
	for(int y = 0;y < 480;y++)
	{
		for(int x = 0;x < 800;x++)
		{
			Display(x,y,color);
		}
	}
}

void LcdSingle::GameEnd(){
    Display_color(0xffffff);
    for(int y=180;y<380;y++){
        for(int x=200;x<600;x++){
            if(x>250&&x<550&&y>230&&y<330){
                continue;
            }else
            {
                Display(x,y,0xff00ff);
            }
        }
    }
    


}

LcdSingle::~LcdSingle()
{
    :: munmap(this ->_plcd,800 * 480 * 4);
    :: close(this ->_fd);
}


