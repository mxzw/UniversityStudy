#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "SelectHead.hpp"

using namespace std;

/*
 * 利用select解决单线程下TCP的accept阻塞和recv阻塞问题
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
    SelectHead sh;
    sh.Set(listen_fd);

    while(1)
    {
        vector<int> iv;
        int fd_num = sh.SelectWait(iv);
        if(fd_num < 0)
        {
            continue;
        }

        for(int i = 0; i < iv.size(); ++i)
        {
            if(iv[i] == listen_fd)
            {
                cout << "new connect" << endl;
                //表明接收到了新连接
                int newSock_fd = accept(iv[i],NULL,NULL);
                if(newSock_fd < 0)
                {
                    perror("newSock_fd");
                    continue;
                }
                
                sh.Set(newSock_fd);
            }
            else 
            {
                cout << "data recv" << endl;
                //表示是数据之间的收发
                char buf[1024] = {0};

                ssize_t recv_size = recv(iv[i],buf,sizeof(buf)-1,0);
                if(recv_size < 0)
                {
                    perror("recv");
                    continue;
                }
                else if(recv_size == 0)
                {
                    cout << "peer shutdown" << endl;
                    sh.Del(iv[i]);
                    close(iv[i]);
                    continue;
                }
                else
                {
                    printf("recv is : %s\n",buf);
                }
            } 
        }
    }

    close(listen_fd);
    return 0;
}
