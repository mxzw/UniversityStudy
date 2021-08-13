#include <unistd.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>

using namespace std;

void signalcallBack(int)
{
    wait(NULL);
    return;
}

int main()
{
    signal(SIGCHLD,signalcallBack);
   
    //创建套接字
    int listen_sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(listen_sock < 0)
    {
        cout << "socket failed" << endl;
        return 0;
    }
    
    //绑定地址信息
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(18989);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    int ret = bind(listen_sock,(struct sockaddr *)&addr,sizeof(addr));
    if(ret < 0)
    {
        cout << "bind failed" << endl;
        return 0;
    }

    //帧听
    ret = listen(listen_sock,1);
    if(ret < 0)
    {
        cout << "listen failed" << endl;
        return 0;
    }

    while(1)
    {
        struct sockaddr_in peer_addr;
        socklen_t peerlen;
        int new_sockfd = accept(listen_sock,(struct sockaddr *)&peer_addr,&peerlen);
        if(new_sockfd < 0)
        {
            cout << "accept failed" << endl;
            return 0;
        }
        pid_t fork_ret = fork();
        if(fork_ret < 0)
        {
            cout << "fork failed" << endl;
            continue;
        }
        else if(fork_ret == 0)
        {
            close(listen_sock);
            //child
            //在子进程中只实现接收和发送数据
            while(1)
            {
                char buf[1024] = {0};
                ssize_t recv_size = recv(new_sockfd,buf,sizeof(buf)-1,0);
                if(recv_size < 0)
                {
                    cout << "recv failed" << endl;
                    continue;
                }
                else if(recv_size == 0)
                {
                    cout << "peer failed" << endl;
                    break;
                }

                cout << "i recv: " << buf << endl;

                //接收数据
                memset(buf,'\0',sizeof(buf));
                sprintf(buf,"hello client,%s:%d\n",inet_ntoa(peer_addr.sin_addr),ntohs(peer_addr.sin_port));
                ssize_t send_size = send(new_sockfd,buf,strlen(buf),0);
                if(send_size < 0)
                {
                    cout << "send failed" << endl;
                    break;
                }
            }
        }

        else
        {
            //father
            //要进行进程等待，防止子进程变成僵尸进程
            //但是还存在着的问题是，该父进程可能会创建多个子进程
            //若是直接在父进程中进行进程等待的话，就意味着若只有一个子进程退出
            //父进程也会随之等待到资源，然后continue上去会陷入到accept的逻辑中
            //因此，我们需要设置信号，自定义信号的处理逻辑，每当有一个sigchild信号发送出来的时候，我们让其在自定义的处理函数进行进程等待即可
            continue;
        }
    }

    return 0;
}
