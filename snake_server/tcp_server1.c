#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/socket.h>
#include <sqlite3.h>


int login(char* username, char* password);
int sigin(char* username, char* password);
int create_socket(char *ipstr, short port);


// 子进程处理tcp_client收消息
void handle_tcp_client(int conn_fd)
{
    int ret;
    char buf[1024] = {0};
    char buf2[10] = {0};
    while (1)
    {
        memset(buf, 0, sizeof(buf));
        ret = recv(conn_fd, buf, 1023, 0);
        if (ret > 0)
        {
            printf("recv data: %s\n", buf);
            buf2[0] = '3'; // 表示收到来自客户端请求；
            send(conn_fd, buf2, ret, 0);
            char username[20];
            char password[20];
            if (buf[0] == '1')
            {
                // 登录
                while (1)
                {
                    memset(username,0,sizeof(username));
                    memset(password,0,sizeof(password));
                    recv(conn_fd, username, 10, 0);
                    send(conn_fd, "abce", 5, 0);
                    recv(conn_fd, password, 10, 0);
                    printf("username :%s\n",username);
                    printf("password :%s\n",password);
                    int r = login(username, password);
                    if (r == 1)
                    {
                        // 正常登入     
                        char s[10] = {0};
                        s[0] = 'y';
                        send(conn_fd, s, 10, 0);
                        break;
                    }
                    else if (r == -2)
                    {
                        char s[10] = {0};
                        s[0] = 'n';
                        send(conn_fd, s, 10, 0);
                        continue;
                        // 账号，密码错误
                    }
                    else {
                            break;
                    }
                }
            }
            else if (buf[0] == '2')
            {
                // 注册
                memset(username,0,sizeof(username));
                memset(password,0,sizeof(password));
                recv(conn_fd, username, 10, 0);
                send(conn_fd, "abce", 5, 0);
                recv(conn_fd, password, 10, 0);
                printf("%s--------%s\n",username, password);
                sigin(username,password);
                send(conn_fd, "yes", 4, 0);
            }
        }

        // send(conn_fd,buf,ret,0);
    }
}

/*
 创建一个准备好的套接字
 ipstr:ip的点分式字符串
 port:端口号
*/
int create_socket(char *ipstr, short port)
{
    // 1.创建套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("socket error\n");
        return -1;
    }

    // 2.指定服务器
    struct sockaddr_in serv;
    serv.sin_family = AF_INET; // 指定协议族
    // serv.sin_port = htons(6666);//指定端口号
    serv.sin_port = htons(port);
    // serv.sin_addr.s_addr = inet_addr("172.3.1.227");
    serv.sin_addr.s_addr = inet_addr(ipstr);

    int ret;
    ret = bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));
    if (ret == -1)
    {
        perror("bind error\n");
        close(sockfd);
        return -1;
    }

    // 3.进入监听
    ret = listen(sockfd, 10);
    if (ret == -1)
    {
        perror("listen erroe\n");
        close(sockfd);
        return -1;
    }
    return sockfd;
}


int sigin(char* username, char* password)
{
    sqlite3 *pdb;
    int r = sqlite3_open("./snakeuser.db", &pdb);
    if (r != SQLITE_OK)
    {
        // perror("");//用 perror不合适了，因为该函数失败不会设置错误
        printf("打开数据库文件失败,r=%d\n", r); // 打印出返回值，根据返回值去 sqlite3.h 中查询原因
        return -1;
    }

    char buf[100];
    printf("%s--------%s\n",username, password);
    sprintf(buf, "insert into USER values(%s,%s);", username, password);
    printf("buf = %s\n",buf);
    // printf("%s",buf);
    sqlite3_stmt *pStmt;
    r = sqlite3_prepare_v2(pdb, buf, strlen(buf), &pStmt, NULL);

    if (r != SQLITE_OK)
    {
        // perror("");//用 perror不合适了，因为该函数失败不会设置错误
        printf("准备SQL语句对象失败,r=%d\n", r); // 打印出返回值，根据返回值去 sqlite3.h 中查询原因
        sqlite3_close(pdb);
        return -1;
    }

    r = sqlite3_step(pStmt);
    if (r == SQLITE_DONE)
    {
        printf("执行sql语句成功\n");
    }
    else
    {
        printf("执行sql语句失败,r=%d\n", r);
    }

    sqlite3_finalize(pStmt);

    sqlite3_close(pdb);
}

int login(char* username, char* password)
{
    int flag = -1;
    sqlite3 *pdb;
    int r = sqlite3_open("./snakeuser.db", &pdb);
    if (r != SQLITE_OK)
    {
        // perror("");//用 perror不合适了，因为该函数失败不会设置错误
        printf("打开数据库文件失败,r=%d\n", r); // 打印出返回值，根据返回值去 sqlite3.h 中查询原因
        return -1;
    }

    char buf[100];
    sprintf(buf, "select* from USER where username=%s AND password = %s;", username, password);
    // printf("%s",buf);
    sqlite3_stmt *pStmt;
    r = sqlite3_prepare_v2(pdb, buf, strlen(buf), &pStmt, NULL);

    if (r != SQLITE_OK)
    {
        //flag = 0;
        // perror("");//用 perror不合适了，因为该函数失败不会设置错误
        printf("准备SQL语句对象失败,r=%d\n", r); // 打印出返回值，根据返回值去 sqlite3.h 中查询原因
        // printf("登录名与密码不匹配\n");
        sqlite3_close(pdb);
        return -1;
    }

    int count; // 保存查询到的字段个数
    while (1)
    {
        r = sqlite3_step(pStmt);
        if (r == SQLITE_DONE)
        {
            flag=1;

            break;
        }
        else if (r == SQLITE_ROW)
        {
            // 处理该条记录
            flag = 0;
            count = sqlite3_column_count(pStmt);
            printf("字段个数:%d\n", count);
        }
        else
        {
            printf("执行sql语句失败,r=%d\n", r);
            flag=-2;
        }
    }

    sqlite3_finalize(pStmt);

    sqlite3_close(pdb);
    return flag;
}

int main(int argc, char *argv[])
{
    int sockfd = create_socket(argv[1], atoi(argv[2]));
    if (sockfd == -1)
    {
        printf("failed to create_socket\n");
        return -1;
    }

    // 4.接受客户端的连接请求
    while (1)
    {
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        int conn_fd = accept(sockfd, (struct sockaddr *)&client, &len);
        if (conn_fd == -1)
        {
            perror("accept error\n");
            close(conn_fd);
        }
        // char* inet_ntoa(struct in_addr in);
        printf("%s port : [%d] connection established\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        pid_t pid = fork();
        if (pid == 0)
        {
            handle_tcp_client(conn_fd);
            //write(conn_fd, "hello", 5);
            // 处理客户端信息
        }
        else if (pid > 0)
        {
            wait(NULL);
            close(sockfd);
        }
        else
        {
            close(conn_fd);
            perror("fork error\n");
            continue;
        }
    }

    // 5.收发数据
    // write(conn_fd,"hello");

    // 6.关闭
     //close(conn_fd);
     return 0;
}