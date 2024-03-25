#ifndef __BMP_HPP__
#define __BMP_HPP__
#include <lcd.hpp>
#include <string>
namespace std
{

    class BmpPictureClass
    {
        int w,h;
        unsigned char  * color = nullptr;//缓存空间
        LcdSingle &_lcd; // 显示是需要lcd屏幕
    public:
        BmpPictureClass();

        //图片的初始化
        void BmpInit(const string pathname);

        void Display(int x0 = 0,int y0 = 0);//将这个图片放在x y这个坐标上面

        ~BmpPictureClass();
    };


}
int GetBmpPicture(const std :: string path,std :: BmpPictureClass * bp,int n);

#endif