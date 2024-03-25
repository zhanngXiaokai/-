/*
    这是图片类的基类
*/
#ifndef __PICTURE_HPP__
#define __PICTURE_HPP__



class Picture
{
protected:
    int _w,_h;//宽高
    unsigned int * _color = nullptr;//缓存数组
public:
    
    virtual void Display(int x0 = 0,int y0 = 0) = 0;

    virtual ~Picture() = default;
};




#endif

