#include "login.hpp"
#include "word_mode.hpp"
#include <string>
#include <bmp.hpp>
#include <unistd.h>
#include <iostream>

login::login() : _lcd(LcdSingle::GetLcd())
{

    // LcdSingle::GetLcd().lcd_clear();                                          // 清屏
    this->_lcd.Display_color(0xAEEEEE); // 刷屏
    std ::BmpPictureClass bp[4];
    bp[0].BmpInit("./log.bmp");
    bp[1].BmpInit("./res.bmp");
    bp[2].BmpInit("./jianpan.bmp");
    bp[0].Display(250, 280);
    bp[1].Display(450, 280);
    bp[2].Display(0, 400);

    lcd_draw_word(word2[0], 250, 60, 24, 24, 0xEE4000);  // 帐
    lcd_draw_word(word2[1], 300, 60, 24, 24, 0xEE4000);  // 号
    lcd_draw_word(word2[2], 250, 180, 24, 24, 0xEE4000); // 密
    lcd_draw_word(word2[3], 300, 180, 24, 24, 0xEE4000); // 码

    for (int y = 60; y < 140; y++) // 账号输入框
    {
        for (int x = 350; x < 600; x++)
        {
            this->_lcd.Display(x, y, 0xFFB6C1);
        }
    }
    for (int y = 180; y < 260; y++) // 密码输入框
    {
        for (int x = 350; x < 600; x++)
        {
            this->_lcd.Display(x, y, 0xFFB6C1);
        }
    }
}

// 调用这个函数就可以在指定的位置显示一个指定的文字
// buf:你要显示的这个文字的字模信息
//(x0,y0):文字的起始位置
//(w,h):文字的大小
void login::lcd_draw_word(char *buf, int x0, int y0, int w, int h, int color)
{
    int x, y, i;
    for (y = 0; y < h; y++) // 当前文字有h行
    {
        for (x = 0; x < (w / 8); x++) // 当前文字每一行w个点,需要w/8个字节
        {
            // 解析buf[y*(w/8))+x]表示的这个字节的8个bit
            for (i = 7; i >= 0; i--)
            {
                if (buf[y * (w / 8) + x] & (1 << i))
                {
                    // ch的第i个bit是1,显示一个颜色
                    this->_lcd.Display(8 * x + 7 - i + x0, y + y0, color);
                    //  lcd_darw_point(); // 字体颜色
                }
            }
        }
    }
}

// 可以在指定的位置显示一个指定的数字
void login::lcd_draw_num(int num, int x0, int y0, int color)
{
    // 所有的数字都是由0~9十个数字组成的
    // 逐个的取出num的每一个数值位并且显示
    // 取出num的每一个数值位
    int y = num;
    int x = 0; // 表示是几位数
    while (y)
    {
        x++;
        y = y / 10;
    }
    // 调用上面的函数显示单独的数值位
    for (int i = 0; i < x; i++)
    {

        lcd_draw_word(dig[num % 10], x0 + (24 - 24 * (i)), y0, 24, 35, color);
        num = num / 10;
    }
}

string login::GetusernameAndpassword()
{
    return username + password;
}




// void login::setusername(int num){
//     this->username+1;
// }

// int login::show_num_mode(int &x, int &y)
// {

//     string mm;
//     int re[6];

// B:
//     for (int i = 0; i < 6; i++)
//     {

//         while (x == 0)
//         {
//         }
//         re[i] = get_num(x, y);
//         // cout<<x<<endl;
//         x = 0;
//         // sleep(1);
//         std::cout << re[i] << std::endl;
//         string str = to_string(re[i]);
//         mm += str;
//         if (i < 3)
//         {
//             // cout <<"re" <<re[i] << endl;
//             lcd_draw_word(dig[re[i]], 350 + i * 48, 100, 24, 35, 0x00c78C);
//         }
//         else
//         {
//             lcd_draw_word(dig[re[i]], 350 + (i - 3) * 48, 200, 24, 35, 0x00c78C);
//         }
//     }

//     cout << mm << endl;
//     // if(_login->Getusername()=="123"&&_login->Getusername() =="123")
//     while (1)
//     {
//         if (x > 250 && x < 350 && (y > 280 && y < 340)) // 获取手指点击坐标
//         {
//             if (this->GetusernameAndpassword() == mm)
//             {
//                 return 0;
//             }
//             else
//             {
//                 for (int y = 60; y < 140; y++) // 账号输入框
//                 {
//                     for (int x = 350; x < 600; x++)
//                     {
//                         this->_lcd.Display(x, y, 0xFFB6C1);
//                     }
//                 }
//                 for (int y = 180; y < 260; y++) // 密码输入框
//                 {
//                     for (int x = 350; x < 600; x++)
//                     {
//                         this->_lcd.Display(x, y, 0xFFB6C1);
//                     }
//                 }
//                 for (int i = 0; i < 6; i++)
//                 {
//                     re[i] = 0;
//                 }
//                 goto B;
//             }
//         }
//     }
// }

char login::get_num(int &x,int &y)// x,y是手指点击触摸屏坐标，返回所点击数字
{
    while (1)
    {
        if (y > 400)
        {
            int temp;
            temp = x / 80;
            char s ;
            cout<<"----"<<temp<<endl;
            // this->lcd_draw_word(dig[temp],)   //	_login->lcd_draw_num(a[i], 350 + i * 48, 100, 0x00c78C);
            s = temp +'0';
            cout<<"----"<<s<<endl;
            return s;
        }
    }
}