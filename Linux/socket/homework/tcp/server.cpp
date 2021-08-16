#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>

#include <iostream>

using namespace std;

void* ThreadEntry(void* arg)
{
    pthread_detach(pthread_self());
    int* newSock_fd = (int*) arg;
    while(1)
    {
        char buf[1024] = {0};
        ssize_t recv_size = recv(*newSock_fd,buf,sizeof(buf)-1,0); 
        if(recv_size < 0)
        {
            cout << "recv failed" << endl;
            continue;
        }
        else if(recv_size == 0)
        {
            cout << "peer shutdown" << endl;
            close(*newSock_fd);
            delete newSock_fd;
            return NULL;
        }

        cout << "client say: " << buf << endl;

        memset(buf,'\0',sizeof(buf));
        sprintf(buf,"hello client ,i am server\n");

        ssize_t send_size = send(*newSock_fd,buf,strlen(buf),0);
        if(send_size < 0)
        {
            cout << "send failed" << endl;
            continue;
        }
    }
    close(*newSock_fd);
    delete newSock_fd;
    return NULL;
}

int main()
{
    int sock_fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sock_fd < 0)
    {
        cout << "socket failed " << endl;
        return 0;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    addr.sin_port = htons(18989);
    int ret = bind(sock_fd,(struct sockaddr *)&addr,sizeof(addr));
    if(ret < 0)
    {
        cout << "bind failed" << endl;
        close(sock_fd);
        return 0;
    }

    ret = listen(sock_fd,5);
    if(ret < 0)
    {
        cout << "listen failed" << endl;
        close(sock_fd);
        return 0;
    }

    while(1)
    {
        
        struct sockaddr_in acceptAddr;
        socklen_t socklen = sizeof(acceptAddr);
        int newSock_fd = accept(sock_fd,(struct sockaddr *)&acceptAddr,&socklen);
        if(newSock_fd < 0)
        {
            cout << "accept failed" << endl;
            continue;
        }

        pthread_t pid;
        int* fd = new int(newSock_fd);
        ret = pthread_create(&pid,NULL,ThreadEntry,fd);
        if(ret < 0)
        {
            cout << "pthread_create failed" << endl;
            delete fd;
            close(newSock_fd);
            close(sock_fd);
            return 0;
        }
        
    }

    close(sock_fd);
    return 0;
}
