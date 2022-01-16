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
    socklen_t socklen;
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
        ssize_t send_size = sendto(*socket_udp,buf,strlen(buf),0,(struct sockaddr*)& addr,socklen);
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

    //将TCP、UDP的文件描述符加入到select中(放到可读事件集合中)
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(socket_tcp,&readfds);
    //这里有一个致命的问题，因为UDP是无连接的，所以当一个UDP数据包进来我们是不知道是否是给我们的消息，
    //只有当recvfrom的时候才能知道是发送给自己的，所以直接检测UDP的套接字是不能就绪的
    FD_SET(*socket_udp,&readfds);

    //设置最大的文件描述符（也就是select进行轮询时最大的界限）
    int nfds = *socket_udp > socket_tcp ? *socket_udp : socket_tcp;

    while(1)
    {
        //select检测到事件就绪之后，就会将没有就绪的事件从事件集合中删除，所以就需要一个tmp
        fd_set tmpFds = readfds;
        int tmpNfds = nfds;
        pthread_t pid;

        int readyNum = select(nfds,&tmpFds,NULL,NULL,NULL);
        if(readyNum < 0)
        {
            cout << "select failed" << endl;
            continue;
        }
        for(int i = 0; i < tmpNfds; ++i)
        {
            //若是检测到tcp的描述符就绪，则意味着有客户端想要进行TCP连接
            if(FD_ISSET(socket_tcp,&tmpFds))
            {
                //进行accept，并且创建相应线程,因为是在多线程的情况下，所以就要在堆上创建空间
                int* newTcpSocket = new int;
                *newTcpSocket = accept(socket_tcp,NULL,NULL);
                if(*newTcpSocket < 0)
                {
                    cout << "accept failed" << endl;
                    continue;
                }
                //将新的文件描述符加入到可读事件集合中,并更新nfds的大小
                FD_SET(*newTcpSocket,&readfds);
                nfds = nfds > *newTcpSocket ? nfds : *newTcpSocket;
                //将旧的文件描述符从tmp中删去，防止程序死循环
                FD_CLR(socket_tcp,&tmpFds);

                //然后启动TCP的线程，进行TCP的通信
                int thread_start = pthread_create(&pid,NULL,TcpStartThread,newTcpSocket);
                if(thread_start < 0)
                {
                    cout << "Tcp start Thread failed" << endl;
                    continue;
                }

            }
            else if(FD_ISSET(*socket_udp,&tmpFds))
            {
                FD_CLR(*socket_udp,&tmpFds);
                int thread_start = pthread_create(&pid,NULL,UdpStartThread,socket_udp);
                if(thread_start < 0)
                {
                    cout << "Udp start Thread failed" << endl;
                    continue;
                }
            }
        }
    } 

    close(socket_tcp);

    return 0;

}
