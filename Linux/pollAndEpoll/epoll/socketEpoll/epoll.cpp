#include <unistd.h>
#include <sys/epoll.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
using namespace std;

int main()
{
    int listen_fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(listen_fd < 0)
    {
        cout << "socket failed" << endl;
        return 0;
    }
    
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(18989);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    int ret = bind(listen_fd,(struct sockaddr *)&addr,sizeof(addr));
    if(ret < 0)
    {
        cout << "bind failed" << endl;
        return 0;
    }
    
    ret = listen(listen_fd,5);
    if(ret < 0)
    {
        cout << "listen failed" << endl;
        return 0;
    }

    int handle = epoll_create(2);
    if(handle < 0)
    {
        cout << "epoll_create failed" << endl;
        return 0;
    }

    struct epoll_event ee;
    ee.events = EPOLLIN;
    ee.data.fd = listen_fd;

    ret = epoll_ctl(handle,EPOLL_CTL_ADD,listen_fd,&ee);
    if(ret < 0)
    {
        cout << "epoll_ctl failed" << endl;
        return 0;
    }

    while(1)
    {
        struct epoll_event arr[10];
        int n = sizeof(arr)/sizeof(arr[0]);
        ret = epoll_wait(handle,arr,n,-1);
        if(ret < 0)
        {
            cout << "epoll_wait failed" << endl;
            continue;
        }

        for(int i = 0; i < n; ++i)
        {
            if(arr[i].data.fd == listen_fd)
            {
                //表示接收到新连接
                int newSockfd = accept(arr[i].data.fd,NULL,NULL);
                if(newSockfd < 0)
                {
                    cout << "accept failed" << endl;
                    continue;
                }

                struct epoll_event nee;
                nee.events = EPOLLIN;
                nee.data.fd = newSockfd;
                ret = epoll_ctl(handle,EPOLL_CTL_ADD,newSockfd,&nee);
                if(ret < 0)
                {
                    cout << "epoll_ctl failed" << endl;
                    continue;
                }
            }
            else
            {
                //表示进行数据的收发
                char buf[1024] = {0};

                ssize_t recv_size = recv(arr[i].data.fd,buf,sizeof(buf)-1,0);
                if(recv_size < 0)
                {
                    cout << "recv failed" << endl;
                    continue;
                }
                else if(recv_size == 0)
                {
                    cout << "peer shutdown" << endl;
                    epoll_ctl(handle,EPOLL_CTL_DEL,arr[i].data.fd,NULL);
                    close(arr[i].data.fd);
                    continue;
                }
                else
                    printf("%s\n",buf);
            }
        }

    }
    close(listen_fd); 
    close(handle);
    return 0;
}
