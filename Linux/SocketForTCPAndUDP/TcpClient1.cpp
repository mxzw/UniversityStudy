#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

int main()
{
;
    int sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sock < 0)
    {
        cout << "socket failed" << endl;
        return 0;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("118.89.67.215");
    addr.sin_port = htons(18989);
   int ret =  connect(sock,(struct sockaddr *)&addr,sizeof(addr));
   if(ret < 0)
   {
       cout << "connect failed" << endl;
       return 0;
   }

   while(1)
   {
       char buf[1024] = {0};
       sprintf(buf,"Hello Server! I'am TCPClient1...");
       ret = send(sock,buf,strlen(buf),0);
       if(ret < 0)
       {
           cout << "send failed" << endl;
           continue;
       }

       memset(buf,0,sizeof(buf));
       ret = recv(sock,buf,sizeof(buf)-1,0);
       if(ret < 0)
       {
           cout << "recv failed" << endl;
           continue;
       }
       else if(ret == 0)
       {
           cout << "Peer shutdown" << endl;
           break;
       }
       cout << buf << endl;



   }
   close(sock);
    return 0;
}
