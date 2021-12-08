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

    //2.进行连接
    //0.0.0.0：任意网卡地址，注意不是任一，它的含义就是哪个网卡地址都行
    //当服务器端绑定的地址为0.0.0.0，那么我们客户端想要与服务端建立连接的时候
    //有两种方法： 
    //1.若是运行服务器的这台机器本身是能够上网的，那么我们只需要连接它的网卡地址中的任意一个就行，(0.0.0.0为任意地址)
    //2.若是运行服务器的这台机器是要经过类似于腾讯云、阿里云这样的云服务器读对私网ip进行转换才能上网的，那么我们就需要连接它的公网ip。
    
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
        //这里接收数据和发送数据是没有顺序而言的
        //因为已经经过三次握手，客户端和服务端的连接以及建立成功了
        char buf[1024] = {0};
        
        //发送数据
        sprintf(buf,"hello server,i am client2\n");
        ssize_t send_ret = send(sockfd,buf,strlen(buf),0); 
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
