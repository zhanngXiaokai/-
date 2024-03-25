#include <iostream>
#include <unistd.h>
#include <thread>
#include <chrono>
#include "ForwardList.hpp"
#include "Game.hpp"
#include "lcd.hpp"
#include <cstdio>
#include <deque>
#include <thread>
#include <touch.hpp>
#include <mutex>
#include <login.hpp>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <word_mode.hpp>
using namespace std;

int start(int &read_x, int &read_y, int &touch_zhuangtai, login &_login);

int main()
{

	try
	{
		cout << __LINE__ << endl;
	start: //
		/* 1，创建套接字 */
		int sockfd = socket(AF_INET, SOCK_STREAM, 0);
		cout << __LINE__ << endl;
		if (sockfd == -1)
		{
			perror("Create socket failed");
			return -1;
		}
		/* 2，发起连接请求 */

		// 配置服务的的地址信息
		struct sockaddr_in server_info;
		server_info.sin_family = AF_INET;
		server_info.sin_port = htons(6666);
		server_info.sin_addr.s_addr = inet_addr("172.90.1.13");
		// 连接服务器
		cout << __LINE__ << endl;
		int con_fd = connect(sockfd, (struct sockaddr *)&server_info, sizeof(server_info));
		if (con_fd == -1)
		{
			perror("Connect server failed");
			close(sockfd);
			return -1;
		}
		cout << "连接成功   " << __LINE__ << endl;
		// pid_t pid = fork();
		// if (pid == 0)
		//{
		login *_login = new login();
		int touch_zhuangtai = -1, read_x = 0, read_y = 0;
		int flag = 1;
		thread th{&Touch::slide_touch, &Touch::GetTouch(), std ::ref(touch_zhuangtai), std::ref(read_x), std::ref(read_y)};
		// int ret;
		// char _send[1024];
		char a[10] = {0};
		cout << __LINE__ << endl;
		while (1)
		{
			if (read_x > 250 && read_x < 350 && (read_y > 280 && read_y < 340)) // 登录
			{
				cout << __LINE__ << endl;
				a[0] = '1'; // 登录
				send(sockfd, (void *)a, 10, 0);
				break;
			}
			else if (read_x > 450 && read_x < 550 && (read_y > 280 && read_y < 340)) // 注册
			{
				cout << __LINE__ << endl;
				a[0] = '2'; // 注册
				send(sockfd, (void *)a, 10, 0);
				break;
			}
		}
		cout << __LINE__ << endl;
		memset(a, 0, 10); // 清空为0
		// sleep(1);
		// read(sockfd,a, 2);	//不阻塞
		recv(sockfd, a, 10, 0); // 等待服务器发送已经收到信息命令 接收
		cout << "recv ==3?  " << a[0] << endl;
		if (a[0] != '3')
		{
			cout << " error" << endl;
			close(sockfd);
			goto start;
		}
		cout << __LINE__ << endl;
		while (1)
		{
			cout << __LINE__ << endl;
			for (int i = 0; i < 3; i++) // 输入账号到数组
			{
				read_x = read_y = 0;
				cout << __LINE__ << endl;
				a[i] = _login->get_num(read_x, read_y);
				cout << a[i] << endl;
				cout << "a[i]   " << a[i] << "  ---  " << __LINE__ << endl;
				// 取子摸
				char* re=&a[i];
				_login->lcd_draw_word(dig[atoi(re)], 350 + i * 48,100,24,35,0x00c78C);
			
				cout << __LINE__ << endl;
			}
		
			a[4]='\0';
			cout << __LINE__ << endl;
			send(sockfd, (void *)a, 10, 0); // 发送账号
			cout << __LINE__ << endl;
			recv(sockfd, (void *)a, 10, 0);
			cout << a[0] << endl;
			memset(a, 0, 10); // 清空为0
			char b[10];
			for (int i = 0; i < 3; i++) // 输入密码到数组
			{
				read_x = read_y = 0;
				b[i] = _login->get_num(read_x, read_y);
			char* re=&b[i];
					_login->lcd_draw_word(dig[atoi(re)], 350 + i * 48,200,24,35,0x00c78C);
			}
				b[3]='\0';
				cout<<b[0]<<b[1]<<b[2]<<endl;
			cout << __LINE__ << endl;
			send(sockfd, (void *)b, 10, 0); // 发送密码

			memset(a, 0, 10);
			cout << __LINE__ << endl;
			recv(sockfd, (void *)a, 10, 0); // 等待服务端发送接收信息，账号密码是否正确
			cout << __LINE__ << endl;
			if (a[0] == 'y')
			{ // 正确返回y
				cout << __LINE__ << endl;
				break;
			}
			else if (a[0] == 'n')
			{ // 错误则继续输入
				memset(a, 0, 10);
				cout << __LINE__ << endl;
				continue;
			}
			else
			{
				cout << "a[0] error:  " << a[0] << endl;
				continue;
			}
		}
		// fget(_send, 1024, stdin);
		// _send[] = _login->show_num_mode(read_x, read_y);
		// ret = send(con_fd, _send, 1023, 0);
		// char buf[512] = {0};
		// read(con_fd, buf, 512);
		// printf("服务器消息:%s\n", buf);
		cout << __LINE__ << endl;
		int start_rs = start(read_x, read_y, touch_zhuangtai, *_login);
		if (start_rs == 1)
		{
			cout << __LINE__ << endl;
			start(read_x, read_y, touch_zhuangtai, *_login);
		}
		else if (start_rs == 2)
		{
			cout << __LINE__ << endl;
			goto start;
		}
		//}
	}
	catch (std ::runtime_error &w)
	{
		cerr << w.what();
		perror(" ");
	}
}
int start(int &read_x, int &read_y, int &touch_zhuangtai, login &_login)
{
	Gameclass gls;
	int temp;
	gls.Display();
	while (1)
	{
		if (touch_zhuangtai != -1)
		{
			temp = touch_zhuangtai;
			touch_zhuangtai = -1;
		}

		if (temp == right)
			gls.Move_right();
		else if (temp == left)
			gls.Move_left();
		else if (temp == down)
			gls.Move_down();
		else if (temp == up)
			gls.Move_up();
		if (gls.Snake_Myself() || gls.Snake_qiangbi())
		{
			int rs = gls.end_index(read_x, read_y);
			if (rs == 1)
			{
				return 1;
			}
			else if (rs == 2)
			{
				return 2;
			}
		}
		cout << __LINE__ << endl;
		_login.lcd_draw_num(gls.show_fenshu(), 10, 10, 0x792c97);
	}
	while (1)
	{
	}

	return 0;
}