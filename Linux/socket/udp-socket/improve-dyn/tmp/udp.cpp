#include "udp.h"

udp_class::udp_class()
{
    sockfd_ = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(sockfd_ < 0)
    {
        cout << "socket failed" << endl;
        close(sockfd_);
        exit(0);
    }
}

void udp_class::bindAddressInfo(string ip_address,uint16_t port)
{
    addr_.sin_family = AF_INET;
    addr_.sin_addr.s_addr = inet_addr(ip_address.c_str());
    addr_.sin_port = htons(port);

    socklen_t socklen = sizeof(addr_);

    int ret = bind(sockfd_,(Sock_Default *)&addr_,socklen);
    if(ret < 0)
    {
        cout << "bind failed" << endl;
        close(sockfd_);
        exit(0);
    }
}


void udp_class:: recvfromInUdp(char* buf,size_t len,struct sockaddr_in* recv_addr,socklen_t* socklen)
{
    ssize_t recv_size = recvfrom(sockfd_,buf,len,0,(Sock_Default *)recv_addr,socklen);
    if(recv_size < 0)
    {
        cout << "recvfrom failed" << endl;
        close(sockfd_);
        exit(0);
    }

}


void udp_class:: sentoInfo(char* buf,struct sockaddr_in* sendto_addr)
{
    ssize_t sen_ret = sendto(sockfd_,buf,strlen(buf),0,(Sock_Default *)sendto_addr,sizeof(*sendto_addr));
    if(sen_ret < 0)
    {
        cout << "sendto failed" << endl;
        close(sockfd_);
        exit(0);
    }
}


udp_class:: ~udp_class()
{
    close(sockfd_);
}
