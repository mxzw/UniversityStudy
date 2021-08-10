#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

class udp_class
{
    public:
        udp_class();

        void bindAddressInfo(string ip_address,uint16_t port);

        void recvfromInUdp(char* buf,size_t len,struct sockaddr_in* recv_addr,socklen_t* socklen);
        void sentoInfo(char* buf,struct sockaddr_in* sendto_addr);
        ~udp_class();
    protected:
        typedef struct sockaddr_in Sock_UDP;
        typedef struct sockaddr Sock_Default;

    private:
        int sockfd_;
        Sock_UDP addr_;

};
