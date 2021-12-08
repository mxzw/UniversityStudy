#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "ssocket.hpp"

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
    addr.sin_port = htons(18989);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    int ret = bind(sockfd,(struct sockaddr *)&addr,sizeof(addr));
    if(ret < 0)
    {
        close(sockfd);
        cout << "bind failed" << endl;
    }

    ret = listen(sockfd,5);
    if(ret < 0)
    {
        close(sockfd);
        cout << "listen failed" << endl;
    }

    SocketSelect ss;
    ss.SetFd(sockfd);

    while(1)
    {
        vector<int> iv;
        ret = ss.SelectWait(iv);
        if(ret < 0)
        {
            continue;
        }

        for(size_t i = 0; i < iv.size(); ++i)
        {
            if(iv[i] == sockfd)
            {
                //new con
                int newsockfd = accept(iv[i],NULL,NULL);
                if(newsockfd < 0)
                {
                    cout << "accept failed" << endl;
                    continue;
                }

                ss.SetFd(newsockfd);
            }
            else
            {
                //recv
                char buf[1024] = {0};
                ssize_t recv_size = recv(iv[i],buf,sizeof(buf)-1,0);
                if(recv_size < 0)
                {
                    cout << "recv failed" << endl;
                    continue;
                }
                else if(recv_size == 0)
                {
                    cout << "peer shutdown" << endl;
                    ss.RmFd(iv[i]);
                    close(iv[i]);
                    continue;
                }
                else
                {
                    cout << buf << endl;
                }
            }
        }
    }
    
    close(sockfd);
    return 0;
}
