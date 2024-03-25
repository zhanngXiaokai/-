#include "touch.hpp"

Touch Touch::_touch;

Touch::Touch()
{
    touch_fd = open("/dev/input/event0", O_RDWR);
}

Touch &Touch::GetTouch()
{
    return _touch;
}

void Touch::slide_touch(int &touch_zhuangtai,int &r_x,int &r_y )//,int &r_x,int &r_y
{
       
   
    int x = -1, y = -1, x0 = -1, y0 = -1;
    while (1)
    {
        struct input_event ev;
      read(touch_fd, &ev, sizeof(ev));

        // cout << ev.type << "  " << ev.code << "  " <<  ev.value << endl;
        if (ev.type == 0x03)
        {
            if (ev.code == 0x00)
                x = ev.value;
            else if (ev.code == 0x01)
                y = ev.value;
        }
        if (ev.code == 0x14a && ev.value == 0x01)
        {
            x0 = x;
            y0 = y;
        }
        else if (ev.code == 0x14a && ev.value == 0x00)
        {
            if (x == x0 && y == y0)
            {
                  
                cout << "click:\n";
                touch_zhuangtai = 0;
                r_x=x0*(1.0*800/1024);
                r_y=y0*(1.0*480/600);
          
            }
            if (x > x0 && abs(x - x0) >= abs(y - y0))
            {
                cout << "right\n";
                touch_zhuangtai = right;
            }
            else if (x < x0 && abs(x - x0) >= abs(y - y0))
            {
                cout << "left\n";
                touch_zhuangtai = left;
            }
            else if (y > y0 && abs(x - x0) < abs(y - y0))
            {
                cout << "down\n";
                touch_zhuangtai = down;
            }
            else
            {
                cout << "up\n";
                touch_zhuangtai = up;
            }
        }
    }

}

Touch::~Touch()
{
    close(touch_fd);
}
