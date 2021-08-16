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
        cout << "socket failed " << endl;
        return 0;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("118.89.67.215");
    addr.sin_port = htons(18989);

    while(1)
    {
        char buf[1024] = {0};
        sprintf(buf,"hello server, i am client\n");
        ssize_t send_size = sendto(sock_fd,buf,strlen(buf),0,(struct sockaddr * )&addr,sizeof(addr));
        if(send_size < 0)
        {
            cout << "sendto failed" << endl;
            break;
        }

        memset(buf,'\0',sizeof(buf));
        struct sockaddr_in recvAddr;
        socklen_t socklen = sizeof(recvAddr);
        ssize_t recv_size = recvfrom(sock_fd,buf,sizeof(buf)-1,0,(struct sockaddr *)&recvAddr,&socklen);
        if(recv_size < 0)
        {
            cout << "recvfrom failed" << endl;
            break;
        }
        cout << "server say: " << buf << endl;
    }

    close(sock_fd);
    return 0;
}
