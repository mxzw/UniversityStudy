#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string.h>
#include <string.h>
#include <iostream>
using namespace std;


int main()
{

    int sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(sock < 0)
    {
        cout << "socket failed" << endl;
        return 0;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("118.89.67.215");
    addr.sin_port = htons(18989);

    while(1)
    {
        char buf[1024] = {0};
        sprintf(buf,"It's UDP Client1, I want to communicate with you ");
        ssize_t ret = sendto(sock, buf,strlen(buf),0,(struct sockaddr *)&addr,sizeof(addr));
        if(ret < 0)
        {
            cout << "sendto failed" << endl;
            continue;
        }
        memset(buf,0,sizeof(buf));
        ret = recvfrom(sock,buf,sizeof(buf)-1,0,NULL,NULL);
        if(ret < 0)
        {
            cout << "recvfrom failed" << endl;
            continue;
        }
        cout << buf << endl;
    }
    return 0;
}
