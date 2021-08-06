#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>

using namespace std;

int main()
{
    //1.创建套接字
    int sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(sockfd < 0)
    {
        cout << "socket failed" << endl;
        return 0;
    }

    //2.直接发送消息
    while(1)
    {
        char buf[1024] = {0};
        sprintf(buf,"i am client2");

        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(18989);
        addr.sin_addr.s_addr = inet_addr("172.17.0.5");
        ssize_t s_ret = sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&addr,sizeof(addr));
        if(s_ret < 0)
        {
            cout << "sento failed" << endl;
            return 0;
        }

        //3.接收消息
        memset(buf,'\0',sizeof(buf));
        
        struct sockaddr_in recv_addr;
        socklen_t socklen = sizeof(recv_addr);

        ssize_t recv_ret = recvfrom(sockfd,buf,sizeof(buf)-1,0,(struct sockaddr *)&recv_addr,&socklen);
        if(recv_ret < 0)
        {
            cout << "recvfrom failed" << endl;
            return 0;
        }
        printf("%s\n",buf);
    }

    return 0;
}
