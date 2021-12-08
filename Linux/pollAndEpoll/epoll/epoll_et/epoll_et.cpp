#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>

#include <iostream>

using namespace std;

int main()
{

    //设置文件描述符的读写属性为非阻塞属性
    int flag = fcntl(0,F_GETFL);
    if(flag < 0)
    {
        cout << "fcntl failed" << endl;
        return -1;
    }
    
    //设置非阻塞属性
    fcntl(0,F_SETFL,flag | O_NONBLOCK);

    int epoll_handle = epoll_create(2);
    if(epoll_handle < 0)
    {
        cout << "epoll_create failed" << endl;
        return 0;
    }
    
    struct epoll_event ee;
    //设置对当前文件描述符的监控为可读事件和ET模式
    ee.events = EPOLLIN | EPOLLET;
    ee.data.fd = 0;
    int ret = epoll_ctl(epoll_handle,EPOLL_CTL_ADD,0,&ee);
    if(ret < 0)
    {
        cout << "epoll_ctl failed" << endl;
        return 0;
    }

    while(1)
    {
        struct epoll_event arr[2];
        ret = epoll_wait(epoll_handle,arr,2,-1);
        if(ret < 0)
        {
            cout << "epoll_wait failed" << endl;
            return 0;
        }

        for(int i = 0; i < 2; ++i)
        {
            if(arr[i].data.fd == 0)
            {
                string res = "";
                while(1)
                {
                    char buf[3] = {0};
                    int t = read(arr[i].data.fd,buf,sizeof(buf)-1);
                    if(t < 0)
                    {   //注意：这里当返回值小于0的时候，不一定是发生了错误
                        //由于文件描述符是非阻塞属性，因此，每次读的时候都会返回一个值
                        //若返回的错误码是EAGAIN或者EWOULDBLOCK的时候，说明此时已经将缓冲区中的内容读完了
                        if(errno == EAGAIN || errno == EWOULDBLOCK)
                            break;
                    }
                    res += buf;
                }
                cout << res << endl; 
            }
        }
    }

    return 0;
}
