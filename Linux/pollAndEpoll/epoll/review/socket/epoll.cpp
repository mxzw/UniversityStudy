#include <iostream>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
using namespace std;

#define MAXSIZE 2
#define Judge(x) if(x<0) {cout << "failed" << endl; return 0;}


int main()
{
    int lisnfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(lisnfd < 0)
    {
        cout << "socket failed" << endl;
        return 0;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(18989);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");

    int ret = bind(lisnfd,(struct sockaddr *)&addr,sizeof(addr));
    Judge(ret);

    ret = listen(lisnfd,5);
    Judge(ret);

    int epoll_handle = epoll_create(2);
    Judge(epoll_handle);

    struct epoll_event ee;
    ee.events = EPOLLIN;
    ee.data.fd = lisnfd;
    ret = epoll_ctl(epoll_handle,EPOLL_CTL_ADD,lisnfd,&ee);
    Judge(ret);

    while(1)
    {
        struct epoll_event arr[MAXSIZE];
        ret = epoll_wait(epoll_handle,arr,MAXSIZE,-1);
        if(ret < 0)
        {
            cout << "epoll_wait failed" << endl;
            return 0;
        }

        for(int i = 0; i < MAXSIZE; ++i)
        {
            if(arr[i].data.fd == lisnfd)
            {
                int sockfd = accept(lisnfd,NULL,NULL);
                if(sockfd < 0)
                {
                    cout << "accept failed" << endl;
                    continue;
                }
                struct epoll_event tmp;
                tmp.events = EPOLLIN;
                tmp.data.fd = sockfd;
                ret = epoll_ctl(epoll_handle,EPOLL_CTL_ADD,sockfd,&tmp);
                if(ret < 0)
                {
                    cout << "epoll_ctl failed" << endl;
                    continue;
                }
            }
            else
            {
                char buf[1024] = {0};
                ssize_t recv_size = recv(arr[i].data.fd,buf,sizeof(buf)-1,0);
                if(recv_size < 0)
                {
                    cout << "recv failed" << endl;
                    continue;
                }
                else if(recv_size == 0)
                {
                    cout << "Peer Shutdown" << endl;
                    epoll_ctl(epoll_handle,EPOLL_CTL_DEL,arr[i].data.fd,&arr[i]);
                    close(arr[i].data.fd);
                    continue;
                }
                else
                    cout << buf << endl;
            }
        }

    }

    
    return 0;
}
