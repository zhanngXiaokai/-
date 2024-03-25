#ifndef __LCD_HPP__
#define __LCD_HPP__



//lcd单例
class LcdSingle
{
    int _fd;
    unsigned int * _plcd = nullptr;
    static LcdSingle _lcd;
    LcdSingle();
    LcdSingle(const LcdSingle &) = delete;//禁止拷贝
    LcdSingle & operator=(const LcdSingle &) = delete;//禁止赋值
public:
    static LcdSingle & GetLcd();
    void Display(int x,int y,unsigned int color);
	//将屏幕刷新一个颜色
	void Display_color(unsigned int color);
    void GameEnd();
    void index();
    ~LcdSingle();
};




#endif


