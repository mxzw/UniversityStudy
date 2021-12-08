#include <unistd.h>
#include <sys/epoll.h>

#include <iostream>
using namespace std;

int main()
{
    //创建epoll操作句柄,注意这个句柄也是一个文件描述符
    int handle = epoll_create(2);
    if(handle < 0)
    {
        cout << "epoll_create failed" << endl;
        return 0;
    }

    struct epoll_event ee;
    ee.events = EPOLLIN;
    ee.data.fd = 0;

    //设置操作句柄的属性，类比fctl函数
    int ret = epoll_ctl(handle,EPOLL_CTL_ADD,0,&ee);
    if(ret < 0)
    {
        cout << "epoll_ctl failed" << endl;
        return 0;
    }

    while(1)
    {
        struct epoll_event arr[2];
        //对操作句柄进行监控，等待就绪的文件描述符
        int ret = epoll_wait(handle,arr,2,-1);
        if(ret < 0)
        {
            cout << "epoll_wait failed" << endl;
            continue;
        }

        for(int i = 0; i < 2; ++i)
        {
            if(arr[i].events == EPOLLIN)
            {
                //如果发生的是可读事件
                char buf[1024] = {0};
                read(arr[i].data.fd,buf,sizeof(buf)-1);
                printf("%s\n",buf);
            }
        }

    }
    close(handle);
    return 0;
}
