#include <unistd.h>
#include <sys/epoll.h>

#include <iostream>

#define MAXSIZE 1

using namespace std;

int main()
{
    int handle = epoll_create(5);
    if(handle < 0)
    {
        cout << "epoll_create failed" << endl;
        return 0;
    }
    
    struct epoll_event ee;
    ee.events = EPOLLIN;
    ee.data.fd = 0;

    int res = epoll_ctl(handle,EPOLL_CTL_ADD,0,&ee);
    if(res < 0)
    {
        cout << "epoll_ctl failed" << endl;
        return 0;
    }

    while(1)
    {
        struct epoll_event arr[MAXSIZE];
        res = epoll_wait(handle,arr,MAXSIZE,-1);
        if(res < 0)
        {
            cout << "epoll_wait failed" << endl;
            continue;
        }
        
        for(int i = 0; i < MAXSIZE; ++i)
        {
            if(arr[i].events == EPOLLIN)
            {
                char buf[1024] = {0};
                read(arr[i].data.fd,buf,sizeof(buf)-1);
                cout << buf << endl;
            }
        }
    }

    return 0;
}

