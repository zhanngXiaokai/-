/*
    代码里面我用系统io去操作文件，你们要换标准io
        或者后面有文件类的需求了，你们用文件类 -> 普通文件
*/
#include <iostream>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <thread>
#include <bmp.hpp>

// 构造函数
std ::BmpPictureClass ::BmpPictureClass() : _lcd(LcdSingle::GetLcd()) {}

// 图片的初始化
void std ::BmpPictureClass ::BmpInit(const string pathname)
{
    // 将路径拿到之后打开  缓存即可
    cout << "pathname: ---" << pathname << endl;
    int fd = ::open(pathname.c_str(), O_RDWR);
    if (-1 == fd)
    {
        throw std ::runtime_error("open bmp error");
    }

    lseek(fd, 0x12, SEEK_SET);
    read(fd, &w, 4); // 读宽
    read(fd, &h, 4); // 读高
   
    int depth = 0;
    lseek(fd, 0x1c, SEEK_SET);
    read(fd, &depth, 2);
   
    // cout << this ->w << " " << this ->h << " " << depth << endl;
  
    int n = (4 - this->w * depth / 8 % 4) % 4; // 每一行末尾补充的没有什么作用的字节
   
    // 读取像素数组
    // unsigned char * _color = new unsigned char[(this->w * depth / 8 + n) * this->h];
     int line_size = abs(w)*(h/8)+n;
     color  = (unsigned char * )malloc(abs(h)*line_size);
 
    lseek(fd, 0x36, SEEK_SET);
    read(fd, color, (this->w * depth / 8 + n) * this->h);
   
    // 给缓存分配空间
   // this->color = new unsigned int[this->w * this->h];
    // cout <<"  1 1 1   "<< __LINE__ << endl;
    int x, y;
    unsigned char ca = 0, cr, cg, cb;
    int i = 0;
    for (y = this->h - 1; y >= 0; y--)
    {
 
        for (x = 0; x < this->w; x++)
        {

            cb = color[i++];
            cg = color[i++];
            cr = color[i++];
            if (32 == depth)
            {
                ca = color[i++];
            }
          
            // 缓存
            this->color[y * this->w + x] = ca << 24 | cr << 16 | cg << 8 | cb;
          
        }
        i += n; // 跳过末尾的n个字节
    }

    // delete[] color;

    ::close(fd);
}

// 显示图片
void std ::BmpPictureClass ::Display(int x0, int y0) // 将这个图片放在x y这个坐标上面
{
    for (int y = 0; y < this->h; y++)
    {
        for (int x = 0; x < this->w; x++)
        {
            _lcd.Display(x + x0, y + y0, this->color[x + y * this->w]);
        }
    }
}

// 析构
std ::BmpPictureClass ::~BmpPictureClass()
{
    if (this->color != nullptr)
        delete[] this->color;
}

// std :: LcdClass :: LcdClass()
// {
//     this ->fd = ::open("/dev/fb0",O_RDWR);
//     if(-1 == this ->fd)
//     {
//         throw std :: runtime_error("open fb0 error");
//     }
//     this ->plcd = (unsigned int *):: mmap(NULL,
//                                             800 * 480 * 4,
//                                             PROT_READ | PROT_WRITE,
//                                             MAP_SHARED,
//                                             this ->fd,
//                                             0);
//     if(MAP_FAILED == this ->plcd)
//     {
//         throw std :: runtime_error("mmap fb0 error");
//     }
// }

// //画点
// void std :: LcdClass :: Display(int x,int y,unsigned int color)
// {
//     if(x >= 0 && x < 800 && y >= 0 && y < 480)
//     {
//         *(this ->plcd +  x + y * 800) = color;
//     }
// }

// std :: LcdClass :: ~LcdClass()
// {
//     :: munmap(this ->plcd,800 * 480 * 4);
//     :: close(this ->fd);
// }

#include <string.h>

// 返回找到的文件个数
int GetBmpPicture(const std ::string path, std ::BmpPictureClass *bp, int n)
{
    int i = 0;
    // 打开文件夹
    ::DIR *dirp = ::opendir(path.c_str());
    if (NULL == dirp)
    {
        throw std ::runtime_error("opendir error");
    }

    struct dirent *drt;

    while (drt = ::readdir(dirp))
    {
        // 过掉. ..
        if (!strcmp(drt->d_name, ".") || !strcmp(drt->d_name, ".."))
        {
            continue;
        }
        // 普通文件才需要去判断
        if (drt->d_type == ::DT_REG)
        {
            if (!strcmp(drt->d_name + strlen(drt->d_name) - 4, ".bmp"))
            {
                std ::cout << drt->d_name << "\n";
                bp[i++].BmpInit(drt->d_name);
                if (i >= n)
                    break; // 返回个数
            }
        }
    }

    return i;
}

// int main()
// {
//     try
//     {

//         using namespace std::chrono_literals;

//         std :: BmpPictureClass bp[10];

//         int n = :: GetBmpPicture("./",bp,10);

//         for(int i = 0;i < n;i++)
//         {
//             bp[i].Display();
//             std::this_thread::sleep_for(2s);

//         }

//         //bp.BmpInit("./1.bmp");

//         //bp.Display();
//     }
//     catch(std :: runtime_error & w)
//     {
//         std :: cout << w.what();
//         :: fflush(NULL);
//         :: perror(" ");
//     }
//     return 0;
// }
