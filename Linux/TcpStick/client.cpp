#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>

#include "DataType.hpp"

using namespace std;

int main()
{
    //1. 创建套接字
    int sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sockfd < 0)
    {
        cout << "TCP socket failed" << endl;
        return 0;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(18989);
    //此处我们使用的公网ip
    addr.sin_addr.s_addr = inet_addr("118.89.67.215");

    int ret = connect(sockfd,(struct sockaddr *)&addr,sizeof(addr));
    if(ret < 0)
    {
        cout << "connnect failed" << endl;
        return 0;
    }

    //3.接收和发送数据
    while(1)
    {
        char buf[1024] = {0};
        
        //发送数据
        struct DataType dt;
        dt.data1_ = 10;
        dt.data2_ = 200;
        dt.c_ = '+';
        ssize_t send_ret = send(sockfd,&dt,sizeof(dt),0); 
        if(send_ret < 0)
        {
            cout << "send failed" << endl;
            continue;
        }
        send_ret = send(sockfd,&dt,sizeof(dt),0); 
        if(send_ret < 0)
        {
            cout << "send failed" << endl;
            continue;
        }

        memset(buf,'\0',sizeof(buf));

        ssize_t recv_size = recv(sockfd,buf,sizeof(buf)-1,0);
        if(recv_size < 0)
        {
            cout << "recv failed" << endl;
            continue;
        }
        else if(recv_size == 0)
        {
            cout << "Peer close" << endl;
            close(sockfd);
            return 0;
        }
        
        cout << "recv data is : " << buf << endl;

    }

    close(sockfd);


    return 0;
}
