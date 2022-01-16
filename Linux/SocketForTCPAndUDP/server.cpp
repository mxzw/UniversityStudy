#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/select.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
using namespace std;

#define Check(x) if(x < 0) {cout << "x failed:" << x << endl; return -1;}


void* TcpStartThread(void* arg)
{
    pthread_detach(pthread_self());
    int *socket_tcp = (int*)arg;

    while(1)
    {
        char buf[1024] = {0};
        ssize_t recv_size = recv(*socket_tcp,buf,sizeof(buf)-1,0);
        if(recv_size == 0)
        {
            cout << "Peer shutdown" << endl;
            close(*socket_tcp);
            delete socket_tcp;
            break;
        }
        else if(recv_size < 0)
        {
            cout << "recv failed" << endl;
            continue;
        }

        cout << "TCP client say : " << buf << endl;

        memset(buf,0,sizeof(buf));
        sprintf(buf,"hello client, It's TCP Server");
        /* ssize_t send_size = send(socket_tcp,buf,strlen(buf),0);
           if(send_size < 0)
           {
           cout << "send failed" << endl;
           continue;
           } */
        while(send(*socket_tcp,buf,strlen(buf),0) < 0)
        {
            cout << "send failed,resend" << endl;
        }

    }
    return NULL;
}

void* UdpStartThread(void* arg)
{
    pthread_detach(pthread_self());
    int* socket_udp = (int*) arg;
    struct sockaddr_in addr;
    socklen_t socklen = sizeof(addr);
    while(1)
    {
        char buf[1024] = {0};
        ssize_t recv_size = recvfrom(*socket_udp,buf,sizeof(buf)-1,0,(struct sockaddr*)&addr,&socklen);
        if(recv_size < 0)
        {
            cout << "recvfrom failed" << endl;
            continue;
        }
        cout << "UDP client say : " << buf << endl;
        memset(buf,0,sizeof(buf));
        sprintf(buf,"hello client,It's UDP server");
        ssize_t send_size = sendto(*socket_udp,buf,strlen(buf),0,(struct sockaddr*)&addr,sizeof(addr));
        if(send_size < 0)
        {
            cout << "sendto failed " << endl;
            continue;
        }

    }
    close(*socket_udp);
    delete socket_udp;

    return NULL;
}

int main()
{
    int socket_tcp = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    Check(socket_tcp);

    int* socket_udp = new int;
    *socket_udp = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP); 
    Check(*socket_udp);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    addr.sin_port = htons(18989);
    int bind_sz = bind(socket_tcp,(struct sockaddr *)&addr,sizeof(addr));
    Check(bind_sz);
    int bind_udpSz = bind(*socket_udp,(struct sockaddr *)&addr,sizeof(addr));
    Check(bind_udpSz);
    /*
     * TCP 和 UDP 是可以绑定同一个端口的，因为端口这个概念他实际上只是两个字节，被操作系统用来标识某个进程的
     * 当TCP 和 UDP 共用一个端口时，即便是相同ip和端口号，他所产生的文件描述符也是不也一样的，换句话说，两者进行各自
     * 数据的通讯是完全不受影响的，换句话说网络数据在传输过程中是要根据五元组信息来判断接收方的 
     * {网络协议，目的ip，目的端口，源ip，源端口}
     */
    listen(socket_tcp,5);

    // 因此就单独给UDP一个线程，让他自己去玩
    pthread_t pid;
    int thread_start = pthread_create(&pid,NULL,UdpStartThread,socket_udp);
    if(thread_start < 0)
    {
        cout << "Tcp start Thread failed" << endl;
        close(*socket_udp);
        return 0;
    }


    while(1)
    {
        pthread_t pid;

        int* newTcpSocket = new int;
        *newTcpSocket = accept(socket_tcp,NULL,NULL);
        if(*newTcpSocket < 0)
        {
            cout << "accept failed" << endl;
            continue;
        }
        //然后启动TCP的线程，进行TCP的通信
        int thread_start = pthread_create(&pid,NULL,TcpStartThread,newTcpSocket);
        if(thread_start < 0)
        {
            cout << "Tcp start Thread failed" << endl;
            continue;
        }
    }

    close(pid);
    close(socket_tcp);

    return 0;

}
