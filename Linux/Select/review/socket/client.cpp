#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

#include <iostream>

using namespace std;

int main()
{
    int sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sockfd < 0)
    {
        cout << "socket failed" << endl;
        return 0;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(18989);
    addr.sin_addr.s_addr = inet_addr("118.89.67.215");
    int ret = connect(sockfd,(struct sockaddr *)&addr,sizeof(addr));
    if(ret < 0)
    {
        cout << "connect failed" << endl; 
    }

    while(1)
    {
        char buf[1024] = "i am clientxxxxx\n";
        ssize_t send_size = send(sockfd,buf,strlen(buf),0);
        if(send_size < 0)
        {
            cout << "send failed" << endl;
            continue;
        }
        sleep(1);
    }
    return 0;
}
