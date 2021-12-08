#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/select.h>

#include <iostream>

using namespace std;

/*
 * 利用select解决单线程下TCP的accept阻塞和recv阻塞问题
 * 同时将0号文件描述符和socket文件描述符设置到readfds事件集合中。
 * 监控0号文件描述符和sock文件描述符是否有可读事件发生
 */ 

int main()
{
    //服务端--创建套接字、绑定地址信息、监听连接、数据收发
    int listen_fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(listen_fd < 0)
    {
        perror("socket");
        return 0;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(18989);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    int ret = bind(listen_fd,(struct sockaddr *)&addr,sizeof(addr));
    if(ret < 0)
    {
        perror("bind");
        close(listen_fd);
        return 0;
    }

    ret = listen(listen_fd,5);
    if(ret < 0)
    {
        perror("listen");
        close(listen_fd);
        return 0;
    }

    //设置事件集合
    fd_set readfds;
    __FD_ZERO(&readfds);
    __FD_SET(0,&readfds);
    __FD_SET(listen_fd,&readfds);

    while(1)
    {
        fd_set tmp = readfds;
        int fd_num = select(listen_fd + 1,&tmp,NULL,NULL,NULL);
        if(fd_num < 0)
        {
            perror("select");
            return 0;
        }

        if(__FD_ISSET(0,&tmp))
        {
            cout << "0 in readfds" << endl;
            char buf[1024] = {0};
            read(0,buf,sizeof(buf)-1);
            printf("%s\n",buf);
        }
        else if(__FD_ISSET(listen_fd,&tmp))
        {
            cout << "newSockfd in readfds" << endl;
            int new_sockfd = accept(listen_fd,NULL,NULL);
            printf("new_sockfd is : %d\n",new_sockfd);
        }
    }
    return 0;
}
