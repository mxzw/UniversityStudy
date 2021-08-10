#include "udp.h"

using namespace std;


int main()
{
    //1.创建套接字
    udp_class uc;

    //2.直接发送消息
    while(1)
    {
        sleep(1);
        char buf[1024] = {0};
        sprintf(buf,"i am client1");

        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(18989);
        addr.sin_addr.s_addr = inet_addr("172.17.0.5");

        uc.sentoInfo(buf,&addr);

        //3.接收消息
        memset(buf,'\0',sizeof(buf));
        
        struct sockaddr_in recv_addr;
        socklen_t socklen = sizeof(recv_addr);

        uc.recvfromInUdp(buf,sizeof(buf)-1,&recv_addr,&socklen);

        printf("%s\n",buf);
    }

    return 0;
}
