#include "tcp.hpp"
#include <sstream>



void* TcpEntryPthread(void* arg)
{ 
    pthread_detach(pthread_self());
    tcp *tc = (tcp*) arg; 

    while(1)
    {
        char buf[1024] = {0};
        ssize_t ret = tc->Recv(buf,sizeof(buf)-1);
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

        printf("client say: %s\n",buf);

        memset(buf,'\0',sizeof(buf));
        sprintf(buf,"<html>It's test to HTTP!</html>");

        stringstream ss;
        //ss << "HTTP/1.1 200 OK \r\n";
        //ss << "Content-Type: text/html\r\n";
        //ss << "Content-Length: 31 \r\n";
        //ss << "\r\n";

        ss << "HTTP/1.1 302 Redirect \r\n";
        ss << "Content-Type: text/html \r\n";
        ss << "Content-Length: 31 \r\n";
        ss << "Location: https://www.bilibili.com/ \r\n";
        ss << "\r\n";

        char* tmp =(char *) ss.str().c_str();
        ret = tc->Send(tmp,strlen(tmp));
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
