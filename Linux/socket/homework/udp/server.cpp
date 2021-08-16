#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include <iostream>

using namespace std;


int main()
{
    int sock_fd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(sock_fd < 0)
    {
        cout << "socket failed" << endl;
        return 0;
    }
    struct sockaddr_in binAddr;
    binAddr.sin_family = AF_INET;
    binAddr.sin_addr.s_addr = inet_addr("0.0.0.0");
    binAddr.sin_port = htons(18989);
    int ret = bind(sock_fd,(struct sockaddr *)&binAddr,sizeof(binAddr));
    if(ret < 0)
    {
        cout << "bind failed" << endl;
        close(sock_fd);
        return 0;
    }

    while(1)
    {
        char buf[1024] = {0};
        struct sockaddr_in addr;
        socklen_t socklen = sizeof(addr);
        ssize_t recv_size = recvfrom(sock_fd,buf,sizeof(buf)-1,0,(struct sockaddr*)&addr,&socklen);
        if(recv_size < 0)
        {
            cout << "recv failed" << endl;
            break;
        }

        printf("\n client is from : %s : %d ",inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));
        cout << "and client say: " << buf << endl;

        memset(buf,'\0',sizeof(buf));
        sprintf(buf,"hello client ,i am server\n");

        ssize_t send_size = sendto(sock_fd,buf,strlen(buf),0,(struct sockaddr *)&addr,socklen);
        if(send_size < 0)
        {
            cout << "sendto failed" << endl;
            break;
        }

    }
    close(sock_fd);
    return 0;
}

