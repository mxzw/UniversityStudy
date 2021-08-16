#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>

#include <iostream>

using namespace std;

int main()
{
    int sock_fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sock_fd < 0)
    {
        cout << "socket failed " << endl;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("118.89.67.215");
    addr.sin_port = htons(18989);
    int ret = connect(sock_fd,(struct sockaddr *)&addr,sizeof(addr));
    if(ret < 0)
    {
        cout << "connect failed" << endl;
        close(sock_fd);
        return 0;
    }

    while(1)
    {
        char buf[1024] = "hello server, i am client";
        ssize_t send_size = send(sock_fd,buf,strlen(buf),0);
        if(send_size < 0)
        {
            cout << "send failed" << endl;
            continue;
        }

        memset(buf,'\0',sizeof(buf));

        ssize_t recv_size = recv(sock_fd,buf,sizeof(buf)-1,0);
        if(recv_size < 0)
        {
            cout << "recv failed" << endl;
            continue;
        }
        else if(recv_size == 0)
        {
            cout << "peer shutdown" << endl;
            close(sock_fd);
            return 0;
        }

        cout << "server say:" << buf << endl;
    }

    close(sock_fd);

    return 0;
}
