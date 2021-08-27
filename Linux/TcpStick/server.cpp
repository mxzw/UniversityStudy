#include <vector>
#include <algorithm>
#include "tcp.hpp"


ssize_t tcp::Recv(struct DataType* dt)
{
    ssize_t ret = recv(sockfd_,dt,sizeof(*dt),0);
    if(ret < 0)
    {
        cout << "recv failed" << endl;
    }
    return ret;
}


int Sum(struct DataType* dt)
{
    int ret = -1;
    if(dt->c_ == '+')
    {
        ret = dt->data1_ + dt->data2_;
    }

    return ret;
}


void* TcpEntryPthread(void* arg)
{
    pthread_detach(pthread_self());
    tcp *tc = (tcp*) arg; 

    while(1)
    {
        struct DataType dt;

        ssize_t ret = tc->Recv(&dt);
        if(ret < 0)
        {
            cout << "recv failed" << endl;
            continue;
        }
        else if(ret == 0)
        {
            cout << "peer close" << endl;
            break;
        }

        printf("client say: %d,%d,'%c'\n",dt.data1_,dt.data2_,dt.c_);
        

        int sum_ret = Sum(&dt);

        char buf[1024] = {0};
        sprintf(buf,"%d\n",sum_ret);
        
        ret = tc->Send(buf,strlen(buf));
        if(ret < 0)
        {
            cout << "send failed" << endl;
            continue;
        }
    }

    delete tc;
    return nullptr;
}

int main()
{
    tcp tc;
    int ret = tc.createSockfd();
    if(ret < 0)
        return -1;
    //默认ip 0.0.0.0，默认端口18989
    ret = tc.Bind();
    if(ret < 0)
        return -1;
    //默认已完成连接队列大小为2
    ret = tc.Listen();
    if(ret < 0)
        return -1;

    while(1)
    {
        struct sockaddr_in addr;
        socklen_t socklen = sizeof(addr);
        int new_sockfd = tc.Accept(&addr,&socklen);
        if(new_sockfd < 0)
        {
            cout << "Please again to accept" << endl;
            continue;
        }

        //从这里开始创建工作线程
        //如果只是单纯的将new_sockfd传过去的话，是不行的
        //因为它是一个局部变量，因此，我们需要在堆上开辟出一个空间
        tcp *t = new tcp(new_sockfd);
        if(t == nullptr)
        {
            cout << "new class tcp failed" << endl;
            continue;
        }

        pthread_t tid;
        ret = pthread_create(&tid,NULL,TcpEntryPthread,t);
        if(ret < 0)
        {
            cout << "pthread_create failed" << endl;
            delete t;
            continue;
        }
    }


}
