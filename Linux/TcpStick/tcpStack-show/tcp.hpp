#pragma once

#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include <string>
#include <iostream>

#include "DataType.hpp"


using namespace std;

class tcp
{
    public:
        tcp() : sockfd_(-1)
        {}
        tcp(int sock) : sockfd_(sock)
        {}
        ~tcp()
        {
            close(sockfd_);
        }

        int createSockfd()
        {
            sockfd_ = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            if(sockfd_ < 0)
            {
                cout << "socket failed" << endl;
                return -1;
            }
            return sockfd_;
        }

        int Bind(string ip = "0.0.0.0",uint16_t port = 18989)
        {
            struct sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            addr.sin_addr.s_addr = inet_addr(ip.c_str());


            int ret = bind(sockfd_,(struct sockaddr *)&addr,sizeof(addr));
            if(ret < 0)
            {
                cout << "bind failed" << endl;
                return -1;
            }
            return ret;
        }

        int Listen(int backlog = 2)
        {
            int ret = listen(sockfd_,backlog);
            if(ret < 0)
            {
                cout << "listen failed" << endl;
                return -1;
            }
            return ret;
        }

        int Accept(struct sockaddr_in* addr,socklen_t* socklen)
        {
            int new_sockfd = accept(sockfd_,(struct sockaddr *)addr,socklen);
            if(new_sockfd < 0)
            {
                cout << "accept failed" << endl;
                return -1;
            }
            return new_sockfd;
        }

        ssize_t Recv(char* buf,size_t len)
        {
            ssize_t ret = recv(sockfd_,buf,len,0);
            if(ret < 0)
            {
                cout << "recv failed" << endl;
            }
            return ret;
        }

        ssize_t Send(char* buf,size_t len)
        {
            ssize_t ret =  send(sockfd_,buf,len,0);
            if(ret < 0)
            {
                cout << "send faild" << endl;
                return -1;
            }

            return ret;
        }
        ssize_t Recv(struct DataType* dt);
    
    private:
        int sockfd_;
};
