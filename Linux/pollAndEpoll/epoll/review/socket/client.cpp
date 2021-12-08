#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>

using namespace std;

/*
 * 1. 创建套接字
 * 2. 建立连接请求
 * 3. TCP三次握手建立连接----OS会自动进行，不需要我们进行控制
 * 4. 接收数据、发送数据
 * 5. 关闭套接字
 */ 

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
        sprintf(buf,"hello server,i am client1\n");
        ssize_t send_ret = send(sockfd,buf,strlen(buf),0); 
        if(send_ret < 0)
        {
            cout << "send failed" << endl;
            continue;
        }
        sleep(1);

    }

    close(sockfd);


    return 0;
}
