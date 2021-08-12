#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>

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

    //2.绑定地址信息
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(18989);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    int ret = bind(sockfd,(struct sockaddr *)&addr,sizeof(addr));
    if(ret < 0)
    {
        cout << "bind failed" << endl;
        return 0;
    }

    //3.进行侦听(告诉OS内核可以与客户端建立连接了)
    //listen函数中blocklog参数，设定的是已完成三次握手并已建立连接的队列的容量
    ret = listen(sockfd,1);
    if(ret < 0)
    {
        cout << "listen failed" << endl;
        return 0;
    }
    while(1)
    {};
    return 0;

}
