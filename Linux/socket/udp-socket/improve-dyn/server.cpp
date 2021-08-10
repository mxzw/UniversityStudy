#include "udp.h"

using namespace std;

int main()
{
    //1.创建ipv4的套接字
    udp_class uc;
    
    //创建ipv4的结构体，这也是服务端的ip和端口号
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(18989);
    //这里需要注意的是inet_addr包含在#include <arpa/inet.h>
    addr.sin_addr.s_addr = inet_addr("172.17.0.5");

    //2.绑定地址信息结构(sockaddr)
    uc.bindAddressInfo("172.17.0.5",18989);
    
    //3.接收和发送来自客户端的消息
    while(1)
    {
        sleep(1);
        char buf[1024] = {0};
        struct sockaddr_in recv_addr;
        socklen_t recvlen = sizeof(recv_addr);
        uc.recvfromInUdp(buf,sizeof(buf)-1,&recv_addr,&recvlen);
        //走到这表示接收到消息了
        printf("i am server,i recv : %s,i recv sucess %s:%d\n",buf,inet_ntoa(recv_addr.sin_addr),ntohs(recv_addr.sin_port));

        //然后开始处理和发送数据
        memset(buf,'\0',sizeof(buf));
        sprintf(buf,"hello client, i am server, %s:%d\n",inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));

        uc.sentoInfo(buf,&recv_addr);
    }
    return 0;
}
